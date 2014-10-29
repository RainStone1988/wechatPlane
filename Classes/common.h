
#ifndef __H_COMMON_H_
#define __H_COMMON_H_

#include <time.h>
#include <stdlib.h>

static int getRandom(int min, int max)
{
	static bool bInit = false;
	if (!bInit)
	{
		srand((unsigned int)(time(NULL)));
		bInit = true;
	}

	int range = max - min + 1;
	return (rand()%range) + min;
}

#endif // __H_COMMON_H_