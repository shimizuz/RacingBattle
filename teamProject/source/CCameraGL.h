//���d��`�h�~
#ifndef __CCAMERAGL_H__
#define __CCAMERAGL_H__

//�w�b�_�[�C���N���[�h
#include "main.h"
#include "Class_Vector.h"

//�O���錾
class CLightGL;

//�N���X��`
class CCameraGL
{
private:
	CVector m_posCameraP;			//���_
	CVector m_posCameraR;			//�����_
	CVector m_vecCameraUp;
	CVector m_rotCamera;
	float	m_angle;
	CLightGL* m_pLight;
	bool	m_bFlag;
	bool	m_bFlag1;
	static CCameraGL* m_Instance;

public:
	static CCameraGL* getInstance();
	static void Release();
	CCameraGL(){}
	virtual~CCameraGL(){}
	void Init(void);
	void Update(void);
	void Uninit(void);
	void SetCamera(void);
	
	//���W�擾
	CVector GetPosition(void)
	{
		return m_posCameraR;
	}
	//���W�ݒ�
	void SetPosition(CVector pos)
	{
		m_posCameraR = pos;	
	}

	//��]�擾
	CVector GetRotate(void)
	{
		return m_rotCamera;
	}
	//��]�ݒ�
	void SetRotate(CVector rot)
	{
		m_rotCamera = rot;	
	}
};

#endif