//ヘッダーインクルード
#include "CCameraGL.h"
#include "Input.h"
#include <cmath>
#include "CLightGL.h"

POINT g_pos;
POINT pos;
POINT dis;
LONG x = 0,x1 = 0;

CCameraGL* CCameraGL::m_Instance = NULL;

CCameraGL* CCameraGL::getInstance()
{
	if(m_Instance == NULL)
	{
		m_Instance = new CCameraGL();
	}
	return m_Instance;
}

void CCameraGL::Release()
{
	if(m_Instance != NULL)
	{
		delete m_Instance;
		m_Instance = NULL;
	}
}

void CCameraGL::Init()
{
	m_posCameraP.SetValue(0.0f,20.0f,10.0f);
	m_posCameraR.SetValue(0.0f,0.0f,0.0f);
	m_rotCamera.SetValue(0.0f,0.0f,0.0f);
	m_vecCameraUp.SetValue(0.0f,1.0f,0.0f);

	m_rotCamera.SetY( atan2f( ( m_posCameraR.GetX()-m_posCameraP.GetX() ), ( m_posCameraR.GetZ() - m_posCameraP.GetZ() ) ));
	m_rotCamera.SetX( atan2f( ( m_posCameraR.GetZ()-m_posCameraP.GetZ() ), ( m_posCameraR.GetY() - m_posCameraP.GetY() ) ));
	
	m_pLight = new CLightGL();
	m_pLight->Init();
	m_bFlag = false;
	m_bFlag1 = false;
	m_angle= PI;
}
void CCameraGL::Uninit()
{
	SAFE_DELETE(m_pLight);
}
void CCameraGL::Update()
{
	//変数宣言
/*
	// Y軸に対しての回転
	if( CInputSystem::getInstance()->GetKeyPush(VK_LBUTTON) )
	{
		if(!m_bFlag)
		{
			GetCursorPos( &g_pos );	//マウスの座標取得
			ScreenToClient(GethWnd(),&g_pos);	//クライアント座標にする
			m_bFlag = true;
		}
		else
		{
			GetCursorPos(&pos);
			ScreenToClient(GethWnd(),&pos);

			dis.x = g_pos.x-pos.x;
			x = dis.x /10;
		}
		if(dis.x > 0)
		{
			g_pos.x-=2;
		}
		if(pos.x < g_pos.x)
		{
			// m_rotCamera.yは、PからRを見た角度であるが旋回はRからPを見た角度を使いたいので１８０°補正する必要がある
			m_angle = PI;			// １８０°

			m_rotCamera.SetY(m_rotCamera.GetY() + PI * 0.01f);
		}
		
	}
	else
	{
		m_bFlag = false;
	}
	// 右旋回
	if( CInputSystem::getInstance()->GetKeyPush(VK_RBUTTON) )
	{
		if(!m_bFlag1)
		{
			GetCursorPos( &g_pos );	//マウスの座標取得
			ScreenToClient(GethWnd(),&g_pos);	//クライアント座標にする
			m_bFlag1 = true;
		}
		else
		{
			GetCursorPos(&pos);
			ScreenToClient(GethWnd(),&pos);

			dis.x = pos.x-g_pos.x;
			x1 = dis.x /10;
		}
		if(dis.x > 0)
		{
			g_pos.x+=2;
		}
		if(pos.x > g_pos.x)
		{
			// m_rotCamera.yは、PからRを見た角度であるが旋回はRからPを見た角度を使いたいので１８０°補正する必要がある
			m_angle = PI;			// １８０°

			m_rotCamera.SetY(m_rotCamera.GetY() - PI * 0.01f);
		}
	}
*/
	m_posCameraP.SetX ( m_posCameraR.GetX() + ( sinf( m_rotCamera.GetY() ) * m_angle ) * 10.0f);
	m_posCameraP.SetZ ( m_posCameraR.GetZ() + ( cosf( m_rotCamera.GetY() ) * m_angle ) * 10.0f);
}
//カメラ設定
void CCameraGL::SetCamera(void)
{
	//プロジェクション
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0,		// 画角
					4.0/3.0,	// アスペクト比
					1.0,		// ニアクリップ
					300.0);		// ファークリップ


	//ビュー行列
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(static_cast<GLdouble>(m_posCameraP.GetX()),static_cast<GLdouble>(m_posCameraP.GetY()),static_cast<GLdouble>(m_posCameraP.GetZ()),		//位置
				static_cast<GLdouble>(m_posCameraR.GetX()),static_cast<GLdouble>(m_posCameraR.GetY()),static_cast<GLdouble>(m_posCameraR.GetZ()),	//注視点
				0.0,1.0,0.0);	//上方向

	//ライトをここでやる
	m_pLight->SetLight();

}

/*
	double modelview[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);

	double projection[16];
	glGetDoublev(GL_PROJECTION_MATRIX, projection);

	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	float z;
	double objX;
	double objY;
	double objZ;

	glReadPixels(50,WindowHeight - 50,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&z);

	gluUnProject(50,WindowHeight - 50,z,modelview,projection,viewport,&objX,&objY,&objZ);
*/