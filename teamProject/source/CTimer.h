//=============================================================================
//
// �^�C�}�[���� [ CTimer.h ]
// Author : DYE IMAIZUMI
//
//=============================================================================
//*****************************************************************************
// �C���N���[�h�K�[�h
//*****************************************************************************
#ifndef �QTIMER_H_
#define �QTIMER_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "CScene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUMBER_PLACE_MAX (2)
#define TIME_WIDTH (40.0f)		// �X�R�A�ꌅ���̉���
#define TIME_HEIGHT (80.0f)		// �X�R�A�ꌅ���̏c��
#define X_CENTER_POS_TIME ( 400 )					// �e�N�X�`���̐^�񒆂�X���W
#define Y_CENTER_POS_TIME ( 300 )					// �e�N�X�`���̐^�񒆂�Y���W
#define TIME_X_LENGTH ( 100 )					// �e�N�X�`���̎Ε�X����
#define TIME_Y_LENGTH ( 100 )					// �e�N�X�`���̎Ε�Y����

//*****************************************************************************
// �N���X�݌v
//*****************************************************************************
class CTimer : public CScene2D
{

public:

	CTimer();										// �R���X�g���N�^
	~CTimer();									// �f�X�g���N�^
	void Init( char* ptexFileName,float scaleWidth,float scaleHeight );			// ������
	void Uninit( void );							// �I��
	void Update( void );							// �X�V
	void Draw( void );								// �`��

	static CScene2D* CreateTimer( CVector pos,char* ptexFileName,float scaleWidth,float scaleHeight );// �N���G�C�g�֐�

	static int GetSecNum( void ){ return m_nSecNum; };

	//���W�ݒ�
	void SetPosition(CVector pos)
	{
		m_Timepos = pos;	
	}

private:

	float	m_fLength;
	float	m_fAngle;
	CVector m_Timepos;
	CVector m_Timerot;
	CVector m_Timescl;
	CVector m_vtx[8];
	unsigned int m_texture;

	int m_nNumber;
	static int m_nSecNum;

};
#endif //�QTIMER_H_

// EOF