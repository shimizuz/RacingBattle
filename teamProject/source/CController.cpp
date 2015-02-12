//==============================================================================
//
// �R���g���[���[
// Author : Shimizu Shoji
//
// ���삷��B
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "CController.h"
#include "CPlayer.h"
#include "Input.h"

//==============================================================================
// class implementation
//==============================================================================
//-------------------------------------------------
// ctor
//-------------------------------------------------
CController::CController(CPlayer& rPlayer) : rPlayer_(rPlayer) {
}

//-------------------------------------------------
// dtor
//-------------------------------------------------
CController::~CController() {
}

//-------------------------------------------------
// Update
//-------------------------------------------------
void CController::Update(void) {
  // �v���C���[�̃R���g���[��
  if (CInputSystem::getInstance()->GetKeyPush(VK_UP)) {
    rPlayer_.MoveForward();
  }
  if (CInputSystem::getInstance()->GetKeyPush(VK_DOWN)) {
    rPlayer_.MoveBackward();
  }
  if (CInputSystem::getInstance()->GetKeyPush(VK_LEFT)) {
    rPlayer_.MoveLeft();
  }
  if (CInputSystem::getInstance()->GetKeyPush(VK_RIGHT)) {
    rPlayer_.MoveRight();
  }
  if (CInputSystem::getInstance()->GetKeyPush(VK_SPACE)) {
	  rPlayer_.AttackRazer();
  }
}
