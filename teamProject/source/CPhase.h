//=============================================================================
//
// 各フェーズ処理 [CPhase.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//多重定義防止
#ifndef __CPHASE_H__
#define __CPHASE_H__

#include <windows.h>
#include <stdio.h>

//シーン管理用クラス
class CPhase
{
protected:
	
public:
	
	//コンストラクタ
	CPhase(){}	
	//デストラクタ
	virtual ~CPhase(){}

	//各シーン
	virtual bool Init(void *lpArgs = NULL) = 0;
	virtual bool Update(void *lpArgs = NULL) = 0;
	virtual bool Release(void *lpArgs = NULL) = 0;
	virtual bool Draw(void *lpArgs = NULL) = 0;

};

#endif
//eof