#include "R_2D.h"

void R_2D::Init(const wchar_t  texturepass[38]) {        //2023-12-18(月)　追加　2D初期化



	// 使用するシェーダーを生成
	shader.SetShader(
		"shader/unlitTextureVS.hlsl",				// 頂点シェーダ
		"shader/unlitTexturePS.hlsl");				// ピクセルシェーダ
	


	// テクスチャ読み込み
	DirectX::CreateWICTextureFromFile(
		Renderer::GetDevice(),
		texturepass,
		nullptr,
		&Texture);


	assert(Texture);


	// 頂点バッファ生成
	VERTEX_3D vertex[4];

	vertex[0].Position = Vector3(0.0f, 0.0f, 1.0f);
	vertex[0].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = Vector4(1.0f, 1.0f, 1.0f, alpha);
	vertex[0].TexCoord = Vector2(0.0f, 0.0f);


	vertex[1].Position = Vector3(width, 0.0f, 1.0f);
	vertex[1].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = Vector4(1.0f, 1.0f, 1.0f, alpha);
	vertex[1].TexCoord = Vector2(1.0f, 0.0f);


	vertex[2].Position = Vector3(0.0f, height, 1.0f);
	vertex[2].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = Vector4(1.0f, 1.0f, 1.0f, alpha);
	vertex[2].TexCoord = Vector2(0.0f, 1.0f);


	vertex[3].Position = Vector3(width, height, 1.0f);
	vertex[3].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = Vector4(1.0f, 1.0f, 1.0f, alpha);
	vertex[3].TexCoord = Vector2(1.0f, 1.0f);


	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;


	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &VertexBuffer);

	// マテリアル初期化
	MATERIAL mtrl;
	mtrl.Ambient = Color(1, 1, 1, 1);
	mtrl.Diffuse = Color(1, 1, 1, 1);
	mtrl.Emission = Color(0, 0, 0, 0);
	mtrl.Specular = Color(0, 0, 0, 0);
	mtrl.Shininess = 0;
	mtrl.TextureEnable = TRUE;

	material.Init(mtrl);

}



void R_2D::Draw() {        //2023-12-18(月)　追加　2D描画


	// 2D描画用のカメラ処理実行
  	Camera::Draw2D();

	// シェーダーをGPUにセット
	shader.SetGPU();


	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);


	// マテリアル設定
	material.SetGPU();

	// テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &Texture);

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);


	//頂点データ書き換え       GPUに転送　MapUnMap
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(VertexBuffer, 0,
	D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	//左上
	vertex[0].Position = Vector3(-(width / 2),-(height / 2),depth);
	vertex[0].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = Vector4(1.0f, 1.0f, 1.0f, alpha);
	vertex[0].TexCoord = Vector2(0.0f, 0.0f);

	//右上
	vertex[1].Position = Vector3(+(width / 2), -(height / 2), depth);
	vertex[1].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = Vector4(1.0f, 1.0f, 1.0f, alpha);
	vertex[1].TexCoord = Vector2(1.0f, 0.0f);

	//左下
	vertex[2].Position = Vector3(-(width / 2), +(height / 2), depth);
	vertex[2].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = Vector4(1.0f, 1.0f, 1.0f, alpha);
	vertex[2].TexCoord = Vector2(0.0f, 1.0f);

	//右下
	vertex[3].Position = Vector3(+(width / 2), +(height / 2), depth);
	vertex[3].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = Vector4(1.0f, 1.0f, 1.0f, alpha);
	vertex[3].TexCoord = Vector2(1.0f, 1.0f);


	Renderer::GetDeviceContext()->Unmap(VertexBuffer, 0);


	//マトリクスを計算
	Matrix mtx;
	DX11MakeWorldMatrixRadian(
		mtx,
		scale,
		rotation,
		position
	);

	//ワールドマトリクスをセット
	Renderer::SetWorldMatrix(&mtx);
	

	// ポリゴン描画
	Renderer::GetDeviceContext()->Draw(4, 0);
	
}



void R_2D::Exit() {

	VertexBuffer->Release();
	material.Uninit();
	Texture->Release();
}


void R_2D::TextureChange(const wchar_t* texturepass) {     //2023-1-18(木)　追加　テクスチャ更新　

	// テクスチャ読み込み
	DirectX::CreateWICTextureFromFile(
		Renderer::GetDevice(),
		texturepass,
		nullptr,
		&Texture);

	assert(Texture);

}


//セッター
void R_2D::SetWidth(float t_width) {                    //2023-12-19(火)　追加　横幅

	width = t_width;
}

void R_2D::SetHeight(float t_height) {                  //2023-12-19(火)　追加　縦幅

	height = t_height;
}

void R_2D::SetPosition(DirectX::XMFLOAT3 pos) {         //2023-12-19(火)　追加　位置

	position = pos;
}

void R_2D::SetRotation(DirectX::XMFLOAT3 rot) {         //2023-12-19(火)　追加　角度

	rotation = rot;
}

void R_2D::SetScale(DirectX::XMFLOAT3 scl) {            //2023-12-19(火)　追加　拡縮

	scale = scl;
}
void R_2D::SetAlpha(float al) {                                  //2024-1-11(木)　追加　透明度

	alpha = al;
}


//ゲッター
DirectX::XMFLOAT3 R_2D::GetPos() {           //2023-12-21(木)　追加　位置取得　

	return position;
}
DirectX::XMFLOAT3 R_2D::GetScl() {           //2023-12-21(木)　追加　拡縮　

	return scale;
}
float R_2D::GetAlpha() {                     //2023-1-24(水)　追加　透明度取得

	return alpha;
}

void R_2D::SetDepth_ON() {                   //2023-1-18(木)　追加　2Dを奥に描画する

	depth = 1.0f;        //深度を入れる
}
