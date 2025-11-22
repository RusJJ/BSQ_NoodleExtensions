#pragma once

#include <optional>

#include "tracks/shared/Vector.h"

#include "GlobalNamespace/BeatmapObjectSpawnController.hpp"
#include "GlobalNamespace/NoteLineLayer.hpp"
#include "NELogger.h"
#include "SpawnDataHelper.h"

#include "GlobalNamespace/BeatmapObjectSpawnMovementData.hpp"
#include "GlobalNamespace/BeatmapObjectData.hpp"
#include "GlobalNamespace/NoteData.hpp"
#include "GlobalNamespace/BeatmapObjectSpawnController.hpp"

#include "custom-json-data/shared/CustomBeatmapData.h"
#include "NECaches.h"

namespace GlobalNamespace {
class BeatmapObjectSpawnMovementData;
class BeatmapObjectData;
class BeatmapObjectSpawnMovementData;
struct NoteLineLayer;
} // namespace GlobalNamespace

namespace SpawnDataHelper {

using namespace GlobalNamespace;

static inline float const kHalfJumpDistanceEpsilon = 0.001f;

// CoreMathUtils.CalculateHalfJumpDurationInBeats
constexpr float CalculateHalfJumpDurationInBeats(float startHalfJumpDurationInBeats, float maxHalfJumpDistance,
                                                 float noteJumpMovementSpeed, float oneBeatDuration,
                                                 float noteJumpStartBeatOffset) {
  float num = startHalfJumpDurationInBeats;
  float num2 = noteJumpMovementSpeed * oneBeatDuration;
  float num3 = num2 * num;
  maxHalfJumpDistance -= 0.001f;
  while (num3 > maxHalfJumpDistance) {
    num /= 2.0f;
    num3 = num2 * num;
  }
  num += noteJumpStartBeatOffset;
  if (num < 0.25f) {
    num = 0.25f;
  }
  return num;
}

constexpr float OneBeatDuration(float bpm) {
  if (bpm <= 0.0f) {
    return 0.0f;
  }
  return 60.0f / bpm;
}

constexpr float GetJumpDuration(std::optional<float> inputNjs,
                                std::optional<float> inputOffset) {

  if (!inputNjs && !inputOffset) {
    return NECaches::VariableMovementDataProvider->get_jumpDuration();
  }

  float njs = inputNjs.value_or(NECaches::VariableMovementDataProvider->get_noteJumpSpeed());
  float spawnOffset = inputOffset.value_or(NECaches::InitData->noteJumpValue);
  auto valueType = NECaches::InitData->noteJumpValueType;
  if (valueType == GlobalNamespace::BeatmapObjectSpawnMovementData::NoteJumpValueType::JumpDuration) {
    return spawnOffset * 2.0f;
  }

  auto movementData = NECaches::beatmapObjectSpawnController->beatmapObjectSpawnMovementData;

  float oneBeatDuration = OneBeatDuration(NECaches::InitData->beatsPerMinute);
  float halfJumpDurationInBeats =
      CalculateHalfJumpDurationInBeats(movementData->_startHalfJumpDurationInBeats, 
                                       movementData->_maxHalfJumpDistance,
                                       njs, oneBeatDuration,
                                       spawnOffset);

  return oneBeatDuration * halfJumpDurationInBeats * 2.0f;
}

inline float GetSpawnAheadTime(std::optional<float> inputNjs,
                               std::optional<float> inputOffset) {
  float moveDuration = GlobalNamespace::VariableMovementDataProvider::kMoveDuration;
  return moveDuration + (GetJumpDuration(inputNjs, inputOffset) * 0.5f);
}

float HighestJumpPosYForLineLayer(float lineLayer);

float GetGravityBase(float noteLineLayer, float beforeJumpLineLayer);

float LineYPosForLineLayer(float height);

constexpr NEVector::Vector2 Get2DNoteOffset(float lineIndex, int noteLinesCount, float lineLayer) {
  float distance = -(float(noteLinesCount) - 1.0f) * 0.5f;
  return { (distance + lineIndex) * NECaches::get_noteLinesDistanceFast(), LineYPosForLineLayer(lineLayer) };
}

constexpr NEVector::Vector3 GetNoteOffset(GlobalNamespace::BeatmapObjectSpawnMovementData* spawnMovementData,
                                          float lineIndex, float lineLayer) {
  NEVector::Vector2 coords = Get2DNoteOffset(lineIndex, spawnMovementData->noteLinesCount, lineLayer);
  return NEVector::Vector3(0, coords.y, 0) + NEVector::Vector3::op_Multiply(spawnMovementData->_rightVec, coords.x);
}

constexpr UnityEngine::Vector3 GetObstacleOffset(GlobalNamespace::BeatmapObjectSpawnMovementData* spawnMovementData,
                                                 float lineIndex, float lineLayer) {
  UnityEngine::Vector3 result = GetNoteOffset(spawnMovementData, lineIndex, lineLayer);
  result.y += -0.15f;
  return result;
}

} // namespace SpawnDataHelper