#pragma once
#include <iostream>
#include "CBoundingBox.h"
#include "CBoxMesh.h"
#include "CMaterial.h"
#include "CMeshRenderer.h"
#include "dx11mathutil.h"
#include "Box_R.h"
#include "BoxCol_Info.h"

//2023-12-1(金)　DirectXとDirecctX::SimpleMathのネームスペースが混在すると、
//               コンパイラが混乱するので、DirectX::を判別できるように先頭につける


using namespace DirectX::SimpleMath;


class Box_Col {                 //2023-11-30(木)　 試作　当たり判定ボックス描画セット

private:


	int ctrl = 0;                      //拡縮移動回転操作変える用

	Box_R  box_model;
	CBoundingBox obb;                  //バウンディングボックス
	
	bool flag_hitcheck_ON;             //当たり判定の切り替え


public:

	char col_name[60]; //当たり判定の名前

	Box_Col();     //コンストラクタ
	~Box_Col();    //デストラクタ


	//基本関数
	void Init();
	bool Draw(BoundingBoxOBB obbB);
	void Exit();
	
	void Edit_Update(int sel_srt, int sel_xyz);
	bool CheckDraw(BoundingBoxOBB obbB, Color before_color, Color after_color);    //Editer用描画


	//当たり判定切り替えフラグ
	void HitCheck_ON();
	void HitCheck_OFF();


	//セッター
	void SetMat(Matrix parent_mat, Matrix child_mat);
	void SetBoxLength(DirectX::XMFLOAT3 length);
	void SetBoxColEdit_Value(Edit_Value edit_value);
	
	//ゲッター
	BoundingBoxOBB GetBoundingBox();


	//セーブ関連
	void Save(const char* filename);        //セーブ
	void SetSave(const char* filename);     //セーブ書き出し
	
};

