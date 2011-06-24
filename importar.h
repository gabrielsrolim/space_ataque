#ifndef _IMPORTAR_H_
  #define _IMPORTAR_H_

typedef struct{
    float x;
    float y;
    float z;
}tPoints;

typedef tPoints tTipoPoint;

typedef struct noPoint{
    tTipoPoint ponto;
    struct noPoint *proximo;
}tNoRegPoints;

typedef tNoRegPoints *tRegPoints;

typedef struct{
    int point1;
    int point2;
    int point3;
    int point4;
    int point5;
}tFaces;

typedef tFaces tTipo;

typedef struct no{
    tTipo face;
    int qtd;
    struct no *proximo;
}tNoRegFaces;

typedef tNoRegFaces *tRegFaces;



extern void CriaRegPoints (tRegPoints *faces);
extern void VaziaRegPoints (tRegPoints faces,int *ret);
extern void TamanhoRegPoints (tRegPoints faces,int *qtd);
extern void DestroiRegPoints (tRegPoints *faces);
extern void InsereRegPoints (tRegPoints *faces,tTipoPoint tipo);
extern void elementoRegPoints (tRegPoints faces,int pos,tTipoPoint *tipo);
extern void CriaRegFaces (tRegFaces *faces);
extern void VaziaRegFaces (tRegFaces faces,int *ret);
extern void TamanhoRegFaces (tRegFaces faces,int *qtd);
extern void DestroiRegFaces (tRegFaces *faces);
extern void InsereRegFaces (tRegFaces *faces,tTipo tipo,int qtd);
extern void elementoRegFaces (tRegFaces faces,int pos,tTipo *tipo,int *qtd);
extern void PegarCoordenadas3(FILE *file,char *mystring,tRegPoints *points);
extern void PegarCoordIndex(FILE *file,char *mystring,tRegFaces *faces);
extern void importarBlenderWrl(char *nomeArq,tRegFaces *faces,tRegPoints *points);
extern void Imprimir(tRegFaces faces,tRegPoints points);


#include "importar.c"

#endif
