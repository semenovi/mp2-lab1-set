#include "tset.h"
#include <iostream>
#include <conio.h>
int W = 10, H = 10;
void change_cell_state(int x, int y, int state, TSet _sheet)
{
	if (state > -1 && state < 2 && x > -1 && x < W && y > -1 && y < H)
	{
		_sheet.InsElem(x + y * W);
	}
	else throw(0);
}
int get_cell_state(int x, int y, TSet * _sheet)
{
	if (x > -1 && x < W && y > -1 && y < H)
	{
		return (*_sheet).IsMember(x + y * W);
	}
	else throw(0);
}
void draw_cells(int _cursor, TSet * _sheet)
{
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
			if (i * W + j == _cursor)
				cout << "_ ";
			else
				cout << ((*_sheet).IsMember(i * W + j) ? "x" : "-") << " ";
		cout << "\n";
	}
}
int get_cell_state_in_next_generation(int _i, TSet * _sheet)
{
	int x = 0, y = 0, sum_current = 0;

	x = _i - (_i / W) * W;
	y = _i / W;
	if (y < 1)
	{//bottom
		if (x < 1)
		{//left
			sum_current = (
				get_cell_state(x + 1, y, _sheet) +
				get_cell_state(x + 1, y + 1, _sheet) +
				get_cell_state(x, y + 1, _sheet)
				);
		}
		else if (x > H - 2)
		{//right
			sum_current = (
				get_cell_state(x - 1, y, _sheet) +
				get_cell_state(x - 1, y + 1, _sheet) +
				get_cell_state(x, y + 1, _sheet)
				);
		}
		else
		{//center
			sum_current = (
				get_cell_state(x - 1, y, _sheet) +
				get_cell_state(x + 1, y, _sheet) +
				get_cell_state(x, y + 1, _sheet) +
				get_cell_state(x + 1, y + 1, _sheet) +
				get_cell_state(x - 1, y + 1, _sheet)
				);
		}
	}
	else if (y > H - 2)
	{//top
		if (x < 1)
		{//left
			sum_current = (
				get_cell_state(x + 1, y, _sheet) +
				get_cell_state(x, y - 1, _sheet) +
				get_cell_state(x + 1, y - 1, _sheet)
				);
		}
		else if (x > W - 2)
		{//right
			sum_current = (
				get_cell_state(x - 1, y, _sheet) +
				get_cell_state(x, y - 1, _sheet) +
				get_cell_state(x - 1, y - 1, _sheet)
				);
		}
		else
		{//center
			sum_current = (
				get_cell_state(x - 1, y, _sheet) +
				get_cell_state(x + 1, y, _sheet) +
				get_cell_state(x - 1, y - 1, _sheet) +
				get_cell_state(x, y - 1, _sheet) +
				get_cell_state(x + 1, y - 1, _sheet)
				);
		}
	}
	else
	{//center
		if (x < 1)
		{//left
			sum_current = (
				get_cell_state(x, y + 1, _sheet) +
				get_cell_state(x, y - 1, _sheet) +
				get_cell_state(x + 1, y - 1, _sheet) +
				get_cell_state(x + 1, y, _sheet) +
				get_cell_state(x + 1, y + 1, _sheet)
				);
		}
		else if (x > W - 2)
		{//right
			sum_current = (
				get_cell_state(x, y + 1, _sheet) +
				get_cell_state(x, y - 1, _sheet) +
				get_cell_state(x - 1, y - 1, _sheet) +
				get_cell_state(x - 1, y, _sheet) +
				get_cell_state(x - 1, y + 1, _sheet)
				);
		}
		else
		{//center
			sum_current = (
				get_cell_state(x, y + 1, _sheet) +
				get_cell_state(x, y - 1, _sheet) +
				get_cell_state(x - 1, y - 1, _sheet) +
				get_cell_state(x - 1, y, _sheet) +
				get_cell_state(x - 1, y + 1, _sheet) +
				get_cell_state(x + 1, y - 1, _sheet) +
				get_cell_state(x + 1, y, _sheet) +
				get_cell_state(x + 1, y + 1, _sheet)
				);
		}
	}
	if ((*_sheet).IsMember(_i) == 0)
	{
		if (sum_current == 3)
		{
			return 1;
		}
		return 0;
	}
	else if ((*_sheet).IsMember(_i) == 1)
	{
		//printf("%d, %d, %d\n", _i - (_i / W) * W,
		//	(_i - this->w) - ((_i - this->w) / this->w) * this->w, y);
		if (sum_current == 3 || sum_current == 2)
		{
			return 1;
		}
		return 0;
	}

}
void apply_next_generation(TSet * _sheet, TSet * _next_sheet)
{
	for (int i = 0; i < H * W; i++)
	{
		if (get_cell_state_in_next_generation(i, _sheet) == 0)
			(*_next_sheet).DelElem(i);
		else if (get_cell_state_in_next_generation(i, _sheet) == 1)
			(*_next_sheet).InsElem(i);
	}
	for (int i = 0; i < H * W; i++)
	{
		if ((*_next_sheet).IsMember(i))
			(*_sheet).InsElem(i);
		else
			(*_sheet).DelElem(i);
	}
}
void clear(TSet * _sheet, TSet * _next_sheet)
{
	for (int i = 0; i < H * W; i++)
	{
		(*_sheet).DelElem(i);
		(*_next_sheet).DelElem(i);
	}
}

int input_reaction(int _in, TSet * _sheet, TSet * _next_sheet)
{
	int out = 1;
	if (_in == 32) //space
		apply_next_generation(_sheet, _next_sheet);
	else if (_in == 97)
		out = 2; //left
	else if (_in == 115)
		out = 3; //down
	else if (_in == 100)
		out = 4; //right
	else if (_in == 119)
		out = 5; //up
	else if (_in == 120)
		out = 6; //x
	else if (_in == 101)
		out = 0; //e
	return out;
}
int main()
{
	int state = 0, in = 0, cursor = 0;
	cout << "Enter width of area (<40):\n";
	cin >> in;
	if (in > 39)
		W = 40;
	else
		W = in;
	cout << "Enter height of area (<30):\n";
	cin >> in;
	if (in > 29)
		H = 30;
	else
		H = in;
	TSet * sheet = new TSet(W * H);
	TSet * next_sheet = new TSet(W * H);
	cout << "Done. Press space to start game\n";
	cout << "(Use wasd to move, x to create/kill cell, space to live, e to exit)";
	while (getch() != 32) {}
	system("cls");
	/*
	in = getch();
	cout << in;
	in = getch();
	in = 0;
	*/
	draw_cells(cursor, sheet);
	while (1)
	{
		in = getch();
		state = input_reaction(in, sheet, next_sheet);
		system("cls");
		if (state == 1)
		{
			draw_cells(cursor, sheet);
		}
		else if (state == 2)
		{
			if ((cursor % W) > 0)
				cursor--;
			draw_cells(cursor, sheet);
		}
		else if (state == 3)
		{
			if ((cursor / W) < H)
				cursor += W;
			draw_cells(cursor, sheet);
		}
		else if (state == 4)
		{
			if ((cursor % W) < W)
				cursor++;
			draw_cells(cursor, sheet);
		}
		else if (state == 5)
		{
			if ((cursor / W) > 0)
				cursor -= W;
			draw_cells(cursor, sheet);
		}
		else if (state == 6)
		{
			if ((*sheet).IsMember(cursor))
				(*sheet).DelElem(cursor);
			else
				(*sheet).InsElem(cursor);
			draw_cells(cursor, sheet);
		}
		else
			break;
	}
	return 0;
}