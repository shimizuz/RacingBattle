//================================================================================
//�x������
//================================================================================
//�Ӑ}�I�ɋ��^�̊֐����g�p���邽�߂ɁA�x���𐧌�����
#pragma warning (disable : 4996 )
#include <windows.h>
#include <cmath>
#include "Class_Matrix.h"
#include "Class_Vector.h"

//�v�Z���x�㏸
#pragma intrinsic(sqrt,pow,sin,cos,tan,asin,acos,atan)

//================================================================================
//�R���X�g���N�^
//�y�@�@�\�z
//	�x�N�g���̐������O�ŏ���������
//�y���@���z
//	�Ȃ�
//�y���@�l�z
//	w�����̓f�t�H���g��1.0�ɂ��Ă���
//================================================================================
CVector::CVector( void )
{
	this->ZeroVector();	//��x�N�g���쐬
	//w�́u1.0�v�ŌŒ�
	this->m_Vector.w = 1.0f;
}

//================================================================================
//�R���X�g���N�^
//�y�@�@�\�z
//	�C�ӂ̒l�Ŋe����������������
//�y���@���z
//	�P�F�w����
//	�Q�F�x����
//	�R�F�y����
//�y���@�l�z
//	�Ȃ�
//================================================================================
CVector::CVector( float fx , float fy , float fz )
{
	this->m_Vector.x = fx;
	this->m_Vector.y = fy;
	this->m_Vector.z = fz;
	this->m_Vector.w = 1.0f;	//�u1.0�v�ŌŒ�
}

//================================================================================
//�R�s�[�R���X�g���N�^
//�y�@�@�\�z
//	�󂯎�����x�N�g���̃R�s�[���쐬����
//�y���@���z
//	�P�F�R�s�[����CVector�I�u�W�F�N�g
//�y���@�l�z
//	�Ȃ�
//================================================================================
CVector::CVector( const CVector &vec )
{
	this->m_Vector = vec.m_Vector;
}

//================================================================================
//�f�X�g���N�^
//�y�@�@�\�z
//	�x�N�g���̐������O�ŏ���������
//�y���@���z
//	�Ȃ�
//�y���@�l�z
//	�Ȃ�
//================================================================================
CVector::~CVector( void )
{
	this->ZeroVector();
}

//================================================================================
//GetX�֐�
//�y�@�@�\�z
//	�x�N�g���̂w�������擾����
//�y���@���z
//	�Ȃ�
//�y�߂�l�z
//	�w����
//�y���@�l�z
//	�Ȃ�
//================================================================================
float CVector::GetX( void )const
{
	return this->m_Vector.x;
}

//================================================================================
//GetY�֐�
//�y�@�@�\�z
//	�x�N�g���̂x�������擾����
//�y���@���z
//	�Ȃ�
//�y�߂�l�z
//	�x����
//�y���@�l�z
//	�Ȃ�
//================================================================================
float CVector::GetY( void )const
{
	return this->m_Vector.y;
}

//================================================================================
//GetZ�֐�
//�y�@�@�\�z
//	�x�N�g���̂y�������擾����
//�y���@���z
//	�Ȃ�
//�y�߂�l�z
//	�y����
//�y���@�l�z
//	�Ȃ�
//================================================================================
float CVector::GetZ( void )const
{
	return this->m_Vector.z;
}

//================================================================================
//GetW�֐�
//�y�@�@�\�z
//	�x�N�g���̂v�������擾����
//�y���@���z
//	�Ȃ�
//�y�߂�l�z
//	�v����
//�y���@�l�z
//	�Ȃ�
//================================================================================
float CVector::GetW( void )const
{
	return this->m_Vector.w;
}

//================================================================================
//GetVector�֐�
//�y�@�@�\�z
//	�x�N�g�����擾����
//�y���@���z
//	�Ȃ�
//�y�߂�l�z
//	VECTOR�^�̃f�[�^
//�y���@�l�z
//	�Ȃ�
//================================================================================
VECTOR CVector::GetVector( void )const
{
	return this->m_Vector;
}

//================================================================================
//SetX�֐�
//�y�@�@�\�z
//	�x�N�g���̂w������ݒ肷��
//�y���@���z
//	�P�F�w�����̒l
//�y�߂�l�z
//	�Ȃ�
//�y���@�l�z
//	�Ȃ�
//================================================================================
void CVector::SetX( float fx )
{
	this->m_Vector.x = fx;
}

//================================================================================
//SetY�֐�
//�y�@�@�\�z
//	�x�N�g���̂x������ݒ肷��
//�y���@���z
//	�P�F�x�����̒l
//�y�߂�l�z
//	�Ȃ�
//�y���@�l�z
//	�Ȃ�
//================================================================================
void CVector::SetY( float fy )
{
	this->m_Vector.y = fy;
}

//================================================================================
//SetZ�֐�
//�y�@�@�\�z
//	�x�N�g���̂y������ݒ肷��
//�y���@���z
//	�P�F�y�����̒l
//�y�߂�l�z
//	�Ȃ�
//�y���@�l�z
//	�Ȃ�
//================================================================================
void CVector::SetZ( float fz )
{
	this->m_Vector.z = fz;
}

//================================================================================
//SetW�֐�
//�y�@�@�\�z
//	�x�N�g���̂v������ݒ肷��
//�y���@���z
//	�P�F�v�����̒l
//�y�߂�l�z
//	�Ȃ�
//�y���@�l�z
//	�Ȃ�
//================================================================================
void CVector::SetW( float fw )
{
	this->m_Vector.w = fw;
}

//================================================================================
//SetValue�֐�
//�y�@�@�\�z
//	�x�N�g���̊e������ݒ肷��
//�y���@���z
//	�P�F�w�����̒l
//	�Q�F�x�����̒l
//	�R�F�y�����̒l
//�y�߂�l�z
//	�Ȃ�
//�y���@�l�z
//	�Ȃ�
//================================================================================
void CVector::SetValue( float fx , float fy , float fz )
{
	this->m_Vector.x = fx;
	this->m_Vector.y = fy;
	this->m_Vector.z = fz;
	//w�́u1.0�v�ŌŒ�
	this->m_Vector.w = 1.0f;
}

//================================================================================
//ZeroVector�֐�
//�y�@�@�\�z
//	��x�N�g�����쐬����
//�y���@���z
//	�Ȃ�
//�y�߂�l�z
//	�Ăяo�����I�u�W�F�N�g
//�y���@�l�z
//	�Ȃ�
//================================================================================
CVector &CVector::ZeroVector( void )
{
	ZeroMemory( &this->m_Vector , sizeof( VECTOR ) );
	return *this;
}

//================================================================================
//Inverse�֐�
//�y�@�@�\�z
//	�t�x�N�g�����쐬����
//�y���@���z
//	�Ȃ�
//�y�߂�l�z
//	�t�x�N�g��
//�y���@�l�z
//	�Ăяo�����̃x�N�g���͕ω����Ȃ�
//================================================================================
CVector CVector::Inverse( void )const
{
	CVector	vecInverse;

	vecInverse.m_Vector.x = -this->m_Vector.x;
	vecInverse.m_Vector.y = -this->m_Vector.y;
	vecInverse.m_Vector.z = -this->m_Vector.z;

	return vecInverse;
}

//================================================================================
//Length�֐�
//�y�@�@�\�z
//	�x�N�g���̒��������߂�
//�y���@���z
//	�P�F�Q��t���O(�f�t�H���g:FALSE[�Q�悵�Ȃ�])
//�y�߂�l�z
//	�x�N�g���̒���
//�y���@�l�z
//	�Ȃ�
//================================================================================
float CVector::Length( BOOL bSquare )const
{
	float		fLength = 0.0f;
	fLength =	(this->m_Vector.x * this->m_Vector.x) +
			(this->m_Vector.y * this->m_Vector.y) + 
			(this->m_Vector.z * this->m_Vector.z);
	if( bSquare == TRUE ){	//�Q�悷��
		return fLength;
	}
	//�Q�悵�Ȃ�(�������ŕԂ�)
	return (float)sqrt( (double)fLength );
}

//================================================================================
//Normalize�֐�
//�y�@�@�\�z
//	�x�N�g���𐳋K������
//�y���@���z
//	�Ȃ�
//�y�߂�l�z
//	���K�����ꂽ�x�N�g��
//�y���@�l�z
//	�Ȃ�
//================================================================================
CVector CVector::Normalize( void )const
{
	CVector	vecNormalize;
	float	fLength = this->Length();
	//�e�������x�N�g���̒����Ŋ���
	vecNormalize.m_Vector.x = this->m_Vector.x / fLength;
	vecNormalize.m_Vector.y = this->m_Vector.y / fLength;
	vecNormalize.m_Vector.z = this->m_Vector.z / fLength;
	return vecNormalize;
}

//================================================================================
//Dot�֐�
//�y�@�@�\�z
//	�x�N�g���̓��ς����߂�
//�y���@���z
//	�P�F���ς����߂�Ώۂ̃x�N�g��
//	�Q�F���K���t���O
//		(TRUE:���K������ , FALSE:���K�����Ȃ�)
//�y�߂�l�z
//	���ς̒l
//�y���@�l�z
//	�Ȃ�
//================================================================================
float CVector::Dot( const CVector &vec , BOOL bNormalize )const
{
	CVector	vec_copy1 , vec_copy2;	//�v�Z�p
	float	fDot = 0.0f;				//���ϒl

	//�x�N�g�����v�Z�p�ɃR�s�[
	vec_copy1 = *this;
	vec_copy2 = vec;
	if( bNormalize ){	//���K��
		vec_copy1 = vec_copy1.Normalize();
		vec_copy2 = vec_copy2.Normalize();
	}
	fDot =	(vec_copy1.m_Vector.x * vec_copy2.m_Vector.x) +
			(vec_copy1.m_Vector.y * vec_copy2.m_Vector.y) +
			(vec_copy1.m_Vector.z * vec_copy2.m_Vector.z);
	return fDot;
}

//================================================================================
//Cross�֐�
//�y�@�@�\�z
//	�x�N�g���̊O�ς����߂�
//�y���@���z
//	�O�ς����߂�Ώۂ̃x�N�g��
//�y�߂�l�z
//	�@���x�N�g��
//�y���@�l�z
//	DirectX�g�p�i������W�n�j�@OpenGL�Ȃ炻�̂܂܁i�E����W�n�j
//================================================================================
CVector CVector::Cross( const CVector &vec ,BOOL flag )const
{
	CVector	vecCross;	//�@���x�N�g��
	
	vecCross.m_Vector.x =	(this->m_Vector.y * vec.m_Vector.z) - 
							(this->m_Vector.z * vec.m_Vector.y);
	vecCross.m_Vector.y =	(this->m_Vector.z * vec.m_Vector.x) - 
							(this->m_Vector.x * vec.m_Vector.z);
	vecCross.m_Vector.z =	(this->m_Vector.x * vec.m_Vector.y) - 
							(this->m_Vector.y * vec.m_Vector.x);

	//�߂�l�͍�����W�p��
	//�t�x�N�g���ɂ��ĕԂ�
	if(flag)
	{
		return vecCross.Inverse();
	}
	else
	{
		return vecCross;
	}
}

//================================================================================
//InnerProductAngle�֐�
//�y�@�@�\�z
//	�x�N�g���̂Ȃ��p�����߂�
//�y���@���z
//	�p�x�����߂�Ώۂ̃x�N�g��
//�y�߂�l�z
//	�x�N�g���̂Ȃ��p�x(���W�A��)
//�y���@�l�z
//	�߂�l�̊p�x�̓��W�A���P��
//================================================================================
float CVector::InnerProductAngle( const CVector &vec )const
{
	float	fAngle = 0.0f;

	//����(���K���̗L���͊֌W�Ȃ�)
	float	fDot = this->Dot( vec , FALSE );
	fAngle = (float)acos( fDot / (this->Length()*vec.Length()) );
	return fAngle;
}

//================================================================================
//TransformMatrix�֐�
//�y�@�@�\�z
//	�x�N�g�����s��ŕϊ�����
//�y���@���z
//	�P�F�v�Z�Ώۂ̍s��
//�y�߂�l�z
//	�Ăяo�����I�u�W�F�N�g
//�y���@�l�z
//	�Ȃ�
//================================================================================
CVector &CVector::TransformMatrix( const CMatrix &mat )
{
	CVector	vec_copy;	//�v�Z�p
	MATRIX	mat_copy;

	mat_copy = mat.GetMatrix();

	//�x�N�g���̐����ƍs�����Z����
	vec_copy.m_Vector.x =	(this->m_Vector.x * mat_copy._11) +
					(this->m_Vector.y * mat_copy._21) +
					(this->m_Vector.z * mat_copy._31) +
					(this->m_Vector.w * mat_copy._41);
	vec_copy.m_Vector.y =	(this->m_Vector.x * mat_copy._12) +
					(this->m_Vector.y * mat_copy._22) +
					(this->m_Vector.z * mat_copy._32) +
					(this->m_Vector.w * mat_copy._42);
	vec_copy.m_Vector.z =	(this->m_Vector.x * mat_copy._13) +
					(this->m_Vector.y * mat_copy._23) +
					(this->m_Vector.z * mat_copy._33) +
					(this->m_Vector.w * mat_copy._43);
	vec_copy.m_Vector.w =	(this->m_Vector.x * mat_copy._14) +
					(this->m_Vector.y * mat_copy._24) +
					(this->m_Vector.z * mat_copy._34) +
					(this->m_Vector.w * mat_copy._44);
	//�e������w�����Ŋ���
	vec_copy /= vec_copy.m_Vector.w;
	//w�������g������
	vec_copy.m_Vector.w /= vec_copy.m_Vector.w;
	//���g�̃I�u�W�F�N�g�ɃR�s�[
	*this = vec_copy;

	return *this;
}

//================================================================================
//�u=�v�̃I�[�o�[���[�h
//�y�@�@�\�z
//	�x�N�g���̐������R�s�[����
//�y���@���z
//	�P�F�R�s�[���̃x�N�g��
//�y�߂�l�z
//	�Ăяo�����̃I�u�W�F�N�g
//�y���@�l�z
//	�Ȃ�
//================================================================================
CVector &CVector::operator =( const CVector &vec )
{
	this->m_Vector.x = vec.m_Vector.x;
	this->m_Vector.y = vec.m_Vector.y;
	this->m_Vector.z = vec.m_Vector.z;
	this->m_Vector.w = vec.m_Vector.w;
	return *this;
}

//================================================================================
//�u+�v�̃I�[�o�[���[�h
//�y�@�@�\�z
//	�x�N�g���̐��������Z����
//�y���@���z
//	�v�Z�Ώۂ̃x�N�g��
//�y�߂�l�z
//	�v�Z���ʂ̃x�N�g��
//�y���@�l�z
//	�Ȃ�
//================================================================================
CVector CVector::operator +( const CVector &vec )const
{
	CVector	vec_copy;
	vec_copy.m_Vector.x = this->m_Vector.x + vec.m_Vector.x;
	vec_copy.m_Vector.y = this->m_Vector.y + vec.m_Vector.y;
	vec_copy.m_Vector.z = this->m_Vector.z + vec.m_Vector.z;
	return vec_copy;
}

//================================================================================
//�u-�v�̃I�[�o�[���[�h
//�y�@�@�\�z
//	�x�N�g���̐��������Z����
//�y���@���z
//	�P�F�v�Z�Ώۂ̃x�N�g��
//�y�߂�l�z
//	�v�Z���ʂ̃x�N�g��
//�y���@�l�z
//	�Ȃ�
//================================================================================
CVector CVector::operator -( const CVector &vec )const
{
	CVector	vec_copy;
	vec_copy.m_Vector.x = this->m_Vector.x - vec.m_Vector.x;
	vec_copy.m_Vector.y = this->m_Vector.y - vec.m_Vector.y;
	vec_copy.m_Vector.z = this->m_Vector.z - vec.m_Vector.z;
	return vec_copy;
}

//================================================================================
//�u*�v�̃I�[�o�[���[�h
//�y�@�@�\�z
//	�x�N�g���̐����������{����
//�y���@���z
//	�����{����l
//�y�߂�l�z
//	�v�Z���ʂ̃x�N�g��
//�y���@�l�z
//	�Ȃ�
//================================================================================
CVector CVector::operator *( const float fValue )const
{
	CVector	vec_copy;
	vec_copy.m_Vector.x = this->m_Vector.x * fValue;
	vec_copy.m_Vector.y = this->m_Vector.y * fValue;
	vec_copy.m_Vector.z = this->m_Vector.z * fValue;
	return vec_copy;
}

//================================================================================
//�u*�v�̃I�[�o�[���[�h
//�y�@�@�\�z
//	�x�N�g�����s��ŕϊ�����
//�y���@���z
//	�v�Z�Ώۂ̍s��
//�y�߂�l�z
//	�v�Z���ʂ̃x�N�g��
//�y���@�l�z
//	�Ȃ�
//================================================================================
CVector CVector::operator *( const CMatrix &mat )const
{
	CVector	vec_copy = *this;
	vec_copy.TransformMatrix( mat );
	return vec_copy;
}

//================================================================================
//�u/�v�̃I�[�o�[���[�h
//�y�@�@�\�z
//	�x�N�g���̐����������ŏ��Z����
//�y���@���z
//	���Z����l
//�y�߂�l�z
//	�v�Z���ʂ̃x�N�g��
//�y���@�l�z
//	�Ȃ�
//================================================================================
CVector CVector::operator /( const float fValue )const
{
	CVector	vec_copy;
	if( fValue == 0.0f )	return vec_copy;
	vec_copy.m_Vector.x = this->m_Vector.x / fValue;
	vec_copy.m_Vector.y = this->m_Vector.y / fValue;
	vec_copy.m_Vector.z = this->m_Vector.z / fValue;
	return vec_copy;
}

//================================================================================
//�u+=�v�̃I�[�o�[���[�h
//�y�@�@�\�z
//	�x�N�g���̉��Z���s�����ʂ����ӂ֑������
//�y���@���z
//	�v�Z�Ώۂ̃x�N�g��
//�y�߂�l�z
//	�Ăяo�����I�u�W�F�N�g
//�y���@�l�z
//	�Ȃ�
//================================================================================
CVector& CVector::operator +=( const CVector &vec )
{
	this->m_Vector.x += vec.m_Vector.x;
	this->m_Vector.y += vec.m_Vector.y;
	this->m_Vector.z += vec.m_Vector.z;
	return *this;
}

//================================================================================
//�u-=�v�̃I�[�o�[���[�h
//�y�@�@�\�z
//	�x�N�g���̌��Z���s�����ʂ����ӂ֑������
//�y���@���z
//	�v�Z�Ώۂ̃x�N�g��
//�y�߂�l�z
//	�Ăяo�����I�u�W�F�N�g
//�y���@�l�z
//	�Ȃ�
//================================================================================
CVector& CVector::operator -=( const CVector &vec )
{
	this->m_Vector.x -= vec.m_Vector.x;
	this->m_Vector.y -= vec.m_Vector.y;
	this->m_Vector.z -= vec.m_Vector.z;
	return *this;
}

//================================================================================
//�u*=�v�̃I�[�o�[���[�h
//�y�@�@�\�z
//	�x�N�g���̎����{���s�����ʂ����ӂ֑������
//�y���@���z
//	�����{����l
//�y�߂�l�z
//	�Ăяo�����I�u�W�F�N�g
//�y���@�l�z
//	�Ȃ�
//================================================================================
CVector& CVector::operator *=( const float fValue )
{
	this->m_Vector.x *= fValue;
	this->m_Vector.y *= fValue;
	this->m_Vector.z *= fValue;
	return *this;
}

//================================================================================
//�u*=�v�̃I�[�o�[���[�h
//�y�@�@�\�z
//	�x�N�g�����s��ŕϊ����A���ʂ����ӂփR�s�[����
//�y���@���z
//	�v�Z�Ώۂ̍s��
//�y�߂�l�z
//	�Ăяo�����I�u�W�F�N�g
//�y���@�l�z
//	�Ȃ�
//================================================================================
CVector& CVector::operator *=( const CMatrix &mat )
{
	this->TransformMatrix( mat );
	return *this;
}

//================================================================================
//�u/=�v�̃I�[�o�[���[�h
//�y�@�@�\�z
//	�x�N�g���̏��Z���s�����ʂ����ӂɑ������
//�y���@���z
//	���Z����l
//�y�߂�l�z
//	�Ăяo�����I�u�W�F�N�g
//�y���@�l�z
//	�Ȃ�
//================================================================================
CVector& CVector::operator /=( const float fValue )
{
	if( fValue == 0.0f )	return *this;
	this->m_Vector.x /= fValue;
	this->m_Vector.y /= fValue;
	this->m_Vector.z /= fValue;
	return *this;
}
