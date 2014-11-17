//�w�b�_�[�C���N���[�h
#include "CScene.h"

//�ÓI�����o�ϐ��̏�����
CScene* CScene::m_pTop[PRIORITY_MAX] = {NULL};
CScene* CScene::m_pCur[PRIORITY_MAX] = {NULL};

//�����t��
CScene::CScene(int nPriority)
: m_nPriority(nPriority)
{
	this->m_bDeath = false;	
	LinkList();
}
//�f�X�g���N�^
CScene::~CScene()
{

}
//�����N���X�g���X�g�֒ǉ�
void CScene::LinkList(void)
{
	/*
	//�ŏ���肳��ɑO�ɂ���_�~�[�v�f
	m_DummyHead->m_pNext = m_DummyTail;
	m_DummyHead->m_pPrev = NULL;
	//�Ō�̗v�f�̂���Ɍ�ɂ���_�~�[�v�f�B
	m_DummyTail->m_pNext = 0;
	m_DummyTail->m_pPrev = m_DummyHead;
	*/

	if(m_pTop[m_nPriority] == NULL)
	{
		m_pTop[m_nPriority] = this;
		m_pCur[m_nPriority] = this;
		this->m_pPrev = NULL;
		this->m_pNext = NULL;
	}
	else
	{
		this->m_pPrev = m_pCur[m_nPriority];
		m_pCur[m_nPriority]->m_pNext = this;
		this->m_pNext = NULL;
		m_pCur[m_nPriority] = this;
	}
}
//���X�g����폜
void CScene::UnlinkList(CScene* pScene)
{
	
	if(pScene == m_pTop[m_nPriority])
	{
		if(pScene == m_pCur[m_nPriority])
		{
			m_pTop[m_nPriority] = NULL;
			m_pCur[m_nPriority] = NULL;
			m_pNext = NULL;
			m_pPrev = NULL;
		}
		else
		{
			m_pTop[m_nPriority] = pScene->m_pNext;
			m_pTop[m_nPriority]->m_pPrev = NULL;
		}
	}
	else if(pScene == m_pCur[m_nPriority])
	{
		pScene->m_pPrev->m_pNext = NULL;
		m_pCur[m_nPriority] = pScene->m_pPrev;
	}
	else
	{
		
		//�O�̓z�̎����A���ɂ���B
		pScene->m_pPrev->m_pNext = pScene->m_pNext;
		//���̓z�̑O���A�O�ɂ���B
		pScene->m_pNext->m_pPrev = pScene->m_pPrev;
	}
}
//�폜
void CScene::Release()
{
//	this->Uninit();
//	UnlinkList();
	this->m_bDeath = true;
//	delete this;
}
//�폜
void CScene::Delete(int nIdxEnemy)
{
	int nCnt = 0;
	CScene* pScene = m_pTop[nIdxEnemy];
	CScene* pNext = NULL;
	//�G���[�`�F�b�N
	if(nIdxEnemy >10)
	{
		MessageBox(NULL,"������������","ERROR",MB_OK);
		return;
	}
	//�폜
	while(pScene)
	{
	
		if(nCnt==nIdxEnemy)
		{
			pScene->Release();
		}
		else
		{
			pNext = pScene->m_pNext;
			pScene = pNext;
			nCnt++;
		}
	}

}
//�S�X�V
void CScene::UpdateAll(void)
{
	for(int i = 0;i < PRIORITY_MAX;i++)
	{
		CScene* pScene = m_pTop[i];
		CScene* pNext = NULL;

		while(pScene != NULL)	//NULL����Ȃ���Ώ���
		{
			if(pScene->m_bDeath)
			{
				pScene->UnlinkList(pScene);
				SAFE_DELETE(pScene);
			
			}
			if(pScene != NULL)
			{
				pNext = pScene->m_pNext;
				pScene->Update();
				pScene = pNext;
			}
			

		}
	}
}
void CScene::FreePhase(void)
{
	for(int i = 0;i < PRIORITY_MAX;i++)
	{
		CScene* pScene = m_pTop[i];
		CScene* pNext = NULL;

		while(pScene != NULL)	//NULL����Ȃ���Ώ���
		{
			pScene->Release();
			pNext = pScene->m_pNext;
			
			if(pScene->m_bDeath)
			{
				pScene->Uninit();
				pScene->UnlinkList(pScene);
				SAFE_DELETE(pScene);
			}
			if(pNext != NULL)
			{
				
				pScene = pNext;
			}
		}
	}

}
//�S�J��
void CScene::ReleaseAll(void)
{
	for(int i = 0;i < PRIORITY_MAX;i++)
	{
		CScene* pScene = m_pTop[i];
		CScene* pNext = NULL;

		while(pScene)	//NULL����Ȃ���Ώ���
		{
			pScene->Uninit();
			pNext = pScene->m_pNext;
			delete pScene;
			pScene = pNext;
		}
	}
	
}
//�S�`��
void CScene::DrawAll(void)
{
	for(int i = 0;i < PRIORITY_MAX;i++)
	{
		CScene* pScene = m_pTop[i];
		CScene* pNext = NULL;

		while(pScene)	//NULL����Ȃ���Ώ���
		{
			pNext = pScene->m_pNext;
			pScene->Draw();
			pScene = pNext;
		}
	}
}