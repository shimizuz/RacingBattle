//==============================================================================
//
// �C�x���g
// Author : Shimizu Shoji
//
// �C�x���g�����̃��b�p
//
//==============================================================================
#pragma once
#ifndef VG_GENERAL_THREAD_EVENT_H_
#define VG_GENERAL_THREAD_EVENT_H_
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �t�@�C���w�b�_�ɂċL�q�B
class Event {
 public:
  // ctor
   Event(bool manual_reset, bool is_signaled);

  // dtor
  ~Event();

  // �V�O�i����Ԃɂ���B
  void Set(void);

  // ��V�O�i����Ԃɂ���B
  void Reset(void);

  // �ҋ@����B
  // -1�Ȃ疳���҂��B
  void Wait(int wait_time);

 private:
   HANDLE h_event_;
};

#endif  // VG_GENERAL_THREAD_EVENT_H_
