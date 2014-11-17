#pragma warning(disable:4996)
//�w�b�_�[�C���N���[�h
#include "CScene2D.h"
#include <cmath>
#include <stdio.h>
#include "texture.h"

#define POS_MARGIN_X	(50)
#define POS_MARGIN_Y	(50)

//�쐬
CScene2D* CScene2D::Create(CVector pos,char* ptexFileName,float scaleWidth,float scaleHeight)
{
	CScene2D* pScene2D = new CScene2D();

	pScene2D->SetPosition(pos);

	pScene2D->Init(ptexFileName,scaleWidth,scaleHeight);

	return pScene2D;

}
//������
void CScene2D::Init()
{
	m_rot = CVector(0,0,0);
	m_scl = CVector(1,1,1);

	//���_�f�[�^
	for(int i = 0;i < 4;i++)
	{
		m_vtx[i].SetValue(0,0,0);
	}

	//�Ίp���̒���
	m_fLength = sqrtf(POS_MARGIN_X*POS_MARGIN_X+POS_MARGIN_Y*POS_MARGIN_Y);
	//�Ίp���̊p�x
	m_fAngle  = atan2((float)POS_MARGIN_X,(float)POS_MARGIN_Y);

	//����
	m_vtx[0].SetX(m_pos.GetX() - sinf(-m_rot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[0].SetY(m_pos.GetY() + cosf(-m_rot.GetZ()+m_fAngle)*m_fLength);
	//����
	m_vtx[1].SetX(m_pos.GetX() - sinf(m_rot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[1].SetY(m_pos.GetY() - cosf(m_rot.GetZ()+m_fAngle)*m_fLength);
	//�E��
	m_vtx[2].SetX(m_pos.GetX() + sinf(m_rot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[2].SetY(m_pos.GetY() + cosf(m_rot.GetZ()+m_fAngle)*m_fLength);
	//�E��
	m_vtx[3].SetX(m_pos.GetX() + sinf(-m_rot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[3].SetY(m_pos.GetY() - cosf(-m_rot.GetZ()+m_fAngle)*m_fLength);

	//�e�N�X�`���ǂݍ���
	m_texture	= LoadTexture("data\\texture\\witch3.tga");

}
//�������I�[�o�[���[�h
void CScene2D::Init(char* ptexFileName,float scaleWidth,float scaleHeight)
{
	//�e�N�X�`���ǂݍ���
	m_texture	= CreateTexture(ptexFileName);

	m_rot = CVector(0,0,0);
	m_scl = CVector(1,1,1);

	m_pos.m_Vector.x += scaleWidth;
	m_pos.m_Vector.y += scaleHeight; 

	for(int i = 0;i < 4;i++)
	{
		m_vtx[i].SetValue(0,m_pos.GetY(),0);
	}

	//�Ίp���̒���
	m_fLength = sqrtf(scaleWidth*scaleWidth+scaleHeight*scaleHeight);

	//�Ίp���̊p�x
	m_fAngle  = atan2((float)scaleWidth,(float)scaleHeight);

	//����
	m_vtx[0].SetX(m_pos.GetX() - sinf(-m_rot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[0].SetY(m_pos.GetY() + cosf(-m_rot.GetZ()+m_fAngle)*m_fLength);
	//����
	m_vtx[1].SetX(m_pos.GetX() - sinf(m_rot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[1].SetY(m_pos.GetY() - cosf(m_rot.GetZ()+m_fAngle)*m_fLength);
	//�E��
	m_vtx[2].SetX(m_pos.GetX() + sinf(m_rot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[2].SetY(m_pos.GetY() + cosf(m_rot.GetZ()+m_fAngle)*m_fLength);
	//�E��
	m_vtx[3].SetX(m_pos.GetX() + sinf(-m_rot.GetZ()+m_fAngle)*m_fLength);
	m_vtx[3].SetY(m_pos.GetY() - cosf(-m_rot.GetZ()+m_fAngle)*m_fLength);

}
//�J��
void CScene2D::Uninit()
{
	glDeleteTextures(1,&m_texture);
	Release();
}
//�X�V
void CScene2D::Update()
{

}
//�`��
void CScene2D::Draw()
{
	//���C�e�B���O����
	glDisable(GL_LIGHTING);

	//2D�p�}�g���N�X�ݒ�
	glMatrixMode(GL_PROJECTION);
	glPushMatrix(); //�ۑ�glPopMatrix();����
	glLoadIdentity();
	glOrtho(0,SCREEN_WIDTH,SCREEN_HEIGHT,0,0,1);
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//�e�N�X�`���Z�b�g
	glBindTexture(GL_TEXTURE_2D,m_texture);
	

	//�`��J�n
	glBegin(GL_TRIANGLE_STRIP);

	//��������͐F�A���_�e�N�X�`����
	//�F�w��
	glColor4f(1.0f,1.0f,1.0f,1.0f);
	//���_�ʒu�ݒ�
	glTexCoord2f(0,0);
	glVertex3f(m_vtx[1].GetX(), m_vtx[1].GetY(), m_vtx[1].GetZ());
	glTexCoord2f(0,1);
	glVertex3f(m_vtx[0].GetX(), m_vtx[0].GetY(), m_vtx[0].GetZ());
	glTexCoord2f(1,0);
	glVertex3f(m_vtx[3].GetX(), m_vtx[3].GetY(), m_vtx[3].GetZ());
	glTexCoord2f(1,1);
	glVertex3f(m_vtx[2].GetX(), m_vtx[2].GetY(), m_vtx[2].GetZ());

	//�`��I��
	glEnd();
	//�e�N�X�`���J��
	glBindTexture(GL_TEXTURE_2D,0);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	
}

