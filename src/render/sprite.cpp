#include "sprite.hpp"
#include "decode_img.hpp"

byte Sprite::frame_cnt = 0;
void Sprite::start_next_frame()
{
	// 60번째 프레임일 경우 0으로 세팅.
	frame_cnt = frame_cnt > 59 ? 0 : frame_cnt + 1;
}

Sprite::Sprite() {}
Sprite::Sprite(byte _face_id, short _x, short _y)
{
	x = _x;
	y = _y;
	vx = 0; // 속도의 단위는 vx px / x_frame 프레임으로 계산한다. 즉 x_frame 프레임마다 vx px 만큼 움직인다.
	vy = 0;
	x_frame = 100; // x_frame, y_frame이 가질 수 있는 값은 60의 약수이다. 메모리 최적화를 위해 frame_cnt를 static으로 관리하고, 60 프레임마다 0으로 세팅하기 때문이다.
	y_frame = 100;
	face_id = _face_id;
}

void Sprite::render() { DecodeSprite(face_id, x, y); }

void Sprite::next_frame()
{
	// 나머지가 0일 경우, 즉 x_frame만큼 지났을 경우 x좌표 이동.
	if (!(frame_cnt % x_frame))
	{
		x += vx;
	}
	if (!(frame_cnt % y_frame))
	{
		y += vy;
	}
	// % 연산은 굉장히 느림. x_frame을 2^n의 값만 가지게 한다면 시프트 연산으로 처리 가능...
}