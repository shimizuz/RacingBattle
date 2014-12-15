//==============================================================================
//
// 当たり判定管理
// Author : Masahiro Yamaguchi
//==============================================================================
//==============================================================================
//多重定義防止
//==============================================================================
#ifndef __CCOLIDER_H__
#define __CCOLIDER_H__

//==============================================================================
//ヘッダーインクルード
//==============================================================================
#include <cmath>
#include "Class_Vector.h"
#include "CGame.h"

//==============================================================================
//クラス定義
//==============================================================================
namespace Colider
{
	//球の当たり判定
	bool SpherColider(float x1, float y1,float z1, float r1, float x2, float y2,float z2, float r2)
	{
		return (pow(x2-x1,2) + pow(y2-y1,2) + pow(z2-z1,2)) < pow(r1 + r2,2);
	}
	//円の当たり判定
	bool CircleColider(float x1, float y1, float r1, float x2, float y2, float r2)
	{
		return (pow(x2-x1,2) + pow(y2-y1,2) < pow(r1 + r2,2));
	}
	//当たり判定する場所を判定
	float GetHeightColider(CVector pos,CVector* pNormal,int blockNum,int size)
	{
		CVector Vec0,Vec1;
		CVector tmpVec(0,0,0);
		float fPosX,fPosZ;
		float fpx,fpz;
		CVector p(0,0,0);
		CVector colVector[4];


		p = pos;
	//	p.x -= 500;
	//	p.z += 500;
	/*
		if(pos.x <= 0)
		{
			pos.x += 500.0f;
		}
		if(pos.z <= 0)
		{
			pos.z += 500.0f;
		}
	*/
		fpx = p.m_Vector.x/size;
		fpz = p.m_Vector.z/size;
		fPosX = p.m_Vector.x/size;
		fPosZ = p.m_Vector.z/size;
	///*
		if(fPosX <= 0)
		{
			fPosX *= -1.0f;
		}
		if(fPosZ <= 0)
		{
			fPosZ *= -1.0f;
		}
	//*/
		int nNum = static_cast<int>(fPosZ)*(blockNum+1) + static_cast<int>(fPosX);
		int nNum1 = (static_cast<int>(fPosZ)+1)*(blockNum+1) + static_cast<int>(fPosX);
	
	//	CDebugProc::Print("実際X%f 実際Z%f\n",fpx,fpz);
	//	CDebugProc::Print("現在X%f 現在Z%f\n",fPosX,fPosZ);
		/*
		//TODO：ここをどうにかする
		colVector[0] = CGame::GetCMeshFieldGL()->[nNum];
		colVector[1] = CGame::GetCMeshFieldGL()-[nNum+1];
		colVector[2] = CGame::GetCMeshFieldGL()-[nNum1];
		colVector[3] = CGame::GetCMeshFieldGL()-[nNum1+1];

		Vec0 = colVector[0] - colVector[2];
		Vec1 = pos - colVector[2];
		//左側
		if(Vec0.m_Vector.z * Vec1.m_Vector.x - Vec0.m_Vector.x * Vec1.m_Vector.z >= 0)
		{
			Vec0 = colVector[3] - colVector[0];
			Vec1 = pos - colVector[0];
			if(Vec0.m_Vector.z * Vec1.m_Vector.x - Vec0.m_Vector.x * Vec1.m_Vector.z >= 0)
			{
				Vec0 = colVector[2] - colVector[3];
				Vec1 = pos - colVector[3];
				if(Vec0.m_Vector.z * Vec1.m_Vector.x - Vec0.m_Vector.x * Vec1.m_Vector.z >= 0)
				{
					return GetHeightPolygon(colVector[2],colVector[0],colVector[3],pos,pNormal,0,m_norVector[2],m_norVector[0],m_norVector[3]);
				}
			}
		}

		//右側
		Vec0 = colVector[0] - colVector[3];
		Vec1 = pos - colVector[3];	
		if(Vec0.m_Vector.z * Vec1.m_Vector.x - Vec0.m_Vector.x * Vec1.m_Vector.z >= 0)
		{
			Vec0 = colVector[1] - colVector[0];
			Vec1 = pos - colVector[0];
			if(Vec0.m_Vector.z * Vec1.m_Vector.x - Vec0.m_Vector.x * Vec1.m_Vector.z >= 0)
			{
				Vec0 = colVector[3] - colVector[1];
				Vec1 = pos - colVector[1];
				if(Vec0.m_Vector.z * Vec1.m_Vector.x - Vec0.m_Vector.x * Vec1.m_Vector.z >= 0)
				{
					return GetHeightPolygon(colVector[1],colVector[0],colVector[3],pos,pNormal,1,m_norVector[1],m_norVector[0],m_norVector[3]);
				}
			}
		}
		*/
		return 0.0f;
	}
	//個々の当たり判定
	float GetHeightPolygonColider(CVector& p0,CVector& p1,CVector& p2,CVector& pos,CVector* pNormal,int nNum,CVector& n0,CVector& n1,CVector& n2)
	{
		CVector Vec0,Vec1;
		CVector tmpNormal;

		Vec0 = p1 - p0;
		Vec1 = p2 - p0;
		float fHeight = 0.0f;

		//外積
		tmpNormal = Vec0.Cross(Vec1,false);
		//正規化
		tmpNormal.Normalize();
		n0.m_Vector.y*=-1;
		
		if(tmpNormal.m_Vector.y == 0.0f)
		{
			return 0.0f;
		}
		pNormal = &tmpNormal;

		fHeight = p0.m_Vector.y - (pNormal->m_Vector.x*(pos.m_Vector.x-p0.m_Vector.x)+pNormal->m_Vector.z*(pos.m_Vector.z-p0.m_Vector.z))/pNormal->m_Vector.y;

		return fHeight;
	}

};
#endif
//eof