#pragma once
#include    "dx11mathutil.h"
#include	<SimpleMath.h>
#include	"CPlaneMesh.h"
#include	"CMeshRenderer.h"

// ビルボードクラス
class CBillboard {

	DirectX::XMFLOAT3 m_position{0.0f,0.0f ,0.0f};
	DirectX::XMFLOAT3 m_scale = {1.0f,1.0f,1.0f};

	CMeshRenderer* m_meshrenderer{};
	// ワールド変換行列
	DirectX::SimpleMath::Matrix m_WorldMtx{};
	//　ビュー変換行列からワールド変換行列を生成
	DirectX::SimpleMath::Matrix CalcBillboardMatrix(DirectX::SimpleMath::Matrix viewmtx);

public:

	// 描画前処理
	void SetBeforeDraw(
		CMeshRenderer* meshrenderer)
	{
		m_meshrenderer = meshrenderer;
	}

	// 描画
	void Draw(
		DirectX::SimpleMath::Matrix viewmtx,		// ビュー変換行列
		DirectX::SimpleMath::Vector3 parent_pos);			// 位置

	//セット
	void  SetPos(DirectX::XMFLOAT3 pos);
	void  SetScale(DirectX::XMFLOAT3 scale);
};
