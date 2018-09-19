#include "tset.h"
#include <iostream>
const int W = 10, H = 10;
void show(TSet& _field)
{
  for (int i = 0; i < H; i++)
  {
    for (int j = 0; j < W; j++)
      cout << _field.IsMember(i * W + j);
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
  for (int i = 1; i < H - 1; i++)
  {
    for (int j = 1; j < W - 1; j++)
    {
      for (int s = 0; s < 9; s++)
      {
        if (_field.IsMember(((i - 1) * W) + (j - 1)))
          sum++;
        if (_field.IsMember(((i - 1) * W) + (j)))
          sum++;
        if (_field.IsMember(((i - 1) * W) + (j + 1)))
          sum++;
        if (_field.IsMember((i * W) + (j - 1)))
          sum++;
        if (_field.IsMember((i * W) + (j + 1)))
          sum++;
        if (_field.IsMember(((i + 1) * W) + (j - 1)))
          sum++;
        if (_field.IsMember(((i + 1) * W) + (j)))
          sum++;
        if (_field.IsMember(((i + 1) * W) + (j + 1)))
          sum++;
      }
      if (sum > 3)
        kill(_field, i, j);
      if (sum == 2)
        spawn(_field, i, j);
    }
  }
}
int main()
{
  int width = 10, height = 10;
  TSet field(height * width);
  spawn(field, 4, 4);
  spawn(field, 4, 5);
  spawn(field, 5, 4);
  spawn(field, 5, 5);
  show(field);
  next_generation(field);
  show(field);
  return 0;
}