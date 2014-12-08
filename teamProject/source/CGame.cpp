//=============================================================================
//
// シーン遷移処理 [CGame.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
//=============================================================================
//ヘッダーインクルード
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

//=============================================================================
//クラス定義
//=============================================================================
//初期化
bool CGame::Init(void *lpArgs)
{
	//メッシュフィールド作成
	CMeshFieldGL::Create(10,10,10,10,CVector(0,0,0),CVector(0,0,0),"data\\texture\\images4.tga");
	// プレイヤー
	pPlayer = CPlayer::Create(CVector(0, 1, 0), 1, 1);

	pController_ = new CController(*pPlayer);

	return true;
}

//更新
bool CGame::Update(void* lpArgs)
{
	if(CInputSystem::getInstance()->GetKeyPush(VK_RETURN))
	{
		CManager::SetFactory(new CPhaseFactory<CResult>);
	}
	pPos = pPlayer->GetPosition();
	CCameraGL::getInstance()->SetPosition(pPos);

	pController_->Update();

	return true;
}

//開放
bool CGame::Release(void* lpArgs)
{
  SAFE_DELETE(pController_);
	CScene::FreePhase();
	return true;
}
//描画
bool CGame::Draw(void* lpArgs)
{
//	CScene::DrawAll();
	return true;
}


//eof