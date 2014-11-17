//=============================================================================
//
// �t�F�[�h���� [CFade.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//���d��`�h�~
#ifndef __CFADE_H__
#define __CFADE_H__

//�w�b�_�[�C���N���[�h
#include "main.h"
#include "CScene2D.h"


//���[�h�`�F���W�p�񋓌^
typedef enum
{
	FADE_NONE,
	FADE_OUT,
	FADE_IN,
	FADE_OUT_FINISH,
	FADE_IN_FINISH,
	FADE_MAX
}FADEMODE;

class CRender;

//�N���X��`
class CFade
{
private:
	FADEMODE	m_FadeMode;
	bool		m_fadeFlag;
	float		m_Alpha;
//	float					m_fLength;				// ���S���璸�_�܂ł̒���
//	float					m_fAngle;				// ���S���璸�_�ւ̊p�x
	char*					m_pTexName;
	static CFade*			m_instance;
	float	m_fLength;
	float	m_fAngle;
	CVector m_pos;
	CVector m_rot;
	CVector m_scl;
	CVector m_vtx[4];
	unsigned int m_texture;
public:
	static CFade*			getinstance();
	static void				Release();
	CFade()
	{
		m_Alpha = 0;
	}
	virtual ~CFade()
	{
		
	}
	
	HRESULT Init();
	void Update();
	void Uninit();
	void Draw();

	FADEMODE	GetFadeMode(void)
	{
		return m_FadeMode;
	}
	void		SetFadeMode(FADEMODE iNum)
	{
		m_FadeMode = iNum;
	}

	bool		FadeOut(void);
	bool		FadeIn(void);

};

#endif