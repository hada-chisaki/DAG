#pragma once
#include	<simplemath.h>
#include	<random>
#include	"CMesh.h"
#include    "dx11mathutil.h"
#include    "Effect_Info.h"

using namespace DirectX::SimpleMath;


class CPlaneMesh_Effect : public CMesh {   //�G�t�F�N�g�p�v���[�����b�V�� 

private:

	float  m_height = 50.0f;
	float  m_width = 50.0f;
	DirectX::SimpleMath::Color m_color;
	DirectX::SimpleMath::Vector3 m_normal;

	//�A�j���[�V�����֘A
	int animcnt_x = 0;
	int animcnt_y = 0;

	int loopcnt = 0;     //���[�v�J�E���^�[
	int anim_kankaku{};  //�A�j���̐؂�ւ��Ԋu���i�[
	int anim_loop_cnt{};

	int anim_div_x{};  //�A�j���摜�̕�������
	int anim_div_y{};  //�A�j���摜�̕�������

	bool only_one_line = false;  //�ꃉ�C���̂݃��[�v��

public:

	struct FACE {
		unsigned int idx[3];
	};

	void Init(
		Effect_Info info,
		DirectX::SimpleMath::Color color,
		DirectX::SimpleMath::Vector3 normal,
		bool xzflag);

	void CreateVertex();
	void CreateVertexXZ();
	void CreateIndex();

	void AnimUpdate();
	void AnimUpdate_XZ();   //XZ���p

	void ResetAnim();       //�A�j�����[�v�����Z�b�g

	//�Q�b�^�[
	int  GetAnimLoop();     //�A�j���̃��[�v�����擾

};