//=============================================================================
//
// �V�[���J�ڏ��� [CGame.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
//=============================================================================
//���d��`�h�~
//=============================================================================
#ifndef __CGAME_H__
#define __CGAME_H__

class CController;
class CPlayerManager;
class CFlag;

//�w�b�_�[�C���N���[�h
#include "CPhase.h"
#include "CPlayer.h"
#include "CFlag.h"

//�N���X��`
class CGame : public CPhase
{
private:

public:
	//�R���X�g���N�^
  CGame() : pController_(nullptr)
	{

	}
	//�f�X�g���N�^
  ~CGame();

	//�e�V�[��
	virtual bool Init(void *lpArgs = NULL);
	virtual bool Update(void *lpArgs = NULL);
	virtual bool Release(void *lpArgs = NULL);
	virtual bool Draw(void *lpArgs = NULL);

private:
  CController* pController_;
  CPlayerManager* pPlayerManager_;
  CVector pPos;
  CFlag*	m_pFlag[CFlag::kMaxFlags];
};

#endif
//eof