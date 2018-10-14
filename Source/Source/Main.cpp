//Project main file
#include "MapBot.h"

int main(int argc, char* argv[])
{
	if (argc != 3)
		return 0;

	MapBot mb;
	//mb.ReadMap("D:\\Projects\\Uni\\Year 5\\AI\\DoAn1\\Uni_2018_AI_PROJECT1\\Source\\Debug\\test.txt");
	//mb.PrintResult("D:\\Projects\\Uni\\Year 5\\AI\\DoAn1\\Uni_2018_AI_PROJECT1\\Source\\Debug\\out.txt");

	mb.ReadMap(argv[1]);
	mb.PrintResult(argv[2]);

	return 1;
}