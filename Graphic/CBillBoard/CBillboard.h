#pragma once
#include    "dx11mathutil.h"
#include	<SimpleMath.h>
#include	"CPlaneMesh.h"
#include	"CMeshRenderer.h"

// �r���{�[�h�N���X
class CBillboard {

	DirectX::XMFLOAT3 m_position{0.0f,0.0f ,0.0f};
	DirectX::XMFLOAT3 m_scale = {1.0f,1.0f,1.0f};

	CMeshRenderer* m_meshrenderer{};
	// ���[���h�ϊ��s��
	DirectX::SimpleMath::Matrix m_WorldMtx{};
	//�@�r���[�ϊ��s�񂩂烏�[���h�ϊ��s��𐶐�
	DirectX::SimpleMath::Matrix CalcBillboardMatrix(DirectX::SimpleMath::Matrix viewmtx);

public:

	// �`��O����
	void SetBeforeDraw(
		CMeshRenderer* meshrenderer)
	{
		m_meshrenderer = meshrenderer;
	}

	// �`��
	void Draw(
		DirectX::SimpleMath::Matrix viewmtx,		// �r���[�ϊ��s��
		DirectX::SimpleMath::Vector3 parent_pos);			// �ʒu

	//�Z�b�g
	void  SetPos(DirectX::XMFLOAT3 pos);
	void  SetScale(DirectX::XMFLOAT3 scale);
};
