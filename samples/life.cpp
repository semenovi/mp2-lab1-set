#include "tset.h"
#include <iostream>
const int W = 10, H = 10;
void show(TSet& _field)
{
  for (int i = 0; i < H; i++)
  {
    for (int j = 0; j < W; j++)
		cout << (_field.IsMember(i * W + j) ? "x" : "-");
    cout << "\n";
  }
}
void spawn(TSet& _field, int _x, int _y)
{
  _field.InsElem(_x * W + _y);
}
void kill(TSet& _field, int _x, int _y)
{
  _field.DelElem(_x * W + _y);
}
void next_generation(TSet& _field)
{
	int sum = 0;
	for (int i = 1; i < H; i++)
	{
		for (int j = 1; j < W; j++)
		{
		
		if (sum > 3)
			kill(_field, i, j);
		if (sum == 2)
			spawn(_field, i, j);
		}
	}
}
int input_reaction(int _in, TSet& _field)
{
	int out = 1;
	if (_in == 110)
		next_generation(_field);
	else if (_in == 115)
		out = 0;
	return out;
}
int main()
{
	int state = 0, in = 0;
	TSet field(H * W);
	spawn(field, 4, 4);
	spawn(field, 4, 5);
	spawn(field, 5, 4);
	spawn(field, 5, 5);
	show(field);
	while (1)
	{
		in = getchar();
		state = input_reaction(in, field);
		if (state)
		{
			system("cls");
			show(field);
		}
		else
			break;
	}
	return 0;
}