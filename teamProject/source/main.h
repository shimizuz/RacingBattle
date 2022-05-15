#ifndef __MAIN_H__
#define __MAIN_H__

#define SCREEN_WIDTH	(800)
#define SCREEN_HEIGHT	(600)


#include <windows.h>
#include <stdio.h>
//#include <tchar.h>
#include <GL/gl.h>
#include <GL/glu.h>
//ライブラリ
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


//色情報
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
//マテリアル
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

//4次元ベクトル
typedef struct VECTOR4
{
	float	x;
	float	y;
	float	z;
	float	w;
} VECTOR4;
//4x4の行列
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
		//対角成分に1を設定
		_11 = 1.0f;
		_22 = 1.0f;
		_33 = 1.0f;
		_44 = 1.0f;

		return *this;
	}
	MATRIX4x4 Transpose(void)
	{
		int i = 0,j = 0;
		MATRIX4x4 matTranspose;	//転置用

		matTranspose.Identity(); //正規化
	
		for(i = 0;i < 4;i++)
		{
			for(j = 0;j < 4;j++)
			{
				matTranspose.m[i][j] = m[j][i];	//転置
			}
		}
		//転置した行列を返す
		return matTranspose;
	}
} MATRIX4x4;

//頂点情報
typedef struct CUSTOM_VERTEX
{
	float r, g, b, a;	//色
	float nx, ny, nz;	//法線
	float x, y, z;		//頂点
	float tu,tv;		//テクスチャ
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