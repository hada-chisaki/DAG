#pragma once
#include <SimpleMath.h>


struct PlaneInfo {       //2023-12-25(月)　追加　平面の方程式情報

	DirectX::SimpleMath::Plane      plane;  //平面の方程式

	//頂点座標
	DirectX::SimpleMath::Vector3    p0;
	DirectX::SimpleMath::Vector3    p1;
	DirectX::SimpleMath::Vector3    p2;
	
};



class CPlane {          //2023-12-25(月)　追加　平面クラス

private:

	PlaneInfo plane_info;

public:


	void MakeEquatation(
		DirectX::SimpleMath::Vector3    p0,
		DirectX::SimpleMath::Vector3    p1,
		DirectX::SimpleMath::Vector3    p2
	);


	//ゲッター
	PlaneInfo GetPlaneInfo();
};