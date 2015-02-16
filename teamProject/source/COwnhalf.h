//==============================================================================
//
// 自分の陣地管理
// Author : Masahiro Yamaguchi
//
// 自陣にフラッグを持って帰ってきた時等
//
//==============================================================================
//==============================================================================
//多重定義防止
//==============================================================================
#pragma once
#ifndef __COWNHALF_H__
#define __COWNHALF_H__

//==============================================================================
//ヘッダーインクルード
//==============================================================================
#include "main.h"
#include "CScene3D.h"

//==============================================================================
//クラス定義
//==============================================================================
class COwnhalf : public CScene3D
{
public:
	// ctor
  COwnhalf();

  // dtor
  virtual ~COwnhalf();

  // Init
  void Init(float scaleWidth, float scaleHeight);

  // Uninit
  void Uninit(void);

  // Update
  void Update(void);

  // Draw
  void Draw(void);

  //texturePathSet
  void SetTextureFileName(char* path)
  {
	  m_pTexName = path;
  }

  // Create
  static COwnhalf* Create(CVector pos, float scaleWidth, float scaleHeight,char* texPath);
private:
	int	  m_flagNum;
	char* m_pTexName;
};
#endif
//eof