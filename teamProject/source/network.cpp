//==============================================================================
//
// network[network.cpp]
// Author : Yasuaki Yamashita : 2014/12/15
//
//==============================================================================

//******************************************************************************
// include
//******************************************************************************
#include <WS2tcpip.h>
#include <Winsock.h>
#include "Class_Vector.h"
#include "network.h"

#include "CPlayerManager.h"
#include "CPlayer.h"

#pragma comment(lib, "ws2_32.lib")

namespace {
const char* SEND_IP = ("239.192.1.2");  // 送信先IPアドレス
};

//==============================================================================
// 送信用クラス
//------------------------------------------------------------------------------
void SendUDP::sendData(const NetworkData& data) {
  CiriticalSection::Lock  lock(_CS);

  _queue.push(data);

  Set();
}

//==============================================================================
// 送信用クラス
//------------------------------------------------------------------------------
DWORD SendUDP::_ThreadProccess(FunctionData* data) {
  WSAData wsaData;
  SOCKET sock;
  struct sockaddr_in addr;
  struct sockaddr_in from;
  int sockaddr_in_size = sizeof(struct sockaddr_in);

  // 初期化
  int nErrorStatus = WSAStartup(MAKEWORD(2, 2), &wsaData);

  // エラーチェック
  if (nErrorStatus != 0)
  {
    return 0;
  }
  else
  {
    // 要求したバージョンと同一か確認
    if (LOBYTE(wsaData.wVersion) == 2 && HIBYTE(wsaData.wVersion) == 2)
    {
    }
    else
    {
      return 0;
    }
  }

  // ソケット生成
  sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  // マルチキャスト受信許可
  BOOL chk = TRUE;
  DWORD ipaddr;
  ipaddr = inet_addr("127.0.0.1");
  setsockopt(sock, SOL_SOCKET, IP_MULTICAST_IF, (const char*)&ipaddr, sizeof(ipaddr));

  // ブロードキャスト受信許可
  setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (const char*)&chk, sizeof(chk));

  // 送信用
  addr.sin_family = AF_INET;
  addr.sin_port = htons(20000);
  addr.sin_addr.S_un.S_addr = inet_addr(SEND_IP);


  // 送信
  while (true) {
      // 待機
      Wait(-1);

      CiriticalSection::Lock  lock(_CS);

      if(_queue.empty()) break ;

      while(!_queue.empty()) {

          const auto it = _queue.front();
          _queue.pop();
        
          addr.sin_addr.S_un.S_addr = inet_addr(SEND_IP);
          sendto(sock, (char *)&it, sizeof(it), 0, (struct sockaddr *)&addr, sizeof(addr));
      }

  }

  closesocket(sock);
  WSACleanup();

  return 0;
}

//==============================================================================
// 受信用クラス
//------------------------------------------------------------------------------
DWORD RecvUDP::_ThreadProccess(FunctionData* data) {
  WSAData wsaData;
  SOCKET sock;
  struct sockaddr_in addr;
  struct sockaddr_in from;
  struct ip_mreq stMreq;

  // タイムアウト用
  fd_set fds, readfds;
  struct timeval tv;

  int sockaddr_in_size = sizeof(struct sockaddr_in);

  // 初期化
  int nErrorStatus = WSAStartup(MAKEWORD(2, 2), &wsaData);

  // エラーチェック
  if (nErrorStatus != 0)
  {
    return 0;
  }
  else
  {
    // 要求したバージョンと同一か確認
    if (LOBYTE(wsaData.wVersion) == 2 && HIBYTE(wsaData.wVersion) == 2)
    {
    }
    else
    {
      return 0;
    }
  }

  // ソケット生成
  sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  // 受信用
  addr.sin_family = AF_INET;
  addr.sin_port = htons(20000);
  addr.sin_addr.S_un.S_addr = INADDR_ANY;
  bind(sock, (struct sockaddr *)&addr, sizeof(addr));
  
  memset(&stMreq, 0, sizeof(stMreq));
  stMreq.imr_interface.S_un.S_addr = INADDR_ANY;
  stMreq.imr_multiaddr.S_un.S_addr = inet_addr("239.192.1.2");

  // マルチキャスト受信許可
  BOOL chk = TRUE;
  setsockopt(sock, SOL_SOCKET, IP_ADD_MEMBERSHIP, (const char*)&stMreq, sizeof(stMreq));

  // ブロードキャスト受信許可
  setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (const char*)&chk, sizeof(chk));

  // タイムアウト用
  tv.tv_sec  = 1; // 一秒でタイムアウト
  tv.tv_usec = 0;

  FD_ZERO(&readfds);
  FD_SET(sock, &readfds);

  CPlayerManager* playerManager = (CPlayerManager*)data->p_data;

  // メインループ
  while (!data->is_exit)
  {
    NetworkData buf;
    int n = 0;

    memcpy(&fds, &readfds, sizeof(fds));
    n = select(sock + 1, &fds, nullptr, nullptr, &tv);

    if (n != 0 && FD_ISSET(sock, &fds))
    {
      // 受信
      int ret = recvfrom(sock, (char*)&buf, sizeof(buf), 0, (struct sockaddr *)&from, &sockaddr_in_size);
      if (ret == -1) continue;

      switch (buf._types)
      {
      case NETWORKCOMMAND_GAMEDATA:
      {
        playerManager->GetPlayer(buf._id)->SetPosition(CVector(buf.dataFloat[0],buf.dataFloat[1],buf.dataFloat[2]));
      }
      }
    }
  }

  closesocket(sock);
  WSACleanup();

  return 0;
}

//EOF