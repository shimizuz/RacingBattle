//=============================================================================
//
// メッシュ地面の処理 [CMeshFieldGL.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
//多重定義防止
#ifndef __CMESHFIELDGL_H__
#define __CMESHFIELDGL_H__

//ヘッダーインクルード
#include "main.h"
#include "CScene.h"

//クラス定義
class CMeshFieldGL : public CScene
{
private:
	CVector			m_pos;							// ポジション
	CVector			m_rot;							// 回転
	CVector			m_scl;							// 拡縮
	LPCUSTOM_VERTEX	m_VtxBuffer;					// 頂点バッファ
	int*			m_indexBuffer;					// インデックスバッファ
	unsigned int	m_texture;						// テクスチャID格納
	int				m_nNumVertex;					// 総頂点数
	int				m_nNumPolygon;					// 総ポリゴン数
	int				m_nNumVertexIndex;				// 頂点の総インデックス数
	int				m_nNumBlockX, m_nNumBlockZ;		// ブロック数
	float			m_fSizeBlockX, m_fSizeBlockZ;	// ブロックサイズ
	CVector*		m_norBuffer;					// 法線バッファ
	static CVector	m_Vertex[4];					// 4隅の頂点
public:
	CMeshFieldGL(int nPriority = 3):CScene(nPriority){}
	virtual ~CMeshFieldGL(){}

	//初期化
	void Init(){}

	//初期化オーバーロード
	void Init(int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ,CVector pos,CVector rot,char *pTexPath);
	//更新
	void Update();
	//開放
	void Uninit();
	//描画
	void Draw();
	
	//座標取得
	CVector GetPosition(void)
	{
		return m_pos;
	}
	//座標設定
	void SetPosition(CVector pos)
	{
		m_pos = pos;	
	}
	//回転取得
	CVector GetRotate(void)
	{
		return m_rot;
	}
	//回転設定
	void SetRotate(CVector rot)
	{
		m_rot = rot;	
	}
	//拡縮取得
	CVector GetScale(void)
	{
		return m_scl;
	}
	//拡縮設定
	CVector SetScale(CVector scl)
	{
		m_scl = scl;
	}
	//生成
	static CMeshFieldGL* Create(int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ,CVector pos,CVector rot,char *pTexPath);
	//四隅取得
	static CVector GetVertex(int index)
	{
		return m_Vertex[index];
	}
	LPCUSTOM_VERTEX GetVerttexBuffer(int index)
	{
		return m_VtxBuffer;
	}
};


#endif