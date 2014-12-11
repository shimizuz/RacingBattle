//==============================================================================
//
// �t���b�O�Ǘ�
// Author : Masahiro Yamaguchi
//==============================================================================
//==============================================================================
//���d��`�h�~
//==============================================================================
#ifndef __CFLAG_H__
#define __CFLAG_G__

//==============================================================================
//�w�b�_�[�C���N���[�h
//==============================================================================
#include "CBillboard.h"

//==============================================================================
//�N���X��`
//==============================================================================
class CFlag : public CBillboard
{
public:

	//�}�N����`
	static const int kMaxFlags = 3;		//�t���b�O�̐�
	static const int kLoadLevels = 10;	//�V�[���J��

	//�R���X�g���N�^
	CFlag(int nPriority = 3):CBillboard(nPriority)
	{
		m_FlagNum = 0;
		m_kLoadLevelNum = 0;
	
		m_haveflag = false;
	}
	//�f�X�g���N�^
	virtual ~CFlag()
	{

	}
	//����
	static CFlag* Create(CVector pos,float fangle,char* ptexname,float scaleWidth,float scaleHeight);
	//������
	void Init(float fangle,char* ptexname,float scaleWidth,float scaleHeight);
	//�X�V
	void Update();
	//�J��
	void Uninit();
	//�`��
	void Draw();

	//���擾
	int GetFlagNum()
	{
		return m_FlagNum;
	}
	int GetLoadLevelNum()
	{
		return m_kLoadLevelNum;
	}
	bool GetHaveFlag()
	{
		return m_haveflag;
	}
	void SetHaveFlag(bool flag)
	{
		m_haveflag = flag;
	}
private:
	
	int	m_FlagNum;
	int m_kLoadLevelNum;
	bool m_haveflag;
};
#endif
//eof