#pragma once


#include	"CDirectInput.h"
#include	"dx11mathutil.h"
#include    "CShader.h"
#include	"CStaticMesh.h"
#include	"CStaticMeshRenderer.h"


struct Model_SRT{         //2023-12-14(��)�@�ǉ��@�ʒu���


	// ���f���̏��(S,R,T)
	DirectX::XMFLOAT3	position = { 0.0f,0.0f,0.0f };		// �ʒu
	DirectX::XMFLOAT3	rotation = { 0.0f,0.0f,0.0f };		// �p��
	DirectX::XMFLOAT3	scale = { 1.0f,1.0f,1.0f };			// �g�k

};

struct Model_Info {

	DirectX::XMFLOAT3  max; 
	DirectX::XMFLOAT3  min;
	DirectX::XMFLOAT3  center;
    DirectX::XMFLOAT3  length;

};

struct CameraForward {

	DirectX::SimpleMath::Vector3 c_front;      //y��
    DirectX::SimpleMath::Vector3 c_right;      //x��

};

class Model_Render {       //2023-12-14(��)�@�ҏW�@���f�������_�[�N���X

public:


	void Init(std::string modelname);
	void Edit_Update();
	void Parent_Draw();          //�e���f���̏ꍇ
	void Child_Draw(DirectX::SimpleMath::Matrix parent_mat);      //�q���f���̏ꍇ
	void GrandChild_Draw(DirectX::SimpleMath::Matrix parent_mat, DirectX::SimpleMath::Matrix child_mat);    //�����f���̏ꍇ
	void Exit();
	
	void Model_VerCalc();     //���_���v�Z

	//�Z�b�^�[
	void SetModelPos(DirectX::XMFLOAT3 pos);
	void SetModelRot(DirectX::XMFLOAT3 rot);
	void SetModelScl(DirectX::XMFLOAT3 scl);
	void SetModel_SRT(Model_SRT srt);
	void SetCameraForward(DirectX::SimpleMath::Vector3 c_front, DirectX::SimpleMath::Vector3 c_right);

	//�}�g���N�X�쐬
	DirectX::SimpleMath::Matrix Create_Parent_Mat();     //�e���f���̏ꍇ
	DirectX::SimpleMath::Matrix Create_Child_Mat(DirectX::SimpleMath::Matrix parent_mat);      //�q���f���̏ꍇ
	DirectX::SimpleMath::Matrix Create_GrandChild_Mat(DirectX::SimpleMath::Matrix parent_mat, DirectX::SimpleMath::Matrix child_mat);
	

	//�Q�b�^�[
	DirectX::SimpleMath::Matrix Get_Parent_Mat();                 //�e�̃}�g���N�X���Q�b�g
	DirectX::SimpleMath::Matrix Get_Child_Mat(DirectX::SimpleMath::Matrix parent_mat);
	DirectX::XMFLOAT3 GetModelPos();
    DirectX::XMFLOAT3 GetModelRot();
	DirectX::XMFLOAT3 GetModelScl();
	Model_SRT GetModel_SRT();
	DirectX::XMFLOAT3 GetModel_Min();      //���f���̍ŏ����_�l��Ԃ�
    DirectX::XMFLOAT3 GetModel_Man();      //���f���̍ő咸�_�l��Ԃ�
	DirectX::XMFLOAT3 GetModel_Center();   //���f���̒��S�_�Ԃ�
    DirectX::XMFLOAT3 GetModel_Length();    //���f���̒�����Ԃ�


	//�Z�[�u
	void Save(const char* filename);         //�t�@�C���ɏ�������
	void SetSave(const char* filename);      //�Z�[�u�����Z�b�g


private:


	CShader     shader;
	CameraForward  camera_forward;
	Model_Info  model_info;
	Model_SRT   model_srt;      //�ʒu���i�[ 

	int edit_sel{};   //�ҏW�p

	//���b�V���ƃ����_���[
	CStaticMesh staticmesh;   	              // �X�^�e�B�b�N���b�V���i�W�I���g���f�[�^�j
	CStaticMeshRenderer staticmeshrenderer;   // ���b�V�������_���[


};