#include "tracks/shared/Animation/Track.h"
#include "tracks/shared/AssociatedData.h"
#include "Animation/ParentObject.h"

#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "beatsaber-hook/shared/utils/hooking.hpp"

#include "GlobalNamespace/BeatmapObjectManager.hpp"
#include "GlobalNamespace/NoteController.hpp"
#include "GlobalNamespace/ObstacleController.hpp"
#include "GlobalNamespace/SliderController.hpp"

#include "NEHooks.h"
#include "custom-json-data/shared/CustomBeatmapData.h"

using namespace GlobalNamespace;

MAKE_HOOK_MATCH(BeatmapObjectManager_Note_Despawn,
                static_cast<void (GlobalNamespace::BeatmapObjectManager::*)(GlobalNamespace::NoteController*)>(
                    &GlobalNamespace::BeatmapObjectManager::Despawn),
                void, BeatmapObjectManager* self, NoteController* noteController) {
  if (!Hooks::isNoodleHookEnabled()) return BeatmapObjectManager_Note_Despawn(self, noteController);

  auto customNoteData = il2cpp_utils::try_cast<CustomJSONData::CustomNoteData>(noteController->noteData);

  if (customNoteData && customNoteData.value()->customData && customNoteData.value()->customData->value) {
    auto const& tracks = TracksAD::getAD(customNoteData.value()->customData).tracks;
    if (!tracks.empty()) {
      auto go = noteController->get_gameObject();
      for (auto const& track : tracks) {
        track.UnregisterGameObject(go);
      }
    }
  }
  BeatmapObjectManager_Note_Despawn(self, noteController);
}

MAKE_HOOK_MATCH(BeatmapObjectManager_Obstacle_Despawn,
                static_cast<void (GlobalNamespace::BeatmapObjectManager::*)(GlobalNamespace::ObstacleController*)>(
                    &GlobalNamespace::BeatmapObjectManager::Despawn),
                void, BeatmapObjectManager* self, ObstacleController* obstacleController) {
  if (!Hooks::isNoodleHookEnabled()) return BeatmapObjectManager_Obstacle_Despawn(self, obstacleController);

  auto customObstacleData =
      il2cpp_utils::try_cast<CustomJSONData::CustomObstacleData>(obstacleController->obstacleData);

  if (customObstacleData && customObstacleData.value()->customData && customObstacleData.value()->customData->value) {
    auto const& tracks = TracksAD::getAD(customObstacleData.value()->customData).tracks;
    if (!tracks.empty()) {
      auto go = obstacleController->get_gameObject();
      for (auto const& track : tracks) {
        track.UnregisterGameObject(go);
      }
    }
  }
  BeatmapObjectManager_Obstacle_Despawn(self, obstacleController);
}

MAKE_HOOK_MATCH(BeatmapObjectManager_Slider_Despawn,
                static_cast<void (GlobalNamespace::BeatmapObjectManager::*)(GlobalNamespace::SliderController*)>(
                    &GlobalNamespace::BeatmapObjectManager::Despawn),
                void, BeatmapObjectManager* self, SliderController* sliderController) {
  if (!Hooks::isNoodleHookEnabled()) return BeatmapObjectManager_Slider_Despawn(self, sliderController);

  auto customSliderData =
      il2cpp_utils::try_cast<CustomJSONData::CustomSliderData>(sliderController->sliderData);

  if (customSliderData && customSliderData.value()->customData && customSliderData.value()->customData->value) {
    auto const& tracks = TracksAD::getAD(customSliderData.value()->customData).tracks;
    if (!tracks.empty()) {
      auto go = sliderController->get_gameObject();
      for (auto const& track : tracks) {
        track.UnregisterGameObject(go);
      }
    }
  }
  BeatmapObjectManager_Slider_Despawn(self, sliderController);
}

MAKE_HOOK_MATCH(BeatmapObjectManager_Note_Spawn, &GlobalNamespace::BeatmapObjectManager::AddSpawnedNoteController, void,
                BeatmapObjectManager* self, ::GlobalNamespace::NoteController* noteController,
                ::GlobalNamespace::NoteSpawnData noteSpawnData) {
  if (!Hooks::isNoodleHookEnabled()) return BeatmapObjectManager_Note_Spawn(self, noteController, noteSpawnData);
  BeatmapObjectManager_Note_Spawn(self, noteController, noteSpawnData);

  auto customNoteData = il2cpp_utils::try_cast<CustomJSONData::CustomNoteData>(noteController->noteData);
  if (customNoteData && customNoteData.value()->customData && customNoteData.value()->customData->value) {
    auto const& tracks = TracksAD::getAD(customNoteData.value()->customData).tracks;
    if (!tracks.empty()) {
      auto go = noteController->get_gameObject();
      for (auto const& track : tracks) {
        track.RegisterGameObject(go);
      }
    }
  }
}

MAKE_HOOK_MATCH(BeatmapObjectManager_Obstacle_Spawn,
                &GlobalNamespace::BeatmapObjectManager::AddSpawnedObstacleController, void,
                BeatmapObjectManager* self, ::GlobalNamespace::ObstacleController* obstacleController,
                ::GlobalNamespace::ObstacleSpawnData obstacleSpawnData) {
  if (!Hooks::isNoodleHookEnabled())
    return BeatmapObjectManager_Obstacle_Spawn(self, obstacleController, obstacleSpawnData);
  BeatmapObjectManager_Obstacle_Spawn(self, obstacleController, obstacleSpawnData);

  auto customObstacleData =
      il2cpp_utils::try_cast<CustomJSONData::CustomObstacleData>(obstacleController->obstacleData);
  if (customObstacleData && customObstacleData.value()->customData && customObstacleData.value()->customData->value) {
    auto const& tracks = TracksAD::getAD(customObstacleData.value()->customData).tracks;
    if (!tracks.empty()) {
      auto go = obstacleController->get_gameObject();
      for (auto const& track : tracks) {
        track.RegisterGameObject(go);
      }
    }
  }
}

MAKE_HOOK_MATCH(BeatmapObjectManager_Slider_Spawn,
                &GlobalNamespace::BeatmapObjectManager::AddSpawnedSliderController, void,
                BeatmapObjectManager* self, ::GlobalNamespace::SliderController* sliderController,
                ::GlobalNamespace::SliderSpawnData sliderSpawnData) {
  if (!Hooks::isNoodleHookEnabled()) return BeatmapObjectManager_Slider_Spawn(self, sliderController, sliderSpawnData);
  BeatmapObjectManager_Slider_Spawn(self, sliderController, sliderSpawnData);

  auto customSliderData =
      il2cpp_utils::try_cast<CustomJSONData::CustomSliderData>(sliderController->sliderData);
  if (customSliderData && customSliderData.value()->customData && customSliderData.value()->customData->value) {
    auto const& tracks = TracksAD::getAD(customSliderData.value()->customData).tracks;
    if (!tracks.empty()) {
      auto go = sliderController->get_gameObject();
      for (auto const& track : tracks) {
        track.RegisterGameObject(go);
      }
    }
  }
}

void InstallBeatmapObjectManagerHooksTrack() {
  INSTALL_HOOK(NELogger::Logger, BeatmapObjectManager_Note_Despawn);
  INSTALL_HOOK(NELogger::Logger, BeatmapObjectManager_Obstacle_Despawn);
  INSTALL_HOOK(NELogger::Logger, BeatmapObjectManager_Slider_Despawn);

  INSTALL_HOOK(NELogger::Logger, BeatmapObjectManager_Note_Spawn);
  INSTALL_HOOK(NELogger::Logger, BeatmapObjectManager_Obstacle_Spawn);
  INSTALL_HOOK(NELogger::Logger, BeatmapObjectManager_Slider_Spawn);
}

NEInstallHooks(InstallBeatmapObjectManagerHooksTrack);