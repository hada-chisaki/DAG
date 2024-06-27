#include  "CPlane.h"



void CPlane::MakeEquatation(         //2023-12-25(��)�@�ǉ��@���ʂ̕��������쐬����
    DirectX::SimpleMath::Vector3 p0,
    DirectX::SimpleMath::Vector3 p1,
    DirectX::SimpleMath::Vector3 p2
) {


    DirectX::SimpleMath::Plane p;
    DirectX::SimpleMath::Vector3 p0p1;     //�_p0��p1�̃x�N�g���i�[
    DirectX::SimpleMath::Vector3 p1p2;     //�_p1��p2�̃x�N�g���i�[
    DirectX::SimpleMath::Vector3 normal;     //�O�ς��i�[���Đ��K��


    //�x�N�g�������߂�
    p0p1 = p1 - p0;
    p1p2 = p2 - p1;

    //�O�ς����߂�
    normal = p0p1.Cross(p1p2);

    //���K��
    normal.Normalize();


    //���ʂ̕�������a,b,c,d�����߂�
    p.x = normal.x;
    p.y = normal.y;
    p.z = normal.z;
    p.w = -(p.x * p0.x + p.y * p0.y + p.z * p0.z);


    //�����o�ϐ��ɃZ�b�g
    plane_info.plane = p;

    plane_info.p0 = p0;
    plane_info.p1 = p1;
    plane_info.p2 = p2;
}

PlaneInfo CPlane::GetPlaneInfo() {  //2023-12-25(��)�@�ǉ��@�����o�ϐ���Ԃ�

    return plane_info;
}