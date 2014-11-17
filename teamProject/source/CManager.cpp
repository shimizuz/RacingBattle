//�w�b�_�[�C���N���[�h
#include "CPhase.h"
#include "CPhaseFactory.h"
#include "CManager.h"
#include "CRenderer.h"
#include "CScene.h"
#include "Input.h"
#include "CScene2D.h"
#include "CScene3D.h"
#include "CTitle.h"
#include "CGame.h"
#include "CResult.h"
#include "CFade.h"
#include "CCameraGL.h"

CFactoryPtr* CManager::m_pNextPtr = NULL;	
CPhase*	CManager::m_pCurrentPhase = NULL;

//�O���[�o��
CRenderer* CManager::m_pRenderer = NULL;


//������
void CManager::Init(HWND hWnd)
{
	//���͏�񏉊���
	CInputSystem::getInstance()->InputInitInfo();

	//�J�����̏�����
	CCameraGL::getInstance()->Init();

	m_pRenderer = new CRenderer();
	//������
	m_pRenderer->Init(hWnd);

	m_pCurrentPhase = new CTitle();
	
	m_pCurrentPhase->Init();

	CFade::getinstance()->Init();
}
//�J��
void CManager::Uninit()
{
	// �I������
	m_pRenderer->Uninit();

	//�J��
	SAFE_DELETE(m_pRenderer);

	CInputSystem::Release();

	CCameraGL::Release();

	CScene::ReleaseAll();
}
//�X�V
void CManager::Updata()
{

	//���͏��X�V
	CInputSystem::getInstance()->InputUpdateInfo();

	//�J�����X�V
	CCameraGL::getInstance()->Update();

	//���̃V�[����NULL����Ȃ��Ȃ�
	if(m_pNextPtr != NULL)
	{
		//�t�F�[�h�J�n
		if(CFade::getinstance()->GetFadeMode() == FADE_NONE)
		{

			//�t�F�[�h�A�E�g
			CFade::getinstance()->SetFadeMode(FADE_OUT);
			//���݂̃V�[�����폜���Đ���
			m_pCurrentPhase->Release();
			delete m_pCurrentPhase;
			m_pCurrentPhase = NULL;
		}

		if(CFade::getinstance()->GetFadeMode() == FADE_OUT_FINISH)
		{	
			
			m_pCurrentPhase = m_pNextPtr->Create();
			m_pCurrentPhase->Init();
			DeleteFactory();
			//�t�F�[�h�C��
			CFade::getinstance()->SetFadeMode(FADE_IN);
		}
	}
	//���݂̃V�[�����X�V
	if(m_pCurrentPhase != NULL)
	{
		m_pCurrentPhase->Update();
	}
	//�����_�[�N���X�̍X�V
	m_pRenderer->Update();
}
//�`��
void CManager::Draw()
{
	//���݂̃V�[����`��
	//m_pCurrentPhase->Draw();

	m_pRenderer->Draw();
}