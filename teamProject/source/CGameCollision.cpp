//==============================================================================
//
// ゲームの衝突判定クラス
// Author : Shimizu Shoji
//
// プレイヤーとフィールドの衝突判定などを行います。
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <algorithm>
#include "CGameCollision.h"
#include "CColider.h"

#include "CBullet.h"
#include "CField.h"
#include "CPlayer.h"
#include "COwnhalf.h"
#include "CPlayerManager.h"
#include "CBulletManager.h"
#include "COwnhalfManager.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// 判定に関連するクラスの参照を渡す。
//------------------------------------------------
CGameCollision::CGameCollision(
    CBulletManager& bullet_manager,
    CField& field,
    CPlayerManager& player_manager,
	COwnhalfManager& ownhalf_manager )
    : bullet_manager_(bullet_manager),
      field_(field),
      player_manager_(player_manager),
	  ownhalf_manager_(ownhalf_manager)
{

}

//------------------------------------------------
// dtor
//------------------------------------------------
CGameCollision::~CGameCollision() 
{

}

//------------------------------------------------
// 複数のプレイヤーとフィールドの衝突を行う。
//------------------------------------------------
void CGameCollision::CollidePlayersAndField(void) 
{
  // 現在のプレイヤーのワールド座標からフィールド座標を求める
  
  // プレイヤーの速度から移動後のワールド座標を求める
  
  // 移動後のワールド座標からフィールド座標を求める
  
  // 現在のフィールド座標から移動後のフィールド座標までの
  // 移動経路上にある全てのフィールド座標と衝突判定を取る
    // if 衝突していなかった場合、何もしないで終了
    // else 衝突していた場合

    // TODO: 反射ベクトルを利用した方が良い
    //       また、ベクトルの角度によって速度を削ること
    //       例えば-1なら垂直に壁に突っ込んでいるので、
    //       反射ベクトルの方向(真後ろ)に対して、かなり速度を減速させて移動させる
    // 衝突した地点ギリギリまで移動させて、停止
}

//------------------------------------------------
// 複数のプレイヤーと複数の弾の衝突を行う。
//------------------------------------------------
void CGameCollision::CollidePlayersAndBullets(void) {
	//変数宣言

	// プレイヤーの座標を取得

	// 弾の座標を取得
	// 衝突の判定を行う
	auto it = bullet_manager_.GetBullet().begin();

	while(it != bullet_manager_.GetBullet().end())
	{
		CBullet* p_bullet = *it;
		CPlayer* p_player = player_manager_.GetPlayer(1);

		if(Colider::SpherColider(
			player_manager_.GetPlayer(1)->GetPosition().m_Vector.x,
			p_player->GetPosition().m_Vector.y,
			p_player->GetPosition().m_Vector.z,
			1,
			p_bullet->GetPosition().m_Vector.x,
			p_bullet->GetPosition().m_Vector.y,
			p_bullet->GetPosition().m_Vector.z,
			1))
		{
			//当たっていたら
			p_player->Apply();

			//弾削除
			p_bullet->Uninit();
				
				
			//イテレータ削除
			it = bullet_manager_.GetBullet().erase(it);
		}
		else 
		{
			++it;
		}
	}
}

//------------------------------------------------
// 複数の弾とフィールドの衝突を行う。
//------------------------------------------------
void CGameCollision::CollideBulletsAndField(void) 
{
  // 現在の弾のワールド座標からフィールド座標を求める

  // 弾の速度から移動後のワールド座標を求める

  // 移動後のワールド座標からフィールド座標を求める

  // 現在のフィールド座標から移動後のフィールド座標までの
  // 移動経路上にある全てのフィールド座標と衝突判定を取る
  // if 衝突していなかった場合、何もしないで終了
  // else 衝突していた場合

  // TODO: 反射ベクトルを利用した方が良い
  //       また、ベクトルの角度によって速度を削ること
  //       例えば-1なら垂直に壁に突っ込んでいるので、
  //       反射ベクトルの方向(真後ろ)に対して、かなり速度を減速させて移動させる
  // 衝突した地点ギリギリまで移動させて、停止
}


// 自分の陣地と判定を取る。
//------------------------------------------------
void CGameCollision::CollidePlayerAndOwnhalf(void)
{

	//プレイヤー座標取得
	CPlayer* p_player = player_manager_.GetPlayer(0);
	//陣地の座標取得
	COwnhalf* p_ownhalf = ownhalf_manager_.GetOwnhalf(0);
	
	//当たり判定を行う
	if(Colider::SpherColider(p_player->GetPosition().m_Vector.x,
							p_player->GetPosition().m_Vector.y,
							p_player->GetPosition().m_Vector.z,
							1,
							p_ownhalf->GetPosition().m_Vector.x,
							p_ownhalf->GetPosition().m_Vector.y,
							p_ownhalf->GetPosition().m_Vector.z,
							1
							))
	{
		//TODO:ポイントアップ

	}
	else
	{

	}
}

//eof