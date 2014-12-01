//警告制限
//意図的に旧型の関数を使用するために、警告を制限する
#pragma warning (disable : 4996 )
#include <windows.h>
#include "Class_Matrix.h"
#include <cmath>
#include "Class_Vector.h"

#pragma intrinsic(sin,cos)

//================================================================================
//コンストラクタ
//【機　能】
//	全成分を０で初期化する(零行列を作成)
//【引　数】
//	なし
//【備　考】
//	なし
//================================================================================
CMatrix::CMatrix( void )
{
	this->ZeroMatrix();	//零行列作成
}

//================================================================================
//コンストラクタ
//【機　能】
//	任意の値で各成分を初期化する
//【引　数】
//	1 ～ 16:各成分の値
//【備　考】
//	なし
//================================================================================
CMatrix::CMatrix( float _11 , float _12 , float _13 , float _14 ,
			  float _21 , float _22 , float _23 , float _24 , 
			  float _31 , float _32 , float _33 , float _34 ,
			  float _41 , float _42 , float _43 , float _44 )
{
	//各成分に代入
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
//コンストラクタ
//【機　能】
//	受け取った行列のコピーを作成する
//【引　数】
//	1:コピー元のCMatrixオブジェクト
//【備　考】
//	なし
//================================================================================
CMatrix::CMatrix( const CMatrix& mat )
{
	//行列をコピー
	this->m_Matrix = mat.m_Matrix;
}

//================================================================================
//コンストラクタ
//【機　能】
//	要素数16の配列から成分を初期化する
//【引　数】
//	1:float型配列のアドレス
//【備　考】
//	なし
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
//デストラクタ
//【機　能】
//	行列の成分を０にする
//【引　数】
//	なし
//【備　考】
//	なし
//================================================================================
CMatrix::~CMatrix( void )
{
	this->ZeroMatrix();
}

//================================================================================
//GetMatrix関数
//【機　能】
//	行列を取得する
//【引　数】
//	なし
//【戻り値】
//	MATRIX型のデータ
//【備　考】
//	なし
//================================================================================
MATRIX CMatrix::GetMatrix( void )const
{
	return this->m_Matrix;
}

//================================================================================
//GetElement関数
//【機　能】
//	行列の成分を取得する
//【引　数】
//	1:行要素(1～4)
//	2:列要素(1～4)
//【戻り値】
//	指定した要素の成分
//【備　考】
//	配列は0～3だが、行列の成分なので1～4で指定。
//================================================================================
float CMatrix::GetElement( BYTE i , BYTE j )const
{
	//エラーチェック
	if( i == 0 || i > 4 )	return 0.0f;
	if( j == 0 || j > 4 )	return 0.0f;
	//引数が1～4なので「-1」をして参照
	return this->m_Matrix.mat[i-1][j-1];
}

//================================================================================
//SetMatrix関数
//【機　能】
//	CMatrixオブジェクトからコピーを作成する
//【引　数】
//	コピー元のCMatrixオブジェクト
//【戻り値】
//	なし
//【備　考】
//	なし
//================================================================================
void CMatrix::SetMatrix( const CMatrix& mat )
{
	this->m_Matrix = mat.m_Matrix;
}

//================================================================================
//SetElement関数
//【機　能】
//	指定した要素の成分を設定する
//【引　数】
//	1:行要素(1～4)
//	2:列要素(1～4)
//	3:成分の値
//【戻り値】
//	なし
//【備　考】
//	行要素・列要素は1～4で指定
//================================================================================
void CMatrix::SetElement( BYTE i , BYTE j , float fValue )
{
	//エラーチェック
	if( i == 0 || i > 4 )	return;
	if( j == 0 || j > 4 )	return;
	this->m_Matrix.mat[i-1][j-1] = fValue;
}

//================================================================================
//ZeroMatrix関数
//【機　能】
//	成分が全て０の行列(零行列)を作成する
//【引　数】
//	なし
//【戻り値】
//	呼び出し元オブジェクト
//【備　考】
//	なし
//================================================================================
CMatrix& CMatrix::ZeroMatrix( void )
{
	ZeroMemory( &this->m_Matrix , sizeof( MATRIX ) );
	return *this;
}

//================================================================================
//Identity関数
//【機　能】
//	単位行列を作成する
//【引　数】
//	なし
//【戻り値】
//	呼び出し元オブジェクト
//【備　考】
//	なし
//================================================================================
CMatrix& CMatrix::Identity( void )
{
	//０で初期化
	this->ZeroMatrix();
	//対角成分に1を設定
	this->m_Matrix._11 = 1.0f;
	this->m_Matrix._22 = 1.0f;
	this->m_Matrix._33 = 1.0f;
	this->m_Matrix._44 = 1.0f;
	return *this;
}

//================================================================================
//Inverse関数
//【機　能】
//	逆行列を作成する
//【引　数】
//	なし
//【戻り値】
//	逆行列
//【備　考】
//	呼び出し元オブジェクトは逆行列にならない
//================================================================================
CMatrix CMatrix::Inverse( void )
{
	//行列式を求める
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
	//行列式の値が０の場合逆行列は存在しない
	if( !fDet )	return *this;

	//各成分を求める
	MATRIX	mat = {0.0f};	//逆行列用
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

	CMatrix	matInverse;		//逆行列用
	matInverse.m_Matrix = mat;	//逆行列をコピー
	//逆行列を返す
	return matInverse;
	//※自身のメンバを逆行列で書き換えないよう注意
}
//================================================================================
//[機能]
//行列を転置する
//[引数]
//無し
//[戻り値]
//転置した行列
//[備考]
//DirectXとOpenGLでは座標系が違う為（左手座標系と右手座標系での行列転置）
//================================================================================
CMatrix CMatrix::Transpose(void)
{
	int i = 0,j = 0;
	CMatrix matTranspose;	//転置用

	matTranspose.Identity(); //正規化
	
	for(i = 0;i < 4;i++)
	{
		for(j = 0;j < 4;j++)
		{
			matTranspose.m_Matrix.mat[i][j] = this->m_Matrix.mat[j][i];	//転置
		}
	}
	//転置した行列を返す
	return matTranspose;
}
//================================================================================
//[機能]：平行移動行列生成
//[引数]：ベクトル
//[戻り値]：無し
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
//[機能]：拡縮行列生成
//[引数]：ベクトル
//[戻り値]：無し
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
//[機能]：回転行列X生成
//[引数]：ラジアン
//[戻り値]：無し
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
//[機能]：回転行列Y生成
//[引数]：ラジアン
//[戻り値]：無し
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
//[機能]：回転行列Z生成
//[引数]：ラジアン
//[戻り値]：無し
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
//[機能]：平行移動行列と乗算
//[引数]：ベクトル
//[戻り値]：無し
//================================================================================
void CMatrix::Translate(const CVector &vec)
{
	m_Matrix._14 += m_Matrix._11 * vec.GetX() + m_Matrix._12 * vec.GetY() + m_Matrix._13 * vec.GetZ();
	m_Matrix._24 += m_Matrix._21 * vec.GetX() + m_Matrix._22 * vec.GetY() + m_Matrix._23 * vec.GetZ();
	m_Matrix._34 += m_Matrix._31 * vec.GetX() + m_Matrix._32 * vec.GetY() + m_Matrix._33 * vec.GetZ();

}
//================================================================================
//[機能]：拡縮行列と乗算
//[引数]：ベクトル
//[戻り値]：無し
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
//[機能]：X回転行列と乗算
//[引数]：ラジアン
//[戻り値]：無し
//================================================================================
void CMatrix::RotateX(double rad)
{
	double s = sin(rad);
	double c = cos(rad);
	double t;
	
	//1行目
	t = c * m_Matrix._12 + s * m_Matrix._13;
	m_Matrix._13 = (float)(-s * m_Matrix._12 + c * m_Matrix._13);
	m_Matrix._12 = (float)t;
	//2行目
	t = c * m_Matrix._22 + s * m_Matrix._23;
	m_Matrix._23 = (float)(-s * m_Matrix._22 + c * m_Matrix._23);
	m_Matrix._22 = (float)t;
	//3行目
	t = c * m_Matrix._32 + s * m_Matrix._33;
	m_Matrix._33 = (float)(-s * m_Matrix._32 + c * m_Matrix._33);
	m_Matrix._32 = (float)t;
}
//================================================================================
//[機能]：Y回転行列と乗算
//[引数]：ラジアン
//[戻り値]：無し
//================================================================================
void CMatrix::RotateY(double rad)
{
	double s = sin(rad);
	double c = cos(rad);
	double t;
	
	//1行目
	t = c * m_Matrix._11 - s * m_Matrix._13;
	m_Matrix._13 = (float)(s * m_Matrix._11 + c * m_Matrix._13);
	m_Matrix._11 = (float)t;
	//2行目
	t = c * m_Matrix._21 - s * m_Matrix._23;
	m_Matrix._23 = (float)(s * m_Matrix._21 + c * m_Matrix._23);
	m_Matrix._21 = (float)t;
	//3行目
	t = c * m_Matrix._31 - s * m_Matrix._33;
	m_Matrix._33 = (float)(s * m_Matrix._31 + c * m_Matrix._33);
	m_Matrix._31 = (float)t;
}

//================================================================================
//[機能]：Z回転行列と乗算
//[引数]：ラジアン
//[戻り値]：無し
//================================================================================
void CMatrix::RotateZ(double rad)
{
	double s = sin(rad);
	double c = cos(rad);
	double t;
	
	//1行目
	t = c * m_Matrix._11 + s * m_Matrix._12;
	m_Matrix._12 = (float)(-s * m_Matrix._11 + c * m_Matrix._12);
	m_Matrix._11 = (float)t;
	//2行目
	t = c * m_Matrix._21 + s * m_Matrix._22;
	m_Matrix._22 = (float)(-s * m_Matrix._21 + c * m_Matrix._22);
	m_Matrix._21 = (float)t;
	//3行目
	t = c * m_Matrix._31 + s * m_Matrix._32;
	m_Matrix._32 = (float)(-s * m_Matrix._31 + c * m_Matrix._32);
	m_Matrix._31 = (float)t;
}

//================================================================================
//「=」オーバーロード
//【機　能】
//	行列を左辺へ代入する
//【引　数】
//	1:代入対象のCMatrixオブジェクト
//【戻り値】
//	呼び出し元オブジェクト
//【備　考】
//	なし
//================================================================================
CMatrix& CMatrix::operator =( const CMatrix& mat )
{
	this->m_Matrix = mat.m_Matrix;
	return *this;
}

//================================================================================
//「+」オーバーロード
//【機　能】
//	行列を加算する
//【引　数】
//	加算対象のCMatrixオブジェクト
//【戻り値】
//	計算結果のオブジェクト
//【備　考】
//	なし
//================================================================================
CMatrix  CMatrix::operator +( const CMatrix& mat )const
{
	CMatrix	mat_copy;	//計算用
	int		i = 0 , j = 0;
	//呼び出し元の行列をコピー
	mat_copy.SetMatrix( *this );
	for( i = 0 ; i < 4 ; i++ ){
		for( j = 0 ; j < 4 ; j++ ){
			mat_copy.m_Matrix.mat[i][j] += mat.m_Matrix.mat[i][j];
		}
	}
	return mat_copy;
}

//================================================================================
//「-」オーバーロード
//【機　能】
//	行列を減算する
//【引　数】
//	減算対象のCMatrixオブジェクト
//【戻り値】
//	計算結果のオブジェクト
//【備　考】
//	なし
//================================================================================
CMatrix  CMatrix::operator -( const CMatrix& mat )const
{
	CMatrix	mat_copy;	//計算用
	int		i = 0 , j = 0;
	//呼び出し元の行列をコピー
	mat_copy.SetMatrix( *this );
	for( i = 0 ; i < 4 ; i++ ){
		for( j = 0 ; j < 4 ; j++ ){
			mat_copy.m_Matrix.mat[i][j] -= mat.m_Matrix.mat[i][j];
		}
	}
	return mat_copy;
}

//================================================================================
//「*」オーバーロード
//【機　能】
//	行列を乗算する
//【引　数】
//	乗算対象のCMatrixオブジェクト
//【戻り値】
//	計算結果のオブジェクト
//【備　考】
//	なし
//================================================================================
CMatrix  CMatrix::operator *( const CMatrix& mat )const
{
	CMatrix	mat_copy;	//計算用
	int		i = 0 , j = 0;
	//呼び出し元の行列をコピー
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
//「*」オーバーロード
//【機　能】
//	行列を実数倍する
//【引　数】
//	実数倍する値
//【戻り値】
//	計算結果のオブジェクト
//【備　考】
//	なし
//================================================================================
CMatrix  CMatrix::operator *( const float fValue )const
{
	CMatrix	mat_copy;	//計算用
	int		i = 0 , j = 0;
	//呼び出し元の行列をコピー
	mat_copy.SetMatrix( *this );
	for( i = 0 ; i < 4 ; i++ ){
		for( j = 0 ; j < 4 ; j++ ){
			mat_copy.m_Matrix.mat[i][j] *= fValue;
		}
	}
	return mat_copy;
}

//================================================================================
//「/」オーバーロード
//【機　能】
//	行列を実数で除算する
//【引　数】
//	除算する値
//【戻り値】
//	計算結果のオブジェクト
//【備　考】
//	なし
//================================================================================
CMatrix  CMatrix::operator /( const float fValue )const
{
	CMatrix	mat_copy;	//計算用
	int		i = 0 , j = 0;
	//呼び出し元の行列をコピー
	mat_copy.SetMatrix( *this );
	//０除算チェック
	if( fValue == 0 )	return mat_copy;
	for( i = 0 ; i < 4 ; i++ ){
		for( j = 0 ; j < 4 ; j++ ){
			mat_copy.m_Matrix.mat[i][j] /= fValue;
		}
	}
	return mat_copy;
}

//================================================================================
//「+=」オーバーロード
//【機　能】
//	行列の加算を行い結果を左辺へ代入する
//【引　数】
//	加算対象のCMatrixオブジェクト
//【戻り値】
//	計算結果の左辺オブジェクト
//【備　考】
//	なし
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
//「-=」オーバーロード
//【機　能】
//	行列の減算を行い結果を左辺へ代入する
//【引　数】
//	減算対象のCMatrixオブジェクト
//【戻り値】
//	計算結果の左辺オブジェクト
//【備　考】
//	なし
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
//「*=」オーバーロード
//【機　能】
//	行列の乗算を行い結果を左辺へ代入する
//【引　数】
//	乗算対象のCMatrixオブジェクト
//【戻り値】
//	計算結果の左辺オブジェクト
//【備　考】
//	なし
//================================================================================
CMatrix& CMatrix::operator *=( const CMatrix& mat )
{
	int	i = 0 , j = 0;
	CMatrix	mat_copy;	//計算用
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
//「*=」オーバーロード
//【機　能】
//	行列を実数で乗算し、結果を左辺へ代入する
//【引　数】
//	実数倍の値
//【戻り値】
//	計算結果の左辺オブジェクト
//【備　考】
//	なし
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
//「/=」オーバーロード
//【機　能】
//	行列を実数で除算し、結果を左辺へ代入する
//【引　数】
//	除算する値
//【戻り値】
//	計算結果の左辺オブジェクト
//【備　考】
//	なし
//================================================================================
CMatrix& CMatrix::operator /=( const float fValue )
{
	int	i = 0 , j = 0;
	//０除算チェック
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
//Scaling関数
//[機能]：スケーリング行列を作成する
//[引数]：スケーリング倍率
//[戻り値]：呼び出し元オブジェクト
//[備考]：全方向を同じ倍率でスケーリングする
//====================================================================================================================================
CMatrix &CMatrix::Scaling(float fScale){
	
	this->Identity();	//単位行列作成

	//各成分に倍率を格納
	this->m_Matrix._11 = fScale;
	this->m_Matrix._22 = fScale;
	this->m_Matrix._33 = fScale;


	return *this;
}
//===================================================================================================================================
//Scaling関数
//[機能]：スケーリング行列を作成する
//[引数]1：X方向倍率
//		2：Y方向倍率
//		3：Z方向倍率
//[戻り値]：呼び出し元オブジェクト
//[備考]：全方向を同じ倍率でスケーリングする
//====================================================================================================================================
CMatrix &CMatrix::Scaling(float fScaleX, float fScaleY, float fScaleZ){
	
	this->Identity();	//単位行列作成

	//各成分に倍率を格納
	this->m_Matrix._11 = fScaleX;
	this->m_Matrix._22 = fScaleY;
	this->m_Matrix._33 = fScaleZ;


	return *this;
}
//=====================================================================================================================================
//RotationX関数
//[機能]：X軸基準の回転行列を作成する
//[引数]1：回転角度
//[戻り値]：呼び出し元オブジェクト
//[備考]：角度はラジアンで指定
//====================================================================================================================================
CMatrix &CMatrix::RotationX(float fAngle){

	this->Identity();	//単位行列作成

	//対応する成分に三角関数の値を格納

	this->m_Matrix._22 = (float)cos(fAngle);
	this->m_Matrix._23 = (float)sin(fAngle);
	this->m_Matrix._32 = -(float)sin(fAngle);
	this->m_Matrix._33 = (float)cos(fAngle);

	return *this;

}
//=====================================================================================================================================
//RotationY関数
//[機能]：Y軸基準の回転行列を作成する
//[引数]1：回転角度
//[戻り値]：呼び出し元オブジェクト
//[備考]：角度はラジアンで指定
//====================================================================================================================================
CMatrix &CMatrix::RotationY(float fAngle){
	
	this->Identity();	//単位行列作成

	//対応する成分に三角関数の値を指定
	this->m_Matrix._11 = (float)cos(fAngle);
	this->m_Matrix._13 = -(float)sin(fAngle);
	this->m_Matrix._31 = (float)sin(fAngle);
	this->m_Matrix._33 = (float)cos(fAngle);

	return *this;

}
//=====================================================================================================================================
//RotationZ関数
//[機能]：Z軸基準の回転行列を作成する
//[引数]1：回転角度
//[戻り値]：呼び出し元オブジェクト
//[備考]：角度はラジアンで指定
//====================================================================================================================================
CMatrix &CMatrix::RotationZ(float fAngle){
	
	this->Identity();	//単位行列作成

	//対応する成分に三角関数の値を代入
	this->m_Matrix._11 = (float)cos(fAngle);
	this->m_Matrix._12 = (float)sin(fAngle);
	this->m_Matrix._21 = -(float)sin(fAngle);
	this->m_Matrix._22 = (float)cos(fAngle);

	
	return *this;
}
//====================================================================================================================================
//[機能]：ヨーピッチロール回転行列を作成する
//[引数]：1：ヨー回転（Y軸回転）
//		：2：ピッチ回転（X軸回転）
//		：3：ロール回転（Z軸回転）
//[戻り値]：呼び出し元オブジェクト
//[備考]：角度はラジアンで指定
//=====================================================================================================================================
CMatrix &CMatrix::RotationYawPitchRoll(float fYaw, float fPitch, float fRoll){
	
	CMatrix matRotX,matRotY,matRotZ;

	//各軸の回転行列を作成
	matRotX.RotationX(fPitch);
	matRotY.RotationY(fYaw);
	matRotZ.RotationZ(fRoll);

	this->Identity();	//単位行列作成
	//Z,X,Yの順で行列の積を求める
	*this = matRotZ * matRotX * matRotY;

	return *this;

}
//=====================================================================================================================================
//[機能]：平行移動行列を作成する
//[引数]：1：X方向の移動量
//		：2：Y方向の移動量
//		：3：Z方向の移動量
//[戻り値]：呼び出し元のオブジェクト
//[備考]：無し
//=====================================================================================================================================
CMatrix &CMatrix::Translation(float fTx, float fTy, float fTz){
	
	this->Identity();	//単位行列作成
	//対応する成分に移動量を格納
	this->m_Matrix._41 = fTx;
	this->m_Matrix._42 = fTy;
	this->m_Matrix._43 = fTz;
	return *this;
}
//=====================================================================================================================================
//[機能]：左手座標系用のビュー行列を作成する
//[引数]：第1引数：カメラの位置ベクトル
//		：第2引数：カメラの注視点ベクトル
//		：第3引数：上向きベクトル
//[戻り値]：呼び出し元オブジェクト
//[備考]：無し
//=====================================================================================================================================
CMatrix &CMatrix::LookAtLH(const CVector &vecEye, const CVector &vecAt, const CVector &vecUp){

	//カメラの軸ベクトル
	CVector vecX,vecY,vecZ;
	
	//▼カメラのZ軸
	//「注視点－視点」の結果を正規化
	vecZ = (vecAt-vecEye).Normalize();

	//▼カメラのX軸
	//カメラのZ軸と上向きベクトルの外積を正規化
	vecX = (vecZ.Cross(vecUp,FALSE)).Normalize();

	//▼カメラのY軸
	//カメラのX軸とカメラのZ軸の外積
	vecY = vecX.Cross(vecZ,FALSE);

	//行列に成分を格納する
	this->Identity();	//単位行列作成

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
//[機能]：左手座標系用の射影行列作成
//[引数]：第1引数：視野角
//		：第2引数：アスペクト比
//		：第3引数：フロントクリップ平面
//		：第4引数：バッククリップ平面
//[戻り値]：呼び出し元オブジェクト
//[備考]：視野角はラジアン単位で指定
//=====================================================================================================================================
CMatrix &CMatrix::PerspectiveFovLH(float fFov, float fAspect, float fFront, float fBack){

	//X・Y方向スケーリング
	float fSx = 0.0f,fSy = 0.0f;

	fSy = (float)(1.0f/tan(fFov/2.0f));

	fSx = fSy / fAspect;
	
	this->ZeroMatrix();	//零行列作成		
	//各成分に値の設定
	this->m_Matrix._11 = fSx;
	this->m_Matrix._22 = fSy;
	this->m_Matrix._33 = fBack/(fBack-fFront);
	this->m_Matrix._34 = 1.0f;
	this->m_Matrix._43 = -fFront*fBack/(fBack-fFront);

	return *this;
}
//======================================================================================================================================
//[機能]：ビューポート行列を作成する
//[引数]：第1引数：描画先のX座標
//		：第2引数：描画先のY座標
//		：第3引数：描画する幅
//		：第4引数：描画する高さ
//		：第5引数：深度の最小値
//		：第6引数：深度の最大値
//[戻り値]：呼び出しもとのオブジェクト
//[備考]：無し
//=====================================================================================================================================
CMatrix &CMatrix::Viewport(DWORD dwX, DWORD dwY, DWORD dwWidth, DWORD dwHeight, float fMinZ, float fMaxZ){
	
	this->Identity();	//単位行列作成

	//各成分に値を設定
	this->m_Matrix._11 = (float)dwWidth / 2.0f;
	this->m_Matrix._22 = -(float)dwHeight / 2.0f;
	this->m_Matrix._33 = fMaxZ-fMinZ;
	this->m_Matrix._41 = (float)dwX+(float)dwWidth/2.0f;
	this->m_Matrix._42 = (float)dwY+(float)dwHeight/2.0f;
	this->m_Matrix._43 = fMinZ;

	return *this;
}