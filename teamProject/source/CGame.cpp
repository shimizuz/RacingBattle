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
#include "CBullet.h"
#include "COwnhalf.h"
#include "CGameCollision.h"
#include "CBulletManager.h"
#include "COwnhalfManager.h"
#include "CGameCollision.h"

//=============================================================================
//�ÓI�����o�ϐ�
//=============================================================================
CMeshFieldGL* CGame::m_pMeshField = NULL;
CFlag*		  CGame::m_pFlag[CFlag::kMaxFlags];

#include "network.h"

SendUDP* sendUdp;
RecvUDP* recvUdp;

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
  if(pBulletManager_)
  {
	  delete pBulletManager_;
	  pBulletManager_ = nullptr;
  }
  if(pOwnhalfManager_)
  {
	  delete pOwnhalfManager_;
	  pOwnhalfManager_ = nullptr;
  }
  if(pGameCollision_)
  {
	  delete pGameCollision_;
	  pGameCollision_ = nullptr;
  }
}

//������
bool CGame::Init(void *lpArgs)
{

	float x,y,z;
	x = y = z  = 0;

  // �N���C�A���g�����グ���Ƀl�b�g���[�N�̐ڑ�
  // (�T�[�o�[�֐ڑ�����)
  // �T�[�o�[�Ɏ���ID�̎擾��v������
  // ����ID��ۑ�����

  // �R���g���[���[��������ID�ŏ�����

  // -----
  // ����M�f�[�^(����ꍇ�͎���ID���Z�b�g)
  // �w�b�_
  // ID�ƃf�[�^�̎��
  // �f�[�^�{��
  // �f�[�^�̎�ނɉ������l
  // �E���W�Ƃ��H
  // �E�t���O�ʒm/����


	//�J�����̏�����
	CCameraGL::getInstance()->Init();
	//���b�V���t�B�[���h�쐬
	m_pMeshField = CMeshFieldGL::Create(10,10,10,10,CVector(0,0,0),CVector(0,0,0),"data\\texture\\field.tga");
	
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

  recvUdp = new RecvUDP(pPlayerManager_);
  sendUdp = new SendUDP();
  
  recvUdp->Start(false);
  sendUdp->Start(false);

  //�e
	pBulletManager_ = new CBulletManager();
  //�v���C���[�ɒe�}�l�[�W���[�Z�b�g
	pPlayerManager_->GetPlayer(0)->SetBulletManager(pBulletManager_);

  //�w�n
	pOwnhalfManager_ = new COwnhalfManager();
  //�Q�[���R���W����
	pGameCollision_ = new CGameCollision(*pBulletManager_,*pField_,*pPlayerManager_,*pOwnhalfManager_);

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
			pPlayerManager_->GetPlayer(0)->addflagCount();
		}
		
		//�t���b�O���������Ă�����
		if(m_pFlag[i]->GetHaveFlag())
		{
			//���W�ݒ�
			tmpMoveY += 2.0f;

			pos.m_Vector.x = pPos.m_Vector.x;
			pos.m_Vector.y = pPos.m_Vector.y + tmpMoveY;
			pos.m_Vector.z = pPos.m_Vector.z;
			m_pFlag[i]->SetPosition(pos);
		}
	}
	
	NetworkData data;
	data._id = 1;
	data._types = NETWORKCOMMAND_GAMEDATA;
	memcpy(data.dataFloat, &pPos, sizeof(float) * 4);
	sendUdp->sendData(data);
	
	//�N���A
	if(pPlayerManager_->GetPlayer(0)->GetFlagNum() == CFlag::kMaxFlags)
	{
		CManager::SetFactory(new CPhaseFactory<CResult>);
	}

	CCameraGL::getInstance()->SetPosition(pPos);
	pController_->Update();

	pGameCollision_->CollidePlayersAndBullets();

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