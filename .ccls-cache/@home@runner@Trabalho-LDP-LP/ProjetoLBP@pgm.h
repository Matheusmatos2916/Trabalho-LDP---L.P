#ifndef __PGM_H_
#define __PGM_H_

#include <stdio.h>
#include <stdlib.h>

struct pgm{
	int tipo;
	int c;
	int r;
	int mv;
	unsigned char *pData;
};

#endif // __LISTA05_H_