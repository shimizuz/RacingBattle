//==============================================================================
//
// プレイヤーマネージャ
// Author : Shimizu Shoji
//
// プレイヤーのマネージャクラスです。
// マネージャといってもほぼマネージングしないんですけどね。
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "CPlayer.h"
#include "CPlayerManager.h"
#include <cmath>
#include <assert.h>

#include <d3dx9.h>
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// const
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace {
const float kInitDistance = 10.0f;
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
CPlayerManager::CPlayerManager() {
	for (int i = 0; i < kNumPlayers; ++i) {
		m_pPlayers[i] = nullptr;
	}
	for (int i = 0; i < kNumPlayers; ++i) {
		m_pPlayers[i] = new CPlayer();
		m_pPlayers[i]->Init(1.0f, 1.0f);
	}
	float angle = 0;
	for (int i = 0; i < kNumPlayers; ++i) {
		CVector pos (
        sinf(angle) * kInitDistance,
			  1.0f,
			  cosf(angle) * kInitDistance);

		m_pPlayers[i]->SetPosition(pos);
		angle += D3DX_PI * 0.5f;
	}
}


//------------------------------------------------
// dtor
//------------------------------------------------
CPlayerManager::~CPlayerManager() {
	for (int i = 0; i < kNumPlayers; ++i) {
		delete m_pPlayers[i];
		m_pPlayers[i] = nullptr;
	}
}

//------------------------------------------------
// check range
//------------------------------------------------
void CPlayerManager::_CheckRange(int id) {
	assert(id < kNumPlayers && "あほか範囲外だぞ");
}



