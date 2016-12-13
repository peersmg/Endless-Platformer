#pragma once


// List of object types available in the game
// Add a name for each possible type of entity in your game
// Still using old enums until C++11 is available

enum ObjectType{UNKNOWN, WALL, PLAYER, BLOCK, DESTROY, GM, TEXT //Normal types
                                             , BACKGROUND, UI}; // Special types

enum GameMode{ NORMAL, ROCKET, JUMP };

enum ColorType{ WHITE, BLACK, RED, GREEN, BLUE, PURPLE, YELLOW, ORANGE 
              , RED_L, GREEN_L, BLUE_L, PURPLE_L, YELLOW_L, ORANGE_L
              , LIGHTRED, LIGHTGREEN, LIGHTBLUE, LIGHTPURPLE, LIGHTYELLOW, LIGHTORANGE
              , LIGHTRED_L, LIGHTGREEN_L, LIGHTBLUE_L, LIGHTPURPLE_L, LIGHTYELLOW_L, LIGHTORANGE_L};

enum Alignment{ TOPLEFT, MIDDLELEFT, BOTTOMLEFT, TOPCENTRE, MIDDLECENTRE, BOTTOMCENTRE, TOPRIGHT, MIDDLERIGHT, BOTTOMRIGHT };