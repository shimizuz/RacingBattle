#pragma once
//多重定義防止
#ifndef __CPHASEFACTORY_H__
#define __CPHASEFACTORY_H__

#include "CPhase.h"
#include "CTitle.h"
//前方宣言
//クラス定義
class CFactoryPtr
{
public:
	virtual CPhase* Create() = 0;
};

template<class T>
class CPhaseFactory : public CFactoryPtr
{
public:
	//生成
	CPhase* Create()
	{
		return static_cast<CPhase*> (new T());
	}
};

#endif