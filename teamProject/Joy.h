#ifndef __JOY_H__
#define __JOY_H__


//�@�}�N����`
#define JOYMAX		(4)
#define JOY_RECORD_MAX (30)
//�@�\���L�[�̊e�L�[��\���}�N��
#define	JOY_UP		(0)		//�@��
#define	JOY_DOWN	(1)		//�@��
#define	JOY_LEFT	(2)		//�@��
#define	JOY_RIGHT	(3)		//�@�E
//�@�e�{�^�������炷�}�N��
#define	JOY_BTN1	(0)		//�@�{�^���P
#define	JOY_BTN2	(1)		//�@�{�^���Q
#define	JOY_BTN3	(2)		//�@�{�^���R
#define	JOY_BTN4	(3)		//�@�{�^���S
#define	JOY_BTN5	(4)		//�@�{�^���T
#define	JOY_BTN6	(5)		//�@�{�^���U
#define	JOY_BTN7	(6)		//�@�{�^���V
#define	JOY_BTN8	(7)		//�@�{�^���W
#define	JOY_BTN9	(8)		//�@�{�^���X
#define	JOY_BTN10	(9)		//�@�{�^���P�O
#define	JOY_BTN11	(10)	//�@�{�^���P�P
#define	JOY_BTN12	(11)	//�@�{�^���P�Q
#define	JOY_BTN13	(12)	//�@�{�^���P�R
#define	JOY_BTN14	(13)	//�@�{�^���P�S
#define	JOY_BTN15	(14)	//�@�{�^���P�T
#define	JOY_BTN16	(15)	//�@�{�^���P�U
#define	JOY_BTN17	(16)	//�@�{�^���P�V
#define	JOY_BTN18	(17)	//�@�{�^���P�W
#define	JOY_BTN19	(18)	//�@�{�^���P�X
#define	JOY_BTN20	(19)	//�@�{�^���Q�O
#define	JOY_BTN21	(20)	//�@�{�^���Q�P
#define	JOY_BTN22	(21)	//�@�{�^���Q�Q
#define	JOY_BTN23	(22)	//�@�{�^���Q�R
#define	JOY_BTN24	(23)	//�@�{�^���Q�S
#define	JOY_BTN25	(24)	//�@�{�^���Q�T
#define	JOY_BTN26	(25)	//�@�{�^���Q�U
#define	JOY_BTN27	(26)	//�@�{�^���Q�V
#define	JOY_BTN28	(27)	//�@�{�^���Q�W
#define	JOY_BTN29	(28)	//�@�{�^���Q�X
#define	JOY_BTN30	(29)	//�@�{�^���R�O
#define	JOY_BTN31	(30)	//�@�{�^���R�P
#define	JOY_BTN32	(31)	//�@�{�^���R�Q


//�@�\���̒�`
typedef struct tagJOYSTICKINFO
{		//�@�W���C�X�e�B�b�N�̏\���L�[�\����
	BOOL	now;	//�@���ݏ��
	BOOL	past;	//�@�ߋ����
}JOYSTICKINFO;
typedef struct tagJOYBUTTONINFO
{	//�@�W���C�X�e�B�b�N�̃{�^���\����
	BOOL	now;	//�@���ݏ��
	BOOL	past;	//�@�ߋ����
}JOYBUTTONINFO;
typedef struct tagJOYRECORD
{
	BYTE byKeepPushCount;				// �p�����̓J�E���^
	DWORD dwDoublePushFlag;			// �A�����͔���t���O
	DWORD dwSamePushFlag;				// �������͔���t���O
}JOYRECORD,*LPJOYRECORD;

//�W���C�p�b�h�Ǘ��p�N���X
class CJoySystem
{
protected:
	JOYSTICKINFO	m_JoyStickInfo[4];
	JOYBUTTONINFO	m_JoyButtonInfo[32];
	JOYRECORD		m_JoyStickRecord[JOYMAX];
	JOYRECORD		m_JoyButtonRecord[JOYMAX];
	BOOL			Flag;
public:
	CJoySystem();	//�R���X�g���N�^
	~CJoySystem();	//�f�X�g���N�^
	void	JoyZeroInit(void);			//�����o���O�ŏ���������
	void	JoyInitInfo(void);				//�@�W���C�X�e�B�b�N�̏������֐�
	void	JoyUpdateInfo(void);			//�@�W���C�X�e�B�b�N���̍X�V�p�֐�
	BOOL	GetJoyStkPush( BYTE );		//�@�\���L�[�̉������u�Ԃ𒲂ׂ�֐�
	BOOL	GetJoyStkPull( BYTE );		//�@�\���L�[�̗������u�Ԃ𒲂ׂ�֐�
	BOOL	GetJoyStkKeep( BYTE );		//�@�\���L�[�̉������ςȂ��𒲂ׂ�֐�
	BOOL	GetJoyStkFree( BYTE );		//�@�\���L�[�̗������ςȂ��𒲂ׂ�֐�
	BOOL	GetJoyStkNowInfo( BYTE );	//�@�\���L�[�̌��ݏ��̎擾���s���֐�
	BOOL	GetJoyStkPastInfo( BYTE );	//�@�\���L�[�̉ߋ����̎擾���s���֐�
	BOOL	GetJoyBtnPush( BYTE );		//�@�{�^���̉������u�Ԃ𒲂ׂ�֐�
	BOOL	GetJoyBtnPull( BYTE );		//�@�{�^���̗������u�Ԃ𒲂ׂ�֐�
	BOOL	GetJoyBtnKeep( BYTE );		//�@�{�^���̉������ςȂ��𒲂ׂ�֐�
	BOOL	GetJoyBtnFree( BYTE );		//�@�{�^���̗������ςȂ��𒲂ׂ�֐�
	BOOL	GetJoyBtnNowInfo( BYTE );	//�@�{�^���̌��ݏ��̎擾���s���֐�
	BOOL	GetJoyBtnPastInfo( BYTE );	//�@�{�^���̉ߋ����̎擾���s���֐�
	void	UpdateKeepJoyBtnPushInfo();		//  �{�^���p�����͏��X�V
	void	UpdateKeepJoyStkPushInfo();		//  �X�e�B�b�N�p�����͏��X�V
	void	UpdateDoubleJoyBtnPushInfo();	//�{�^���A�����͏��X�V
	void	UpdateSameJoyBtnPushInfo();		//�{�^���������͏��X�V
	void    UpdateDoubleJoyStkPushInfo();	//�X�e�B�b�N�A�����͏��X�V
	void	UpdateSameJoyStkPushInfo();		//�X�e�B�b�N�������͏��X�V
	BOOL	GetKeepJoyStkPush(BYTE,BYTE);		//  �X�e�B�b�N�p�����͂𒲂ׂ�
	BOOL	GetKeepJoyBtnPush(BYTE,BYTE);		//  �{�^���p�����͂𒲂ׂ�
	BOOL	GetDoubleJoyStkPush(BYTE,BYTE);	//  �X�e�B�b�N�A�����͂𒲂ׂ�
	BOOL	GetDoubleJoyBtnPush(BYTE,BYTE);	//	�{�^���A�����͂𒲂ׂ�
	BOOL	GetSameJoyStkPush(BYTE,BYTE,BYTE);//�X�e�B�b�N�������͂𒲂ׂ�
	BOOL	GetSameJoyBtnPush(BYTE,BYTE,BYTE);//�{�^���������͂𒲂ׂ�
	BOOL	GetSameJoyPush(BYTE,BYTE,BYTE); //�{�^���A�X�e�B�b�N��������
};
#endif