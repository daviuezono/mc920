#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// mascara do filtro: qualquer numero impar
#define MASK 7


// estrutura que define a imagem
typedef struct IMG {
  int *pixels;
  int largura;
  int altura;
  int maximo;
} imagem;


/* funcoes auxliares */
void ler_linha(void);
int min(int a, int b);
int max(int a, int b, int max_alt);

/* funcoes do programa */
int ler_imagem(imagem *img);
imagem *aplicar_filtro(imagem *img);
void imprimir_imagem(imagem *img);
void liberar_imagem(imagem *img);


/* funcao principal */
int main() {
  imagem img;
  imagem *img_com_filtro;

  //le a imagem
  if( ! ler_imagem(&img) ) {
    //erro ao ler imagem?
    fprintf(stderr, "Erro ao ler a imagem.\n");
    return 1;
  }
  
//  printf("Imagem Original:\n");
//  imprimir_imagem(&img);
  
  img_com_filtro = aplicar_filtro(&img);
  liberar_imagem(&img);

  imprimir_imagem(img_com_filtro);
  
  liberar_imagem(img_com_filtro);

  return 0;

}


/**
 * funcoes do QuickSort
 */
void swap(int *a, int *b) {
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}
 
int partition(int vec[], int left, int right) {
  int i, j;
  
  i = left;
  for (j = left + 1; j <= right; ++j) {
    if (vec[j] < vec[left]) {
      ++i;
      swap(&vec[i], &vec[j]);
    }
  }
  swap(&vec[left], &vec[i]);
  
  return i;
}
 
void quickSort(int vec[], int left, int right) {
  int r;
  
  if (right > left) {
    r = partition(vec, left, right);
    quickSort(vec, left, r - 1);
    quickSort(vec, r + 1, right);
  }
}



/**
 * funcoes auxiliares
 */

//le uma linha da entrada padrao
void ler_linha() {
  char c;
  while ((c=getchar())!='\n' && c!=EOF);
}


// retorna o minimo entre dois numeros
int min(int a, int b) {
  if (a<b)
    if (a>=0)
      return a;
    else
      return min(a+1, b);
  else if (b>=0)
    return b;
  else
    return min(a, b+1);
}

// retorna o maximo entre dois numeros
int max(int a, int b, int max_alt) {
  if (a>b)
    if (a<max_alt)
      return a;
    else
      return max(a-1, b, max_alt);
  else if (b<max_alt)
    return b;
  else
    return max(a, b-1, max_alt);
}

// funcao auxiliar do qsort
int compara (const void * a, const void * b) {
  return ( *(int*)a - *(int*)b );
}


/**
 * funcoes do programa
 */

//funcao para ler a imagem. Retorna 1 se a imagem foi lida com sucesso; 0 caso contrario
int ler_imagem(imagem *img) {
  char img_tipo[2];
  int retorno;
  int i;
  char c;

  //le o tipo da imagem
  while ( (img_tipo[0] = getchar() ) != EOF ) {
    //tipo da imagem P2 foi lido?
    if (img_tipo[0] == 'P' && (img_tipo[1] = getchar()) == '2')
      break;
    else if (img_tipo[0]=='#') //comentario?
      ler_linha();
  }

  //o tipo da imagem eh P2?
  if(img_tipo[0]!='P' || img_tipo[1]!='2')
    return 0; //tipo da imagem invalido

  //le a largura da imagem
  while ( (retorno = scanf("%d", &img->largura)) != EOF && retorno != 1) {
    if (getchar() == '#') //comentario?
      ler_linha();
  }

  if(img->largura==0) //largura da imagem eh valida?
    return 0; //largura da imagem invalida

  //le a altura da imagem
  while ( (retorno = scanf("%d", &img->altura)) != EOF && retorno != 1) {
    if (getchar() == '#') //comentario?
      ler_linha();
  }

  if(img->altura==0) //altura da imagem eh valida?
    return 0; //altura da imagem invalida

  //profundidade maxima da imagem
  scanf("%d", &img->maximo);

  //aloca memoria para os pixels da imagem
  img->pixels = (int*) malloc(sizeof(int) * img->largura * img->altura);

  for (i = 0; i < (img->altura)*(img->largura); i++) {
    scanf("%d", &img->pixels[i]);
    if (img->pixels[i] > img->maximo)
      return 0;
  }

  return 1;

}


imagem *aplicar_filtro(imagem *img) {
  imagem *img_com_filtro;
  int sup, inf, esq, dir, med;
  int i, j, pos;
  int m, n, t;
  int vet[MASK*MASK];
  int a; // contador generico
  
  img_com_filtro = (imagem *) malloc(sizeof(imagem));
  img_com_filtro->altura = img->altura;
  img_com_filtro->largura = img->largura;
  img_com_filtro->maximo = img->maximo;
  img_com_filtro->pixels = (int *) malloc((img->altura)*(img->largura)*sizeof(int));
  
  for (a=0; a<(img_com_filtro->altura)*(img_com_filtro->largura); a++)
    img_com_filtro->pixels[a] = -1;
  
  for (i=0; i<(img->altura); i++) {
    for (j=0; j<(img->largura); j++) {
      t = 0;

      for (m=(i-MASK/2); m<(i+MASK/2); m++)
        for (n=(j-MASK/2); n<(j+MASK/2); n++)
          if ((m>=0 && m<(img->altura)) && (n>=0 && n<(img->largura)))
            vet[t++] = img->pixels[m*(img->largura)+n];

      quickSort(vet, 0, t-1);
      
      pos = i*(img->largura)+j;
      med = t/2;
      
      if (t%2) // mediana de um numero par de elementos
        img_com_filtro->pixels[pos] = (vet[med-1] + vet[med])/2;
      else // mediana de um numero impar de elementos
        img_com_filtro->pixels[pos] = vet[med];
      
      // limpa o vetor que armazena os elementos da mascara
      for (a=0; a<MASK*MASK; a++)
        vet[a] = 0;
    }
  }
  
  return img_com_filtro;
}



void imprimir_imagem(imagem *img) {
  int i, j;
  
  printf("P2\n");
  printf("# MC202D: LAB06 - FILTRO DA MEDIANA\n");
  printf("%d %d\n", img->largura, img->altura);
  printf("%d\n", img->maximo);
  
  for (i=0; i<(img->altura); i++) {
    for (j=0; j<(img->largura); j++) {
      printf("%d", img->pixels[i*(img->largura)+j] );
      if (j < (img->largura) - 1)
        printf(" ");
    }
    printf("\n");
  }
  
  return;
}

//desaloca a memoria para a imagem
void liberar_imagem(imagem *img) {
  free (img->pixels);
}
