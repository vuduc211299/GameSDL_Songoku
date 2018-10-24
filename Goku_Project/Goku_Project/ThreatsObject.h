#ifndef THREATSOBJECT_H_

#define THREATSOBJECT_H_


#include "BaseObject.h"
#include "CommonFunction.h"

const int  WIDTH_THREAT =80;
const int  HEIGHT_THREAT =45;


class ThreatsObject : public BaseObject
{
public:
	ThreatsObject();
	~ThreatsObject();

	void HandleMove(const int &x, const int &y);
	void Resetthreats(const int &x_border);
	void Set_x_val(const int &val) { x_val_ = val; }
	void Set_y_val(const int &val) { y_val_ = val; }

	int get_x_val() const { return x_val_; }
	int get_y_val() const { return y_val_; }

private:
	int x_val_;
	int y_val_;
};



#endif // THREATSOBJECT_H_
