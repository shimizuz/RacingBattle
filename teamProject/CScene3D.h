//���d��`�h�~
#ifndef __CSCENE3D_H__
#define __CSCENE3D_H__

//�w�b�_�[�C���N���[�h
#include "main.h"
#include "CScene.h"

//�O���錾
class CRender;

//�N���X��`
class CScene3D:public CScene
{
private:
	float	m_fLength;
	float	m_fAngle;
	CVector m_pos;
	CVector m_rot;
	CVector m_scl;
	CVector m_vtx[4];
	unsigned int m_texture;

public:
	CScene3D(int nPriority = 3):CScene(nPriority){}
	virtual ~CScene3D(){}

	//������
	void Init();
	//�������I�[�o�[���[�h
	void Init(char* ptexFileName,float scaleWidth,float scaleHeight);
	//�X�V
	void Update();
	//�J��
	void Uninit();
	//�`��
	void Draw();
	
	//���W�擾
	CVector GetPosition(void)
	{
		return m_pos;
	}
	//���W�ݒ�
	void SetPosition(CVector pos)
	{
		m_pos = pos;	
	}
	//��]�擾
	CVector GetRotate(void)
	{
		return m_rot;
	}
	//��]�ݒ�
	void SetRotate(CVector rot)
	{
		m_rot = rot;	
	}
	//�g�k�擾
	CVector GetScale(void)
	{
		return m_scl;
	}
	//�g�k�ݒ�
	CVector SetScale(CVector scl)
	{
		m_scl = scl;
	}
	static CScene3D* Create(CVector pos,char* ptexFileName,float scaleWidth,float scaleHeight);
};

#endif