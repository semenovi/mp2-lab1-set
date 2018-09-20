#include "tset.h"
class out_member
{
	bit_matrix * matrix;
public:
	out_member(bit_matrix * _matrix) :
		matrix(_matrix) {};
	out_member& operator= (const int _n)
	{
		matrix
	}
};
class bit_matrix
{
private:
	TSet * bitset;
	int width, height;
public:
	bit_matrix(int _width, int _height, TSet * _bitset) :
		bitset(_bitset), width(_width), height(_height) {};
	out_member operator() (int line, int row)
	{
		return out_member(this);
	}
	void change_state(int _x, int _y, int _n)
	{
		if (_n > height * width)
			return;
		if (_n)
			(*bitset).InsElem(_x + _y * width);
		else
			(*bitset).DelElem(_x + _y * width);
	};
};