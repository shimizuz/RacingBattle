//==============================================================================
//
// フラッグ管理
// Author : Masahiro Yamaguchi
//==============================================================================
//==============================================================================
//多重定義防止
//==============================================================================
#ifndef __CFLAG_H__
#define __CFLAG_G__

//==============================================================================
//ヘッダーインクルード
//==============================================================================
#include "CBillboard.h"

//==============================================================================
//クラス定義
//==============================================================================
class CFlag : public CBillboard
{
public:

	//マクロ定義
	static const int kMaxFlags = 3;		//フラッグの数
	static const int kLoadLevels = 10;	//シーン遷移

	//コンストラクタ
	CFlag(int nPriority = 3):CBillboard(nPriority)
	{
		m_FlagNum = 0;
		m_kLoadLevelNum = 0;
	
		m_haveflag = false;
	}
	//デストラクタ
	virtual ~CFlag()
	{

	}
	//生成
	static CFlag* Create(CVector pos,float fangle,char* ptexname,float scaleWidth,float scaleHeight);
	//初期化
	void Init(float fangle,char* ptexname,float scaleWidth,float scaleHeight);
	//更新
	void Update();
	//開放
	void Uninit();
	//描画
	void Draw();

	//▼取得
	int GetFlagNum()
	{
		return m_FlagNum;
	}
	int GetLoadLevelNum()
	{
		return m_kLoadLevelNum;
	}
	bool GetHaveFlag()
	{
		return m_haveflag;
	}
	void SetHaveFlag(bool flag)
	{
		m_haveflag = flag;
	}
private:
	
	int	m_FlagNum;
	int m_kLoadLevelNum;
	bool m_haveflag;
};
#endif
//eof