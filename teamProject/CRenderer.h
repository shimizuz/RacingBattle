//���d��`�h�~
#ifndef __CRENDERER_H__
#define __CRENDERER_H__


//�w�b�_�[�C���N���[�h
#include "main.h"
//�}�N��

//�O���錾
class CScene;
class CCameraGL;

//�N���X��`
class CRenderer
{
private:
	HDC			m_dc;
	HGLRC		m_glRC;
	HWND		m_hWnd;
	CCameraGL*	m_Camera;
public:

	CRenderer();
	virtual ~CRenderer();

	bool Init(HWND hWnd);
	void Update();
	void Uninit();
	void Draw();
};
#endif