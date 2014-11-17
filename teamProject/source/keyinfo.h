#ifndef __KEYINFO_H__
#define __KEYINFO_H__
//ヘッダファイルのインクルード
#include <windows.h>

//マクロ定義
#define	KEYMAX			(256)	//　キー総数
#define KEYRECORDMAX	(32)	//入力履歴保存数
#define KEYUSEMAX		(7)		//使用するキー総数

///// 構造体定義 /////
typedef struct tagKEYINFO
{		//　キー情報管理構造体
	BOOL	now;
	BOOL	past;
}KEYINFO;

typedef struct tagKEYRECORD
{
	BYTE KeepPushCount;				// 継続入力カウンタ
	DWORD DoublePushFlag;			// 連続入力判定フラグ
	DWORD SamePushFlag;				// 同時入力判定フラグ
}KEYRECORD,*LPKEYRECORD;


//キー情報管理用クラス
class CKeySystem
{
protected:
	KEYINFO m_KeyInfo[KEYMAX];
	KEYRECORD m_KeyRecord[KEYMAX];
public:
	//コンストラクタ
	CKeySystem();
	//デストラクタ
	~CKeySystem();
	//メンバを0で初期化する
	void KeyZeroInit(void);
	void	KeyInitInfo(void);					//　キーに関する初期化を行う
	void	KeyUpdateInfo(void);				//　毎ループごとのキー情報を更新
	BOOL	GetKeyPush( int );				//　押した「瞬間」のキー情報の取得
	BOOL	GetKeyPull( int );				//　離した「瞬間」のキー情報の取得
	BOOL	GetKeyKeep( int );				//　押し「っぱなし」のキー情報の取得
	BOOL	GetKeyFree( int );				//　離し「っぱなし」のキー情報の取得
	BOOL	GetKeyNowInfo( int );			//　各キーの現在情報の取得
	BOOL	GetKeyPastInfo( int );			//　各キーの過去情報の取得
	void	UpdateKeepKeyPushInfo(void);		//  継続入力情報更新
	void	UpdateDoubleKeyPushInfo(void);		//  連続入力情報更新
	void	UpdateSameKeyPushInfo(void);		//  同時入力情報更新
	BOOL	GetKeepKeyPush(BYTE,BYTE);		//  継続入力を調べる
	BOOL	GetDoubleKeyPush(BYTE,BYTE);	//  連続入力を調べる
	BOOL	GetSameKeyPush(BYTE,BYTE,BYTE);	//  同時入力を調べる

};
#endif