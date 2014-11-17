//���d��`�h�~
#ifndef __TEXTURE_H__
#define __TEXTURE_H__

//�w�b�_�[�C���N���[�h
#include "main.h"
//�\���̒�`
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

//�v���g�^�C�v
bool LoadTexture(char* pFileName);
unsigned int CreateTexture(char* pFileName);
#endif
