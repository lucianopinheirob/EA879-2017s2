
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "imageprocessing.h"

#include <FreeImage.h>


imagem abrir_imagem(char *nome_do_arquivo) {
  FIBITMAP *bitmapIn;
  int x, y;
  RGBQUAD color;
  imagem I;

  bitmapIn = FreeImage_Load(FIF_JPEG, nome_do_arquivo, 0);

  if (bitmapIn == 0) {
    printf("Erro! Nao achei arquivo - %s\n", nome_do_arquivo);
  } else {
    printf("Arquivo lido corretamente!\n");
   }

  x = FreeImage_GetWidth(bitmapIn);
  y = FreeImage_GetHeight(bitmapIn);

  I.width = x;
  I.height = y;
  I.r = malloc(sizeof(float) * x * y);
  I.g = malloc(sizeof(float) * x * y);
  I.b = malloc(sizeof(float) * x * y);


  float maximo;
  float base = 0.0;

   for (int i=0; i<x; i++) {
     for (int j=0; j <y; j++) {
      int idx;
      FreeImage_GetPixelColor(bitmapIn, i, j, &color);

      idx = i + (j*x);

      I.r[idx] = color.rgbRed;
      I.g[idx] = color.rgbGreen;
      I.b[idx] = color.rgbBlue;
    }
   } 

  return I;

}

void BRILHOMUL (imagem *I, float *multiplicador) {
  float mult = (*multiplicador);
  printf("banana %f\n", mult);

for (int i=0; i<(I->width); i++) {
    for (int j=0; j <(I->height); j++) {
       int idx;

       idx = i + (j*I->width);

       I->r[idx] = I->r[idx]*mult;
       I->g[idx] = I->g[idx]*mult;
       I->b[idx] = I->b[idx]*mult;

       if (I->r[idx]>255){
	 I->r[idx] = 255;
       }
	if (I->g[idx]>255){
	 I->g[idx] = 255;
       }
	if (I->b[idx]>255){
	 I->b[idx] = 255;
       }
    }
  } 
}


void BRILHODIV (imagem *I, float *divisor) {
float div = (*divisor);
printf("terra %f \n", div);
  for (int i=0; i<(I->width); i++) {
    for (int j=0; j <(I->height); j++) {
       int idx;

       idx = i + (j*I->width);

       I->r[idx] = I->r[idx]/div;
       I->g[idx] = I->g[idx]/div;
       I->b[idx] = I->b[idx]/div;

       if (I->r[idx]>255){
	 I->r[idx] = 255;
       }
	if (I->g[idx]>255){
	 I->g[idx] = 255;
       }
	if (I->b[idx]>255){
	 I->b[idx] = 255;
       }
    }
  } 
}


void max (imagem *I){

  float res1;
  float res2;
  float max = 0.0;

  for (int i=0; i<(I->width); i++) {
    for (int j=0; j <(I->height); j++) {
      int idx;

      idx = i + (j*I->width);
      
      res1 = (I->r[idx]) + (I->g[idx]) + (I->b[idx]);
      res2 = (res1);

      if (max < res2){
        max = res2;
      }
    }
  } 
  printf ("%f\n", max);
}


void liberar_imagem(imagem *I) {
  free(I->r);
  free(I->g);
  free(I->b);
}

void salvar_imagem(char *nome_do_arquivo, imagem *I) {
  FIBITMAP *bitmapOut;
  RGBQUAD color;

  printf("Salvando imagem %d por %d...\n", I->width, I->height);
  bitmapOut = FreeImage_Allocate(I->width, I->height, 24, 0, 0, 0);

   for (int i=0; i<I->width; i++) {
     for (int j=0; j<I->height; j++) {
      int idx;

      idx = i + (j*I->width);
      color.rgbRed = I->r[idx];
      color.rgbGreen = I->g[idx];
      color.rgbBlue = I->b[idx];

      FreeImage_SetPixelColor(bitmapOut, i, j, &color);
    }
  }

  FreeImage_Save(FIF_JPEG, bitmapOut, nome_do_arquivo, JPEG_DEFAULT);
}


