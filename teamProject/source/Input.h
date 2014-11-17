#ifndef __INPUT_H__
#define __INPUT_H__

// ヘッダーインクルード 
#include "keyinfo.h"
#include "Joy.h"


// マクロ定義 
#define	INPUT_MAX		(7)			//  ゲーム中に使うボタンの最大数(十字キー4方向、4ボタン)

#define	INPUT_UP		(0)			//　上
#define	INPUT_DOWN		(1)			//　下
#define	INPUT_LEFT		(2)			//　左
#define	INPUT_RIGHT		(3)			//　右
#define	INPUT_BTN1		(4)			//　ボタン1
#define	INPUT_BTN2		(5)			//　ボタン2
#define	INPUT_BTN3		(6)			//　ボタン3
#define	INPUT_BTN4		(7)			//　ボタン4
#define	INPUT_BTN5		(8)			//　ボタン5
#define	INPUT_BTN6		(9)			//　ボタン6
#define	INPUT_BTN7		(10)		//　ボタン7
#define	INPUT_BTN8		(11)		//　ボタン8
#define	INPUT_BTN9		(12)		//　ボタン9
#define	INPUT_BTN10		(13)		//　ボタン10
#define	INPUT_BTN11		(14)		//　ボタン11
#define	INPUT_BTN12		(15)		//　ボタン12
#define	INPUT_BTN13		(16)		//　ボタン13
#define	INPUT_BTN14		(17)		//　ボタン14
#define	INPUT_BTN15		(18)		//　ボタン15
#define	INPUT_BTN16		(19)		//　ボタン16
#define	INPUT_BTN17		(20)		//　ボタン17
#define	INPUT_BTN18		(21)		//　ボタン18
#define	INPUT_BTN19		(22)		//　ボタン19
#define	INPUT_BTN20		(23)		//　ボタン20
#define	INPUT_BTN21		(24)		//　ボタン21
#define	INPUT_BTN22		(25)		//　ボタン22
#define	INPUT_BTN23		(26)		//　ボタン23
#define	INPUT_BTN24		(27)		//　ボタン24
#define	INPUT_BTN25		(28)		//　ボタン25
#define	INPUT_BTN26		(29)		//　ボタン26
#define	INPUT_BTN27		(30)		//　ボタン27
#define	INPUT_BTN28		(31)		//　ボタン28
#define	INPUT_BTN29		(32)		//　ボタン29
#define	INPUT_BTN30		(33)		//　ボタン30
#define	INPUT_BTN31		(34)		//　ボタン31
#define	INPUT_BTN32		(35)		//　ボタン32

#define INPUT_RECORD_MAX	(32)	// 入力履歴保存最大フレーム数

///// 構造体定義 /////
typedef struct tagINPUTRECORD{
	BYTE byKeepPushCount;				// 継続入力カウンタ
	DWORD dwDoublePushFlag;			// 連続入力判定フラグ
	DWORD dwSamePushFlag;				// 同時入力判定フラグ
}INPUTRECORD,*LPINPUTRECORD;


//入力情報管理用クラス
class CInputSystem :public CKeySystem ,public CJoySystem
{
private:
	static CInputSystem* m_pInput;
protected:
	INPUTRECORD m_InputRecord[INPUT_MAX];
public:
	static CInputSystem* getInstance();
	static void Release();
	CInputSystem();						// コンストラクタ
	~CInputSystem();					// デストラクタ
	void InputZeroInit();				// メンバを0で初期化する
	void InputInitInfo();				// 入力情報初期化
	void InputUpdateInfo();				// 入力情報更新
	BOOL GetInputPush(BYTE);			// 押した瞬間を調べる
	BOOL GetInputKeep(BYTE);			// 押され続けているかを調べる
	BOOL GetInputPull(BYTE);			// 離された瞬間を調べる
	BOOL GetInputFree(BYTE);			// 離され続けているかを調べる
	BOOL GetInputNowInfo(BYTE);			// 現在の入力状態を調べる
	BOOL GetInputPastInfo(BYTE);		// 過去の入力状態を調べる
	void UpdateKeepPushInfo();			// 継続入力情報更新
	void UpdateDoublePushInfo();		// 連続入力情報更新
	void UpdateSamePushInfo();			// 同時入力情報更新
	BOOL GetKeepPush(BYTE,BYTE);		// 継続入力を調べる
	BOOL GetDoublePush(BYTE,BYTE);		// 連続入力を調べる
	BOOL GetSamePush(BYTE,BYTE,BYTE);	// 同時入力を調べる
};





#endif
