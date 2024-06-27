#include   "Model_Render.h"

using namespace DirectX::SimpleMath;


void Model_Render::Init(std::string modelname) {        //2023-12-13(水)　編集　モデルメッシュ・レンダラー初期化


	shader.SetShader(
		"shader/unlitTextureVS.hlsl",				// 頂点シェーダ
		"shader/unlitTexturePS.hlsl");				// ピクセルシェーダ


	// メッシュ生成（ジオメトリデータ）
	staticmesh.Init(modelname);

	// 描画の為のデータ生成
	staticmeshrenderer.Init(staticmesh);

	Model_VerCalc();
}


void Model_Render::Edit_Update() {


	if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_P)) {

		edit_sel = edit_sel + 1;

		if (edit_sel > 1) {

			edit_sel = 0;
		}
	}

	float position_vul = 0.2f;
	float rotation_vul = 0.1f;


	switch (edit_sel) {

	case 0:   //位置変更

		     
		    
		    if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_L)) {
		    
		    	model_srt.position.x += position_vul;
		    }
		    if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_J)) {
		    
		    	model_srt.position.x -= position_vul;
		    }
		    if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_I)) {
		    
		    	model_srt.position.y += position_vul;
		    }
		    if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_K)) {
		    
		    	model_srt.position.y -= position_vul;
		    }
		    if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_V)) {
		    
		    	model_srt.position.z += position_vul;
		    }
		    if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_B)) {
		    
		    	model_srt.position.z -= position_vul;
		    }
		    

		    break;

		case 1: //角度

	

			if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_L)) {

				model_srt.rotation.x += rotation_vul;
			}
			if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_J)) {

				model_srt.rotation.x -= rotation_vul;
			}
			if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_I)) {

				model_srt.rotation.y += rotation_vul;
			}
			if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_K)) {

				model_srt.rotation.y -= rotation_vul;
			}
			if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_V)) {

				model_srt.rotation.z += rotation_vul;
			}
			if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_B)) {

				model_srt.rotation.z -= rotation_vul;
			}
			break;


		case 2: //拡縮

			float scale_vul = 0.1f;

			if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_L)) {

				model_srt.scale.x += scale_vul;
			}
			if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_J)) {

				model_srt.scale.x -= scale_vul;
			}
			if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_I)) {

				model_srt.scale.y += scale_vul;
			}
			if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_K)) {

				model_srt.scale.y -= scale_vul;
			}
			if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_V)) {

				model_srt.scale.z += scale_vul;
			}
			if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_B)) {

				model_srt.scale.z -= scale_vul;
			}
			break;
	}

}



void Model_Render::Parent_Draw() {

	shader.SetGPU();

	Matrix mtx = Create_Parent_Mat();    //マトリクスを作成

	// GPUに行列をセットする
	Renderer::SetWorldMatrix(&mtx);

	// モデル描画
	staticmeshrenderer.Draw();

}


void Model_Render::Child_Draw(Matrix parent_mat) {      //2023-12-13(水)　編集　子描画

	shader.SetGPU();

	Matrix mtx = Create_Child_Mat(parent_mat);    //マトリクスを作成

	// GPUに行列をセットする
	Renderer::SetWorldMatrix(&mtx);

	// モデル描画
	staticmeshrenderer.Draw();

}


void Model_Render::GrandChild_Draw(Matrix parent_mat ,Matrix child_mat) {      //2023-12-13(水)　編集　孫描画

	shader.SetGPU();

	Matrix mtx = Create_GrandChild_Mat(parent_mat , child_mat);    //マトリクスを作成

	// GPUに行列をセットする
	Renderer::SetWorldMatrix(&mtx);

	// モデル描画
	staticmeshrenderer.Draw();

}


void Model_Render::Exit() {


	staticmeshrenderer.Uninit();

}


void Model_Render::Model_VerCalc() {      //2023-12-24(日)　編集　頂点の最大と最小を計算


	std::vector<VERTEX_3D> vertices = staticmesh.GetVertices();    //頂点データを取得

	Vector3 max;
	Vector3 min;

	// 最大値と最小値を求める
	min = max = vertices[0].Position;
	for (auto& v : vertices) {

		if (min.x > v.Position.x) min.x = v.Position.x;
		if (min.y > v.Position.y) min.y = v.Position.y;
		if (min.z > v.Position.z) min.z = v.Position.z;

		if (max.x < v.Position.x) max.x = v.Position.x;
		if (max.y < v.Position.y) max.y = v.Position.y;
		if (max.z < v.Position.z) max.z = v.Position.z;
	}

	//格納
	model_info.min = min;
	model_info.max = max;

	// 中心を求める
	model_info.center = (max - min) * 0.5f;

	// 長さを設定
	DirectX::SimpleMath::Vector3 len;
	len = model_info.max - model_info.min;

	model_info.length.x = fabs(len.x);
	model_info.length.y = fabs(len.y);
	model_info.length.z = fabs(len.z);

}






Matrix Model_Render::Create_Parent_Mat() {    //2023-12-13(水)　編集　親マトリクス作成


	Matrix parent_mtx;

	DX11MakeWorldMatrixRadian(
		parent_mtx,
		model_srt.scale,
		model_srt.rotation,
		model_srt.position
	);

	return parent_mtx;
}



Matrix Model_Render::Create_Child_Mat(Matrix parent_mat) {    //2023-12-13(水)　編集　子マトリクス作成


	Matrix child_mtx;
	Matrix parent_mtx = parent_mat;   //親マトリクスを格納

	DX11MakeWorldMatrixRadian(
		child_mtx,
		model_srt.scale,
		model_srt.rotation,
		model_srt.position
	);


	child_mtx = child_mtx * parent_mtx;      //親子関係にする


	return child_mtx;
}


DirectX::SimpleMath::Matrix Model_Render::Create_GrandChild_Mat(DirectX::SimpleMath::Matrix parent_mat, DirectX::SimpleMath::Matrix child_mat) {     //2023-1-2(火)　編集　孫マトリクス作成



	Matrix mtx;
	Matrix grandchild_mtx;
	Matrix child_mtx = child_mat;
	Matrix parent_mtx = parent_mat;


	DX11MakeWorldMatrixRadian(
		grandchild_mtx,
		model_srt.scale,
		model_srt.rotation,
		model_srt.position
	);

    
	mtx = grandchild_mtx * child_mtx * parent_mtx;    //孫、子、親関係を作る

	return mtx;
}



//セッター
void Model_Render::SetModelPos(DirectX::XMFLOAT3 pos) {    //2023-12-13(水)　追加　セットポジション

	model_srt.position = pos;
}
void Model_Render::SetModelRot(DirectX::XMFLOAT3 rot) {    //2023-12-13(水)　追加　セットローテーション

	model_srt.rotation = rot;
}
void  Model_Render::SetModelScl(DirectX::XMFLOAT3 scl) {   //2023-12-13(水)　追加　セットスケール

	model_srt.scale = scl;
}
void Model_Render::SetModel_SRT(Model_SRT srt) {           //2023-12-13(水)　追加　セットSRT

	model_srt = srt;
}
void Model_Render::SetCameraForward(DirectX::SimpleMath::Vector3 c_front, DirectX::SimpleMath::Vector3 c_right) {     //2024-1-24(水)　追加　方向セット

	camera_forward.c_front = c_front;
	camera_forward.c_right = c_right;
}


//ゲッター
Matrix Model_Render::Get_Parent_Mat() {              //2023-12-13(水)　追加　ゲット親マトリクス

	Matrix mtx = Create_Parent_Mat();   //マトリクス作成

	return mtx;
}
Matrix Model_Render::Get_Child_Mat(Matrix parent_mat) {              //2023-1-2(水)　追加　ゲット子マトリクス

	Matrix mtx = Create_Child_Mat(parent_mat);

	return mtx;
}
DirectX::XMFLOAT3 Model_Render::GetModelPos(){       //2023-12-13(水)　追加　ゲットポジション

	return model_srt.position;
}
DirectX::XMFLOAT3 Model_Render::GetModelRot() {      //2023-12-13(水)　追加　ゲットローテーション

	return model_srt.rotation;
}
DirectX::XMFLOAT3 Model_Render::GetModelScl() {      //2023-12-13(水)　追加　ゲットスケール

	return model_srt.scale;
}
Model_SRT Model_Render::GetModel_SRT() {             //2023-12-14(木)　追加　ゲットSRT

	return model_srt;
}
DirectX::XMFLOAT3 Model_Render::GetModel_Min() {     //2023-12-24(日)　追加  モデルの最小頂点値を返す

	return model_info.min;
}
DirectX::XMFLOAT3 Model_Render::GetModel_Man() {     //2023-12-24(日)　追加  モデルの最大頂点値を返す

	return model_info.max;
}
DirectX::XMFLOAT3 Model_Render::GetModel_Center() {   //2023-12-24(日)　追加　モデルの中心点返す

	return model_info.center;
}
DirectX::XMFLOAT3 Model_Render::GetModel_Length() {      //2023-12-24(日)　追加　モデルの長さを返す

	return model_info.length;
}



//セーブ関連

void Model_Render::Save(const char* filename) {        //2023-12-14(木)　追加　ファイルに書き込み


	Model_SRT model = model_srt;

	FILE* save;
	fopen_s(&save,filename, "wb");

	if (save == NULL) {

		MessageBox(NULL, "ファイルを開けません",filename, MB_ABORTRETRYIGNORE);
	}

	fwrite(&model, sizeof(model), 1, save);      //データを書き込み
	fclose(save);


}


void Model_Render::SetSave(const char* filename) {      //2023-12-14(木)　追加　セーブ情報をセット


	FILE* save;
		errno_t err = fopen_s(&save, filename, "rb");
		Model_SRT srt;
	
		if (err == 0 && save != nullptr) {
			// ファイルが正常に開かれた場合の処理
	
			fread(&srt, sizeof(srt), 1, save);   //データを読み込む
	
			fclose(save); // ファイルを閉じる
		}
		else if (err == ENOENT) {     //ファイルない場合は閉じる
	
			fclose(save); // ファイルを閉じる
		}
		

		model_srt = srt;  //セーブしたものをセット

}
