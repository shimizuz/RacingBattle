//多重定義防止
#ifndef __CMANAGER_H__
#define __CMANAGER_H__

//ヘッダーインクルード
#include "main.h"
#include "CPhaseFactory.h"
#include "CPhase.h"

//前方宣言
class CRenderer;
class CScene;
//class CFactoryPtr;
//class CPhase;
//クラス定義
class CManager
{
private:
	static CRenderer*		m_pRenderer;
	static CFactoryPtr*		m_pNextPtr;
	static CPhase*			m_pCurrentPhase;
public:

	//コンストラクタ
	CManager(){}
	//デストラクタ
	virtual ~CManager(){}
	//初期化
	void Init(HWND hWnd);
	//開放
	void Uninit(void);
	//更新
	void Updata(void);
	//描画
	void Draw(void);
	//ゲッター
	static CRenderer* GetRenderer(void)
	{
		return m_pRenderer;
	}
	//ファクトリをセット
	static bool SetFactory(CFactoryPtr* ptr)
	{
		if(m_pNextPtr == NULL)
		{
			m_pNextPtr = ptr;
			return true;
		}
		return false;
	}
	//ファクトリを削除
	static void DeleteFactory(void)
	{
		delete m_pNextPtr;
		m_pNextPtr = NULL;
	}

};
#endif