#include "Effect_PlaneMesh.h"


void CPlaneMesh_Effect::Init(
	Effect_Info effect_info,
	DirectX::SimpleMath::Color color,
	DirectX::SimpleMath::Vector3 normal,
	bool xzflag) {

	

	// サイズセット（幅と高さ）（XY平面）
	m_width = static_cast<float>(effect_info.width);
	m_height = static_cast<float>(effect_info.height);

	// 法線ベクトル
	m_normal = normal;

	// 頂点カラー
	m_color = color;

	anim_div_x = effect_info.anim_div_x;  //アニメ画像の分割数ｘ
	anim_div_y = effect_info.anim_div_y;  //アニメ画像の分割数ｙ

	anim_kankaku = effect_info.anim_kankaku;  //アニメの間隔

	if (xzflag == true) {
		// 頂点データ生成
		CreateVertexXZ();
	}
	else {
		// 頂点データ生成
		CreateVertex();
	}
	// インデックスデータ生成
	CreateIndex();

}
void CPlaneMesh_Effect::CreateVertex() {    //頂点データ作成

	// 頂点データクリア
	m_vertices.clear();

	int m_divY = 1;
	int m_divX = 1;

	for (unsigned int y = 0; y <= m_divY; y++) {
		VERTEX_3D	vtx{};

		for (unsigned int x = 0; x <= m_divX; x++) {

			// 頂点座標セット
			vtx.Position.x = -m_width / 2.0f + x * m_width / m_divX;
			vtx.Position.y = -m_height / 2.0f + y * m_height / m_divY;
			vtx.Position.z = 0.0f;

			// 法線ベクトルセット
			vtx.Normal = m_normal;				    // 法線をセット
			vtx.Diffuse = m_color;					// カラー値セット

			// 繰り返しに対応（テクスチャの）
			float texu = 1.0f * m_divX  / anim_div_x;
			float texv = 1.0f * m_divY  / anim_div_y;
			vtx.TexCoord.x = (texu * x / m_divX);
			vtx.TexCoord.y = texv - (texv * y / m_divY);

			m_vertices.emplace_back(vtx);		// 頂点データセット
		}
	}
}
void CPlaneMesh_Effect::CreateVertexXZ() {  //頂点データXZ作成

	// 頂点データクリア
	m_vertices.clear();

	int m_divY = 1;
	int m_divX = 1;

	for (unsigned int y = 0; y <= m_divY; y++) {
		VERTEX_3D	vtx{};

		for (unsigned int x = 0; x <= m_divX; x++) {

			// 頂点座標セット
			vtx.Position.x = -m_width / 2.0f + x * m_width / m_divX;
			vtx.Position.y = 0.0f;
			vtx.Position.z = -m_height / 2.0f + y * m_height / m_divY;

			// 法線ベクトルセット
			vtx.Normal = m_normal;				// 法線をセット
			vtx.Diffuse = m_color;			    // カラー値セット

			// 繰り返しに対応（テクスチャの）
			float texu = 1.0f * m_divX / anim_div_x;
			float texv = 1.0f * m_divY / anim_div_y;

			vtx.TexCoord.x = (texu * x / m_divX);
			vtx.TexCoord.y = (texv * y / m_divY);


			m_vertices.emplace_back(vtx);		// 頂点データセット
		}
	}
}
void CPlaneMesh_Effect::CreateIndex() {     //インデックス作成

	int m_divY = 1;
	int m_divX = 1;

	// インデックスデータクリア
	m_indices.clear();

	// インデックス生成
	for (unsigned int y = 0; y < m_divY; y++) {
		for (unsigned int x = 0; x < m_divX; x++) {
			int count = (m_divX + 1) * y + x;		// 左下座標のインデックス

			// 下半分
			{
				FACE face{};

				face.idx[0] = count;						// 左下
				face.idx[1] = count + 1 + (m_divX + 1);		// 右上
				face.idx[2] = count + 1;					// 右

				m_indices.emplace_back(face.idx[0]);
				m_indices.emplace_back(face.idx[1]);
				m_indices.emplace_back(face.idx[2]);

			}

			// 上半分
			{
				FACE face{};
				face.idx[0] = count;						// 左下
				face.idx[1] = count + (m_divX + 1);			// 上
				face.idx[2] = count + (m_divX + 1) + 1;		// 右上

				m_indices.emplace_back(face.idx[0]);
				m_indices.emplace_back(face.idx[1]);
				m_indices.emplace_back(face.idx[2]);
			}
		}
	}
}
void CPlaneMesh_Effect::AnimUpdate() {      //テックス更新

	// 頂点データクリア
	m_vertices.clear();

	//プレーンの分割数
	int m_divY = 1;
	int m_divX = 1;

	//アニメ遷移計算
	float diffx = 1.0f / anim_div_x;
	float diffy = 1.0f / anim_div_y;


	// 頂点データクリア
	m_vertices.clear();

	for (unsigned int y = 0; y <= m_divY; y++) {
		VERTEX_3D	vtx{};

		for (unsigned int x = 0; x <= m_divX; x++) {

			// 頂点座標セット
			vtx.Position.x = -m_width / 2.0f + x * m_width / m_divX;
			vtx.Position.y = -m_height / 2.0f + y * m_height / m_divY;
			vtx.Position.z = 0.0f;

			// 法線ベクトルセット
			vtx.Normal = m_normal;				// 法線をセット
			vtx.Diffuse = m_color;					// カラー値セット

			// 繰り返しに対応（テクスチャの）
			float texu = 1.0f * m_divX / anim_div_x;
			float texv = 1.0f * m_divY / anim_div_y;

			vtx.TexCoord.x = (texu * x / m_divX) + animcnt_x * diffx;
			vtx.TexCoord.y =  texv - (texv * y / m_divY) + animcnt_y * diffy;

			m_vertices.emplace_back(vtx);		// 頂点データセット
		}
	}

	// アニメーション切り替え時間調整
	loopcnt++;

	if (loopcnt % anim_kankaku == 0) {

		animcnt_x++;
		animcnt_x = animcnt_x % anim_div_x;

		if (animcnt_x % anim_div_x == 0 && !only_one_line) {   //横が終わったら

			animcnt_y++;  //下に移動
			animcnt_y = animcnt_y % anim_div_y; //縦のライン終わったら０初めに戻す

			if (animcnt_y % anim_div_y == 0) {

				anim_loop_cnt++;
			}
		}
	}
}
void CPlaneMesh_Effect::AnimUpdate_XZ() {   //XZ軸用

	// 頂点データクリア
	m_vertices.clear();

	int m_divY = 1;
	int m_divX = 1;

	//アニメ遷移計算
	float diffx = 1.0f / anim_div_x;
	float diffy = 1.0f / anim_div_y;


	for (unsigned int y = 0; y <= m_divY; y++) {
		VERTEX_3D	vtx{};

		for (unsigned int x = 0; x <= m_divX; x++) {

			// 頂点座標セット
			vtx.Position.x = -m_width / 2.0f + x * m_width / m_divX;
			vtx.Position.y = 0.0f;
			vtx.Position.z = -m_height / 2.0f + y * m_height / m_divY;

			// 法線ベクトルセット
			vtx.Normal = m_normal;				// 法線をセット
			vtx.Diffuse = m_color;			    // カラー値セット

			// 繰り返しに対応（テクスチャの）
			float texu = 1.0f * m_divX  / anim_div_x;
			float texv = 1.0f * m_divY  / anim_div_y;

			vtx.TexCoord.x = (texu * x / m_divX) / animcnt_x * diffx;
			vtx.TexCoord.y = (texv * y / m_divY) / animcnt_y * diffy;


			m_vertices.emplace_back(vtx);		// 頂点データセット
		}
	}

	// アニメーション切り替え時間調整
	loopcnt++;

	if (loopcnt % anim_kankaku == 0) {

		animcnt_x++;
		animcnt_x = animcnt_x % anim_div_x;

		if (animcnt_x % anim_div_x == 0 && !only_one_line) {   //横が終わったら

			animcnt_y++;  //下に移動
			animcnt_y = animcnt_y % anim_div_y; //縦のライン終わったら０初めに戻す

			if (animcnt_y % anim_div_y== 0) {

				anim_loop_cnt++;
			}
		}
	}
}


void CPlaneMesh_Effect::ResetAnim() {       //アニメループをリセット

	loopcnt = 0;

	animcnt_x = 0;
	animcnt_y = 0;

	anim_loop_cnt = 0;
}

int  CPlaneMesh_Effect::GetAnimLoop() {     //アニメのループ数を取得

	return anim_loop_cnt;
}