//=============================================================================
//
// �V�[���J�ڏ��� [CGame.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
//=============================================================================
//�w�b�_�[�C���N���[�h
//=============================================================================
#include "CScene.h"
#include "CPhase.h"
#include "CGame.h"
#include "CPhaseFactory.h"
#include "CManager.h"
#include "Joy.h"
#include "Input.h"
#include "CCameraGL.h"
#include "CScene2D.h"
#include "CScene3D.h"
#include "CResult.h"
#include "CBillboard.h"

//=============================================================================
//�N���X��`
//=============================================================================
//������
bool CGame::Init(void *lpArgs)
{
	//�QD����
	CScene2D::Create(CVector(0,0,0),"data\\texture\\wall.tga",50,50);
	//�RD����
	CScene3D::Create(CVector(0,0,0),"data\\texture\\wall.tga",50,50);
	//�r���{�[�h
	CBillboard::Create(CVector(0,0,0),"data\\texture\\wall.tga",10,10);

	return true;
}

//�X�V
bool CGame::Update(void* lpArgs)
{
	if(CInputSystem::getInstance()->GetKeyPush(VK_RETURN))
	{
		CManager::SetFactory(new CPhaseFactory<CResult>);
	}

	return true;
}

//�J��
bool CGame::Release(void* lpArgs)
{
	CScene::FreePhase();
	return true;
}
//�`��
bool CGame::Draw(void* lpArgs)
{
//	CScene::DrawAll();
	return true;
}


//eof