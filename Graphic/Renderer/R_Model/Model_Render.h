#pragma once


#include	"CDirectInput.h"
#include	"dx11mathutil.h"
#include    "CShader.h"
#include	"CStaticMesh.h"
#include	"CStaticMeshRenderer.h"


struct Model_SRT{         //2023-12-14(木)　追加　位置情報


	// モデルの情報(S,R,T)
	DirectX::XMFLOAT3	position = { 0.0f,0.0f,0.0f };		// 位置
	DirectX::XMFLOAT3	rotation = { 0.0f,0.0f,0.0f };		// 姿勢
	DirectX::XMFLOAT3	scale = { 1.0f,1.0f,1.0f };			// 拡縮

};

struct Model_Info {

	DirectX::XMFLOAT3  max; 
	DirectX::XMFLOAT3  min;
	DirectX::XMFLOAT3  center;
    DirectX::XMFLOAT3  length;

};

struct CameraForward {

	DirectX::SimpleMath::Vector3 c_front;      //y軸
    DirectX::SimpleMath::Vector3 c_right;      //x軸

};

class Model_Render {       //2023-12-14(木)　編集　モデルレンダークラス

public:


	void Init(std::string modelname);
	void Edit_Update();
	void Parent_Draw();          //親モデルの場合
	void Child_Draw(DirectX::SimpleMath::Matrix parent_mat);      //子モデルの場合
	void GrandChild_Draw(DirectX::SimpleMath::Matrix parent_mat, DirectX::SimpleMath::Matrix child_mat);    //孫モデルの場合
	void Exit();
	
	void Model_VerCalc();     //頂点を計算

	//セッター
	void SetModelPos(DirectX::XMFLOAT3 pos);
	void SetModelRot(DirectX::XMFLOAT3 rot);
	void SetModelScl(DirectX::XMFLOAT3 scl);
	void SetModel_SRT(Model_SRT srt);
	void SetCameraForward(DirectX::SimpleMath::Vector3 c_front, DirectX::SimpleMath::Vector3 c_right);

	//マトリクス作成
	DirectX::SimpleMath::Matrix Create_Parent_Mat();     //親モデルの場合
	DirectX::SimpleMath::Matrix Create_Child_Mat(DirectX::SimpleMath::Matrix parent_mat);      //子モデルの場合
	DirectX::SimpleMath::Matrix Create_GrandChild_Mat(DirectX::SimpleMath::Matrix parent_mat, DirectX::SimpleMath::Matrix child_mat);
	

	//ゲッター
	DirectX::SimpleMath::Matrix Get_Parent_Mat();                 //親のマトリクスをゲット
	DirectX::SimpleMath::Matrix Get_Child_Mat(DirectX::SimpleMath::Matrix parent_mat);
	DirectX::XMFLOAT3 GetModelPos();
    DirectX::XMFLOAT3 GetModelRot();
	DirectX::XMFLOAT3 GetModelScl();
	Model_SRT GetModel_SRT();
	DirectX::XMFLOAT3 GetModel_Min();      //モデルの最小頂点値を返す
    DirectX::XMFLOAT3 GetModel_Man();      //モデルの最大頂点値を返す
	DirectX::XMFLOAT3 GetModel_Center();   //モデルの中心点返す
    DirectX::XMFLOAT3 GetModel_Length();    //モデルの長さを返す


	//セーブ
	void Save(const char* filename);         //ファイルに書き込み
	void SetSave(const char* filename);      //セーブ情報をセット


private:


	CShader     shader;
	CameraForward  camera_forward;
	Model_Info  model_info;
	Model_SRT   model_srt;      //位置情報格納 

	int edit_sel{};   //編集用

	//メッシュとレンダラー
	CStaticMesh staticmesh;   	              // スタティックメッシュ（ジオメトリデータ）
	CStaticMeshRenderer staticmeshrenderer;   // メッシュレンダラー


};