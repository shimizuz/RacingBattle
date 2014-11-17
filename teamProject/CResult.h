//=============================================================================
//
// シーン遷移処理 [CResult.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
//=============================================================================
//多重定義防止
//=============================================================================
#ifndef __CRESULT_H__
#define __CRESULT_H__

//ヘッダーインクルード
#include "CPhase.h"

//クラス定義
class CResult : public CPhase
{
private:

public:
	//コンストラクタ
	CResult()
	{

	}
	//デストラクタ
	~CResult()
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