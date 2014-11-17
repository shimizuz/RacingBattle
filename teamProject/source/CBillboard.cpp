#include "CBillboard.h"
#include <cmath>
#include "texture.h"
#include "Class_Matrix.h"
#include "Input.h"

//生成
CBillboard* CBillboard::Create(CVector pos,char* ptexFileName,float scaleWidth,float scaleHeight)
{
	CBillboard* pScene3D = new CBillboard(0);

	pScene3D->SetPosition(pos);

	pScene3D->Init(ptexFileName,scaleWidth,scaleHeight);

	

	return pScene3D;

}
//初期化
void CBillboard::Init()
{
	for(int i = 0;i < 4;i++)
	{
		m_vtx[i].SetValue(0,0,0);
	}

	m_rot = CVector(0,0,0);
	m_scl = CVector(1,1,1);

	//対角線の長さ
	m_fLength = sqrtf(50*50+50*50);
	//対角線の角度
	m_fAngle  = atan2((float)50,(float)50);

}
//初期化オーバーロード
void CBillboard::Init(char* ptexFileName,float scaleWidth,float scaleHeight)
{
	//テクスチャ読み込み
	m_texture	= CreateTexture(ptexFileName);

	m_rot = CVector(0,0,0);
	m_scl = CVector(1,1,1);

	for(int i = 0;i < 4;i++)
	{
		m_vtx[i].SetValue(0,0,0);
	}

	//対角線の長さ
	m_fLength = sqrtf(scaleWidth*scaleWidth+scaleHeight*scaleHeight);

	//対角線の角度
	m_fAngle  = atan2(scaleWidth,scaleHeight);

	//左下
	m_vtx[1].SetX(m_pos.GetX() - sinf(-m_rot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[1].SetY(m_pos.GetY() + cosf(-m_rot.GetZ()+m_fAngle)*m_fLength);
	//左上
	m_vtx[0].SetX(m_pos.GetX() - sinf(m_rot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[0].SetY(m_pos.GetY() - cosf(m_rot.GetZ()+m_fAngle)*m_fLength);
	//右下
	m_vtx[3].SetX(m_pos.GetX() + sinf(m_rot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[3].SetY(m_pos.GetY() + cosf(m_rot.GetZ()+m_fAngle)*m_fLength);
	//右上
	m_vtx[2].SetX(m_pos.GetX() + sinf(-m_rot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[2].SetY(m_pos.GetY() - cosf(-m_rot.GetZ()+m_fAngle)*m_fLength);
	int a = 0;
}
//開放
void CBillboard::Uninit()
{
	Release();
}
//更新
void CBillboard::Update()
{

}

//描画
void CBillboard::Draw()
{
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	//3D用マトリクス設定
	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();//プッシュ
			
	//ビルボード用
	MATRIX matrix,invMatrix;

	glGetFloatv(GL_MODELVIEW_MATRIX,(float*)&matrix);

	//行列転置
	for(int i = 0;i < 4;i++)
	{
		for(int j = 0;j < 4;j++)
		{
			invMatrix.mat[i][j] = matrix.mat[j][i]; 
		}
	}

	invMatrix._14 = 0;
	invMatrix._24 = 0;
	invMatrix._34 = 0;

	glMultMatrixf((float*)&invMatrix);

	//テクスチャセット
	glBindTexture(GL_TEXTURE_2D,m_texture);
	
	//描画開始
	glBegin(GL_TRIANGLE_STRIP);
	//ここからは色、頂点テクスチャ等
	//色指定
	glColor4f(1.0f,1.0f,1.0f,1.0f);
	//頂点位置設定
	glNormal3f(0.0f,0.0f,0.0f);
	glTexCoord2f(0,0);
	glVertex3f(m_vtx[1].GetX(), m_vtx[1].GetY(), m_vtx[1].GetZ());
	glNormal3f(0.0f,0.0f,0.0f);
	glTexCoord2f(0,1);
	glVertex3f(m_vtx[0].GetX(), m_vtx[0].GetY(), m_vtx[0].GetZ());
	glNormal3f(0.0f,0.0f,0.0f);
	glTexCoord2f(1,0);
	glVertex3f(m_vtx[3].GetX(), m_vtx[3].GetY(), m_vtx[3].GetZ());
	glNormal3f(0.0f,0.0f,0.0f);
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
//eof