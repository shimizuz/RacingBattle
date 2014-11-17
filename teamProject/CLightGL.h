//���d��`�h�~
#ifndef __CLIGHTGL_H__
#define __CLIGHTGL_H__

//�w�b�_�[�C���N���[�h
#include "main.h"
#include "Class_Vector.h"

typedef struct _LIGHT
{
	CVector	pos;
	_COLOR	diffuse;
	_COLOR	ambient;
	_COLOR	specular;
}LIGHT,*LPLIGHT;

//�N���X��`
class CLightGL
{
private:
	_LIGHT m_Light;
	_LIGHT m_Light1;
public:
	CLightGL(){}
	virtual ~CLightGL(){}
	void Init();
	void SetLight();
	void SetLightParam(LIGHT light);
};
#endif