#ifndef __HEADER_H_
#define __HEADER_H_

#include "pgm.h"
#include <dirent.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void filtrolbp(struct pgm *img, struct pgm *fil);
void histogram(unsigned char *m, int l, int c, unsigned char *hist);
void readPGMImage(struct pgm *pio, char *filename);
void writePGMImage(struct pgm *pio, char *filename);
void viewPGMImage(struct pgm *pio);
void gravarEmCSV(const unsigned char *const, char *const);
#endif // __LISTA05_H_