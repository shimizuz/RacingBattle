//���^�̊֐����Ӑ}�I�Ɏg�p����ׂɌx�������O����
#pragma warning (disable:4996)
//�w�b�_�[�C���N���[�h
#include "Input.h"

//�L�[�{�[�h�ƃW���C�p�b�h�̃I�u�W�F�N�g����
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

//�R���X�g���N�^
CInputSystem::CInputSystem(){

	this->InputZeroInit();
	
}
//�f�X�g���N�^
CInputSystem::~CInputSystem(){
	this->InputZeroInit();
}
//�����o��0�ŏ���������
void CInputSystem::InputZeroInit(){
	ZeroMemory(&this->m_InputRecord,sizeof(INPUTRECORD));
}

//���͏�񏉊���
void CInputSystem::InputInitInfo(){
	
	//�L�[���̏�����
//	g_joy.JoyInitInfo();
	this->JoyInitInfo();
	//�W���C�p�b�h���̏�����
//	g_key.KeyInitInfo();
	this->KeyInitInfo();	
	return;
}

//���͏��̍X�V
void CInputSystem::InputUpdateInfo(){
	
	//�L�[�{�[�h���X�V
//	g_key.KeyUpdateInfo();
	this->KeyUpdateInfo();
	//�W���C�p�b�h���X�V
//	g_joy.JoyUpdateInfo();
	this->JoyUpdateInfo();
	//�e����͏�Ԃ��X�V����
	this->UpdateDoublePushInfo();
	this->UpdateKeepPushInfo();
	this->UpdateSamePushInfo();

}

//�L�[�{�[�h�ƃW���C�p�b�h�̃{�^���������������ׂ�
BOOL CInputSystem::GetInputPush(BYTE byInputNum){

	BYTE UseKey[7] = {VK_UP,VK_DOWN,VK_LEFT,VK_RIGHT,'Z','X','C'};								// �g���L�[
	BYTE UseJoyBtn[7] = {JOY_BTN1,JOY_DOWN,JOY_LEFT,JOY_RIGHT,JOY_BTN2,JOY_BTN3,JOY_BTN4};	// �g���{�^��
	
	// �G���[�`�F�b�N
	if(byInputNum >= INPUT_MAX)return FALSE;

	// �w�肳�ꂽ�L�[�������ꂽ�u�Ԃ��𒲂ׂ�
	if(byInputNum == 0){

		return (this->GetKeyPush(UseKey[byInputNum]) | this->GetJoyBtnPush(UseJoyBtn[byInputNum]));
	
	}else if(byInputNum <= 3 && byInputNum >=1){

		return (this->GetKeyPush(UseKey[byInputNum]) | this->GetJoyStkPush(UseJoyBtn[byInputNum]));

	}else{

		return (this->GetKeyPush(UseKey[byInputNum]) | this->GetJoyBtnPush(UseJoyBtn[byInputNum]));

	}
}
//�L�[�{�[�h�̃L�[�ƃW���C�p�b�h�̃{�^�����������ςȂ����ǂ������ׂ�
BOOL CInputSystem::GetInputKeep(BYTE byInputNum){
	
	BYTE UseKey[7] = {VK_UP,VK_DOWN,VK_LEFT,VK_RIGHT,'Z','X','C'};								// �g���L�[
	BYTE UseJoyBtn[7] = {JOY_BTN1,JOY_DOWN,JOY_LEFT,JOY_RIGHT,JOY_BTN2,JOY_BTN3,JOY_BTN4};	// �g���{�^��
	
	// �G���[�`�F�b�N
	if(byInputNum >= INPUT_MAX)return FALSE;

	// �w�肳�ꂽ�L�[�������ꂽ�u�Ԃ��𒲂ׂ�
	if(byInputNum == 0){

		return (this->GetKeyKeep(UseKey[byInputNum]) | this->GetJoyBtnKeep(UseJoyBtn[byInputNum]));
	
	}else if(byInputNum <= 3 && byInputNum >=1){

		return (this->GetKeyKeep(UseKey[byInputNum]) | this->GetJoyStkKeep(UseJoyBtn[byInputNum]));

	}else{

		return (this->GetKeyKeep(UseKey[byInputNum]) | this->GetJoyBtnKeep(UseJoyBtn[byInputNum]));

	}
}
//�L�[�{�[�h�̃L�[�ƃW���C�p�b�h�̃{�^���𗣂����u�Ԃ��ǂ������ׂ�
BOOL CInputSystem::GetInputPull(BYTE byInputNum){
	
	BYTE UseKey[7] = {VK_UP,VK_DOWN,VK_LEFT,VK_RIGHT,'Z','X','C'};								// �g���L�[
	BYTE UseJoyBtn[7] = {JOY_BTN1,JOY_DOWN,JOY_LEFT,JOY_RIGHT,JOY_BTN2,JOY_BTN3,JOY_BTN4};	// �g���{�^��
	
	// �G���[�`�F�b�N
	if(byInputNum >= INPUT_MAX)return FALSE;

	// �w�肳�ꂽ�L�[�������ꂽ�u�Ԃ��𒲂ׂ�
	if(byInputNum == 0){

		return (this->GetKeyPull(UseKey[byInputNum]) | this->GetJoyBtnPull(UseJoyBtn[byInputNum]));
	
	}else if(byInputNum <= 3 && byInputNum >=1){

		return (this->GetKeyPull(UseKey[byInputNum]) | this->GetJoyStkPull(UseJoyBtn[byInputNum]));

	}else{

		return (this->GetKeyPull(UseKey[byInputNum]) | this->GetJoyBtnPull(UseJoyBtn[byInputNum]));

	}
}
//�L�[�{�[�h�̃L�[�ƃW���C�p�b�h�̃{�^���𗣂����ςȂ����ǂ������ׂ�
BOOL CInputSystem::GetInputFree(BYTE byInputNum){
	
	BYTE UseKey[7] = {VK_UP,VK_DOWN,VK_LEFT,VK_RIGHT,'Z','X','C'};								// �g���L�[
	BYTE UseJoyBtn[7] = {JOY_BTN1,JOY_DOWN,JOY_LEFT,JOY_RIGHT,JOY_BTN2,JOY_BTN3,JOY_BTN4};	// �g���{�^��
	
	// �G���[�`�F�b�N
	if(byInputNum >= INPUT_MAX)return FALSE;

	// �w�肳�ꂽ�L�[�������ꂽ�u�Ԃ��𒲂ׂ�
	if(byInputNum == 0){

		return (this->GetKeyFree(UseKey[byInputNum]) | this->GetJoyBtnFree(UseJoyBtn[byInputNum]));
	
	}else if(byInputNum <= 3 && byInputNum >=1){

		return (this->GetKeyFree(UseKey[byInputNum]) | this->GetJoyStkFree(UseJoyBtn[byInputNum]));

	}else{

		return (this->GetKeyFree(UseKey[byInputNum]) | this->GetJoyBtnFree(UseJoyBtn[byInputNum]));

	}
}
//�e�L�[�ƃW���C�p�b�h�̉ߋ������擾
BOOL CInputSystem::GetInputPastInfo(BYTE byInputNum){
	
	BYTE UseKey[7] = {VK_UP,VK_DOWN,VK_LEFT,VK_RIGHT,'Z','X','C'};								// �g���L�[
	BYTE UseJoyBtn[7] = {JOY_BTN1,JOY_DOWN,JOY_LEFT,JOY_RIGHT,JOY_BTN2,JOY_BTN3,JOY_BTN4};	// �g���{�^��
	
	// �G���[�`�F�b�N
	if(byInputNum >= INPUT_MAX)return FALSE;

	// �w�肳�ꂽ�L�[�������ꂽ�u�Ԃ��𒲂ׂ�
	if(byInputNum == 0){

		return (this->GetKeyPastInfo(UseKey[byInputNum]) | this->GetJoyBtnPastInfo(UseJoyBtn[byInputNum]));

	}else if(byInputNum <= 3 && byInputNum >=1){

		return (this->GetKeyPastInfo(UseKey[byInputNum]) | this->GetJoyStkPastInfo(UseJoyBtn[byInputNum]));

	}else{

		return (this->GetKeyPastInfo(UseKey[byInputNum]) | this->GetJoyBtnPastInfo(UseJoyBtn[byInputNum]));

	}
}
//�e�L�[�ƃW���C�p�b�h�̌��݂̏����擾
BOOL CInputSystem::GetInputNowInfo(BYTE byInputNum){
	
	BYTE UseKey[7] = {VK_UP,VK_DOWN,VK_LEFT,VK_RIGHT,'Z','X','C'};								// �g���L�[
	BYTE UseJoyBtn[7] = {JOY_BTN1,JOY_DOWN,JOY_LEFT,JOY_RIGHT,JOY_BTN2,JOY_BTN3,JOY_BTN4};	// �g���{�^��
	
	// �G���[�`�F�b�N
	if(byInputNum >= INPUT_MAX)return FALSE;

	// �w�肳�ꂽ�L�[�������ꂽ�u�Ԃ��𒲂ׂ�
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
// * UpdateKeepPushInfo�֐� *
//
// �y�@�\�z
//	�p�����͏��̍X�V���s��
//
// �y�����z
//	�Ȃ�
//	
// �y�߂�l�z
//	�Ȃ�
//
//==========================================
void CInputSystem::UpdateKeepPushInfo(){

	int i = 0;

	// ���ݎg�p���Ă���{�^�����̏��X�V���s��
	for(i = 0 ; i < INPUT_MAX ; i++){

		// ����Ώۂ̃L�[�����������Ă���Ȃ�J�E���g�A�b�v����
		if(this->GetInputKeep(i)){

			// ���E�l�ɒB���Ă���Ȃ�A���̒l�ŌŒ肷��(�����ӂ�h�~)
			if(this->m_InputRecord[i].byKeepPushCount != 255)this->m_InputRecord[i].byKeepPushCount++;

		}else{	// ����ΏۃL�[�������ꂽ��J�E���^�����Z�b�g����

			this->m_InputRecord[i].byKeepPushCount = 0;

		}

	}

	return;

}

//==========================================
//
// * GetKeepPush�֐� *
//
// �y�@�\�z
//	�w�肵���L�[���w�肵���t���[���̊Ԍp�����͂���Ă��邩�𒲂ׂ�
//
// �y�����z
//	��P�����F�Ώۂ̃L�[�������l(�}�N���Ŏw��)
//	��Q�����F�p�����͂���t���[����
//	
// �y�߂�l�z
//	�p�����͂���Ă���FTRUE	�p�����͂���Ă��Ȃ� or �s���Ȓl���w��FFALSE
//
//==========================================
BOOL CInputSystem::GetKeepPush(BYTE byInputNum,BYTE byWait){

	// �G���[�`�F�b�N
	if(byInputNum >= INPUT_MAX ||
	   byWait == 0)return FALSE;

	// �w�肵���L�[���w�肵���t���[�����p�����͂���Ă�������͐���
	if(this->m_InputRecord[byInputNum].byKeepPushCount >= byWait)return TRUE;

	// ���͎��s
	return FALSE;

}

//==========================================
//
// * UpdateDoublePushInfo�֐� *
//
// �y�@�\�z
//	�A�����͏��̍X�V���s��
//
// �y�����z
//	�Ȃ�
//	
// �y�߂�l�z
//	�Ȃ�
//
//==========================================
void CInputSystem::UpdateDoublePushInfo(){

	int i = 0;

	// ���ݎg�p���Ă���{�^�����̏��X�V���s��
	for(i = 0 ; i < INPUT_MAX ; i++){

		// �������u�Ԃ̗������P�t���[�������炷
		this->m_InputRecord[i].dwDoublePushFlag <<= 1;
		
		// ���݃t���[���ł̑Ώۂ̃L�[���͂��������u�ԂȂ�O�r�b�g�ڂɃ`�F�b�N����
		if(this->GetInputPush(i))this->m_InputRecord[i].dwDoublePushFlag |= 0x1;

	}

	return;

}

//==========================================
//
// * GetDoublePush�֐� *
//
// �y�@�\�z
//	�w�肵���L�[���A�����͂��ꂽ���𒲂ׂ�
//
// �y�����z
//	��P�����F�Ώۂ̃L�[�������l(�}�N���Ŏw��)
//	��Q�����F�A�����͂��󂯕t����t���[����(�ő�R�Q�t���[��)
//
// �y�߂�l�z
//	���͐����FTRUE	���͎��s or �s���Ȓl���w��FFALSE
//
//==========================================
BOOL CInputSystem::GetDoublePush(BYTE byInputNum,BYTE byWait){

	int i = 0;

	// �G���[�`�F�b�N
	if(byInputNum >= INPUT_MAX ||byWait <= 1 ||byWait >= INPUT_RECORD_MAX)return FALSE;

	// �w�肳�ꂽ�t���[���Ԃ̘A�����͏��𒲂ׂ�
	for(i = 0 ; i < byWait ; i++){

		// �w�肵���t���[���ԓ��Ɉ�x�ڂ̎w�肵���L�[�̓��͂����������𒲂ׂ�
		if((this->m_InputRecord[byInputNum].dwDoublePushFlag >> i) & 0x1){

			// ��x�ڂ̓��͂����������̃t���[������w�肳�ꂽ�t���[���Ԃ̓��͏��𒲂ׂ�
			for(i = (i + 1) ; i < byWait ; i++){

				// �w�肵���t���[���ԓ��ɓ�x�ڂ̎w�肵���L�[�̓��͂����������𒲂ׂ�
				if((this->m_InputRecord[byInputNum].dwDoublePushFlag >> i) & 0x1){

					// ��x�ڂ̓��͂����������_�ŗ��������Z�b�g����
					this->m_InputRecord[byInputNum].dwDoublePushFlag = 0;

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

//==========================================
//
// * UpdateSamePushInfo�֐� *
//
// �y�@�\�z
//	�������͏��̍X�V���s��
//
// �y�����z
//	�Ȃ�
//	
// �y�߂�l�z
//	�Ȃ�
//
//==========================================
void CInputSystem::UpdateSamePushInfo(){

	int i = 0;

	// ���ݎg�p���Ă���{�^�����̏��X�V���s��
	for(i = 0 ; i < INPUT_MAX ; i++){
	
		// �������u�Ԃ̓��͗������P�t���[�������炷
		this->m_InputRecord[i].dwSamePushFlag <<= 1;

		// ���݃t���[���ł̑Ώۂ̃L�[���͂��������u�ԂȂ�O�r�b�g�ڂɃ`�F�b�N����
		if(this->GetInputPush(i))this->m_InputRecord[i].dwSamePushFlag |= 0x1;

	}

	return;

}

//==========================================
//
// * GetSamePush�֐� *
//
// �y�@�\�z
//	�w�肳�ꂽ��̃L�[���������͂��ꂽ���𒲂ׂ�
//
// �y�����z
//	��P�����F��ڂ̑Ώۂ̃L�[�������l(�}�N���Ŏw��)
//�@��Q�����F��ڂ̑Ώۂ̃L�[�������l(�}�N���Ŏw��)	
//  ��R�����F�������͂��󂯕t����t���[����(�ő�R�Q�t���[��)
//
// �y�߂�l�z
//	���͐����FTRUE	���͎��s or �s���Ȓl���w��FFALSE
//
//==========================================
BOOL CInputSystem::GetSamePush(BYTE byInputNum1,BYTE byInputNum2,BYTE byWait){

	int i = 0;
	BYTE byPushCheck = 0;			// �������̓`�F�b�N�p

	// �G���[�`�F�b�N
	if(byInputNum1 >= INPUT_MAX ||
	   byInputNum2 >= INPUT_MAX ||
	   byInputNum1 == byInputNum2 ||
	   byWait == 0 ||
	   byWait > INPUT_RECORD_MAX)return FALSE;

	// �w�肳�ꂽ�t���[���Ԃ̓������͏��𒲂ׂ�
	for(i = 0 ; i < byWait ; i++){

		// �w�肵���t���[���ԓ��Ɉ�ڂ̃L�[�̓��͂����������𒲂ׂ�
		if((this->m_InputRecord[byInputNum1].dwSamePushFlag >> i) & 0x1){
		
			// ���͂���������O�r�b�g�ڂɃ`�F�b�N����
			byPushCheck |= 0x1;

		}

		// �w�肵���t���[���ԓ��Ɉ�ڂ̃L�[�̓��͂����������𒲂ׂ�
		if((this->m_InputRecord[byInputNum2].dwSamePushFlag >> i) & 0x1){
		
			// ���͂���������P�r�b�g�ڂɃ`�F�b�N����
			byPushCheck |= 0x2;

		}

	}

	// �����̃L�[�����͂���Ă��邩�𒲂ׂ�
	if((byPushCheck & 0x1) && (byPushCheck & 0x2)){

		// �������͂���Ă������_�ŗ��������Z�b�g����
		this->m_InputRecord[byInputNum1].dwSamePushFlag = 0;
		this->m_InputRecord[byInputNum2].dwSamePushFlag = 0;

		// ���͐���
		return TRUE;

	}else{	// �������͂���Ă��Ȃ���������͎��s

		return FALSE;

	}
}
