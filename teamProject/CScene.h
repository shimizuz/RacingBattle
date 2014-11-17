//多重定義防止
#ifndef __CSCENE_H__
#define __CSCENE_H__

//ヘッダーインクルード
#include "main.h"
#include "Class_Vector.h"

//マクロ定義
#define PRIORITY_MAX	(8)

//前方宣言
class CRenderer;
//クラス定義
class CScene
{
private:
	
	static CScene*		m_pTop[PRIORITY_MAX];	//リストの先頭アドレス
	static CScene*		m_pCur[PRIORITY_MAX];	//リストの現在位置アドレス
	CScene*				m_pNext;				//前のオブジェクトへのポインタ
	CScene*				m_pPrev;				//次のオブジェクトへのポインタ
	const int			m_nPriority;			//プライオリティ
	bool				m_bDeath;				//オブジェクト削除フラグ
public:
	//コンストラクタ
	explicit CScene(int nPriority = 3);
	virtual ~CScene();

	//初期化
	virtual void Init() = 0;
	//更新
	virtual void Update() = 0;
	//開放
	virtual void Uninit() = 0;
	//描画
	virtual void Draw() = 0;
	
	//座標取得
	virtual CVector GetPosition(void) = 0;

	//座標設定
	virtual void SetPosition(CVector pos) = 0;
		
	virtual CVector GetRotate(void) = 0;
	
	//回転設定
	virtual void SetRotate(CVector rot) = 0;
	//▼リスト系
	void Release(void);
	void LinkList(void);
	void UnlinkList(CScene* pScene);
	static void DrawAll(void);
	static void UpdateAll(void);
	static void ReleaseAll(void);
	static void FreePhase(void);
	static void Delete(int nIdxScene);
};


#endif