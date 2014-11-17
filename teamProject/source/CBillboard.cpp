#include "CBillboard.h"
#include <cmath>
#include "texture.h"
#include "Class_Matrix.h"
#include "Input.h"

//����
CBillboard* CBillboard::Create(CVector pos,char* ptexFileName,float scaleWidth,float scaleHeight)
{
	CBillboard* pScene3D = new CBillboard(0);

	pScene3D->SetPosition(pos);

	pScene3D->Init(ptexFileName,scaleWidth,scaleHeight);

	

	return pScene3D;

}
//������
void CBillboard::Init()
{
	for(int i = 0;i < 4;i++)
	{
		m_vtx[i].SetValue(0,0,0);
	}

	m_rot = CVector(0,0,0);
	m_scl = CVector(1,1,1);

	//�Ίp���̒���
	m_fLength = sqrtf(50*50+50*50);
	//�Ίp���̊p�x
	m_fAngle  = atan2((float)50,(float)50);

}
//�������I�[�o�[���[�h
void CBillboard::Init(char* ptexFileName,float scaleWidth,float scaleHeight)
{
	//�e�N�X�`���ǂݍ���
	m_texture	= CreateTexture(ptexFileName);

	m_rot = CVector(0,0,0);
	m_scl = CVector(1,1,1);

	for(int i = 0;i < 4;i++)
	{
		m_vtx[i].SetValue(0,0,0);
	}

	//�Ίp���̒���
	m_fLength = sqrtf(scaleWidth*scaleWidth+scaleHeight*scaleHeight);

	//�Ίp���̊p�x
	m_fAngle  = atan2(scaleWidth,scaleHeight);

	//����
	m_vtx[1].SetX(m_pos.GetX() - sinf(-m_rot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[1].SetY(m_pos.GetY() + cosf(-m_rot.GetZ()+m_fAngle)*m_fLength);
	//����
	m_vtx[0].SetX(m_pos.GetX() - sinf(m_rot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[0].SetY(m_pos.GetY() - cosf(m_rot.GetZ()+m_fAngle)*m_fLength);
	//�E��
	m_vtx[3].SetX(m_pos.GetX() + sinf(m_rot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[3].SetY(m_pos.GetY() + cosf(m_rot.GetZ()+m_fAngle)*m_fLength);
	//�E��
	m_vtx[2].SetX(m_pos.GetX() + sinf(-m_rot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[2].SetY(m_pos.GetY() - cosf(-m_rot.GetZ()+m_fAngle)*m_fLength);
	int a = 0;
}
//�J��
void CBillboard::Uninit()
{
	Release();
}
//�X�V
void CBillboard::Update()
{

}

//�`��
void CBillboard::Draw()
{
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	//3D�p�}�g���N�X�ݒ�
	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();//�v�b�V��
			
	//�r���{�[�h�p
	MATRIX matrix,invMatrix;

	glGetFloatv(GL_MODELVIEW_MATRIX,(float*)&matrix);

	//�s��]�u
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

	//�e�N�X�`���Z�b�g
	glBindTexture(GL_TEXTURE_2D,m_texture);
	
	//�`��J�n
	glBegin(GL_TRIANGLE_STRIP);
	//��������͐F�A���_�e�N�X�`����
	//�F�w��
	glColor4f(1.0f,1.0f,1.0f,1.0f);
	//���_�ʒu�ݒ�
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

	//�`��I��
	glEnd();
	//�e�N�X�`���J��
	glBindTexture(GL_TEXTURE_2D,0);

	glPopMatrix();	//�|�b�v
	
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
}
//eof