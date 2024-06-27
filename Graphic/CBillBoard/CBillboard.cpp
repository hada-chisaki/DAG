#include	"CBillboard.h"

using namespace DirectX::SimpleMath;

// �r���{�[�h�`��p�̎p����\���s����v�Z
Matrix CBillboard::CalcBillboardMatrix(Matrix viewmtx) {

	Matrix billboardmtx{};

	// �r���[�ϊ��s���]�u�i���K���s�s��͓]�u���j
	billboardmtx = viewmtx.Transpose();

	// �s�v�������N���A
	billboardmtx._41 = billboardmtx._42 = billboardmtx._43 = 0.0f;
	billboardmtx._14 = billboardmtx._24 = billboardmtx._34 = 0.0f;
	billboardmtx._44 = 1.0f;

	return billboardmtx;
}

// �`��
void CBillboard::Draw(
	DirectX::SimpleMath::Matrix viewmtx,		// �r���[�ϊ��s��
	DirectX::SimpleMath::Vector3 pos)			// �ʒu
{

	// �r���{�[�h�`��p�̍s����쐬����
	m_WorldMtx = CalcBillboardMatrix(viewmtx);

	// �ʒu���Z�b�g
	m_WorldMtx._41 = pos.x;
	m_WorldMtx._42 = pos.y;
	m_WorldMtx._43 = pos.z;

	Matrix mtx{};
	DirectX::XMFLOAT3 rot{};

	DX11MakeWorldMatrix(
		mtx,
		m_scale,
		rot,
		m_position
	);

	m_WorldMtx = mtx * m_WorldMtx;

	// �s����Z�b�g���ĕ`��
	Renderer::SetWorldMatrix(&m_WorldMtx);
	m_meshrenderer->Draw();
}

void   CBillboard::SetPos(DirectX::XMFLOAT3 pos) {    //�ʒu�Z�b�g

	m_position = pos;
}
void   CBillboard::SetScale(DirectX::XMFLOAT3 scale) {  //�X�P�[���Z�b�g

	m_scale = scale;
}