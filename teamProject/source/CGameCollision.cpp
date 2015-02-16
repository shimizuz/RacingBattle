//==============================================================================
//
// �Q�[���̏Փ˔���N���X
// Author : Shimizu Shoji
//
// �v���C���[�ƃt�B�[���h�̏Փ˔���Ȃǂ��s���܂��B
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
// ����Ɋ֘A����N���X�̎Q�Ƃ�n���B
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
// �����̃v���C���[�ƃt�B�[���h�̏Փ˂��s���B
//------------------------------------------------
void CGameCollision::CollidePlayersAndField(void) 
{
  // ���݂̃v���C���[�̃��[���h���W����t�B�[���h���W�����߂�
  
  // �v���C���[�̑��x����ړ���̃��[���h���W�����߂�
  
  // �ړ���̃��[���h���W����t�B�[���h���W�����߂�
  
  // ���݂̃t�B�[���h���W����ړ���̃t�B�[���h���W�܂ł�
  // �ړ��o�H��ɂ���S�Ẵt�B�[���h���W�ƏՓ˔�������
    // if �Փ˂��Ă��Ȃ������ꍇ�A�������Ȃ��ŏI��
    // else �Փ˂��Ă����ꍇ

    // TODO: ���˃x�N�g���𗘗p���������ǂ�
    //       �܂��A�x�N�g���̊p�x�ɂ���đ��x����邱��
    //       �Ⴆ��-1�Ȃ琂���ɕǂɓ˂�����ł���̂ŁA
    //       ���˃x�N�g���̕���(�^���)�ɑ΂��āA���Ȃ葬�x�����������Ĉړ�������
    // �Փ˂����n�_�M���M���܂ňړ������āA��~
}

//------------------------------------------------
// �����̃v���C���[�ƕ����̒e�̏Փ˂��s���B
//------------------------------------------------
void CGameCollision::CollidePlayersAndBullets(void) {
	//�ϐ��錾

	// �v���C���[�̍��W���擾

	// �e�̍��W���擾
	// �Փ˂̔�����s��
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
			//�������Ă�����
			p_player->Apply();

			//�e�폜
			p_bullet->Uninit();
				
				
			//�C�e���[�^�폜
			it = bullet_manager_.GetBullet().erase(it);
		}
		else 
		{
			++it;
		}
	}
}

//------------------------------------------------
// �����̒e�ƃt�B�[���h�̏Փ˂��s���B
//------------------------------------------------
void CGameCollision::CollideBulletsAndField(void) 
{
  // ���݂̒e�̃��[���h���W����t�B�[���h���W�����߂�

  // �e�̑��x����ړ���̃��[���h���W�����߂�

  // �ړ���̃��[���h���W����t�B�[���h���W�����߂�

  // ���݂̃t�B�[���h���W����ړ���̃t�B�[���h���W�܂ł�
  // �ړ��o�H��ɂ���S�Ẵt�B�[���h���W�ƏՓ˔�������
  // if �Փ˂��Ă��Ȃ������ꍇ�A�������Ȃ��ŏI��
  // else �Փ˂��Ă����ꍇ

  // TODO: ���˃x�N�g���𗘗p���������ǂ�
  //       �܂��A�x�N�g���̊p�x�ɂ���đ��x����邱��
  //       �Ⴆ��-1�Ȃ琂���ɕǂɓ˂�����ł���̂ŁA
  //       ���˃x�N�g���̕���(�^���)�ɑ΂��āA���Ȃ葬�x�����������Ĉړ�������
  // �Փ˂����n�_�M���M���܂ňړ������āA��~
}


// �����̐w�n�Ɣ�������B
//------------------------------------------------
void CGameCollision::CollidePlayerAndOwnhalf(void)
{

	//�v���C���[���W�擾
	CPlayer* p_player = player_manager_.GetPlayer(0);
	//�w�n�̍��W�擾
	COwnhalf* p_ownhalf = ownhalf_manager_.GetOwnhalf(0);
	
	//�����蔻����s��
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
		//TODO:�|�C���g�A�b�v

	}
	else
	{

	}
}

//eof