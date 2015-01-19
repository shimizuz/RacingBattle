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
#include "CScene3D.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CBullet : public CScene3D {
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

private:
  CVector spd_;
};

#endif  // CBULLET_H_