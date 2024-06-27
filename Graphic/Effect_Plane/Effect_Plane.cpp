#include "Effect_Plane.h"

Effect_Plane::Effect_Plane(const wchar_t* filename , Effect_Info effect_info) {     //コンストラクタ

	// 使用するシェーダーを生成(billboard用)
	shader.SetShader(
		"shader/unlitTextureVS.hlsl",					// 頂点シェーダ
		"shader/unlitTexturePS.hlsl");				    // ピクセルシェーダ

	
	// ビルボード用のメッシュ生成
	plane_mesh.Init(
		effect_info,
		effect_info.color,
		Vector3(0.0f,0.0f,-1.0f),
		false
	);

	// ビルボード用マテリアル
	MATERIAL mtrl{};
	mtrl.Ambient = Color(0, 0, 0, 0);
	mtrl.Diffuse = effect_info.color;
	mtrl.Specular = Color(0, 0, 0, 0);
	mtrl.Shininess = 0;
	mtrl.Emission = Color(0, 0, 0, 0);
	mtrl.TextureEnable = true;

	material.Init(mtrl);

	mesh_renderer.Init(plane_mesh);

	// ビルボード用テクスチャ読み込み
	DirectX::CreateWICTextureFromFile(
		Renderer::GetDevice(),
		filename,
		nullptr,
		&g_Texture);

	assert(g_Texture);
}
Effect_Plane::~Effect_Plane() {    //デストラクタ

	material.Uninit();
}

void Effect_Plane::Update() {      //更新

	plane_mesh.AnimUpdate();
	anim_loop_cnt = plane_mesh.GetAnimLoop();   //アニメループ取得
	
	mesh_renderer.Init(plane_mesh);
}
void Effect_Plane::Draw() {        //描画

	// ビルボード描画
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture);
	shader.SetGPU();							// ビルボード用シェーダーをセット
	material.SetGPU();						    // ビルボード用マテリアルをセット
	billboard.SetBeforeDraw(&mesh_renderer);
	billboard.Draw(m_view_matrix, m_parent_pos);

}

bool Effect_Plane::LimitedTimesDraw(int loop_times) {  //限られたループの間だけ描画

	if (anim_loop_cnt <= loop_times) {    //アニメループが指定した回数以下の時描画

		// ビルボード描画
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture);
		shader.SetGPU();							// ビルボード用シェーダーをセット
		material.SetGPU();						    // ビルボード用マテリアルをセット
		billboard.SetBeforeDraw(&mesh_renderer);
		billboard.Draw(m_view_matrix, m_parent_pos);

	}

	if (anim_loop_cnt == loop_times) return true;

	return false;
}

void Effect_Plane::StartDraw() {                       //描画を開始する

	plane_mesh.ResetAnim();  //アニメ情報を初期化
	
}

