//�w�b�_�[
#include "CRenderer.h"
#include "CScene.h"
#include "Input.h"
#include "CCameraGL.h"
#include "CFade.h"

CRenderer::CRenderer(){}

CRenderer::~CRenderer(){}

bool CRenderer::Init(HWND hWnd)
{
	m_hWnd = hWnd;
	// OpenGL������
	// �s�N�Z���t�H�[�}�b�g������
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, //Flags
		PFD_TYPE_RGBA, //The kind of framebuffer. RGBA or palette.
		32, //Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		32, //Number of bits for the depthbuffer
		0, //Number of bits for the stencilbuffer
		0, //Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};
	//�f�o�C�X�R���e�L�X�g�擾
	m_dc = GetDC(m_hWnd);
	int format = ChoosePixelFormat(m_dc, &pfd);
	if (format == 0)
		return false; // �Y������s�N�Z���t�H�[�}�b�g������

	// OpenGL���g���f�o�C�X�R���e�L�X�g�Ɏw��̃s�N�Z���t�H�[�}�b�g���Z�b�g
	if (!SetPixelFormat(m_dc, format, &pfd))
		return false; // DC�փt�H�[�}�b�g��ݒ肷��̂Ɏ��s

	// OpenGL context���쐬(OpenGL�� GL context�ɊG��`��HDC�ƃ����N������)
	m_glRC = wglCreateContext(m_dc);

	// �쐬���ꂽ�R���e�L�X�g���J�����g�i���ݎg�p���̃R���e�L�X�g�j���H
	if (!wglMakeCurrent(m_dc, m_glRC))	//�\�����悤�Ƃ���R���e�L�X�g�w��glRC�𕡐��쐬�o����
		return false; // �����������Ȃ��݂����c

	//OpenGL�`��ݒ�
	//�e�N�X�`����L����
	glEnable(GL_TEXTURE_2D);
	//�J�����O
	glEnable(GL_CULL_FACE);
//	glDisable(GL_CULL_FACE);	//�J�����O����

	//�[�x�e�X�g
	glEnable(GL_DEPTH_TEST);
	//���C�g
	glEnable(GL_LIGHTING);

	//�J����������
//	m_Camera = new CCameraGL();
//	m_Camera->Init();
	return true;
}

void CRenderer::Uninit()
{
	// �㏈��
	// �J�����g�R���e�L�X�g�𖳌��ɂ���
	wglMakeCurrent(NULL, NULL);

	// �J�����g�R���e�L�X�g���폜
	wglDeleteContext(m_glRC);

	// �f�o�C�X�R���e�L�X�g���
	ReleaseDC(m_hWnd, m_dc);
	
	//�J�����J��
//	SAFE_DELETE(m_Camera);
	//�J��
	CInputSystem::Release();
}
void CRenderer::Update()
{
	//���͏��X�V
	//CInputSystem::getInstance()->InputUpdateInfo();

	//�J�����X�V
	//m_Camera->Update();

	//�X�V
	CScene::UpdateAll();

	//�t�F�[�h�X�V
	CFade::getinstance()->Update();
}
//�`��
void CRenderer::Draw()
{
	//OPENGL�`��
	wglMakeCurrent(m_dc, m_glRC);
//
	//�w�i�F�w��
	glClearColor(255/101.f, 255/145.f, 255/239.f, 1.0f);	
	//�w�i�N���A
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//���J����
	CCameraGL::getInstance()->SetCamera();

	//�`��
	CScene::DrawAll();

	//�t�F�[�h�`��
	CFade::getinstance()->Draw();

	//�o�b�N�o�b�t�@�ɏ�������
	glFlush();
	//�t�����g�o�b�t�@�E�o�b�N�o�b�t�@�̓���ւ�
	SwapBuffers(m_dc);
	
}