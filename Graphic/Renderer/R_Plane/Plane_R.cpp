#include "Plane_R.h"
#include "Collision.h"


void Plane_R::Init(const char* texture_filename) {           //2024-1-13(�y)�@�ǉ��@�n�ʏ�����


	// �g�p����V�F�[�_�[�𐶐�
	shader.SetShader(
		"shader/unlitTextureVS.hlsl",				// ���_�V�F�[�_
		"shader/unlitTexturePS.hlsl");				// �s�N�Z���V�F�[�_


	// �����b�V������
	planemesh.Init(
		plane_info.div_x, 
		plane_info.div_y,		          // ������
		plane_info.width,			      // �T�C�Y
		plane_info.height,			      // �T�C�Y
		plane_info.color,		          // ���_�J���[
		plane_info.normal,                 // �@���x�N�g��
		plane_info.xz_flag
		);


	makepalenequatation();

	// ���b�V�������_�������i���p�j
	meshrenderer.Init(planemesh);

	// �e�N�X�`���ǂݍ���
	ID3D11Device* dev;
	ID3D11DeviceContext* devcontext;

	dev = Renderer::GetDevice();
	devcontext = Renderer::GetDeviceContext();



	bool sts = CreateSRVfromFile(texture_filename, dev, devcontext, &srv);
	if (!sts) {
		MessageBox(nullptr, "CreateSRVfromFile error(MeshWallInit)", "error", MB_OK);
	}

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
void Plane_R::Update() {                                     //2024-1-13(�y)�@�ǉ��@�n�ʍX�V


}
void Plane_R::Draw() {                                       //2024-1-13(�y)�@�ǉ��@�n�ʕ`��

	Matrix mtx;

	// GPU�ɍs����Z�b�g����
	Renderer::SetWorldMatrix(&mtx);

	// ���p�V�F�[�_�Z�b�g
	shader.SetGPU();

	// ���p�}�e���A���Z�b�g
	material.SetGPU();

	// GPU�ɍs����Z�b�g����
	DX11MakeWorldMatrix(
		mtx,
		plane_srt.scale,							// �X�P�[��
		plane_srt.rotation,							// �p��
		plane_srt.position);						// �ʒu

	Renderer::SetWorldMatrix(&mtx);

	// �e�N�X�`�����Z�b�g
	ID3D11DeviceContext* devcontext;
	devcontext = Renderer::GetDeviceContext();
	devcontext->PSSetShaderResources(0, 1, srv.GetAddressOf());

	// ���`��
	meshrenderer.Draw();

}
void Plane_R::Exit() {                                       //2024-1-13(�y)�@�ǉ��@�n�ʏI��


	material.Uninit();
}





//�n�ʂƂ̓����蔻��
void   Plane_R::makepalenequatation() {                   //2024-1-13(�y)�@


	for (unsigned int idx = 0; idx < planemesh.GetIndices().size() / 3; idx++) {
		CPlaneMesh::FACE f = planemesh.GetTriangle(idx);

		VERTEX_3D v0 = planemesh.GetVertices()[f.idx[0]];
		VERTEX_3D v1 = planemesh.GetVertices()[f.idx[1]];
		VERTEX_3D v2 = planemesh.GetVertices()[f.idx[2]];

		CPlane p;
		p.MakeEquatation(v0.Position, v1.Position, v2.Position);
		planes.emplace_back(p);
	}
}
float  Plane_R::GetFieldHeightBySqno(Vector3 pos) {                  //2024-1-13(�y)�@�ǉ��@���݂̍��������߂�


	float t;

	// ���݈ʒu����̂����Ă���l�p�`�ԍ����擾
	int sqno = planemesh.GetSquareNo(pos);

	static float oldheight = 0;

	// ���ʃ`�F�b�N
	{
		int idx = sqno * 2;

		// �ʐ���
		Vector3 up = { 0,1,0 };
		Vector3 startpoint = { pos.x,0,pos.z };
		Plane p = planes[idx].GetPlaneInfo().plane;
		Vector3 ans;


		bool sts = LinetoPlaneCross(p, startpoint, up, t, ans);
		if (sts) {
			sts = CheckInTriangle(
				planes[idx].GetPlaneInfo().p0,
				planes[idx].GetPlaneInfo().p1,
				planes[idx].GetPlaneInfo().p2, ans);
			if (sts) {
				oldheight = ans.y;
				return ans.y;
			}
		}

	}

	// ��ʃ`�F�b�N
	{
		int idx = sqno * 2 + 1;

		// �ʐ���
		Vector3 up = { 0,1,0 };
		Vector3 startpoint = { pos.x,0,pos.z };
		Plane p = planes[idx].GetPlaneInfo().plane;
		Vector3 ans;

		bool sts = LinetoPlaneCross(p, startpoint, up, t, ans);
		if (sts) {
			sts = CheckInTriangle(
				planes[idx].GetPlaneInfo().p0,
				planes[idx].GetPlaneInfo().p1,
				planes[idx].GetPlaneInfo().p2, ans);
			if (sts) {
				oldheight = ans.y;
				return ans.y;
			}
		}
	}

	// ������Ȃ������ꍇ�͂O
	std::cout << "���Ȃ�" << "(" << sqno << ")" << std::endl;
	return oldheight;

}
float  Plane_R::GetFieldHeight(Vector3 pos) {                      //2024-1-13(�y)�@�ǉ��@���݂̍��������߂�

	float t;

	// �ʐ���
	for (unsigned int idx = 0; idx < planes.size(); idx++) {
		Vector3 up = { 0,1,0 };
		Vector3 startpoint = { pos.x,0,pos.z };
		Plane p = planes[idx].GetPlaneInfo().plane;
		Vector3 ans;

		bool sts = LinetoPlaneCross(p, startpoint, up, t, ans);
		if (sts) {
			sts = CheckInTriangle(
				planes[idx].GetPlaneInfo().p0,
				planes[idx].GetPlaneInfo().p1,
				planes[idx].GetPlaneInfo().p2, ans);
			if (sts) return ans.y;
		}

	}

	return 0;
}


//�Z�b�^�[
void Plane_R::SetPlaneInfo(Plane_Info info) {          //2024-1-15(��)�@�ǉ��@PlaneInfo�Z�b�g

	plane_info = info;
}
void Plane_R::SetPlaneSRT(Plane_SRT srt) {                          //2024-1-26(��)�@�ҏW�@PlaneSRT�Z�b�g

	plane_srt = srt;
}

//�Q�b�^�[
Plane_Info Plane_R::GetPlaneInfo() {                   //�v���[���̏����擾

	return plane_info;
}