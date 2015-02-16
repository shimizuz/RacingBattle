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
//静的メンバ変数
//=============================================================================
CMeshFieldGL* CGame::m_pMeshField = NULL;
CFlag*		  CGame::m_pFlag[CFlag::kMaxFlags];

#include "network.h"

SendUDP* sendUdp;
RecvUDP* recvUdp;

//=============================================================================
//クラス定義
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

//初期化
bool CGame::Init(void *lpArgs)
{

	float x,y,z;
	x = y = z  = 0;

  // クライアント立ち上げ時にネットワークの接続
  // (サーバーへ接続する)
  // サーバーに自己IDの取得を要請する
  // 自己IDを保存する

  // コントローラー等を自己IDで初期化

  // -----
  // 送受信データ(送る場合は自己IDをセット)
  // ヘッダ
  // IDとデータの種類
  // データ本体
  // データの種類に応じた値
  // ・座標とか？
  // ・フラグ通知/判定


	//カメラの初期化
	CCameraGL::getInstance()->Init();
	//メッシュフィールド作成
	m_pMeshField = CMeshFieldGL::Create(10,10,10,10,CVector(0,0,0),CVector(0,0,0),"data\\texture\\field.tga");
	
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
  // フィールド
  pField_ = new CField();

  recvUdp = new RecvUDP(pPlayerManager_);
  sendUdp = new SendUDP();
  
  recvUdp->Start(false);
  sendUdp->Start(false);

  //弾
	pBulletManager_ = new CBulletManager();
  //プレイヤーに弾マネージャーセット
	pPlayerManager_->GetPlayer(0)->SetBulletManager(pBulletManager_);

  //陣地
	pOwnhalfManager_ = new COwnhalfManager();
  //ゲームコリジョン
	pGameCollision_ = new CGameCollision(*pBulletManager_,*pField_,*pPlayerManager_,*pOwnhalfManager_);

	return true;
}

//更新
bool CGame::Update(void* lpArgs)
{
	//変数宣言
	CVector pos(0,0,0);
	float tmpMoveY = 0.0f;

	//シーン切り替え
	if(CInputSystem::getInstance()->GetKeyPush(VK_RETURN))
	{
		CManager::SetFactory(new CPhaseFactory<CResult>);
	}

	
	pPos = pPlayerManager_->GetPlayer(0)->GetPosition();
	
	//フラッグ所持
	for(int i = 0;i < CFlag::kMaxFlags;i++)
	{
		//当たり判定
		if(Colider::SpherColider(m_pFlag[i]->GetPosition().m_Vector.x,m_pFlag[i]->GetPosition().m_Vector.y,m_pFlag[i]->GetPosition().m_Vector.z,1,
			pPos.m_Vector.x,pPos.m_Vector.y,pPos.m_Vector.z,1))
		{
			m_pFlag[i]->SetHaveFlag(true);
			pPlayerManager_->GetPlayer(0)->addflagCount();
		}
		
		//フラッグを所持していたら
		if(m_pFlag[i]->GetHaveFlag())
		{
			//座標設定
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
	
	//クリア
	if(pPlayerManager_->GetPlayer(0)->GetFlagNum() == CFlag::kMaxFlags)
	{
		CManager::SetFactory(new CPhaseFactory<CResult>);
	}

	CCameraGL::getInstance()->SetPosition(pPos);
	pController_->Update();

	pGameCollision_->CollidePlayersAndBullets();

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
	return true;
}


//eof