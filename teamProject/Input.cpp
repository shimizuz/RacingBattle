//旧型の関数を意図的に使用する為に警告を除外する
#pragma warning (disable:4996)
//ヘッダーインクルード
#include "Input.h"

//キーボードとジョイパッドのオブジェクト生成
//static CKeySystem g_key;
//static CJoySystem g_joy;
CInputSystem* CInputSystem::m_pInput = NULL;

CInputSystem* CInputSystem::getInstance()
{
	if(m_pInput == NULL)
	{
		m_pInput = new CInputSystem();
	}
	return m_pInput;
}
void CInputSystem::Release()
{
	if(m_pInput != NULL)
	{
		delete m_pInput;
		m_pInput = NULL;
	}
}

//コンストラクタ
CInputSystem::CInputSystem(){

	this->InputZeroInit();
	
}
//デストラクタ
CInputSystem::~CInputSystem(){
	this->InputZeroInit();
}
//メンバを0で初期化する
void CInputSystem::InputZeroInit(){
	ZeroMemory(&this->m_InputRecord,sizeof(INPUTRECORD));
}

//入力情報初期化
void CInputSystem::InputInitInfo(){
	
	//キー情報の初期化
//	g_joy.JoyInitInfo();
	this->JoyInitInfo();
	//ジョイパッド情報の初期化
//	g_key.KeyInitInfo();
	this->KeyInitInfo();	
	return;
}

//入力情報の更新
void CInputSystem::InputUpdateInfo(){
	
	//キーボード情報更新
//	g_key.KeyUpdateInfo();
	this->KeyUpdateInfo();
	//ジョイパッド情報更新
//	g_joy.JoyUpdateInfo();
	this->JoyUpdateInfo();
	//各種入力状態を更新する
	this->UpdateDoublePushInfo();
	this->UpdateKeepPushInfo();
	this->UpdateSamePushInfo();

}

//キーボードとジョイパッドのボタンを押したか調べる
BOOL CInputSystem::GetInputPush(BYTE byInputNum){

	BYTE UseKey[7] = {VK_UP,VK_DOWN,VK_LEFT,VK_RIGHT,'Z','X','C'};								// 使うキー
	BYTE UseJoyBtn[7] = {JOY_BTN1,JOY_DOWN,JOY_LEFT,JOY_RIGHT,JOY_BTN2,JOY_BTN3,JOY_BTN4};	// 使うボタン
	
	// エラーチェック
	if(byInputNum >= INPUT_MAX)return FALSE;

	// 指定されたキーが押された瞬間かを調べる
	if(byInputNum == 0){

		return (this->GetKeyPush(UseKey[byInputNum]) | this->GetJoyBtnPush(UseJoyBtn[byInputNum]));
	
	}else if(byInputNum <= 3 && byInputNum >=1){

		return (this->GetKeyPush(UseKey[byInputNum]) | this->GetJoyStkPush(UseJoyBtn[byInputNum]));

	}else{

		return (this->GetKeyPush(UseKey[byInputNum]) | this->GetJoyBtnPush(UseJoyBtn[byInputNum]));

	}
}
//キーボードのキーとジョイパッドのボタンが押しっぱなしかどうか調べる
BOOL CInputSystem::GetInputKeep(BYTE byInputNum){
	
	BYTE UseKey[7] = {VK_UP,VK_DOWN,VK_LEFT,VK_RIGHT,'Z','X','C'};								// 使うキー
	BYTE UseJoyBtn[7] = {JOY_BTN1,JOY_DOWN,JOY_LEFT,JOY_RIGHT,JOY_BTN2,JOY_BTN3,JOY_BTN4};	// 使うボタン
	
	// エラーチェック
	if(byInputNum >= INPUT_MAX)return FALSE;

	// 指定されたキーが押された瞬間かを調べる
	if(byInputNum == 0){

		return (this->GetKeyKeep(UseKey[byInputNum]) | this->GetJoyBtnKeep(UseJoyBtn[byInputNum]));
	
	}else if(byInputNum <= 3 && byInputNum >=1){

		return (this->GetKeyKeep(UseKey[byInputNum]) | this->GetJoyStkKeep(UseJoyBtn[byInputNum]));

	}else{

		return (this->GetKeyKeep(UseKey[byInputNum]) | this->GetJoyBtnKeep(UseJoyBtn[byInputNum]));

	}
}
//キーボードのキーとジョイパッドのボタンを離した瞬間かどうか調べる
BOOL CInputSystem::GetInputPull(BYTE byInputNum){
	
	BYTE UseKey[7] = {VK_UP,VK_DOWN,VK_LEFT,VK_RIGHT,'Z','X','C'};								// 使うキー
	BYTE UseJoyBtn[7] = {JOY_BTN1,JOY_DOWN,JOY_LEFT,JOY_RIGHT,JOY_BTN2,JOY_BTN3,JOY_BTN4};	// 使うボタン
	
	// エラーチェック
	if(byInputNum >= INPUT_MAX)return FALSE;

	// 指定されたキーが押された瞬間かを調べる
	if(byInputNum == 0){

		return (this->GetKeyPull(UseKey[byInputNum]) | this->GetJoyBtnPull(UseJoyBtn[byInputNum]));
	
	}else if(byInputNum <= 3 && byInputNum >=1){

		return (this->GetKeyPull(UseKey[byInputNum]) | this->GetJoyStkPull(UseJoyBtn[byInputNum]));

	}else{

		return (this->GetKeyPull(UseKey[byInputNum]) | this->GetJoyBtnPull(UseJoyBtn[byInputNum]));

	}
}
//キーボードのキーとジョイパッドのボタンを離しっぱなしかどうか調べる
BOOL CInputSystem::GetInputFree(BYTE byInputNum){
	
	BYTE UseKey[7] = {VK_UP,VK_DOWN,VK_LEFT,VK_RIGHT,'Z','X','C'};								// 使うキー
	BYTE UseJoyBtn[7] = {JOY_BTN1,JOY_DOWN,JOY_LEFT,JOY_RIGHT,JOY_BTN2,JOY_BTN3,JOY_BTN4};	// 使うボタン
	
	// エラーチェック
	if(byInputNum >= INPUT_MAX)return FALSE;

	// 指定されたキーが押された瞬間かを調べる
	if(byInputNum == 0){

		return (this->GetKeyFree(UseKey[byInputNum]) | this->GetJoyBtnFree(UseJoyBtn[byInputNum]));
	
	}else if(byInputNum <= 3 && byInputNum >=1){

		return (this->GetKeyFree(UseKey[byInputNum]) | this->GetJoyStkFree(UseJoyBtn[byInputNum]));

	}else{

		return (this->GetKeyFree(UseKey[byInputNum]) | this->GetJoyBtnFree(UseJoyBtn[byInputNum]));

	}
}
//各キーとジョイパッドの過去情報を取得
BOOL CInputSystem::GetInputPastInfo(BYTE byInputNum){
	
	BYTE UseKey[7] = {VK_UP,VK_DOWN,VK_LEFT,VK_RIGHT,'Z','X','C'};								// 使うキー
	BYTE UseJoyBtn[7] = {JOY_BTN1,JOY_DOWN,JOY_LEFT,JOY_RIGHT,JOY_BTN2,JOY_BTN3,JOY_BTN4};	// 使うボタン
	
	// エラーチェック
	if(byInputNum >= INPUT_MAX)return FALSE;

	// 指定されたキーが押された瞬間かを調べる
	if(byInputNum == 0){

		return (this->GetKeyPastInfo(UseKey[byInputNum]) | this->GetJoyBtnPastInfo(UseJoyBtn[byInputNum]));

	}else if(byInputNum <= 3 && byInputNum >=1){

		return (this->GetKeyPastInfo(UseKey[byInputNum]) | this->GetJoyStkPastInfo(UseJoyBtn[byInputNum]));

	}else{

		return (this->GetKeyPastInfo(UseKey[byInputNum]) | this->GetJoyBtnPastInfo(UseJoyBtn[byInputNum]));

	}
}
//各キーとジョイパッドの現在の情報を取得
BOOL CInputSystem::GetInputNowInfo(BYTE byInputNum){
	
	BYTE UseKey[7] = {VK_UP,VK_DOWN,VK_LEFT,VK_RIGHT,'Z','X','C'};								// 使うキー
	BYTE UseJoyBtn[7] = {JOY_BTN1,JOY_DOWN,JOY_LEFT,JOY_RIGHT,JOY_BTN2,JOY_BTN3,JOY_BTN4};	// 使うボタン
	
	// エラーチェック
	if(byInputNum >= INPUT_MAX)return FALSE;

	// 指定されたキーが押された瞬間かを調べる
	if(byInputNum == 0){

		return (this->GetKeyNowInfo(UseKey[byInputNum]) | this->GetJoyBtnNowInfo(UseJoyBtn[byInputNum]));

	}else if(byInputNum <= 3 && byInputNum >=1){

		return (this->GetKeyNowInfo(UseKey[byInputNum]) | this->GetJoyStkNowInfo(UseJoyBtn[byInputNum]));

	}else{

		return (this->GetKeyNowInfo(UseKey[byInputNum]) | this->GetJoyBtnNowInfo(UseJoyBtn[byInputNum]));

	}
}
//==========================================
//
// * UpdateKeepPushInfo関数 *
//
// 【機能】
//	継続入力情報の更新を行う
//
// 【引数】
//	なし
//	
// 【戻り値】
//	なし
//
//==========================================
void CInputSystem::UpdateKeepPushInfo(){

	int i = 0;

	// 現在使用しているボタン分の情報更新を行う
	for(i = 0 ; i < INPUT_MAX ; i++){

		// 判定対象のキーを押し続けているならカウントアップする
		if(this->GetInputKeep(i)){

			// 限界値に達しているなら、その値で固定する(桁あふれ防止)
			if(this->m_InputRecord[i].byKeepPushCount != 255)this->m_InputRecord[i].byKeepPushCount++;

		}else{	// 判定対象キーが離されたらカウンタをリセットする

			this->m_InputRecord[i].byKeepPushCount = 0;

		}

	}

	return;

}

//==========================================
//
// * GetKeepPush関数 *
//
// 【機能】
//	指定したキーが指定したフレームの間継続入力されているかを調べる
//
// 【引数】
//	第１引数：対象のキーを示す値(マクロで指定)
//	第２引数：継続入力するフレーム数
//	
// 【戻り値】
//	継続入力されている：TRUE	継続入力されていない or 不正な値を指定：FALSE
//
//==========================================
BOOL CInputSystem::GetKeepPush(BYTE byInputNum,BYTE byWait){

	// エラーチェック
	if(byInputNum >= INPUT_MAX ||
	   byWait == 0)return FALSE;

	// 指定したキーが指定したフレーム数継続入力されていたら入力成功
	if(this->m_InputRecord[byInputNum].byKeepPushCount >= byWait)return TRUE;

	// 入力失敗
	return FALSE;

}

//==========================================
//
// * UpdateDoublePushInfo関数 *
//
// 【機能】
//	連続入力情報の更新を行う
//
// 【引数】
//	なし
//	
// 【戻り値】
//	なし
//
//==========================================
void CInputSystem::UpdateDoublePushInfo(){

	int i = 0;

	// 現在使用しているボタン分の情報更新を行う
	for(i = 0 ; i < INPUT_MAX ; i++){

		// 押した瞬間の履歴を１フレーム分ずらす
		this->m_InputRecord[i].dwDoublePushFlag <<= 1;
		
		// 現在フレームでの対象のキー入力が押した瞬間なら０ビット目にチェックする
		if(this->GetInputPush(i))this->m_InputRecord[i].dwDoublePushFlag |= 0x1;

	}

	return;

}

//==========================================
//
// * GetDoublePush関数 *
//
// 【機能】
//	指定したキーが連続入力されたかを調べる
//
// 【引数】
//	第１引数：対象のキーを示す値(マクロで指定)
//	第２引数：連続入力を受け付けるフレーム数(最大３２フレーム)
//
// 【戻り値】
//	入力成功：TRUE	入力失敗 or 不正な値を指定：FALSE
//
//==========================================
BOOL CInputSystem::GetDoublePush(BYTE byInputNum,BYTE byWait){

	int i = 0;

	// エラーチェック
	if(byInputNum >= INPUT_MAX ||byWait <= 1 ||byWait >= INPUT_RECORD_MAX)return FALSE;

	// 指定されたフレーム間の連続入力情報を調べる
	for(i = 0 ; i < byWait ; i++){

		// 指定したフレーム間内に一度目の指定したキーの入力があったかを調べる
		if((this->m_InputRecord[byInputNum].dwDoublePushFlag >> i) & 0x1){

			// 一度目の入力があった次のフレームから指定されたフレーム間の入力情報を調べる
			for(i = (i + 1) ; i < byWait ; i++){

				// 指定したフレーム間内に二度目の指定したキーの入力があったかを調べる
				if((this->m_InputRecord[byInputNum].dwDoublePushFlag >> i) & 0x1){

					// 二度目の入力があった時点で履歴をリセットする
					this->m_InputRecord[byInputNum].dwDoublePushFlag = 0;

					// 入力成功
					return TRUE;

				}

			}

			// 二度目の入力がなかったら失敗
			return FALSE;

		}

	}

	// 一度目の入力がなかったら失敗
	return FALSE;
	
}

//==========================================
//
// * UpdateSamePushInfo関数 *
//
// 【機能】
//	同時入力情報の更新を行う
//
// 【引数】
//	なし
//	
// 【戻り値】
//	なし
//
//==========================================
void CInputSystem::UpdateSamePushInfo(){

	int i = 0;

	// 現在使用しているボタン分の情報更新を行う
	for(i = 0 ; i < INPUT_MAX ; i++){
	
		// 押した瞬間の入力履歴を１フレーム分ずらす
		this->m_InputRecord[i].dwSamePushFlag <<= 1;

		// 現在フレームでの対象のキー入力が押した瞬間なら０ビット目にチェックする
		if(this->GetInputPush(i))this->m_InputRecord[i].dwSamePushFlag |= 0x1;

	}

	return;

}

//==========================================
//
// * GetSamePush関数 *
//
// 【機能】
//	指定された二つのキーが同時入力されたかを調べる
//
// 【引数】
//	第１引数：一つ目の対象のキーを示す値(マクロで指定)
//　第２引数：二つ目の対象のキーを示す値(マクロで指定)	
//  第３引数：同時入力を受け付けるフレーム数(最大３２フレーム)
//
// 【戻り値】
//	入力成功：TRUE	入力失敗 or 不正な値を指定：FALSE
//
//==========================================
BOOL CInputSystem::GetSamePush(BYTE byInputNum1,BYTE byInputNum2,BYTE byWait){

	int i = 0;
	BYTE byPushCheck = 0;			// 同時入力チェック用

	// エラーチェック
	if(byInputNum1 >= INPUT_MAX ||
	   byInputNum2 >= INPUT_MAX ||
	   byInputNum1 == byInputNum2 ||
	   byWait == 0 ||
	   byWait > INPUT_RECORD_MAX)return FALSE;

	// 指定されたフレーム間の同時入力情報を調べる
	for(i = 0 ; i < byWait ; i++){

		// 指定したフレーム間内に一つ目のキーの入力があったかを調べる
		if((this->m_InputRecord[byInputNum1].dwSamePushFlag >> i) & 0x1){
		
			// 入力があったら０ビット目にチェックする
			byPushCheck |= 0x1;

		}

		// 指定したフレーム間内に一つ目のキーの入力があったかを調べる
		if((this->m_InputRecord[byInputNum2].dwSamePushFlag >> i) & 0x1){
		
			// 入力があったら１ビット目にチェックする
			byPushCheck |= 0x2;

		}

	}

	// 両方のキーが入力されているかを調べる
	if((byPushCheck & 0x1) && (byPushCheck & 0x2)){

		// 同時入力されていた時点で履歴をリセットする
		this->m_InputRecord[byInputNum1].dwSamePushFlag = 0;
		this->m_InputRecord[byInputNum2].dwSamePushFlag = 0;

		// 入力成功
		return TRUE;

	}else{	// 同時入力されていなかったら入力失敗

		return FALSE;

	}
}
