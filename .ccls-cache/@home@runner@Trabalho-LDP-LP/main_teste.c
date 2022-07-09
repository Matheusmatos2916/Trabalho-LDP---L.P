/*#include <math.h>
#include <stdio.h>
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

void filtrolbp(struct pgm *, struct pgm *);

void histogram(unsigned char *m, int l, int c, unsigned char *hist) {
  for (int i = 0; i < l * c; i++) {
    *(hist + *(m + i)) += 1;
  }
}

void histogramaPGM(char *arquivo, struct pgm *img) {
  FILE *fp;
  fp = (fopen("Histograma.csv", "a"));
  if (fp == NULL) {
    printf("Erro");
    exit(1);
    
  }

  unsigned char *hist;
  hist = (unsigned char *)calloc((img->mv) + 1, sizeof(unsigned char));
  for (int i = 0; i < img->r * img->c; i++) {
    *(hist + *(img->pData + i)) += 1;
  }

  fseek(fp, 0, SEEK_END);
  for (int k = 0; k <= img->mv; k++) {
    fprintf(fp, "%d,", *(hist + k));
  }
  fprintf(fp, "%c\n", arquivo[0]);
  fclose(fp);
}

int main() {

  struct pgm img, fil;
  // char entrada[20] = "img03_ORIGINAL.pgm";
  // char entrada[30] = "0_10300_Colon TMA.pgm";
  char entrada[30] = "pgm/img.p";
  char saida[30] = "histogramas/saida.pgm";

  readPGMImage(&img, entrada);

  writePGMImage(&img, saida);

  viewPGMImage(&img);

  // Função Filtrar
  filtrolbp(&img, &fil);

  printf("\nFiltro 01:\n");

  viewPGMImage(&fil);

  // Criar histograma
  unsigned char *vetor;
  vetor = calloc(256, sizeof(unsigned char));
  histogram(fil.pData, img.r, img.c, vetor);

  printf("\n\nHistograma 01:\n");
  for (int k = 0; k < 256; k++) {
    printf("%d,", *(vetor + k));
  }
  printf("%c\n", entrada[0]);

  //histogramaPGM(entrada, &fil);

  return 0;
}

void filtrolbp(struct pgm *img, struct pgm *fil) {
  // Filtro LBP. Janela de 8 bits. Método Comparativo
  // Prenchimento da estrutura
  fil->tipo = 5;
  fil->r = img->r;
  fil->c = img->c;
  fil->mv = 255;
  fil->pData = (unsigned char *)malloc(fil->r * fil->c * sizeof(unsigned char));

  // Execução do filtro LBP
  int l = fil->r, c = fil->c;  // linhas e colunas
  unsigned char soma, bjanela; // soma dos bits das janelas e bit da janela
  int j, k, sent, pos; // j = posição linha, k = posição coluna, sent = sentido
                       // de rotação, pos = posição do bit na janela

  for (int i = 0; i < l * c; i++) { // i = posição ponteiro inicial
    soma = 0, j = -1, k = -1, sent = 1, pos = 0;
    do {
      bjanela = 0; // Valor da janela de filtro, 0 para fora da matriz

      if (i < c && j == -1) {                 // superior
      } else if (!(i % c) && k == -1) {       // esquerdo
      } else if (i > (l * c) - c && j == 1) { // inferior
      } else if (!((i + 1) % c) && k == 1) {  // direito
      } else
        bjanela = *(img->pData + i + k + j * c);

      if (bjanela >= *(img->pData + i)) { // metodo comparativo
        soma += pow(2, pos);
      }
      pos++;

      switch (sent) { // J e K desloca a janela, sent Muda o Sentido da janela
      case 1:
        k++;
        if (k == 1)
          sent++;
        break;
      case 2:
        j++;
        if (j == 1)
          sent++;
        break;
      case 3:
        k--;
        if (k == -1)
          sent++;
        break;
      case 4:
        j--;
        if (j == -1)
          sent++;
        break;
      }
    } while (sent <= 4);
    *(fil->pData + i) = soma; // Recebe a soma dos bits no ponteiro de saída
  }
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
}*/