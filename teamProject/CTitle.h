//=============================================================================
//
// 各フェーズ処理 [CTitle.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//多重定義
#ifndef __CTITLE_H__
#define __CTITLE_H__

//ヘッダーインクルード
#include "CPhase.h"

//前方宣言
class CRender;

//クラス定義
class CTitle:public CPhase
{
private:
	
public:

	//コンストラクタ
	CTitle()
	{

	}
	//デストラクタ
	~CTitle()
	{

	}
	//各シーン
	virtual bool Init(void *lpArgs = NULL);
	virtual bool Update(void *lpArgs = NULL);
	virtual bool Release(void *lpArgs = NULL);
	virtual bool Draw(void *lpArgs = NULL);
};

#endif