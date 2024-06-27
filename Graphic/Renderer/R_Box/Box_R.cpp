#include "Box_R.h"
#include "CDirectInput.h"

void Box_R::Init() {           //2024-2-12(月)　編集　初期化


	box_mesh.Init(
		boxinfo_srtl.length.x,
		boxinfo_srtl.length.y,
		boxinfo_srtl.length.z,
		Color(1.0f, 1.0f, 1.0f, 0.8f)
	);


	shader.SetShader("shader/Laser_VS.hlsl", 
		             "shader/Laser_PS.hlsl");


	MATERIAL mtrl;
	material.Init(mtrl);

	mesh_renderer.Init(box_mesh);

}
void Box_R::EditUpdate(int sel_srt , int sel_xyz) {     //2024-2-12(月)　編集　編集用アップデート


	switch (sel_srt) {

	case 0:   //位置変更

		if((CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_2))) EditPos(sel_xyz);
		
		break;

	case 1:  //回転

		if ((CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_2))) EditRot(sel_xyz);

		break;

	case 2: //拡縮

		if ((CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_2))) EditScl(sel_xyz);

		break;

	}

}
void Box_R::Draw(bool hit , Color before_color, Color after_color) {


	if (hit) {

		MATERIAL mtrl;
		mtrl.Ambient = Color(0, 0, 0, 0);
		mtrl.Diffuse = after_color;
		mtrl.Emission = Color(1, 1, 1, 1);
		mtrl.Specular = Color(0, 0, 0, 0);
		mtrl.Shininess = 0;
		mtrl.TextureEnable = FALSE;
		material.SetMaterial(mtrl);
	}

	else {

		MATERIAL mtrl;
		mtrl.Ambient = Color(0, 0, 0, 0);
		mtrl.Diffuse = before_color;
		mtrl.Emission = Color(0, 0, 0, 0);
		mtrl.Specular = Color(0, 0, 0, 0);
		mtrl.Shininess = 0;
		mtrl.TextureEnable = FALSE;
		material.SetMaterial(mtrl);
	}

	material.SetGPU();
	shader.SetGPU();

	Matrix mtx = CreateMatrix();
	Renderer::SetWorldMatrix(&mtx);

	mesh_renderer.Draw();
}

void Box_R::Exit() {           //2024-2-12(月)　編集　終了

	material.Uninit();
}



void Box_R::EditPos(int sel_xyz) {

	switch (sel_xyz) {

	case 0:

		boxinfo_srtl.position.x += edit_value.position_value;

		break;

	case 1:

		boxinfo_srtl.position.y += edit_value.position_value;

		break;

	

	case 2:

		boxinfo_srtl.position.z += edit_value.position_value;

		break;
	}

}
void Box_R::EditRot(int sel_xyz) {

	switch (sel_xyz) {

	case 0:

		boxinfo_srtl.rotation.x += edit_value.rotation_value;

		break;

	case 1:

		boxinfo_srtl.rotation.y += edit_value.rotation_value;

		break;

	case 2:

		boxinfo_srtl.rotation.z += edit_value.rotation_value;

		break;

	}
}
void Box_R::EditScl(int sel_xyz) {

	switch (sel_xyz) {

	case 0:

		boxinfo_srtl.scale.x += edit_value.scale_value;

		break;

	case 1:

		boxinfo_srtl.scale.y += edit_value.scale_value;

		break;

	case 2:

		boxinfo_srtl.scale.z += edit_value.scale_value;

		break;

	}
}

Matrix Box_R::CreateMatrix() {

	Matrix mtx;

	DX11MakeWorldMatrixRadian(
		mtx,
		boxinfo_srtl.scale,
        boxinfo_srtl.rotation,
        boxinfo_srtl.position
		);

	mtx = mtx * child_mtx * parent_mtx;

	return mtx;
}



//ゲッター
Matrix Box_R::GetMatrix() {

	Matrix mtx = CreateMatrix();

	return mtx;
}
std::vector<VERTEX_3D> Box_R::GetVertices() {

	return box_mesh.GetVertices();
}
DirectX::XMFLOAT3 Box_R::GetScale() {

	return boxinfo_srtl.scale;
}
BoxInfo_SRTL Box_R::GetBox_SRTL() {

	return boxinfo_srtl;
}



//セッター
void Box_R::SetMat(Matrix child_mat, Matrix parent_mat) {           //2024-2-12 編集　マトリクスセット

	child_mtx = child_mat;
	parent_mtx = parent_mat;
}
void Box_R::SetBoxInfo_SRTL(BoxInfo_SRTL boxinfo) {

	boxinfo_srtl = boxinfo;
}
void Box_R::SetLength(DirectX::XMFLOAT3 length) {

	boxinfo_srtl.length = length;
}
void Box_R::SetEditSRT_Value(Edit_Value value) {               //2024-2-12 編集　Edit用数値セット

	edit_value = value;
}
