#pragma once
#include  "SimpleMath.h"

using namespace DirectX::SimpleMath;


struct BoundingBoxAABB {   //2023-11-28(火)　編集　AABB

	DirectX::SimpleMath::Vector3 min;      //最小頂点格納
	DirectX::SimpleMath::Vector3 max;      //最大頂点格納

};

struct BoundingBoxOBB : public BoundingBoxAABB{    //2023-11-28(火)　編集　AABBを継承したOBB


	DirectX::SimpleMath::Vector3 center;               //ローカル座標での中心
	DirectX::SimpleMath::Vector3 worldcenter;          //ワールド座標での中心

	// 中心軸（X軸、Y軸、Z軸）Boxの向きを定義
	DirectX::SimpleMath::Vector3 axisX;
	DirectX::SimpleMath::Vector3 axisY;
	DirectX::SimpleMath::Vector3 axisZ;

	// BOXサイズ
	float	lengthx;
	float	lengthy;
	float	lengthz;

};


bool HitCheckOBB(
   const BoundingBoxOBB& obbA,
   const BoundingBoxOBB& obbB);


bool LinetoPlaneCross(     //平面と直線の交差判定
	const Plane& plane,			//平面の方程式
	const Vector3& p0,			//直線の起点
	const Vector3& wv,			//直線の方向ベクトル
	float& t,					// 交点位置情報	
	Vector3& ans);				//交点座標


bool CheckInTriangle(
	const Vector3& a,
	const Vector3& b,
	const Vector3& c,
	const Vector3& p);