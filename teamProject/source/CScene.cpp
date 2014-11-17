//ヘッダーインクルード
#include "CScene.h"

//静的メンバ変数の初期化
CScene* CScene::m_pTop[PRIORITY_MAX] = {NULL};
CScene* CScene::m_pCur[PRIORITY_MAX] = {NULL};

//引数付き
CScene::CScene(int nPriority)
: m_nPriority(nPriority)
{
	this->m_bDeath = false;	
	LinkList();
}
//デストラクタ
CScene::~CScene()
{

}
//リンクリストリストへ追加
void CScene::LinkList(void)
{
	/*
	//最初よりさらに前にあるダミー要素
	m_DummyHead->m_pNext = m_DummyTail;
	m_DummyHead->m_pPrev = NULL;
	//最後の要素のさらに後にあるダミー要素。
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
//リストから削除
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
		
		//前の奴の次を、次にする。
		pScene->m_pPrev->m_pNext = pScene->m_pNext;
		//次の奴の前を、前にする。
		pScene->m_pNext->m_pPrev = pScene->m_pPrev;
	}
}
//削除
void CScene::Release()
{
//	this->Uninit();
//	UnlinkList();
	this->m_bDeath = true;
//	delete this;
}
//削除
void CScene::Delete(int nIdxEnemy)
{
	int nCnt = 0;
	CScene* pScene = m_pTop[nIdxEnemy];
	CScene* pNext = NULL;
	//エラーチェック
	if(nIdxEnemy >10)
	{
		MessageBox(NULL,"数が多すぎる","ERROR",MB_OK);
		return;
	}
	//削除
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
//全更新
void CScene::UpdateAll(void)
{
	for(int i = 0;i < PRIORITY_MAX;i++)
	{
		CScene* pScene = m_pTop[i];
		CScene* pNext = NULL;

		while(pScene != NULL)	//NULLじゃなければ処理
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

		while(pScene != NULL)	//NULLじゃなければ処理
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
//全開放
void CScene::ReleaseAll(void)
{
	for(int i = 0;i < PRIORITY_MAX;i++)
	{
		CScene* pScene = m_pTop[i];
		CScene* pNext = NULL;

		while(pScene)	//NULLじゃなければ処理
		{
			pScene->Uninit();
			pNext = pScene->m_pNext;
			delete pScene;
			pScene = pNext;
		}
	}
	
}
//全描画
void CScene::DrawAll(void)
{
	for(int i = 0;i < PRIORITY_MAX;i++)
	{
		CScene* pScene = m_pTop[i];
		CScene* pNext = NULL;

		while(pScene)	//NULLじゃなければ処理
		{
			pNext = pScene->m_pNext;
			pScene->Draw();
			pScene = pNext;
		}
	}
}