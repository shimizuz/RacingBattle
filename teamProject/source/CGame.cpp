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
#include "CPlayerManager.h"
#include "CBillboard.h"
#include "CColider.h"

//=============================================================================
//クラス定義
//=============================================================================
CGame::~CGame() {
  if (pPlayerManager_) {
    delete pPlayerManager_;
    pPlayerManager_ = nullptr;
  }
  
}

//初期化
bool CGame::Init(void *lpArgs)
{

	float x,y,z;
	x = y = z  = 0;

	//メッシュフィールド作成
	CMeshFieldGL::Create(10,10,10,10,CVector(0,0,0),CVector(0,0,0),"data\\texture\\images4.tga");
	// プレイヤー
  pPlayerManager_ = new CPlayerManager();
	pController_ = new CController(*pPlayerManager_->GetPlayer(0));


	//フラッグ
	int nNum = 20;
	for(int i = 0;i < CFlag::kMaxFlags;i++)
	{
		x = static_cast<float>(rand()% nNum);
		y = 1;
		z = static_cast<float>(rand()% nNum);
		m_pFlag[i] = CFlag::Create(CVector(x,y,z),0,"data\\texture\\flag.tga",1,1);
	}
	return true;
}

//更新
bool CGame::Update(void* lpArgs)
{
	CVector pos(0,0,0);

	//シーン切り替え
	if(CInputSystem::getInstance()->GetKeyPush(VK_RETURN))
	{
		CManager::SetFactory(new CPhaseFactory<CResult>);
	}

	

	pPos = pPlayerManager_->GetPlayer(0)->GetPosition();
	pos = pPos;


	//フラッグ所持
	for(int i = 0;i < CFlag::kMaxFlags;i++)
	{
		if(Colider::SpherColider(m_pFlag[i]->GetPosition().m_Vector.x,m_pFlag[i]->GetPosition().m_Vector.y,m_pFlag[i]->GetPosition().m_Vector.z,1,
			pos.m_Vector.x,pos.m_Vector.y,pos.m_Vector.z,1))
		{
			m_pFlag[i]->SetHaveFlag(i,true);
		}
		
		if(m_pFlag[i]->GetHaveFlag(i))
		{
			pos.m_Vector.y += 2;
			m_pFlag[i]->SetPosition(pos);
		}
	}

	CCameraGL::getInstance()->SetPosition(pPos);
	pController_->Update();

	return true;
}

//開放
bool CGame::Release(void* lpArgs)
{

  for(int i = 0;i < CFlag::kMaxFlags;i++)
  {
  	SAFE_DELETE(m_pFlag[i]);
  }
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