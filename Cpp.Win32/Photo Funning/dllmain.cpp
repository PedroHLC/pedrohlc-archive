#include "dll.h"
#include <math.h>
#include <windows.h>
#include <stdint.h>

#define DLL_EXTERN extern "C" __declspec(dllexport)
#define PRRGBA(r, g, b, a) ( ( b & 0xff) | (( g & 0xff) << 8) | (( r & 0xff) << 16) | (( a & 0xff) << 24))
#define PRGetAValue(col) ((col >> 24) & 0xFF)
#define PRGetRValue(col) ((col >> 16) & 0xFF)
#define PRGetGValue(col) ((col >> 8) & 0xFF)
#define PRGetBValue(col) (col & 0xFF)

typedef struct{
  DWORD unk1;
  DWORD unk2;
  BITMAPINFOHEADER *infoheader;
  RGBQUAD *firstRow;
  RGBQUAD *lastRow;
} RGSSBMINFO;

typedef struct{
  DWORD unk1;
  DWORD unk2;
  RGSSBMINFO *bminfo;
} RGSSBMSTRUCT;

typedef struct{
  DWORD flags;
  DWORD klass;
  void (*dmark)(void*);
  void (*dfree)(void*);
  RGSSBMSTRUCT *bm;
} RGSSBITMAP;


int gP(int x, int y, int width){
    return(x - (width * y));
}

DLL_EXTERN int Multiply(long b1id, long b2id){
  // Pega a informação do bitmap
  RGSSBMINFO *bitmap1 = ((RGSSBITMAP*)(b1id << 1))->bm->bminfo;
  RGSSBMINFO *bitmap2 = ((RGSSBITMAP*)(b2id << 1))->bm->bminfo;
  // Pega largura e altura minima
  int width1 = bitmap1->infoheader->biWidth;
  int height1 = bitmap1->infoheader->biHeight;
  int width2 = bitmap2->infoheader->biWidth;
  int height2 = bitmap2->infoheader->biHeight;
  int width = width1;
  int height = height1;
  if(width2 < width) width = width2;
  if(height2 < height) height = height2;
  // Pega o conteudo
  uint32_t *b1row = (uint32_t *)bitmap1->firstRow;
  uint32_t *b2row = (uint32_t *)bitmap2->firstRow;
  // ..
  //row[gP(x, y, width)] = 0xAARRGGBB;
  int pos1, pos2, posR;
  float b1a, b1r, b1g, b1b, b2a, b2r, b2g, b2b, bRa, bRr, bRg, bRb;
  for(int h=0; h < height1; h++) for(int w=0; w < width1; w++) {
     pos1 = gP(w, h, width1);
     if(h < height & w < width){
       pos2 = gP(w, h, width2);
       b1a = (float) PRGetAValue(b1row[pos1]);
       b1r = (float) PRGetRValue(b1row[pos1]);
       b1g = (float) PRGetGValue(b1row[pos1]);
       b1b = (float) PRGetBValue(b1row[pos1]);
       b2a = (float) PRGetAValue(b2row[pos2]);
       b2r = (float) PRGetRValue(b2row[pos2]);
       b2g = (float) PRGetGValue(b2row[pos2]);
       b2b = (float) PRGetBValue(b2row[pos2]);
       bRa = ((b1a /255) * b2a);//(((b1a /255) * (b2a / 255)) * 255);
       bRr = ((b1r /255) * b2r);
       bRg = ((b1g /255) * b2g);
       bRb = ((b1b /255) * b2b);
       b1row[pos1] = PRRGBA((int) bRr, (int) bRg, (int) bRb, (int) bRa);
     }else b1row[pos1] = 0;
  }
  // Retorna
  return(1);
}

DLL_EXTERN int SameSizeMultiply(long b1id, long b2id){
  // Pega a informação do bitmap
  RGSSBMINFO *bitmap1 = ((RGSSBITMAP*)(b1id << 1))->bm->bminfo;
  RGSSBMINFO *bitmap2 = ((RGSSBITMAP*)(b2id << 1))->bm->bminfo;
  // Pega largura e altura minima
  int width = bitmap1->infoheader->biWidth;
  int height = bitmap1->infoheader->biHeight;
  // Pega o conteudo
  uint32_t *b1row = (uint32_t *)bitmap1->lastRow;
  uint32_t *b2row = (uint32_t *)bitmap2->lastRow;
  // ..
  //row[gP(x, y, width)] = 0xAARRGGBB;
  int pos;
  float b1a, b1r, b1g, b1b, b2a, b2r, b2g, b2b, bRa, bRr, bRg, bRb;
  uint32_t *b1, *b2;
  for(pos=0; pos < (height * width); pos++){
     b1a = (float) PRGetAValue(b1row[pos]);
     b1r = (float) PRGetRValue(b1row[pos]);
     b1g = (float) PRGetGValue(b1row[pos]);
     b1b = (float) PRGetBValue(b1row[pos]);
     b2a = (float) PRGetAValue(b2row[pos]);
     b2r = (float) PRGetRValue(b2row[pos]);
     b2g = (float) PRGetGValue(b2row[pos]);
     b2b = (float) PRGetBValue(b2row[pos]);
     bRa = ((b1a /255) * b2a);//(((b1a /255) * (b2a / 255)) * 255);
     bRr = ((b1r /255) * b2r);
     bRg = ((b1g /255) * b2g);
     bRb = ((b1b /255) * b2b);
     b1row[pos] = PRRGBA((int) bRr, (int) bRg, (int) bRb, (int) bRa);
  }
  // Retorna
  return(1);
}

DLL_EXTERN int Invert(long bid){
  // Pega a informação do bitmap
  RGSSBMINFO *bitmap = ((RGSSBITMAP*)(bid << 1))->bm->bminfo;
  int width = bitmap->infoheader->biWidth;
  int height = bitmap->infoheader->biHeight;
  // Pega o conteudo
  uint32_t *row = (uint32_t *)bitmap->lastRow;
  // ..
  //row[gP(x, y, width)] = 0xAARRGGBB;
  int pr, pg, pb, cor, pos;
  for(pos=0; pos < (height * width); pos++){
      pr = (255 - PRGetRValue(row[pos]));
      pg = (255 - PRGetGValue(row[pos]));
      pb = (255 - PRGetBValue(row[pos]));
      row[pos] = PRRGBA(pr, pg, pb, PRGetAValue(row[pos]));
  } 
  // Retorna
  return(1);
}

DLL_EXTERN int Rotate180(long bid){
  // Pega a informação do bitmap
  RGSSBMINFO *bitmap = ((RGSSBITMAP*)(bid << 1))->bm->bminfo;
  int sz = (int)(bitmap->infoheader->biWidth) * (int)(bitmap->infoheader->biHeight);
  // Pega o conteudo
  uint32_t *lrow = (uint32_t*) bitmap->lastRow ,
           *frow = (uint32_t*) bitmap->firstRow ,
           *trow = (uint32_t*) malloc(sz * sizeof(uint32_t) + 1);
  // ..
  int pos;
  for (pos=0; pos < sz; pos++)
      trow[pos] = frow[pos];
  for (pos=0; pos < sz; pos++)
      lrow[pos] = trow[pos];
  // Retorna
  return(1);
}*/

DLL_EXTERN int BlackWhite(long bid){
  // Pega a informação do bitmap
  RGSSBMINFO *bitmap = ((RGSSBITMAP*)(bid << 1))->bm->bminfo;
  int width = bitmap->infoheader->biWidth;
  int height = bitmap->infoheader->biHeight;
  // Pega o conteudo
  uint32_t *row = (uint32_t *)bitmap->lastRow;
  // ..
  //row[gP(x, y, width)] = 0xAARRGGBB;
  int pr, pg, pb, cor, pos;
  for(pos=0; pos < (height * width); pos++){
      pr = PRGetRValue(row[pos]);
      pg = PRGetGValue(row[pos]);
      pb = PRGetBValue(row[pos]);
      cor = (pr * 0.3 +  pg * 0.59 + pb * 0.11);
      row[pos] = PRRGBA(cor, cor, cor, PRGetAValue(row[pos]));
  } 
  // Retorna
  return(1);
}

DLL_EXTERN int BlackWhite_Invert(long bid){
  // Pega a informação do bitmap
  RGSSBMINFO *bitmap = ((RGSSBITMAP*)(bid << 1))->bm->bminfo;
  int width = bitmap->infoheader->biWidth;
  int height = bitmap->infoheader->biHeight;
  // Pega o conteudo
  uint32_t *row = (uint32_t *)bitmap->lastRow;
  // ..
  //row[gP(x, y, width)] = 0xAARRGGBB;
  int pr, pg, pb, cor, pos;
  for(pos=0; pos < (height * width); pos++){
      pr = PRGetRValue(row[pos]);
      pg = PRGetGValue(row[pos]);
      pb = PRGetBValue(row[pos]);
      cor = 255 - (pr * 0.3 +  pg * 0.59 + pb * 0.11);
      row[pos] = PRRGBA(cor, cor, cor, PRGetAValue(row[pos]));
  } 
  // Retorna
  return(1);
}

DLL_EXTERN int ColorDodge(long pbid, long tbid){
  // Pega a informação do bitmap
  RGSSBMINFO *bitmap = ((RGSSBITMAP*)(pbid << 1))->bm->bminfo;
  RGSSBMINFO *tempb = ((RGSSBITMAP*)(tbid << 1))->bm->bminfo;
  int width = bitmap->infoheader->biWidth;
  int height = bitmap->infoheader->biHeight;
  // Pega o conteudo
  uint32_t *row1 = (uint32_t *)bitmap->lastRow;
  uint32_t *row2 = (uint32_t *)tempb->lastRow;
  //Color Dodge + Multiply
  int b1r, b1g, b1b, b2r, b2g, b2b, bBr, bBg, bBb, pos;
  for(pos=0; pos < (height * width); pos++){
      b1r = (float) PRGetRValue(row1[pos]);
      b1g = (float) PRGetGValue(row1[pos]);
      b1b = (float) PRGetBValue(row1[pos]);
      b2r = (float) PRGetRValue(row2[pos]);
      b2g = (float) PRGetGValue(row2[pos]);
      b2b = (float) PRGetBValue(row2[pos]);
      b1r = b2r >= 255? 255 : min(b1r * 255 / (255 - b2r), 255);
      b1g = b2g >= 255? 255 : min(b1g * 255 / (255 - b2g), 255);
      b1b = b2b >= 255? 255 : min(b1b * 255 / (255 - b2b), 255);
      row1[pos] = PRRGBA((int) b1r, (int) b1g, (int) b1b, PRGetAValue(row1[pos]));
  }
  // Retorna
  return(1);
}

long gauss(int x, int y, long sigma){
     long r, xf=(long)x, xy=(long)y;
     r = pow( (1 / 2 * 3.14159265 * (sigma * sigma)), ((x*x)+(y*y) / (2 * (sigma*sigma)) ));
     return(r);
}

/*DLL_EXTERN int GaussianBlur(long bid, int level){
  // Pega a informação do bitmap
  RGSSBMINFO *bitmap = ((RGSSBITMAP*)(bid << 1))->bm->bminfo;
  int width = bitmap->infoheader->biWidth;
  int height = bitmap->infoheader->biHeight;
  // Pega a matrix
  long* matrix;
  for(int iy; iy <= level; iy++) for(int ix; ix <= level; ix++){
    matrix[ix + (iy * (level+1))] = gauss(ix, iy, level);
  }
  // Pega o conteudo
  uint32_t *row = (uint32_t *)bitmap->firstRow;
  uint32_t *rowT;
  //Gaussian Blur
  int pos, w, h, pr, pg, pb;
  for(int x; x < (width / level); x++) for(int y; y < (height / level); y++){
    w = (x * level);
    h = (y * level);
    for(int iy; iy <= level; iy++) for(int ix; ix <= level; ix++){
      pos = gP(w + ix, h + iy, width);
      pr = PRGetRValue(row[pos]) * matrix[x + (y * (level+1))] ;
      pg = PRGetGValue(row[pos]) * matrix[x + (y * (level+1))] ;
      pb = PRGetBValue(row[pos]) * matrix[x + (y * (level+1))] ;
      row[pos] = PRRGBA(pr, pg, pb, PRGetAValue(row[pos]));;
    }
  }
  // Retorna
  return(1);
}*/

DLL_EXTERN int ChromaKeyFilter(long bid, long mid){
  // Pega a informação do bitmap
  RGSSBMINFO *bitmap = ((RGSSBITMAP*)(bid << 1))->bm->bminfo;
  RGSSBMINFO *mask = ((RGSSBITMAP*)(mid << 1))->bm->bminfo;
  // Pega os conteudos
  uint32_t *bitmap_row = (uint32_t *)bitmap->firstRow;
  uint32_t *mask_row = (uint32_t *)mask->firstRow;
  // Pega largura e altura minima
  int width1 = bitmap->infoheader->biWidth;
  int height1 = bitmap->infoheader->biHeight;
  int width2 = mask->infoheader->biWidth;
  int height2 = mask->infoheader->biHeight;
  int width = width1;
  int height = height1;
  if(width2 < width) width = width2;
  if(height2 < height) height = height2;
  // ..
  //row[gP(x, y, width)] = 0xAARRGGBB;
  int pos1, pos2, posR;
  float b1a, b2g, bRa;
  for(int h=0; h < height1; h++) for(int w=0; w < width1; w++) {
     pos1 = gP(w, h, width1);
     if(h < height & w < width){
       pos2 = gP(w, h, width2);
       b1a = (float) PRGetAValue(bitmap_row[pos1]);
       b2g = (float) PRGetGValue(mask_row[pos2]);
       bRa = (b2g >= 127.5 ? b1a : 0);
       bitmap_row[pos1] = PRRGBA(PRGetRValue(bitmap_row[pos2]),
                           PRGetGValue(bitmap_row[pos2]),
                           PRGetBValue(bitmap_row[pos2]),
                           (int) bRa);
     }else bitmap_row[pos1] = 0;
  }
  // Retorna
  return(1);
}

DLL_EXTERN int KeyFilter(long bid, long mid){
  // Pega a informação do bitmap
  RGSSBMINFO *bitmap = ((RGSSBITMAP*)(bid << 1))->bm->bminfo;
  RGSSBMINFO *mask = ((RGSSBITMAP*)(mid << 1))->bm->bminfo;
  // Pega os conteudos
  uint32_t *bitmap_row = (uint32_t *)bitmap->firstRow;
  uint32_t *mask_row = (uint32_t *)mask->firstRow;
  // Pega largura e altura minima
  int width1 = bitmap->infoheader->biWidth;
  int height1 = bitmap->infoheader->biHeight;
  int width2 = mask->infoheader->biWidth;
  int height2 = mask->infoheader->biHeight;
  int width = width1;
  int height = height1;
  if(width2 < width) width = width2;
  if(height2 < height) height = height2;
  // ..
  //row[gP(x, y, width)] = 0xAARRGGBB;
  int pos1, pos2, posR;
  float b1a, b2r, bRa;
  for(int h=0; h < height1; h++) for(int w=0; w < width1; w++) {
     pos1 = gP(w, h, width1);
     if(h < height & w < width){
       pos2 = gP(w, h, width2);
       b1a = (float) PRGetAValue(bitmap_row[pos1]);
       b2r = (float) PRGetRValue(mask_row[pos2]);
       bRa = (b1a - (255 - b2r));
       bitmap_row[pos1] = PRRGBA(PRGetRValue(bitmap_row[pos2]),
                           PRGetGValue(bitmap_row[pos2]),
                           PRGetBValue(bitmap_row[pos2]),
                           (int) bRa);
     }else bitmap_row[pos1] = 0;
  }
  // Retorna
  return(1);
}

DLL_EXTERN int Remover(long bid, long mid){
  // Pega a informação do bitmap
  RGSSBMINFO *bitmap = ((RGSSBITMAP*)(bid << 1))->bm->bminfo;
  RGSSBMINFO *mask = ((RGSSBITMAP*)(mid << 1))->bm->bminfo;
  // Pega os conteudos
  uint32_t *bitmap_row = (uint32_t *)bitmap->firstRow;
  uint32_t *mask_row = (uint32_t *)mask->firstRow;
  // Pega largura e altura minima
  int width1 = bitmap->infoheader->biWidth;
  int height1 = bitmap->infoheader->biHeight;
  int width2 = mask->infoheader->biWidth;
  int height2 = mask->infoheader->biHeight;
  int width = width1;
  int height = height1;
  if(width2 < width) width = width2;
  if(height2 < height) height = height2;
  // ..
  //row[gP(x, y, width)] = 0xAARRGGBB;
  int pos1, pos2, posR;
  float b1a, b2a, bRa;
  for(int h=0; h < height1; h++) for(int w=0; w < width1; w++) {
     pos1 = gP(w, h, width1);
     if(h < height & w < width){
       pos2 = gP(w, h, width2);
       b1a = (float) PRGetAValue(bitmap_row[pos1]);
       b2a = (float) PRGetAValue(mask_row[pos2]);
       bRa = (b2a > 0 ? b1a : 0);
       bitmap_row[pos1] = PRRGBA(PRGetRValue(bitmap_row[pos2]),
                           PRGetGValue(bitmap_row[pos2]),
                           PRGetBValue(bitmap_row[pos2]),
                           (int) bRa);
     }else bitmap_row[pos1] = 0;
  }
  // Retorna
  return(1);
}
