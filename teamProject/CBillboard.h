#pragma once

//�w�b�_�[�C���N���[�h
#include "main.h"
#include "CScene.h"

class CBillboard : public CScene
{
private:
	CVector m_pos;
	CVector m_rot;
	CVector m_scl;
	CVector m_vtx[4];
	float	m_fLength;
	float	m_fAngle;
	unsigned int m_texture;
public:
	CBillboard(int nPriority = 3):CScene(nPriority){}
	virtual ~CBillboard(){}

	//������
	void Init();
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
	//�g�k���ݒ�
	void SetScale(CVector scl)
	{
		m_scl = scl;
	}
	static CBillboard* Create(CVector pos,char* ptexFileName,float scaleWidth,float scaleHeight);
};
