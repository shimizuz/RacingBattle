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

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CPlayer : public CScene3D {
 private:
	 CVector m_Move;
	 int	 m_flagNum;
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

  //フラグを増やす
  void addflagCount(void)
  {
	  m_flagNum++;
  }
  int GetFlagNum()
  {
	  return m_flagNum;
  }
  // Create
  static CPlayer* Create(CVector pos, float scaleWidth, float scaleHeight);

};

#endif  // __H_CPLAYER_H__
