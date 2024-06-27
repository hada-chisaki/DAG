#pragma once

#include	<simplemath.h>
#include	"CMesh.h"

class CBoxMesh : public CMesh {


	// 法線ベクトルを計算
	// 頂点座標をノーマライズ
	void Normalize(
		DirectX::SimpleMath::Vector3 vec,
		DirectX::SimpleMath::Vector3& Normal);

public:

	void Init(float width,
		float height,
		float depth,
		DirectX::SimpleMath::Color color);

	// 頂点データ生成
	void CreateVertex();
	// インデックス生成
	void CreateIndex();

private:

	DirectX::SimpleMath::Color m_color;
	float lengthx = 0.0f;
	float lengthy = 0.0f;
	float lengthz = 0.0f;
};


