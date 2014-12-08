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
#include "CController.h"
#include "CMeshFiledGL.h"
#include "CPlayerManager.h"

//=============================================================================
//�N���X��`
//=============================================================================
CGame::~CGame() {
  if (pPlayerManager_) {
    delete pPlayerManager_;
    pPlayerManager_ = nullptr;
  }
}

//������
bool CGame::Init(void *lpArgs)
{
	//���b�V���t�B�[���h�쐬
	CMeshFieldGL::Create(10,10,10,10,CVector(0,0,0),CVector(0,0,0),"data\\texture\\images4.tga");
	// �v���C���[
  pPlayerManager_ = new CPlayerManager();
	pController_ = new CController(*pPlayerManager_->GetPlayer(0));

	return true;
}

//�X�V
bool CGame::Update(void* lpArgs)
{
	if(CInputSystem::getInstance()->GetKeyPush(VK_RETURN))
	{
		CManager::SetFactory(new CPhaseFactory<CResult>);
	}
	pPos = pPlayerManager_->GetPlayer(0)->GetPosition();
	CCameraGL::getInstance()->SetPosition(pPos);

	pController_->Update();

	return true;
}

//�J��
bool CGame::Release(void* lpArgs)
{
  SAFE_DELETE(pController_);
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