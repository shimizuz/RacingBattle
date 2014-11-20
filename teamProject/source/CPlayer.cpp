//==============================================================================
//
// プレイヤー
// Author : Shimizu Shoji
//
// プレイヤー
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "CPlayer.h"

//==============================================================================
// class implementation
//==============================================================================
//-------------------------------------------------
// ctor
//-------------------------------------------------
CPlayer::CPlayer() : CScene3D(3) {
}

//-------------------------------------------------
// dtor
//-------------------------------------------------
CPlayer::~CPlayer() {
}

//-------------------------------------------------
// Init
//-------------------------------------------------
void CPlayer::Init(float scaleWidth, float scaleHeight) {
  CScene3D::Init("data/TEXTURE/texture006.tga", scaleWidth, scaleHeight);
}

//-------------------------------------------------
// Uninit
//-------------------------------------------------
void CPlayer::Uninit(void) {
  CScene3D::Uninit();
}

//-------------------------------------------------
// Update
//-------------------------------------------------
void CPlayer::Update(void) {
  CScene3D::Update();
}

//-------------------------------------------------
// Draw
//-------------------------------------------------
void CPlayer::Draw(void) {
  CScene3D::Draw();
}

//-------------------------------------------------
// Move Forward
//-------------------------------------------------
void CPlayer::MoveForward(void) {
  CVector pos = GetPosition();
  pos.m_Vector.z -= 0.5f;
  SetPosition(pos);
}

//-------------------------------------------------
// Move Backward
//-------------------------------------------------
void CPlayer::MoveBackward(void) {
  CVector pos = GetPosition();
  pos.m_Vector.z += 0.5f;
  SetPosition(pos);
}

//-------------------------------------------------
// Move Right
//-------------------------------------------------
void CPlayer::MoveRight(void) {
  CVector pos = GetPosition();
  pos.m_Vector.x += 0.5f;
  SetPosition(pos);
}

//-------------------------------------------------
// Move Left
//-------------------------------------------------
void CPlayer::MoveLeft(void) {
  CVector pos = GetPosition();
  pos.m_Vector.x -= 0.5f;
  SetPosition(pos);
}

//-------------------------------------------------
// Create
//-------------------------------------------------
CPlayer* CPlayer::Create(CVector pos, float scaleWidth, float scaleHeight) {
  CPlayer* pCPlayer = new CPlayer();

  pCPlayer->SetPosition(pos);

  pCPlayer->Init(scaleWidth,scaleHeight);

  return pCPlayer;
}
