//==============================================================================
//
// ゲームの衝突判定クラス
// Author : Shimizu Shoji
//
// プレイヤーとフィールドの衝突判定などを行います。
//
//==============================================================================
#pragma once
#ifndef CFIELD_H_
#define CFIELD_H_
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class declaration
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CBulletManager;
class CField;
class CPlayerManager;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CGameCollision {
public:
  // 判定に関連するクラスの参照を渡す。
  CGameCollision(
    CBulletManager& bullet_manager,
    CField& field,
    CPlayerManager& player_manager);

  // dtor
  ~CGameCollision();

  // 複数のプレイヤーとフィールドの衝突を行う。
  void CollidePlayersAndField(void);

  // 複数のプレイヤーと複数の弾の衝突を行う。
  void CollidePlayersAndBullets(void);

  // 複数の弾とフィールドの衝突を行う。
  void CollideBulletsAndField(void);

private:
  CBulletManager& bullet_manager_;
  CField& field_;
  CPlayerManager& player_manager_;
};

#endif  // CFIELD_H_
