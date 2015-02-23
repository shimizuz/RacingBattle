//==============================================================================
//
// network[network.h]
// Author : Yasuaki Yamashita : 2014/12/15
//
//==============================================================================

#pragma once

#ifndef _NETWORK_H_
#define _NETWORK_H_

#include <Windows.h>
#include "thread.h"
#include "event.h"
#include "critical_section.h"
#include "NetworkCommand.h"
#include <queue>

class CPlayerManager;

//==============================================================================
// ���M�p�N���X
//------------------------------------------------------------------------------
class SendUDP : public ThreadProcedure, protected Event, public Thread
{
public:
  SendUDP():Event(false, false),Thread(false, this){};

  void sendData(const NetworkData& data);

protected:
  DWORD _ThreadProccess(FunctionData* data);
  std::queue<NetworkData> _queue;

  CiriticalSection _CS;

};

//==============================================================================
// ��M�p�N���X
//------------------------------------------------------------------------------
class RecvUDP : public ThreadProcedure, public Thread
{
public:
  RecvUDP(CPlayerManager* playerManager):Thread( playerManager, this){};

protected:
  DWORD _ThreadProccess(FunctionData* data);
};

#endif
//EOF