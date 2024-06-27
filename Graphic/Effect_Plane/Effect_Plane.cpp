#include "Effect_Plane.h"

Effect_Plane::Effect_Plane(const wchar_t* filename , Effect_Info effect_info) {     //�R���X�g���N�^

	// �g�p����V�F�[�_�[�𐶐�(billboard�p)
	shader.SetShader(
		"shader/unlitTextureVS.hlsl",					// ���_�V�F�[�_
		"shader/unlitTexturePS.hlsl");				    // �s�N�Z���V�F�[�_

	
	// �r���{�[�h�p�̃��b�V������
	plane_mesh.Init(
		effect_info,
		effect_info.color,
		Vector3(0.0f,0.0f,-1.0f),
		false
	);

	// �r���{�[�h�p�}�e���A��
	MATERIAL mtrl{};
	mtrl.Ambient = Color(0, 0, 0, 0);
	mtrl.Diffuse = effect_info.color;
	mtrl.Specular = Color(0, 0, 0, 0);
	mtrl.Shininess = 0;
	mtrl.Emission = Color(0, 0, 0, 0);
	mtrl.TextureEnable = true;

	material.Init(mtrl);

	mesh_renderer.Init(plane_mesh);

	// �r���{�[�h�p�e�N�X�`���ǂݍ���
	DirectX::CreateWICTextureFromFile(
		Renderer::GetDevice(),
		filename,
		nullptr,
		&g_Texture);

	assert(g_Texture);
}
Effect_Plane::~Effect_Plane() {    //�f�X�g���N�^

	material.Uninit();
}

void Effect_Plane::Update() {      //�X�V

	plane_mesh.AnimUpdate();
	anim_loop_cnt = plane_mesh.GetAnimLoop();   //�A�j�����[�v�擾
	
	mesh_renderer.Init(plane_mesh);
}
void Effect_Plane::Draw() {        //�`��

	// �r���{�[�h�`��
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture);
	shader.SetGPU();							// �r���{�[�h�p�V�F�[�_�[���Z�b�g
	material.SetGPU();						    // �r���{�[�h�p�}�e���A�����Z�b�g
	billboard.SetBeforeDraw(&mesh_renderer);
	billboard.Draw(m_view_matrix, m_parent_pos);

}

bool Effect_Plane::LimitedTimesDraw(int loop_times) {  //����ꂽ���[�v�̊Ԃ����`��

	if (anim_loop_cnt <= loop_times) {    //�A�j�����[�v���w�肵���񐔈ȉ��̎��`��

		// �r���{�[�h�`��
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture);
		shader.SetGPU();							// �r���{�[�h�p�V�F�[�_�[���Z�b�g
		material.SetGPU();						    // �r���{�[�h�p�}�e���A�����Z�b�g
		billboard.SetBeforeDraw(&mesh_renderer);
		billboard.Draw(m_view_matrix, m_parent_pos);

	}

	if (anim_loop_cnt == loop_times) return true;

	return false;
}

void Effect_Plane::StartDraw() {                       //�`����J�n����

	plane_mesh.ResetAnim();  //�A�j������������
	
}

