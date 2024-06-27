#pragma once
#include  "CBoxMesh.h"
#include  "CMaterial.h"
#include  "CMeshRenderer.h"
#include  "CShader.h"
#include  "dx11mathutil.h"
#include  "BoxCol_Info.h"

using namespace DirectX::SimpleMath;


struct BoxInfo_SRTL {

	DirectX::XMFLOAT3 position = { 0.0f,0.0f,0.0f };
	DirectX::XMFLOAT3 rotation = { 0.0f,0.0f,0.0f };
	DirectX::XMFLOAT3 scale = { 1.0f,1.0f,1.0f };

	DirectX::XMFLOAT3 length = { 1.0f,1.0f,1.0f };   //�ӂ̒���

};

class Box_R {           //2024-2-12(��) �{�b�N�X�����_�[�N���X

private:

	//���ߗp�@
	Edit_Value  edit_value;

	CBoxMesh     box_mesh;          
	BoxInfo_SRTL boxinfo_srtl;       //���̏��

	CMaterial    material; 
	CShader      shader;

	CMeshRenderer   mesh_renderer;

	//�e�q�֌W�쐬�}�g���N�X
	Matrix parent_mtx;     
	Matrix child_mtx;
    Matrix CreateMatrix();    

	void EditPos(int sel_xyz);
	void EditRot(int sel_xyz);
	void EditScl(int sel_xyz);

public:


	void Init();
	void EditUpdate(int sel_srt,int sel_xyz);
	void Draw(bool hit , Color before_color, Color after_color);
	void Exit();

	//===================
    //�Q�b�^�[
    //===================
	Matrix GetMatrix();
	BoxInfo_SRTL GetBox_SRTL();
	std::vector<VERTEX_3D> GetVertices(); 
	DirectX::XMFLOAT3 GetScale();
	
	//===================
	//�O�����Z�b�^�[
	//===================
	void SetMat(Matrix child_mtx, Matrix parent_mtx);
	void SetBoxInfo_SRTL(BoxInfo_SRTL boxinfo_srtl);
	void SetLength(DirectX::XMFLOAT3 length);
	void SetEditSRT_Value(Edit_Value edit_value);

};