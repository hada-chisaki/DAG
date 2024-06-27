#include "Plane_R.h"
#include "Collision.h"


void Plane_R::Init(const char* texture_filename) {           //2024-1-13(土)　追加　地面初期化


	// 使用するシェーダーを生成
	shader.SetShader(
		"shader/unlitTextureVS.hlsl",				// 頂点シェーダ
		"shader/unlitTexturePS.hlsl");				// ピクセルシェーダ


	// 床メッシュ生成
	planemesh.Init(
		plane_info.div_x, 
		plane_info.div_y,		          // 分割数
		plane_info.width,			      // サイズ
		plane_info.height,			      // サイズ
		plane_info.color,		          // 頂点カラー
		plane_info.normal,                 // 法線ベクトル
		plane_info.xz_flag
		);


	makepalenequatation();

	// メッシュレンダラ生成（床用）
	meshrenderer.Init(planemesh);

	// テクスチャ読み込み
	ID3D11Device* dev;
	ID3D11DeviceContext* devcontext;

	dev = Renderer::GetDevice();
	devcontext = Renderer::GetDeviceContext();



	bool sts = CreateSRVfromFile(texture_filename, dev, devcontext, &srv);
	if (!sts) {
		MessageBox(nullptr, "CreateSRVfromFile error(MeshWallInit)", "error", MB_OK);
	}

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
void Plane_R::Update() {                                     //2024-1-13(土)　追加　地面更新


}
void Plane_R::Draw() {                                       //2024-1-13(土)　追加　地面描画

	Matrix mtx;

	// GPUに行列をセットする
	Renderer::SetWorldMatrix(&mtx);

	// 床用シェーダセット
	shader.SetGPU();

	// 床用マテリアルセット
	material.SetGPU();

	// GPUに行列をセットする
	DX11MakeWorldMatrix(
		mtx,
		plane_srt.scale,							// スケール
		plane_srt.rotation,							// 姿勢
		plane_srt.position);						// 位置

	Renderer::SetWorldMatrix(&mtx);

	// テクスチャをセット
	ID3D11DeviceContext* devcontext;
	devcontext = Renderer::GetDeviceContext();
	devcontext->PSSetShaderResources(0, 1, srv.GetAddressOf());

	// 床描画
	meshrenderer.Draw();

}
void Plane_R::Exit() {                                       //2024-1-13(土)　追加　地面終了


	material.Uninit();
}





//地面との当たり判定
void   Plane_R::makepalenequatation() {                   //2024-1-13(土)　


	for (unsigned int idx = 0; idx < planemesh.GetIndices().size() / 3; idx++) {
		CPlaneMesh::FACE f = planemesh.GetTriangle(idx);

		VERTEX_3D v0 = planemesh.GetVertices()[f.idx[0]];
		VERTEX_3D v1 = planemesh.GetVertices()[f.idx[1]];
		VERTEX_3D v2 = planemesh.GetVertices()[f.idx[2]];

		CPlane p;
		p.MakeEquatation(v0.Position, v1.Position, v2.Position);
		planes.emplace_back(p);
	}
}
float  Plane_R::GetFieldHeightBySqno(Vector3 pos) {                  //2024-1-13(土)　追加　現在の高さを求める


	float t;

	// 現在位置からのっかている四角形番号を取得
	int sqno = planemesh.GetSquareNo(pos);

	static float oldheight = 0;

	// 下面チェック
	{
		int idx = sqno * 2;

		// 面数分
		Vector3 up = { 0,1,0 };
		Vector3 startpoint = { pos.x,0,pos.z };
		Plane p = planes[idx].GetPlaneInfo().plane;
		Vector3 ans;


		bool sts = LinetoPlaneCross(p, startpoint, up, t, ans);
		if (sts) {
			sts = CheckInTriangle(
				planes[idx].GetPlaneInfo().p0,
				planes[idx].GetPlaneInfo().p1,
				planes[idx].GetPlaneInfo().p2, ans);
			if (sts) {
				oldheight = ans.y;
				return ans.y;
			}
		}

	}

	// 上面チェック
	{
		int idx = sqno * 2 + 1;

		// 面数分
		Vector3 up = { 0,1,0 };
		Vector3 startpoint = { pos.x,0,pos.z };
		Plane p = planes[idx].GetPlaneInfo().plane;
		Vector3 ans;

		bool sts = LinetoPlaneCross(p, startpoint, up, t, ans);
		if (sts) {
			sts = CheckInTriangle(
				planes[idx].GetPlaneInfo().p0,
				planes[idx].GetPlaneInfo().p1,
				planes[idx].GetPlaneInfo().p2, ans);
			if (sts) {
				oldheight = ans.y;
				return ans.y;
			}
		}
	}

	// 見つからなかった場合は０
	std::cout << "床なし" << "(" << sqno << ")" << std::endl;
	return oldheight;

}
float  Plane_R::GetFieldHeight(Vector3 pos) {                      //2024-1-13(土)　追加　現在の高さを求める

	float t;

	// 面数分
	for (unsigned int idx = 0; idx < planes.size(); idx++) {
		Vector3 up = { 0,1,0 };
		Vector3 startpoint = { pos.x,0,pos.z };
		Plane p = planes[idx].GetPlaneInfo().plane;
		Vector3 ans;

		bool sts = LinetoPlaneCross(p, startpoint, up, t, ans);
		if (sts) {
			sts = CheckInTriangle(
				planes[idx].GetPlaneInfo().p0,
				planes[idx].GetPlaneInfo().p1,
				planes[idx].GetPlaneInfo().p2, ans);
			if (sts) return ans.y;
		}

	}

	return 0;
}


//セッター
void Plane_R::SetPlaneInfo(Plane_Info info) {          //2024-1-15(月)　追加　PlaneInfoセット

	plane_info = info;
}
void Plane_R::SetPlaneSRT(Plane_SRT srt) {                          //2024-1-26(月)　編集　PlaneSRTセット

	plane_srt = srt;
}

//ゲッター
Plane_Info Plane_R::GetPlaneInfo() {                   //プレーンの情報を取得

	return plane_info;
}