//==============================================================================
//
// �}���`�X���b�h�p[thread.h]
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
// ���M�f�[�^
// �X���b�h�p�C���^�t�F�[�X�|�C���^�ƃX���b�h�쐬���ɔC�ӂ̃f�[�^�𑗂�܂��B
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
// �X���b�h�v���V�[�W���p�C���^�t�F�[�X
// �X���b�h�쐬���ɓ����ł��̃N���X�̊֐��������I�Ɏ��s����܂��B
// ������p�������Ďg���ĂˁB
//------------------------------------------------------------------------------
class ThreadProcedure {
 public:
   // TODO ���O�ǂ����邩
  static unsigned int WINAPI LocalFunction(void* p_data);

 private:
  // �e���v���[�g�p�^�[��
  // �X���b�h�쐬���ɓ����ł��̊֐��������I�Ɏ��s����܂��B
  virtual DWORD _ThreadProccess(FunctionData* p_function_data) = 0;
};

//==============================================================================
// �X���b�h�N���X
// �X���b�h�f�[�^���󂯎���āA
// �X���b�h�v���V�[�W���p�C���^�t�F�[�X�̊֐����Ăяo���܂��B
// �N���C�A���g�́A
// �X���b�h�v���V�[�W���p�C���^�t�F�[�X�̃|�C���^��
// �X���b�h�쐬���ɓn�������C�ӂ̃f�[�^��^���邱�ƂŁA�X���b�h���쐬�ł��܂��B
//------------------------------------------------------------------------------
class Thread {
public:
  // ctor
  Thread(void* p_data, ThreadProcedure* p_param);

  // dtor
  ~Thread();

  // �X���b�h���쐬����B
  // �n���ꂽ�l�ɂ���Ă��̂܂܊J�n���邩�A�ҋ@���邩�I������B
  bool Start(bool is_suspend);

  // �X���b�h���I��������B
  void End(void);

  // �N�����̃X���b�h���ꎞ��~������B
  void Suspend(void);

  // �ҋ@���̃X���b�h���ĊJ������B
  void Resume(void);

  // �X���b�h����~���Ă��邩�m�F����B
  bool ConfirmDeath(void) const;

  // �A�N�Z�T
  //bool is_exit(void) const { return p_function_data->is_exit; }

 private:
  HANDLE h_thread_;
  FunctionData* p_function_data;
  unsigned int thread_id_;
  bool is_suspend_;
};

#endif  // VG_GENERAL_THERAD_THREAD_H_
