////=============================================================================
//
// メッシュ地面の処理 [CMeshFieldGL.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//===============================================================================

//ヘッダーインクルード
#include "CMeshFiledGL.h"
#include "texture.h"

static const float height_map[11*11] = 
{
	20.0f,20.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,
	20.0f,20.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,
	20.0f,20.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,
	20.0f,20.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,
	20.0f,20.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,
	20.0f,20.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,
	20.0f,20.0f,0.0f,0.0f,0.0f,0.0f,20.0f,20.0f,20.0f,0.0f,0.0f,
	0.0f,0.0f,0.0f,0.0f,0.0f,10.0f,20.0f,30.0f,30.0f,20.0f,0.0f,
	0.0f,0.0f,0.0f,0.0f,0.0f,10.0f,20.0f,30.0f,30.0f,20.0f,0.0f,
	0.0f,0.0f,0.0f,0.0f,0.0f,10.0f,20.0f,30.0f,30.0f,0.0f,0.0f,
	0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,20.0f,20.0f,30.0f,0.0f,0.0f,
};

//生成
CMeshFieldGL* CMeshFieldGL::Create(int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ,CVector pos,CVector rot,char *pTexPath)
{
	CMeshFieldGL* pMeshField = new CMeshFieldGL(3);

	pMeshField->Init(nNumBlockX,nNumBlockZ,fSizeBlockX,fSizeBlockZ,pos,rot,pTexPath);

	return pMeshField;
}

//初期化
void CMeshFieldGL::Init(int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ,CVector pos,CVector rot,char *pTexPath)
{
	//テクスチャ読み込み
	m_texture	= CreateTexture(pTexPath);

	//総頂点数
	m_nNumVertex = (nNumBlockX+1) * (nNumBlockZ+1);
	//ポリゴン数
	m_nNumPolygon = nNumBlockX*nNumBlockZ*2+(nNumBlockZ-1)*4;
	//インデックス総数
	m_nNumVertexIndex = (nNumBlockX+1)*(nNumBlockZ+1)+(nNumBlockZ-1)*(3+nNumBlockX);

	//それぞれの値を保存
	m_nNumBlockX = nNumBlockX;
	m_nNumBlockZ = nNumBlockZ;
	m_fSizeBlockX = fSizeBlockX;
	m_fSizeBlockZ = fSizeBlockZ;

	m_pos = pos;
	m_rot = rot;

	//作業用変数
	int num = 0;
	float fPosX, fPosZ;
	float fTexU, fTexV;
	//バーテックスバッファ生成
	m_VtxBuffer = new CUSTOM_VERTEX[m_nNumVertex];
	CUSTOM_VERTEX vtx[4];
	//値の設定
	for(int i = 0;i <= m_nNumBlockZ;i++)
	{
		fTexU = 0;
		fTexV = static_cast<float>(i)/2.0f;
		for(int j = 0;j <= m_nNumBlockX;j++)
		{
			num = i * (nNumBlockX+1) + j;
			fPosX = -fSizeBlockX * nNumBlockX/2 + j*fSizeBlockX;
			fPosZ = fSizeBlockZ * nNumBlockZ/2 - i*fSizeBlockZ;
			fTexU = static_cast<float>(-j)/2.0f;

			//頂点
			m_VtxBuffer[num].x = fPosX;
			m_VtxBuffer[num].y = height_map[num];
			m_VtxBuffer[num].z = fPosZ;

			//法線
			m_VtxBuffer[num].nx = 0.0f;
			m_VtxBuffer[num].ny = 1.0f;
			m_VtxBuffer[num].nz = 0.0f;

			//色
			m_VtxBuffer[num].r = 1.0f;
			m_VtxBuffer[num].g = 1.0f;
			m_VtxBuffer[num].b = 1.0f;
			m_VtxBuffer[num].a = 1.0f;

			//テクスチャ
			m_VtxBuffer[num].tu = static_cast<float>(i);
			m_VtxBuffer[num].tv = static_cast<float>(j);

		}
	}

	//TODO：面法線作成する
	m_norBuffer = new CVector[(nNumBlockX)*(nNumBlockZ)*2];
	//作業用変数
	int Index1 = 0;
	int Index2 = 0;
	int Index3 = 0;
	int Index4 = 0;

	CVector vecFace[4];
	CVector vecCross[3];

	//面法線を算出して法線バッファに格納
	for(int i = 0,count = 0; i < nNumBlockZ; i++)
	{
		for(int j = 0; j < nNumBlockX; j++,count+=2)
		{
			//nNum = Index1,nNum1 = Index2,nNum2 = Index3,nNum3 = Index4;
			Index1 = i * (nNumBlockX+1) + j;
			Index2 = i * (nNumBlockX+1) + j+1;
			Index3 = ((i+1)*(nNumBlockX +1))+j;
			Index4 = ((i+1)*(nNumBlockX +1))+j+1;
			//norBuff		
			vecFace[0].SetValue(m_VtxBuffer[Index1].x-m_VtxBuffer[Index2].x,m_VtxBuffer[Index1].y-m_VtxBuffer[Index2].y,m_VtxBuffer[Index1].z-m_VtxBuffer[Index2].z);
			vecFace[1].SetValue(m_VtxBuffer[Index4].x-m_VtxBuffer[Index2].x,m_VtxBuffer[Index4].y-m_VtxBuffer[Index2].y,m_VtxBuffer[Index4].z-m_VtxBuffer[Index2].z);

			vecFace[2].SetValue(m_VtxBuffer[Index1].x - m_VtxBuffer[Index3].x,m_VtxBuffer[Index1].y - m_VtxBuffer[Index3].y,m_VtxBuffer[Index1].z - m_VtxBuffer[Index3].z);
			vecFace[3].SetValue(m_VtxBuffer[Index4].x - m_VtxBuffer[Index3].x,m_VtxBuffer[Index4].y - m_VtxBuffer[Index3].y,m_VtxBuffer[Index4].z - m_VtxBuffer[Index3].z);

			//外積
			vecCross[0] = vecFace[0];
			vecCross[1] = vecFace[2];
			vecCross[0] = vecCross[0].Cross(vecFace[1],FALSE);
			vecCross[1] = vecCross[1].Cross(vecFace[3],FALSE);

			//-なのでプラスにする
			//vecTmp[0].y*=-1;
			vecCross[1].m_Vector.y*=-1;
		
			m_norBuffer[count] = vecCross[0];
			m_norBuffer[count+1] = vecCross[1];			
		}
	}
///*
	Index1 = 0;
	Index2 = 0;
	Index3 = nNumBlockX*2;
	Index4 = 0;
	//隣接する頂点法線の算出
	for(int i = 0; i <= nNumBlockZ; i++)
	{
	
		for(int j = 0; j <= nNumBlockX; j++)
		{
			//nNum = Index1,nNum1 = Index2,nNum2 = Index3,nNum3 = Index4;
			Index1 = i * (nNumBlockX+1) + j;
			//▼一番上の列
			//左上
			if(i == 0 && j == 0)
			{
				vecCross[2] = m_norBuffer[(Index3*i)+(2*j)] + m_norBuffer[(Index3*i+1)+(2*j)];
				vecCross[2] = vecCross[2].Normalize();
				m_VtxBuffer[Index1].nx = vecCross[2].m_Vector.x;
				m_VtxBuffer[Index1].ny = vecCross[2].m_Vector.y;
				m_VtxBuffer[Index1].nz = vecCross[2].m_Vector.z;

				m_Vertex[0].m_Vector.x = m_VtxBuffer[Index1].x;
				m_Vertex[0].m_Vector.y = m_VtxBuffer[Index1].y;
				m_Vertex[0].m_Vector.z = m_VtxBuffer[Index1].z;
			}
			//中間
			if(i == 0 && j >= 1 && j <= nNumBlockX-1)
			{
				vecCross[2] = m_norBuffer[(Index3*i)+(2*j-1)] + m_norBuffer[(Index3*i)+(2*j)] + m_norBuffer[(Index3*i)+(2*j+1)];
				vecCross[2] = vecCross[2].Normalize();
				m_VtxBuffer[Index1].nx = vecCross[2].m_Vector.x;
				m_VtxBuffer[Index1].ny = vecCross[2].m_Vector.y;
				m_VtxBuffer[Index1].nz = vecCross[2].m_Vector.z;
				
				
			}
			//右上
			if(i == 0 && j == nNumBlockX)
			{
				vecCross[2] = m_norBuffer[(Index3*i)+(2*j-1)];
				vecCross[2] = vecCross[2].Normalize();
				
				m_VtxBuffer[Index1].nx = vecCross[2].m_Vector.x;
				m_VtxBuffer[Index1].ny = vecCross[2].m_Vector.y;
				m_VtxBuffer[Index1].nz = vecCross[2].m_Vector.z;
				
				m_Vertex[1].m_Vector.x = m_VtxBuffer[Index1].x;
				m_Vertex[1].m_Vector.y = m_VtxBuffer[Index1].y;
				m_Vertex[1].m_Vector.z = m_VtxBuffer[Index1].z;
			}
			//▼中間の列
			//中間左端
			if(i >= 1 && i <= nNumBlockZ-1 && j == 0)
			{
				vecCross[2] = m_norBuffer[Index3*i] + m_norBuffer[Index3*i+1] + m_norBuffer[(i-1)*Index3];
				vecCross[2] = vecCross[2].Normalize();
				
				m_VtxBuffer[Index1].nx = vecCross[2].m_Vector.x;
				m_VtxBuffer[Index1].ny = vecCross[2].m_Vector.y;
				m_VtxBuffer[Index1].nz = vecCross[2].m_Vector.z;
				
			}
			//中間の中間
			if(i >= 1 && i <= nNumBlockZ-1 && j >= 1 && j <= nNumBlockX-1)
			{
				vecCross[2] = m_norBuffer[(i-1)*Index3 + (2*j-2)] + m_norBuffer[(i-1)*Index3 + (2*j-1)] + m_norBuffer[(i-1)*Index3 + (2*j)] + m_norBuffer[(Index3*i)+(2*j-1)] + m_norBuffer[(Index3*i)+(2*j)] + m_norBuffer[(Index3*i)+(2*j+1)];
				vecCross[2] = vecCross[2].Normalize();
				m_VtxBuffer[Index1].nx = vecCross[2].m_Vector.x;
				m_VtxBuffer[Index1].ny = vecCross[2].m_Vector.y;
				m_VtxBuffer[Index1].nz = vecCross[2].m_Vector.z;
			}
			//中間の右端
			if(i >= 1 && i <= nNumBlockZ-1 && j == nNumBlockX)
			{
				vecCross[2] = m_norBuffer[(i-1)*Index3 + (2*j-2)] + m_norBuffer[(i-1)*Index3 + (2*j-1)] + m_norBuffer[(Index3*i)+(2*j-1)];
				vecCross[2] = vecCross[2].Normalize();
				m_VtxBuffer[Index1].nx = vecCross[2].m_Vector.x;
				m_VtxBuffer[Index1].ny = vecCross[2].m_Vector.y;
				m_VtxBuffer[Index1].nz = vecCross[2].m_Vector.z;
			}
			//▼一番下の列
			//左下
			if(i == nNumBlockZ && j == 0)
			{
				vecCross[2] = m_norBuffer[Index3*(i-1)];
				vecCross[2] = vecCross[2].Normalize();
				m_VtxBuffer[Index1].nx = vecCross[2].m_Vector.x;
				m_VtxBuffer[Index1].ny = vecCross[2].m_Vector.y;
				m_VtxBuffer[Index1].nz = vecCross[2].m_Vector.z;
				m_Vertex[2].m_Vector.x = m_VtxBuffer[Index1].x;
				m_Vertex[2].m_Vector.y = m_VtxBuffer[Index1].y;
				m_Vertex[2].m_Vector.z = m_VtxBuffer[Index1].z;
			}
			//中間
			if(i == nNumBlockZ && j >= 1 && j <= nNumBlockX-1)
			{
				vecCross[2] = m_norBuffer[Index3*(i-1) + (2*j-2)] + m_norBuffer[Index3*(i-1) + (2*j-1)] + m_norBuffer[Index3*(i-1) + (2*j)];
				vecCross[2] = vecCross[2].Normalize();
				m_VtxBuffer[Index1].nx = vecCross[2].m_Vector.x;
				m_VtxBuffer[Index1].ny = vecCross[2].m_Vector.y;
				m_VtxBuffer[Index1].nz = vecCross[2].m_Vector.z;
				
			}
			//右下
			if(i == nNumBlockZ && j == nNumBlockX)
			{
				vecCross[2] = m_norBuffer[Index3*(i-1) + (2*j-2)] + m_norBuffer[Index3*(i-1) + (2*j-1)];
				vecCross[2] = vecCross[2].Normalize();
				
				m_VtxBuffer[Index1].nx = vecCross[2].m_Vector.x;
				m_VtxBuffer[Index1].ny = vecCross[2].m_Vector.y;
				m_VtxBuffer[Index1].nz = vecCross[2].m_Vector.z;
				
				m_Vertex[3].m_Vector.x = m_VtxBuffer[Index1].x;
				m_Vertex[3].m_Vector.y = m_VtxBuffer[Index1].y;
				m_Vertex[3].m_Vector.z = m_VtxBuffer[Index1].z;
			}
		}
	}
//*/
	//インデックスバッファ生成
	m_indexBuffer = new int[m_nNumVertexIndex];

	//作業用変数
	// xIndex行xzIndex列
	int xIndex = 0;
	int yIndex = 0;
	int ind[4] = {0};
	//設定
	for(int i = 0; i < m_nNumVertexIndex; i++)
	{
		// 縮退ポリゴン点
		if(i == 2*(nNumBlockX+1)+yIndex*(2*(nNumBlockX+1)+2))
		{
			m_indexBuffer[i] =  (xIndex -1) + yIndex*(nNumBlockX+1);
			m_indexBuffer[i+1] = xIndex + (yIndex+1)*(nNumBlockX+1);

			// 段が変わる
			i += 2;
			yIndex++;
			xIndex = 0;
		}

		// 下の点
		if(i % 2 == 0)
		{
			m_indexBuffer[i] = xIndex + (yIndex+1)*(nNumBlockX+1);

		}
		// 上の点
		else
		{
			m_indexBuffer[i] = xIndex + yIndex*(nNumBlockX+1);
			xIndex++;
		}
	}


}

//開放
void CMeshFieldGL::Uninit()
{
	//バーテックスバッファ削除
	SAFE_DELETE_ARRAY(m_VtxBuffer);

	//インデックスバッファ削除
	SAFE_DELETE_ARRAY(m_indexBuffer);
}

//更新
void CMeshFieldGL::Update()
{

}

//描画
void CMeshFieldGL::Draw()
{
	//ライトを切る
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

	//3D用マトリクス設定
	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();//プッシュ

	//テクスチャセット
	glBindTexture(GL_TEXTURE_2D,m_texture);
	
	//描画開始
	glBegin(GL_TRIANGLE_STRIP);

	for(int i = 0;i < m_nNumVertexIndex;i++)
	{
		//色指定
		glColor4f(m_VtxBuffer[m_indexBuffer[i]].r,m_VtxBuffer[m_indexBuffer[i]].g,m_VtxBuffer[m_indexBuffer[i]].b,m_VtxBuffer[m_indexBuffer[i]].a);
		//法線
		glNormal3f(m_VtxBuffer[m_indexBuffer[i]].nx,m_VtxBuffer[m_indexBuffer[i]].ny,m_VtxBuffer[m_indexBuffer[i]].nz);
		//テクスチャ
		glTexCoord2f(m_VtxBuffer[m_indexBuffer[i]].tu,m_VtxBuffer[m_indexBuffer[i]].tv);
		//頂点
		glVertex3f(m_VtxBuffer[m_indexBuffer[i]].x,m_VtxBuffer[m_indexBuffer[i]].y, m_VtxBuffer[m_indexBuffer[i]].z);
	}

	//描画終了
	glEnd();
	//テクスチャ開放
	glBindTexture(GL_TEXTURE_2D,0);

	glPopMatrix();	//ポップ

	//ライトを切る
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
}
//eof