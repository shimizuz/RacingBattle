//=============================================================================
//
// シーン遷移処理 [CTitle.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//ヘッダーインクルード
#include "CScene.h"
#include "CPhase.h"
#include "CTitle.h"
#include "CPhaseFactory.h"
#include "CManager.h"
#include "Joy.h"
#include "Input.h"
#include "CCameraGL.h"
#include "CScene2D.h"
#include "CScene3D.h"
#include "CGame.h"
#include "CBillboard.h"

//初期化
bool CTitle::Init(void *lpArgs)
{
	//２D生成
	CScene2D::Create(CVector(0,0,0),"data\\texture\\witch3.tga",50,50);
	//３D生成
	CScene3D::Create(CVector(0,0,0),"data\\texture\\witch3.tga",10,10);
	
	return true;
}

//更新
bool CTitle::Update(void* lpArgs)
{
//	CScene::UpdateAll();
	if(CInputSystem::getInstance()->GetKeyPush(VK_RETURN))
	{
		CManager::SetFactory(new CPhaseFactory<CGame>);
	}

	return true;
}

//開放
bool CTitle::Release(void* lpArgs)
{
	CScene::FreePhase();
	return true;
}
//描画
bool CTitle::Draw(void* lpArgs)
{
//	CScene::DrawAll();
	return true;
}
