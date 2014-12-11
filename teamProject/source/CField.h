//==============================================================================
//
// �t�B�[���h
// Author : Shimizu Shoji
//
// ���[���h���W����t�B�[���h���W�ւ̕ϊ��͕ʃN���X�ōs���Ă��������B
// �܂��A����Ώۂ��ǂ��̃t�B�[���h�P�ʂƏՓ˔������邩�́A�ʃN���X�ōs���Ă��������B
// ���̃N���X�́A�����܂ł��t�B�[���h�P�ʂ̏Փˏ��������A�₢���킹�ɕԓ����邾���ł��B
//
//==============================================================================
#pragma once
#ifndef CFIELD_H_
#define CFIELD_H_
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CField {
public:
  enum Direction {
    kUp = 1 << 0,
    kDown = 1 << 1,
    kRight = 1 << 2,
    kLeft = 1 << 3
  };

  // ctor
  CField();

  // dtor
  ~CField();

  // �X�V�������s���B
  void Update(void);

  // �`�揈�����s���B
  void Draw(void);

  // �N��������擾����B
  // �N���������w�肵�āA���̕�������̔����Ԃ��܂��B
  // �^�Ȃ�N���\�A���Ȃ�N���s�\�ɂȂ�܂��B
  bool CanIntrude(unsigned int w, unsigned int h, Direction direction) const;

private:
  unsigned int* p_possible_intrusion_map_;
};

#endif  // CFIELD_H_