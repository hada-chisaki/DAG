#include "R_2D.h"

void R_2D::Init(const wchar_t  texturepass[38]) {        //2023-12-18(��)�@�ǉ��@2D������



	// �g�p����V�F�[�_�[�𐶐�
	shader.SetShader(
		"shader/unlitTextureVS.hlsl",				// ���_�V�F�[�_
		"shader/unlitTexturePS.hlsl");				// �s�N�Z���V�F�[�_
	


	// �e�N�X�`���ǂݍ���
	DirectX::CreateWICTextureFromFile(
		Renderer::GetDevice(),
		texturepass,
		nullptr,
		&Texture);


	assert(Texture);


	// ���_�o�b�t�@����
	VERTEX_3D vertex[4];

	vertex[0].Position = Vector3(0.0f, 0.0f, 1.0f);
	vertex[0].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = Vector4(1.0f, 1.0f, 1.0f, alpha);
	vertex[0].TexCoord = Vector2(0.0f, 0.0f);


	vertex[1].Position = Vector3(width, 0.0f, 1.0f);
	vertex[1].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = Vector4(1.0f, 1.0f, 1.0f, alpha);
	vertex[1].TexCoord = Vector2(1.0f, 0.0f);


	vertex[2].Position = Vector3(0.0f, height, 1.0f);
	vertex[2].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = Vector4(1.0f, 1.0f, 1.0f, alpha);
	vertex[2].TexCoord = Vector2(0.0f, 1.0f);


	vertex[3].Position = Vector3(width, height, 1.0f);
	vertex[3].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = Vector4(1.0f, 1.0f, 1.0f, alpha);
	vertex[3].TexCoord = Vector2(1.0f, 1.0f);


	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;


	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &VertexBuffer);

	// �}�e���A��������
	MATERIAL mtrl;
	mtrl.Ambient = Color(1, 1, 1, 1);
	mtrl.Diffuse = Color(1, 1, 1, 1);
	mtrl.Emission = Color(0, 0, 0, 0);
	mtrl.Specular = Color(0, 0, 0, 0);
	mtrl.Shininess = 0;
	mtrl.TextureEnable = TRUE;

	material.Init(mtrl);

}



void R_2D::Draw() {        //2023-12-18(��)�@�ǉ��@2D�`��


	// 2D�`��p�̃J�����������s
  	Camera::Draw2D();

	// �V�F�[�_�[��GPU�ɃZ�b�g
	shader.SetGPU();


	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);


	// �}�e���A���ݒ�
	material.SetGPU();

	// �e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &Texture);

	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);


	//���_�f�[�^��������       GPU�ɓ]���@MapUnMap
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(VertexBuffer, 0,
	D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	//����
	vertex[0].Position = Vector3(-(width / 2),-(height / 2),depth);
	vertex[0].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = Vector4(1.0f, 1.0f, 1.0f, alpha);
	vertex[0].TexCoord = Vector2(0.0f, 0.0f);

	//�E��
	vertex[1].Position = Vector3(+(width / 2), -(height / 2), depth);
	vertex[1].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = Vector4(1.0f, 1.0f, 1.0f, alpha);
	vertex[1].TexCoord = Vector2(1.0f, 0.0f);

	//����
	vertex[2].Position = Vector3(-(width / 2), +(height / 2), depth);
	vertex[2].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = Vector4(1.0f, 1.0f, 1.0f, alpha);
	vertex[2].TexCoord = Vector2(0.0f, 1.0f);

	//�E��
	vertex[3].Position = Vector3(+(width / 2), +(height / 2), depth);
	vertex[3].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = Vector4(1.0f, 1.0f, 1.0f, alpha);
	vertex[3].TexCoord = Vector2(1.0f, 1.0f);


	Renderer::GetDeviceContext()->Unmap(VertexBuffer, 0);


	//�}�g���N�X���v�Z
	Matrix mtx;
	DX11MakeWorldMatrixRadian(
		mtx,
		scale,
		rotation,
		position
	);

	//���[���h�}�g���N�X���Z�b�g
	Renderer::SetWorldMatrix(&mtx);
	

	// �|���S���`��
	Renderer::GetDeviceContext()->Draw(4, 0);
	
}



void R_2D::Exit() {

	VertexBuffer->Release();
	material.Uninit();
	Texture->Release();
}


void R_2D::TextureChange(const wchar_t* texturepass) {     //2023-1-18(��)�@�ǉ��@�e�N�X�`���X�V�@

	// �e�N�X�`���ǂݍ���
	DirectX::CreateWICTextureFromFile(
		Renderer::GetDevice(),
		texturepass,
		nullptr,
		&Texture);

	assert(Texture);

}


//�Z�b�^�[
void R_2D::SetWidth(float t_width) {                    //2023-12-19(��)�@�ǉ��@����

	width = t_width;
}

void R_2D::SetHeight(float t_height) {                  //2023-12-19(��)�@�ǉ��@�c��

	height = t_height;
}

void R_2D::SetPosition(DirectX::XMFLOAT3 pos) {         //2023-12-19(��)�@�ǉ��@�ʒu

	position = pos;
}

void R_2D::SetRotation(DirectX::XMFLOAT3 rot) {         //2023-12-19(��)�@�ǉ��@�p�x

	rotation = rot;
}

void R_2D::SetScale(DirectX::XMFLOAT3 scl) {            //2023-12-19(��)�@�ǉ��@�g�k

	scale = scl;
}
void R_2D::SetAlpha(float al) {                                  //2024-1-11(��)�@�ǉ��@�����x

	alpha = al;
}


//�Q�b�^�[
DirectX::XMFLOAT3 R_2D::GetPos() {           //2023-12-21(��)�@�ǉ��@�ʒu�擾�@

	return position;
}
DirectX::XMFLOAT3 R_2D::GetScl() {           //2023-12-21(��)�@�ǉ��@�g�k�@

	return scale;
}
float R_2D::GetAlpha() {                     //2023-1-24(��)�@�ǉ��@�����x�擾

	return alpha;
}

void R_2D::SetDepth_ON() {                   //2023-1-18(��)�@�ǉ��@2D�����ɕ`�悷��

	depth = 1.0f;        //�[�x������
}
