#ifndef __CSCENE2D_H__
#define __CSCENE2D_H__

#include "main.h"
#include "CScene.h"

//前方宣言
class CRender;

//クラス定義
class CScene2D:public CScene
{
private:
	float	m_fLength;
	float	m_fAngle;
	CVector m_pos;
	CVector m_rot;
	CVector m_scl;
	CVector m_vtx[4];
	unsigned int m_texture;
public:
	CScene2D(int nPriority = 6):CScene(nPriority){}
	virtual ~CScene2D(){}

	//初期化
	void Init();
	//初期化オーバーロード
	void Init(char* ptexFileName,float scaleWidth,float scaleHeight);
	//更新
	void Update();
	//開放
	void Uninit();
	//描画
	void Draw();
	
	//座標取得
	CVector GetPosition(void)
	{
		return m_pos;
	}
	//座標設定
	void SetPosition(CVector pos)
	{
		m_pos = pos;	
	}
	//回転取得
	CVector GetRotate(void)
	{
		return m_rot;
	}
	//回転設定
	void SetRotate(CVector rot)
	{
		m_rot = rot;	
	}
	static CScene2D* Create(CVector pos,char* ptexFileName,float scaleWidth,float scaleHeight);
};
#endif