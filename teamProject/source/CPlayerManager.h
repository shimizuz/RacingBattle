//==============================================================================
//
// プレイヤーマネージャ
// Author : Shimizu Shoji
//
// プレイヤーのマネージャクラスです。
// マネージャといってもほぼマネージングしないんですけどね。
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class declaration
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CPlayer;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ヘッダに書いてあります。
class CPlayerManager {
public:
	// const
	static const int kNumPlayers = 4;

	// ctor
	CPlayerManager();

	// dtor
	~CPlayerManager();

	// プレイヤーの取得
	CPlayer* GetPlayer(int id) {
		_CheckRange(id);
		return m_pPlayers[id];
	}
	
  // ミューテータ
  void SetPosition(int id, const CVector& position);
  void SetRotation(int id, const CVector& rotation);

private:
	void _CheckRange(int id);

	CPlayer* m_pPlayers[kNumPlayers];
};

