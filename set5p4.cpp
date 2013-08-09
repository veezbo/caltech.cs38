#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <cmath>

#define PI 3.14159

#define mod2(a, m) (a)&((m)-1)
#define eNy(N, y) cos((y)*2.*PI/(N))

double F(int L);
double fL(int L, long y);
long powMod(long inv, int power, long mod);

//PRECALCULATED VALUES

	//powers of 2, by index
long pow2L[31]  = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824};
	
	//3^(-1) mod 2^k calculated with extended euclidean algorithm
	//alternatively, this sequence on OEIS details the values (though it's not quite the exact sequence):
		//http://oeis.org/A007583
long inv2L3[31] = {0, 1, 3, 3, 11, 11, 43, 43, 171, 171, 683, 683, 2731, 2731, 10923, 10923, 43691, 43691, 174763, 174763, 699051, 699051, 2796203, 2796203, 11184811, 11184811, 44739243, 44739243, 178956971, 178956971};


double diffclock(clock_t clock1,clock_t clock2)
{
    double diffticks=clock1-clock2;
    double diffms=(diffticks)/(CLOCKS_PER_SEC/1000);
    return diffms;
}

int main (int argc, char* argv[])
{
	clock_t start = clock();

	if (argc != 2)
	{
		std::cout << "Please Enter 1 Integer Command Line Argument" << std::endl;
		return 1;
	}

	int L = atoi(argv[1]);
	for (int i = 1; i <= L; i++)
	{
		std::cout << F(i) << std::endl;
	}

	clock_t end = clock();
	std::cout << "Number of Milliseconds: " << diffclock(end, start) << std::endl;

	return 0;
}

double F(int L)
{
	double maxfL = -1.;
	long pow2 = pow2L[L];
	for (long y = 1; y < pow2; y+=2)
	{
		double fl = fL(L, y);
		maxfL = std::max(fl, maxfL);
	}
	return maxfL;
}

long powMod(long inv, int power, long mod)
{
	long val = 1;
	for (int i = 0; i < power; i++)
	{
		val*=inv;
		val=mod2(val,mod);
	}
	return val;
}

double fL(int L, long y)
{
	double sumeNy = 0.;
	long Lpow2 = pow2L[L];

	for(int m = 0; m < L; m++)
	{
		long mpow2 = pow2L[m];
		long arg = (((y * mpow2) % Lpow2) * powMod(inv2L3[L], m, Lpow2)) % Lpow2;		
		sumeNy += eNy(Lpow2, arg);
	}
	return 1./L * sumeNy;
}