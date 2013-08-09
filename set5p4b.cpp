#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <cmath>

#define PI 3.14159

using namespace std;

int l;

double diffclock(clock_t clock1,clock_t clock2)
{
    double diffticks=clock1-clock2;
    double diffms=(diffticks)/(CLOCKS_PER_SEC/1000);
    return diffms;
}

struct Node {
	double fwy;
	int level;
	double z;
};

double maxLeafVal = -2.;
void maxF(Node parent, int right)
{
	double fvy;
	double z;
	if (right == 0)
	{
		z = (3.*parent.z - floor(3. * parent.z)) / 2.;
	}
	else
	{
		z = (3.*parent.z - floor(3. * parent.z)) / 2. + .5;
	}

	fvy = (cos(2.*PI*z) + parent.fwy*parent.level) / (parent.level + 1.);

	double bound = ((double)parent.level * parent.fwy + (l - parent.level)) / (double)l;
	if (bound <= maxLeafVal)
	{
		return;
	}

	Node current;
	current.fwy = fvy;
	current.level = parent.level + 1;
	current.z = z;

	if (current.level == l)
	{
		if (current.fwy > maxLeafVal)
		{
			maxLeafVal = current.fwy;
		}
		return;
	}

	maxF(current, 0);

	if (bound <= maxLeafVal)
	{
		cout << "second bound" << endl;
		return;
	}

	maxF(current, 1);

}

int main (int argc, char* argv[])
{
	clock_t start = clock();

	if (argc != 2)
	{
		std::cout << "Please Enter 1 Integer Command Line Argument" << std::endl;
		return 1;
	}
	int maxl;
	maxl = atoi(argv[1]);

	Node begin;
	begin.fwy = -1;
	begin.level = 1;
	begin.z = .5;

	for (int i = 1; i <= maxl; i++)
	{
		l = i;
		maxF(begin, 0);
		maxF(begin, 1);

		std::cout << maxLeafVal << std::endl;
		maxLeafVal = -2;
	}

	clock_t end = clock();
	std::cout << "Number of Milliseconds: " << diffclock(end, start) << std::endl;

	return 0;
}