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

//=============================================================================
//クラス定義
//=============================================================================
//初期化
bool CGame::Init(void *lpArgs)
{
	//２D生成
	CScene2D::Create(CVector(0,0,0),"data\\texture\\wall.tga",50,50);
	//３D生成
	CScene3D::Create(CVector(0,0,0),"data\\texture\\wall.tga",50,50);
	//ビルボード
	CBillboard::Create(CVector(0,0,0),"data\\texture\\wall.tga",10,10);

	return true;
}

//更新
bool CGame::Update(void* lpArgs)
{
	if(CInputSystem::getInstance()->GetKeyPush(VK_RETURN))
	{
		CManager::SetFactory(new CPhaseFactory<CResult>);
	}

	return true;
}

//開放
bool CGame::Release(void* lpArgs)
{
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