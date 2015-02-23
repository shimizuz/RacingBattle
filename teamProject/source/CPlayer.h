//==============================================================================
//
// プレイヤー
// Author : Shimizu Shoji
//
// プレイヤー
//
//==============================================================================
#pragma once
#ifndef __H_CPLAYER_H__
#define __H_CPLAYER_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "../source/CScene3D.h"
#include "../source/CBullet.h"

class CBulletManager;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CPlayer : public CScene3D {
 private:
	 CVector  m_Move;
	 int	  m_flagNum;
	 CBulletManager *m_pBulletManager;
public:
  // ctor
  CPlayer();

  // dtor
  virtual ~CPlayer();

  // Init
  void Init(float scaleWidth, float scaleHeight);

  // Uninit
  void Uninit(void);

  // Update
  void Update(void);

  // Draw
  void Draw(void);

  // Move
  void MoveForward(void);
  void MoveBackward(void);
  void MoveRight(void);
  void MoveLeft(void);

  // Attack
  void AttackRazer();

  // AddFlag
  void addflagCount(void)
  {
	  m_flagNum++;
  }
  // GetFlag
  int GetFlagNum()
  {
	  return m_flagNum;
  }
  
  // GetBullet
  CBulletManager* GetBulletManager()
  {
	  return m_pBulletManager;
  }
  // SetBullet
  void SetBulletManager(CBulletManager* pbulletManager)
  {
	  m_pBulletManager = pbulletManager;
  }
  // AttackHitAfter
  void Apply();
  // Create
  static CPlayer* Create(CVector pos, float scaleWidth, float scaleHeight);

};

#endif  // __H_CPLAYER_H__
