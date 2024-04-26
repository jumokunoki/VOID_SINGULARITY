//　カメラ

#pragma once
#include "DxLib.h"		// VECTORやMATRIXを定義として使うため、.hに入れておく
#include "mymath.h"

class Camera {
public:
	Camera();
	~Camera();

	void	Process();
	float GetScale() { return _scale; }

	void SetrcLimit(MYRECT rc) { _rcLimit = rc; }
	void SetPos(VECTOR pos) { _pos = pos; }
	void  Setscale(float scale) { _scale = scale; }

	MATRIX	GetViewMatrix() { return _mView; }

protected:
	
	MATRIX	_mView;		// View行列
	VECTOR	_pos;		// カメラの位置。world座標で
	VECTOR	_lookat;	// カメラの注視点。画面のここを中心に、拡大/回転をする
	float	_scale;		// カメラの拡大率
	float	_rotate;	// カメラの回転（degree)

	MYRECT	_rcLimit;	// world座標でリミット設定


};


