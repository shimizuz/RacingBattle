//=============================================================================
//
// �V�[���J�ڏ��� [CResult.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
//=============================================================================
//���d��`�h�~
//=============================================================================
#ifndef __CRESULT_H__
#define __CRESULT_H__

//�w�b�_�[�C���N���[�h
#include "CPhase.h"

//�N���X��`
class CResult : public CPhase
{
private:

public:
	//�R���X�g���N�^
	CResult()
	{

	}
	//�f�X�g���N�^
	~CResult()
	{

	}
	//�e�V�[��
	virtual bool Init(void *lpArgs = NULL);
	virtual bool Update(void *lpArgs = NULL);
	virtual bool Release(void *lpArgs = NULL);
	virtual bool Draw(void *lpArgs = NULL);
};

#endif

//eof