#pragma once
#include <iostream>
#include <cstdio>
#include <vector>
#include <stdio.h>
using namespace std;

struct vec2
{
	int x;
	int y;

	vec2() {};
	~vec2() {};

	vec2(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	inline void operator=(vec2 v)
	{
		x = v.x;
		y = v.y;
	}

	inline bool operator==(vec2 v2)
	{
		if (x == v2.x && y == v2.y)
			return true;
		else
			return false;
	}

	inline bool operator!=(vec2 v2)
	{
		if (x != v2.x || y != v2.y)
			return true;
		else
			return false;
	}
};

struct Node
{
	int type;			//Path(0) or object(1)
	vec2 pos;			//Node coordinates in map
	int f;				//Node value f = g + h
	int g;				//Distance from start node to current node
	int h;				//(heurisic) Euclid distance from current node to goal node
	int mark;			//0: in Open , 1: in Close , 2: neither in Open nor Close , 3: path from S to G
	vec2 prevNode;		//
};

class MapBot
{
	int mapSize;
	vec2 startPos;
	vec2 goalPos;
	vector<vector<Node>> map;
	vector<Node*> openNode;
	vector<Node*> closeNode;
	vector<Node> path;

public:
	MapBot();
	~MapBot();

	int ReadMap(char inputFile[]);
	void PrintResult(char outputFile[]);

	int AStar();
	void FindMinF();
	vector<Node*>::iterator FindNode(vec2 v, vector<Node*> &listNode);
};
