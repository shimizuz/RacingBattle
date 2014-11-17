//���d��`�h�~
#ifndef __CMANAGER_H__
#define __CMANAGER_H__

//�w�b�_�[�C���N���[�h
#include "main.h"
#include "CPhaseFactory.h"
#include "CPhase.h"

//�O���錾
class CRenderer;
class CScene;
//class CFactoryPtr;
//class CPhase;
//�N���X��`
class CManager
{
private:
	static CRenderer*		m_pRenderer;
	static CFactoryPtr*		m_pNextPtr;
	static CPhase*			m_pCurrentPhase;
public:

	//�R���X�g���N�^
	CManager(){}
	//�f�X�g���N�^
	virtual ~CManager(){}
	//������
	void Init(HWND hWnd);
	//�J��
	void Uninit(void);
	//�X�V
	void Updata(void);
	//�`��
	void Draw(void);
	//�Q�b�^�[
	static CRenderer* GetRenderer(void)
	{
		return m_pRenderer;
	}
	//�t�@�N�g�����Z�b�g
	static bool SetFactory(CFactoryPtr* ptr)
	{
		if(m_pNextPtr == NULL)
		{
			m_pNextPtr = ptr;
			return true;
		}
		return false;
	}
	//�t�@�N�g�����폜
	static void DeleteFactory(void)
	{
		delete m_pNextPtr;
		m_pNextPtr = NULL;
	}

};
#endif