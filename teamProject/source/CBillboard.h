#pragma once

//ヘッダーインクルード
#include "main.h"
#include "CScene.h"

class CBillboard : public CScene
{
private:
	CVector m_pos;
	CVector m_rot;
	CVector m_scl;
	CVector m_vtx[4];
	float	m_fLength;
	float	m_fAngle;
	unsigned int m_texture;
public:
	CBillboard(int nPriority = 3):CScene(nPriority){}
	virtual ~CBillboard(){}

	//初期化
	void Init();
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
	//拡縮率設定
	void SetScale(CVector scl)
	{
		m_scl = scl;
	}
	static CBillboard* Create(CVector pos,char* ptexFileName,float scaleWidth,float scaleHeight);
};
