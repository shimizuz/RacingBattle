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

class CController;
class CPlayerManager;
class CFlag;
class CField;
<<<<<<< HEAD
class CMeshFieldGL;
=======
class CBullet;
>>>>>>> dev/tama

//ヘッダーインクルード
#include "CPhase.h"
#include "CPlayer.h"
#include "CFlag.h"

//クラス定義
class CGame : public CPhase
{
private:

public:
	//コンストラクタ
  CGame() : pController_(nullptr)
	{
		pPlayerManager_ = NULL;
		pController_ = NULL;
    pBullet_ = nullptr;
	}
	//デストラクタ
  ~CGame();

	//各シーン
	virtual bool Init(void *lpArgs = NULL);
	virtual bool Update(void *lpArgs = NULL);
	virtual bool Release(void *lpArgs = NULL);
	virtual bool Draw(void *lpArgs = NULL);

	//取得
	static CMeshFieldGL* GetCMeshFieldGL()
	{
		return m_pMeshField;
	}

private:
  CController* pController_;
  CPlayerManager* pPlayerManager_;
  CField* pField_;
  CVector pPos;
  CFlag*	m_pFlag[CFlag::kMaxFlags];
  static CMeshFieldGL* m_pMeshField;
  CBullet* pBullet_;
};

#endif
//eof