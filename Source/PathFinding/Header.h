#ifndef _HEADER_H_
#define _HEADER_H_

#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <memory>

using namespace std;

#define CELL_W 64
#define CELL_H 64

#define COST_X 14
#define COST_Y 14
#define COST_XY 10

#define GRID_W 24
#define GRID_H 12

#define PLAYER_S 300

#include "Helper.h"
#include "Node.h"
#include "Cursor.h"
#include "Finder.h"
#include "Player.h"
#include "Scene.h"

#endif