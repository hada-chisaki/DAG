#include "Box_Col.h"
#include "Player.h"

//2023-11-30 明示宣言
#include "CMaterial.h"
#include "Collision.h"
#include "CDirectInput.h"
#include <DirectXMath.h>
#include "Logger.h"


#define _CRT_SECURE_NO_WARNINGS 


using namespace DirectX::SimpleMath;

Box_Col::Box_Col() {     //コンストラクタ

	box_model.Init();

	//OBB作成
	obb.Caliculate(box_model.GetVertices());   //ボックスの頂点を計算

}
Box_Col::~Box_Col() {    //デストラクタ

	box_model.Exit();
}

void Box_Col::Init(
) {

	box_model.Init();

	//OBB作成
	obb.Caliculate(box_model.GetVertices());   //ボックスの頂点を計算

}
void Box_Col::Edit_Update(int sel_srt,int sel_xyz) {

	box_model.EditUpdate(sel_srt, sel_xyz);
}



void Box_Col::Exit() {

	box_model.Exit();
}



//判定色付き
bool  Box_Col::CheckDraw(          //Editer用
	BoundingBoxOBB obbB,
	DirectX::SimpleMath::Color before_color,
	DirectX::SimpleMath::Color after_color
) {

	// OBB情報生成
	BoundingBoxOBB obbA;
	Matrix mtx = box_model.GetMatrix();

	DirectX::XMFLOAT3 scale = box_model.GetScale();
	obbA = obb.MakeOBB(mtx,scale);

	
	bool sts = HitCheckOBB(obbA, obbB);
	box_model.Draw(sts, before_color, after_color);
	
	//OBB描画
	mtx = obb.MakeWorldMtx(scale, mtx);
	Renderer::SetWorldMatrix(&mtx);           //ワールドマトリクスをセット


	return sts;
}



//通常使用
bool Box_Col::Draw(  BoundingBoxOBB obbB        
) {

	bool sts = false;

	if (flag_hitcheck_ON) {

		// OBB情報生成
		BoundingBoxOBB obbA;
		Matrix mtx = box_model.GetMatrix();

		DirectX::XMFLOAT3 scale = box_model.GetScale();
		obbA = obb.MakeOBB(mtx, scale);

	    sts = HitCheckOBB(obbA, obbB);

		//OBB描画
		mtx = obb.MakeWorldMtx(scale, mtx);
		Renderer::SetWorldMatrix(&mtx);           //ワールドマトリクスをセット

	}

	return sts;
}


 
//フラグ切り替え
void Box_Col::HitCheck_ON() {   //2023-12-18(月)　編集　フラグをtrueにする

	flag_hitcheck_ON = true;
}
void Box_Col::HitCheck_OFF() {  //2023-12-18(月)　編集　フラグをfalseにする

	flag_hitcheck_ON = false;
}




//セッター
void Box_Col::SetMat(Matrix parent_mat, Matrix child_mat) {

	box_model.SetMat(child_mat,parent_mat);
}
void Box_Col::SetBoxLength(DirectX::XMFLOAT3 length) {

	box_model.SetLength(length);
}
void Box_Col::SetBoxColEdit_Value(Edit_Value edit_value) {        //エディター用　量をセット

	box_model.SetEditSRT_Value(edit_value);
}



//ゲッター
BoundingBoxOBB Box_Col::GetBoundingBox() {


	// OBB情報生成
	BoundingBoxOBB box_obb;
	
	Matrix mtx = box_model.GetMatrix();

	DirectX::XMFLOAT3 scale = box_model.GetScale();
	box_obb = obb.MakeOBB(mtx, scale);
	

	return box_obb;
}




void Box_Col::Save(const char* filename) {       //2023-12-17(日)　追加　セーブ


	BoxInfo_SRTL srtl = box_model.GetBox_SRTL();

	FILE* save;
	fopen_s(&save, filename, "wb");

	if (save == NULL) {

		MessageBox(NULL, "ファイルを開けません", filename, MB_ABORTRETRYIGNORE);
	}

	fwrite(&srtl, sizeof(srtl), 1, save);      //データを書き込み
	fclose(save);

}


void Box_Col::SetSave(const char* filename) {     // //2023-12-17(日)　追加　セーブ書き出し


	FILE* save;
	errno_t err = fopen_s(&save, filename, "rb");
	BoxInfo_SRTL srtl;

	if (err == 0 && save != nullptr) {
		// ファイルが正常に開かれた場合の処理

		fread(&srtl, sizeof(srtl), 1, save);   //データを読み込む

		fclose(save); // ファイルを閉じる
	}
	else if (err == ENOENT) {     //ファイルない場合は閉じる

		fclose(save); // ファイルを閉じる
	}

	box_model.SetBoxInfo_SRTL(srtl);
}

