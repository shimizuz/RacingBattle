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
#include "CField.h"
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
#include "CBillboard.h"
#include "CColider.h"

//=============================================================================
//�N���X��`
//=============================================================================
CGame::~CGame() {
  if (pPlayerManager_) {
    delete pPlayerManager_;
    pPlayerManager_ = nullptr;
  }

  if (pField_) {
    delete pField_;
    pField_ = nullptr;
  }

}

//������
bool CGame::Init(void *lpArgs)
{

	float x,y,z;
	x = y = z  = 0;

	//���b�V���t�B�[���h�쐬
	CMeshFieldGL::Create(10,10,10,10,CVector(0,0,0),CVector(0,0,0),"data\\texture\\field.tga");
	
	// �v���C���[
  pPlayerManager_ = new CPlayerManager();
	pController_ = new CController(*pPlayerManager_->GetPlayer(0));


	//�t���b�O
	int nNum = 20;
	for(int i = 0;i < CFlag::kMaxFlags;i++)
	{
		x = static_cast<float>(rand()% nNum);
		y = 1;
		z = static_cast<float>(rand()% nNum);
		m_pFlag[i] = CFlag::Create(CVector(x,y,z),0,"data\\texture\\flag.tga",1,1);
	}
  // �t�B�[���h
  pField_ = new CField();

	return true;
}

//�X�V
bool CGame::Update(void* lpArgs)
{
	//�ϐ��錾
	CVector pos(0,0,0);
	float tmpMoveY = 0.0f;

	//�V�[���؂�ւ�
	if(CInputSystem::getInstance()->GetKeyPush(VK_RETURN))
	{
		CManager::SetFactory(new CPhaseFactory<CResult>);
	}

	
	pPos = pPlayerManager_->GetPlayer(0)->GetPosition();
	
	//�t���b�O����
	for(int i = 0;i < CFlag::kMaxFlags;i++)
	{
		//�����蔻��
		if(Colider::SpherColider(m_pFlag[i]->GetPosition().m_Vector.x,m_pFlag[i]->GetPosition().m_Vector.y,m_pFlag[i]->GetPosition().m_Vector.z,1,
			pPos.m_Vector.x,pPos.m_Vector.y,pPos.m_Vector.z,1))
		{
			m_pFlag[i]->SetHaveFlag(true);
		}
		
		if(m_pFlag[i]->GetHaveFlag())
		{
			tmpMoveY += 2.0f;

			pos.m_Vector.x = pPos.m_Vector.x;
			pos.m_Vector.y = pPos.m_Vector.y + tmpMoveY;
			pos.m_Vector.z = pPos.m_Vector.z;
			m_pFlag[i]->SetPosition(pos);
		}
	}
	
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
	return true;
}


//eof