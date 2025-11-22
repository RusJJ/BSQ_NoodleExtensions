#include "Animation/NoodleMovementDataProvider.hpp"
#include "AssociatedData.h"

#include "GlobalNamespace/BeatmapObjectSpawnMovementData.hpp"
#include "GlobalNamespace/CoreMathUtils.hpp"
#include "NECaches.h"
#include "SpawnDataHelper.h"

DEFINE_TYPE(NoodleExtensions, NoodleMovementDataProvider);

NoodleExtensions::NoodleMovementDataProvider* NoodleExtensions::NoodleMovementDataProvider::InitObject(GlobalNamespace::BeatmapObjectData* beatmapObjectData) {
  jumpDistanceOverride = std::nullopt;
  jumpDurationOverride = std::nullopt;
  halfJumpDurationOverride = std::nullopt;
  spawnAheadTimeOverride = std::nullopt;
  noteJumpSpeedOverride = std::nullopt;
  moveStartPositionOverride = std::nullopt;
  moveEndPositionOverride = std::nullopt;
  jumpEndPositionOverride = std::nullopt;

  static auto* customObstacleDataClass = classof(CustomJSONData::CustomObstacleData*);
  static auto* customNoteDataClass = classof(CustomJSONData::CustomNoteData*);
  static auto* customSliderDataClass = classof(CustomJSONData::CustomSliderData*);

  CustomJSONData::JSONWrapper* customDataWrapper = nullptr;
  if (beatmapObjectData->klass == customObstacleDataClass) {
    customDataWrapper = ((CustomJSONData::CustomObstacleData*)beatmapObjectData)->customData;
  } else if (beatmapObjectData->klass == customNoteDataClass) {
    customDataWrapper = ((CustomJSONData::CustomNoteData*)beatmapObjectData)->customData;
  } else if (beatmapObjectData->klass == customSliderDataClass) {
    customDataWrapper = ((CustomJSONData::CustomSliderData*)beatmapObjectData)->customData;
  }
  BeatmapObjectAssociatedData& ad = getAD(customDataWrapper);

  if (!ad.parsed) return this;

  if (!ad.objectData.noteJumpMovementSpeed.has_value() && !ad.objectData.noteJumpStartBeatOffset.has_value()) return this;

  noteJumpSpeedOverride = ad.objectData.noteJumpMovementSpeed;

  float njs = get_noteJumpSpeed();
  float spawnOffset = ad.objectData.noteJumpStartBeatOffset.value_or(noteJumpStartBeatOffset);
  switch (noteJumpValueType) {
    case GlobalNamespace::BeatmapObjectSpawnMovementData::NoteJumpValueType::JumpDuration: {
      jumpDurationOverride = spawnOffset * 2.0f;
      halfJumpDurationOverride = spawnOffset;
      break;
    }
     
    case GlobalNamespace::BeatmapObjectSpawnMovementData::NoteJumpValueType::BeatOffset: {
      float halfJumpDurationInBeats = GlobalNamespace::CoreMathUtils::CalculateHalfJumpDurationInBeats(
        beatmapObjectSpawnMovementData->_startHalfJumpDurationInBeats,
        beatmapObjectSpawnMovementData->_maxHalfJumpDistance,
        njs,
        oneBeatDuration,
        spawnOffset);

      float halfJump = oneBeatDuration * halfJumpDurationInBeats;
      halfJumpDurationOverride = halfJump;
      jumpDurationOverride = halfJump * 2.0f;
      break;
    }
     
    default:
      NELogger::Logger.error("Unknown NoteJumpValueType {}", (int)noteJumpValueType);
      break;
  }

  spawnAheadTimeOverride = GlobalNamespace::VariableMovementDataProvider::kMoveDuration + get_halfJumpDuration();

  float jumpDist = njs * get_jumpDuration();
  jumpDistanceOverride = jumpDist;
  float halfJumpDistance = jumpDist * 0.5f;
  NEVector::Vector3 center = beatmapObjectSpawnMovementData->centerPos;
  NEVector::Vector3 forward = NEVector::Vector3::forward();
  
  moveStartPositionOverride = center + (forward * (GlobalNamespace::VariableMovementDataProvider::kMoveDistance + halfJumpDistance));
  moveEndPositionOverride = center + (forward * halfJumpDistance);
  jumpEndPositionOverride = center - (forward * halfJumpDistance);
  return this;
}

bool NoodleExtensions::NoodleMovementDataProvider::get_wasUpdatedThisFrame() {
  return original->get_wasUpdatedThisFrame();
}

float NoodleExtensions::NoodleMovementDataProvider::get_jumpDistance() {
  return jumpDistanceOverride.value_or(original->get_jumpDistance());
}

float NoodleExtensions::NoodleMovementDataProvider::get_jumpDuration() {
  return jumpDurationOverride.value_or(original->get_jumpDuration());
}

float NoodleExtensions::NoodleMovementDataProvider::get_halfJumpDuration() {
  return halfJumpDurationOverride.value_or(original->get_halfJumpDuration());
}

float NoodleExtensions::NoodleMovementDataProvider::get_moveDuration() {
  return original->get_moveDuration();
}

float NoodleExtensions::NoodleMovementDataProvider::get_spawnAheadTime() {
  return spawnAheadTimeOverride.value_or(original->get_spawnAheadTime());
}

float NoodleExtensions::NoodleMovementDataProvider::get_waitingDuration() {
  return 0.0f;
}

float NoodleExtensions::NoodleMovementDataProvider::get_noteJumpSpeed() {
  return noteJumpSpeedOverride.value_or(original->get_noteJumpSpeed());
}

NEVector::Vector3 NoodleExtensions::NoodleMovementDataProvider::get_moveStartPosition() {
  return moveStartPositionOverride.value_or(original->get_moveStartPosition());
}

NEVector::Vector3 NoodleExtensions::NoodleMovementDataProvider::get_moveEndPosition() {
  return moveEndPositionOverride.value_or(original->get_moveEndPosition());
}

NEVector::Vector3 NoodleExtensions::NoodleMovementDataProvider::get_jumpEndPosition() {
  return jumpEndPositionOverride.value_or(original->get_jumpEndPosition());
}

void NoodleExtensions::NoodleMovementDataProvider::Init(float startHalfJumpDurationInBeats,
                                                          float maxHalfJumpDistance,
                                                          float noteJumpMovementSpeed,
                                                          float minRelativeNoteJumpSpeed,
                                                          float bpm,
                                                          GlobalNamespace::BeatmapObjectSpawnMovementData::NoteJumpValueType noteJumpValueType,
                                                          float noteJumpValue,
                                                          NEVector::Vector3 centerPosition,
                                                          NEVector::Vector3 forwardVector) {
}

float NoodleExtensions::NoodleMovementDataProvider::CalculateCurrentNoteJumpGravity(float gravityBase) {
  float halfJumpDur = get_halfJumpDuration();
  return 2.0f * gravityBase / (halfJumpDur * halfJumpDur);
}

float NoodleExtensions::NoodleMovementDataProvider::NoteJumpGravityForLineLayerWithoutJumpOffset(float highestJumpPosY, float beforeJumpLineLayer)
{
  float num = get_jumpDistance() / get_noteJumpSpeed() * 0.5f;
  return 2.0f * (highestJumpPosY - SpawnDataHelper::LineYPosForLineLayer(beforeJumpLineLayer)) / (num * num);
}

float NoodleExtensions::NoodleMovementDataProvider::JumpPosYForLineLayerAtDistanceFromPlayerWithoutJumpOffset(float highestJumpPosY, float distanceFromPlayer) {
  float num = ((get_jumpDistance() * 0.5f) - distanceFromPlayer) / get_noteJumpSpeed();
  float num2 = NoteJumpGravityForLineLayerWithoutJumpOffset(highestJumpPosY, 0);
  float num3 = num2 * get_jumpDuration() * 0.5f;
  return SpawnDataHelper::LineYPosForLineLayer(0) + (num3 * num) - (num2 * num * num * 0.5f);
}

void NoodleExtensions::NoodleMovementDataProvider::ctor() {
  beatmapObjectSpawnMovementData = GlobalNamespace::BeatmapObjectSpawnMovementData::New_ctor();
  beatmapObjectSpawnMovementData->Init(NECaches::numberOfLines, NECaches::JumpOffsetYProvider.ptr(), NEVector::Vector3::right());
  
  // initialize base data
  // TODO: Check if we need more initialization
  noteJumpValueType = NECaches::InitData->noteJumpValueType;
  noteJumpStartBeatOffset = NECaches::InitData->noteJumpValue;
  oneBeatDuration = SpawnDataHelper::OneBeatDuration(NECaches::beatsPerMinute);
}