//==============================================================================
//
// �v���C���[�}�l�[�W��
// Author : Shimizu Shoji
//
// �v���C���[�̃}�l�[�W���N���X�ł��B
// �}�l�[�W���Ƃ����Ă��قڃ}�l�[�W���O���Ȃ���ł����ǂˁB
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class declaration
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CPlayer;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �w�b�_�ɏ����Ă���܂��B
class CPlayerManager {
public:
	// const
	static const int kNumPlayers = 4;

	// ctor
	CPlayerManager();

	// dtor
	~CPlayerManager();

	// �v���C���[�̎擾
	CPlayer* GetPlayer(int id) {
		_CheckRange(id);
		return m_pPlayers[id];
	}
	
  // �~���[�e�[�^
  void SetPosition(int id, const CVector& position);
  void SetRotation(int id, const CVector& rotation);

private:
	void _CheckRange(int id);

	CPlayer* m_pPlayers[kNumPlayers];
};

