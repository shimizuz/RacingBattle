//==============================================================================
//
// �}���`�X���b�h�p[thread.cpp]
// Author : Yamashita Yasuaki
//          Shimizu Shoji
//
//   _beginthreadex ���g�p���č쐬����B
// �����ō����X���b�h�n���h���́A�ʏ��API�ɑ΂��Ă��g�p�ł�����̂ł���B
// �܂�AResumeThread�Ȃǂ̊֐��ɑ΂��Ďg�p�ł���B
//   �X���b�h�֐����I�����鎞�_�Ŏ����I�� _endthreadex ���Ăяo�����B
// �Ȃ��A _endthreadex �̓X���b�h�n���h������Ȃ��̂ŁA
// CloseHandle ���g�p���ăX���b�h�n���h�������K�v������B
//   �쐬�J�n�ƒ�~�폜�ȊO�͒ʏ�̃X���b�h�Ɠ��l�ł���B
//
//==============================================================================
//------------------------------------------------------------------------------
// include
//------------------------------------------------------------------------------
#include "thread.h"

#include <assert.h>
#include <process.h>


//==============================================================================
// �R���X�g���N�^
//------------------------------------------------------------------------------
FunctionData::FunctionData(void* _p_data, ThreadProcedure* _p_thread_procedure)
    : p_data(_p_data), p_thread_procedure(_p_thread_procedure), is_exit(false) {
  // none
};

//==============================================================================
// �f�X�g���N�^
//------------------------------------------------------------------------------
FunctionData::~FunctionData() {
  //common::SafeDelete(p_thread_procedure);
}

//==============================================================================
// �X���b�h�v���V�[�W���p�̃��[�J���֐�
//------------------------------------------------------------------------------
unsigned int WINAPI ThreadProcedure::LocalFunction(void* p_data) {
  FunctionData* p_function_data = (FunctionData*)p_data;
  const int ret = p_function_data->p_thread_procedure->_ThreadProccess(
    p_function_data );

	// �I��
	_endthreadex( ret );
	return ret;
}

//==============================================================================
// �R���X�g���N�^
//------------------------------------------------------------------------------
Thread::Thread(void* p_data, ThreadProcedure* p_thread_procedure)
    : h_thread_(nullptr),
      thread_id_(0),
      p_function_data(nullptr),
      is_suspend_(true) {
  // �X���b�h�f�[�^�̍쐬
  p_function_data = new FunctionData(p_data, p_thread_procedure);
}

//==============================================================================
// �f�X�g���N�^
//------------------------------------------------------------------------------
Thread::~Thread() {
  // �n���h���̉��
  CloseHandle(h_thread_);
  if(p_function_data != nullptr) {
    delete p_function_data;
    p_function_data = nullptr;
  }
}

//==============================================================================
// �X���b�h���쐬���A�J�n����B
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
// �X���b�h���I������B
//------------------------------------------------------------------------------
void Thread::End(void) {
  p_function_data->is_exit = true;
}

//==============================================================================
// �N�����̃X���b�h���ꎞ��~������B
//==============================================================================
void Thread::Suspend(void) {
  // if �X���b�h���~�܂��Ă����� �������Ȃ�
  if (is_suspend_) {
    return;
  }

  // �X���b�h�̒�~
  const int ret = SuspendThread(h_thread_);
  if (ret == -1) {
    return;
  }
  is_suspend_ = true;
}

//==============================================================================
// �X���b�h���ĊJ����
//------------------------------------------------------------------------------
void Thread::Resume(void) {
  // if �X���b�h�������Ă����� �������Ȃ�
  if (!is_suspend_) {
    return;
  }

  // �X���b�h�̍ĊJ
  const int ret = ResumeThread(h_thread_);
  if (ret == -1) {
    return;
  }
  is_suspend_ = false;
}

//==============================================================================
// �X���b�h�̎����m�F
//------------------------------------------------------------------------------
bool Thread::ConfirmDeath(void) const {
  //return WAIT_OBJECT_0 == WaitForSingleObject(h_thread_, 0);
  DWORD exit_code;
  GetExitCodeThread(h_thread_, &exit_code);

  return exit_code != STILL_ACTIVE;
}
