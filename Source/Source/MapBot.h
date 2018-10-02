#pragma once
#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;

struct vec2
{
	int x;
	int y;
};

class MapBot
{
	int nStep;
	vec2 startPos;
	vec2 goalPos;
	vector<vector<int>> map;
	vector<vec2> path;

public:
	MapBot();
	~MapBot();

	int ReadMap(char inputFile[]);
	void PrintResult();
	void FindPath();
};
