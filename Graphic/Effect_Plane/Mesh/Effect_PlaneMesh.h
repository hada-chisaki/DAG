#pragma once
#include	<simplemath.h>
#include	<random>
#include	"CMesh.h"
#include    "dx11mathutil.h"
#include    "Effect_Info.h"

using namespace DirectX::SimpleMath;


class CPlaneMesh_Effect : public CMesh {   //エフェクト用プレーンメッシュ 

private:

	float  m_height = 50.0f;
	float  m_width = 50.0f;
	DirectX::SimpleMath::Color m_color;
	DirectX::SimpleMath::Vector3 m_normal;

	//アニメーション関連
	int animcnt_x = 0;
	int animcnt_y = 0;

	int loopcnt = 0;     //ループカウンター
	int anim_kankaku{};  //アニメの切り替え間隔を格納
	int anim_loop_cnt{};

	int anim_div_x{};  //アニメ画像の分割数ｘ
	int anim_div_y{};  //アニメ画像の分割数ｙ

	bool only_one_line = false;  //一ラインのみループか

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
	void AnimUpdate_XZ();   //XZ軸用

	void ResetAnim();       //アニメループをリセット

	//ゲッター
	int  GetAnimLoop();     //アニメのループ数を取得

};