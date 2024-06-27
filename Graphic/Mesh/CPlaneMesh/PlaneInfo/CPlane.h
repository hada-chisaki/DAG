#pragma once
#include <SimpleMath.h>


struct PlaneInfo {       //2023-12-25(��)�@�ǉ��@���ʂ̕��������

	DirectX::SimpleMath::Plane      plane;  //���ʂ̕�����

	//���_���W
	DirectX::SimpleMath::Vector3    p0;
	DirectX::SimpleMath::Vector3    p1;
	DirectX::SimpleMath::Vector3    p2;
	
};



class CPlane {          //2023-12-25(��)�@�ǉ��@���ʃN���X

private:

	PlaneInfo plane_info;

public:


	void MakeEquatation(
		DirectX::SimpleMath::Vector3    p0,
		DirectX::SimpleMath::Vector3    p1,
		DirectX::SimpleMath::Vector3    p2
	);


	//�Q�b�^�[
	PlaneInfo GetPlaneInfo();
};