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
#include "CMeshFiledGL.h"

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
  m_Move.SetValue(0.5f,0,0.5f);
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

	//フィールドとの境界判定
	CVector vecLine[4];
	CVector vecToTarget[4];
	CVector vecCol[4];
	CVector vecPos;;

	vecLine[0] = CMeshFieldGL::GetVertex(1)-CMeshFieldGL::GetVertex(0);
	vecToTarget[0] = GetPosition() - CMeshFieldGL::GetVertex(0);
	
	vecCol[0] = vecLine[0];

	vecCol[0].Cross(vecToTarget[0],FALSE);
	if(vecToTarget[0].m_Vector.x * vecLine[0].m_Vector.z - vecToTarget[0].m_Vector.z*vecLine[0].m_Vector.x <= 0)
	{
		vecPos = GetPosition();
		vecPos.m_Vector.z = vecLine[0].m_Vector.z;
		SetPosition(vecPos);
		return;
	}
	
	vecLine[1] = CMeshFieldGL::GetVertex(3)-CMeshFieldGL::GetVertex(1);
	vecToTarget[1] = GetPosition() - CMeshFieldGL::GetVertex(1);

	vecCol[1] = vecLine[1];

	vecCol[1].Cross(vecToTarget[1],FALSE);
	if(vecToTarget[1].m_Vector.x * vecLine[1].m_Vector.z - vecToTarget[1].m_Vector.z*vecLine[1].m_Vector.x <= 0)
	{
		vecPos = GetPosition();
		vecPos.m_Vector.x = vecLine[1].m_Vector.x;
		SetPosition(vecPos);
		return;
	}

	vecLine[2] = CMeshFieldGL::GetVertex(2)-CMeshFieldGL::GetVertex(3);
	vecToTarget[2] = GetPosition() - CMeshFieldGL::GetVertex(3);

	vecCol[2] = vecLine[2];

	vecCol[2].Cross(vecToTarget[2],FALSE);	
	if(vecToTarget[2].m_Vector.x * vecLine[2].m_Vector.z - vecToTarget[2].m_Vector.z*vecLine[2].m_Vector.x <= 0)
	{
		vecPos = GetPosition();
		vecPos.m_Vector.z = vecLine[2].m_Vector.z;
		SetPosition(vecPos);
		return;
	}

	vecLine[3] = CMeshFieldGL::GetVertex(0)-CMeshFieldGL::GetVertex(2);
	vecToTarget[3] = GetPosition() - CMeshFieldGL::GetVertex(2);

	vecCol[3] = vecLine[3];

	vecCol[3].Cross(vecToTarget[3],FALSE);
	if(vecToTarget[3].m_Vector.x * vecLine[3].m_Vector.z - vecToTarget[3].m_Vector.z*vecLine[3].m_Vector.x <= 0)
	{
		vecPos = GetPosition();
		vecPos.m_Vector.x = vecLine[3].m_Vector.x;
		SetPosition(vecPos);
		return;
	}

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
  pos.m_Vector.z += m_Move.m_Vector.z;
  SetPosition(pos);
}

//-------------------------------------------------
// Move Backward
//-------------------------------------------------
void CPlayer::MoveBackward(void) {
  CVector pos = GetPosition();
  pos.m_Vector.z -= m_Move.m_Vector.z;
  SetPosition(pos);
}

//-------------------------------------------------
// Move Right
//-------------------------------------------------
void CPlayer::MoveRight(void) {
  CVector pos = GetPosition();
  pos.m_Vector.x -= m_Move.m_Vector.x;
  SetPosition(pos);
}

//-------------------------------------------------
// Move Left
//-------------------------------------------------
void CPlayer::MoveLeft(void) {
  CVector pos = GetPosition();
  pos.m_Vector.x += m_Move.m_Vector.x;
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
