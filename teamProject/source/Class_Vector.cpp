//================================================================================
//警告制限
//================================================================================
//意図的に旧型の関数を使用するために、警告を制限する
#pragma warning (disable : 4996 )
#include <windows.h>
#include <cmath>
#include "Class_Matrix.h"
#include "Class_Vector.h"

//計算速度上昇
#pragma intrinsic(sqrt,pow,sin,cos,tan,asin,acos,atan)

//================================================================================
//コンストラクタ
//【機　能】
//	ベクトルの成分を０で初期化する
//【引　数】
//	なし
//【備　考】
//	w成分はデフォルトで1.0にしておく
//================================================================================
CVector::CVector( void )
{
	this->ZeroVector();	//零ベクトル作成
	//wは「1.0」で固定
	this->m_Vector.w = 1.0f;
}

//================================================================================
//コンストラクタ
//【機　能】
//	任意の値で各成分を初期化する
//【引　数】
//	１：Ｘ成分
//	２：Ｙ成分
//	３：Ｚ成分
//【備　考】
//	なし
//================================================================================
CVector::CVector( float fx , float fy , float fz )
{
	this->m_Vector.x = fx;
	this->m_Vector.y = fy;
	this->m_Vector.z = fz;
	this->m_Vector.w = 1.0f;	//「1.0」で固定
}

//================================================================================
//コピーコンストラクタ
//【機　能】
//	受け取ったベクトルのコピーを作成する
//【引　数】
//	１：コピー元のCVectorオブジェクト
//【備　考】
//	なし
//================================================================================
CVector::CVector( const CVector &vec )
{
	this->m_Vector = vec.m_Vector;
}

//================================================================================
//デストラクタ
//【機　能】
//	ベクトルの成分を０で初期化する
//【引　数】
//	なし
//【備　考】
//	なし
//================================================================================
CVector::~CVector( void )
{
	this->ZeroVector();
}

//================================================================================
//GetX関数
//【機　能】
//	ベクトルのＸ成分を取得する
//【引　数】
//	なし
//【戻り値】
//	Ｘ成分
//【備　考】
//	なし
//================================================================================
float CVector::GetX( void )const
{
	return this->m_Vector.x;
}

//================================================================================
//GetY関数
//【機　能】
//	ベクトルのＹ成分を取得する
//【引　数】
//	なし
//【戻り値】
//	Ｙ成分
//【備　考】
//	なし
//================================================================================
float CVector::GetY( void )const
{
	return this->m_Vector.y;
}

//================================================================================
//GetZ関数
//【機　能】
//	ベクトルのＺ成分を取得する
//【引　数】
//	なし
//【戻り値】
//	Ｚ成分
//【備　考】
//	なし
//================================================================================
float CVector::GetZ( void )const
{
	return this->m_Vector.z;
}

//================================================================================
//GetW関数
//【機　能】
//	ベクトルのＷ成分を取得する
//【引　数】
//	なし
//【戻り値】
//	Ｗ成分
//【備　考】
//	なし
//================================================================================
float CVector::GetW( void )const
{
	return this->m_Vector.w;
}

//================================================================================
//GetVector関数
//【機　能】
//	ベクトルを取得する
//【引　数】
//	なし
//【戻り値】
//	VECTOR型のデータ
//【備　考】
//	なし
//================================================================================
VECTOR CVector::GetVector( void )const
{
	return this->m_Vector;
}

//================================================================================
//SetX関数
//【機　能】
//	ベクトルのＸ成分を設定する
//【引　数】
//	１：Ｘ成分の値
//【戻り値】
//	なし
//【備　考】
//	なし
//================================================================================
void CVector::SetX( float fx )
{
	this->m_Vector.x = fx;
}

//================================================================================
//SetY関数
//【機　能】
//	ベクトルのＹ成分を設定する
//【引　数】
//	１：Ｙ成分の値
//【戻り値】
//	なし
//【備　考】
//	なし
//================================================================================
void CVector::SetY( float fy )
{
	this->m_Vector.y = fy;
}

//================================================================================
//SetZ関数
//【機　能】
//	ベクトルのＺ成分を設定する
//【引　数】
//	１：Ｚ成分の値
//【戻り値】
//	なし
//【備　考】
//	なし
//================================================================================
void CVector::SetZ( float fz )
{
	this->m_Vector.z = fz;
}

//================================================================================
//SetW関数
//【機　能】
//	ベクトルのＷ成分を設定する
//【引　数】
//	１：Ｗ成分の値
//【戻り値】
//	なし
//【備　考】
//	なし
//================================================================================
void CVector::SetW( float fw )
{
	this->m_Vector.w = fw;
}

//================================================================================
//SetValue関数
//【機　能】
//	ベクトルの各成分を設定する
//【引　数】
//	１：Ｘ成分の値
//	２：Ｙ成分の値
//	３：Ｚ成分の値
//【戻り値】
//	なし
//【備　考】
//	なし
//================================================================================
void CVector::SetValue( float fx , float fy , float fz )
{
	this->m_Vector.x = fx;
	this->m_Vector.y = fy;
	this->m_Vector.z = fz;
	//wは「1.0」で固定
	this->m_Vector.w = 1.0f;
}

//================================================================================
//ZeroVector関数
//【機　能】
//	零ベクトルを作成する
//【引　数】
//	なし
//【戻り値】
//	呼び出し元オブジェクト
//【備　考】
//	なし
//================================================================================
CVector &CVector::ZeroVector( void )
{
	ZeroMemory( &this->m_Vector , sizeof( VECTOR ) );
	return *this;
}

//================================================================================
//Inverse関数
//【機　能】
//	逆ベクトルを作成する
//【引　数】
//	なし
//【戻り値】
//	逆ベクトル
//【備　考】
//	呼び出し元のベクトルは変化しない
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
//Length関数
//【機　能】
//	ベクトルの長さを求める
//【引　数】
//	１：２乗フラグ(デフォルト:FALSE[２乗しない])
//【戻り値】
//	ベクトルの長さ
//【備　考】
//	なし
//================================================================================
float CVector::Length( BOOL bSquare )const
{
	float		fLength = 0.0f;
	fLength =	(this->m_Vector.x * this->m_Vector.x) +
			(this->m_Vector.y * this->m_Vector.y) + 
			(this->m_Vector.z * this->m_Vector.z);
	if( bSquare == TRUE ){	//２乗する
		return fLength;
	}
	//２乗しない(平方根で返す)
	return (float)sqrt( (double)fLength );
}

//================================================================================
//Normalize関数
//【機　能】
//	ベクトルを正規化する
//【引　数】
//	なし
//【戻り値】
//	正規化されたベクトル
//【備　考】
//	なし
//================================================================================
CVector CVector::Normalize( void )const
{
	CVector	vecNormalize;
	float	fLength = this->Length();
	//各成分をベクトルの長さで割る
	vecNormalize.m_Vector.x = this->m_Vector.x / fLength;
	vecNormalize.m_Vector.y = this->m_Vector.y / fLength;
	vecNormalize.m_Vector.z = this->m_Vector.z / fLength;
	return vecNormalize;
}

//================================================================================
//Dot関数
//【機　能】
//	ベクトルの内積を求める
//【引　数】
//	１：内積を求める対象のベクトル
//	２：正規化フラグ
//		(TRUE:正規化する , FALSE:正規化しない)
//【戻り値】
//	内積の値
//【備　考】
//	なし
//================================================================================
float CVector::Dot( const CVector &vec , BOOL bNormalize )const
{
	CVector	vec_copy1 , vec_copy2;	//計算用
	float	fDot = 0.0f;				//内積値

	//ベクトルを計算用にコピー
	vec_copy1 = *this;
	vec_copy2 = vec;
	if( bNormalize ){	//正規化
		vec_copy1 = vec_copy1.Normalize();
		vec_copy2 = vec_copy2.Normalize();
	}
	fDot =	(vec_copy1.m_Vector.x * vec_copy2.m_Vector.x) +
			(vec_copy1.m_Vector.y * vec_copy2.m_Vector.y) +
			(vec_copy1.m_Vector.z * vec_copy2.m_Vector.z);
	return fDot;
}

//================================================================================
//Cross関数
//【機　能】
//	ベクトルの外積を求める
//【引　数】
//	外積を求める対象のベクトル
//【戻り値】
//	法線ベクトル
//【備　考】
//	DirectX使用（左手座標系）　OpenGLならそのまま（右手座標系）
//================================================================================
CVector CVector::Cross( const CVector &vec ,BOOL flag )const
{
	CVector	vecCross;	//法線ベクトル
	
	vecCross.m_Vector.x =	(this->m_Vector.y * vec.m_Vector.z) - 
							(this->m_Vector.z * vec.m_Vector.y);
	vecCross.m_Vector.y =	(this->m_Vector.z * vec.m_Vector.x) - 
							(this->m_Vector.x * vec.m_Vector.z);
	vecCross.m_Vector.z =	(this->m_Vector.x * vec.m_Vector.y) - 
							(this->m_Vector.y * vec.m_Vector.x);

	//戻り値は左手座標用に
	//逆ベクトルにして返す
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
//InnerProductAngle関数
//【機　能】
//	ベクトルのなす角を求める
//【引　数】
//	角度を求める対象のベクトル
//【戻り値】
//	ベクトルのなす角度(ラジアン)
//【備　考】
//	戻り値の角度はラジアン単位
//================================================================================
float CVector::InnerProductAngle( const CVector &vec )const
{
	float	fAngle = 0.0f;

	//内積(正規化の有無は関係ない)
	float	fDot = this->Dot( vec , FALSE );
	fAngle = (float)acos( fDot / (this->Length()*vec.Length()) );
	return fAngle;
}

//================================================================================
//TransformMatrix関数
//【機　能】
//	ベクトルを行列で変換する
//【引　数】
//	１：計算対象の行列
//【戻り値】
//	呼び出し元オブジェクト
//【備　考】
//	なし
//================================================================================
CVector &CVector::TransformMatrix( const CMatrix &mat )
{
	CVector	vec_copy;	//計算用
	MATRIX	mat_copy;

	mat_copy = mat.GetMatrix();

	//ベクトルの成分と行列を乗算する
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
	//各成分をw成分で割る
	vec_copy /= vec_copy.m_Vector.w;
	//w成分自身も割る
	vec_copy.m_Vector.w /= vec_copy.m_Vector.w;
	//自身のオブジェクトにコピー
	*this = vec_copy;

	return *this;
}

//================================================================================
//「=」のオーバーロード
//【機　能】
//	ベクトルの成分をコピーする
//【引　数】
//	１：コピー元のベクトル
//【戻り値】
//	呼び出し元のオブジェクト
//【備　考】
//	なし
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
//「+」のオーバーロード
//【機　能】
//	ベクトルの成分を加算する
//【引　数】
//	計算対象のベクトル
//【戻り値】
//	計算結果のベクトル
//【備　考】
//	なし
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
//「-」のオーバーロード
//【機　能】
//	ベクトルの成分を減算する
//【引　数】
//	１：計算対象のベクトル
//【戻り値】
//	計算結果のベクトル
//【備　考】
//	なし
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
//「*」のオーバーロード
//【機　能】
//	ベクトルの成分を実数倍する
//【引　数】
//	実数倍する値
//【戻り値】
//	計算結果のベクトル
//【備　考】
//	なし
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
//「*」のオーバーロード
//【機　能】
//	ベクトルを行列で変換する
//【引　数】
//	計算対象の行列
//【戻り値】
//	計算結果のベクトル
//【備　考】
//	なし
//================================================================================
CVector CVector::operator *( const CMatrix &mat )const
{
	CVector	vec_copy = *this;
	vec_copy.TransformMatrix( mat );
	return vec_copy;
}

//================================================================================
//「/」のオーバーロード
//【機　能】
//	ベクトルの成分を実数で除算する
//【引　数】
//	除算する値
//【戻り値】
//	計算結果のベクトル
//【備　考】
//	なし
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
//「+=」のオーバーロード
//【機　能】
//	ベクトルの加算を行い結果を左辺へ代入する
//【引　数】
//	計算対象のベクトル
//【戻り値】
//	呼び出し元オブジェクト
//【備　考】
//	なし
//================================================================================
CVector& CVector::operator +=( const CVector &vec )
{
	this->m_Vector.x += vec.m_Vector.x;
	this->m_Vector.y += vec.m_Vector.y;
	this->m_Vector.z += vec.m_Vector.z;
	return *this;
}

//================================================================================
//「-=」のオーバーロード
//【機　能】
//	ベクトルの減算を行い結果を左辺へ代入する
//【引　数】
//	計算対象のベクトル
//【戻り値】
//	呼び出し元オブジェクト
//【備　考】
//	なし
//================================================================================
CVector& CVector::operator -=( const CVector &vec )
{
	this->m_Vector.x -= vec.m_Vector.x;
	this->m_Vector.y -= vec.m_Vector.y;
	this->m_Vector.z -= vec.m_Vector.z;
	return *this;
}

//================================================================================
//「*=」のオーバーロード
//【機　能】
//	ベクトルの実数倍を行い結果を左辺へ代入する
//【引　数】
//	実数倍する値
//【戻り値】
//	呼び出し元オブジェクト
//【備　考】
//	なし
//================================================================================
CVector& CVector::operator *=( const float fValue )
{
	this->m_Vector.x *= fValue;
	this->m_Vector.y *= fValue;
	this->m_Vector.z *= fValue;
	return *this;
}

//================================================================================
//「*=」のオーバーロード
//【機　能】
//	ベクトルを行列で変換し、結果を左辺へコピーする
//【引　数】
//	計算対象の行列
//【戻り値】
//	呼び出し元オブジェクト
//【備　考】
//	なし
//================================================================================
CVector& CVector::operator *=( const CMatrix &mat )
{
	this->TransformMatrix( mat );
	return *this;
}

//================================================================================
//「/=」のオーバーロード
//【機　能】
//	ベクトルの除算を行い結果を左辺に代入する
//【引　数】
//	除算する値
//【戻り値】
//	呼び出し元オブジェクト
//【備　考】
//	なし
//================================================================================
CVector& CVector::operator /=( const float fValue )
{
	if( fValue == 0.0f )	return *this;
	this->m_Vector.x /= fValue;
	this->m_Vector.y /= fValue;
	this->m_Vector.z /= fValue;
	return *this;
}
