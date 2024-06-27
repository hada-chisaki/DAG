#pragma once
#include "CBillboard.h"
#include "Effect_PlaneMesh.h"
#include "CMeshRenderer.h"
#include "CShader.h"
#include "CMaterial.h"
#include "dx11mathutil.h"
#include "Effect_Info.h"
#include "Timer.h"
#include "Box_Col.h"

using namespace DirectX::SimpleMath;


class Effect_Plane {         //�G�t�F�N�g�p�@�r���{�[�h�v���[��

private:

	int anim_loop_cnt{};    //�A�j���̃��[�v�J�E���g

	//�r���{�[�h
    CBillboard billboard{};            //�r���{�[�h

	//�`��p
	CMeshRenderer mesh_renderer{};         //���b�V�������_���[
	CPlaneMesh_Effect  plane_mesh{};       //�v���[�����b�V��
	CShader     shader{};                  //�V�F�[�_�[
	CMaterial   material{};                //�}�e���A��
    ID3D11ShaderResourceView* g_Texture{}; //�e�N�X�`��
										   
	Matrix m_view_matrix{};                //�r���[�ϊ��}�g���N�X
	DirectX::XMFLOAT3 m_parent_pos{};      //�e�̈ʒu���i�[ 

public:

	Effect_Plane(const wchar_t* filename ,Effect_Info effect_info);    //�R���X�g���N�^
	~Effect_Plane();   //�G�t�F�N�g

	void Update();     //�X�V
	void Draw();       //�ʏ�`��
	
	void StartDraw();                       //�`����J�n����
	bool LimitedTimesDraw(int loop_times);  //����ꂽ���[�v�̊Ԃ����`��

	//�Z�b�^�[
	void SetViewMatrix(Matrix view_matrix);
	void SetParentPos(DirectX::XMFLOAT3 parent_pos);
	void SetEffectPos(DirectX::XMFLOAT3 position);
	void SetEffectScale(DirectX::XMFLOAT3 scale);
};