//==============================================================================
//
// �Q�[���̏Փ˔���N���X
// Author : Shimizu Shoji
//
// �v���C���[�ƃt�B�[���h�̏Փ˔���Ȃǂ��s���܂��B
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
  // ����Ɋ֘A����N���X�̎Q�Ƃ�n���B
  CGameCollision(
    CBulletManager& bullet_manager,
    CField& field,
    CPlayerManager& player_manager,
	COwnhalfManager& ownhalf_manager);

  // dtor
  ~CGameCollision();

  // �����̃v���C���[�ƃt�B�[���h�̏Փ˂��s���B
  void CollidePlayersAndField(void);

  // �����̃v���C���[�ƕ����̒e�̏Փ˂��s���B
  void CollidePlayersAndBullets(void);

  // �����̒e�ƃt�B�[���h�̏Փ˂��s���B
  void CollideBulletsAndField(void);

  // �����̐w�n�Ɣ�������B
  void CollidePlayerAndOwnhalf(void);

private:
  CBulletManager& bullet_manager_;
  CField& field_;
  CPlayerManager& player_manager_;
  COwnhalfManager&	ownhalf_manager_;

};

#endif  // 
//eof