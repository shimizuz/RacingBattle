//=============================================================================
//
// �e�t�F�[�Y���� [CTitle.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//���d��`
#ifndef __CTITLE_H__
#define __CTITLE_H__

//�w�b�_�[�C���N���[�h
#include "CPhase.h"

//�O���錾
class CRender;

//�N���X��`
class CTitle:public CPhase
{
private:
	
public:

	//�R���X�g���N�^
	CTitle()
	{

	}
	//�f�X�g���N�^
	~CTitle()
	{

	}
	//�e�V�[��
	virtual bool Init(void *lpArgs = NULL);
	virtual bool Update(void *lpArgs = NULL);
	virtual bool Release(void *lpArgs = NULL);
	virtual bool Draw(void *lpArgs = NULL);
};

#endif