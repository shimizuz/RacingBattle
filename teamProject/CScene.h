//���d��`�h�~
#ifndef __CSCENE_H__
#define __CSCENE_H__

//�w�b�_�[�C���N���[�h
#include "main.h"
#include "Class_Vector.h"

//�}�N����`
#define PRIORITY_MAX	(8)

//�O���錾
class CRenderer;
//�N���X��`
class CScene
{
private:
	
	static CScene*		m_pTop[PRIORITY_MAX];	//���X�g�̐擪�A�h���X
	static CScene*		m_pCur[PRIORITY_MAX];	//���X�g�̌��݈ʒu�A�h���X
	CScene*				m_pNext;				//�O�̃I�u�W�F�N�g�ւ̃|�C���^
	CScene*				m_pPrev;				//���̃I�u�W�F�N�g�ւ̃|�C���^
	const int			m_nPriority;			//�v���C�I���e�B
	bool				m_bDeath;				//�I�u�W�F�N�g�폜�t���O
public:
	//�R���X�g���N�^
	explicit CScene(int nPriority = 3);
	virtual ~CScene();

	//������
	virtual void Init() = 0;
	//�X�V
	virtual void Update() = 0;
	//�J��
	virtual void Uninit() = 0;
	//�`��
	virtual void Draw() = 0;
	
	//���W�擾
	virtual CVector GetPosition(void) = 0;

	//���W�ݒ�
	virtual void SetPosition(CVector pos) = 0;
		
	virtual CVector GetRotate(void) = 0;
	
	//��]�ݒ�
	virtual void SetRotate(CVector rot) = 0;
	//�����X�g�n
	void Release(void);
	void LinkList(void);
	void UnlinkList(CScene* pScene);
	static void DrawAll(void);
	static void UpdateAll(void);
	static void ReleaseAll(void);
	static void FreePhase(void);
	static void Delete(int nIdxScene);
};


#endif