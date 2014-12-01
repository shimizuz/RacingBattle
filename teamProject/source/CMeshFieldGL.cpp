////=============================================================================
//
// ���b�V���n�ʂ̏��� [CMeshFieldGL.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//===============================================================================

//�w�b�_�[�C���N���[�h
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

//����
CMeshFieldGL* CMeshFieldGL::Create(int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ,CVector pos,CVector rot,char *pTexPath)
{
	CMeshFieldGL* pMeshField = new CMeshFieldGL(3);

	pMeshField->Init(nNumBlockX,nNumBlockZ,fSizeBlockX,fSizeBlockZ,pos,rot,pTexPath);

	return pMeshField;
}

//������
void CMeshFieldGL::Init(int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ,CVector pos,CVector rot,char *pTexPath)
{
	//�e�N�X�`���ǂݍ���
	m_texture	= CreateTexture(pTexPath);

	//�����_��
	m_nNumVertex = (nNumBlockX+1) * (nNumBlockZ+1);
	//�|���S����
	m_nNumPolygon = nNumBlockX*nNumBlockZ*2+(nNumBlockZ-1)*4;
	//�C���f�b�N�X����
	m_nNumVertexIndex = (nNumBlockX+1)*(nNumBlockZ+1)+(nNumBlockZ-1)*(3+nNumBlockX);

	//���ꂼ��̒l��ۑ�
	m_nNumBlockX = nNumBlockX;
	m_nNumBlockZ = nNumBlockZ;
	m_fSizeBlockX = fSizeBlockX;
	m_fSizeBlockZ = fSizeBlockZ;

	m_pos = pos;
	m_rot = rot;

	//��Ɨp�ϐ�
	int num = 0;
	float fPosX, fPosZ;
	float fTexU, fTexV;
	//�o�[�e�b�N�X�o�b�t�@����
	m_VtxBuffer = new CUSTOM_VERTEX[m_nNumVertex];
	CUSTOM_VERTEX vtx[4];
	//�l�̐ݒ�
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

			//���_
			m_VtxBuffer[num].x = fPosX;
			m_VtxBuffer[num].y = height_map[num];
			m_VtxBuffer[num].z = fPosZ;

			//�@��
			m_VtxBuffer[num].nx = 0.0f;
			m_VtxBuffer[num].ny = 1.0f;
			m_VtxBuffer[num].nz = 0.0f;

			//�F
			m_VtxBuffer[num].r = 1.0f;
			m_VtxBuffer[num].g = 1.0f;
			m_VtxBuffer[num].b = 1.0f;
			m_VtxBuffer[num].a = 1.0f;

			//�e�N�X�`��
			m_VtxBuffer[num].tu = static_cast<float>(i);
			m_VtxBuffer[num].tv = static_cast<float>(j);

		}
	}

	//TODO�F�ʖ@���쐬����
	m_norBuffer = new CVector[(nNumBlockX)*(nNumBlockZ)*2];
	//��Ɨp�ϐ�
	int Index1 = 0;
	int Index2 = 0;
	int Index3 = 0;
	int Index4 = 0;

	CVector vecFace[4];
	CVector vecCross[3];

	//�ʖ@�����Z�o���Ė@���o�b�t�@�Ɋi�[
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

			//�O��
			vecCross[0] = vecFace[0];
			vecCross[1] = vecFace[2];
			vecCross[0] = vecCross[0].Cross(vecFace[1],FALSE);
			vecCross[1] = vecCross[1].Cross(vecFace[3],FALSE);

			//-�Ȃ̂Ńv���X�ɂ���
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
	//�אڂ��钸�_�@���̎Z�o
	for(int i = 0; i <= nNumBlockZ; i++)
	{
	
		for(int j = 0; j <= nNumBlockX; j++)
		{
			//nNum = Index1,nNum1 = Index2,nNum2 = Index3,nNum3 = Index4;
			Index1 = i * (nNumBlockX+1) + j;
			//����ԏ�̗�
			//����
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
			//����
			if(i == 0 && j >= 1 && j <= nNumBlockX-1)
			{
				vecCross[2] = m_norBuffer[(Index3*i)+(2*j-1)] + m_norBuffer[(Index3*i)+(2*j)] + m_norBuffer[(Index3*i)+(2*j+1)];
				vecCross[2] = vecCross[2].Normalize();
				m_VtxBuffer[Index1].nx = vecCross[2].m_Vector.x;
				m_VtxBuffer[Index1].ny = vecCross[2].m_Vector.y;
				m_VtxBuffer[Index1].nz = vecCross[2].m_Vector.z;
				
				
			}
			//�E��
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
			//�����Ԃ̗�
			//���ԍ��[
			if(i >= 1 && i <= nNumBlockZ-1 && j == 0)
			{
				vecCross[2] = m_norBuffer[Index3*i] + m_norBuffer[Index3*i+1] + m_norBuffer[(i-1)*Index3];
				vecCross[2] = vecCross[2].Normalize();
				
				m_VtxBuffer[Index1].nx = vecCross[2].m_Vector.x;
				m_VtxBuffer[Index1].ny = vecCross[2].m_Vector.y;
				m_VtxBuffer[Index1].nz = vecCross[2].m_Vector.z;
				
			}
			//���Ԃ̒���
			if(i >= 1 && i <= nNumBlockZ-1 && j >= 1 && j <= nNumBlockX-1)
			{
				vecCross[2] = m_norBuffer[(i-1)*Index3 + (2*j-2)] + m_norBuffer[(i-1)*Index3 + (2*j-1)] + m_norBuffer[(i-1)*Index3 + (2*j)] + m_norBuffer[(Index3*i)+(2*j-1)] + m_norBuffer[(Index3*i)+(2*j)] + m_norBuffer[(Index3*i)+(2*j+1)];
				vecCross[2] = vecCross[2].Normalize();
				m_VtxBuffer[Index1].nx = vecCross[2].m_Vector.x;
				m_VtxBuffer[Index1].ny = vecCross[2].m_Vector.y;
				m_VtxBuffer[Index1].nz = vecCross[2].m_Vector.z;
			}
			//���Ԃ̉E�[
			if(i >= 1 && i <= nNumBlockZ-1 && j == nNumBlockX)
			{
				vecCross[2] = m_norBuffer[(i-1)*Index3 + (2*j-2)] + m_norBuffer[(i-1)*Index3 + (2*j-1)] + m_norBuffer[(Index3*i)+(2*j-1)];
				vecCross[2] = vecCross[2].Normalize();
				m_VtxBuffer[Index1].nx = vecCross[2].m_Vector.x;
				m_VtxBuffer[Index1].ny = vecCross[2].m_Vector.y;
				m_VtxBuffer[Index1].nz = vecCross[2].m_Vector.z;
			}
			//����ԉ��̗�
			//����
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
			//����
			if(i == nNumBlockZ && j >= 1 && j <= nNumBlockX-1)
			{
				vecCross[2] = m_norBuffer[Index3*(i-1) + (2*j-2)] + m_norBuffer[Index3*(i-1) + (2*j-1)] + m_norBuffer[Index3*(i-1) + (2*j)];
				vecCross[2] = vecCross[2].Normalize();
				m_VtxBuffer[Index1].nx = vecCross[2].m_Vector.x;
				m_VtxBuffer[Index1].ny = vecCross[2].m_Vector.y;
				m_VtxBuffer[Index1].nz = vecCross[2].m_Vector.z;
				
			}
			//�E��
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
	//�C���f�b�N�X�o�b�t�@����
	m_indexBuffer = new int[m_nNumVertexIndex];

	//��Ɨp�ϐ�
	// xIndex�sxzIndex��
	int xIndex = 0;
	int yIndex = 0;
	int ind[4] = {0};
	//�ݒ�
	for(int i = 0; i < m_nNumVertexIndex; i++)
	{
		// �k�ރ|���S���_
		if(i == 2*(nNumBlockX+1)+yIndex*(2*(nNumBlockX+1)+2))
		{
			m_indexBuffer[i] =  (xIndex -1) + yIndex*(nNumBlockX+1);
			m_indexBuffer[i+1] = xIndex + (yIndex+1)*(nNumBlockX+1);

			// �i���ς��
			i += 2;
			yIndex++;
			xIndex = 0;
		}

		// ���̓_
		if(i % 2 == 0)
		{
			m_indexBuffer[i] = xIndex + (yIndex+1)*(nNumBlockX+1);

		}
		// ��̓_
		else
		{
			m_indexBuffer[i] = xIndex + yIndex*(nNumBlockX+1);
			xIndex++;
		}
	}


}

//�J��
void CMeshFieldGL::Uninit()
{
	//�o�[�e�b�N�X�o�b�t�@�폜
	SAFE_DELETE_ARRAY(m_VtxBuffer);

	//�C���f�b�N�X�o�b�t�@�폜
	SAFE_DELETE_ARRAY(m_indexBuffer);
}

//�X�V
void CMeshFieldGL::Update()
{

}

//�`��
void CMeshFieldGL::Draw()
{
	//���C�g��؂�
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

	//3D�p�}�g���N�X�ݒ�
	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();//�v�b�V��

	//�e�N�X�`���Z�b�g
	glBindTexture(GL_TEXTURE_2D,m_texture);
	
	//�`��J�n
	glBegin(GL_TRIANGLE_STRIP);

	for(int i = 0;i < m_nNumVertexIndex;i++)
	{
		//�F�w��
		glColor4f(m_VtxBuffer[m_indexBuffer[i]].r,m_VtxBuffer[m_indexBuffer[i]].g,m_VtxBuffer[m_indexBuffer[i]].b,m_VtxBuffer[m_indexBuffer[i]].a);
		//�@��
		glNormal3f(m_VtxBuffer[m_indexBuffer[i]].nx,m_VtxBuffer[m_indexBuffer[i]].ny,m_VtxBuffer[m_indexBuffer[i]].nz);
		//�e�N�X�`��
		glTexCoord2f(m_VtxBuffer[m_indexBuffer[i]].tu,m_VtxBuffer[m_indexBuffer[i]].tv);
		//���_
		glVertex3f(m_VtxBuffer[m_indexBuffer[i]].x,m_VtxBuffer[m_indexBuffer[i]].y, m_VtxBuffer[m_indexBuffer[i]].z);
	}

	//�`��I��
	glEnd();
	//�e�N�X�`���J��
	glBindTexture(GL_TEXTURE_2D,0);

	glPopMatrix();	//�|�b�v

	//���C�g��؂�
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
}
//eof