#pragma once
#include "dx11mathutil.h"

using namespace DirectX::SimpleMath;

struct Effect_Info {         //�G�t�F�N�g�̏��

public:

	int width{};
	int height{};

    Color color = {1.0f,1.0f,1.0f,1.0f};

	//�A�j�����
	int anim_div_x{};
	int anim_div_y{};
	int anim_kankaku{};

	bool only_one_line = false;  //�ꃉ�C���������[�v����̂�
};


enum class Effect_Name {     //�G�t�F�N�g�̖��O

	Dash_Attack,
	Water_Shot_1,
	Water_Shot_2,
	Change_Stage_1,
	Change_Stage_2,
	Effect_Max

};

struct Effect_Save {

	Effect_Info effect_info[(int)Effect_Name::Effect_Max];

	DirectX::XMFLOAT3 pos[(int)Effect_Name::Effect_Max];
	DirectX::XMFLOAT3 parent_pos[(int)Effect_Name::Effect_Max];
	DirectX::XMFLOAT3 scl[(int)Effect_Name::Effect_Max];

};