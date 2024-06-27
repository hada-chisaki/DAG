#pragma once
#include <iostream>

#include "CShader.h"
#include "CMaterial.h"
#include "CPlaneMesh.h"
#include "CPlane.h"
#include "CMeshRenderer.h"
#include "dx11mathutil.h"


using namespace DirectX::SimpleMath;


struct Plane_SRT {               //2024-1-13(�y)�@�ǉ��@Plane��SRT���


	// ���̏��(S,R,T)
	DirectX::XMFLOAT3	position = { 0.0f,0.0f,0.0f };		// �ʒu
	DirectX::XMFLOAT3	rotation = { 0.0f,0.0f,0.0f };		// �p��
	DirectX::XMFLOAT3	scale = { 1.0f,1.0f,1.0f };			// �g�k
	

};


struct Plane_Info {          //2024-1-13(�y)�@�ǉ��@Plane�������Z�b�g

	
	int div_x = 10;	                           //�������@��
    int div_y = 10;                             //�������@�c

	int width = 100;                           //���ʂ̕�
	int height = 100;                          //���ʂ̍���

	Color color = { 1.0f,1.0f,1.0f };          //���_�J���[
	Vector3 normal = { 0.0f,0.0f,-1.0f};       //���ʂ̌���
	bool xz_flag = true;                       //xz�̕��ʉ��ǂ���

};


class Plane_R {    //2024-1-13(�y)�@�ǉ��@�n�ʕ`��N���X


private:

	//�`��ɕK�v�ȏ��

	 CShader		shader;                   //�V�F�[�_�[
	 CPlaneMesh     planemesh;                //  �����b�V���i�W�I���g���f�[�^�j
	 CMeshRenderer  meshrenderer;             // �����b�V���i�����_�����O�f�[�^�j
	 CMaterial	    material;                 // ���p�}�e���A��

	// SRV�i�e�N�X�`���j
	 Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;
	 std::vector<CPlane> planes;

	 //Plane���
	 Plane_Info plane_info;
	 Plane_SRT plane_srt;

public:
 

	//��{�֐��@
	void Init(const char* texture_filename);
	void Update();
	void Draw();
	void Exit();


	//�n�ʂ̓����蔻��p
	void   makepalenequatation();
	float  GetFieldHeightBySqno(Vector3 pos);
	float  GetFieldHeight(Vector3 pos);

	//�Z�b�^�[
	void SetPlaneInfo(Plane_Info);
	void SetPlaneSRT(Plane_SRT);

	//�Q�b�^�[
	Plane_Info GetPlaneInfo();
};