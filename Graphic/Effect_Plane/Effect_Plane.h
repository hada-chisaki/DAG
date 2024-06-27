#pragma once
#include "CBillboard.h"
#include "Effect_PlaneMesh.h"
#include "CMeshRenderer.h"
#include "CShader.h"
#include "CMaterial.h"
#include "dx11mathutil.h"
#include "Effect_Info.h"
#include "Timer.h"
#include "Box_Col.h"

using namespace DirectX::SimpleMath;


class Effect_Plane {         //エフェクト用　ビルボードプレーン

private:

	int anim_loop_cnt{};    //アニメのループカウント

	//ビルボード
    CBillboard billboard{};            //ビルボード

	//描画用
	CMeshRenderer mesh_renderer{};         //メッシュレンダラー
	CPlaneMesh_Effect  plane_mesh{};       //プレーンメッシュ
	CShader     shader{};                  //シェーダー
	CMaterial   material{};                //マテリアル
    ID3D11ShaderResourceView* g_Texture{}; //テクスチャ
										   
	Matrix m_view_matrix{};                //ビュー変換マトリクス
	DirectX::XMFLOAT3 m_parent_pos{};      //親の位置を格納 

public:

	Effect_Plane(const wchar_t* filename ,Effect_Info effect_info);    //コンストラクタ
	~Effect_Plane();   //エフェクト

	void Update();     //更新
	void Draw();       //通常描画
	
	void StartDraw();                       //描画を開始する
	bool LimitedTimesDraw(int loop_times);  //限られたループの間だけ描画

	//セッター
	void SetViewMatrix(Matrix view_matrix);
	void SetParentPos(DirectX::XMFLOAT3 parent_pos);
	void SetEffectPos(DirectX::XMFLOAT3 position);
	void SetEffectScale(DirectX::XMFLOAT3 scale);
};