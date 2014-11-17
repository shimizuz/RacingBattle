#pragma warning(disable:4996)
//ヘッダーインクルード
#include "CScene3D.h"
#include <cmath>
#include <stdio.h>
#include "texture.h"
#include "Input.h"

#define POS_MARGIN_X	(50)
#define POS_MARGIN_Y	(50)

int g_cnt = 0;

//作成
CScene3D* CScene3D::Create(CVector pos,char* ptexFileName,float scaleWidth,float scaleHeight)
{
	CScene3D* pScene3D = new CScene3D(0);

	pScene3D->SetPosition(pos);

	pScene3D->Init(ptexFileName,scaleWidth,scaleHeight);

	return pScene3D;

}

//初期化
void CScene3D::Init()
{

	m_rot = CVector(0,0,0);
	m_scl = CVector(1,1,1);

	for(int i = 0;i < 4;i++)
	{
		m_vtx[i].SetValue(0,m_pos.GetY(),0);
	}

	//対角線の長さ
	m_fLength = sqrtf(POS_MARGIN_X*POS_MARGIN_X+POS_MARGIN_Y*POS_MARGIN_Y);
	//対角線の角度
	m_fAngle  = atan2((float)POS_MARGIN_X,(float)POS_MARGIN_Y);

	//左下
	m_vtx[0].SetX(m_pos.GetX() - sinf(-m_rot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[0].SetZ(m_pos.GetZ() + cosf(-m_rot.GetZ()+m_fAngle)*m_fLength);
	//左上
	m_vtx[1].SetX(m_pos.GetX() - sinf(m_rot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[1].SetZ(m_pos.GetZ() - cosf(m_rot.GetZ()+m_fAngle)*m_fLength);
	//右下
	m_vtx[2].SetX(m_pos.GetX() + sinf(m_rot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[2].SetZ(m_pos.GetZ() + cosf(m_rot.GetZ()+m_fAngle)*m_fLength);
	//右上
	m_vtx[3].SetX(m_pos.GetX() + sinf(-m_rot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[3].SetZ(m_pos.GetZ() - cosf(-m_rot.GetZ()+m_fAngle)*m_fLength);
	
	//テクスチャ読み込み
	m_texture	= LoadTexture("data\\texture\\witch3.tga");
}
//初期化オーバーロード
void CScene3D::Init(char* ptexFileName,float scaleWidth,float scaleHeight)
{
	//テクスチャ読み込み
	m_texture	= CreateTexture(ptexFileName);

	m_rot = CVector(0,0,0);
	m_scl = CVector(1,1,1);

	for(int i = 0;i < 4;i++)
	{
		m_vtx[i].SetValue(0,m_pos.GetY(),0);
	}

	//対角線の長さ
	m_fLength = sqrtf(scaleWidth*scaleWidth+scaleHeight*scaleHeight);

	//対角線の角度
	m_fAngle  = atan2(scaleWidth,scaleHeight);

	//左下
	m_vtx[0].SetX(m_pos.GetX() - sinf(-m_rot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[0].SetZ(m_pos.GetZ() + cosf(-m_rot.GetZ()+m_fAngle)*m_fLength);
	//左上
	m_vtx[1].SetX(m_pos.GetX() - sinf(m_rot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[1].SetZ(m_pos.GetZ() - cosf(m_rot.GetZ()+m_fAngle)*m_fLength);
	//右下
	m_vtx[2].SetX(m_pos.GetX() + sinf(m_rot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[2].SetZ(m_pos.GetZ() + cosf(m_rot.GetZ()+m_fAngle)*m_fLength);
	//右上
	m_vtx[3].SetX(m_pos.GetX() + sinf(-m_rot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[3].SetZ(m_pos.GetZ() - cosf(-m_rot.GetZ()+m_fAngle)*m_fLength);
}
//開放
void CScene3D::Uninit()
{
	glDeleteTextures(1,&m_texture);
	Release();
}
//更新
void CScene3D::Update()
{
	if(CInputSystem::getInstance()->GetKeyPush(VK_LEFT))
	{
		m_rot.m_Vector.x += 0.1f;
	}

	if(CInputSystem::getInstance()->GetKeyPush(VK_RIGHT))
	{
		m_rot.m_Vector.x -= 0.1f;
	}
}
//描画
void CScene3D::Draw()
{

	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	//3D用マトリクス設定
	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();//プッシュ
			


	glRotatef(m_rot.m_Vector.z,0,0,1);
	glRotatef(m_rot.m_Vector.y,0,1,0);
	glRotatef(m_rot.m_Vector.x,1,0,0);
	//テクスチャセット
	glBindTexture(GL_TEXTURE_2D,m_texture);
	
	//描画開始
	glBegin(GL_TRIANGLE_STRIP);
	//ここからは色、頂点テクスチャ等
	//色指定
	glColor4f(1.0f,1.0f,1.0f,1.0f);
	//頂点位置設定
	glNormal3f(0.0f,1.0f,0.0f);
	glTexCoord2f(0,0);
	glVertex3f(m_vtx[1].GetX(), m_vtx[1].GetY(), m_vtx[1].GetZ());
	glNormal3f(0.0f,1.0f,0.0f);
	glTexCoord2f(0,1);
	glVertex3f(m_vtx[0].GetX(), m_vtx[0].GetY(), m_vtx[0].GetZ());
	glNormal3f(0.0f,1.0f,0.0f);
	glTexCoord2f(1,0);
	glVertex3f(m_vtx[3].GetX(), m_vtx[3].GetY(), m_vtx[3].GetZ());
	glNormal3f(0.0f,1.0f,0.0f);
	glTexCoord2f(1,1);
	glVertex3f(m_vtx[2].GetX(), m_vtx[2].GetY(), m_vtx[2].GetZ());

	//描画終了
	glEnd();
	//テクスチャ開放
	glBindTexture(GL_TEXTURE_2D,0);

	glPopMatrix();	//ポップ
	
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
}

