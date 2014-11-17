#pragma once
//���d��`�h�~
#ifndef __CPHASEFACTORY_H__
#define __CPHASEFACTORY_H__

#include "CPhase.h"
#include "CTitle.h"
//�O���錾
//�N���X��`
class CFactoryPtr
{
public:
	virtual CPhase* Create() = 0;
};

template<class T>
class CPhaseFactory : public CFactoryPtr
{
public:
	//����
	CPhase* Create()
	{
		return static_cast<CPhase*> (new T());
	}
};

#endif