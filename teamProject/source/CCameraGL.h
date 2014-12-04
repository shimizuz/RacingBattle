//多重定義防止
#ifndef __CCAMERAGL_H__
#define __CCAMERAGL_H__

//ヘッダーインクルード
#include "main.h"
#include "Class_Vector.h"

//前方宣言
class CLightGL;

//クラス定義
class CCameraGL
{
private:
	CVector m_posCameraP;			//視点
	CVector m_posCameraR;			//注視点
	CVector m_vecCameraUp;
	CVector m_rotCamera;
	float	m_angle;
	CLightGL* m_pLight;
	bool	m_bFlag;
	bool	m_bFlag1;
	static CCameraGL* m_Instance;

public:
	static CCameraGL* getInstance();
	static void Release();
	CCameraGL(){}
	virtual~CCameraGL(){}
	void Init(void);
	void Update(void);
	void Uninit(void);
	void SetCamera(void);
	
	//座標取得
	CVector GetPosition(void)
	{
		return m_posCameraR;
	}
	//座標設定
	void SetPosition(CVector pos)
	{
		m_posCameraR = pos;	
	}

	//回転取得
	CVector GetRotate(void)
	{
		return m_rotCamera;
	}
	//回転設定
	void SetRotate(CVector rot)
	{
		m_rotCamera = rot;	
	}
};

#endif