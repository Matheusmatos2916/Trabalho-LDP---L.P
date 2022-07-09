#ifndef __HEADER_H_
#define __HEADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void filtrolbp(struct pgm *img, struct pgm *fil);
void histogram(unsigned char *m, int l, int c, unsigned char *hist);
void readPGMImage(struct pgm *pio, char *filename);
void writePGMImage(struct pgm *pio, char *filename);
void viewPGMImage(struct pgm *pio);
void gravarEmCSV(const unsigned char *const , char *const);
#endif // __LISTA05_H_