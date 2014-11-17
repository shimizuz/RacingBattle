//���^�̊֐����Ӑ}�I�Ɏg�p����ׂɌx�������O����
#pragma warning (disable:4996)
//�w�b�_�[�C���N���[�h
#include	"keyinfo.h"

//�R���X�g���N�^
CKeySystem::CKeySystem(){
	
	this->KeyZeroInit();
}
//�f�X�g���N�^
CKeySystem::~CKeySystem(){
	
	this->KeyZeroInit();
}
//�����o��0�ŏ���������
void CKeySystem::KeyZeroInit(void){
	
	ZeroMemory(&this->m_KeyInfo,sizeof(KEYINFO));
	ZeroMemory(&this->m_KeyRecord,sizeof(KEYRECORD));
}

//�L�[���̏��������s��
void CKeySystem::KeyInitInfo(void){
	
	for(int i = 0;i < KEYMAX;i++){
		this->m_KeyInfo[i].now = FALSE;
		this->m_KeyInfo[i].past = FALSE;
	}

}
//�L�[���̍X�V
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
	

	
	this->UpdateKeepKeyPushInfo();			// �p�����͏��X�V
	this->UpdateDoubleKeyPushInfo();		// �A�����͏��X�V
	this->UpdateSameKeyPushInfo();			// �������͏��X�V
}
//�L�[���������u�Ԃ𔻒�
BOOL CKeySystem::GetKeyPush(int nNum){

	//�G���[�`�F�b�N
	if( nNum>=KEYMAX )	return	FALSE;
	
	if( this->m_KeyInfo[nNum].now ==TRUE && this->m_KeyInfo[nNum].past ){
		return	TRUE;
	}

	return	FALSE;

}
//�@�L�[�𗣂����u�Ԃ𔻒�
BOOL CKeySystem::GetKeyPull( int nNum ){

	//�G���[�`�F�b�N
	if( nNum>=KEYMAX )	return	FALSE;
	
	if( this->m_KeyInfo[nNum].now==FALSE && this->m_KeyInfo[nNum].past ==TRUE ){
		return	TRUE;
	}

	return	FALSE;
}

//�@�L�[������������
BOOL CKeySystem::GetKeyKeep( int nNum ){

	//�G���[�`�F�b�N
	if( nNum>=KEYMAX )	return	FALSE;

	if(this->m_KeyInfo[nNum].now == TRUE && this->m_KeyInfo[nNum].past == TRUE){
		return	TRUE;
	}

	return	FALSE;

}

//�@�L�[�𗣂����ςȂ�
BOOL CKeySystem::GetKeyFree( int nNum ){

	//�G���[�`�F�b�N
	if( nNum>=KEYMAX )	return	FALSE;

	if( this->m_KeyInfo[nNum].now == FALSE &&this->m_KeyInfo[nNum].past == FALSE){
		return	TRUE;
	}

	return	FALSE;

}

//�@�e�L�[�̌��ݏ��̎擾
BOOL CKeySystem::GetKeyNowInfo( int nNum ){

	return	this->m_KeyInfo[nNum].now;

}

//�@�e�L�[�̉ߋ����̎擾
BOOL CKeySystem::GetKeyPastInfo( int nNum ){

	return	this->m_KeyInfo[nNum].past;

}
// �p�����͏��X�V
void CKeySystem::UpdateKeepKeyPushInfo(void){
	

	int i = 0;

	// ���ݎg�p���Ă���{�^�����̏��X�V���s��
	for(i = 0 ; i < KEYMAX ; i++){

		// ����Ώۂ̃L�[�����������Ă���Ȃ�J�E���g�A�b�v����
		if(this->GetKeyKeep(i)){

			// ���E�l�ɒB���Ă���Ȃ�A���̒l�ŌŒ肷��(�����ӂ�h�~)
			if(this->m_KeyRecord[i].KeepPushCount != 255)this->m_KeyRecord[i].KeepPushCount++;

		}else{	// ����ΏۃL�[�������ꂽ��J�E���^�����Z�b�g����

			this->m_KeyRecord[i].KeepPushCount = 0;

		}

	}

	return;

}

// �A�����͏��X�V
void CKeySystem::UpdateDoubleKeyPushInfo(void){
	
	int i = 0;

	// ���ݎg�p���Ă���{�^�����̏��X�V���s��
	for(i = 0 ; i < KEYMAX ; i++){

		// �������u�Ԃ̗������P�t���[�������炷
		this->m_KeyRecord[i].DoublePushFlag <<= 1;
		
		// ���݃t���[���ł̑Ώۂ̃L�[���͂��������u�ԂȂ�O�r�b�g�ڂɃ`�F�b�N����
		if(this->GetKeyPush(i))this->m_KeyRecord[i].DoublePushFlag |= 0x1;

	}

	return;
}

// �������͏��X�V	
void CKeySystem::UpdateSameKeyPushInfo(void){
	
	int i = 0;

	// ���ݎg�p���Ă���{�^�����̏��X�V���s��
	for(i = 0 ; i < KEYMAX ; i++){
	
		// �������u�Ԃ̓��͗������P�t���[�������炷
		this->m_KeyRecord[i].SamePushFlag <<= 1;

		// ���݃t���[���ł̑Ώۂ̃L�[���͂��������u�ԂȂ�O�r�b�g�ڂɃ`�F�b�N����
		if(this->GetKeyPush(i))this->m_KeyRecord[i].SamePushFlag |= 0x1;

	}

	return;
}
// �p�����͂𒲂ׂ�
BOOL CKeySystem::GetKeepKeyPush(BYTE byKeyNum,BYTE byWait){

	// �G���[�`�F�b�N
	if(byKeyNum >= KEYMAX ||
	   byWait == 0)return FALSE;

	// �w�肵���L�[���w�肵���t���[�����p�����͂���Ă�������͐���
	if(this->m_KeyRecord[byKeyNum].KeepPushCount >= byWait)return TRUE;

	// ���͎��s
	return FALSE;
}

// �A�����͂𒲂ׂ�
BOOL CKeySystem::GetDoubleKeyPush(BYTE byKeyNum,BYTE byWait){

	int i = 0;

	// �G���[�`�F�b�N
	if(byKeyNum >= KEYMAX ||byWait <= 1 ||byWait >= KEYRECORDMAX)return FALSE;

	// �w�肳�ꂽ�t���[���Ԃ̘A�����͏��𒲂ׂ�
	for(i = 0 ; i < byWait ; i++){

		// �w�肵���t���[���ԓ��Ɉ�x�ڂ̎w�肵���L�[�̓��͂����������𒲂ׂ�
		if((this->m_KeyRecord[byKeyNum].DoublePushFlag >> i) & 0x1){

			// ��x�ڂ̓��͂����������̃t���[������w�肳�ꂽ�t���[���Ԃ̓��͏��𒲂ׂ�
			for(i = (i + 1) ; i < byWait ; i++){

				// �w�肵���t���[���ԓ��ɓ�x�ڂ̎w�肵���L�[�̓��͂����������𒲂ׂ�
				if((this->m_KeyRecord[byKeyNum].DoublePushFlag >> i) & 0x1){

					// ��x�ڂ̓��͂����������_�ŗ��������Z�b�g����
					this->m_KeyRecord[byKeyNum].DoublePushFlag = 0;

					// ���͐���
					return TRUE;

				}

			}

			// ��x�ڂ̓��͂��Ȃ������玸�s
			return FALSE;

		}

	}

	// ��x�ڂ̓��͂��Ȃ������玸�s
	return FALSE;
}

// �������͂𒲂ׂ�
BOOL CKeySystem::GetSameKeyPush(BYTE byKeyNum1,BYTE byKeyNum2,BYTE byWait){

	int i = 0;
	BYTE byPushCheck = 0;			// �������̓`�F�b�N�p

	// �G���[�`�F�b�N
	if(byKeyNum1 >= KEYMAX ||
	   byKeyNum2 >= KEYMAX ||
	   byKeyNum1 == byKeyNum2 ||
	   byWait == 0 ||
	   byWait > KEYRECORDMAX)return FALSE;

	// �w�肳�ꂽ�t���[���Ԃ̓������͏��𒲂ׂ�
	for(i = 0 ; i < byWait ; i++){

		// �w�肵���t���[���ԓ��Ɉ�ڂ̃L�[�̓��͂����������𒲂ׂ�
		if((this->m_KeyRecord[byKeyNum1].SamePushFlag >> i) & 0x1){
		
			// ���͂���������O�r�b�g�ڂɃ`�F�b�N����
			byPushCheck |= 0x1;

		}

		// �w�肵���t���[���ԓ��Ɉ�ڂ̃L�[�̓��͂����������𒲂ׂ�
		if((this->m_KeyRecord[byKeyNum2].SamePushFlag >> i) & 0x1){
		
			// ���͂���������P�r�b�g�ڂɃ`�F�b�N����
			byPushCheck |= 0x2;

		}

	}

	// �����̃L�[�����͂���Ă��邩�𒲂ׂ�
	if((byPushCheck & 0x1) && (byPushCheck & 0x2)){

		// �������͂���Ă������_�ŗ��������Z�b�g����
		this->m_KeyRecord[byKeyNum1].SamePushFlag = 0;
		this->m_KeyRecord[byKeyNum2].SamePushFlag = 0;

		// ���͐���
		return TRUE;

	}else{	// �������͂���Ă��Ȃ���������͎��s

		return FALSE;

	}
}



