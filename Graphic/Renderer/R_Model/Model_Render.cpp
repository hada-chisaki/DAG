#include   "Model_Render.h"

using namespace DirectX::SimpleMath;


void Model_Render::Init(std::string modelname) {        //2023-12-13(��)�@�ҏW�@���f�����b�V���E�����_���[������


	shader.SetShader(
		"shader/unlitTextureVS.hlsl",				// ���_�V�F�[�_
		"shader/unlitTexturePS.hlsl");				// �s�N�Z���V�F�[�_


	// ���b�V�������i�W�I���g���f�[�^�j
	staticmesh.Init(modelname);

	// �`��ׂ̈̃f�[�^����
	staticmeshrenderer.Init(staticmesh);

	Model_VerCalc();
}


void Model_Render::Edit_Update() {


	if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_P)) {

		edit_sel = edit_sel + 1;

		if (edit_sel > 1) {

			edit_sel = 0;
		}
	}

	float position_vul = 0.2f;
	float rotation_vul = 0.1f;


	switch (edit_sel) {

	case 0:   //�ʒu�ύX

		     
		    
		    if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_L)) {
		    
		    	model_srt.position.x += position_vul;
		    }
		    if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_J)) {
		    
		    	model_srt.position.x -= position_vul;
		    }
		    if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_I)) {
		    
		    	model_srt.position.y += position_vul;
		    }
		    if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_K)) {
		    
		    	model_srt.position.y -= position_vul;
		    }
		    if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_V)) {
		    
		    	model_srt.position.z += position_vul;
		    }
		    if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_B)) {
		    
		    	model_srt.position.z -= position_vul;
		    }
		    

		    break;

		case 1: //�p�x

	

			if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_L)) {

				model_srt.rotation.x += rotation_vul;
			}
			if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_J)) {

				model_srt.rotation.x -= rotation_vul;
			}
			if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_I)) {

				model_srt.rotation.y += rotation_vul;
			}
			if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_K)) {

				model_srt.rotation.y -= rotation_vul;
			}
			if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_V)) {

				model_srt.rotation.z += rotation_vul;
			}
			if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_B)) {

				model_srt.rotation.z -= rotation_vul;
			}
			break;


		case 2: //�g�k

			float scale_vul = 0.1f;

			if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_L)) {

				model_srt.scale.x += scale_vul;
			}
			if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_J)) {

				model_srt.scale.x -= scale_vul;
			}
			if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_I)) {

				model_srt.scale.y += scale_vul;
			}
			if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_K)) {

				model_srt.scale.y -= scale_vul;
			}
			if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_V)) {

				model_srt.scale.z += scale_vul;
			}
			if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_B)) {

				model_srt.scale.z -= scale_vul;
			}
			break;
	}

}



void Model_Render::Parent_Draw() {

	shader.SetGPU();

	Matrix mtx = Create_Parent_Mat();    //�}�g���N�X���쐬

	// GPU�ɍs����Z�b�g����
	Renderer::SetWorldMatrix(&mtx);

	// ���f���`��
	staticmeshrenderer.Draw();

}


void Model_Render::Child_Draw(Matrix parent_mat) {      //2023-12-13(��)�@�ҏW�@�q�`��

	shader.SetGPU();

	Matrix mtx = Create_Child_Mat(parent_mat);    //�}�g���N�X���쐬

	// GPU�ɍs����Z�b�g����
	Renderer::SetWorldMatrix(&mtx);

	// ���f���`��
	staticmeshrenderer.Draw();

}


void Model_Render::GrandChild_Draw(Matrix parent_mat ,Matrix child_mat) {      //2023-12-13(��)�@�ҏW�@���`��

	shader.SetGPU();

	Matrix mtx = Create_GrandChild_Mat(parent_mat , child_mat);    //�}�g���N�X���쐬

	// GPU�ɍs����Z�b�g����
	Renderer::SetWorldMatrix(&mtx);

	// ���f���`��
	staticmeshrenderer.Draw();

}


void Model_Render::Exit() {


	staticmeshrenderer.Uninit();

}


void Model_Render::Model_VerCalc() {      //2023-12-24(��)�@�ҏW�@���_�̍ő�ƍŏ����v�Z


	std::vector<VERTEX_3D> vertices = staticmesh.GetVertices();    //���_�f�[�^���擾

	Vector3 max;
	Vector3 min;

	// �ő�l�ƍŏ��l�����߂�
	min = max = vertices[0].Position;
	for (auto& v : vertices) {

		if (min.x > v.Position.x) min.x = v.Position.x;
		if (min.y > v.Position.y) min.y = v.Position.y;
		if (min.z > v.Position.z) min.z = v.Position.z;

		if (max.x < v.Position.x) max.x = v.Position.x;
		if (max.y < v.Position.y) max.y = v.Position.y;
		if (max.z < v.Position.z) max.z = v.Position.z;
	}

	//�i�[
	model_info.min = min;
	model_info.max = max;

	// ���S�����߂�
	model_info.center = (max - min) * 0.5f;

	// ������ݒ�
	DirectX::SimpleMath::Vector3 len;
	len = model_info.max - model_info.min;

	model_info.length.x = fabs(len.x);
	model_info.length.y = fabs(len.y);
	model_info.length.z = fabs(len.z);

}






Matrix Model_Render::Create_Parent_Mat() {    //2023-12-13(��)�@�ҏW�@�e�}�g���N�X�쐬


	Matrix parent_mtx;

	DX11MakeWorldMatrixRadian(
		parent_mtx,
		model_srt.scale,
		model_srt.rotation,
		model_srt.position
	);

	return parent_mtx;
}



Matrix Model_Render::Create_Child_Mat(Matrix parent_mat) {    //2023-12-13(��)�@�ҏW�@�q�}�g���N�X�쐬


	Matrix child_mtx;
	Matrix parent_mtx = parent_mat;   //�e�}�g���N�X���i�[

	DX11MakeWorldMatrixRadian(
		child_mtx,
		model_srt.scale,
		model_srt.rotation,
		model_srt.position
	);


	child_mtx = child_mtx * parent_mtx;      //�e�q�֌W�ɂ���


	return child_mtx;
}


DirectX::SimpleMath::Matrix Model_Render::Create_GrandChild_Mat(DirectX::SimpleMath::Matrix parent_mat, DirectX::SimpleMath::Matrix child_mat) {     //2023-1-2(��)�@�ҏW�@���}�g���N�X�쐬



	Matrix mtx;
	Matrix grandchild_mtx;
	Matrix child_mtx = child_mat;
	Matrix parent_mtx = parent_mat;


	DX11MakeWorldMatrixRadian(
		grandchild_mtx,
		model_srt.scale,
		model_srt.rotation,
		model_srt.position
	);

    
	mtx = grandchild_mtx * child_mtx * parent_mtx;    //���A�q�A�e�֌W�����

	return mtx;
}



//�Z�b�^�[
void Model_Render::SetModelPos(DirectX::XMFLOAT3 pos) {    //2023-12-13(��)�@�ǉ��@�Z�b�g�|�W�V����

	model_srt.position = pos;
}
void Model_Render::SetModelRot(DirectX::XMFLOAT3 rot) {    //2023-12-13(��)�@�ǉ��@�Z�b�g���[�e�[�V����

	model_srt.rotation = rot;
}
void  Model_Render::SetModelScl(DirectX::XMFLOAT3 scl) {   //2023-12-13(��)�@�ǉ��@�Z�b�g�X�P�[��

	model_srt.scale = scl;
}
void Model_Render::SetModel_SRT(Model_SRT srt) {           //2023-12-13(��)�@�ǉ��@�Z�b�gSRT

	model_srt = srt;
}
void Model_Render::SetCameraForward(DirectX::SimpleMath::Vector3 c_front, DirectX::SimpleMath::Vector3 c_right) {     //2024-1-24(��)�@�ǉ��@�����Z�b�g

	camera_forward.c_front = c_front;
	camera_forward.c_right = c_right;
}


//�Q�b�^�[
Matrix Model_Render::Get_Parent_Mat() {              //2023-12-13(��)�@�ǉ��@�Q�b�g�e�}�g���N�X

	Matrix mtx = Create_Parent_Mat();   //�}�g���N�X�쐬

	return mtx;
}
Matrix Model_Render::Get_Child_Mat(Matrix parent_mat) {              //2023-1-2(��)�@�ǉ��@�Q�b�g�q�}�g���N�X

	Matrix mtx = Create_Child_Mat(parent_mat);

	return mtx;
}
DirectX::XMFLOAT3 Model_Render::GetModelPos(){       //2023-12-13(��)�@�ǉ��@�Q�b�g�|�W�V����

	return model_srt.position;
}
DirectX::XMFLOAT3 Model_Render::GetModelRot() {      //2023-12-13(��)�@�ǉ��@�Q�b�g���[�e�[�V����

	return model_srt.rotation;
}
DirectX::XMFLOAT3 Model_Render::GetModelScl() {      //2023-12-13(��)�@�ǉ��@�Q�b�g�X�P�[��

	return model_srt.scale;
}
Model_SRT Model_Render::GetModel_SRT() {             //2023-12-14(��)�@�ǉ��@�Q�b�gSRT

	return model_srt;
}
DirectX::XMFLOAT3 Model_Render::GetModel_Min() {     //2023-12-24(��)�@�ǉ�  ���f���̍ŏ����_�l��Ԃ�

	return model_info.min;
}
DirectX::XMFLOAT3 Model_Render::GetModel_Man() {     //2023-12-24(��)�@�ǉ�  ���f���̍ő咸�_�l��Ԃ�

	return model_info.max;
}
DirectX::XMFLOAT3 Model_Render::GetModel_Center() {   //2023-12-24(��)�@�ǉ��@���f���̒��S�_�Ԃ�

	return model_info.center;
}
DirectX::XMFLOAT3 Model_Render::GetModel_Length() {      //2023-12-24(��)�@�ǉ��@���f���̒�����Ԃ�

	return model_info.length;
}



//�Z�[�u�֘A

void Model_Render::Save(const char* filename) {        //2023-12-14(��)�@�ǉ��@�t�@�C���ɏ�������


	Model_SRT model = model_srt;

	FILE* save;
	fopen_s(&save,filename, "wb");

	if (save == NULL) {

		MessageBox(NULL, "�t�@�C�����J���܂���",filename, MB_ABORTRETRYIGNORE);
	}

	fwrite(&model, sizeof(model), 1, save);      //�f�[�^����������
	fclose(save);


}


void Model_Render::SetSave(const char* filename) {      //2023-12-14(��)�@�ǉ��@�Z�[�u�����Z�b�g


	FILE* save;
		errno_t err = fopen_s(&save, filename, "rb");
		Model_SRT srt;
	
		if (err == 0 && save != nullptr) {
			// �t�@�C��������ɊJ���ꂽ�ꍇ�̏���
	
			fread(&srt, sizeof(srt), 1, save);   //�f�[�^��ǂݍ���
	
			fclose(save); // �t�@�C�������
		}
		else if (err == ENOENT) {     //�t�@�C���Ȃ��ꍇ�͕���
	
			fclose(save); // �t�@�C�������
		}
		

		model_srt = srt;  //�Z�[�u�������̂��Z�b�g

}
