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
//ヘッダーインクルード
//==============================================================================
#include "COwnhalfManager.h"
#include "COwnhalf.h"
#include <assert.h>
#include <cmath>
#include <d3dx9.h>
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// const
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace {
const float kInitDistance = 30.0f;
}
//==============================================================================
// コンストラクタ
//==============================================================================
COwnhalfManager::COwnhalfManager()
{
	for (int i = 0; i < kNumOwnhalfs; ++i) 
	{
		m_pOwnhalfs[i] = nullptr;
	}
	for (int i = 0; i < kNumOwnhalfs; ++i) 
	{
		m_pOwnhalfs[i] = new COwnhalf();
		m_pOwnhalfs[i]->Init(5.0f,5.0f);
	}
	float angle = 0;
	for (int i = 0; i < kNumOwnhalfs; ++i) {
		CVector pos (
        sinf(angle) * kInitDistance,
			  1.0f,
			  cosf(angle) * kInitDistance);

		m_pOwnhalfs[i]->SetPosition(pos);
		angle += D3DX_PI * 0.5f;
	}
	
}
//==============================================================================
// デストラクタ
//==============================================================================
COwnhalfManager::~COwnhalfManager()
{

}
//==============================================================================
// 範囲チェック
//==============================================================================
void COwnhalfManager::_CheckRange(int id) 
{
	assert(id < kNumOwnhalfs && "アーウ範囲外だぞ");
}


//eof