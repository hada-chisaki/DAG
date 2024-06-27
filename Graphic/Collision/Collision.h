#pragma once
#include  "SimpleMath.h"

using namespace DirectX::SimpleMath;


struct BoundingBoxAABB {   //2023-11-28(��)�@�ҏW�@AABB

	DirectX::SimpleMath::Vector3 min;      //�ŏ����_�i�[
	DirectX::SimpleMath::Vector3 max;      //�ő咸�_�i�[

};

struct BoundingBoxOBB : public BoundingBoxAABB{    //2023-11-28(��)�@�ҏW�@AABB���p������OBB


	DirectX::SimpleMath::Vector3 center;               //���[�J�����W�ł̒��S
	DirectX::SimpleMath::Vector3 worldcenter;          //���[���h���W�ł̒��S

	// ���S���iX���AY���AZ���jBox�̌������`
	DirectX::SimpleMath::Vector3 axisX;
	DirectX::SimpleMath::Vector3 axisY;
	DirectX::SimpleMath::Vector3 axisZ;

	// BOX�T�C�Y
	float	lengthx;
	float	lengthy;
	float	lengthz;

};


bool HitCheckOBB(
   const BoundingBoxOBB& obbA,
   const BoundingBoxOBB& obbB);


bool LinetoPlaneCross(     //���ʂƒ����̌�������
	const Plane& plane,			//���ʂ̕�����
	const Vector3& p0,			//�����̋N�_
	const Vector3& wv,			//�����̕����x�N�g��
	float& t,					// ��_�ʒu���	
	Vector3& ans);				//��_���W


bool CheckInTriangle(
	const Vector3& a,
	const Vector3& b,
	const Vector3& c,
	const Vector3& p);