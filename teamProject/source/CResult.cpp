//=============================================================================
//
// �V�[���J�ڏ��� [CResult.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
//=============================================================================
//�w�b�_�[�C���N���[�h
//=============================================================================
#include "CScene.h"
#include "CPhase.h"
#include "CResult.h"
#include "CPhaseFactory.h"
#include "CManager.h"
#include "Joy.h"
#include "Input.h"
#include "CCameraGL.h"
#include "CScene2D.h"
#include "CScene3D.h"
#include "CTitle.h"

//=============================================================================
//�N���X��`
//=============================================================================
//������
bool CResult::Init(void *lpArgs)
{
	//�J�����̏�����
	CCameraGL::getInstance()->Init();
	//�QD����
	CScene2D::Create(CVector(0,0,0),"data\\texture\\images3.tga",50,50);
	//�RD����
	CScene3D::Create(CVector(0,0,0),"data\\texture\\images3.tga",50,50);
	return true;
}

//�X�V
bool CResult::Update(void* lpArgs)
{

	if(CInputSystem::getInstance()->GetKeyPush(VK_RETURN))
	{
		CManager::SetFactory(new CPhaseFactory<CTitle>);
	}

	return true;
}

//�J��
bool CResult::Release(void* lpArgs)
{
	CScene::FreePhase();
	return true;
}
//�`��
bool CResult::Draw(void* lpArgs)
{
//	CScene::DrawAll();
	return true;
}
//eof