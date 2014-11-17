#ifndef __INPUT_H__
#define __INPUT_H__

// �w�b�_�[�C���N���[�h 
#include "keyinfo.h"
#include "Joy.h"


// �}�N����` 
#define	INPUT_MAX		(7)			//  �Q�[�����Ɏg���{�^���̍ő吔(�\���L�[4�����A4�{�^��)

#define	INPUT_UP		(0)			//�@��
#define	INPUT_DOWN		(1)			//�@��
#define	INPUT_LEFT		(2)			//�@��
#define	INPUT_RIGHT		(3)			//�@�E
#define	INPUT_BTN1		(4)			//�@�{�^��1
#define	INPUT_BTN2		(5)			//�@�{�^��2
#define	INPUT_BTN3		(6)			//�@�{�^��3
#define	INPUT_BTN4		(7)			//�@�{�^��4
#define	INPUT_BTN5		(8)			//�@�{�^��5
#define	INPUT_BTN6		(9)			//�@�{�^��6
#define	INPUT_BTN7		(10)		//�@�{�^��7
#define	INPUT_BTN8		(11)		//�@�{�^��8
#define	INPUT_BTN9		(12)		//�@�{�^��9
#define	INPUT_BTN10		(13)		//�@�{�^��10
#define	INPUT_BTN11		(14)		//�@�{�^��11
#define	INPUT_BTN12		(15)		//�@�{�^��12
#define	INPUT_BTN13		(16)		//�@�{�^��13
#define	INPUT_BTN14		(17)		//�@�{�^��14
#define	INPUT_BTN15		(18)		//�@�{�^��15
#define	INPUT_BTN16		(19)		//�@�{�^��16
#define	INPUT_BTN17		(20)		//�@�{�^��17
#define	INPUT_BTN18		(21)		//�@�{�^��18
#define	INPUT_BTN19		(22)		//�@�{�^��19
#define	INPUT_BTN20		(23)		//�@�{�^��20
#define	INPUT_BTN21		(24)		//�@�{�^��21
#define	INPUT_BTN22		(25)		//�@�{�^��22
#define	INPUT_BTN23		(26)		//�@�{�^��23
#define	INPUT_BTN24		(27)		//�@�{�^��24
#define	INPUT_BTN25		(28)		//�@�{�^��25
#define	INPUT_BTN26		(29)		//�@�{�^��26
#define	INPUT_BTN27		(30)		//�@�{�^��27
#define	INPUT_BTN28		(31)		//�@�{�^��28
#define	INPUT_BTN29		(32)		//�@�{�^��29
#define	INPUT_BTN30		(33)		//�@�{�^��30
#define	INPUT_BTN31		(34)		//�@�{�^��31
#define	INPUT_BTN32		(35)		//�@�{�^��32

#define INPUT_RECORD_MAX	(32)	// ���͗���ۑ��ő�t���[����

///// �\���̒�` /////
typedef struct tagINPUTRECORD{
	BYTE byKeepPushCount;				// �p�����̓J�E���^
	DWORD dwDoublePushFlag;			// �A�����͔���t���O
	DWORD dwSamePushFlag;				// �������͔���t���O
}INPUTRECORD,*LPINPUTRECORD;


//���͏��Ǘ��p�N���X
class CInputSystem :public CKeySystem ,public CJoySystem
{
private:
	static CInputSystem* m_pInput;
protected:
	INPUTRECORD m_InputRecord[INPUT_MAX];
public:
	static CInputSystem* getInstance();
	static void Release();
	CInputSystem();						// �R���X�g���N�^
	~CInputSystem();					// �f�X�g���N�^
	void InputZeroInit();				// �����o��0�ŏ���������
	void InputInitInfo();				// ���͏�񏉊���
	void InputUpdateInfo();				// ���͏��X�V
	BOOL GetInputPush(BYTE);			// �������u�Ԃ𒲂ׂ�
	BOOL GetInputKeep(BYTE);			// �����ꑱ���Ă��邩�𒲂ׂ�
	BOOL GetInputPull(BYTE);			// �����ꂽ�u�Ԃ𒲂ׂ�
	BOOL GetInputFree(BYTE);			// �����ꑱ���Ă��邩�𒲂ׂ�
	BOOL GetInputNowInfo(BYTE);			// ���݂̓��͏�Ԃ𒲂ׂ�
	BOOL GetInputPastInfo(BYTE);		// �ߋ��̓��͏�Ԃ𒲂ׂ�
	void UpdateKeepPushInfo();			// �p�����͏��X�V
	void UpdateDoublePushInfo();		// �A�����͏��X�V
	void UpdateSamePushInfo();			// �������͏��X�V
	BOOL GetKeepPush(BYTE,BYTE);		// �p�����͂𒲂ׂ�
	BOOL GetDoublePush(BYTE,BYTE);		// �A�����͂𒲂ׂ�
	BOOL GetSamePush(BYTE,BYTE,BYTE);	// �������͂𒲂ׂ�
};





#endif
