#include "MapBot.h"
#pragma warning(disable:4996)

MapBot::MapBot()
{
}

MapBot::~MapBot()
{
}

int MapBot::ReadMap(char inputFile[])
{
	FILE *fp;
	fp = fopen(inputFile, "r");

	if (fp != nullptr)
	{
		fscanf(fp, "%d", &mapSize);
		fscanf(fp, "%d", &startPos.x);
		fscanf(fp, "%d", &startPos.y);
		fscanf(fp, "%d", &goalPos.x);
		fscanf(fp, "%d", &goalPos.y);

		map.resize(mapSize, vector<Node>(mapSize));	//Create 2D map

		for (int x = 0; x < mapSize; x++)
		{
			for (int y = 0; y < mapSize; y++)
			{
				fscanf(fp, "%d", &map[x][y].type);
				map[x][y].pos = vec2(x, y);
				map[x][y].mark = 2;
				if (map[x][y].type == 0)
					map[x][y].h = ((goalPos.x - x) * (goalPos.x - x)) + ((goalPos.y - y) * (goalPos.y - y));
			}
		}

		fclose(fp);
	}
	else
	{
		cout << "File not found";
		return 0;
	}
	
}

void MapBot::PrintResult(char outputFile[])
{
	FILE* fp;
	fp = fopen(outputFile, "w");

	if (AStar() == -1)
	{
		fprintf(fp, "-1");
	}
	else
	{
		vector<vec2> result;
		vec2 path = map[goalPos.x][goalPos.y].prevNode;
		while (path != map[startPos.x][startPos.y].pos)
		{
			result.push_back(path);
			map[path.x][path.y].mark = 3;
			path = map[path.x][path.y].prevNode;
		}

		fprintf(fp, "%d \n", result.size() + 2);
		fprintf(fp, "(%d , %d)  ", map[startPos.x][startPos.y].pos.x, map[startPos.x][startPos.y].pos.y);
		for(int i = result.size() - 1; i >=0; i--)
		{
			fprintf(fp, "(%d , %d)  ", result[i].x, result[i].y);
		}
		fprintf(fp, "(%d , %d)\n", map[goalPos.x][goalPos.y].pos.x, map[goalPos.x][goalPos.y].pos.y);
		for (int x = 0; x < mapSize; x++)
		{
			for (int y = 0; y < mapSize; y++)
			{
				if (map[x][y].pos == startPos)
				{
					fprintf(fp, "S ");
					continue;
				}
				if (map[x][y].pos == goalPos)
				{
					fprintf(fp, "G ");
					continue;
				}
				if (map[x][y].mark == 3)
				{
					fprintf(fp, "x ");
					continue;
				}
				if (map[x][y].type == 0)
					fprintf(fp, "- ");
				if (map[x][y].type == 1)
					fprintf(fp, "o ");
			}
			fprintf(fp, "\n");
		}
	}
	fclose(fp);
}

//-------A* algorithm function-------

int MapBot::AStar()
{
	map[startPos.x][startPos.y].g = 0;
	openNode.push_back(&map[startPos.x][startPos.y]);

	while (!openNode.empty())
	{
		FindMinF();
		Node* curNode = openNode.back();
		openNode.pop_back();

		if (curNode->pos == map[goalPos.x][goalPos.y].pos)
		{
			return 1;
		}

		for (int row = curNode->pos.x - 1; row <= curNode->pos.x + 1; row++)
		{
 			for (int col = curNode->pos.y - 1; col <= curNode->pos.y + 1; col++)
			{
				if ((curNode->pos == vec2(row, col)) || col < 0 || row < 0 || col == mapSize || row == mapSize || map[row][col].type == 1)
					continue;
				else
				{
					if (map[row][col].mark == 0)
					{
						if (map[row][col].g < curNode->g + 1)
							continue;
					}
					if (map[row][col].mark == 1)
					{
						if (map[row][col].g < curNode->g + 1)
							continue;
						else
						{
							vector<Node*>::iterator cIt = FindNode(vec2(row, col),closeNode);
							closeNode.erase(cIt);
							map[row][col].mark = 0;
							openNode.push_back(&map[row][col]);
						}
					}
					if (map[row][col].mark == 2)
					{
						map[row][col].mark = 0;
						openNode.push_back(&map[row][col]);
					}
					map[row][col].g = curNode->g + 1;
					map[row][col].f = map[row][col].g + map[row][col].h;
					map[row][col].prevNode = curNode->pos;
				}
			}
		}
		curNode->mark = 1;
		closeNode.push_back(curNode);
	}
	return -1;
}

void MapBot::FindMinF()
{
	//Find node with minimum F and swap it to the end of the list
	if (openNode.size() == 1)
		return;

	int minId = 0;
	int minF = openNode[0]->f;
	for (int i = 1; i < openNode.size(); i++)
	{
		if (minF > openNode[i]->f)
		{
			minId = i;
			minF = openNode[i]->f;
		}
	}

	Node* temp = openNode.back();
	openNode.back() = openNode[minId];
	openNode[minId] = temp;
}

vector<Node*>::iterator MapBot::FindNode(vec2 v, vector<Node*> &listNode)
{
	for (vector<Node*>::iterator it = listNode.begin(); it != listNode.end(); ++it)
	{
		if ((*it)->pos == v)
		{
			return it;
		}
	}
}


