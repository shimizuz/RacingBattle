//ヘッダー
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
	// OpenGL初期化
	// ピクセルフォーマット初期化
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
	//デバイスコンテキスト取得
	m_dc = GetDC(m_hWnd);
	int format = ChoosePixelFormat(m_dc, &pfd);
	if (format == 0)
		return false; // 該当するピクセルフォーマットが無い

	// OpenGLが使うデバイスコンテキストに指定のピクセルフォーマットをセット
	if (!SetPixelFormat(m_dc, format, &pfd))
		return false; // DCへフォーマットを設定するのに失敗

	// OpenGL contextを作成(OpenGLは GL contextに絵を描くHDCとリンクさせる)
	m_glRC = wglCreateContext(m_dc);

	// 作成されたコンテキストがカレント（現在使用中のコンテキスト）か？
	if (!wglMakeCurrent(m_dc, m_glRC))	//表示しようとするコンテキスト指定glRCを複数作成出来る
		return false; // 何か正しくないみたい…

	//OpenGL描画設定
	//テクスチャを有効に
	glEnable(GL_TEXTURE_2D);
	//カリング
	glEnable(GL_CULL_FACE);
//	glDisable(GL_CULL_FACE);	//カリング無効

	//深度テスト
	glEnable(GL_DEPTH_TEST);
	//ライト
	glEnable(GL_LIGHTING);

	//カメラ初期化
//	m_Camera = new CCameraGL();
//	m_Camera->Init();
	return true;
}

void CRenderer::Uninit()
{
	// 後処理
	// カレントコンテキストを無効にする
	wglMakeCurrent(NULL, NULL);

	// カレントコンテキストを削除
	wglDeleteContext(m_glRC);

	// デバイスコンテキスト解放
	ReleaseDC(m_hWnd, m_dc);
	
	//カメラ開放
//	SAFE_DELETE(m_Camera);
	//開放
	CInputSystem::Release();
}
void CRenderer::Update()
{
	//入力情報更新
	//CInputSystem::getInstance()->InputUpdateInfo();

	//カメラ更新
	//m_Camera->Update();

	//更新
	CScene::UpdateAll();

	//フェード更新
	CFade::getinstance()->Update();
}
//描画
void CRenderer::Draw()
{
	//OPENGL描画
	wglMakeCurrent(m_dc, m_glRC);
//
	//背景色指定
	glClearColor(255/101.f, 255/145.f, 255/239.f, 1.0f);	
	//背景クリア
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//▼カメラ
	CCameraGL::getInstance()->SetCamera();

	//描画
	CScene::DrawAll();

	//フェード描画
	CFade::getinstance()->Draw();

	//バックバッファに書き込む
	glFlush();
	//フロントバッファ・バックバッファの入れ替え
	SwapBuffers(m_dc);
	
}