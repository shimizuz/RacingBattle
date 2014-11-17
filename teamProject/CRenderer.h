//多重定義防止
#ifndef __CRENDERER_H__
#define __CRENDERER_H__


//ヘッダーインクルード
#include "main.h"
//マクロ

//前方宣言
class CScene;
class CCameraGL;

//クラス定義
class CRenderer
{
private:
	HDC			m_dc;
	HGLRC		m_glRC;
	HWND		m_hWnd;
	CCameraGL*	m_Camera;
public:

	CRenderer();
	virtual ~CRenderer();

	bool Init(HWND hWnd);
	void Update();
	void Uninit();
	void Draw();
};
#endif