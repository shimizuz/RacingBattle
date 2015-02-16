//�uWindows Skeleton Program Sample�v
//�x����������
#pragma warning(disable:4996)

//�}�N��
#define CLASS_NAME		"AppClass"	// �E�C���h�E�̃N���X��
#define WINDOW_NAME		"OpenGL"		// �E�C���h�E�̃L���v�V������



//Windows�p�̃w�b�_�[�t�@�C�����C���N���[�h

#include "main.h"
#include <windows.h>
#include <commctrl.h>
#include <string>
#include "CRenderer.h"
#include "CScene.h"
#include "CPhase.h"
#include "CPhaseFactory.h"
#include "CManager.h"

//�E�B���h�E�v���V�[�W���֐��̃v���g�^�C�v�錾
LRESULT	CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
BOOL	CALLBACK AboutDlgProc(HWND Dialog,UINT Msg,WPARAM wParam,LPARAM lParam);
BOOL GetFileName( HWND hDlgWnd, char *lpszFullPath, int nPathLength,char *lpszFilter,char *lpszDefExt );

//�O���[�o���ϐ��錾
LPSTR lpszWinClsName = "Window Sample";		//�E�B���h�E�N���X��
LPSTR lpszWinTitle = "Skeleton Program Sample"; //�E�B���h�E�^�C�g����
char fileName[ 256 ] = {0};
char g_mobFileName[256] = {0};
char g_texFileName[256] = {0};
BOOL g_fActive = FALSE;

#ifdef _DEBUG
int					g_nCountFPS;			// FPS�J�E���^
#endif
float				g_angle=0.0f;
HDC dc;
HGLRC glRC;
HWND hWnd;
int g_posX= 0,g_posY = 0,g_posZ = 0;
int g_sclX = 1,g_sclY = 1,g_sclZ = 1;
//=============================================================================
// ���C���֐�
//  (WINAPI : Win32API�֐����Ăяo�����̋K��)
//  hInstance     : ���̃A�v���P�[�V�����̃C���X�^���X�n���h��(���ʎq)
//  hPrevInstance : ���NULL(16bit����̖��c��)
//  lpCmdLine     : �R�}���h���C������󂯎���������ւ̃|�C���^
//  nCmdShow      : �A�v���P�[�V�����̏����E�C���h�E�\�����@�̎w��
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszArgs,int nWinMode)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(lpszArgs);		// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j


	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	MSG			msg = {0};		//���b�Z�[�W�擾�p�̍\����
	
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	
	

	//�E�B���h�E�E�N���X�o�^���������s�����烁�b�Z�[�W�{�b�N�X��\�����ďI��������
	if(!RegisterClassEx(&wcex))
	{
		MessageBox(hWnd,"�E�B���h�E�E�N���X�o�^�Ɏ��s���܂���",
						"�G���[",MB_OK);
		return 0;
	}

	// �E�B���h�E�̍쐬
	hWnd = CreateWindowEx(0,
						CLASS_NAME,
						WINDOW_NAME,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,
						SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),
						NULL,
						NULL,
						hInstance,
						NULL);

	//�E�B���h�E�쐬�̃`�F�b�N���������s�����烁�b�Z�[�W�{�b�N�X��\�����ďI��������
	if(hWnd == NULL)
	{
		MessageBox(hWnd,"�E�B���h�E�̍쐬�Ɏ��s���܂���","�G���[",MB_OK);
		return 0;
	}
	
	//�t���[���J�E���g������
	timeBeginPeriod(1);	// ����\��ݒ�
	dwExecLastTime = dwFPSLastTime = timeGetTime();
	dwCurrentTime = dwFrameCount = 0;
	
	
	//�E�B���h�E�\��
	ShowWindow(hWnd,nWinMode);
	//�E�B���h�E�̈�̍X�V
	UpdateWindow(hWnd);
	//������
	CManager* pManager = new CManager();

	pManager->Init(hWnd);

	// ���b�Z�[�W���[�v
	while(true)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			dwCurrentTime = timeGetTime();
			if((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5�b���ƂɎ��s
			{
#ifdef _DEBUG
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
#endif
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;
				

				// �X�V����
				pManager->Updata();
				// �`�揈��
				pManager->Draw();

				dwFrameCount++;
			}
		}
	}
	
	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// �I������
	pManager->Uninit();
	//�J��
	SAFE_DELETE(pManager);

	timeEndPeriod(1);				// ����\��߂�

	return msg.wParam;		//�I�����̖߂�l
}

//=============================================================================
// �E�C���h�E�v���V�[�W��
//  (CALLBACK : Win32API�֐����Ăяo�����̋K��)
//  hWnd   : �E�B���h�E�̃n���h��
//  uMsg   : ���b�Z�[�W�̎��ʎq
//  wParam : ���b�Z�[�W�̍ŏ��̃p�����[�^
//  lParam : ���b�Z�[�W��2�Ԗڂ̃p�����[�^
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{

	int resourceId;
	POINT pt = {0,0};
	HMENU hMenu = NULL;
	HMENU hSubMenu = NULL;
	HWND  hDlgWnd = NULL;

//	OPENFILENAME of;
	
	char texName[256] = {0};
	char defDir[256] = {0};
	char tmpFile[256] = {"\\data\\model\\"};
	char tmpFile1[256] = {"robo.tga"};
	int  ret = 0;

	switch(message)
	{
	case WM_KEYDOWN:
		if(wParam==VK_ESCAPE){
			//WM_DESTROY���b�Z�[�W�𔭐�������
			DestroyWindow(hWnd);
		};
		
		if( wParam==VK_ESCAPE )		DestroyWindow( hWnd );
		break;
	case WM_DESTROY:
		PostQuitMessage(0);		//�E�B���h�E�j���̃��b�Z�[�W
		break;
	case WM_COMMAND:
		resourceId = LOWORD(wParam);
		break;
	case WM_ACTIVATEAPP:
		g_fActive = (BOOL)wParam;
		break;
	case WM_RBUTTONDOWN:
		
		break;
	case WM_LBUTTONDOWN:
		{
			break;
			
		}
		//�I���̃��b�Z�[�W�𑗂�
	default: //���̑��̃��b�Z�[�W
		//Windows�W���̏������s��
		return DefWindowProc(hWnd,message,wParam,lParam);
	}
	return 0;	//�E�B���h�E�v���V�[�W���̖߂�l
}
//�_�C�A���O�v���V�[�W��
BOOL CALLBACK AboutDlgProc(HWND Dialog,UINT Msg,WPARAM wParam,LPARAM lParam)
{

	
	return FALSE;
}
//�ǂݍ���
BOOL GetFileName( HWND hDlgWnd, char *lpszFullPath, int nPathLength,char *lpszFilter,char *lpszDefExt )
{

	//�G���[�`�F�b�N
//	if( lpszFullPath == NULL )	return FALSE;
	if( nPathLength <= 0 )		return FALSE;

	OPENFILENAME	ofn;
	char			FileName[256] = "�t�@�C�����J��";
	char			Dir[256] = {0};

	memset( &ofn, 0,sizeof( OPENFILENAME ) );

	//�t�@�C�����i�[����N���A�ɂ���
	memset( lpszFullPath,0,sizeof(char)*256);
	memset( Dir,0,sizeof(char)*256);
	/*
	if( lpszFullPath != NULL )
	{
		ZeroMemory( lpszFullPath, sizeof(char)*nPathLength );
	}
	*/
	GetCurrentDirectory( 256, Dir );					//���݂̃f�B���N�g���̃p�X�擾

	//OPENFILENAME�\���̂ւ̐ݒ�
	ofn.lStructSize = sizeof(OPENFILENAME);				//���g�̃T�C�Y
	ofn.lpstrInitialDir = Dir;							//�f�B���N�g���w��
	ofn.hwndOwner = hDlgWnd;							//�E�B���h�E�n���h��
	ofn.nFilterIndex = 1;								//�t�@�C���t�B���^��
	ofn.lpstrDefExt = lpszDefExt;						//�g���q
	ofn.Flags = OFN_FILEMUSTEXIST;//OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT;	//�t���O
	ofn.nMaxFile = nPathLength;							//�t���p�X��������f�[�^��
	ofn.nMaxFileTitle = 256;							//�t�@�C�����̃f�[�^�T�C�Y
	ofn.lpstrFilter = lpszFilter;						//�t�@�C���t�B���^
	ofn.lpstrFile = lpszFullPath;						//�t���p�X��������f�[�^
	ofn.lpstrFileTitle = FileName;						//�t�@�C����������f�[�^
	

	//�_�C�A���O�N��
	return (BOOL)GetOpenFileName( &ofn );
}
HWND GethWnd()
{
	return hWnd;
}
BOOL GetActive()
{
	return g_fActive;
}

//eof