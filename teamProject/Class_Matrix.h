//多重定義防止
#ifndef __CLASS_MATRIX_H__
#define __CLASS_MATRIX_H__
#pragma once

//構造体定義
typedef struct _MATRIX
{
	//各成分を変数と配列の両方で扱えるように
	//共用体でまとめる
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

//前方宣言
class CVector;

//クラス定義
class CMatrix
{
private:
	
public:
	//４次の正方行列
	MATRIX	m_Matrix;	
	//コンストラクタ
	CMatrix( void );
	explicit CMatrix( float _11 , float _12 , float _13 , float _14 ,
		 float _21 , float _22 , float _23 , float _24 ,
		 float _31 , float _32 , float _33 , float _34 ,
		 float _41 , float _42 , float _43 , float _44 );
	//コピーコンストラクタ
	CMatrix( const CMatrix& mat );

	CMatrix( const float * lpMat );
	//デストラクタ
	~CMatrix( void );
	//行列取得
	MATRIX GetMatrix( void )const;
	float GetElement( BYTE i , BYTE j )const;
	//行列設定
	void SetMatrix( const CMatrix& mat );
	void SetElement( BYTE i , BYTE j , float fValue );
	CMatrix& ZeroMatrix( void );
	CMatrix& Identity( void );	//単位行列
	CMatrix Inverse( void );	//逆行列作成
	CMatrix Transpose(void);	//行列転置
	//平行移動行列作成
	void setTranslation(const CVector& vec);
	//拡縮行列作成
	void setScaling(const CVector& vec);
	//回転行列X作成
	void setRotationX(double rad);
	//回転行列Y作成
	void setRotationY(double rad);
	//回転行列Z作成
	void setRotationZ(double rad);
	//平行移動行列と乗算
	void Translate(const CVector &vec);
	//拡縮行列と乗算
	void Scaling(const CVector &vec);
	//X回転行列と乗算
	void RotateX(double rad);
	//Y回転行列と乗算
	void RotateY(double rad);
	//Z回転行列と乗算
	void RotateZ(double rad);
	//演算子のオーバーロード
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
	//スケーリング行列
	CMatrix &Scaling(float fScale);
	CMatrix &Scaling(float fScaleX,float fScaleY,float fScaleZ);
	//回転行列
	CMatrix &RotationX(float fAngle);
	CMatrix &RotationY(float fAngle);
	CMatrix &RotationZ(float fAngle);
	CMatrix &RotationYawPitchRoll(float fYaw,float fPitch,float fRoll);
	//平行移動行列
	CMatrix &Translation(float fTx,float fTy,float fTz);
	//ビュー行列作成（ビュートランスフォーム）
	CMatrix &LookAtLH(const CVector &vecEye,const CVector &vecAt,const CVector &vecUp);
	//射影行列作成（プロジェクショントランスフォーム）
	CMatrix &PerspectiveFovLH(float fFov,float fAspect,float fFront,float fBack);
	//ビューポート行列作成
	CMatrix &Viewport(DWORD dwX,DWORD dwY,DWORD dwWidth,DWORD dwHeight,float fMinZ,float fMaxZ);
};

#endif
