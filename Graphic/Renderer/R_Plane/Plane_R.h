#pragma once
#include <iostream>

#include "CShader.h"
#include "CMaterial.h"
#include "CPlaneMesh.h"
#include "CPlane.h"
#include "CMeshRenderer.h"
#include "dx11mathutil.h"


using namespace DirectX::SimpleMath;


struct Plane_SRT {               //2024-1-13(土)　追加　PlaneのSRT情報


	// 床の情報(S,R,T)
	DirectX::XMFLOAT3	position = { 0.0f,0.0f,0.0f };		// 位置
	DirectX::XMFLOAT3	rotation = { 0.0f,0.0f,0.0f };		// 姿勢
	DirectX::XMFLOAT3	scale = { 1.0f,1.0f,1.0f };			// 拡縮
	

};


struct Plane_Info {          //2024-1-13(土)　追加　Plane初期化セット

	
	int div_x = 10;	                           //分割数　横
    int div_y = 10;                             //分割数　縦

	int width = 100;                           //平面の幅
	int height = 100;                          //平面の高さ

	Color color = { 1.0f,1.0f,1.0f };          //頂点カラー
	Vector3 normal = { 0.0f,0.0f,-1.0f};       //平面の向き
	bool xz_flag = true;                       //xzの平面化どうか

};


class Plane_R {    //2024-1-13(土)　追加　地面描画クラス


private:

	//描画に必要な情報

	 CShader		shader;                   //シェーダー
	 CPlaneMesh     planemesh;                //  床メッシュ（ジオメトリデータ）
	 CMeshRenderer  meshrenderer;             // 床メッシュ（レンダリングデータ）
	 CMaterial	    material;                 // 床用マテリアル

	// SRV（テクスチャ）
	 Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;
	 std::vector<CPlane> planes;

	 //Plane情報
	 Plane_Info plane_info;
	 Plane_SRT plane_srt;

public:
 

	//基本関数　
	void Init(const char* texture_filename);
	void Update();
	void Draw();
	void Exit();


	//地面の当たり判定用
	void   makepalenequatation();
	float  GetFieldHeightBySqno(Vector3 pos);
	float  GetFieldHeight(Vector3 pos);

	//セッター
	void SetPlaneInfo(Plane_Info);
	void SetPlaneSRT(Plane_SRT);

	//ゲッター
	Plane_Info GetPlaneInfo();
};