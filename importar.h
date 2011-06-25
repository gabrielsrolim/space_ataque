#ifndef _IMPORTAR_H_
  #define _IMPORTAR_H_

//#include <time.h>

/*Defines para Esfera*/
#define LINHA_CIMA_ESFERA 18.5
#define QTD_LINHA_ESFERA 13
#define DISPONIVEL 1
#define DESTRUIDO 0
#define DIST_X_ESFERA 3
#define DIST_Y_ESFERA 3
#define QTD_ESFERAS  52

#define FIM_JOGO 65

#define VELOCIDADE_DELC_AVIAO 0.5
#define VELOCIDADE_MISSEL 0.5
#define VELOCIDADE_DESC_ESFERA 1.0

#define PERDE_VIDA 0.3

/*Defines para os misseis*/
#define M_ESFERA    1
#define M_NAVE      0

//calcular normais
typedef struct p3d{
    double x, y, z;
}Point3D;

//tipo esfera: util para saber se houve colisao, alterando status.
typedef struct esfera{
        double x , y ,z ;
        int status;
        }tEsfera;

//tipo esfera: util para saber se houve colisao, alterando status.
typedef struct missel{
        double translacao_x;
        double translacao_y;
        }tPosicao;


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
extern void NormalTriangulo(Point3D p1, Point3D p2, Point3D p3, Point3D *n);
extern int InitEsferas(tEsfera *esfera);
extern void Desenha();
extern void desenha_aviao();
extern void Esferas();
extern void misseis();
extern void barravida();
extern void chances();
extern void RecomecaJogo();


#include "importar.c"

#endif
