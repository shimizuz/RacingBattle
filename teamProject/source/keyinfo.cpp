//旧型の関数を意図的に使用する為に警告を除外する
#pragma warning (disable:4996)
//ヘッダーインクルード
#include	"keyinfo.h"

//コンストラクタ
CKeySystem::CKeySystem(){
	
	this->KeyZeroInit();
}
//デストラクタ
CKeySystem::~CKeySystem(){
	
	this->KeyZeroInit();
}
//メンバを0で初期化する
void CKeySystem::KeyZeroInit(void){
	
	ZeroMemory(&this->m_KeyInfo,sizeof(KEYINFO));
	ZeroMemory(&this->m_KeyRecord,sizeof(KEYRECORD));
}

//キー情報の初期化を行う
void CKeySystem::KeyInitInfo(void){
	
	for(int i = 0;i < KEYMAX;i++){
		this->m_KeyInfo[i].now = FALSE;
		this->m_KeyInfo[i].past = FALSE;
	}

}
//キー情報の更新
void CKeySystem::KeyUpdateInfo(void){
	
	for( int i=0 ; i <KEYMAX ; i++ ){
		this->m_KeyInfo[i].past = this->m_KeyInfo[i].now;
	}

	for( int i=0 ; i<KEYMAX ; i++ ){
		if( HIBYTE( GetAsyncKeyState( i ) ) ){
			this->m_KeyInfo[i].now = TRUE;
		} else {
			this->m_KeyInfo[i].now = FALSE;
		}
	}
	

	
	this->UpdateKeepKeyPushInfo();			// 継続入力情報更新
	this->UpdateDoubleKeyPushInfo();		// 連続入力情報更新
	this->UpdateSameKeyPushInfo();			// 同時入力情報更新
}
//キーを押した瞬間を判定
BOOL CKeySystem::GetKeyPush(int nNum){

	//エラーチェック
	if( nNum>=KEYMAX )	return	FALSE;
	
	if( this->m_KeyInfo[nNum].now ==TRUE && this->m_KeyInfo[nNum].past ){
		return	TRUE;
	}

	return	FALSE;

}
//　キーを離した瞬間を判定
BOOL CKeySystem::GetKeyPull( int nNum ){

	//エラーチェック
	if( nNum>=KEYMAX )	return	FALSE;
	
	if( this->m_KeyInfo[nNum].now==FALSE && this->m_KeyInfo[nNum].past ==TRUE ){
		return	TRUE;
	}

	return	FALSE;
}

//　キーを押しっ放し
BOOL CKeySystem::GetKeyKeep( int nNum ){

	//エラーチェック
	if( nNum>=KEYMAX )	return	FALSE;

	if(this->m_KeyInfo[nNum].now == TRUE && this->m_KeyInfo[nNum].past == TRUE){
		return	TRUE;
	}

	return	FALSE;

}

//　キーを離しっぱなし
BOOL CKeySystem::GetKeyFree( int nNum ){

	//エラーチェック
	if( nNum>=KEYMAX )	return	FALSE;

	if( this->m_KeyInfo[nNum].now == FALSE &&this->m_KeyInfo[nNum].past == FALSE){
		return	TRUE;
	}

	return	FALSE;

}

//　各キーの現在情報の取得
BOOL CKeySystem::GetKeyNowInfo( int nNum ){

	return	this->m_KeyInfo[nNum].now;

}

//　各キーの過去情報の取得
BOOL CKeySystem::GetKeyPastInfo( int nNum ){

	return	this->m_KeyInfo[nNum].past;

}
// 継続入力情報更新
void CKeySystem::UpdateKeepKeyPushInfo(void){
	

	int i = 0;

	// 現在使用しているボタン分の情報更新を行う
	for(i = 0 ; i < KEYMAX ; i++){

		// 判定対象のキーを押し続けているならカウントアップする
		if(this->GetKeyKeep(i)){

			// 限界値に達しているなら、その値で固定する(桁あふれ防止)
			if(this->m_KeyRecord[i].KeepPushCount != 255)this->m_KeyRecord[i].KeepPushCount++;

		}else{	// 判定対象キーが離されたらカウンタをリセットする

			this->m_KeyRecord[i].KeepPushCount = 0;

		}

	}

	return;

}

// 連続入力情報更新
void CKeySystem::UpdateDoubleKeyPushInfo(void){
	
	int i = 0;

	// 現在使用しているボタン分の情報更新を行う
	for(i = 0 ; i < KEYMAX ; i++){

		// 押した瞬間の履歴を１フレーム分ずらす
		this->m_KeyRecord[i].DoublePushFlag <<= 1;
		
		// 現在フレームでの対象のキー入力が押した瞬間なら０ビット目にチェックする
		if(this->GetKeyPush(i))this->m_KeyRecord[i].DoublePushFlag |= 0x1;

	}

	return;
}

// 同時入力情報更新	
void CKeySystem::UpdateSameKeyPushInfo(void){
	
	int i = 0;

	// 現在使用しているボタン分の情報更新を行う
	for(i = 0 ; i < KEYMAX ; i++){
	
		// 押した瞬間の入力履歴を１フレーム分ずらす
		this->m_KeyRecord[i].SamePushFlag <<= 1;

		// 現在フレームでの対象のキー入力が押した瞬間なら０ビット目にチェックする
		if(this->GetKeyPush(i))this->m_KeyRecord[i].SamePushFlag |= 0x1;

	}

	return;
}
// 継続入力を調べる
BOOL CKeySystem::GetKeepKeyPush(BYTE byKeyNum,BYTE byWait){

	// エラーチェック
	if(byKeyNum >= KEYMAX ||
	   byWait == 0)return FALSE;

	// 指定したキーが指定したフレーム数継続入力されていたら入力成功
	if(this->m_KeyRecord[byKeyNum].KeepPushCount >= byWait)return TRUE;

	// 入力失敗
	return FALSE;
}

// 連続入力を調べる
BOOL CKeySystem::GetDoubleKeyPush(BYTE byKeyNum,BYTE byWait){

	int i = 0;

	// エラーチェック
	if(byKeyNum >= KEYMAX ||byWait <= 1 ||byWait >= KEYRECORDMAX)return FALSE;

	// 指定されたフレーム間の連続入力情報を調べる
	for(i = 0 ; i < byWait ; i++){

		// 指定したフレーム間内に一度目の指定したキーの入力があったかを調べる
		if((this->m_KeyRecord[byKeyNum].DoublePushFlag >> i) & 0x1){

			// 一度目の入力があった次のフレームから指定されたフレーム間の入力情報を調べる
			for(i = (i + 1) ; i < byWait ; i++){

				// 指定したフレーム間内に二度目の指定したキーの入力があったかを調べる
				if((this->m_KeyRecord[byKeyNum].DoublePushFlag >> i) & 0x1){

					// 二度目の入力があった時点で履歴をリセットする
					this->m_KeyRecord[byKeyNum].DoublePushFlag = 0;

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

// 同時入力を調べる
BOOL CKeySystem::GetSameKeyPush(BYTE byKeyNum1,BYTE byKeyNum2,BYTE byWait){

	int i = 0;
	BYTE byPushCheck = 0;			// 同時入力チェック用

	// エラーチェック
	if(byKeyNum1 >= KEYMAX ||
	   byKeyNum2 >= KEYMAX ||
	   byKeyNum1 == byKeyNum2 ||
	   byWait == 0 ||
	   byWait > KEYRECORDMAX)return FALSE;

	// 指定されたフレーム間の同時入力情報を調べる
	for(i = 0 ; i < byWait ; i++){

		// 指定したフレーム間内に一つ目のキーの入力があったかを調べる
		if((this->m_KeyRecord[byKeyNum1].SamePushFlag >> i) & 0x1){
		
			// 入力があったら０ビット目にチェックする
			byPushCheck |= 0x1;

		}

		// 指定したフレーム間内に一つ目のキーの入力があったかを調べる
		if((this->m_KeyRecord[byKeyNum2].SamePushFlag >> i) & 0x1){
		
			// 入力があったら１ビット目にチェックする
			byPushCheck |= 0x2;

		}

	}

	// 両方のキーが入力されているかを調べる
	if((byPushCheck & 0x1) && (byPushCheck & 0x2)){

		// 同時入力されていた時点で履歴をリセットする
		this->m_KeyRecord[byKeyNum1].SamePushFlag = 0;
		this->m_KeyRecord[byKeyNum2].SamePushFlag = 0;

		// 入力成功
		return TRUE;

	}else{	// 同時入力されていなかったら入力失敗

		return FALSE;

	}
}



