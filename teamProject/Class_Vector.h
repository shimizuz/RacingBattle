//================================================================================
//多重定義防止
//================================================================================
#ifndef __CLASS_VECTOR_H__
#define __CLASS_VECTOR_H__
#pragma once

//ヘッダーファイル
#include <windows.h>

//================================================================================
//構造体定義
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

//前方宣言
class CMatrix;

//================================================================================
//クラス定義
//================================================================================
class CVector
{
private:
	
public:
	//メンバ変数
	VECTOR	m_Vector;
	//コンストラクタ
	CVector( void );
	explicit CVector( float fx , float fy , float fz );
	//コピーコンストラクタ
	CVector( const CVector &vec );
	//デストラクタ
	~CVector( void );
	//ベクトル取得
	float GetX( void )const;
	float GetY( void )const;
	float GetZ( void )const;
	float GetW( void )const;
	VECTOR GetVector( void )const;
	//ベクトル設定
	void SetX( const float fx );
	void SetY( const float fy );
	void SetZ( const float fz );
	void SetW( const float fw );
	void SetValue( float fx , float fy , float fz );
	//零ベクトル
	CVector &ZeroVector( void );
	//逆ベクトル
	CVector Inverse( void )const;
	//ベクトルの長さ
	float Length( BOOL bSquare = FALSE )const;
	//ベクトルの正規化
	CVector Normalize( void )const;
	//ベクトルの内積
	float Dot( const CVector &vec , BOOL bNormalize )const;
	//ベクトルの外積
	CVector Cross( const CVector &vec )const;
	//ベクトルのなす角
	float InnerProductAngle( const CVector &vec )const;
	//行列との合成
	CVector &TransformMatrix( const CMatrix &mat );
	//演算子のオーバーロード
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
