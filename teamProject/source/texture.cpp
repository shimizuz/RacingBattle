//�x����������
#pragma warning(disable:4996)
//�w�b�_�[�C���N���[�h
#include "texture.h"
#include <stdio.h>

TEXTURE g_Tex = {0};
GLuint g_texture = 0;
//�e�N�X�`���ǂݍ���
bool LoadTexture(char* pFileName)
{
	//�ϐ��錾
	FILE *fp;
	GLubyte header[18]; 
	GLubyte bytePerPixel;
	GLuint temp;
	
	

	//�@�t�@�C�����J��
	if ( (fp = fopen(pFileName,"rb")) == NULL )
	{
		MessageBox(NULL,pFileName,"ERROR",MB_OK);
		return 0;
	}

	//�@�w�b�_�[���̓ǂݍ���
	fread(header, 1, sizeof(header), fp);
	
	//�@���ƍ��������߂�
	g_Tex.width = header[13] * 256 + header[12];
	g_Tex.height = header[15] * 256 + header[14];
	
	//�@�r�b�g�̐[��
	g_Tex.bpp = header[16];

	//�@24 bit
	if ( g_Tex.bpp == 24 )
	{
		g_Tex.format = GL_RGB;
		g_Tex.internalFormat = GL_RGB;
	}
	//�@32 bit
	else if ( g_Tex.bpp = 32 )
	{
		g_Tex.format = GL_RGBA;
		g_Tex.internalFormat = GL_RGBA;
	}

	//�@1�s�N�Z��������̃o�C�g��������
	bytePerPixel = g_Tex.bpp/8;
	
	//�@�f�[�^�T�C�Y�̌���
	g_Tex.imageSize = g_Tex.width * g_Tex.height * bytePerPixel;
	
	//�@���������m��
	g_Tex.imageData = new GLubyte[g_Tex.imageSize];
	
	//�@�e�N�Z���f�[�^����C�ɓǂݎ��
	fread(g_Tex.imageData, 1, g_Tex.imageSize, fp);
	
	//�@BGR(A)��RGB(A)�ɃR���o�[�g	
	for ( int i=0; i<static_cast<int>(g_Tex.imageSize); i+=bytePerPixel )
	{
	
		temp = g_Tex.imageData[i];
		g_Tex.imageData[i+0] = g_Tex.imageData[i+2];
		g_Tex.imageData[i+2] = temp;
	}
	
	//�@�t�@�C�������
	fclose(fp);


	


	
	return true;
}
//�e�N�X�`������
unsigned int CreateTexture(char * pFileName)
{
	//�ǂݍ���
	LoadTexture(pFileName);

	GLuint texture = 0;

	//���e�N�X�`������
	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D,texture);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,1);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,1);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,g_Tex.internalFormat,g_Tex.width,g_Tex.height,0,g_Tex.format,GL_UNSIGNED_BYTE,&g_Tex.imageData[0]);
	glBindTexture(GL_TEXTURE_2D,0);

	//���������
	if(g_Tex.imageData )
	{
		delete [] g_Tex.imageData;
		g_Tex.imageData = NULL;
	}
	return texture;
}