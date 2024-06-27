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


class R_2D {             //2023-12-19(��)�@�ҏW�@2D�`��N���X

private:
	

	//-------------------------------------
	//�傫����ʒu�E�g�k��
	//-------------------------------------

	float height = 10.0f;
	float width  = 10.0f;
	float alpha  = 0.0f;
	float depth = 0.0f;    

	// RTS���
	DirectX::XMFLOAT3 position = {SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f};
	DirectX::XMFLOAT3 rotation = {0.0f,0.0f,0.0f};
	DirectX::XMFLOAT3 scale = {1.0f,1.0f,1.0f};
   

	 //-------------------------------------
	 //�`��ɕK�v�Ȃ���
	 //-------------------------------------

	 CShader shader{};                      // �g�p����V�F�[�_�[
	 ID3D11Buffer* VertexBuffer{};          // ���_�o�b�t�@
	 ID3D11ShaderResourceView* Texture{};   // �e�N�X�`�����\�[�X
	 CMaterial	material{};                 // �}�e���A��
	   
	 
public:

	//��{�֐�
	void Init(const wchar_t  texturepass[38]);   
	void Draw();
	void Exit();
	
	//�X�V
	bool FadeIn(int waitframe, int endframe, int passframe, float speed);      //��{�I�ȃt�F�[�h�C��
	bool FadeOut(int waitframe, int endframe, int passframe, float speed);     //�t�F�[�h�A�E�g
	bool StampUpdate(int waitframe, int endframe, int passframe, float speed); //�X�^���v�X�V


	void TextureChange(const wchar_t* filename);     //�e�N�X�`���̒���
	
	//�Z�b�^�[
	void SetWidth(float t_width);                    //����
	void SetHeight(float t_height);                  //�c��
	void SetPosition(DirectX::XMFLOAT3 pos);         //�ʒu
	void SetRotation(DirectX::XMFLOAT3 rot);         //�p�x
	void SetScale(DirectX::XMFLOAT3 scl);            //�g�k
	void SetAlpha(float alpha);                      //�����x
	void SetDepth_ON();                              //2D�����ɕ`�悷��


	//�Q�b�^�[
	DirectX::XMFLOAT3 GetPos();
	DirectX::XMFLOAT3 GetScl();
	float GetAlpha(); 
};