//警告制限無視
#pragma warning(disable:4996)
//ヘッダーインクルード
#include "texture.h"
#include <stdio.h>

TEXTURE g_Tex = {0};
GLuint g_texture = 0;
//テクスチャ読み込み
bool LoadTexture(char* pFileName)
{
	//変数宣言
	FILE *fp;
	GLubyte header[18]; 
	GLubyte bytePerPixel;
	GLuint temp;
	
	

	//　ファイルを開く
	if ( (fp = fopen(pFileName,"rb")) == NULL )
	{
		MessageBox(NULL,pFileName,"ERROR",MB_OK);
		return 0;
	}

	//　ヘッダー情報の読み込み
	fread(header, 1, sizeof(header), fp);
	
	//　幅と高さを決める
	g_Tex.width = header[13] * 256 + header[12];
	g_Tex.height = header[15] * 256 + header[14];
	
	//　ビットの深さ
	g_Tex.bpp = header[16];

	//　24 bit
	if ( g_Tex.bpp == 24 )
	{
		g_Tex.format = GL_RGB;
		g_Tex.internalFormat = GL_RGB;
	}
	//　32 bit
	else if ( g_Tex.bpp = 32 )
	{
		g_Tex.format = GL_RGBA;
		g_Tex.internalFormat = GL_RGBA;
	}

	//　1ピクセル当たりのバイト数を決定
	bytePerPixel = g_Tex.bpp/8;
	
	//　データサイズの決定
	g_Tex.imageSize = g_Tex.width * g_Tex.height * bytePerPixel;
	
	//　メモリを確保
	g_Tex.imageData = new GLubyte[g_Tex.imageSize];
	
	//　テクセルデータを一気に読み取り
	fread(g_Tex.imageData, 1, g_Tex.imageSize, fp);
	
	//　BGR(A)をRGB(A)にコンバート	
	for ( int i=0; i<static_cast<int>(g_Tex.imageSize); i+=bytePerPixel )
	{
	
		temp = g_Tex.imageData[i];
		g_Tex.imageData[i+0] = g_Tex.imageData[i+2];
		g_Tex.imageData[i+2] = temp;
	}
	
	//　ファイルを閉じる
	fclose(fp);


	


	
	return true;
}
//テクスチャ生成
unsigned int CreateTexture(char * pFileName)
{
	//読み込み
	LoadTexture(pFileName);

	GLuint texture = 0;

	//▼テクスチャ生成
	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D,texture);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,1);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,1);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,g_Tex.internalFormat,g_Tex.width,g_Tex.height,0,g_Tex.format,GL_UNSIGNED_BYTE,&g_Tex.imageData[0]);
	glBindTexture(GL_TEXTURE_2D,0);

	//メモリ解放
	if(g_Tex.imageData )
	{
		delete [] g_Tex.imageData;
		g_Tex.imageData = NULL;
	}
	return texture;
}