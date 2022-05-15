//==============================================================================
//
// タイマー表示[ CTimer.cpp ]
// Author : Dye Imaizumi
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルード
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "CTimer.h"
#include "texture.h"
#include <math.h>

#define POS_MARGIN_X	(50)
#define POS_MARGIN_Y	(50)
//==============================================================================
// 
//==============================================================================
int CTimer :: m_nSecNum;

//-------------------------------------------------
// コンストラクター
//-------------------------------------------------
CTimer :: CTimer()
{
	m_nNumber = 60;
	m_nSecNum = 10;
}
//-------------------------------------------------
// デストラクター
//-------------------------------------------------
CTimer :: ~CTimer()
{
}

//-------------------------------------------------
// 初期化
//-------------------------------------------------
void CTimer :: Init( char* ptexFileName,float scaleWidth,float scaleHeight )
{
	//テクスチャ読み込み
	m_texture = CreateTexture(ptexFileName);

	m_Timerot = CVector(0,0,0);
	m_Timescl = CVector(1,1,1);

	m_Timepos.m_Vector.x += scaleWidth;
	m_Timepos.m_Vector.y += scaleHeight; 

	for(int i = 0;i < 4;i++)
	{
		m_vtx[i].SetValue(0,m_Timepos.GetY(),0);
	}

	//対角線の長さ
	m_fLength = sqrtf(scaleWidth*scaleWidth+scaleHeight*scaleHeight);

	//対角線の角度
	m_fAngle  = atan2((float)scaleWidth,(float)scaleHeight);

	//左下
	m_vtx[0].SetX(m_Timepos.GetX() - sinf(-m_Timerot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[0].SetY(m_Timepos.GetY() + cosf(-m_Timerot.GetZ()+m_fAngle)*m_fLength);
	//左上
	m_vtx[1].SetX(m_Timepos.GetX() - sinf(m_Timerot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[1].SetY(m_Timepos.GetY() - cosf(m_Timerot.GetZ()+m_fAngle)*m_fLength);
	//右下
	m_vtx[2].SetX(m_Timepos.GetX() + sinf(m_Timerot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[2].SetY(m_Timepos.GetY() + cosf(m_Timerot.GetZ()+m_fAngle)*m_fLength);
	//右上
	m_vtx[3].SetX(m_Timepos.GetX() + sinf(-m_Timerot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[3].SetY(m_Timepos.GetY() - cosf(-m_Timerot.GetZ()+m_fAngle)*m_fLength);
	//左下
	m_vtx[4].SetX(m_Timepos.GetX() - sinf(-m_Timerot.GetZ()+m_fAngle)*m_fLength - 60);
	m_vtx[4].SetY(m_Timepos.GetY() + cosf(-m_Timerot.GetZ()+m_fAngle)*m_fLength);
	//左上
	m_vtx[5].SetX(m_Timepos.GetX() - sinf(m_Timerot.GetZ()+m_fAngle)*m_fLength - 60);
	m_vtx[5].SetY(m_Timepos.GetY() - cosf(m_Timerot.GetZ()+m_fAngle)*m_fLength);
	//右下
	m_vtx[6].SetX(m_Timepos.GetX() + sinf(m_Timerot.GetZ()+m_fAngle)*m_fLength - 60);
	m_vtx[6].SetY(m_Timepos.GetY() + cosf(m_Timerot.GetZ()+m_fAngle)*m_fLength);
	//右上
	m_vtx[7].SetX(m_Timepos.GetX() + sinf(-m_Timerot.GetZ()+m_fAngle)*m_fLength - 60);
	m_vtx[7].SetY(m_Timepos.GetY() - cosf(-m_Timerot.GetZ()+m_fAngle)*m_fLength);
	
}

//-------------------------------------------------
// 終了
//-------------------------------------------------
void CTimer :: Uninit()
{
}

//-------------------------------------------------
// 更新
//-------------------------------------------------
void CTimer :: Update()
{
	// 現在のスコアに加算
	m_nNumber--;

	if( m_nNumber > (int)powf(10,NUMBER_PLACE_MAX) )	// エラーチェック
	{
		m_nNumber = (int)powf(10,NUMBER_PLACE_MAX) - 1;
	}
	if( m_nNumber > 0  )
	{
		m_nNumber = 0;
	}
	if(m_nNumber % 60 == 0)
	{
		m_nSecNum--;
		//m_nSecNum %= 60;
	}


}

//-------------------------------------------------
// 描画
//-------------------------------------------------
void CTimer :: Draw()
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

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	//テクスチャセット
	glBindTexture(GL_TEXTURE_2D,m_texture);

	//描画開始
	glBegin(GL_TRIANGLE_STRIP);

	//ここからは色、頂点テクスチャ等
	//色指定
	glColor4f(1.0f,1.0f,1.0f,1.0f);

	for(int nCntPlace = 0 ; nCntPlace < NUMBER_PLACE_MAX ; nCntPlace++)
	{
		// 1ケタずつの時間格納変数
		int nNumber = 0;
	
		// 1ケタずつの時間の出し抜き
		nNumber = m_nSecNum % (int)pow( (double)10, nCntPlace + 1 ) / (int)pow( (double)10, nCntPlace );

		//頂点位置設定
		glTexCoord2f( ( (float)nNumber / 10) + 0.0f , 1.0f );
		glVertex3f(m_vtx[1 + ( nCntPlace * 4 )].GetX(), m_vtx[1].GetY(), m_vtx[1].GetZ());
		glTexCoord2f( ( (float)nNumber / 10) + 0.0f , 0.0f );
		glVertex3f(m_vtx[0 + ( nCntPlace * 4 )].GetX(), m_vtx[0].GetY(), m_vtx[0].GetZ());
		glTexCoord2f( ( (float)nNumber / 10) + 0.1f , 1.0f );
		glVertex3f(m_vtx[3 + ( nCntPlace * 4 )].GetX(), m_vtx[3].GetY(), m_vtx[3].GetZ());
		glTexCoord2f( ( (float)nNumber / 10) + 0.1f , 0.0f );
		glVertex3f(m_vtx[2 + ( nCntPlace * 4 )].GetX(), m_vtx[2].GetY(), m_vtx[2].GetZ());

	}

	//描画終了
	glEnd();
	//テクスチャ開放
	glBindTexture(GL_TEXTURE_2D,0);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

//-------------------------------------------------
// クリエイト
//-------------------------------------------------
CScene2D* CTimer :: CreateTimer( CVector pos,char* ptexFileName,float scaleWidth,float scaleHeight )
{
	CTimer* pTimer = new CTimer();

	pTimer->SetPosition(pos);

	pTimer->Init( ptexFileName, scaleWidth, scaleHeight );

	return pTimer;
}
