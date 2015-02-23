//==============================================================================
//
// ‚½‚Ü
// Author : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef CBULLET_H_
#define CBULLET_H_
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "CBillboard.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CBullet : public CBillboard {
public:
  // ctor
  CBullet();

  // dtor
 virtual ~CBullet();

 // Init
 void Init(void);

 // Uninit
 void Uninit(void);

  // Reset
  void Reset(const CVector& pos, const CVector& spd);

  // Update
  void Update(void);

  // Draw
  void Draw(void);

  // Create
  static CBullet* Create(const CVector& pos, const CVector& spd,float angle,int id);

  //getter
  bool GetHitFlag()
  {
	  return hit_;
  }

  // setter
  void SetAngle(float angle)
  {
	  angle_ = angle;
  }
  void SetId(int id)
  {
	  id_ = id;
  }
  void SetHitFlag(bool flag)
  {
	  hit_ = flag;
  }
private:
  CVector spd_;
  float   angle_;
  int	  id_;
  bool	  hit_;
};

#endif  // CBULLET_H_