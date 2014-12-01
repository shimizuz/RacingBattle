//�x������
//�Ӑ}�I�ɋ��^�̊֐����g�p���邽�߂ɁA�x���𐧌�����
#pragma warning (disable : 4996 )
#include <windows.h>
#include "Class_Matrix.h"
#include <cmath>
#include "Class_Vector.h"

#pragma intrinsic(sin,cos)

//================================================================================
//�R���X�g���N�^
//�y�@�@�\�z
//	�S�������O�ŏ���������(��s����쐬)
//�y���@���z
//	�Ȃ�
//�y���@�l�z
//	�Ȃ�
//================================================================================
CMatrix::CMatrix( void )
{
	this->ZeroMatrix();	//��s��쐬
}

//================================================================================
//�R���X�g���N�^
//�y�@�@�\�z
//	�C�ӂ̒l�Ŋe����������������
//�y���@���z
//	1 �` 16:�e�����̒l
//�y���@�l�z
//	�Ȃ�
//================================================================================
CMatrix::CMatrix( float _11 , float _12 , float _13 , float _14 ,
			  float _21 , float _22 , float _23 , float _24 , 
			  float _31 , float _32 , float _33 , float _34 ,
			  float _41 , float _42 , float _43 , float _44 )
{
	//�e�����ɑ��
	MATRIX	mat = 
	{
		_11 , _12 , _13 , _14 ,
		_21 , _22 , _23 , _24 ,
		_31 , _32 , _33 , _34 ,
		_41 , _42 , _43 , _44
	};
	this->m_Matrix = mat;
}

//================================================================================
//�R���X�g���N�^
//�y�@�@�\�z
//	�󂯎�����s��̃R�s�[���쐬����
//�y���@���z
//	1:�R�s�[����CMatrix�I�u�W�F�N�g
//�y���@�l�z
//	�Ȃ�
//================================================================================
CMatrix::CMatrix( const CMatrix& mat )
{
	//�s����R�s�[
	this->m_Matrix = mat.m_Matrix;
}

//================================================================================
//�R���X�g���N�^
//�y�@�@�\�z
//	�v�f��16�̔z�񂩂琬��������������
//�y���@���z
//	1:float�^�z��̃A�h���X
//�y���@�l�z
//	�Ȃ�
//================================================================================
CMatrix::CMatrix( const float *lpMat )
{
	if( lpMat != NULL )
	{
		memcpy( this->m_Matrix.mat , lpMat , sizeof(float)*16 );
	}
	else 
	{
		this->ZeroMatrix();
	}
}

//================================================================================
//�f�X�g���N�^
//�y�@�@�\�z
//	�s��̐������O�ɂ���
//�y���@���z
//	�Ȃ�
//�y���@�l�z
//	�Ȃ�
//================================================================================
CMatrix::~CMatrix( void )
{
	this->ZeroMatrix();
}

//================================================================================
//GetMatrix�֐�
//�y�@�@�\�z
//	�s����擾����
//�y���@���z
//	�Ȃ�
//�y�߂�l�z
//	MATRIX�^�̃f�[�^
//�y���@�l�z
//	�Ȃ�
//================================================================================
MATRIX CMatrix::GetMatrix( void )const
{
	return this->m_Matrix;
}

//================================================================================
//GetElement�֐�
//�y�@�@�\�z
//	�s��̐������擾����
//�y���@���z
//	1:�s�v�f(1�`4)
//	2:��v�f(1�`4)
//�y�߂�l�z
//	�w�肵���v�f�̐���
//�y���@�l�z
//	�z���0�`3�����A�s��̐����Ȃ̂�1�`4�Ŏw��B
//================================================================================
float CMatrix::GetElement( BYTE i , BYTE j )const
{
	//�G���[�`�F�b�N
	if( i == 0 || i > 4 )	return 0.0f;
	if( j == 0 || j > 4 )	return 0.0f;
	//������1�`4�Ȃ̂Łu-1�v�����ĎQ��
	return this->m_Matrix.mat[i-1][j-1];
}

//================================================================================
//SetMatrix�֐�
//�y�@�@�\�z
//	CMatrix�I�u�W�F�N�g����R�s�[���쐬����
//�y���@���z
//	�R�s�[����CMatrix�I�u�W�F�N�g
//�y�߂�l�z
//	�Ȃ�
//�y���@�l�z
//	�Ȃ�
//================================================================================
void CMatrix::SetMatrix( const CMatrix& mat )
{
	this->m_Matrix = mat.m_Matrix;
}

//================================================================================
//SetElement�֐�
//�y�@�@�\�z
//	�w�肵���v�f�̐�����ݒ肷��
//�y���@���z
//	1:�s�v�f(1�`4)
//	2:��v�f(1�`4)
//	3:�����̒l
//�y�߂�l�z
//	�Ȃ�
//�y���@�l�z
//	�s�v�f�E��v�f��1�`4�Ŏw��
//================================================================================
void CMatrix::SetElement( BYTE i , BYTE j , float fValue )
{
	//�G���[�`�F�b�N
	if( i == 0 || i > 4 )	return;
	if( j == 0 || j > 4 )	return;
	this->m_Matrix.mat[i-1][j-1] = fValue;
}

//================================================================================
//ZeroMatrix�֐�
//�y�@�@�\�z
//	�������S�ĂO�̍s��(��s��)���쐬����
//�y���@���z
//	�Ȃ�
//�y�߂�l�z
//	�Ăяo�����I�u�W�F�N�g
//�y���@�l�z
//	�Ȃ�
//================================================================================
CMatrix& CMatrix::ZeroMatrix( void )
{
	ZeroMemory( &this->m_Matrix , sizeof( MATRIX ) );
	return *this;
}

//================================================================================
//Identity�֐�
//�y�@�@�\�z
//	�P�ʍs����쐬����
//�y���@���z
//	�Ȃ�
//�y�߂�l�z
//	�Ăяo�����I�u�W�F�N�g
//�y���@�l�z
//	�Ȃ�
//================================================================================
CMatrix& CMatrix::Identity( void )
{
	//�O�ŏ�����
	this->ZeroMatrix();
	//�Ίp������1��ݒ�
	this->m_Matrix._11 = 1.0f;
	this->m_Matrix._22 = 1.0f;
	this->m_Matrix._33 = 1.0f;
	this->m_Matrix._44 = 1.0f;
	return *this;
}

//================================================================================
//Inverse�֐�
//�y�@�@�\�z
//	�t�s����쐬����
//�y���@���z
//	�Ȃ�
//�y�߂�l�z
//	�t�s��
//�y���@�l�z
//	�Ăяo�����I�u�W�F�N�g�͋t�s��ɂȂ�Ȃ�
//================================================================================
CMatrix CMatrix::Inverse( void )
{
	//�s�񎮂����߂�
	float	fDet =	this->m_Matrix._11*( (this->m_Matrix._22*this->m_Matrix._33*this->m_Matrix._44)+
						    (this->m_Matrix._23*this->m_Matrix._34*this->m_Matrix._42)+
						    (this->m_Matrix._24*this->m_Matrix._32*this->m_Matrix._43)-
						    (this->m_Matrix._24*this->m_Matrix._33*this->m_Matrix._42)-
						    (this->m_Matrix._23*this->m_Matrix._32*this->m_Matrix._44)-
						    (this->m_Matrix._22*this->m_Matrix._34*this->m_Matrix._43) ) - 
				this->m_Matrix._12*( (this->m_Matrix._21*this->m_Matrix._33*this->m_Matrix._44)+
						    (this->m_Matrix._23*this->m_Matrix._34*this->m_Matrix._41)+
						    (this->m_Matrix._24*this->m_Matrix._31*this->m_Matrix._43)-
						    (this->m_Matrix._24*this->m_Matrix._33*this->m_Matrix._41)-
						    (this->m_Matrix._23*this->m_Matrix._31*this->m_Matrix._44)-
						    (this->m_Matrix._21*this->m_Matrix._34*this->m_Matrix._43) ) + 
				this->m_Matrix._13*( (this->m_Matrix._21*this->m_Matrix._32*this->m_Matrix._44)+
						    (this->m_Matrix._22*this->m_Matrix._34*this->m_Matrix._41)+
						    (this->m_Matrix._24*this->m_Matrix._31*this->m_Matrix._42)-
						    (this->m_Matrix._24*this->m_Matrix._32*this->m_Matrix._41)-
						    (this->m_Matrix._22*this->m_Matrix._31*this->m_Matrix._44)-
						    (this->m_Matrix._21*this->m_Matrix._34*this->m_Matrix._42) ) - 
				this->m_Matrix._14*( (this->m_Matrix._21*this->m_Matrix._32*this->m_Matrix._43)+
						    (this->m_Matrix._22*this->m_Matrix._33*this->m_Matrix._41)+
						    (this->m_Matrix._23*this->m_Matrix._31*this->m_Matrix._42)-
						    (this->m_Matrix._23*this->m_Matrix._32*this->m_Matrix._41)-
						    (this->m_Matrix._22*this->m_Matrix._31*this->m_Matrix._43)-
						    (this->m_Matrix._21*this->m_Matrix._33*this->m_Matrix._42) );
	//�s�񎮂̒l���O�̏ꍇ�t�s��͑��݂��Ȃ�
	if( !fDet )	return *this;

	//�e���������߂�
	MATRIX	mat = {0.0f};	//�t�s��p
	mat.mat[0][0] = (+((this->m_Matrix._22*this->m_Matrix._33*this->m_Matrix._44)+
					   (this->m_Matrix._23*this->m_Matrix._34*this->m_Matrix._42)+
					   (this->m_Matrix._24*this->m_Matrix._32*this->m_Matrix._43)-
					   (this->m_Matrix._24*this->m_Matrix._33*this->m_Matrix._42)-
					   (this->m_Matrix._23*this->m_Matrix._32*this->m_Matrix._44)-
					   (this->m_Matrix._22*this->m_Matrix._34*this->m_Matrix._43))) / fDet;
	mat.mat[1][0] = (-((this->m_Matrix._21*this->m_Matrix._33*this->m_Matrix._44)+
					   (this->m_Matrix._23*this->m_Matrix._34*this->m_Matrix._41)+
					   (this->m_Matrix._24*this->m_Matrix._31*this->m_Matrix._43)-
					   (this->m_Matrix._24*this->m_Matrix._33*this->m_Matrix._41)-
					   (this->m_Matrix._23*this->m_Matrix._31*this->m_Matrix._44)-
					   (this->m_Matrix._21*this->m_Matrix._34*this->m_Matrix._43))) / fDet;
	mat.mat[2][0] = (+((this->m_Matrix._21*this->m_Matrix._32*this->m_Matrix._44)+
					   (this->m_Matrix._22*this->m_Matrix._34*this->m_Matrix._41)+
					   (this->m_Matrix._24*this->m_Matrix._31*this->m_Matrix._42)-
					   (this->m_Matrix._24*this->m_Matrix._32*this->m_Matrix._41)-
					   (this->m_Matrix._22*this->m_Matrix._31*this->m_Matrix._44)-
					   (this->m_Matrix._21*this->m_Matrix._34*this->m_Matrix._42))) / fDet;
	mat.mat[3][0] = (-((this->m_Matrix._21*this->m_Matrix._32*this->m_Matrix._43)+
					   (this->m_Matrix._22*this->m_Matrix._33*this->m_Matrix._41)+
					   (this->m_Matrix._23*this->m_Matrix._31*this->m_Matrix._42)-
					   (this->m_Matrix._23*this->m_Matrix._32*this->m_Matrix._41)-
					   (this->m_Matrix._22*this->m_Matrix._31*this->m_Matrix._43)-
					   (this->m_Matrix._21*this->m_Matrix._33*this->m_Matrix._42))) / fDet;

	mat.mat[0][1] = (-((this->m_Matrix._12*this->m_Matrix._33*this->m_Matrix._44)+
					   (this->m_Matrix._13*this->m_Matrix._34*this->m_Matrix._42)+
					   (this->m_Matrix._14*this->m_Matrix._32*this->m_Matrix._43)-
					   (this->m_Matrix._14*this->m_Matrix._33*this->m_Matrix._42)-
					   (this->m_Matrix._13*this->m_Matrix._32*this->m_Matrix._44)-
					   (this->m_Matrix._12*this->m_Matrix._34*this->m_Matrix._43))) / fDet;
	mat.mat[1][1] = (+((this->m_Matrix._11*this->m_Matrix._33*this->m_Matrix._44)+
					   (this->m_Matrix._13*this->m_Matrix._34*this->m_Matrix._41)+
					   (this->m_Matrix._14*this->m_Matrix._31*this->m_Matrix._43)-
					   (this->m_Matrix._14*this->m_Matrix._33*this->m_Matrix._41)-
					   (this->m_Matrix._13*this->m_Matrix._31*this->m_Matrix._44)-
					   (this->m_Matrix._11*this->m_Matrix._34*this->m_Matrix._43))) / fDet;
	mat.mat[2][1] = (-((this->m_Matrix._11*this->m_Matrix._32*this->m_Matrix._44)+
					   (this->m_Matrix._12*this->m_Matrix._34*this->m_Matrix._41)+
					   (this->m_Matrix._14*this->m_Matrix._31*this->m_Matrix._42)-
					   (this->m_Matrix._14*this->m_Matrix._32*this->m_Matrix._41)-
					   (this->m_Matrix._12*this->m_Matrix._31*this->m_Matrix._44)-
					   (this->m_Matrix._11*this->m_Matrix._34*this->m_Matrix._42))) / fDet;
	mat.mat[3][1] = (+((this->m_Matrix._11*this->m_Matrix._32*this->m_Matrix._43)+
					   (this->m_Matrix._12*this->m_Matrix._33*this->m_Matrix._41)+
					   (this->m_Matrix._13*this->m_Matrix._31*this->m_Matrix._42)-
					   (this->m_Matrix._13*this->m_Matrix._32*this->m_Matrix._41)-
					   (this->m_Matrix._12*this->m_Matrix._31*this->m_Matrix._43)-
					   (this->m_Matrix._11*this->m_Matrix._33*this->m_Matrix._42))) / fDet;

	mat.mat[0][2] = (+((this->m_Matrix._12*this->m_Matrix._23*this->m_Matrix._44)+
					   (this->m_Matrix._13*this->m_Matrix._24*this->m_Matrix._42)+
					   (this->m_Matrix._14*this->m_Matrix._22*this->m_Matrix._43)-
					   (this->m_Matrix._14*this->m_Matrix._23*this->m_Matrix._42)-
					   (this->m_Matrix._13*this->m_Matrix._22*this->m_Matrix._44)-
					   (this->m_Matrix._12*this->m_Matrix._24*this->m_Matrix._43))) / fDet;
	mat.mat[1][2] = (-((this->m_Matrix._11*this->m_Matrix._23*this->m_Matrix._44)+
					   (this->m_Matrix._13*this->m_Matrix._24*this->m_Matrix._41)+
					   (this->m_Matrix._14*this->m_Matrix._21*this->m_Matrix._43)-
					   (this->m_Matrix._14*this->m_Matrix._23*this->m_Matrix._41)-
					   (this->m_Matrix._13*this->m_Matrix._21*this->m_Matrix._44)-
					   (this->m_Matrix._11*this->m_Matrix._24*this->m_Matrix._43))) / fDet;
	mat.mat[2][2] = (+((this->m_Matrix._11*this->m_Matrix._22*this->m_Matrix._44)+
					   (this->m_Matrix._12*this->m_Matrix._24*this->m_Matrix._41)+
					   (this->m_Matrix._14*this->m_Matrix._21*this->m_Matrix._42)-
					   (this->m_Matrix._14*this->m_Matrix._22*this->m_Matrix._41)-
					   (this->m_Matrix._12*this->m_Matrix._21*this->m_Matrix._44)-
					   (this->m_Matrix._11*this->m_Matrix._24*this->m_Matrix._42))) / fDet;
	mat.mat[3][2] = (-((this->m_Matrix._11*this->m_Matrix._22*this->m_Matrix._43)+
					   (this->m_Matrix._12*this->m_Matrix._23*this->m_Matrix._41)+
					   (this->m_Matrix._13*this->m_Matrix._21*this->m_Matrix._42)-
					   (this->m_Matrix._13*this->m_Matrix._22*this->m_Matrix._41)-
					   (this->m_Matrix._12*this->m_Matrix._21*this->m_Matrix._43)-
					   (this->m_Matrix._11*this->m_Matrix._23*this->m_Matrix._42))) / fDet;

	mat.mat[0][3] = (-((this->m_Matrix._12*this->m_Matrix._23*this->m_Matrix._34)+
					   (this->m_Matrix._13*this->m_Matrix._24*this->m_Matrix._32)+
					   (this->m_Matrix._14*this->m_Matrix._22*this->m_Matrix._33)-
					   (this->m_Matrix._14*this->m_Matrix._23*this->m_Matrix._32)-
					   (this->m_Matrix._13*this->m_Matrix._22*this->m_Matrix._34)-
					   (this->m_Matrix._12*this->m_Matrix._24*this->m_Matrix._33))) / fDet;
	mat.mat[1][3] = (+((this->m_Matrix._11*this->m_Matrix._23*this->m_Matrix._34)+
					   (this->m_Matrix._13*this->m_Matrix._24*this->m_Matrix._31)+
					   (this->m_Matrix._14*this->m_Matrix._21*this->m_Matrix._33)-
					   (this->m_Matrix._14*this->m_Matrix._23*this->m_Matrix._31)-
					   (this->m_Matrix._13*this->m_Matrix._21*this->m_Matrix._34)-
					   (this->m_Matrix._11*this->m_Matrix._24*this->m_Matrix._33))) / fDet;
	mat.mat[2][3] = (-((this->m_Matrix._11*this->m_Matrix._22*this->m_Matrix._34)+
					   (this->m_Matrix._12*this->m_Matrix._24*this->m_Matrix._31)+
					   (this->m_Matrix._14*this->m_Matrix._21*this->m_Matrix._32)-
					   (this->m_Matrix._14*this->m_Matrix._22*this->m_Matrix._31)-
					   (this->m_Matrix._12*this->m_Matrix._21*this->m_Matrix._34)-
					   (this->m_Matrix._11*this->m_Matrix._24*this->m_Matrix._32))) / fDet;
	mat.mat[3][3] = (+((this->m_Matrix._11*this->m_Matrix._22*this->m_Matrix._33)+
					   (this->m_Matrix._12*this->m_Matrix._23*this->m_Matrix._31)+
					   (this->m_Matrix._13*this->m_Matrix._21*this->m_Matrix._32)-
					   (this->m_Matrix._13*this->m_Matrix._22*this->m_Matrix._31)-
					   (this->m_Matrix._12*this->m_Matrix._21*this->m_Matrix._33)-
					   (this->m_Matrix._11*this->m_Matrix._23*this->m_Matrix._32))) / fDet;

	CMatrix	matInverse;		//�t�s��p
	matInverse.m_Matrix = mat;	//�t�s����R�s�[
	//�t�s���Ԃ�
	return matInverse;
	//�����g�̃����o���t�s��ŏ��������Ȃ��悤����
}
//================================================================================
//[�@�\]
//�s���]�u����
//[����]
//����
//[�߂�l]
//�]�u�����s��
//[���l]
//DirectX��OpenGL�ł͍��W�n���Ⴄ�ׁi������W�n�ƉE����W�n�ł̍s��]�u�j
//================================================================================
CMatrix CMatrix::Transpose(void)
{
	int i = 0,j = 0;
	CMatrix matTranspose;	//�]�u�p

	matTranspose.Identity(); //���K��
	
	for(i = 0;i < 4;i++)
	{
		for(j = 0;j < 4;j++)
		{
			matTranspose.m_Matrix.mat[i][j] = this->m_Matrix.mat[j][i];	//�]�u
		}
	}
	//�]�u�����s���Ԃ�
	return matTranspose;
}
//================================================================================
//[�@�\]�F���s�ړ��s�񐶐�
//[����]�F�x�N�g��
//[�߂�l]�F����
//================================================================================
void CMatrix::setTranslation(const CVector &vec)
{
	m_Matrix._11 = m_Matrix._22 = m_Matrix._33 = m_Matrix._44 = 1.0f;
	m_Matrix._12 = m_Matrix._13 = m_Matrix._21 = m_Matrix._23 = m_Matrix._31 = m_Matrix._32 = m_Matrix._41 = m_Matrix._42 = m_Matrix._43 = 0;

	m_Matrix._14 = vec.GetX();
	m_Matrix._24 = vec.GetY();
	m_Matrix._34 = vec.GetZ();

}
//================================================================================
//[�@�\]�F�g�k�s�񐶐�
//[����]�F�x�N�g��
//[�߂�l]�F����
//================================================================================
void CMatrix::setScaling(const CVector &vec)
{
	m_Matrix._44 = 1;
	m_Matrix._12 = m_Matrix._13 = m_Matrix._14 = 0;
	m_Matrix._21 = m_Matrix._23 = m_Matrix._24 = 0;
	m_Matrix._31 = m_Matrix._32 = m_Matrix._34 = 0;
	
	m_Matrix._11 = vec.GetX();
	m_Matrix._22 = vec.GetY();
	m_Matrix._33 = vec.GetZ();
}
//================================================================================
//[�@�\]�F��]�s��X����
//[����]�F���W�A��
//[�߂�l]�F����
//================================================================================
void CMatrix::setRotationX(const double rad)
{
	double s = sin(rad);
	double c = cos(rad);
	
	m_Matrix._12 = m_Matrix._13 = m_Matrix._14 = m_Matrix._21 = m_Matrix._24 = m_Matrix._31 = m_Matrix._34 = 0;
	m_Matrix._41 = m_Matrix._42 = m_Matrix._43 = 0;

	m_Matrix._44 = 1;
	m_Matrix._22 = m_Matrix._33 = (float)c;
	m_Matrix._23 = (float)-s;
	m_Matrix._32 = (float)s;
}
//================================================================================
//[�@�\]�F��]�s��Y����
//[����]�F���W�A��
//[�߂�l]�F����
//================================================================================
void CMatrix::setRotationY(const double rad)
{
	double s = sin(rad);
	double c = cos(rad);
	
	m_Matrix._12 = m_Matrix._14 = m_Matrix._21 = m_Matrix._23 = m_Matrix._24 = 0;
	m_Matrix._32 = m_Matrix._34 = m_Matrix._41 = m_Matrix._42 = m_Matrix._43 = 0;
	
	m_Matrix._44 = 1;
	m_Matrix._11 = m_Matrix._33 = (float)c;
	m_Matrix._13 = (float)s;
	m_Matrix._31 = (float)-s;
}
//================================================================================
//[�@�\]�F��]�s��Z����
//[����]�F���W�A��
//[�߂�l]�F����
//================================================================================
void CMatrix::setRotationZ(const double rad)
{
	double s = sin(rad);
	double c = cos(rad);
	
	m_Matrix._13 = m_Matrix._14 = m_Matrix._23 = m_Matrix._24 = m_Matrix._31 = m_Matrix._32 = m_Matrix._34 = 0;
	m_Matrix._41 = m_Matrix._42 = m_Matrix._43 = 0;

	m_Matrix._11 = m_Matrix._22 = (float)c;
	m_Matrix._12 = (float)-s;
	m_Matrix._21 = (float)s;
	m_Matrix._33 = m_Matrix._44 = 1;
	
}
//================================================================================
//[�@�\]�F���s�ړ��s��Ə�Z
//[����]�F�x�N�g��
//[�߂�l]�F����
//================================================================================
void CMatrix::Translate(const CVector &vec)
{
	m_Matrix._14 += m_Matrix._11 * vec.GetX() + m_Matrix._12 * vec.GetY() + m_Matrix._13 * vec.GetZ();
	m_Matrix._24 += m_Matrix._21 * vec.GetX() + m_Matrix._22 * vec.GetY() + m_Matrix._23 * vec.GetZ();
	m_Matrix._34 += m_Matrix._31 * vec.GetX() + m_Matrix._32 * vec.GetY() + m_Matrix._33 * vec.GetZ();

}
//================================================================================
//[�@�\]�F�g�k�s��Ə�Z
//[����]�F�x�N�g��
//[�߂�l]�F����
//================================================================================
void CMatrix::Scaling(const CVector &vec)
{
	m_Matrix._11 *= vec.GetX();
	m_Matrix._12 *= vec.GetY();
	m_Matrix._13 *= vec.GetZ();
	m_Matrix._21 *= vec.GetX();
	m_Matrix._22 *= vec.GetY();
	m_Matrix._23 *= vec.GetZ();
	m_Matrix._31 *= vec.GetX();
	m_Matrix._32 *= vec.GetY();
	m_Matrix._33 *= vec.GetZ();
}
//================================================================================
//[�@�\]�FX��]�s��Ə�Z
//[����]�F���W�A��
//[�߂�l]�F����
//================================================================================
void CMatrix::RotateX(double rad)
{
	double s = sin(rad);
	double c = cos(rad);
	double t;
	
	//1�s��
	t = c * m_Matrix._12 + s * m_Matrix._13;
	m_Matrix._13 = (float)(-s * m_Matrix._12 + c * m_Matrix._13);
	m_Matrix._12 = (float)t;
	//2�s��
	t = c * m_Matrix._22 + s * m_Matrix._23;
	m_Matrix._23 = (float)(-s * m_Matrix._22 + c * m_Matrix._23);
	m_Matrix._22 = (float)t;
	//3�s��
	t = c * m_Matrix._32 + s * m_Matrix._33;
	m_Matrix._33 = (float)(-s * m_Matrix._32 + c * m_Matrix._33);
	m_Matrix._32 = (float)t;
}
//================================================================================
//[�@�\]�FY��]�s��Ə�Z
//[����]�F���W�A��
//[�߂�l]�F����
//================================================================================
void CMatrix::RotateY(double rad)
{
	double s = sin(rad);
	double c = cos(rad);
	double t;
	
	//1�s��
	t = c * m_Matrix._11 - s * m_Matrix._13;
	m_Matrix._13 = (float)(s * m_Matrix._11 + c * m_Matrix._13);
	m_Matrix._11 = (float)t;
	//2�s��
	t = c * m_Matrix._21 - s * m_Matrix._23;
	m_Matrix._23 = (float)(s * m_Matrix._21 + c * m_Matrix._23);
	m_Matrix._21 = (float)t;
	//3�s��
	t = c * m_Matrix._31 - s * m_Matrix._33;
	m_Matrix._33 = (float)(s * m_Matrix._31 + c * m_Matrix._33);
	m_Matrix._31 = (float)t;
}

//================================================================================
//[�@�\]�FZ��]�s��Ə�Z
//[����]�F���W�A��
//[�߂�l]�F����
//================================================================================
void CMatrix::RotateZ(double rad)
{
	double s = sin(rad);
	double c = cos(rad);
	double t;
	
	//1�s��
	t = c * m_Matrix._11 + s * m_Matrix._12;
	m_Matrix._12 = (float)(-s * m_Matrix._11 + c * m_Matrix._12);
	m_Matrix._11 = (float)t;
	//2�s��
	t = c * m_Matrix._21 + s * m_Matrix._22;
	m_Matrix._22 = (float)(-s * m_Matrix._21 + c * m_Matrix._22);
	m_Matrix._21 = (float)t;
	//3�s��
	t = c * m_Matrix._31 + s * m_Matrix._32;
	m_Matrix._32 = (float)(-s * m_Matrix._31 + c * m_Matrix._32);
	m_Matrix._31 = (float)t;
}

//================================================================================
//�u=�v�I�[�o�[���[�h
//�y�@�@�\�z
//	�s������ӂ֑������
//�y���@���z
//	1:����Ώۂ�CMatrix�I�u�W�F�N�g
//�y�߂�l�z
//	�Ăяo�����I�u�W�F�N�g
//�y���@�l�z
//	�Ȃ�
//================================================================================
CMatrix& CMatrix::operator =( const CMatrix& mat )
{
	this->m_Matrix = mat.m_Matrix;
	return *this;
}

//================================================================================
//�u+�v�I�[�o�[���[�h
//�y�@�@�\�z
//	�s������Z����
//�y���@���z
//	���Z�Ώۂ�CMatrix�I�u�W�F�N�g
//�y�߂�l�z
//	�v�Z���ʂ̃I�u�W�F�N�g
//�y���@�l�z
//	�Ȃ�
//================================================================================
CMatrix  CMatrix::operator +( const CMatrix& mat )const
{
	CMatrix	mat_copy;	//�v�Z�p
	int		i = 0 , j = 0;
	//�Ăяo�����̍s����R�s�[
	mat_copy.SetMatrix( *this );
	for( i = 0 ; i < 4 ; i++ ){
		for( j = 0 ; j < 4 ; j++ ){
			mat_copy.m_Matrix.mat[i][j] += mat.m_Matrix.mat[i][j];
		}
	}
	return mat_copy;
}

//================================================================================
//�u-�v�I�[�o�[���[�h
//�y�@�@�\�z
//	�s������Z����
//�y���@���z
//	���Z�Ώۂ�CMatrix�I�u�W�F�N�g
//�y�߂�l�z
//	�v�Z���ʂ̃I�u�W�F�N�g
//�y���@�l�z
//	�Ȃ�
//================================================================================
CMatrix  CMatrix::operator -( const CMatrix& mat )const
{
	CMatrix	mat_copy;	//�v�Z�p
	int		i = 0 , j = 0;
	//�Ăяo�����̍s����R�s�[
	mat_copy.SetMatrix( *this );
	for( i = 0 ; i < 4 ; i++ ){
		for( j = 0 ; j < 4 ; j++ ){
			mat_copy.m_Matrix.mat[i][j] -= mat.m_Matrix.mat[i][j];
		}
	}
	return mat_copy;
}

//================================================================================
//�u*�v�I�[�o�[���[�h
//�y�@�@�\�z
//	�s�����Z����
//�y���@���z
//	��Z�Ώۂ�CMatrix�I�u�W�F�N�g
//�y�߂�l�z
//	�v�Z���ʂ̃I�u�W�F�N�g
//�y���@�l�z
//	�Ȃ�
//================================================================================
CMatrix  CMatrix::operator *( const CMatrix& mat )const
{
	CMatrix	mat_copy;	//�v�Z�p
	int		i = 0 , j = 0;
	//�Ăяo�����̍s����R�s�[
	mat_copy.SetMatrix( *this );
	for( i = 0 ; i < 4 ; i++ ){
		for( j = 0 ; j < 4 ; j++ ){
			mat_copy.m_Matrix.mat[i][j] = (this->m_Matrix.mat[i][0]*mat.m_Matrix.mat[0][j]) + 
							(this->m_Matrix.mat[i][1]*mat.m_Matrix.mat[1][j]) + 
							(this->m_Matrix.mat[i][2]*mat.m_Matrix.mat[2][j]) + 
							(this->m_Matrix.mat[i][3]*mat.m_Matrix.mat[3][j]);
		}
	}
	return mat_copy;
}

//================================================================================
//�u*�v�I�[�o�[���[�h
//�y�@�@�\�z
//	�s��������{����
//�y���@���z
//	�����{����l
//�y�߂�l�z
//	�v�Z���ʂ̃I�u�W�F�N�g
//�y���@�l�z
//	�Ȃ�
//================================================================================
CMatrix  CMatrix::operator *( const float fValue )const
{
	CMatrix	mat_copy;	//�v�Z�p
	int		i = 0 , j = 0;
	//�Ăяo�����̍s����R�s�[
	mat_copy.SetMatrix( *this );
	for( i = 0 ; i < 4 ; i++ ){
		for( j = 0 ; j < 4 ; j++ ){
			mat_copy.m_Matrix.mat[i][j] *= fValue;
		}
	}
	return mat_copy;
}

//================================================================================
//�u/�v�I�[�o�[���[�h
//�y�@�@�\�z
//	�s��������ŏ��Z����
//�y���@���z
//	���Z����l
//�y�߂�l�z
//	�v�Z���ʂ̃I�u�W�F�N�g
//�y���@�l�z
//	�Ȃ�
//================================================================================
CMatrix  CMatrix::operator /( const float fValue )const
{
	CMatrix	mat_copy;	//�v�Z�p
	int		i = 0 , j = 0;
	//�Ăяo�����̍s����R�s�[
	mat_copy.SetMatrix( *this );
	//�O���Z�`�F�b�N
	if( fValue == 0 )	return mat_copy;
	for( i = 0 ; i < 4 ; i++ ){
		for( j = 0 ; j < 4 ; j++ ){
			mat_copy.m_Matrix.mat[i][j] /= fValue;
		}
	}
	return mat_copy;
}

//================================================================================
//�u+=�v�I�[�o�[���[�h
//�y�@�@�\�z
//	�s��̉��Z���s�����ʂ����ӂ֑������
//�y���@���z
//	���Z�Ώۂ�CMatrix�I�u�W�F�N�g
//�y�߂�l�z
//	�v�Z���ʂ̍��ӃI�u�W�F�N�g
//�y���@�l�z
//	�Ȃ�
//================================================================================
CMatrix& CMatrix::operator +=( const CMatrix& mat )
{
	int	i = 0 , j = 0;
	for( i = 0 ; i < 4 ; i++ )
	{
		for( j = 0 ; j < 4 ; j++ )
		{
			this->m_Matrix.mat[i][j] += mat.m_Matrix.mat[i][j];
		}
	}
	return *this;
}

//================================================================================
//�u-=�v�I�[�o�[���[�h
//�y�@�@�\�z
//	�s��̌��Z���s�����ʂ����ӂ֑������
//�y���@���z
//	���Z�Ώۂ�CMatrix�I�u�W�F�N�g
//�y�߂�l�z
//	�v�Z���ʂ̍��ӃI�u�W�F�N�g
//�y���@�l�z
//	�Ȃ�
//================================================================================
CMatrix& CMatrix::operator -=( const CMatrix& mat )
{
	int	i = 0 , j = 0;
	for( i = 0 ; i < 4 ; i++ )
	{
		for( j = 0 ; j < 4 ; j++ )
		{
			this->m_Matrix.mat[i][j] -= mat.m_Matrix.mat[i][j];
		}
	}
	return *this;
}

//================================================================================
//�u*=�v�I�[�o�[���[�h
//�y�@�@�\�z
//	�s��̏�Z���s�����ʂ����ӂ֑������
//�y���@���z
//	��Z�Ώۂ�CMatrix�I�u�W�F�N�g
//�y�߂�l�z
//	�v�Z���ʂ̍��ӃI�u�W�F�N�g
//�y���@�l�z
//	�Ȃ�
//================================================================================
CMatrix& CMatrix::operator *=( const CMatrix& mat )
{
	int	i = 0 , j = 0;
	CMatrix	mat_copy;	//�v�Z�p
	for( i = 0 ; i < 4 ; i++ )
	{
		for( j = 0 ; j < 4 ; j++ )
		{
			mat_copy.m_Matrix.mat[i][j] =
				(this->m_Matrix.mat[i][0]*mat.m_Matrix.mat[0][j]) + 
				(this->m_Matrix.mat[i][1]*mat.m_Matrix.mat[1][j]) + 
				(this->m_Matrix.mat[i][2]*mat.m_Matrix.mat[2][j]) + 
				(this->m_Matrix.mat[i][3]*mat.m_Matrix.mat[3][j]);
		}
	}
	*this = mat_copy;
	return *this;
}

//================================================================================
//�u*=�v�I�[�o�[���[�h
//�y�@�@�\�z
//	�s��������ŏ�Z���A���ʂ����ӂ֑������
//�y���@���z
//	�����{�̒l
//�y�߂�l�z
//	�v�Z���ʂ̍��ӃI�u�W�F�N�g
//�y���@�l�z
//	�Ȃ�
//================================================================================
CMatrix& CMatrix::operator *=( const float fValue )
{
	int	i = 0 , j = 0;
	for( i = 0 ; i < 4 ; i++ )
	{
		for( j = 0 ; j < 4 ; j++ )
		{
			this->m_Matrix.mat[i][j] *= fValue;
		}
	}
	return *this;
}

//================================================================================
//�u/=�v�I�[�o�[���[�h
//�y�@�@�\�z
//	�s��������ŏ��Z���A���ʂ����ӂ֑������
//�y���@���z
//	���Z����l
//�y�߂�l�z
//	�v�Z���ʂ̍��ӃI�u�W�F�N�g
//�y���@�l�z
//	�Ȃ�
//================================================================================
CMatrix& CMatrix::operator /=( const float fValue )
{
	int	i = 0 , j = 0;
	//�O���Z�`�F�b�N
	if( fValue == 0 )	return *this;
	for( i = 0 ; i < 4 ; i++ )
	{
		for( j = 0 ; j < 4 ; j++ )
		{
			this->m_Matrix.mat[i][j] /= fValue;
		}
	}
	return *this;
}
//===================================================================================================================================
//Scaling�֐�
//[�@�\]�F�X�P�[�����O�s����쐬����
//[����]�F�X�P�[�����O�{��
//[�߂�l]�F�Ăяo�����I�u�W�F�N�g
//[���l]�F�S�����𓯂��{���ŃX�P�[�����O����
//====================================================================================================================================
CMatrix &CMatrix::Scaling(float fScale){
	
	this->Identity();	//�P�ʍs��쐬

	//�e�����ɔ{�����i�[
	this->m_Matrix._11 = fScale;
	this->m_Matrix._22 = fScale;
	this->m_Matrix._33 = fScale;


	return *this;
}
//===================================================================================================================================
//Scaling�֐�
//[�@�\]�F�X�P�[�����O�s����쐬����
//[����]1�FX�����{��
//		2�FY�����{��
//		3�FZ�����{��
//[�߂�l]�F�Ăяo�����I�u�W�F�N�g
//[���l]�F�S�����𓯂��{���ŃX�P�[�����O����
//====================================================================================================================================
CMatrix &CMatrix::Scaling(float fScaleX, float fScaleY, float fScaleZ){
	
	this->Identity();	//�P�ʍs��쐬

	//�e�����ɔ{�����i�[
	this->m_Matrix._11 = fScaleX;
	this->m_Matrix._22 = fScaleY;
	this->m_Matrix._33 = fScaleZ;


	return *this;
}
//=====================================================================================================================================
//RotationX�֐�
//[�@�\]�FX����̉�]�s����쐬����
//[����]1�F��]�p�x
//[�߂�l]�F�Ăяo�����I�u�W�F�N�g
//[���l]�F�p�x�̓��W�A���Ŏw��
//====================================================================================================================================
CMatrix &CMatrix::RotationX(float fAngle){

	this->Identity();	//�P�ʍs��쐬

	//�Ή����鐬���ɎO�p�֐��̒l���i�[

	this->m_Matrix._22 = (float)cos(fAngle);
	this->m_Matrix._23 = (float)sin(fAngle);
	this->m_Matrix._32 = -(float)sin(fAngle);
	this->m_Matrix._33 = (float)cos(fAngle);

	return *this;

}
//=====================================================================================================================================
//RotationY�֐�
//[�@�\]�FY����̉�]�s����쐬����
//[����]1�F��]�p�x
//[�߂�l]�F�Ăяo�����I�u�W�F�N�g
//[���l]�F�p�x�̓��W�A���Ŏw��
//====================================================================================================================================
CMatrix &CMatrix::RotationY(float fAngle){
	
	this->Identity();	//�P�ʍs��쐬

	//�Ή����鐬���ɎO�p�֐��̒l���w��
	this->m_Matrix._11 = (float)cos(fAngle);
	this->m_Matrix._13 = -(float)sin(fAngle);
	this->m_Matrix._31 = (float)sin(fAngle);
	this->m_Matrix._33 = (float)cos(fAngle);

	return *this;

}
//=====================================================================================================================================
//RotationZ�֐�
//[�@�\]�FZ����̉�]�s����쐬����
//[����]1�F��]�p�x
//[�߂�l]�F�Ăяo�����I�u�W�F�N�g
//[���l]�F�p�x�̓��W�A���Ŏw��
//====================================================================================================================================
CMatrix &CMatrix::RotationZ(float fAngle){
	
	this->Identity();	//�P�ʍs��쐬

	//�Ή����鐬���ɎO�p�֐��̒l����
	this->m_Matrix._11 = (float)cos(fAngle);
	this->m_Matrix._12 = (float)sin(fAngle);
	this->m_Matrix._21 = -(float)sin(fAngle);
	this->m_Matrix._22 = (float)cos(fAngle);

	
	return *this;
}
//====================================================================================================================================
//[�@�\]�F���[�s�b�`���[����]�s����쐬����
//[����]�F1�F���[��]�iY����]�j
//		�F2�F�s�b�`��]�iX����]�j
//		�F3�F���[����]�iZ����]�j
//[�߂�l]�F�Ăяo�����I�u�W�F�N�g
//[���l]�F�p�x�̓��W�A���Ŏw��
//=====================================================================================================================================
CMatrix &CMatrix::RotationYawPitchRoll(float fYaw, float fPitch, float fRoll){
	
	CMatrix matRotX,matRotY,matRotZ;

	//�e���̉�]�s����쐬
	matRotX.RotationX(fPitch);
	matRotY.RotationY(fYaw);
	matRotZ.RotationZ(fRoll);

	this->Identity();	//�P�ʍs��쐬
	//Z,X,Y�̏��ōs��̐ς����߂�
	*this = matRotZ * matRotX * matRotY;

	return *this;

}
//=====================================================================================================================================
//[�@�\]�F���s�ړ��s����쐬����
//[����]�F1�FX�����̈ړ���
//		�F2�FY�����̈ړ���
//		�F3�FZ�����̈ړ���
//[�߂�l]�F�Ăяo�����̃I�u�W�F�N�g
//[���l]�F����
//=====================================================================================================================================
CMatrix &CMatrix::Translation(float fTx, float fTy, float fTz){
	
	this->Identity();	//�P�ʍs��쐬
	//�Ή����鐬���Ɉړ��ʂ��i�[
	this->m_Matrix._41 = fTx;
	this->m_Matrix._42 = fTy;
	this->m_Matrix._43 = fTz;
	return *this;
}
//=====================================================================================================================================
//[�@�\]�F������W�n�p�̃r���[�s����쐬����
//[����]�F��1�����F�J�����̈ʒu�x�N�g��
//		�F��2�����F�J�����̒����_�x�N�g��
//		�F��3�����F������x�N�g��
//[�߂�l]�F�Ăяo�����I�u�W�F�N�g
//[���l]�F����
//=====================================================================================================================================
CMatrix &CMatrix::LookAtLH(const CVector &vecEye, const CVector &vecAt, const CVector &vecUp){

	//�J�����̎��x�N�g��
	CVector vecX,vecY,vecZ;
	
	//���J������Z��
	//�u�����_�|���_�v�̌��ʂ𐳋K��
	vecZ = (vecAt-vecEye).Normalize();

	//���J������X��
	//�J������Z���Ə�����x�N�g���̊O�ς𐳋K��
	vecX = (vecZ.Cross(vecUp,FALSE)).Normalize();

	//���J������Y��
	//�J������X���ƃJ������Z���̊O��
	vecY = vecX.Cross(vecZ,FALSE);

	//�s��ɐ������i�[����
	this->Identity();	//�P�ʍs��쐬

	this->m_Matrix._11 = vecX.GetX();
	this->m_Matrix._21 = vecX.GetY();
	this->m_Matrix._31 = vecX.GetZ();
	this->m_Matrix._12 = vecY.GetX();
	this->m_Matrix._22 = vecY.GetY();
	this->m_Matrix._32 = vecY.GetZ();
	this->m_Matrix._13 = vecZ.GetX();
	this->m_Matrix._23 = vecZ.GetY();
	this->m_Matrix._33 = vecZ.GetZ();
	this->m_Matrix._41 = -(vecX.Dot(vecEye,FALSE));
	this->m_Matrix._42 = -(vecY.Dot(vecEye,FALSE));	
	this->m_Matrix._43 = -(vecZ.Dot(vecEye,FALSE));

	return *this;
}
//=====================================================================================================================================
//[�@�\]�F������W�n�p�̎ˉe�s��쐬
//[����]�F��1�����F����p
//		�F��2�����F�A�X�y�N�g��
//		�F��3�����F�t�����g�N���b�v����
//		�F��4�����F�o�b�N�N���b�v����
//[�߂�l]�F�Ăяo�����I�u�W�F�N�g
//[���l]�F����p�̓��W�A���P�ʂŎw��
//=====================================================================================================================================
CMatrix &CMatrix::PerspectiveFovLH(float fFov, float fAspect, float fFront, float fBack){

	//X�EY�����X�P�[�����O
	float fSx = 0.0f,fSy = 0.0f;

	fSy = (float)(1.0f/tan(fFov/2.0f));

	fSx = fSy / fAspect;
	
	this->ZeroMatrix();	//��s��쐬		
	//�e�����ɒl�̐ݒ�
	this->m_Matrix._11 = fSx;
	this->m_Matrix._22 = fSy;
	this->m_Matrix._33 = fBack/(fBack-fFront);
	this->m_Matrix._34 = 1.0f;
	this->m_Matrix._43 = -fFront*fBack/(fBack-fFront);

	return *this;
}
//======================================================================================================================================
//[�@�\]�F�r���[�|�[�g�s����쐬����
//[����]�F��1�����F�`����X���W
//		�F��2�����F�`����Y���W
//		�F��3�����F�`�悷�镝
//		�F��4�����F�`�悷�鍂��
//		�F��5�����F�[�x�̍ŏ��l
//		�F��6�����F�[�x�̍ő�l
//[�߂�l]�F�Ăяo�����Ƃ̃I�u�W�F�N�g
//[���l]�F����
//=====================================================================================================================================
CMatrix &CMatrix::Viewport(DWORD dwX, DWORD dwY, DWORD dwWidth, DWORD dwHeight, float fMinZ, float fMaxZ){
	
	this->Identity();	//�P�ʍs��쐬

	//�e�����ɒl��ݒ�
	this->m_Matrix._11 = (float)dwWidth / 2.0f;
	this->m_Matrix._22 = -(float)dwHeight / 2.0f;
	this->m_Matrix._33 = fMaxZ-fMinZ;
	this->m_Matrix._41 = (float)dwX+(float)dwWidth/2.0f;
	this->m_Matrix._42 = (float)dwY+(float)dwHeight/2.0f;
	this->m_Matrix._43 = fMinZ;

	return *this;
}