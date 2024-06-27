#include "Box_Col.h"
#include "Player.h"

//2023-11-30 �����錾
#include "CMaterial.h"
#include "Collision.h"
#include "CDirectInput.h"
#include <DirectXMath.h>
#include "Logger.h"


#define _CRT_SECURE_NO_WARNINGS 


using namespace DirectX::SimpleMath;

Box_Col::Box_Col() {     //�R���X�g���N�^

	box_model.Init();

	//OBB�쐬
	obb.Caliculate(box_model.GetVertices());   //�{�b�N�X�̒��_���v�Z

}
Box_Col::~Box_Col() {    //�f�X�g���N�^

	box_model.Exit();
}

void Box_Col::Init(
) {

	box_model.Init();

	//OBB�쐬
	obb.Caliculate(box_model.GetVertices());   //�{�b�N�X�̒��_���v�Z

}
void Box_Col::Edit_Update(int sel_srt,int sel_xyz) {

	box_model.EditUpdate(sel_srt, sel_xyz);
}



void Box_Col::Exit() {

	box_model.Exit();
}



//����F�t��
bool  Box_Col::CheckDraw(          //Editer�p
	BoundingBoxOBB obbB,
	DirectX::SimpleMath::Color before_color,
	DirectX::SimpleMath::Color after_color
) {

	// OBB��񐶐�
	BoundingBoxOBB obbA;
	Matrix mtx = box_model.GetMatrix();

	DirectX::XMFLOAT3 scale = box_model.GetScale();
	obbA = obb.MakeOBB(mtx,scale);

	
	bool sts = HitCheckOBB(obbA, obbB);
	box_model.Draw(sts, before_color, after_color);
	
	//OBB�`��
	mtx = obb.MakeWorldMtx(scale, mtx);
	Renderer::SetWorldMatrix(&mtx);           //���[���h�}�g���N�X���Z�b�g


	return sts;
}



//�ʏ�g�p
bool Box_Col::Draw(  BoundingBoxOBB obbB        
) {

	bool sts = false;

	if (flag_hitcheck_ON) {

		// OBB��񐶐�
		BoundingBoxOBB obbA;
		Matrix mtx = box_model.GetMatrix();

		DirectX::XMFLOAT3 scale = box_model.GetScale();
		obbA = obb.MakeOBB(mtx, scale);

	    sts = HitCheckOBB(obbA, obbB);

		//OBB�`��
		mtx = obb.MakeWorldMtx(scale, mtx);
		Renderer::SetWorldMatrix(&mtx);           //���[���h�}�g���N�X���Z�b�g

	}

	return sts;
}


 
//�t���O�؂�ւ�
void Box_Col::HitCheck_ON() {   //2023-12-18(��)�@�ҏW�@�t���O��true�ɂ���

	flag_hitcheck_ON = true;
}
void Box_Col::HitCheck_OFF() {  //2023-12-18(��)�@�ҏW�@�t���O��false�ɂ���

	flag_hitcheck_ON = false;
}




//�Z�b�^�[
void Box_Col::SetMat(Matrix parent_mat, Matrix child_mat) {

	box_model.SetMat(child_mat,parent_mat);
}
void Box_Col::SetBoxLength(DirectX::XMFLOAT3 length) {

	box_model.SetLength(length);
}
void Box_Col::SetBoxColEdit_Value(Edit_Value edit_value) {        //�G�f�B�^�[�p�@�ʂ��Z�b�g

	box_model.SetEditSRT_Value(edit_value);
}



//�Q�b�^�[
BoundingBoxOBB Box_Col::GetBoundingBox() {


	// OBB��񐶐�
	BoundingBoxOBB box_obb;
	
	Matrix mtx = box_model.GetMatrix();

	DirectX::XMFLOAT3 scale = box_model.GetScale();
	box_obb = obb.MakeOBB(mtx, scale);
	

	return box_obb;
}




void Box_Col::Save(const char* filename) {       //2023-12-17(��)�@�ǉ��@�Z�[�u


	BoxInfo_SRTL srtl = box_model.GetBox_SRTL();

	FILE* save;
	fopen_s(&save, filename, "wb");

	if (save == NULL) {

		MessageBox(NULL, "�t�@�C�����J���܂���", filename, MB_ABORTRETRYIGNORE);
	}

	fwrite(&srtl, sizeof(srtl), 1, save);      //�f�[�^����������
	fclose(save);

}


void Box_Col::SetSave(const char* filename) {     // //2023-12-17(��)�@�ǉ��@�Z�[�u�����o��


	FILE* save;
	errno_t err = fopen_s(&save, filename, "rb");
	BoxInfo_SRTL srtl;

	if (err == 0 && save != nullptr) {
		// �t�@�C��������ɊJ���ꂽ�ꍇ�̏���

		fread(&srtl, sizeof(srtl), 1, save);   //�f�[�^��ǂݍ���

		fclose(save); // �t�@�C�������
	}
	else if (err == ENOENT) {     //�t�@�C���Ȃ��ꍇ�͕���

		fclose(save); // �t�@�C�������
	}

	box_model.SetBoxInfo_SRTL(srtl);
}

