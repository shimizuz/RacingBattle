//ヘッダーインクルード
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

//グローバル
CRenderer* CManager::m_pRenderer = NULL;


//初期化
void CManager::Init(HWND hWnd)
{
	//入力情報初期化
	CInputSystem::getInstance()->InputInitInfo();

	//カメラの初期化
	CCameraGL::getInstance()->Init();

	m_pRenderer = new CRenderer();
	//初期化
	m_pRenderer->Init(hWnd);

	m_pCurrentPhase = new CTitle();
	
	m_pCurrentPhase->Init();

	CFade::getinstance()->Init();
}
//開放
void CManager::Uninit()
{
	// 終了処理
	m_pRenderer->Uninit();

	//開放
	SAFE_DELETE(m_pRenderer);

	CInputSystem::Release();

	CCameraGL::Release();

	CScene::ReleaseAll();
}
//更新
void CManager::Updata()
{

	//入力情報更新
	CInputSystem::getInstance()->InputUpdateInfo();

	//カメラ更新
	CCameraGL::getInstance()->Update();

	//次のシーンがNULLじゃないなら
	if(m_pNextPtr != NULL)
	{
		//フェード開始
		if(CFade::getinstance()->GetFadeMode() == FADE_NONE)
		{

			//フェードアウト
			CFade::getinstance()->SetFadeMode(FADE_OUT);
			//現在のシーンを削除して生成
			m_pCurrentPhase->Release();
			delete m_pCurrentPhase;
			m_pCurrentPhase = NULL;
		}

		if(CFade::getinstance()->GetFadeMode() == FADE_OUT_FINISH)
		{	
			
			m_pCurrentPhase = m_pNextPtr->Create();
			m_pCurrentPhase->Init();
			DeleteFactory();
			//フェードイン
			CFade::getinstance()->SetFadeMode(FADE_IN);
		}
	}
	//現在のシーンを更新
	if(m_pCurrentPhase != NULL)
	{
		m_pCurrentPhase->Update();
	}
	//レンダークラスの更新
	m_pRenderer->Update();
}
//描画
void CManager::Draw()
{
	//現在のシーンを描画
	//m_pCurrentPhase->Draw();

	m_pRenderer->Draw();
}