#include "NELogger.h"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "beatsaber-hook/shared/utils/hooking.hpp"

#include "UnityEngine/Bounds.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Time.hpp"

#include "GlobalNamespace/ObstacleController.hpp"
#include "GlobalNamespace/PlayerHeadAndObstacleInteraction.hpp"
#include "GlobalNamespace/BeatmapObjectManager.hpp"
#include "System/Collections/Generic/HashSet_1.hpp"
#include "System/Action_1.hpp"
#include "tracks/shared/Vector.h"
#include "AssociatedData.h"

#include "FakeNoteHelper.h"
#include "NEHooks.h"
#include "custom-json-data/shared/CustomBeatmapData.h"
#include "custom-json-data/shared/VList.h"

using namespace GlobalNamespace;
using namespace UnityEngine;

MAKE_HOOK_MATCH(PlayerHeadAndObstacleInteraction_RefreshIntersectingObstacles,
                &PlayerHeadAndObstacleInteraction::RefreshIntersectingObstacles, void,
                PlayerHeadAndObstacleInteraction* self, Vector3 worldPos) {

    bool noodleHookEnabled = Hooks::isNoodleHookEnabled();

    // TRANSPILE ORIGINAL START
    int frameCount = UnityEngine::Time::get_frameCount();
    if (self->_lastFrameNumCheck == frameCount) {
      NELogger::Logger.debug("Skipping RefreshIntersectingObstacles call in frame {}", frameCount);
      return;
    }
    self->_lastFrameNumCheck = frameCount;

    for (auto& obstacleController : static_cast<ListW<UnityW<GlobalNamespace::ObstacleController>>>(self->_beatmapObjectManager->activeObstacleControllers)) {
      // TODO: Maybe delete it? It's not supposed to be null here, will keep it just in case
      if (!obstacleController) {
        continue;
      };

      // Noodle Specific processing 
      if (noodleHookEnabled) {
        // Skip zero size obstacles 
        if (NEVector::Vector3(obstacleController->bounds.get_size()) == NEVector::Vector3::zero()) {
          continue;
        }
 
        auto obstacleData = il2cpp_utils::try_cast<CustomJSONData::CustomObstacleData>(obstacleController->obstacleData);
        if (obstacleData) {
          auto& ad = getAD(obstacleData.value()->customData);
          bool isFake = ad.objectData.fake.value_or(false);
          if (isFake) {
            continue;
          }
        };
      }
      /// Noodle Specific processing end
      
      if (!obstacleController  || obstacleController->get_isActiveAndEnabled()) {
        if (!obstacleController->hasPassedAvoidedMark) {
          auto vector = obstacleController->transform->InverseTransformPoint(worldPos);
          if (obstacleController->bounds.Contains(vector)) {
            if (!self->_intersectingObstacles->Contains(obstacleController)) {
              self->_intersectingObstacles->Add(obstacleController);
              auto* action = self->headDidEnterObstacleEvent;
              if (action != nullptr) {
                action->Invoke(obstacleController);
              }
            }
          } else {
            self->_intersectingObstacles->Remove(obstacleController);
          }
        }
      }
    }
    // TRANSPILE ORIGINAL END
}

void InstallPlayerHeadAndObstacleInterationHooks() {
  INSTALL_HOOK_ORIG(NELogger::Logger, PlayerHeadAndObstacleInteraction_RefreshIntersectingObstacles);
}

NEInstallHooks(InstallPlayerHeadAndObstacleInterationHooks);