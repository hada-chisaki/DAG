#pragma once

#include	<d3d11.h>
#include	<SimpleMath.h>
#include	<WICTextureLoader.h>

#include   "game.h"
#include   "dx11mathutil.h"
#include	"renderer.h"
#include	"CShader.h"
#include	"camera.h"
#include	"CMaterial.h"
#include    "easing.h"

using namespace DirectX::SimpleMath;


class R_2D {             //2023-12-19(火)　編集　2D描画クラス

private:
	

	//-------------------------------------
	//大きさや位置・拡縮等
	//-------------------------------------

	float height = 10.0f;
	float width  = 10.0f;
	float alpha  = 0.0f;
	float depth = 0.0f;    

	// RTS情報
	DirectX::XMFLOAT3 position = {SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f};
	DirectX::XMFLOAT3 rotation = {0.0f,0.0f,0.0f};
	DirectX::XMFLOAT3 scale = {1.0f,1.0f,1.0f};
   

	 //-------------------------------------
	 //描画に必要なもの
	 //-------------------------------------

	 CShader shader{};                      // 使用するシェーダー
	 ID3D11Buffer* VertexBuffer{};          // 頂点バッファ
	 ID3D11ShaderResourceView* Texture{};   // テクスチャリソース
	 CMaterial	material{};                 // マテリアル
	   
	 
public:

	//基本関数
	void Init(const wchar_t  texturepass[38]);   
	void Draw();
	void Exit();
	
	//更新
	bool FadeIn(int waitframe, int endframe, int passframe, float speed);      //基本的なフェードイン
	bool FadeOut(int waitframe, int endframe, int passframe, float speed);     //フェードアウト
	bool StampUpdate(int waitframe, int endframe, int passframe, float speed); //スタンプ更新


	void TextureChange(const wchar_t* filename);     //テクスチャの張替
	
	//セッター
	void SetWidth(float t_width);                    //横幅
	void SetHeight(float t_height);                  //縦幅
	void SetPosition(DirectX::XMFLOAT3 pos);         //位置
	void SetRotation(DirectX::XMFLOAT3 rot);         //角度
	void SetScale(DirectX::XMFLOAT3 scl);            //拡縮
	void SetAlpha(float alpha);                      //透明度
	void SetDepth_ON();                              //2Dを奥に描画する


	//ゲッター
	DirectX::XMFLOAT3 GetPos();
	DirectX::XMFLOAT3 GetScl();
	float GetAlpha(); 
};