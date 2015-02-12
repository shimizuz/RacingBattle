//=============================================================================
//
// シーン遷移処理 [CResult.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
//=============================================================================
//ヘッダーインクルード
//=============================================================================
#include "CScene.h"
#include "CPhase.h"
#include "CResult.h"
#include "CPhaseFactory.h"
#include "CManager.h"
#include "Joy.h"
#include "Input.h"
#include "CCameraGL.h"
#include "CScene2D.h"
#include "CScene3D.h"
#include "CTitle.h"

//=============================================================================
//クラス定義
//=============================================================================
//初期化
bool CResult::Init(void *lpArgs)
{
	//カメラの初期化
	CCameraGL::getInstance()->Init();
	//２D生成
	CScene2D::Create(CVector(0,0,0),"data\\texture\\images3.tga",50,50);
	//３D生成
	CScene3D::Create(CVector(0,0,0),"data\\texture\\images3.tga",50,50);
	return true;
}

//更新
bool CResult::Update(void* lpArgs)
{

	if(CInputSystem::getInstance()->GetKeyPush(VK_RETURN))
	{
		CManager::SetFactory(new CPhaseFactory<CTitle>);
	}

	return true;
}

//開放
bool CResult::Release(void* lpArgs)
{
	CScene::FreePhase();
	return true;
}
//描画
bool CResult::Draw(void* lpArgs)
{
//	CScene::DrawAll();
	return true;
}
//eof