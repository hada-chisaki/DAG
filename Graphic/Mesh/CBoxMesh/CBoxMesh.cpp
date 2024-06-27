#include	"CBoxMesh.h"

using namespace DirectX::SimpleMath;


// ���_���W���m�[�}���C�Y
void CBoxMesh::Normalize(
	Vector3 vec,
	Vector3& Normal) {

	vec.Normalize();
	Normal = vec;

}

void CBoxMesh::Init(float width,
	float height,
	float depth,
	Color color)
{
	// �T�C�Y��ۑ�
	lengthx = width;
	lengthy = height;
	lengthz = depth;

	// �J���[�l��ۑ�
	m_color = color;

	// �C���f�b�N�X�f�[�^���쐬
	CreateIndex();

	// ���_�f�[�^���쐬
	CreateVertex();
}

// ���_�f�[�^����
void CBoxMesh::CreateVertex() {

	// ���_�N���A
	m_vertices.clear();

	m_vertices.resize(12);
	m_vertices[0].Position.x = -(lengthx / 2.0f);
	m_vertices[0].Position.y = (lengthy / 2.0f);
	m_vertices[0].Position.z = -(lengthz / 2.0f);

	m_vertices[1].Position.x = (lengthx / 2.0f);
	m_vertices[1].Position.y = (lengthy / 2.0f);
	m_vertices[1].Position.z = -(lengthz / 2.0f);

	m_vertices[2].Position.x = (lengthx / 2.0f);
	m_vertices[2].Position.y = -(lengthy / 2.0f);
	m_vertices[2].Position.z = -(lengthz / 2.0f);

	m_vertices[3].Position.x = -(lengthx / 2.0f);
	m_vertices[3].Position.y = -(lengthy / 2.0f);
	m_vertices[3].Position.z = -(lengthz / 2.0f);

	m_vertices[4].Position.x = -(lengthx / 2.0f);
	m_vertices[4].Position.y = (lengthy / 2.0f);
	m_vertices[4].Position.z = (lengthz / 2.0f);

	m_vertices[5].Position.x = (lengthx / 2.0f);
	m_vertices[5].Position.y = (lengthy / 2.0f);
	m_vertices[5].Position.z = (lengthz / 2.0f);

	m_vertices[6].Position.x = (lengthx / 2.0f);
	m_vertices[6].Position.y = -(lengthy / 2.0f);
	m_vertices[6].Position.z = (lengthz / 2.0f);

	m_vertices[7].Position.x = -(lengthx / 2.0f);
	m_vertices[7].Position.y = -(lengthy / 2.0f);
	m_vertices[7].Position.z = (lengthz / 2.0f);


	for (int i = 0; i < 8; i++) {
		// ���_�J���[�ݒ�
		m_vertices[i].Diffuse = m_color;
		// �m�[�}���C�Y
		Normalize(
			m_vertices[i].Position,
			m_vertices[i].Normal);
	}

}

// �C���f�b�N�X����
void CBoxMesh::CreateIndex() {

	struct FACE {
		unsigned int idx[3];
	};

	// �C���f�b�N�X�f�[�^�N���A
	m_indices.clear();

	// �C���f�b�N�X�𐶐�
	FACE faces[12];

	//-----------------------------------

	faces[0].idx[0] = 0;		// ��O  
	faces[0].idx[1] = 1;
	faces[0].idx[2] = 2;

	faces[1].idx[0] = 2;
	faces[1].idx[1] = 3;
	faces[1].idx[2] = 0;

	//-----------------------------------

	faces[2].idx[0] = 5;		// ��  
	faces[2].idx[1] = 4;
	faces[2].idx[2] = 7;

	faces[3].idx[0] = 7;
	faces[3].idx[1] = 6;
	faces[3].idx[2] = 5;

	//-----------------------------------

	faces[4].idx[0] = 4;		// ���� 
	faces[4].idx[1] = 0;
	faces[4].idx[2] = 7;

	faces[5].idx[0] = 0;
	faces[5].idx[1] = 3;
	faces[5].idx[2] = 7;

	//-----------------------------------

	faces[6].idx[0] = 1;		// �E�� 
	faces[6].idx[1] = 5;
	faces[6].idx[2] = 6;

	faces[7].idx[0] = 1;
	faces[7].idx[1] = 6;
	faces[7].idx[2] = 2;

	//-----------------------------------

	faces[8].idx[0] = 0;		// �㑤 
	faces[8].idx[1] = 4;
	faces[8].idx[2] = 1;

	faces[9].idx[0] = 4;
	faces[9].idx[1] = 5;
	faces[9].idx[2] = 1;

	//-----------------------------------

	faces[10].idx[0] = 3;		// ����
	faces[10].idx[1] = 2;
	faces[10].idx[2] = 7;

	faces[11].idx[0] = 6;
	faces[11].idx[1] = 7;
	faces[11].idx[2] = 2;

	//-----------------------------------


	// �C���f�b�N�X�o�^
	for (int i = 0; i < 12; i++) {
		m_indices.emplace_back(faces[i].idx[0]);
		m_indices.emplace_back(faces[i].idx[1]);
		m_indices.emplace_back(faces[i].idx[2]);
	}
}
