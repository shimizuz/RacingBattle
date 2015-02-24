//=============================================================================
//
// タイマー処理 [ CTimer.h ]
// Author : DYE IMAIZUMI
//
//=============================================================================
//*****************************************************************************
// インクルードガード
//*****************************************************************************
#ifndef ＿TIMER_H_
#define ＿TIMER_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "CScene2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUMBER_PLACE_MAX (2)
#define TIME_WIDTH (40.0f)		// スコア一桁分の横幅
#define TIME_HEIGHT (80.0f)		// スコア一桁分の縦幅
#define X_CENTER_POS_TIME ( 400 )					// テクスチャの真ん中のX座標
#define Y_CENTER_POS_TIME ( 300 )					// テクスチャの真ん中のY座標
#define TIME_X_LENGTH ( 100 )					// テクスチャの斜辺X方向
#define TIME_Y_LENGTH ( 100 )					// テクスチャの斜辺Y方向

//*****************************************************************************
// クラス設計
//*****************************************************************************
class CTimer : public CScene2D
{

public:

	CTimer();										// コンストラクタ
	~CTimer();									// デストラクタ
	void Init( char* ptexFileName,float scaleWidth,float scaleHeight );			// 初期化
	void Uninit( void );							// 終了
	void Update( void );							// 更新
	void Draw( void );								// 描画

	static CScene2D* CreateTimer( CVector pos,char* ptexFileName,float scaleWidth,float scaleHeight );// クリエイト関数

	static int GetSecNum( void ){ return m_nSecNum; };

	//座標設定
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
#endif //＿TIMER_H_

// EOF