//==============================================================================
//
// ゲームの衝突判定クラス
// Author : Shimizu Shoji
//
// プレイヤーとフィールドの衝突判定などを行います。
//
//==============================================================================
#pragma once
#ifndef CGAMECOLLISION_H_
#define CGAMECOLLISION_H_
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class declaration
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CBulletManager;
class CField;
class CPlayerManager;
class COwnhalfManager;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CGameCollision {
public:
  // 判定に関連するクラスの参照を渡す。
  CGameCollision(
    CBulletManager& bullet_manager,
    CField& field,
    CPlayerManager& player_manager,
	COwnhalfManager& ownhalf_manager);

  // dtor
  ~CGameCollision();

  // 複数のプレイヤーとフィールドの衝突を行う。
  void CollidePlayersAndField(void);

  // 複数のプレイヤーと複数の弾の衝突を行う。
  void CollidePlayersAndBullets(void);

  // 複数の弾とフィールドの衝突を行う。
  void CollideBulletsAndField(void);

  // 自分の陣地と判定を取る。
  void CollidePlayerAndOwnhalf(void);

private:
  CBulletManager& bullet_manager_;
  CField& field_;
  CPlayerManager& player_manager_;
  COwnhalfManager&	ownhalf_manager_;

};

#endif  // 
//eof