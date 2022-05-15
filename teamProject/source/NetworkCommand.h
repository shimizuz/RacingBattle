//==============================================================================
//
// ネットワークコマンド
// Author : Shimizu Shoji
//
//==============================================================================
#pragma once

#ifndef _NETWORK_COMMAND_H_
#define _NETWORK_COMMAND_H_

#include <d3dx9.h>

// ネットワークコマンド一覧だよ
enum NetworkCommandTypes {
  NETWORKCOMMAND_CONNECT,
  NETWORKCOMMAND_TO_TITLE,
  NETWORKCOMMAND_TO_GAME,
  NETWORKCOMMAND_TO_GAMEEND,
  NETWORKCOMMAND_TO_RESULT,
  NETWORKCOMMAND_GAMEDATA,
};

struct NetworkData {
  NetworkCommandTypes _types;
  unsigned int _id;
  
  union {
      char dataChar[128];
      float dataFloat[32];
  };

};

#endif