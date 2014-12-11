//==============================================================================
//
// フィールド
// Author : Shimizu Shoji
//
// ワールド座標からフィールド座標への変換は別クラスで行ってください。
// また、判定対象がどこのフィールド単位と衝突判定を取るかは、別クラスで行ってください。
// このクラスは、あくまでもフィールド単位の衝突情報を持ち、問い合わせに返答するだけです。
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

  // 更新処理を行う。
  void Update(void);

  // 描画処理を行う。
  void Draw(void);

  // 侵入判定を取得する。
  // 侵入方向を指定して、その方向からの判定を返します。
  // 真なら侵入可能、負なら侵入不可能になります。
  bool CanIntrude(unsigned int w, unsigned int h, Direction direction) const;

private:
  unsigned int* p_possible_intrusion_map_;
};

#endif  // CFIELD_H_