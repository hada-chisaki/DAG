#include  "CPlane.h"



void CPlane::MakeEquatation(         //2023-12-25(月)　追加　平面の方程式を作成する
    DirectX::SimpleMath::Vector3 p0,
    DirectX::SimpleMath::Vector3 p1,
    DirectX::SimpleMath::Vector3 p2
) {


    DirectX::SimpleMath::Plane p;
    DirectX::SimpleMath::Vector3 p0p1;     //点p0とp1のベクトル格納
    DirectX::SimpleMath::Vector3 p1p2;     //点p1とp2のベクトル格納
    DirectX::SimpleMath::Vector3 normal;     //外積を格納して正規化


    //ベクトルを求める
    p0p1 = p1 - p0;
    p1p2 = p2 - p1;

    //外積を求める
    normal = p0p1.Cross(p1p2);

    //正規化
    normal.Normalize();


    //平面の方程式のa,b,c,dを求める
    p.x = normal.x;
    p.y = normal.y;
    p.z = normal.z;
    p.w = -(p.x * p0.x + p.y * p0.y + p.z * p0.z);


    //メンバ変数にセット
    plane_info.plane = p;

    plane_info.p0 = p0;
    plane_info.p1 = p1;
    plane_info.p2 = p2;
}

PlaneInfo CPlane::GetPlaneInfo() {  //2023-12-25(月)　追加　メンバ変数を返す

    return plane_info;
}