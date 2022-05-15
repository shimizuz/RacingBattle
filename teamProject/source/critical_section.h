//==============================================================================
//
// 排他処理クラス[ciritical_section.h]
// Author : Toshihiko Tsukamoto
//          Kajiya Ryusei
//
// 用途：
//  マルチスレッドで排他処理を行うクラス。
//  具体的には、特定のブロック内の処理を排他制御することができる。
//
// 使用方法：
//  基本コンストラクタとデストラクタで自動で初期化と終了処理をしています。
//  実際にやることは
//   ① ciritical_section::CiriticalSection型のインスタンス生成
//   ② ciritical_section::CiriticalSection::Lock型のインスタンス生成
//  ①は使いたい人が適当に作って持っといてください。
//  ②は排他処理を行いたいブロックの中に書いてください。
//   
// [ex]
// // クリティカルセクションを生成
// ciritical_section::CiriticalSection cs;
// 
// // 複数スレッドが通る関数
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
// クリティカルセクションを生成（と初期化と終了処理）を自動するクラス
//==============================================================================
class CiriticalSection {
 public:
  // コンストラクタ
  CiriticalSection(){
    InitializeCriticalSection(&critical_section_);
  }
  // デストラクタ
  virtual ~CiriticalSection(){
    DeleteCriticalSection(&critical_section_);
  }
 private:
  // スコープが外れた時にデストラクタで呼ぶためのコピー変数
  CRITICAL_SECTION critical_section_;
 public:
  //==============================================================================
  // クリティカルセクションの排他処理（ロック）を行うクラス
  // このクラスインスタンスがスコープを外れた時に自動でロックは解除される
  //==============================================================================
  class Lock {
   public:
    // コンストラクタ
    Lock(CiriticalSection& cs){
      // アクセス権利取得
      EnterCriticalSection(&cs.critical_section_);
      // コピー
      critical_section_ = &cs.critical_section_;
    }
    // デストラクタ
    virtual ~Lock(){
      // アクセス権利解放
      LeaveCriticalSection(critical_section_);
    }
   private:
    // スコープが外れた時にデストラクタで呼ぶためのコピー変数
    LPCRITICAL_SECTION critical_section_;
   };
};
#endif  // VG_DEBUG_CRITICAL_SECTION_H_
//EOF