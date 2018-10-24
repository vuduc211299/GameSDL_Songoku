#ifndef BULLET_OBJECT_H_

#define BULLET_OBJECT_H_

#include "BaseObject.h"
#include "CommonFunction.h"

const int WIDTH_BULLET = 88;
const int HEIGHT_BULLET = 57;
const int WIDTH_BULLET2 = 45;
const int HEIGHT_BULLET2 = 45;

class BulletObject : public BaseObject
{
public:
	enum bullet_type
	{
		DRAGON=2,
		SPHERE=1,
		NONE=0
	};

	BulletObject();
	~BulletObject();

	void HandleActionInput(SDL_Event event_);
	void HandleMove(const int &x_border, const int & y_border);

	int get_type() const { return bullet_type; }
	void set_type(const int & type) { bullet_type = type; }

	bool get_is_move() const { return is_move_; }
	void set_is_move(bool is_move) { is_move_ = is_move; }
	void SetWidthHeight(const int &width, const int &height) { rect_.w = width; rect_.h = height; };
	void HandleMoveRighttoLeft();
private:
	int x_val_;
	int y_val_;
	bool is_move_;
	bool check_move_kameha;
	int bullet_type;
};

#endif