#include "Effect_PlaneMesh.h"


void CPlaneMesh_Effect::Init(
	Effect_Info effect_info,
	DirectX::SimpleMath::Color color,
	DirectX::SimpleMath::Vector3 normal,
	bool xzflag) {

	

	// �T�C�Y�Z�b�g�i���ƍ����j�iXY���ʁj
	m_width = static_cast<float>(effect_info.width);
	m_height = static_cast<float>(effect_info.height);

	// �@���x�N�g��
	m_normal = normal;

	// ���_�J���[
	m_color = color;

	anim_div_x = effect_info.anim_div_x;  //�A�j���摜�̕�������
	anim_div_y = effect_info.anim_div_y;  //�A�j���摜�̕�������

	anim_kankaku = effect_info.anim_kankaku;  //�A�j���̊Ԋu

	if (xzflag == true) {
		// ���_�f�[�^����
		CreateVertexXZ();
	}
	else {
		// ���_�f�[�^����
		CreateVertex();
	}
	// �C���f�b�N�X�f�[�^����
	CreateIndex();

}
void CPlaneMesh_Effect::CreateVertex() {    //���_�f�[�^�쐬

	// ���_�f�[�^�N���A
	m_vertices.clear();

	int m_divY = 1;
	int m_divX = 1;

	for (unsigned int y = 0; y <= m_divY; y++) {
		VERTEX_3D	vtx{};

		for (unsigned int x = 0; x <= m_divX; x++) {

			// ���_���W�Z�b�g
			vtx.Position.x = -m_width / 2.0f + x * m_width / m_divX;
			vtx.Position.y = -m_height / 2.0f + y * m_height / m_divY;
			vtx.Position.z = 0.0f;

			// �@���x�N�g���Z�b�g
			vtx.Normal = m_normal;				    // �@�����Z�b�g
			vtx.Diffuse = m_color;					// �J���[�l�Z�b�g

			// �J��Ԃ��ɑΉ��i�e�N�X�`���́j
			float texu = 1.0f * m_divX  / anim_div_x;
			float texv = 1.0f * m_divY  / anim_div_y;
			vtx.TexCoord.x = (texu * x / m_divX);
			vtx.TexCoord.y = texv - (texv * y / m_divY);

			m_vertices.emplace_back(vtx);		// ���_�f�[�^�Z�b�g
		}
	}
}
void CPlaneMesh_Effect::CreateVertexXZ() {  //���_�f�[�^XZ�쐬

	// ���_�f�[�^�N���A
	m_vertices.clear();

	int m_divY = 1;
	int m_divX = 1;

	for (unsigned int y = 0; y <= m_divY; y++) {
		VERTEX_3D	vtx{};

		for (unsigned int x = 0; x <= m_divX; x++) {

			// ���_���W�Z�b�g
			vtx.Position.x = -m_width / 2.0f + x * m_width / m_divX;
			vtx.Position.y = 0.0f;
			vtx.Position.z = -m_height / 2.0f + y * m_height / m_divY;

			// �@���x�N�g���Z�b�g
			vtx.Normal = m_normal;				// �@�����Z�b�g
			vtx.Diffuse = m_color;			    // �J���[�l�Z�b�g

			// �J��Ԃ��ɑΉ��i�e�N�X�`���́j
			float texu = 1.0f * m_divX / anim_div_x;
			float texv = 1.0f * m_divY / anim_div_y;

			vtx.TexCoord.x = (texu * x / m_divX);
			vtx.TexCoord.y = (texv * y / m_divY);


			m_vertices.emplace_back(vtx);		// ���_�f�[�^�Z�b�g
		}
	}
}
void CPlaneMesh_Effect::CreateIndex() {     //�C���f�b�N�X�쐬

	int m_divY = 1;
	int m_divX = 1;

	// �C���f�b�N�X�f�[�^�N���A
	m_indices.clear();

	// �C���f�b�N�X����
	for (unsigned int y = 0; y < m_divY; y++) {
		for (unsigned int x = 0; x < m_divX; x++) {
			int count = (m_divX + 1) * y + x;		// �������W�̃C���f�b�N�X

			// ������
			{
				FACE face{};

				face.idx[0] = count;						// ����
				face.idx[1] = count + 1 + (m_divX + 1);		// �E��
				face.idx[2] = count + 1;					// �E

				m_indices.emplace_back(face.idx[0]);
				m_indices.emplace_back(face.idx[1]);
				m_indices.emplace_back(face.idx[2]);

			}

			// �㔼��
			{
				FACE face{};
				face.idx[0] = count;						// ����
				face.idx[1] = count + (m_divX + 1);			// ��
				face.idx[2] = count + (m_divX + 1) + 1;		// �E��

				m_indices.emplace_back(face.idx[0]);
				m_indices.emplace_back(face.idx[1]);
				m_indices.emplace_back(face.idx[2]);
			}
		}
	}
}
void CPlaneMesh_Effect::AnimUpdate() {      //�e�b�N�X�X�V

	// ���_�f�[�^�N���A
	m_vertices.clear();

	//�v���[���̕�����
	int m_divY = 1;
	int m_divX = 1;

	//�A�j���J�ڌv�Z
	float diffx = 1.0f / anim_div_x;
	float diffy = 1.0f / anim_div_y;


	// ���_�f�[�^�N���A
	m_vertices.clear();

	for (unsigned int y = 0; y <= m_divY; y++) {
		VERTEX_3D	vtx{};

		for (unsigned int x = 0; x <= m_divX; x++) {

			// ���_���W�Z�b�g
			vtx.Position.x = -m_width / 2.0f + x * m_width / m_divX;
			vtx.Position.y = -m_height / 2.0f + y * m_height / m_divY;
			vtx.Position.z = 0.0f;

			// �@���x�N�g���Z�b�g
			vtx.Normal = m_normal;				// �@�����Z�b�g
			vtx.Diffuse = m_color;					// �J���[�l�Z�b�g

			// �J��Ԃ��ɑΉ��i�e�N�X�`���́j
			float texu = 1.0f * m_divX / anim_div_x;
			float texv = 1.0f * m_divY / anim_div_y;

			vtx.TexCoord.x = (texu * x / m_divX) + animcnt_x * diffx;
			vtx.TexCoord.y =  texv - (texv * y / m_divY) + animcnt_y * diffy;

			m_vertices.emplace_back(vtx);		// ���_�f�[�^�Z�b�g
		}
	}

	// �A�j���[�V�����؂�ւ����Ԓ���
	loopcnt++;

	if (loopcnt % anim_kankaku == 0) {

		animcnt_x++;
		animcnt_x = animcnt_x % anim_div_x;

		if (animcnt_x % anim_div_x == 0 && !only_one_line) {   //�����I�������

			animcnt_y++;  //���Ɉړ�
			animcnt_y = animcnt_y % anim_div_y; //�c�̃��C���I�������O���߂ɖ߂�

			if (animcnt_y % anim_div_y == 0) {

				anim_loop_cnt++;
			}
		}
	}
}
void CPlaneMesh_Effect::AnimUpdate_XZ() {   //XZ���p

	// ���_�f�[�^�N���A
	m_vertices.clear();

	int m_divY = 1;
	int m_divX = 1;

	//�A�j���J�ڌv�Z
	float diffx = 1.0f / anim_div_x;
	float diffy = 1.0f / anim_div_y;


	for (unsigned int y = 0; y <= m_divY; y++) {
		VERTEX_3D	vtx{};

		for (unsigned int x = 0; x <= m_divX; x++) {

			// ���_���W�Z�b�g
			vtx.Position.x = -m_width / 2.0f + x * m_width / m_divX;
			vtx.Position.y = 0.0f;
			vtx.Position.z = -m_height / 2.0f + y * m_height / m_divY;

			// �@���x�N�g���Z�b�g
			vtx.Normal = m_normal;				// �@�����Z�b�g
			vtx.Diffuse = m_color;			    // �J���[�l�Z�b�g

			// �J��Ԃ��ɑΉ��i�e�N�X�`���́j
			float texu = 1.0f * m_divX  / anim_div_x;
			float texv = 1.0f * m_divY  / anim_div_y;

			vtx.TexCoord.x = (texu * x / m_divX) / animcnt_x * diffx;
			vtx.TexCoord.y = (texv * y / m_divY) / animcnt_y * diffy;


			m_vertices.emplace_back(vtx);		// ���_�f�[�^�Z�b�g
		}
	}

	// �A�j���[�V�����؂�ւ����Ԓ���
	loopcnt++;

	if (loopcnt % anim_kankaku == 0) {

		animcnt_x++;
		animcnt_x = animcnt_x % anim_div_x;

		if (animcnt_x % anim_div_x == 0 && !only_one_line) {   //�����I�������

			animcnt_y++;  //���Ɉړ�
			animcnt_y = animcnt_y % anim_div_y; //�c�̃��C���I�������O���߂ɖ߂�

			if (animcnt_y % anim_div_y== 0) {

				anim_loop_cnt++;
			}
		}
	}
}


void CPlaneMesh_Effect::ResetAnim() {       //�A�j�����[�v�����Z�b�g

	loopcnt = 0;

	animcnt_x = 0;
	animcnt_y = 0;

	anim_loop_cnt = 0;
}

int  CPlaneMesh_Effect::GetAnimLoop() {     //�A�j���̃��[�v�����擾

	return anim_loop_cnt;
}