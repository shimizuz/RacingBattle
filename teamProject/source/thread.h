//==============================================================================
//
// マルチスレッド用[thread.h]
// Author : Yamashita Yasuaki
//          Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef VG_GENERAL_THERAD_THREAD_H_
#define VG_GENERAL_THERAD_THREAD_H_
//------------------------------------------------------------------------------
// include
//------------------------------------------------------------------------------
#include <Windows.h>

class ThreadProcedure;

//==============================================================================
// 送信データ
// スレッド用インタフェースポインタとスレッド作成時に任意のデータを送れます。
//------------------------------------------------------------------------------
struct FunctionData {
  // ctor
  FunctionData(void* _p_data, ThreadProcedure* _p_thread_procedure);

  // dtor
  ~FunctionData();

  void* p_data;
  ThreadProcedure* p_thread_procedure;
  bool is_exit;
};

//==============================================================================
// スレッドプロシージャ用インタフェース
// スレッド作成時に内部でこのクラスの関数が自動的に実行されます。
// これを継承させて使ってね。
//------------------------------------------------------------------------------
class ThreadProcedure {
 public:
   // TODO 名前どうするか
  static unsigned int WINAPI LocalFunction(void* p_data);

 private:
  // テンプレートパターン
  // スレッド作成時に内部でこの関数が自動的に実行されます。
  virtual DWORD _ThreadProccess(FunctionData* p_function_data) = 0;
};

//==============================================================================
// スレッドクラス
// スレッドデータを受け取って、
// スレッドプロシージャ用インタフェースの関数を呼び出します。
// クライアントは、
// スレッドプロシージャ用インタフェースのポインタと
// スレッド作成時に渡したい任意のデータを与えることで、スレッドを作成できます。
//------------------------------------------------------------------------------
class Thread {
public:
  // ctor
  Thread(void* p_data, ThreadProcedure* p_param);

  // dtor
  ~Thread();

  // スレッドを作成する。
  // 渡された値によってそのまま開始するか、待機するか選択する。
  bool Start(bool is_suspend);

  // スレッドを終了させる。
  void End(void);

  // 起動中のスレッドを一時停止させる。
  void Suspend(void);

  // 待機中のスレッドを再開させる。
  void Resume(void);

  // スレッドが停止しているか確認する。
  bool ConfirmDeath(void) const;

  // アクセサ
  //bool is_exit(void) const { return p_function_data->is_exit; }

 private:
  HANDLE h_thread_;
  FunctionData* p_function_data;
  unsigned int thread_id_;
  bool is_suspend_;
};

#endif  // VG_GENERAL_THERAD_THREAD_H_
