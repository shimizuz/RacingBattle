#pragma warning(disable:4996)
//ヘッダーインクルード
#include "CScene2D.h"
#include <cmath>
#include <stdio.h>
#include "texture.h"

#define POS_MARGIN_X	(50)
#define POS_MARGIN_Y	(50)

//作成
CScene2D* CScene2D::Create(CVector pos,char* ptexFileName,float scaleWidth,float scaleHeight)
{
	CScene2D* pScene2D = new CScene2D();

	pScene2D->SetPosition(pos);

	pScene2D->Init(ptexFileName,scaleWidth,scaleHeight);

	return pScene2D;

}
//初期化
void CScene2D::Init()
{
	m_rot = CVector(0,0,0);
	m_scl = CVector(1,1,1);

	//頂点データ
	for(int i = 0;i < 4;i++)
	{
		m_vtx[i].SetValue(0,0,0);
	}

	//対角線の長さ
	m_fLength = sqrtf(POS_MARGIN_X*POS_MARGIN_X+POS_MARGIN_Y*POS_MARGIN_Y);
	//対角線の角度
	m_fAngle  = atan2((float)POS_MARGIN_X,(float)POS_MARGIN_Y);

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

	//テクスチャ読み込み
	m_texture	= LoadTexture("data\\texture\\witch3.tga");

}
//初期化オーバーロード
void CScene2D::Init(char* ptexFileName,float scaleWidth,float scaleHeight)
{
	//テクスチャ読み込み
	m_texture	= CreateTexture(ptexFileName);

	m_rot = CVector(0,0,0);
	m_scl = CVector(1,1,1);

	m_pos.m_Vector.x += scaleWidth;
	m_pos.m_Vector.y += scaleHeight; 

	for(int i = 0;i < 4;i++)
	{
		m_vtx[i].SetValue(0,m_pos.GetY(),0);
	}

	//対角線の長さ
	m_fLength = sqrtf(scaleWidth*scaleWidth+scaleHeight*scaleHeight);

	//対角線の角度
	m_fAngle  = atan2((float)scaleWidth,(float)scaleHeight);

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

}
//開放
void CScene2D::Uninit()
{
	glDeleteTextures(1,&m_texture);
	Release();
}
//更新
void CScene2D::Update()
{

}
//描画
void CScene2D::Draw()
{
	//ライティング無効
	glDisable(GL_LIGHTING);

	//2D用マトリクス設定
	glMatrixMode(GL_PROJECTION);
	glPushMatrix(); //保存glPopMatrix();復元
	glLoadIdentity();
	glOrtho(0,SCREEN_WIDTH,SCREEN_HEIGHT,0,0,1);
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//テクスチャセット
	glBindTexture(GL_TEXTURE_2D,m_texture);
	

	//描画開始
	glBegin(GL_TRIANGLE_STRIP);

	//ここからは色、頂点テクスチャ等
	//色指定
	glColor4f(1.0f,1.0f,1.0f,1.0f);
	//頂点位置設定
	glTexCoord2f(0,0);
	glVertex3f(m_vtx[1].GetX(), m_vtx[1].GetY(), m_vtx[1].GetZ());
	glTexCoord2f(0,1);
	glVertex3f(m_vtx[0].GetX(), m_vtx[0].GetY(), m_vtx[0].GetZ());
	glTexCoord2f(1,0);
	glVertex3f(m_vtx[3].GetX(), m_vtx[3].GetY(), m_vtx[3].GetZ());
	glTexCoord2f(1,1);
	glVertex3f(m_vtx[2].GetX(), m_vtx[2].GetY(), m_vtx[2].GetZ());

	//描画終了
	glEnd();
	//テクスチャ開放
	glBindTexture(GL_TEXTURE_2D,0);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	
}

