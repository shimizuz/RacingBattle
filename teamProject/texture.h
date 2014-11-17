//多重定義防止
#ifndef __TEXTURE_H__
#define __TEXTURE_H__

//ヘッダーインクルード
#include "main.h"
//構造体定義
typedef struct _TEXTURE
{
	GLuint imageSize;
	GLubyte *imageData;
	GLenum format;
	GLuint internalFormat;
	GLuint width;
	GLuint height;
	GLuint bpp;
}TEXTURE;

//プロトタイプ
bool LoadTexture(char* pFileName);
unsigned int CreateTexture(char* pFileName);
#endif
