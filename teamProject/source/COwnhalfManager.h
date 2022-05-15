//==============================================================================
//
// 陣地マネージャ
// Author : Masahiro Yamaguchi
//
// 陣地のマネージャクラスです。
// マネージャといってもほぼマネージングしないんですけどね。
//
//==============================================================================
//==============================================================================
//多重定義防止
//==============================================================================
#pragma once
#ifndef __COWNHALFMANAGER_H__
#define __COWNHALFMANAGER_H__

//==============================================================================
//ヘッダーインクルード
//==============================================================================

//==============================================================================
//前方宣言
//==============================================================================
class COwnhalf;

//==============================================================================
//クラス定義
//==============================================================================
class COwnhalfManager
{
public:
	// const
	static const int kNumOwnhalfs = 4;

	// ctor
	COwnhalfManager();

	// dtor
	~COwnhalfManager();

	// 陣地の取得
	COwnhalf* GetOwnhalf(int id) 
	{
		_CheckRange(id);
		return m_pOwnhalfs[id];
	}
private:
	void _CheckRange(int id);

	COwnhalf* m_pOwnhalfs[kNumOwnhalfs];
};

#endif

//eof