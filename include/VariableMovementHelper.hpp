#pragma once

#include "Animation/NoodleMovementDataProvider.hpp"
#include "GlobalNamespace/IVariableMovementDataProvider.hpp"

// speed up interface calls
struct BS_HOOKS_HIDDEN VariableMovementW {
  GlobalNamespace::IVariableMovementDataProvider* variable;
  NoodleExtensions::NoodleMovementDataProvider* ne;

  VariableMovementW(GlobalNamespace::IVariableMovementDataProvider* variable) : variable(variable) {
    ne = il2cpp_utils::try_cast<NoodleExtensions::NoodleMovementDataProvider>(variable).value_or(nullptr);
  }

  operator GlobalNamespace::IVariableMovementDataProvider* () {
    return variable;
  }

  // declspec property getters for nicer call syntax (original names)
  __declspec(property(get = get_wasUpdatedThisFrame)) bool wasUpdatedThisFrame;
  __declspec(property(get = get_moveDuration)) float moveDuration;
  __declspec(property(get = get_halfJumpDuration)) float halfJumpDuration;
  __declspec(property(get = get_jumpDistance)) float jumpDistance;
  __declspec(property(get = get_jumpDuration)) float jumpDuration;
  __declspec(property(get = get_spawnAheadTime)) float spawnAheadTime;
  __declspec(property(get = get_waitingDuration)) float waitingDuration;
  __declspec(property(get = get_noteJumpSpeed)) float noteJumpSpeed;
  __declspec(property(get = get_moveStartPosition)) NEVector::Vector3 moveStartPosition;
  __declspec(property(get = get_moveEndPosition)) NEVector::Vector3 moveEndPosition;
  __declspec(property(get = get_jumpEndPosition)) NEVector::Vector3 jumpEndPosition;

  bool get_wasUpdatedThisFrame() const {
    if (!ne) return variable->get_wasUpdatedThisFrame();

    return ne->get_wasUpdatedThisFrame();
  }

  float get_moveDuration() const {
    if (!ne) return variable->get_moveDuration();

    return ne->get_moveDuration();
  }

  float get_halfJumpDuration() const {
    if (!ne) return variable->get_halfJumpDuration();

    return ne->get_halfJumpDuration();
  }

  float get_jumpDistance() const {
    if (!ne) return variable->get_jumpDistance();

    return ne->get_jumpDistance();
  }

  float get_jumpDuration() const {
    if (!ne) return variable->get_jumpDuration();

    return ne->get_jumpDuration();
  }

  float get_spawnAheadTime() const {
    if (!ne) return variable->get_spawnAheadTime();

    return ne->get_spawnAheadTime();
  }

  float get_waitingDuration() const {
    if (!ne) return variable->get_waitingDuration();

    return ne->get_waitingDuration();
  }

  float get_noteJumpSpeed() const {
    if (!ne) return variable->get_noteJumpSpeed();

    return ne->get_noteJumpSpeed();
  }

  NEVector::Vector3 get_moveStartPosition() const {
    if (!ne) return variable->get_moveStartPosition();

    return ne->get_moveStartPosition();
  }

  NEVector::Vector3 get_moveEndPosition() const {
    if (!ne) return variable->get_moveEndPosition();

    return ne->get_moveEndPosition();
  }

  NEVector::Vector3 get_jumpEndPosition() const {
    if (!ne) return variable->get_jumpEndPosition();

    return ne->get_jumpEndPosition();
  }

  float CalculateCurrentNoteJumpGravity(float gravityBase) const {
    if (!ne) return variable->CalculateCurrentNoteJumpGravity(gravityBase);

    return ne->CalculateCurrentNoteJumpGravity(gravityBase);
  }
};
