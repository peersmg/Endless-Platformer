#include "color.h"
#include "mydrawengine.h"

color::color()
{

}

color::color(int r, int g, int b)
{
  R = r;
  G = g;
  B = b;
}

color::color(ColorType colorType)
{
  switch (colorType)
  {
  case WHITE:
    R = 255;
    G = 255;
    B = 255;
    break;
  case BLACK:
    R = 0;
    G = 0;
    B = 0;
    break;
  case RED:
    R = 194;
    G = 0;
    B = 14;
    break;
  case GREEN:
    R = 12;
    G = 134;
    B = 16;
    break;
  case BLUE:
    R = 30;
    G = 53;
    B = 227;
    break;
  case PURPLE:
    R = 130;
    G = 12;
    B = 134;
    break;
  case YELLOW:
    R = 134;
    G = 134;
    B = 12;
    break;
  case ORANGE:
    R = 134;
    G = 95;
    B = 12;
    break;
  case RED_L:
    R = 252;
    G = 66;
    B = 79;
    break;
  case GREEN_L:
    R = 27;
    G = 224;
    B = 40;
    break;
  case BLUE_L:
    R = 84;
    G = 104;
    B = 255;
    break;
  case PURPLE_L:
    R = 217;
    G = 27;
    B = 224;
    break;
  case YELLOW_L:
    R = 217;
    G = 224;
    B = 27;
    break;
  case ORANGE_L:
    R = 224;
    G = 142;
    B = 27;
    break;

  case LIGHTRED:
    R = 245;
    G = 24;
    B = 105;
    break;
  case LIGHTGREEN:
    R = 40;
    G = 179;
    B = 36;
    break;
  case LIGHTBLUE:
    R = 43;
    G = 154;
    B = 214;
    break;
  case LIGHTPURPLE:
    R = 179;
    G = 36;
    B = 140;
    break;
  case LIGHTYELLOW:
    R = 179;
    G = 174;
    B = 36;
    break;
  case LIGHTORANGE:
    R = 179;
    G = 117;
    B = 36;
    break;
  case LIGHTRED_L:
    R = 255;
    G = 89;
    B = 150;
    break;
  case LIGHTGREEN_L:
    R = 61;
    G = 242;
    B = 61;
    break;
  case LIGHTBLUE_L:
    R = 173;
    G = 226;
    B = 255;
    break;
  case LIGHTPURPLE_L:
    R = 221;
    G = 61;
    B = 242;
    break;
  case LIGHTYELLOW_L:
    R = 242;
    G = 221;
    B = 61;
    break;
  case LIGHTORANGE_L:
    R = 242;
    G = 164;
    B = 61;
    break;
  default:
    break;
  }
}

unsigned int color::GetColor()
{
  return _XRGB(R, G, B);
}

bool color::Blend(color targetColor, int pulseRate)
{
  if (GetColor() != targetColor.GetColor())
  {
    if (targetColor.R > R)
    {
      R += pulseRate;
      if (targetColor.R < R)
      {
        R = targetColor.R;
      }
    }
    else if (targetColor.R < R)
    {
      R -= pulseRate;
      if (targetColor.R > R)
      {
        R = targetColor.R;
      }
    }

    if (targetColor.G > G)
    {
      G += pulseRate;
      if (targetColor.G < G)
      {
        G = targetColor.G;
      }
    }
    else if (targetColor.G < G)
    {
      G -= pulseRate;
      if (targetColor.G > G)
      {
        G = targetColor.G;
      }
    }

    if (targetColor.B > B)
    {
      B += pulseRate;
      if (targetColor.B < B)
      {
        B = targetColor.B;
      }
    }
    else if (targetColor.B < B)
    {
      B -= pulseRate;
      if (targetColor.B > B)
      {
        B = targetColor.B;
      }
    }

    return true;
  }
  else
    return false;
}