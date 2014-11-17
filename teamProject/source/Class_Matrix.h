//���d��`�h�~
#ifndef __CLASS_MATRIX_H__
#define __CLASS_MATRIX_H__
#pragma once

//�\���̒�`
typedef struct _MATRIX
{
	//�e������ϐ��Ɣz��̗����ň�����悤��
	//���p�̂ł܂Ƃ߂�
	union
	{
		struct
		{
			float	_11 , _12 , _13 , _14;
			float	_21 , _22 , _23 , _24;
			float	_31 , _32 , _33 , _34;
			float	_41 , _42 , _43 , _44;
		};
		float	mat[ 4 ][ 4 ];
	};
}MATRIX , *LPMATRIX;

//�O���錾
class CVector;

//�N���X��`
class CMatrix
{
private:
	
public:
	//�S���̐����s��
	MATRIX	m_Matrix;	
	//�R���X�g���N�^
	CMatrix( void );
	explicit CMatrix( float _11 , float _12 , float _13 , float _14 ,
		 float _21 , float _22 , float _23 , float _24 ,
		 float _31 , float _32 , float _33 , float _34 ,
		 float _41 , float _42 , float _43 , float _44 );
	//�R�s�[�R���X�g���N�^
	CMatrix( const CMatrix& mat );

	CMatrix( const float * lpMat );
	//�f�X�g���N�^
	~CMatrix( void );
	//�s��擾
	MATRIX GetMatrix( void )const;
	float GetElement( BYTE i , BYTE j )const;
	//�s��ݒ�
	void SetMatrix( const CMatrix& mat );
	void SetElement( BYTE i , BYTE j , float fValue );
	CMatrix& ZeroMatrix( void );
	CMatrix& Identity( void );	//�P�ʍs��
	CMatrix Inverse( void );	//�t�s��쐬
	CMatrix Transpose(void);	//�s��]�u
	//���s�ړ��s��쐬
	void setTranslation(const CVector& vec);
	//�g�k�s��쐬
	void setScaling(const CVector& vec);
	//��]�s��X�쐬
	void setRotationX(double rad);
	//��]�s��Y�쐬
	void setRotationY(double rad);
	//��]�s��Z�쐬
	void setRotationZ(double rad);
	//���s�ړ��s��Ə�Z
	void Translate(const CVector &vec);
	//�g�k�s��Ə�Z
	void Scaling(const CVector &vec);
	//X��]�s��Ə�Z
	void RotateX(double rad);
	//Y��]�s��Ə�Z
	void RotateY(double rad);
	//Z��]�s��Ə�Z
	void RotateZ(double rad);
	//���Z�q�̃I�[�o�[���[�h
	CMatrix& operator =( const CMatrix& mat );
	CMatrix  operator +( const CMatrix& mat )const;
	CMatrix  operator -( const CMatrix& mat )const;
	CMatrix  operator *( const CMatrix& mat )const;
	CMatrix  operator *( const float fValue )const;
	CMatrix  operator /( const float fValue )const;
	CMatrix& operator +=( const CMatrix& mat );
	CMatrix& operator -=( const CMatrix& mat );
	CMatrix& operator *=( const CMatrix& mat );
	CMatrix& operator *=( const float fValue );
	CMatrix& operator /=( const float fValue );
	//�X�P�[�����O�s��
	CMatrix &Scaling(float fScale);
	CMatrix &Scaling(float fScaleX,float fScaleY,float fScaleZ);
	//��]�s��
	CMatrix &RotationX(float fAngle);
	CMatrix &RotationY(float fAngle);
	CMatrix &RotationZ(float fAngle);
	CMatrix &RotationYawPitchRoll(float fYaw,float fPitch,float fRoll);
	//���s�ړ��s��
	CMatrix &Translation(float fTx,float fTy,float fTz);
	//�r���[�s��쐬�i�r���[�g�����X�t�H�[���j
	CMatrix &LookAtLH(const CVector &vecEye,const CVector &vecAt,const CVector &vecUp);
	//�ˉe�s��쐬�i�v���W�F�N�V�����g�����X�t�H�[���j
	CMatrix &PerspectiveFovLH(float fFov,float fAspect,float fFront,float fBack);
	//�r���[�|�[�g�s��쐬
	CMatrix &Viewport(DWORD dwX,DWORD dwY,DWORD dwWidth,DWORD dwHeight,float fMinZ,float fMaxZ);
};

#endif
