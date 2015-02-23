//==============================================================================
//
// �����̐w�n�Ǘ�
// Author : Masahiro Yamaguchi
//
// ���w�Ƀt���b�O�������ċA���Ă�������
//
//==============================================================================
//==============================================================================
//���d��`�h�~
//==============================================================================
#pragma once
#ifndef __COWNHALF_H__
#define __COWNHALF_H__

//==============================================================================
//�w�b�_�[�C���N���[�h
//==============================================================================
#include "main.h"
#include "CScene3D.h"

//==============================================================================
//�N���X��`
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