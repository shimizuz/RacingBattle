//=============================================================================
//
// フェード処理 [CFade.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//多重定義防止
#ifndef __CFADE_H__
#define __CFADE_H__

//ヘッダーインクルード
#include "main.h"
#include "CScene2D.h"


//モードチェンジ用列挙型
typedef enum
{
	FADE_NONE,
	FADE_OUT,
	FADE_IN,
	FADE_OUT_FINISH,
	FADE_IN_FINISH,
	FADE_MAX
}FADEMODE;

class CRender;

//クラス定義
class CFade
{
private:
	FADEMODE	m_FadeMode;
	bool		m_fadeFlag;
	float		m_Alpha;
//	float					m_fLength;				// 中心から頂点までの長さ
//	float					m_fAngle;				// 中心から頂点への角度
	char*					m_pTexName;
	static CFade*			m_instance;
	float	m_fLength;
	float	m_fAngle;
	CVector m_pos;
	CVector m_rot;
	CVector m_scl;
	CVector m_vtx[4];
	unsigned int m_texture;
public:
	static CFade*			getinstance();
	static void				Release();
	CFade()
	{
		m_Alpha = 0;
	}
	virtual ~CFade()
	{
		
	}
	
	HRESULT Init();
	void Update();
	void Uninit();
	void Draw();

	FADEMODE	GetFadeMode(void)
	{
		return m_FadeMode;
	}
	void		SetFadeMode(FADEMODE iNum)
	{
		m_FadeMode = iNum;
	}

	bool		FadeOut(void);
	bool		FadeIn(void);

};

#endif