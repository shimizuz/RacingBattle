//================================================================================
//���d��`�h�~
//================================================================================
#ifndef __CLASS_VECTOR_H__
#define __CLASS_VECTOR_H__
#pragma once

//�w�b�_�[�t�@�C��
#include <windows.h>

//================================================================================
//�\���̒�`
//================================================================================
typedef struct _VEC2
{
	float x;
	float y;
}VEC2,*LPVEC2;
struct VECTOR
{
	float	x;
	float	y;
	float	z;
	float	w;
	VECTOR()
	{
		ZeroMemory(this,sizeof(VECTOR));
	}
};

//�O���錾
class CMatrix;

//================================================================================
//�N���X��`
//================================================================================
class CVector
{
private:
	
public:
	//�����o�ϐ�
	VECTOR	m_Vector;
	//�R���X�g���N�^
	CVector( void );
	explicit CVector( float fx , float fy , float fz );
	//�R�s�[�R���X�g���N�^
	CVector( const CVector &vec );
	//�f�X�g���N�^
	~CVector( void );
	//�x�N�g���擾
	float GetX( void )const;
	float GetY( void )const;
	float GetZ( void )const;
	float GetW( void )const;
	VECTOR GetVector( void )const;
	//�x�N�g���ݒ�
	void SetX( const float fx );
	void SetY( const float fy );
	void SetZ( const float fz );
	void SetW( const float fw );
	void SetValue( float fx , float fy , float fz );
	//��x�N�g��
	CVector &ZeroVector( void );
	//�t�x�N�g��
	CVector Inverse( void )const;
	//�x�N�g���̒���
	float Length( BOOL bSquare = FALSE )const;
	//�x�N�g���̐��K��
	CVector Normalize( void )const;
	//�x�N�g���̓���
	float Dot( const CVector &vec , BOOL bNormalize )const;
	//�x�N�g���̊O��
	CVector Cross( const CVector &vec )const;
	//�x�N�g���̂Ȃ��p
	float InnerProductAngle( const CVector &vec )const;
	//�s��Ƃ̍���
	CVector &TransformMatrix( const CMatrix &mat );
	//���Z�q�̃I�[�o�[���[�h
	CVector &operator =( const CVector &vec );
	CVector operator +( const CVector &vec )const;
	CVector operator -( const CVector &vec )const;
	CVector operator *( const float fValue )const;
	CVector operator *( const CMatrix &mat )const;
	CVector operator /( const float fValue )const;
	CVector& operator +=( const CVector &vec );
	CVector& operator -=( const CVector &vec );
	CVector& operator *=( const float fValue );
	CVector& operator *=( const CMatrix &mat );
	CVector& operator /=( const float fValue );
};
#endif
