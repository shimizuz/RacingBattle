//==============================================================================
//
// イベント
// Author : Shimizu Shoji
//
// イベント処理のラッパ
//
//==============================================================================
#pragma once
#ifndef VG_GENERAL_THREAD_EVENT_H_
#define VG_GENERAL_THREAD_EVENT_H_
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ファイルヘッダにて記述。
class Event {
 public:
  // ctor
   Event(bool manual_reset, bool is_signaled);

  // dtor
  ~Event();

  // シグナル状態にする。
  void Set(void);

  // 非シグナル状態にする。
  void Reset(void);

  // 待機する。
  // -1なら無限待ち。
  void Wait(int wait_time);

 private:
   HANDLE h_event_;
};

#endif  // VG_GENERAL_THREAD_EVENT_H_
