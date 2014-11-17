//=============================================================================
//
// フェード処理 [CFade.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//ヘッダーインクルード
#include "CFade.h"
#include <process.h>
#include "Class_Vector.h"
#include <cmath>

//マクロ
#define POS_MARGIN_FADE_X	(400)
#define POS_MARGIN_FADE_Y	(300)

//メンバ変数
CFade* CFade::m_instance = NULL;

CFade* CFade::getinstance()
{
	if(m_instance == NULL)
	{
		m_instance = new CFade();
	}
	return m_instance;
}

void CFade::Release()
{
	if(m_instance != NULL)
	{
		delete m_instance;
		m_instance = NULL;
	}
}

//初期化
HRESULT CFade::Init()
{
	m_FadeMode = FADE_NONE;

	
	m_rot = CVector(0,0,0);
	m_scl = CVector(1,1,1);

	//頂点データ
	for(int i = 0;i < 4;i++)
	{
		m_vtx[i].SetValue(0,0,0);
	}

	m_pos.m_Vector.x += 400;
	m_pos.m_Vector.y += 300;

	//対角線の長さ
	m_fLength = sqrtf(400*400+300*300);
	//対角線の角度
	m_fAngle  = atan2((float)400,(float)300);

	//左下
	m_vtx[0].SetX(m_pos.GetX() - sinf(-m_rot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[0].SetY(m_pos.GetY() + cosf(-m_rot.GetZ()+m_fAngle)*m_fLength);
	//左上
	m_vtx[1].SetX(m_pos.GetX() - sinf(m_rot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[1].SetY(m_pos.GetY() - cosf(m_rot.GetZ()+m_fAngle)*m_fLength);
	//右下
	m_vtx[2].SetX(m_pos.GetX() + sinf(m_rot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[2].SetY(m_pos.GetY() + cosf(m_rot.GetZ()+m_fAngle)*m_fLength);
	//右上
	m_vtx[3].SetX(m_pos.GetX() + sinf(-m_rot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[3].SetY(m_pos.GetY() - cosf(-m_rot.GetZ()+m_fAngle)*m_fLength);

	m_Alpha = 0.0f;

	return S_OK;
}
//開放
void CFade::Uninit()
{

}
//更新
void CFade::Update()
{
	if(m_FadeMode == FADE_OUT)
	{
		if(FadeOut())
		{
			m_FadeMode = FADE_OUT_FINISH;
			
		}
	}
	
	if(m_FadeMode == FADE_IN)
	{
		if(FadeIn())
		{
			m_FadeMode = FADE_NONE;
			
		}
	}
	
}

//描画
void CFade::Draw()
{
	//ライティング無効
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	
	//αブレンディング
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	
	//2D用マトリクス設定
	glMatrixMode(GL_PROJECTION);
	glPushMatrix(); //保存glPopMatrix();復元
	glLoadIdentity();
	glOrtho(0,SCREEN_WIDTH,SCREEN_HEIGHT,0,0,1);
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	

	//描画開始
	glBegin(GL_TRIANGLE_STRIP);

	//ここからは色、頂点テクスチャ等
	//色指定
	
	//頂点位置設定
	glColor4f(0.0f,0.0f,0.0f,m_Alpha);
	glVertex3f(m_vtx[1].GetX(), m_vtx[1].GetY(), m_vtx[1].GetZ());
	glColor4f(0.0f,0.0f,0.0f,m_Alpha);
	glVertex3f(m_vtx[0].GetX(), m_vtx[0].GetY(), m_vtx[0].GetZ());
	glColor4f(0.0f,0.0f,0.0f,m_Alpha);
	glVertex3f(m_vtx[3].GetX(), m_vtx[3].GetY(), m_vtx[3].GetZ());
	glColor4f(0.0f,0.0f,0.0f,m_Alpha);
	glVertex3f(m_vtx[2].GetX(), m_vtx[2].GetY(), m_vtx[2].GetZ());

	//描画終了
	glEnd();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glDisable(GL_BLEND);
}
//フェードアウト
bool CFade::FadeOut()
{
	if(m_FadeMode == FADE_OUT)
	{
		m_Alpha += 0.05f;
		
		if(m_Alpha >= 1.0f)
		{
			m_Alpha = 1.0f;
			
			return true;
		}
	}
	return false;
}
//フェードイン
bool CFade::FadeIn()
{
	if(m_FadeMode == FADE_IN)
	{
		
		m_Alpha -= 0.05f;
		
		if(m_Alpha <= 0)
		{
			m_Alpha = 0;
			
			return true;
		}
	}
	return false;
}
//eof