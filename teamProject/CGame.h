//=============================================================================
//
// シーン遷移処理 [CGame.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
//=============================================================================
//多重定義防止
//=============================================================================
#ifndef __CGAME_H__
#define __CGAME_H__

//ヘッダーインクルード
#include "CPhase.h"

//クラス定義
class CGame : public CPhase
{
private:

public:
	//コンストラクタ
	CGame()
	{

	}
	//デストラクタ
	~CGame()
	{

	}
	//各シーン
	virtual bool Init(void *lpArgs = NULL);
	virtual bool Update(void *lpArgs = NULL);
	virtual bool Release(void *lpArgs = NULL);
	virtual bool Draw(void *lpArgs = NULL);
};


#endif
//eof