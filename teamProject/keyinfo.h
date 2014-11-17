#ifndef __KEYINFO_H__
#define __KEYINFO_H__
//�w�b�_�t�@�C���̃C���N���[�h
#include <windows.h>

//�}�N����`
#define	KEYMAX			(256)	//�@�L�[����
#define KEYRECORDMAX	(32)	//���͗���ۑ���
#define KEYUSEMAX		(7)		//�g�p����L�[����

///// �\���̒�` /////
typedef struct tagKEYINFO
{		//�@�L�[���Ǘ��\����
	BOOL	now;
	BOOL	past;
}KEYINFO;

typedef struct tagKEYRECORD
{
	BYTE KeepPushCount;				// �p�����̓J�E���^
	DWORD DoublePushFlag;			// �A�����͔���t���O
	DWORD SamePushFlag;				// �������͔���t���O
}KEYRECORD,*LPKEYRECORD;


//�L�[���Ǘ��p�N���X
class CKeySystem
{
protected:
	KEYINFO m_KeyInfo[KEYMAX];
	KEYRECORD m_KeyRecord[KEYMAX];
public:
	//�R���X�g���N�^
	CKeySystem();
	//�f�X�g���N�^
	~CKeySystem();
	//�����o��0�ŏ���������
	void KeyZeroInit(void);
	void	KeyInitInfo(void);					//�@�L�[�Ɋւ��鏉�������s��
	void	KeyUpdateInfo(void);				//�@�����[�v���Ƃ̃L�[�����X�V
	BOOL	GetKeyPush( int );				//�@�������u�u�ԁv�̃L�[���̎擾
	BOOL	GetKeyPull( int );				//�@�������u�u�ԁv�̃L�[���̎擾
	BOOL	GetKeyKeep( int );				//�@�����u���ςȂ��v�̃L�[���̎擾
	BOOL	GetKeyFree( int );				//�@�����u���ςȂ��v�̃L�[���̎擾
	BOOL	GetKeyNowInfo( int );			//�@�e�L�[�̌��ݏ��̎擾
	BOOL	GetKeyPastInfo( int );			//�@�e�L�[�̉ߋ����̎擾
	void	UpdateKeepKeyPushInfo(void);		//  �p�����͏��X�V
	void	UpdateDoubleKeyPushInfo(void);		//  �A�����͏��X�V
	void	UpdateSameKeyPushInfo(void);		//  �������͏��X�V
	BOOL	GetKeepKeyPush(BYTE,BYTE);		//  �p�����͂𒲂ׂ�
	BOOL	GetDoubleKeyPush(BYTE,BYTE);	//  �A�����͂𒲂ׂ�
	BOOL	GetSameKeyPush(BYTE,BYTE,BYTE);	//  �������͂𒲂ׂ�

};
#endif