#pragma once
#include "objecttypes.h"

class color
{
public:
  int R;
  int G;
  int B;

  color();
  color(int r, int g, int b);
  color(ColorType colorType);

  unsigned int GetColor();

  bool Blend(color targetColor, int pulseRate);
};

