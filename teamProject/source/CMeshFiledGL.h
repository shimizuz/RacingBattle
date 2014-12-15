//=============================================================================
//
// ���b�V���n�ʂ̏��� [CMeshFieldGL.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
//���d��`�h�~
#ifndef __CMESHFIELDGL_H__
#define __CMESHFIELDGL_H__

//�w�b�_�[�C���N���[�h
#include "main.h"
#include "CScene.h"

//�N���X��`
class CMeshFieldGL : public CScene
{
private:
	CVector			m_pos;							// �|�W�V����
	CVector			m_rot;							// ��]
	CVector			m_scl;							// �g�k
	LPCUSTOM_VERTEX	m_VtxBuffer;					// ���_�o�b�t�@
	int*			m_indexBuffer;					// �C���f�b�N�X�o�b�t�@
	unsigned int	m_texture;						// �e�N�X�`��ID�i�[
	int				m_nNumVertex;					// �����_��
	int				m_nNumPolygon;					// ���|���S����
	int				m_nNumVertexIndex;				// ���_�̑��C���f�b�N�X��
	int				m_nNumBlockX, m_nNumBlockZ;		// �u���b�N��
	float			m_fSizeBlockX, m_fSizeBlockZ;	// �u���b�N�T�C�Y
	CVector*		m_norBuffer;					// �@���o�b�t�@
	static CVector	m_Vertex[4];					// 4���̒��_
public:
	CMeshFieldGL(int nPriority = 3):CScene(nPriority){}
	virtual ~CMeshFieldGL(){}

	//������
	void Init(){}

	//�������I�[�o�[���[�h
	void Init(int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ,CVector pos,CVector rot,char *pTexPath);
	//�X�V
	void Update();
	//�J��
	void Uninit();
	//�`��
	void Draw();
	
	//���W�擾
	CVector GetPosition(void)
	{
		return m_pos;
	}
	//���W�ݒ�
	void SetPosition(CVector pos)
	{
		m_pos = pos;	
	}
	//��]�擾
	CVector GetRotate(void)
	{
		return m_rot;
	}
	//��]�ݒ�
	void SetRotate(CVector rot)
	{
		m_rot = rot;	
	}
	//�g�k�擾
	CVector GetScale(void)
	{
		return m_scl;
	}
	//�g�k�ݒ�
	CVector SetScale(CVector scl)
	{
		m_scl = scl;
	}
	//����
	static CMeshFieldGL* Create(int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ,CVector pos,CVector rot,char *pTexPath);
	//�l���擾
	static CVector GetVertex(int index)
	{
		return m_Vertex[index];
	}
	LPCUSTOM_VERTEX GetVerttexBuffer(int index)
	{
		return m_VtxBuffer;
	}
};


#endif