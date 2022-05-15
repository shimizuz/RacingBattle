//==============================================================================
//
// �r�������N���X[ciritical_section.h]
// Author : Toshihiko Tsukamoto
//          Kajiya Ryusei
//
// �p�r�F
//  �}���`�X���b�h�Ŕr���������s���N���X�B
//  ��̓I�ɂ́A����̃u���b�N���̏�����r�����䂷�邱�Ƃ��ł���B
//
// �g�p���@�F
//  ��{�R���X�g���N�^�ƃf�X�g���N�^�Ŏ����ŏ������ƏI�����������Ă��܂��B
//  ���ۂɂ�邱�Ƃ�
//   �@ ciritical_section::CiriticalSection�^�̃C���X�^���X����
//   �A ciritical_section::CiriticalSection::Lock�^�̃C���X�^���X����
//  �@�͎g�������l���K���ɍ���Ď����Ƃ��Ă��������B
//  �A�͔r���������s�������u���b�N�̒��ɏ����Ă��������B
//   
// [ex]
// // �N���e�B�J���Z�N�V�����𐶐�
// ciritical_section::CiriticalSection cs;
// 
// // �����X���b�h���ʂ�֐�
// pointer AnyThreadThoughtProc()
// {
//   ciritical_section::CiriticalSection::Lock a(cs);
//   Anything();
// }
// 
//==============================================================================
#pragma once
#ifndef VG_DEBUG_CRITICAL_SECTION_H_
#define VG_DEBUG_CRITICAL_SECTION_H_

//==============================================================================
// �N���e�B�J���Z�N�V�����𐶐��i�Ə������ƏI�������j����������N���X
//==============================================================================
class CiriticalSection {
 public:
  // �R���X�g���N�^
  CiriticalSection(){
    InitializeCriticalSection(&critical_section_);
  }
  // �f�X�g���N�^
  virtual ~CiriticalSection(){
    DeleteCriticalSection(&critical_section_);
  }
 private:
  // �X�R�[�v���O�ꂽ���Ƀf�X�g���N�^�ŌĂԂ��߂̃R�s�[�ϐ�
  CRITICAL_SECTION critical_section_;
 public:
  //==============================================================================
  // �N���e�B�J���Z�N�V�����̔r�������i���b�N�j���s���N���X
  // ���̃N���X�C���X�^���X���X�R�[�v���O�ꂽ���Ɏ����Ń��b�N�͉��������
  //==============================================================================
  class Lock {
   public:
    // �R���X�g���N�^
    Lock(CiriticalSection& cs){
      // �A�N�Z�X�����擾
      EnterCriticalSection(&cs.critical_section_);
      // �R�s�[
      critical_section_ = &cs.critical_section_;
    }
    // �f�X�g���N�^
    virtual ~Lock(){
      // �A�N�Z�X�������
      LeaveCriticalSection(critical_section_);
    }
   private:
    // �X�R�[�v���O�ꂽ���Ƀf�X�g���N�^�ŌĂԂ��߂̃R�s�[�ϐ�
    LPCRITICAL_SECTION critical_section_;
   };
};
#endif  // VG_DEBUG_CRITICAL_SECTION_H_
//EOF