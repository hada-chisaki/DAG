#include	"CBillboard.h"

using namespace DirectX::SimpleMath;

// ビルボード描画用の姿勢を表す行列を計算
Matrix CBillboard::CalcBillboardMatrix(Matrix viewmtx) {

	Matrix billboardmtx{};

	// ビュー変換行列を転置（正規直行行列は転置が）
	billboardmtx = viewmtx.Transpose();

	// 不要成分をクリア
	billboardmtx._41 = billboardmtx._42 = billboardmtx._43 = 0.0f;
	billboardmtx._14 = billboardmtx._24 = billboardmtx._34 = 0.0f;
	billboardmtx._44 = 1.0f;

	return billboardmtx;
}

// 描画
void CBillboard::Draw(
	DirectX::SimpleMath::Matrix viewmtx,		// ビュー変換行列
	DirectX::SimpleMath::Vector3 pos)			// 位置
{

	// ビルボード描画用の行列を作成する
	m_WorldMtx = CalcBillboardMatrix(viewmtx);

	// 位置をセット
	m_WorldMtx._41 = pos.x;
	m_WorldMtx._42 = pos.y;
	m_WorldMtx._43 = pos.z;

	Matrix mtx{};
	DirectX::XMFLOAT3 rot{};

	DX11MakeWorldMatrix(
		mtx,
		m_scale,
		rot,
		m_position
	);

	m_WorldMtx = mtx * m_WorldMtx;

	// 行列をセットして描画
	Renderer::SetWorldMatrix(&m_WorldMtx);
	m_meshrenderer->Draw();
}

void   CBillboard::SetPos(DirectX::XMFLOAT3 pos) {    //位置セット

	m_position = pos;
}
void   CBillboard::SetScale(DirectX::XMFLOAT3 scale) {  //スケールセット

	m_scale = scale;
}