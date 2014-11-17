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
	CVector m_posCameraP;
	CVector m_posCameraR;
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

};


#endif