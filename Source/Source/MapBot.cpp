#include "MapBot.h"
#pragma warning(disable:4996)

MapBot::MapBot()
{
	this->nStep = -1;
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
		int nLine = 0;
		fscanf(fp, "%d", &nLine);
		fscanf(fp, "%d", &this->startPos.x);
		fscanf(fp, "%d", &this->startPos.y);
		fscanf(fp, "%d", &this->goalPos.x);
		fscanf(fp, "%d", &this->goalPos.y);

		this->map.resize(nLine, vector<int>(nLine));	//Create 2D map
		
		for (int x = 0; x < nLine; x++)
		{
			for (int y = 0; y < nLine; y++)
			{
				fscanf(fp, "%d", &map[x][y]);
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

void MapBot::PrintResult()
{

}

void MapBot::FindPath()
{

}
