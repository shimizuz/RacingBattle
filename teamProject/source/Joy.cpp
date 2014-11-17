//���^�̊֐����Ӑ}�I�Ɏg�p����ׂɌx�������O����
#pragma warning (disable:4996)
//�@�w�b�_�[�t�@�C���C���N���[�h
#include	<windows.h>
#include	"Joy.h"

//�R���X�g���N�^
CJoySystem::CJoySystem(){
	
	this->JoyZeroInit();
}
//�f�X�g���N�^
CJoySystem::~CJoySystem(){
	
	this->JoyZeroInit();
	
}
//�����o��0�ŏ���������
void CJoySystem::JoyZeroInit(){
	
	ZeroMemory(&this->m_JoyButtonInfo,sizeof(JOYBUTTONINFO));
	ZeroMemory(&this->m_JoyStickInfo,sizeof(JOYSTICKINFO));
	ZeroMemory(&this->m_JoyButtonRecord,sizeof(JOYRECORD));
	ZeroMemory(&this->m_JoyStickRecord,sizeof(JOYRECORD));
	this->Flag = FALSE;
}

//�W���C�p�b�h������
void CJoySystem::JoyInitInfo(void){

	JOYINFOEX	joy;
	int			i;

	

	//�@�W���C�X�e�B�b�N���ڑ�����Ă��邩���`�F�b�N����ׂɏ��̎擾
	ZeroMemory( &joy, sizeof( joy ) );
	joy.dwSize = sizeof( joy );
	joy.dwFlags = JOY_RETURNBUTTONS | JOY_RETURNX | JOY_RETURNY;
	if( joyGetPosEx( JOYSTICKID1, &joy )!=JOYERR_NOERROR ){

		MessageBox( NULL, "�W���C�X�e�B�b�N���ڑ�����Ă��܂���", "Joy Stick Error", MB_OK );
		this->Flag = FALSE;		//�@�W���C�X�e�B�b�N�g�p�s�\���

	} else {

		//�@�W���C�X�e�B�b�N���̏�����
		for( i=0 ; i<4 ; i++ ){
			this->m_JoyStickInfo[i].now = FALSE;
			this->m_JoyStickInfo[i].past = FALSE;
		}
		//�@�{�^�����̏�����
		for( i=0 ; i<32 ; i++ ){
			this->m_JoyButtonInfo[i].now = FALSE;
			this->m_JoyButtonInfo[i].past = FALSE;
		}
		this->Flag = TRUE;			//�@�W���C�X�e�B�b�N�g�p�\���

	}
}

//�W���C�p�b�h���X�V
void CJoySystem::JoyUpdateInfo(void){

	JOYINFOEX	joy;
	int			i;

	if( this->Flag){
		//�@���݂̏����ߋ��̏��Ƃ��ĕۑ�
		//�@�\���L�[
		for( i=0 ; i<4 ; i++ ){
			this->m_JoyStickInfo[i].past = this->m_JoyStickInfo[i].now;
		}
		//�@�{�^��
		for( i=0 ; i<32 ; i++ ){
			this->m_JoyButtonInfo[i].past = this->m_JoyButtonInfo[i].now;
		}

		//	�����ݒ�
		ZeroMemory( &joy, sizeof( joy ) );
		joy.dwSize = sizeof( joy );
		joy.dwFlags = JOY_RETURNBUTTONS | JOY_RETURNX | JOY_RETURNY;
		if( joyGetPosEx( JOYSTICKID1, &joy )!=JOYERR_NOERROR ){

			MessageBox( NULL, "�W���C�X�e�B�b�N���ڑ�����Ă��܂���", "Joy Stick Error", MB_OK );
			this->Flag = FALSE;

		} else {

			//�@�\���L�[���̍X�V
			//�@��
			if( joy.dwYpos<11000 ){
				this->m_JoyStickInfo[0].now = TRUE;
			} else {
				this->m_JoyStickInfo[0].now = FALSE;
			}
			//	��
			if( joy.dwYpos>50000 ){
				this->m_JoyStickInfo[1].now = TRUE;
			} else {
				this->m_JoyStickInfo[1].now = FALSE;
			}
			//�@��
			if( joy.dwXpos<11000 ){
				this->m_JoyStickInfo[2].now = TRUE;
			} else {
				this->m_JoyStickInfo[2].now = FALSE;
			}
			//�@�E
			if( joy.dwXpos>50000 ){
				this->m_JoyStickInfo[3].now = TRUE;
			} else {
				this->m_JoyStickInfo[3].now = FALSE;
			}

			//�@�{�^�����̍X�V
			for( i=0 ; i<32 ; i++ ){
				//�@�e�r�b�g���O�r�b�g�ڂ܂ňړ����r�b�g�������Ă��邩�`�F�b�N
				if( ( joy.dwButtons>>i )&0x00000001 ){
					this->m_JoyButtonInfo[i].now = TRUE;
				} else {
					this->m_JoyButtonInfo[i].now = FALSE;
				}
			}
		}
		this->UpdateKeepJoyStkPushInfo();		//  �p�����͏��X�V
		this->UpdateKeepJoyBtnPushInfo();		//  �p�����͏��X�V
		this->UpdateDoubleJoyStkPushInfo();		//  �A�����͏��X�V
		this->UpdateSameJoyStkPushInfo();		//  �������͏��X�V
		this->UpdateDoubleJoyBtnPushInfo();		//  �A�����͏��X�V
		this->UpdateSameJoyBtnPushInfo();		//  �������͏��X�V
	}
}

//�@�\���L�[�̉������u�Ԃ̏��𓾂�֐�
BOOL CJoySystem::GetJoyStkPush( BYTE byNum ){

	if( this->Flag ){
		//�@�����̒l���v�f�𒴂��Ă�����
		if( byNum>=4 )	return	FALSE;
		
		//�@�\���L�[���u�������u�ԁv�𔻒�
		if( this->m_JoyStickInfo[ byNum ].now==TRUE && this->m_JoyStickInfo[ byNum ].past==FALSE ){
			return	TRUE;
		}
	}

	return	FALSE;

}


//�@�\���L�[�̗������u�Ԃ̏��𓾂�֐�
BOOL CJoySystem::GetJoyStkPull( BYTE byNum ){

	if( this->Flag ){
		//�@�����̒l���v�f�𒴂��Ă�����
		if( byNum>=4 )	return	FALSE;
		
		//�@�\���L�[���u�������u�ԁv�𔻒�
		if( this->m_JoyStickInfo[ byNum ].now==FALSE && this->m_JoyStickInfo[ byNum ].past==TRUE ){
			return	TRUE;
		}
	}

	return	FALSE;

}


//�@�\���L�[�̉������ςȂ��̏��𓾂�֐�
BOOL CJoySystem::GetJoyStkKeep( BYTE byNum ){

	if( this->Flag ){
		//�@�����̒l���v�f�𒴂��Ă�����
		if( byNum>=4 )	return	FALSE;
		
		//�@�\���L�[���u�������ςȂ��v�𔻒�
		if( this->m_JoyStickInfo[ byNum ].now==TRUE && this->m_JoyStickInfo[ byNum ].past==TRUE ){
			return	TRUE;
		}
	}

	return	FALSE;

}


//�@�\���L�[�̗������ςȂ��̏��𓾂�֐�
BOOL CJoySystem::GetJoyStkFree( BYTE byNum ){

	if( this->Flag ){
		//�@�����̒l���v�f�𒴂��Ă�����
		if( byNum>=4 )	return	FALSE;
		
		//�@�\���L�[���u�������ςȂ��v�𔻒�
		if( this->m_JoyStickInfo[ byNum ].now==FALSE && this->m_JoyStickInfo[ byNum ].past==FALSE ){
			return	TRUE;
		}
	}

	return	FALSE;

}


//�@�\���L�[�̌��ݏ��𓾂�֐�
BOOL CJoySystem::GetJoyStkNowInfo( BYTE byNum ){
	

	if( this->Flag ){

		return	this->m_JoyStickInfo[ byNum ].now;
	}
	
	return	FALSE;

}


//�@�\���L�[�̉ߋ����𓾂�֐�
BOOL CJoySystem::GetJoyStkPastInfo( BYTE byNum ){

	if( this->Flag ){
		return	this->m_JoyStickInfo[ byNum ].past;
	}

	return	FALSE;

}

//�@�{�^���̉������u�Ԃ̏��𓾂�֐�
BOOL CJoySystem::GetJoyBtnPush( BYTE byNum ){

	if( this->Flag ){
		//�@�����̒l���v�f�𒴂��Ă�����
		if( byNum>=32 )	return	FALSE;
		
		//�@�{�^�����u�������u�ԁv�𔻒�
		if( this->m_JoyButtonInfo[ byNum ].now==TRUE && this->m_JoyButtonInfo[ byNum ].past==FALSE ){
			return	TRUE;
		}
	}

	return	FALSE;

}

//�@�{�^���̗������u�Ԃ̏��𓾂�֐�
BOOL CJoySystem::GetJoyBtnPull( BYTE byNum ){

	if( this->Flag ){
		//�@�����̒l���v�f�𒴂��Ă�����
		if( byNum>=32 )	return	FALSE;
		
		//�@�{�^�����u�������u�ԁv�𔻒�
		if( this->m_JoyButtonInfo[ byNum ].now==FALSE && this->m_JoyButtonInfo[ byNum ].past==TRUE ){
			return	TRUE;
		}
	}

	return	FALSE;

}


//�@�{�^���̉������ςȂ��̏��𓾂�֐�
BOOL CJoySystem::GetJoyBtnKeep( BYTE byNum ){

	if( this->Flag ){
		//�@�����̒l���v�f�𒴂��Ă�����
		if( byNum>=32 )	return	FALSE;
		
		//�@�{�^�����u�������ςȂ��v�𔻒�
		if( this->m_JoyButtonInfo[ byNum ].now==TRUE && this->m_JoyButtonInfo[ byNum ].past==TRUE ){
			return	TRUE;
		}
	}

	return	FALSE;

}


//�@�{�^���̗������ςȂ��̏��𓾂�֐�
BOOL CJoySystem::GetJoyBtnFree( BYTE byNum ){

	if(this->Flag ){
		//�@�����̒l���v�f�𒴂��Ă�����
		if( byNum>=32 )	return	FALSE;
		
		//�@�{�^�����u�������ςȂ��v�𔻒�
		if( this->m_JoyButtonInfo[ byNum ].now==FALSE && this->m_JoyButtonInfo[ byNum ].past==FALSE ){
			return	TRUE;
		}
	}

	return	FALSE;

}


//�@�{�^���̌��ݏ��𓾂�֐�
BOOL CJoySystem::GetJoyBtnNowInfo( BYTE byNum ){

	if( this->Flag ){
		return	this->m_JoyButtonInfo[ byNum ].now;
	}
	
	return	FALSE;

}


//�@�{�^���̉ߋ����𓾂�֐�
BOOL CJoySystem::GetJoyBtnPastInfo( BYTE byNum ){

	if(this->Flag ){
		return	this->m_JoyButtonInfo[ byNum ].past;
	}

	return	FALSE;
}

//  �p�����͏��X�V
void CJoySystem::UpdateKeepJoyStkPushInfo(){
	
	int i = 0;

	// ���ݎg�p���Ă���{�^�����̏��X�V���s��
	for(i = 0 ; i < JOYMAX ; i++){

		// ����Ώۂ̃L�[�����������Ă���Ȃ�J�E���g�A�b�v����
		if(this->GetJoyStkKeep(i)){

			// ���E�l�ɒB���Ă���Ȃ�A���̒l�ŌŒ肷��(�����ӂ�h�~)
			if(this->m_JoyStickRecord[i].byKeepPushCount != 255)this->m_JoyStickRecord[i].byKeepPushCount++;

		}else{	// ����ΏۃL�[�������ꂽ��J�E���^�����Z�b�g����

			this->m_JoyStickRecord[i].byKeepPushCount = 0;

		}

	}

	return;
}

//  �p�����͏��X�V
void CJoySystem::UpdateKeepJoyBtnPushInfo(){

	
	int i = 0;

	// ���ݎg�p���Ă���{�^�����̏��X�V���s��
	for(i = 0 ; i < JOYMAX ; i++){

		// ����Ώۂ̃L�[�����������Ă���Ȃ�J�E���g�A�b�v����
		if(this->GetJoyBtnKeep(i)){

			// ���E�l�ɒB���Ă���Ȃ�A���̒l�ŌŒ肷��(�����ӂ�h�~)
			if(this->m_JoyButtonRecord[i].byKeepPushCount != 255)this->m_JoyButtonRecord[i].byKeepPushCount++;

		}else{	// ����ΏۃL�[�������ꂽ��J�E���^�����Z�b�g����

			this->m_JoyButtonRecord[i].byKeepPushCount = 0;

		}

	}

	return;
}

//  �A�����͏��X�V
void CJoySystem::UpdateDoubleJoyStkPushInfo(){

	int i = 0;

	// ���ݎg�p���Ă���{�^�����̏��X�V���s��
	for(i = 0 ; i < JOYMAX ; i++){

		// �������u�Ԃ̗������P�t���[�������炷
		this->m_JoyStickRecord[i].dwDoublePushFlag <<= 1;
		
		// ���݃t���[���ł̑Ώۂ̃L�[���͂��������u�ԂȂ�O�r�b�g�ڂɃ`�F�b�N����
		if(this->GetJoyStkPush(i))this->m_JoyStickRecord[i].dwDoublePushFlag |= 0x1;

	}

	return;
}

//  �A�����͏��X�V
void CJoySystem::UpdateDoubleJoyBtnPushInfo(){

	int i = 0;

	// ���ݎg�p���Ă���{�^�����̏��X�V���s��
	for(i = 0 ; i < JOYMAX ; i++){

		// �������u�Ԃ̗������P�t���[�������炷
		this->m_JoyButtonRecord[i].dwDoublePushFlag <<= 1;
		
		// ���݃t���[���ł̑Ώۂ̃L�[���͂��������u�ԂȂ�O�r�b�g�ڂɃ`�F�b�N����
		if(this->GetJoyBtnPush(i))this->m_JoyButtonRecord[i].dwDoublePushFlag |= 0x1;

	}

	return;
}

//  �������͏��X�V
void CJoySystem::UpdateSameJoyStkPushInfo(){		
	
	
	int i = 0;

	// ���ݎg�p���Ă���{�^�����̏��X�V���s��
	for(i = 0 ; i < JOYMAX ; i++){
	
		// �������u�Ԃ̓��͗������P�t���[�������炷
		this->m_JoyStickRecord[i].dwSamePushFlag <<= 1;

		// ���݃t���[���ł̑Ώۂ̃L�[���͂��������u�ԂȂ�O�r�b�g�ڂɃ`�F�b�N����
		if(this->GetJoyStkPush(i))this->m_JoyStickRecord[i].dwSamePushFlag |= 0x1;

	}

	return;
}

//  �������͏��X�V
void CJoySystem::UpdateSameJoyBtnPushInfo(){		
	
	int i = 0;

	// ���ݎg�p���Ă���{�^�����̏��X�V���s��
	for(i = 0 ; i < JOYMAX ; i++){
	
		// �������u�Ԃ̓��͗������P�t���[�������炷
		this->m_JoyButtonRecord[i].dwSamePushFlag <<= 1;

		// ���݃t���[���ł̑Ώۂ̃L�[���͂��������u�ԂȂ�O�r�b�g�ڂɃ`�F�b�N����
		if(this->GetJoyBtnPush(i))this->m_JoyButtonRecord[i].dwSamePushFlag |= 0x1;

	}

	return;
}

//  �p�����͂𒲂ׂ�
BOOL CJoySystem::GetKeepJoyStkPush(BYTE byJoyNum,BYTE byWait){

	// �G���[�`�F�b�N
	if(byJoyNum >= JOYMAX ||
	   byWait == 0)return FALSE;

	// �w�肵���L�[���w�肵���t���[�����p�����͂���Ă�������͐���
	if(this->m_JoyStickRecord[byJoyNum].byKeepPushCount >= byWait)return TRUE;

	// ���͎��s
	return FALSE;
}
//  �p�����͂𒲂ׂ�
BOOL CJoySystem::GetKeepJoyBtnPush(BYTE byJoyNum,BYTE byWait){
	// �G���[�`�F�b�N
	if(byJoyNum >= JOYMAX ||
	   byWait == 0)return FALSE;

	// �w�肵���L�[���w�肵���t���[�����p�����͂���Ă�������͐���
	if(this->m_JoyButtonRecord[byJoyNum].byKeepPushCount >= byWait)return TRUE;

	// ���͎��s
	return FALSE;
}
//  �A�����͂𒲂ׂ�
BOOL CJoySystem::GetDoubleJoyStkPush(BYTE byJoyNum,BYTE byWait){

	int i = 0;

	// �G���[�`�F�b�N
	if(byJoyNum >= JOYMAX ||byWait <= 1 ||byWait >= JOY_RECORD_MAX)return FALSE;

	// �w�肳�ꂽ�t���[���Ԃ̘A�����͏��𒲂ׂ�
	for(i = 0 ; i < byWait ; i++){

		// �w�肵���t���[���ԓ��Ɉ�x�ڂ̎w�肵���L�[�̓��͂����������𒲂ׂ�
		if((this->m_JoyStickRecord[byJoyNum].dwDoublePushFlag >> i) & 0x1){

			// ��x�ڂ̓��͂����������̃t���[������w�肳�ꂽ�t���[���Ԃ̓��͏��𒲂ׂ�
			for(i = (i + 1) ; i < byWait ; i++){

				// �w�肵���t���[���ԓ��ɓ�x�ڂ̎w�肵���L�[�̓��͂����������𒲂ׂ�
				if((this->m_JoyStickRecord[byJoyNum].dwDoublePushFlag >> i) & 0x1){

					// ��x�ڂ̓��͂����������_�ŗ��������Z�b�g����
					this->m_JoyStickRecord[byJoyNum].dwDoublePushFlag = 0;

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
//  �������͂𒲂ׂ�
BOOL CJoySystem::GetSameJoyStkPush(BYTE byJoyNum1,BYTE byJoyNum2,BYTE byWait){

	int i = 0;
	BYTE byPushCheck = 0;			// �������̓`�F�b�N�p

	// �G���[�`�F�b�N
	if(byJoyNum1 >= JOYMAX ||
	   byJoyNum2 >= JOYMAX ||
	   byJoyNum1 == byJoyNum2 ||
	   byWait == 0 ||
	   byWait > JOY_RECORD_MAX)return FALSE;

	// �w�肳�ꂽ�t���[���Ԃ̓������͏��𒲂ׂ�
	for(i = 0 ; i < byWait ; i++){

		// �w�肵���t���[���ԓ��Ɉ�ڂ̃L�[�̓��͂����������𒲂ׂ�
		if((this->m_JoyStickRecord[byJoyNum1].dwSamePushFlag >> i) & 0x1){
		
			// ���͂���������O�r�b�g�ڂɃ`�F�b�N����
			byPushCheck |= 0x1;

		}

		// �w�肵���t���[���ԓ��Ɉ�ڂ̃L�[�̓��͂����������𒲂ׂ�
		if((this->m_JoyStickRecord[byJoyNum2].dwSamePushFlag >> i) & 0x1){
		
			// ���͂���������P�r�b�g�ڂɃ`�F�b�N����
			byPushCheck |= 0x2;

		}

	}

	// �����̃L�[�����͂���Ă��邩�𒲂ׂ�
	if((byPushCheck & 0x1) && (byPushCheck & 0x2)){

		// �������͂���Ă������_�ŗ��������Z�b�g����
		this->m_JoyStickRecord[byJoyNum1].dwSamePushFlag = 0;
		this->m_JoyStickRecord[byJoyNum2].dwSamePushFlag = 0;

		// ���͐���
		return TRUE;

	}else{	// �������͂���Ă��Ȃ���������͎��s

		return FALSE;

	}
}
//  �A�����͂𒲂ׂ�
BOOL CJoySystem::GetDoubleJoyBtnPush(BYTE byJoyNum,BYTE byWait){
	
	int i = 0;

	// �G���[�`�F�b�N
	if(byJoyNum >= JOYMAX ||byWait <= 1 ||byWait >= JOY_RECORD_MAX)return FALSE;

	// �w�肳�ꂽ�t���[���Ԃ̘A�����͏��𒲂ׂ�
	for(i = 0 ; i < byWait ; i++){

		// �w�肵���t���[���ԓ��Ɉ�x�ڂ̎w�肵���L�[�̓��͂����������𒲂ׂ�
		if((this->m_JoyButtonRecord[byJoyNum].dwDoublePushFlag >> i) & 0x1){

			// ��x�ڂ̓��͂����������̃t���[������w�肳�ꂽ�t���[���Ԃ̓��͏��𒲂ׂ�
			for(i = (i + 1) ; i < byWait ; i++){

				// �w�肵���t���[���ԓ��ɓ�x�ڂ̎w�肵���L�[�̓��͂����������𒲂ׂ�
				if((this->m_JoyButtonRecord[byJoyNum].dwDoublePushFlag >> i) & 0x1){

					// ��x�ڂ̓��͂����������_�ŗ��������Z�b�g����
					this->m_JoyButtonRecord[byJoyNum].dwDoublePushFlag = 0;

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
BOOL CJoySystem::GetSameJoyBtnPush(BYTE byJoyNum1,BYTE byJoyNum2,BYTE byWait){
	//  �������͂𒲂ׂ�
	int i = 0;
	BYTE byPushCheck = 0;			// �������̓`�F�b�N�p

	// �G���[�`�F�b�N
	if(byJoyNum1 >= JOYMAX ||
	   byJoyNum2 >= JOYMAX ||
	   byJoyNum1 == byJoyNum2 ||
	   byWait == 0 ||
	   byWait > JOY_RECORD_MAX)return FALSE;

	// �w�肳�ꂽ�t���[���Ԃ̓������͏��𒲂ׂ�
	for(i = 0 ; i < byWait ; i++){

		// �w�肵���t���[���ԓ��Ɉ�ڂ̃L�[�̓��͂����������𒲂ׂ�
		if((this->m_JoyButtonRecord[byJoyNum1].dwSamePushFlag >> i) & 0x1){
		
			// ���͂���������O�r�b�g�ڂɃ`�F�b�N����
			byPushCheck |= 0x1;

		}

		// �w�肵���t���[���ԓ��Ɉ�ڂ̃L�[�̓��͂����������𒲂ׂ�
		if((this->m_JoyButtonRecord[byJoyNum2].dwSamePushFlag >> i) & 0x1){
		
			// ���͂���������P�r�b�g�ڂɃ`�F�b�N����
			byPushCheck |= 0x2;

		}

	}

	// �����̃L�[�����͂���Ă��邩�𒲂ׂ�
	if((byPushCheck & 0x1) && (byPushCheck & 0x2)){

		// �������͂���Ă������_�ŗ��������Z�b�g����
		this->m_JoyButtonRecord[byJoyNum1].dwSamePushFlag = 0;
		this->m_JoyButtonRecord[byJoyNum2].dwSamePushFlag = 0;

		// ���͐���
		return TRUE;

	}else{	// �������͂���Ă��Ȃ���������͎��s

		return FALSE;

	}
}
BOOL CJoySystem::GetSameJoyPush(BYTE byJoyStk,BYTE byJoyBtn,BYTE byWait){
	//  �������͂𒲂ׂ�
	int i = 0;
	BYTE byPushCheck = 0;			// �������̓`�F�b�N�p

	// �G���[�`�F�b�N
	if(byJoyStk >= JOYMAX ||
	   byJoyBtn >= JOYMAX ||
	   byWait == 0 ||
	   byWait > JOY_RECORD_MAX)return FALSE;

	// �w�肳�ꂽ�t���[���Ԃ̓������͏��𒲂ׂ�
	for(i = 0 ; i < byWait ; i++){

		// �w�肵���t���[���ԓ��Ɉ�ڂ̃L�[�̓��͂����������𒲂ׂ�
		if((this->m_JoyStickRecord[byJoyStk].dwSamePushFlag >> i) & 0x1){
		
			// ���͂���������O�r�b�g�ڂɃ`�F�b�N����
			byPushCheck |= 0x1;

		}

		// �w�肵���t���[���ԓ��Ɉ�ڂ̃L�[�̓��͂����������𒲂ׂ�
		if((this->m_JoyButtonRecord[byJoyBtn].dwSamePushFlag >> i) & 0x1){
		
			// ���͂���������P�r�b�g�ڂɃ`�F�b�N����
			byPushCheck |= 0x2;

		}

	}

	// �����̃L�[�����͂���Ă��邩�𒲂ׂ�
	if((byPushCheck & 0x1) && (byPushCheck & 0x2)){

		// �������͂���Ă������_�ŗ��������Z�b�g����
		this->m_JoyStickRecord[byJoyStk].dwSamePushFlag = 0;
		this->m_JoyButtonRecord[byJoyBtn].dwSamePushFlag = 0;

		// ���͐���
		return TRUE;

	}else{	// �������͂���Ă��Ȃ���������͎��s

		return FALSE;

	}
}
