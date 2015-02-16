//=============================================================================
//
// �V�[���J�ڏ��� [CGame.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
//=============================================================================
//���d��`�h�~
//=============================================================================
#pragma once
#ifndef __CGAME_H__
#define __CGAME_H__
//=============================================================================
//�O���錾
//=============================================================================
class CController;
class CPlayerManager;
class CFlag;
class CField;
class CMeshFieldGL;
class CBullet;
class CBulletManager;
class COwnhalfManager;
class CGameCollision;
//=============================================================================
//�w�b�_�[�C���N���[�h
//=============================================================================
#include "CPhase.h"
#include "CPlayer.h"
#include "CFlag.h"

//=============================================================================
//�N���X��`
//=============================================================================
class CGame : public CPhase
{
private:

public:
	//�R���X�g���N�^
  CGame() : pController_(nullptr)
	{
		pPlayerManager_ = NULL;
		pController_ = NULL;
		pBulletManager_ = NULL;
		pOwnhalfManager_ = NULL;
		pGameCollision_ = NULL;
	}
	//�f�X�g���N�^
  ~CGame();

	//�e�V�[��
	virtual bool Init(void *lpArgs = NULL);
	virtual bool Update(void *lpArgs = NULL);
	virtual bool Release(void *lpArgs = NULL);
	virtual bool Draw(void *lpArgs = NULL);

	//�擾
	static CMeshFieldGL* GetCMeshFieldGL()
	{
		return m_pMeshField;
	}
	//�擾
	static CFlag* GetFlag(int index)
	{
		return m_pFlag[index];
	}

private:
  CController* pController_;
  CPlayerManager* pPlayerManager_;
  CField* pField_;
  CVector pPos;
  static CFlag*	m_pFlag[CFlag::kMaxFlags];
  static CMeshFieldGL* m_pMeshField;
  CBulletManager* pBulletManager_;
  COwnhalfManager* pOwnhalfManager_;
  CGameCollision* pGameCollision_;
};

#endif
//eof