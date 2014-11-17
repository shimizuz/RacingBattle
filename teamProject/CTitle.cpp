//=============================================================================
//
// �V�[���J�ڏ��� [CTitle.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//�w�b�_�[�C���N���[�h
#include "CScene.h"
#include "CPhase.h"
#include "CTitle.h"
#include "CPhaseFactory.h"
#include "CManager.h"
#include "Joy.h"
#include "Input.h"
#include "CCameraGL.h"
#include "CScene2D.h"
#include "CScene3D.h"
#include "CGame.h"
#include "CBillboard.h"

//������
bool CTitle::Init(void *lpArgs)
{
	//�QD����
	CScene2D::Create(CVector(0,0,0),"data\\texture\\witch3.tga",50,50);
	//�RD����
	CScene3D::Create(CVector(0,0,0),"data\\texture\\witch3.tga",10,10);
	
	return true;
}

//�X�V
bool CTitle::Update(void* lpArgs)
{
//	CScene::UpdateAll();
	if(CInputSystem::getInstance()->GetKeyPush(VK_RETURN))
	{
		CManager::SetFactory(new CPhaseFactory<CGame>);
	}

	return true;
}

//�J��
bool CTitle::Release(void* lpArgs)
{
	CScene::FreePhase();
	return true;
}
//�`��
bool CTitle::Draw(void* lpArgs)
{
//	CScene::DrawAll();
	return true;
}
