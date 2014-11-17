#pragma warning(disable:4996)
//�w�b�_�[�C���N���[�h
#include "CScene3D.h"
#include <cmath>
#include <stdio.h>
#include "texture.h"
#include "Input.h"

#define POS_MARGIN_X	(50)
#define POS_MARGIN_Y	(50)

int g_cnt = 0;

//�쐬
CScene3D* CScene3D::Create(CVector pos,char* ptexFileName,float scaleWidth,float scaleHeight)
{
	CScene3D* pScene3D = new CScene3D(0);

	pScene3D->SetPosition(pos);

	pScene3D->Init(ptexFileName,scaleWidth,scaleHeight);

	return pScene3D;

}

//������
void CScene3D::Init()
{

	m_rot = CVector(0,0,0);
	m_scl = CVector(1,1,1);

	for(int i = 0;i < 4;i++)
	{
		m_vtx[i].SetValue(0,m_pos.GetY(),0);
	}

	//�Ίp���̒���
	m_fLength = sqrtf(POS_MARGIN_X*POS_MARGIN_X+POS_MARGIN_Y*POS_MARGIN_Y);
	//�Ίp���̊p�x
	m_fAngle  = atan2((float)POS_MARGIN_X,(float)POS_MARGIN_Y);

	//����
	m_vtx[0].SetX(m_pos.GetX() - sinf(-m_rot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[0].SetZ(m_pos.GetZ() + cosf(-m_rot.GetZ()+m_fAngle)*m_fLength);
	//����
	m_vtx[1].SetX(m_pos.GetX() - sinf(m_rot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[1].SetZ(m_pos.GetZ() - cosf(m_rot.GetZ()+m_fAngle)*m_fLength);
	//�E��
	m_vtx[2].SetX(m_pos.GetX() + sinf(m_rot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[2].SetZ(m_pos.GetZ() + cosf(m_rot.GetZ()+m_fAngle)*m_fLength);
	//�E��
	m_vtx[3].SetX(m_pos.GetX() + sinf(-m_rot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[3].SetZ(m_pos.GetZ() - cosf(-m_rot.GetZ()+m_fAngle)*m_fLength);
	
	//�e�N�X�`���ǂݍ���
	m_texture	= LoadTexture("data\\texture\\witch3.tga");
}
//�������I�[�o�[���[�h
void CScene3D::Init(char* ptexFileName,float scaleWidth,float scaleHeight)
{
	//�e�N�X�`���ǂݍ���
	m_texture	= CreateTexture(ptexFileName);

	m_rot = CVector(0,0,0);
	m_scl = CVector(1,1,1);

	for(int i = 0;i < 4;i++)
	{
		m_vtx[i].SetValue(0,m_pos.GetY(),0);
	}

	//�Ίp���̒���
	m_fLength = sqrtf(scaleWidth*scaleWidth+scaleHeight*scaleHeight);

	//�Ίp���̊p�x
	m_fAngle  = atan2(scaleWidth,scaleHeight);

	//����
	m_vtx[0].SetX(m_pos.GetX() - sinf(-m_rot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[0].SetZ(m_pos.GetZ() + cosf(-m_rot.GetZ()+m_fAngle)*m_fLength);
	//����
	m_vtx[1].SetX(m_pos.GetX() - sinf(m_rot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[1].SetZ(m_pos.GetZ() - cosf(m_rot.GetZ()+m_fAngle)*m_fLength);
	//�E��
	m_vtx[2].SetX(m_pos.GetX() + sinf(m_rot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[2].SetZ(m_pos.GetZ() + cosf(m_rot.GetZ()+m_fAngle)*m_fLength);
	//�E��
	m_vtx[3].SetX(m_pos.GetX() + sinf(-m_rot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[3].SetZ(m_pos.GetZ() - cosf(-m_rot.GetZ()+m_fAngle)*m_fLength);
}
//�J��
void CScene3D::Uninit()
{
	glDeleteTextures(1,&m_texture);
	Release();
}
//�X�V
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
//�`��
void CScene3D::Draw()
{

	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	//3D�p�}�g���N�X�ݒ�
	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();//�v�b�V��
			


	glRotatef(m_rot.m_Vector.z,0,0,1);
	glRotatef(m_rot.m_Vector.y,0,1,0);
	glRotatef(m_rot.m_Vector.x,1,0,0);
	//�e�N�X�`���Z�b�g
	glBindTexture(GL_TEXTURE_2D,m_texture);
	
	//�`��J�n
	glBegin(GL_TRIANGLE_STRIP);
	//��������͐F�A���_�e�N�X�`����
	//�F�w��
	glColor4f(1.0f,1.0f,1.0f,1.0f);
	//���_�ʒu�ݒ�
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

	//�`��I��
	glEnd();
	//�e�N�X�`���J��
	glBindTexture(GL_TEXTURE_2D,0);

	glPopMatrix();	//�|�b�v
	
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
}

