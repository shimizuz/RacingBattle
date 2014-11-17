#ifndef __CSCENE2D_H__
#define __CSCENE2D_H__

#include "main.h"
#include "CScene.h"

//�O���錾
class CRender;

//�N���X��`
class CScene2D:public CScene
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
	CScene2D(int nPriority = 6):CScene(nPriority){}
	virtual ~CScene2D(){}

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
	static CScene2D* Create(CVector pos,char* ptexFileName,float scaleWidth,float scaleHeight);
};
#endif