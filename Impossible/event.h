#pragma once
#include "vector2D.h"
#include "color.h"

enum EventType{EVENT_NONE, EVENT_EXPLOSION, EVENT_OBJECTDESTROYED, EVENT_COLORCHANGE, EVENT_FREEZEALL
  , EVENT_DELETEGAMEOBJECTS, EVENT_GAMEOVER, EVENT_ENABLEROCKETMODE, EVENT_DISABLEROCKETMODE
  , EVENT_ENABLEJUMPMODE, EVENT_DISABLEJUMPMODE };

class GameObject;

struct Event
{
	GameObject* pSource;
	EventType type;
	Vector2D position;
	float data1;
	float data2;
  color newTargetColor;
  int newPulseRate;
};