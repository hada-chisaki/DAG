#include "R_2D.h"



bool R_2D::FadeIn(int waitframe, int endframe, int passframe , float speed) {       //基本的なフェードイン


	if (waitframe <= passframe) {    //待ち時間を超えたら

		float alpha_value = 1.0f / ((float)endframe - waitframe) * speed;    //引く量の計算
		alpha = alpha - alpha_value;  //透明度を引いていく
	}

	if (passframe >= endframe) return true;

	return false;
}
bool R_2D::FadeOut(int waitframe, int endframe, int passframe, float speed) {      //フェードアウト


	if (passframe >= waitframe) {     //待ち時間を超えたら

		float alpha_value = 1.0f / ((float)endframe - waitframe) * speed;    //引く量の計算
		alpha = alpha + alpha_value;  //透明度を引いていく
	}

	if (passframe >= endframe) return true;

	return false;
}
bool R_2D::StampUpdate(int waitframe, int endframe, int passframe,float speed) {  //スタンプ更新

	if (passframe >= waitframe) {              //待ち時間を超えたら

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