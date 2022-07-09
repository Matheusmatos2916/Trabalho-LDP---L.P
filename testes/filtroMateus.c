/*#include <stdio.h>
#include <stdlib.h>

struct pgm {
  int tipo;
  int c;
  int r;
  int mv;
  unsigned char *pData;
};

void readPGMImage(struct pgm *, char *);
void viewPGMImage(struct pgm *);
void writePGMImage(struct pgm *, char *);
void filtramatriz(unsigned char *, int, int, unsigned char *);

int main() {

  struct pgm img, fil;
  //char entrada[20] = "img02_ORIGINAL.pgm";
  char entrada[20] = "img.p";
  char saida[20] = "saida.pgm";

  readPGMImage(&img, entrada);

  // writePGMImage(&img, saida);

  viewPGMImage(&img);

  // Função Filtrar
  fil.pData = (unsigned char *)malloc(img.r * img.c * sizeof(unsigned char));
  filtramatriz(img.pData, img.r, img.c, fil.pData);
  printf("\nFiltro 01:\n");

  // Print Matriz
  for (int k = 0; k < (img.r * img.c); k++) {
    if (!(k % img.c))
      printf("\n");
    printf("%2hhu ", *(fil.pData + k));
  }

  return 0;
}

// Filtra Matriz Ponteiro
void filtramatriz(unsigned char *m, int l, int c, unsigned char *f) {
  char media;
  // j= pos lin / i=pos col
  for (int i = 0; i < l * c; i++) {
    media = 0;
    if (i >= c && i < (l * c) - c && i % c && (i + 1) % c) {
      for (int j = -1; j <= 1; j++) {
        for (int k = -1; k <= 1; k++) {
          media += *(m + i + k + j * c);
        }
      }
    }
    *(f + i) = media / 9;
  }
}

/*
int main(int argc, char *argv[]) {

  struct pgm img;

  if (argc != 3) {
    printf("Formato: \n\t %s <imagemEntrada.pgm> <imagemSaida.pgm>\n", argv[0]);
    exit(1);
  }

  readPGMImage(&img, argv[1]);

  writePGMImage(&img, argv[2]);

  viewPGMImage(&img);

  return 0;
}

void readPGMImage(struct pgm *pio, char *filename) {

  FILE *fp;
  char ch;

  if (!(fp = fopen(filename, "r"))) {
    perror("Erro.");
    exit(1);
  }

  if ((ch = getc(fp)) != 'P') {
    puts("A imagem fornecida não está no formato pgm");
    exit(2);
  }

  pio->tipo = getc(fp) - 48;

  fseek(fp, 1, SEEK_CUR);

  while ((ch = getc(fp)) == '#') {
    while ((ch = getc(fp)) != '\n')
      ;
  }

  fseek(fp, -1, SEEK_CUR);

  fscanf(fp, "%d %d", &pio->c, &pio->r);
  if (ferror(fp)) {
    perror(NULL);
    exit(3);
  }
  fscanf(fp, "%d", &pio->mv);
  fseek(fp, 1, SEEK_CUR);

  pio->pData = (unsigned char *)malloc(pio->r * pio->c * sizeof(unsigned char));

  switch (pio->tipo) {
  case 2:
    puts("Lendo imagem PGM (dados em texto)");
    for (int k = 0; k < (pio->r * pio->c); k++) {
      fscanf(fp, "%hhu", pio->pData + k);
    }
    break;
  case 5:
    puts("Lendo imagem PGM (dados em binário)");
    fread(pio->pData, sizeof(unsigned char), pio->r * pio->c, fp);
    break;
  default:
    puts("Não está implementado");
  }

  fclose(fp);
}

void writePGMImage(struct pgm *pio, char *filename) {
  FILE *fp;
  char ch;

  if (!(fp = fopen(filename, "wb"))) {
    perror("Erro.");
    exit(1);
  }

  fprintf(fp, "%s\n", "P5");
  fprintf(fp, "%d %d\n", pio->c, pio->r);
  fprintf(fp, "%d\n", 255);

  fwrite(pio->pData, sizeof(unsigned char), pio->c * pio->r, fp);

  fclose(fp);
}

void viewPGMImage(struct pgm *pio) {
  printf("Tipo: %d\n", pio->tipo);
  printf("Dimensões: [%d %d]\n", pio->c, pio->r);
  printf("Max: %d\n", pio->mv);

  for (int k = 0; k < (pio->r * pio->c); k++) {
    if (!(k % pio->c))
      printf("\n");
    printf("%2hhu ", *(pio->pData + k));
  }
  printf("\n");
}
*/