//ヘッダーインクルード
#include "CLightGL.h"

void CLightGL::Init()
{
	//ライトの設定
	m_Light.pos.SetValue(1.0f,0.0f,0.0f);
	m_Light.diffuse.SetValue(1.0f,1.0f,1.0f,1.0f);
	m_Light.ambient.SetValue(0.1f,0.1f,0.1f,1.0f);
	m_Light.specular.SetValue(1.0f,1.0f,1.0f,1.0f);

	m_Light1.pos.SetValue(0.0f,1.0f,0.0f);
	m_Light1.diffuse.SetValue(1.0f,1.0f,1.0f,1.0f);
	m_Light1.ambient.SetValue(0.1f,0.1f,0.1f,1.0f);
	m_Light1.specular.SetValue(1.0f,1.0f,1.0f,1.0f);
}
void CLightGL::SetLight(void)
{
	//ライト
	glLightfv(GL_LIGHT0,GL_POSITION,(float*)&m_Light.pos);
	glLightfv(GL_LIGHT0,GL_AMBIENT,(float*)&m_Light.ambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,(float*)&m_Light.diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,(float*)&m_Light.specular);

	//ライト
	glLightfv(GL_LIGHT1,GL_POSITION,(float*)&m_Light1.pos);
	glLightfv(GL_LIGHT1,GL_AMBIENT,(float*)&m_Light1.ambient);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,(float*)&m_Light1.diffuse);
	glLightfv(GL_LIGHT1,GL_SPECULAR,(float*)&m_Light1.specular);
}

void CLightGL::SetLightParam(LIGHT light)
{
	m_Light.pos = light.pos;
	
	m_Light.diffuse.r = light.diffuse.r;
	m_Light.diffuse.g = light.diffuse.g;
	m_Light.diffuse.b = light.diffuse.b;
	m_Light.diffuse.a = light.diffuse.a;

	m_Light.ambient.r = light.ambient.r;
	m_Light.ambient.g = light.ambient.g;
	m_Light.ambient.b = light.ambient.b;
	m_Light.ambient.a = light.ambient.a;

	m_Light.specular.r = light.specular.r;
	m_Light.specular.g = light.specular.g;
	m_Light.specular.b = light.specular.b;
	m_Light.specular.a = light.specular.a;


}