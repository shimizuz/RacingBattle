//「Windows Skeleton Program Sample」
//警告制限無視
#pragma warning(disable:4996)

//マクロ
#define CLASS_NAME		"AppClass"	// ウインドウのクラス名
#define WINDOW_NAME		"OpenGL"		// ウインドウのキャプション名



//Windows用のヘッダーファイルをインクルード

#include "main.h"
#include <windows.h>
#include <commctrl.h>
#include <string>
#include "CRenderer.h"
#include "CScene.h"
#include "CPhase.h"
#include "CPhaseFactory.h"
#include "CManager.h"

//ウィンドウプロシージャ関数のプロトタイプ宣言
LRESULT	CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
BOOL	CALLBACK AboutDlgProc(HWND Dialog,UINT Msg,WPARAM wParam,LPARAM lParam);
BOOL GetFileName( HWND hDlgWnd, char *lpszFullPath, int nPathLength,char *lpszFilter,char *lpszDefExt );

//グローバル変数宣言
LPSTR lpszWinClsName = "Window Sample";		//ウィンドウクラス名
LPSTR lpszWinTitle = "Skeleton Program Sample"; //ウィンドウタイトル名
char fileName[ 256 ] = {0};
char g_mobFileName[256] = {0};
char g_texFileName[256] = {0};
BOOL g_fActive = FALSE;

#ifdef _DEBUG
int					g_nCountFPS;			// FPSカウンタ
#endif
float				g_angle=0.0f;
HDC dc;
HGLRC glRC;
HWND hWnd;
int g_posX= 0,g_posY = 0,g_posZ = 0;
int g_sclX = 1,g_sclY = 1,g_sclZ = 1;
//=============================================================================
// メイン関数
//  (WINAPI : Win32API関数を呼び出す時の規約)
//  hInstance     : このアプリケーションのインスタンスハンドル(識別子)
//  hPrevInstance : 常にNULL(16bit時代の名残り)
//  lpCmdLine     : コマンドラインから受け取った引数へのポインタ
//  nCmdShow      : アプリケーションの初期ウインドウ表示方法の指定
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszArgs,int nWinMode)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpszArgs);		// 無くても良いけど、警告が出る（未使用宣言）


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
	MSG			msg = {0};		//メッセージ取得用の構造体
	
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	
	

	//ウィンドウ・クラス登録ただし失敗したらメッセージボックスを表示して終了させる
	if(!RegisterClassEx(&wcex))
	{
		MessageBox(hWnd,"ウィンドウ・クラス登録に失敗しました",
						"エラー",MB_OK);
		return 0;
	}

	// ウィンドウの作成
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

	//ウィンドウ作成のチェックただし失敗したらメッセージボックスを表示して終了させる
	if(hWnd == NULL)
	{
		MessageBox(hWnd,"ウィンドウの作成に失敗しました","エラー",MB_OK);
		return 0;
	}
	
	//フレームカウント初期化
	timeBeginPeriod(1);	// 分解能を設定
	dwExecLastTime = dwFPSLastTime = timeGetTime();
	dwCurrentTime = dwFrameCount = 0;
	
	
	//ウィンドウ表示
	ShowWindow(hWnd,nWinMode);
	//ウィンドウ領域の更新
	UpdateWindow(hWnd);
	//初期化
	CManager* pManager = new CManager();

	pManager->Init(hWnd);

	// メッセージループ
	while(true)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			dwCurrentTime = timeGetTime();
			if((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5秒ごとに実行
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
				

				// 更新処理
				pManager->Updata();
				// 描画処理
				pManager->Draw();

				dwFrameCount++;
			}
		}
	}
	
	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// 終了処理
	pManager->Uninit();
	//開放
	SAFE_DELETE(pManager);

	timeEndPeriod(1);				// 分解能を戻す

	return msg.wParam;		//終了時の戻り値
}

//=============================================================================
// ウインドウプロシージャ
//  (CALLBACK : Win32API関数を呼び出す時の規約)
//  hWnd   : ウィンドウのハンドル
//  uMsg   : メッセージの識別子
//  wParam : メッセージの最初のパラメータ
//  lParam : メッセージの2番目のパラメータ
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
			//WM_DESTROYメッセージを発生させる
			DestroyWindow(hWnd);
		};
		
		if( wParam==VK_ESCAPE )		DestroyWindow( hWnd );
		break;
	case WM_DESTROY:
		PostQuitMessage(0);		//ウィンドウ破棄のメッセージ
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
		//終了のメッセージを送る
	default: //その他のメッセージ
		//Windows標準の処理を行う
		return DefWindowProc(hWnd,message,wParam,lParam);
	}
	return 0;	//ウィンドウプロシージャの戻り値
}
//ダイアログプロシージャ
BOOL CALLBACK AboutDlgProc(HWND Dialog,UINT Msg,WPARAM wParam,LPARAM lParam)
{

	
	return FALSE;
}
//読み込み
BOOL GetFileName( HWND hDlgWnd, char *lpszFullPath, int nPathLength,char *lpszFilter,char *lpszDefExt )
{

	//エラーチェック
//	if( lpszFullPath == NULL )	return FALSE;
	if( nPathLength <= 0 )		return FALSE;

	OPENFILENAME	ofn;
	char			FileName[256] = "ファイルを開く";
	char			Dir[256] = {0};

	memset( &ofn, 0,sizeof( OPENFILENAME ) );

	//ファイル名格納先をクリアにする
	memset( lpszFullPath,0,sizeof(char)*256);
	memset( Dir,0,sizeof(char)*256);
	/*
	if( lpszFullPath != NULL )
	{
		ZeroMemory( lpszFullPath, sizeof(char)*nPathLength );
	}
	*/
	GetCurrentDirectory( 256, Dir );					//現在のディレクトリのパス取得

	//OPENFILENAME構造体への設定
	ofn.lStructSize = sizeof(OPENFILENAME);				//自身のサイズ
	ofn.lpstrInitialDir = Dir;							//ディレクトリ指定
	ofn.hwndOwner = hDlgWnd;							//ウィンドウハンドル
	ofn.nFilterIndex = 1;								//ファイルフィルタ数
	ofn.lpstrDefExt = lpszDefExt;						//拡張子
	ofn.Flags = OFN_FILEMUSTEXIST;//OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT;	//フラグ
	ofn.nMaxFile = nPathLength;							//フルパス名が入るデータ数
	ofn.nMaxFileTitle = 256;							//ファイル名のデータサイズ
	ofn.lpstrFilter = lpszFilter;						//ファイルフィルタ
	ofn.lpstrFile = lpszFullPath;						//フルパス名が入るデータ
	ofn.lpstrFileTitle = FileName;						//ファイル名が入るデータ
	

	//ダイアログ起動
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