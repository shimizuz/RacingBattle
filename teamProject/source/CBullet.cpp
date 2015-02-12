//==============================================================================
//
// ‚½‚Ü
// Author : Shimizu Shoji
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "CBullet.h"
#include <cmath>

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
CBullet::CBullet()
    : CBillboard(3),
      spd_(CVector(0, 0, 0)) {
}

//------------------------------------------------
// dtor
//------------------------------------------------
CBullet::~CBullet() {
}

//------------------------------------------------
// Init
//------------------------------------------------
void CBullet::Init(void) {
  CBillboard::Init("data/TEXTURE/bullet.tga", 2.0f, 2.0f);
  SetRotate(CVector(-90.0f, 0.0f, 0));
}

//------------------------------------------------
// Uninit
//------------------------------------------------
void CBullet::Uninit(void) {
  CBillboard::Uninit();
}

//------------------------------------------------
// Reset
//------------------------------------------------
void CBullet::Reset(const CVector& pos, const CVector& spd) {
  SetPosition(pos);
  spd_ = spd;
}


//------------------------------------------------
// Update
//------------------------------------------------
void CBullet::Update(void) {
  CVector pos = GetPosition();
  
//  pos += spd_;
  pos.m_Vector.x+=sinf(angle_)*spd_.m_Vector.x;

  pos.m_Vector.z+=cosf(angle_)*spd_.m_Vector.z;
  
  SetPosition(pos);

  CBillboard::Update();
}

//------------------------------------------------
// Draw
//------------------------------------------------
void CBullet::Draw(void) {
  CBillboard::Draw();
}
//------------------------------------------------
// Create
//------------------------------------------------
CBullet* CBullet::Create(const CVector& pos, const CVector& spd,float angle,int id)
{
	CBullet* pBullet = new CBullet();

	pBullet->Init();

	pBullet->SetAngle(angle);

	pBullet->Reset(pos, spd);

	pBullet->SetId(id);

	return pBullet;
}
//eof