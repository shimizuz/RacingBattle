//==============================================================================
//
// マルチスレッド用[thread.cpp]
// Author : Yamashita Yasuaki
//          Shimizu Shoji
//
//   _beginthreadex を使用して作成する。
// ここで作られるスレッドハンドルは、通常のAPIに対しても使用できるものである。
// つまり、ResumeThreadなどの関数に対して使用できる。
//   スレッド関数が終了する時点で自動的に _endthreadex が呼び出される。
// なお、 _endthreadex はスレッドハンドルを閉じないので、
// CloseHandle を使用してスレッドハンドルを閉じる必要がある。
//   作成開始と停止削除以外は通常のスレッドと同様である。
//
//==============================================================================
//------------------------------------------------------------------------------
// include
//------------------------------------------------------------------------------
#include "thread.h"

#include <assert.h>
#include <process.h>


//==============================================================================
// コンストラクタ
//------------------------------------------------------------------------------
FunctionData::FunctionData(void* _p_data, ThreadProcedure* _p_thread_procedure)
    : p_data(_p_data), p_thread_procedure(_p_thread_procedure), is_exit(false) {
  // none
};

//==============================================================================
// デストラクタ
//------------------------------------------------------------------------------
FunctionData::~FunctionData() {
  //common::SafeDelete(p_thread_procedure);
}

//==============================================================================
// スレッドプロシージャ用のローカル関数
//------------------------------------------------------------------------------
unsigned int WINAPI ThreadProcedure::LocalFunction(void* p_data) {
  FunctionData* p_function_data = (FunctionData*)p_data;
  const int ret = p_function_data->p_thread_procedure->_ThreadProccess(
    p_function_data );

	// 終了
	_endthreadex( ret );
	return ret;
}

//==============================================================================
// コンストラクタ
//------------------------------------------------------------------------------
Thread::Thread(void* p_data, ThreadProcedure* p_thread_procedure)
    : h_thread_(nullptr),
      thread_id_(0),
      p_function_data(nullptr),
      is_suspend_(true) {
  // スレッドデータの作成
  p_function_data = new FunctionData(p_data, p_thread_procedure);
}

//==============================================================================
// デストラクタ
//------------------------------------------------------------------------------
Thread::~Thread() {
  // ハンドルの解放
  CloseHandle(h_thread_);
  if(p_function_data != nullptr) {
    delete p_function_data;
    p_function_data = nullptr;
  }
}

//==============================================================================
// スレッドを作成し、開始する。
//------------------------------------------------------------------------------
bool Thread::Start(const bool is_suspend) {
  h_thread_ = (HANDLE)_beginthreadex(
    nullptr,
    0,
    ThreadProcedure::LocalFunction,
    p_function_data,
    is_suspend ? CREATE_SUSPENDED : 0,
    &thread_id_);

  is_suspend_ = is_suspend;

  return h_thread_ != nullptr;
}

//==============================================================================
// スレッドを終了する。
//------------------------------------------------------------------------------
void Thread::End(void) {
  p_function_data->is_exit = true;
}

//==============================================================================
// 起動中のスレッドを一時停止させる。
//==============================================================================
void Thread::Suspend(void) {
  // if スレッドが止まっていたら 何もしない
  if (is_suspend_) {
    return;
  }

  // スレッドの停止
  const int ret = SuspendThread(h_thread_);
  if (ret == -1) {
    return;
  }
  is_suspend_ = true;
}

//==============================================================================
// スレッドを再開する
//------------------------------------------------------------------------------
void Thread::Resume(void) {
  // if スレッドが動いていたら 何もしない
  if (!is_suspend_) {
    return;
  }

  // スレッドの再開
  const int ret = ResumeThread(h_thread_);
  if (ret == -1) {
    return;
  }
  is_suspend_ = false;
}

//==============================================================================
// スレッドの死を確認
//------------------------------------------------------------------------------
bool Thread::ConfirmDeath(void) const {
  //return WAIT_OBJECT_0 == WaitForSingleObject(h_thread_, 0);
  DWORD exit_code;
  GetExitCodeThread(h_thread_, &exit_code);

  return exit_code != STILL_ACTIVE;
}
