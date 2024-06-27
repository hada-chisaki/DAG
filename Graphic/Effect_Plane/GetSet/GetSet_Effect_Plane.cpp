#include "Effect_Plane.h"


void Effect_Plane::SetViewMatrix(Matrix v_matrix) {    //�Z�b�g�r���[�}�g���N�X

	m_view_matrix = v_matrix;
}

void Effect_Plane::SetParentPos(DirectX::XMFLOAT3 parent_pos) {

	m_parent_pos = parent_pos;
}

void Effect_Plane::SetEffectPos(DirectX::XMFLOAT3 pos) {    //�ʒu

	billboard.SetPos(pos);
}
void Effect_Plane::SetEffectScale(DirectX::XMFLOAT3 scl) {  //�X�P�[��

	billboard.SetScale(scl);
}
