#pragma once
#include <iostream>
#include "CBoundingBox.h"
#include "CBoxMesh.h"
#include "CMaterial.h"
#include "CMeshRenderer.h"
#include "dx11mathutil.h"
#include "Box_R.h"
#include "BoxCol_Info.h"

//2023-12-1(��)�@DirectX��DirecctX::SimpleMath�̃l�[���X�y�[�X�����݂���ƁA
//               �R���p�C������������̂ŁADirectX::�𔻕ʂł���悤�ɐ擪�ɂ���


using namespace DirectX::SimpleMath;


class Box_Col {                 //2023-11-30(��)�@ ����@�����蔻��{�b�N�X�`��Z�b�g

private:


	int ctrl = 0;                      //�g�k�ړ���]����ς���p

	Box_R  box_model;
	CBoundingBox obb;                  //�o�E���f�B���O�{�b�N�X
	
	bool flag_hitcheck_ON;             //�����蔻��̐؂�ւ�


public:

	char col_name[60]; //�����蔻��̖��O

	Box_Col();     //�R���X�g���N�^
	~Box_Col();    //�f�X�g���N�^


	//��{�֐�
	void Init();
	bool Draw(BoundingBoxOBB obbB);
	void Exit();
	
	void Edit_Update(int sel_srt, int sel_xyz);
	bool CheckDraw(BoundingBoxOBB obbB, Color before_color, Color after_color);    //Editer�p�`��


	//�����蔻��؂�ւ��t���O
	void HitCheck_ON();
	void HitCheck_OFF();


	//�Z�b�^�[
	void SetMat(Matrix parent_mat, Matrix child_mat);
	void SetBoxLength(DirectX::XMFLOAT3 length);
	void SetBoxColEdit_Value(Edit_Value edit_value);
	
	//�Q�b�^�[
	BoundingBoxOBB GetBoundingBox();


	//�Z�[�u�֘A
	void Save(const char* filename);        //�Z�[�u
	void SetSave(const char* filename);     //�Z�[�u�����o��
	
};

