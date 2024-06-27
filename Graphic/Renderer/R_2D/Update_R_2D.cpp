#include "R_2D.h"



bool R_2D::FadeIn(int waitframe, int endframe, int passframe , float speed) {       //��{�I�ȃt�F�[�h�C��


	if (waitframe <= passframe) {    //�҂����Ԃ𒴂�����

		float alpha_value = 1.0f / ((float)endframe - waitframe) * speed;    //�����ʂ̌v�Z
		alpha = alpha - alpha_value;  //�����x�������Ă���
	}

	if (passframe >= endframe) return true;

	return false;
}
bool R_2D::FadeOut(int waitframe, int endframe, int passframe, float speed) {      //�t�F�[�h�A�E�g


	if (passframe >= waitframe) {     //�҂����Ԃ𒴂�����

		float alpha_value = 1.0f / ((float)endframe - waitframe) * speed;    //�����ʂ̌v�Z
		alpha = alpha + alpha_value;  //�����x�������Ă���
	}

	if (passframe >= endframe) return true;

	return false;
}
bool R_2D::StampUpdate(int waitframe, int endframe, int passframe,float speed) {  //�X�^���v�X�V

	if (passframe >= waitframe) {              //�҂����Ԃ𒴂�����

		int frame = endframe - passframe;
		float ease_x = frame * 0.016f * speed;
		float value = easeOutCirc(ease_x);

		float alpha_value = 1.0f / (endframe - waitframe);
		alpha += alpha_value;

		scale = { value + 1.0f ,value + 1.0f, 1.0f };
	}

	if (passframe >= endframe) return true;

	return false;
}