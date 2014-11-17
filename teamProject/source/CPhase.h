//=============================================================================
//
// �e�t�F�[�Y���� [CPhase.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//���d��`�h�~
#ifndef __CPHASE_H__
#define __CPHASE_H__

#include <windows.h>
#include <stdio.h>

//�V�[���Ǘ��p�N���X
class CPhase
{
protected:
	
public:
	
	//�R���X�g���N�^
	CPhase(){}	
	//�f�X�g���N�^
	virtual ~CPhase(){}

	//�e�V�[��
	virtual bool Init(void *lpArgs = NULL) = 0;
	virtual bool Update(void *lpArgs = NULL) = 0;
	virtual bool Release(void *lpArgs = NULL) = 0;
	virtual bool Draw(void *lpArgs = NULL) = 0;

};

#endif
//eof