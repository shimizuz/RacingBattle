#ifndef __MAIN_H__
#define __MAIN_H__

#define SCREEN_WIDTH	(800)
#define SCREEN_HEIGHT	(600)


#include <windows.h>
#include <stdio.h>
//#include <tchar.h>
#include <GL/gl.h>
#include <GL/glu.h>
//���C�u����
#pragma comment (lib, "winmm.lib")
#pragma comment(lib, "OpenGL32.lib")
#pragma comment (lib,"glu32.lib")

#define SAFE_DELETE(p)	{if(p != NULL){delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p) {if(p != NULL){delete [] (p); (p) = NULL;}}
#define PI	(3.141592f)
#define PART_MAX (3)

typedef enum
{
	MODE_TITLE,
	MODE_GAME,
	MODE_RESULT,
	MODE_MAX
}MODE;


//�F���
struct _COLOR
{
	float r,g,b,a;

	void SetValue(float r1,float g1,float b1,float a1)
	{
		r = r1;
		g = g1;
		b = b1;
		a = a1;
	}
};
//�}�e���A��
struct MATERIAL
{
	_COLOR ambient;
	_COLOR diffuse;
	_COLOR specular;
	_COLOR emission;
	float shininess;

	void SetShininess(float shi)
	{
		shininess = shi;
	}
};

//4�����x�N�g��
typedef struct VECTOR4
{
	float	x;
	float	y;
	float	z;
	float	w;
} VECTOR4;
//4x4�̍s��
typedef struct MATRIX4x4
{
	union
	{
		struct
		{
			float	_11,_12,_13,_14;
			float	_21,_22,_23,_24;
			float	_31,_32,_33,_34;
			float	_41,_42,_43,_44;
		};
		float	f[16];
		float	m[4][4];
		VECTOR4	v[4];
	};
	MATRIX4x4& ZeroMatrix( void )
	{
		ZeroMemory( this, sizeof( MATRIX4x4 ) );
		return *this;
	}
	MATRIX4x4& Identity( void )
	{
		//�Ίp������1��ݒ�
		_11 = 1.0f;
		_22 = 1.0f;
		_33 = 1.0f;
		_44 = 1.0f;

		return *this;
	}
	MATRIX4x4 Transpose(void)
	{
		int i = 0,j = 0;
		MATRIX4x4 matTranspose;	//�]�u�p

		matTranspose.Identity(); //���K��
	
		for(i = 0;i < 4;i++)
		{
			for(j = 0;j < 4;j++)
			{
				matTranspose.m[i][j] = m[j][i];	//�]�u
			}
		}
		//�]�u�����s���Ԃ�
		return matTranspose;
	}
} MATRIX4x4;

//���_���
typedef struct CUSTOM_VERTEX
{
	float r, g, b, a;	//�F
	float nx, ny, nz;	//�@��
	float x, y, z;		//���_
	float tu,tv;		//�e�N�X�`��
}CUSTOM_VERTEX,*LPCUSTOM_VERTEX;

struct KEY_DATA
{
	VECTOR4 position;
	float	rotation;
};
struct PART
{
	VECTOR4 vertex[4];
	KEY_DATA   data;
	VECTOR4 matrix;
};

struct KEY_ANIME
{
    int frame;
    KEY_DATA    key;
};

HWND GethWnd();
BOOL GetActive();
#endif
//EOF