#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "importar.h"

void CriaRegPoints (tRegPoints *faces) {
    *faces = NULL;
}

void VaziaRegPoints (tRegPoints faces,int *ret) {
    if(faces == NULL){
        *ret=1;    
    }else{
        *ret=0;
    }
}

void TamanhoRegPoints (tRegPoints faces,int *qtd) {
    tRegPoints p = faces;
    int qtde = 0;
    while(p != NULL){
      p = p -> proximo;
      qtde++;
    }
    *qtd = qtde;
}


void DestroiRegPoints (tRegPoints *faces){
 tRegPoints pfaces;

  while (*faces != NULL) {
    pfaces = *faces;
    *faces = (*faces)->proximo;
    free(pfaces);
    } // while 

  *faces = NULL;
}




void InsereRegPoints (tRegPoints *faces,tTipoPoint tipo)
{

    tRegPoints p, novo;
    int  n,parar=0;
    // inserção em lista vazia
    if (*faces == NULL) {
      novo =  malloc(sizeof(tNoRegPoints));
      if (novo == NULL){
         printf("Erro\n");
         parar=1; // erro: memória insuf.
      }else{

      novo -> ponto=tipo;
      *faces = novo;
      novo->proximo=NULL;

      parar=1;
      }
  }else{
  // inserção após primeira posição em lista não vazia
  p = *faces;
  while (p->proximo != NULL){
    p = p -> proximo;
  }
  novo = malloc(sizeof(tNoRegPoints));
  if (novo == NULL){
     printf("Erro\n");
     parar=1; // erro: memória insuficiente
  }else{
      novo -> ponto=tipo;
      novo->proximo = p->proximo;
      p -> proximo = novo;
  }
  }
  parar=1;

} // fim da função insere

void elementoRegPoints (tRegPoints faces,int pos,tTipoPoint *tipo)
{

    tRegPoints p = faces;
    int n = 1,parar=0;
    if ( faces == NULL){
     printf("Erro\n");
     parar =1;  //erro: lista vazia
    }
    while ((p != NULL) && (n < pos) && parar==0){
      p = p -> proximo;
      n++;
    }
    if ( p == NULL){
     printf("erro: posição inválida\n");
     parar=1;  //erro: posição inválida
    }else{
        *tipo = p -> ponto;
    }
    parar=1;
}






void CriaRegFaces (tRegFaces *faces) {
    *faces = NULL;
}

void VaziaRegFaces (tRegFaces faces,int *ret) {
    if(faces == NULL){
       *ret =1;     
    }else{
        *ret =0;
    }
}

void TamanhoRegFaces (tRegFaces faces,int *qtd) {
    tRegFaces p = faces;
    int qtde = 0;
    while(p != NULL){
      p = p -> proximo;
      qtde++;
    }
    *qtd = qtde;
}


void DestroiRegFaces (tRegFaces *faces){
 tRegFaces pfaces;

  while (*faces != NULL) {
    pfaces = *faces;
    *faces = (*faces)->proximo;
    free(pfaces);
    } // while 

  *faces = NULL;
}




void InsereRegFaces (tRegFaces *faces,tTipo tipo,int qtd)
{

    tRegFaces p, novo;
    int  n,parar=0;
    // inserção em lista vazia
    if (*faces == NULL) {
      novo =  malloc(sizeof(tNoRegFaces));
      if (novo == NULL){
         printf("Erro\n");
         parar=1; // erro: memória insuf.
      }else{
      novo -> face=tipo;
      novo -> qtd = qtd;
      *faces = novo;
      novo->proximo=NULL;
      }
      parar=1;
  }else{
  // inserção após primeira posição em lista não vazia
  p = *faces;
  while (p->proximo != NULL){
    p = p -> proximo;
  }
  novo = malloc(sizeof(tNoRegFaces));
  if (novo == NULL){
    printf("Erro\n"); 
    parar=1; // erro: memória insuficiente
  }else{
      novo -> face=tipo;
      novo -> qtd = qtd;
      novo->proximo = p->proximo;
      p -> proximo = novo;
  } 
  parar=1;
  }
} // fim da função insere

void elementoRegFaces (tRegFaces faces,int pos,tTipo *tipo,int *qtd)
{

    tRegFaces p = faces;
    int n = 1,parar=0;
    if ( faces == NULL) parar=1;  //erro: lista vazia
    while ((p != NULL) && (n < pos) && parar==0){
      p = p -> proximo;
      n++;
    }
    if ( p == NULL || parar==1){
     printf("Erro posição inválida\n");
     parar=1;  //erro: posição inválida
    }else{
    *tipo = p -> face;
    *qtd = p-> qtd;
    }
    parar=1;
}

void PegarCoordenadas3(FILE *file,char *mystring,tRegPoints *points){
    float p1,p2,p3;
    int i,d;
    char *aux;
    tTipoPoint tipo;
    
    do{
       fgets(mystring , 10000 , file);
        aux = mystring;       
        while(*aux=='\t'||*aux==' '){
            aux++;
        }
      if(memcmp(aux,"]",1)==0 ){ //|| memcmp(aux,"}",1)==0
        break;
      }    
      d=sscanf(aux,"%f %f %f",&tipo.x,&tipo.y,&tipo.z);
      //printf("pontos: %f %f %f\n",tipo.x,tipo.y,tipo.z);
      InsereRegPoints(points,tipo);  
      
    }while(1);
    
}

void PegarCoordIndex(FILE *file,char *mystring,tRegFaces *faces){
    int c1,c2,c3,c4,c5;
    int i,d;
    char *aux;
    tTipo tipo;
    
    do{
       fgets(mystring , 10000 , file);
        aux = mystring;       
        while(*aux=='\t'||*aux==' '){
            aux++;
        }
      if(memcmp(aux,"]",1)==0){
        break;
      }    
      d=sscanf(aux,"%d %d %d %d %d",&tipo.point1,&tipo.point2,&tipo.point3,&tipo.point4,&tipo.point5);
     // printf("faces: %d %d %d %d %d\n",tipo.point1,tipo.point2,tipo.point3,tipo.point4,tipo.point5);
      InsereRegFaces(faces,tipo,(d-1)); 
      
    }while(1);
    
}



void importarBlenderWrl(char *nomeArq,tRegFaces *faces,tRegPoints *points){

    FILE *file;
    int numero;
    char mystring [10000],*aux;
    

   
            
    
    CriaRegFaces(faces);
    CriaRegPoints(points);
    

    file= fopen(nomeArq,"r");
    if(!file){
        printf("Arquivo nao aberto\n");
        //return 0;
    }
    
    for(;!feof(file);){
       
        fgets(mystring , 10000 , file);
        mystring[strlen(mystring)-1]='\0';
        aux=mystring;
        //printf("%s\n",mystring);   
        while(*aux=='\t' || *aux==' '){
            aux++;
        }
        if(memcmp(aux,"Coordinate",10)==0){
            //numero=atoi(aux+10);    
        }
        //printf("point: %s\n",aux);
        if(memcmp(aux,"point",5)==0){
           // if(numero == 3)
            PegarCoordenadas3(file,mystring,points);
            
        }
        //printf("face: %s\n",aux);
        if(memcmp(aux,"coordIndex",10)==0){
            PegarCoordIndex(file,mystring,faces);
        }
       
    }
    printf("importado\n");
    Imprimir(*faces,*points);

}

void Imprimir(tRegFaces faces,tRegPoints points){
   int i,qtd_f,qtd;
   tTipoPoint tipo2;
   Point3D p1,p2,p3;
   tTipo tipo;
   Point3D n;

    TamanhoRegFaces(faces,&qtd_f);
    //printf("tamanho faces: %d\n",qtd);
    
    //glBegin(GL_LINES);
        for(i=0;i<qtd_f;i++){
            elementoRegFaces (faces,i+1,&tipo,&qtd);
            
            switch (qtd){
        
            case 4:
               // printf("errado\n");
                glBegin(GL_QUADS);
                    //normal ponto 1
                    elementoRegPoints (points,tipo.point1+1,&tipo2);
                    p1.x= tipo2.x;
                    p1.y = tipo2.y;
                    p1.z = tipo2.z;
                    elementoRegPoints (points,tipo.point2+1,&tipo2);
                    p2.x= tipo2.x;
                    p2.y = tipo2.y;
                    p2.z = tipo2.z;
                    elementoRegPoints (points,tipo.point3+1,&tipo2);
                    p3.x= tipo2.x;
                    p3.y = tipo2.y;
                    p3.z = tipo2.z;
                        
                    NormalTriangulo(p1, p2, p3, &n);
                    
                    glNormal3f(n.x, n.y, n.z); 
                    //*/
                    elementoRegPoints (points,tipo.point1+1,&tipo2);
                    glVertex3d(tipo2.x,tipo2.y,tipo2.z);
                   
                  
                    elementoRegPoints (points,tipo.point2+1,&tipo2);
                    glVertex3d(tipo2.x,tipo2.y,tipo2.z);

                    elementoRegPoints (points,tipo.point3+1,&tipo2);
                    glVertex3d(tipo2.x,tipo2.y,tipo2.z);

                    elementoRegPoints (points,tipo.point4+1,&tipo2);
                    glVertex3d(tipo2.x,tipo2.y,tipo2.z);

                glEnd();
                 
                break;
            case 3:
                printf("certo\n");
                elementoRegPoints (points,tipo.point1+1,&tipo2);
                Point3D p1={tipo2.x,tipo2.y,tipo2.z};
                elementoRegPoints (points,tipo.point2+1,&tipo2);
                Point3D p2={tipo2.x,tipo2.y,tipo2.z};
                elementoRegPoints (points,tipo.point3+1,&tipo2);
                Point3D p3={tipo2.x,tipo2.y,tipo2.z};    
                NormalTriangulo(p1, p2, p3, &n);

  
                glBegin(GL_TRIANGLES);
                    glNormal3f(n.x, n.y, n.z);
                    elementoRegPoints (points,tipo.point1+1,&tipo2);
                    glVertex3d(tipo2.x,tipo2.y,tipo2.z);
                    

                    elementoRegPoints (points,tipo.point2+1,&tipo2);
                    glVertex3d(tipo2.x,tipo2.y,tipo2.z);
                  
                    elementoRegPoints (points,tipo.point3+1,&tipo2);
                    glVertex3d(tipo2.x,tipo2.y,tipo2.z);
                    
                glEnd();
                break;
                    
        
            }
        
      
            
        }//for        



    //glEnd();

}


void NormalTriangulo(Point3D p1, Point3D p2, Point3D p3, Point3D *n){
    Point3D v1, v2;
    double len;

    /* Encontra vetor v1 */
    v1.x = p2.x - p1.x;
    v1.y = p2.y - p1.y;
    v1.z = p2.z - p1.z;

    /* Encontra vetor v2 */
    v2.x = p3.x - p1.x;
    v2.y = p3.y - p1.y;
    v2.z = p3.z - p1.z;

    /* Calculo do produto vetorial de v1 e v2 */
    n->x = (v1.y * v2.z) - (v1.z * v2.y);
    n->y = (v1.z * v2.x) - (v1.x * v2.z);
    n->z = (v1.x * v2.y) - (v1.y * v2.x);

    /* normalizacao de n */
    len = sqrt(n->x*n->x + n->y*n->y + n->z*n->z);
    n->x /= len;
    n->y /= len;
    n->z /= len;
}

int InitEsferas(tEsfera *esfera){
    int i=0,num_esfera=0;
    
    
    //Esferas devastadoras linha 1
   for(i=0;i<QTD_LINHA_ESFERA;i++,num_esfera++){
     esfera[num_esfera].x = LINHA_CIMA_ESFERA-((DIST_X_ESFERA*i)+1);
     esfera[num_esfera].y = LINHA_CIMA_ESFERA;
     esfera[num_esfera].z = 0;
     esfera[num_esfera].status  = DISPONIVEL;
   }
   
   //Esferas devastadoras linha 2
   for(i=0;i<QTD_LINHA_ESFERA;i++,num_esfera++){
     esfera[num_esfera].x = LINHA_CIMA_ESFERA-((DIST_X_ESFERA*i)+1);
     esfera[num_esfera].y = LINHA_CIMA_ESFERA-(DIST_Y_ESFERA);
     esfera[num_esfera].z = 0;
     esfera[num_esfera].status  = DISPONIVEL;

   }

    //Esferas devastadoras linha 3
   for(i=0;i<QTD_LINHA_ESFERA;i++,num_esfera++){
     esfera[num_esfera].x = LINHA_CIMA_ESFERA-((DIST_X_ESFERA*i)+1);
     esfera[num_esfera].y = LINHA_CIMA_ESFERA-(DIST_Y_ESFERA*2);
     esfera[num_esfera].z = 0;
     esfera[num_esfera].status  = DISPONIVEL;
   }
   
   //Esferas devastadoras linha 4
   for(i=0;i<QTD_LINHA_ESFERA;i++,num_esfera++){
     esfera[num_esfera].x = LINHA_CIMA_ESFERA-((DIST_X_ESFERA*i)+1);
     esfera[num_esfera].y = LINHA_CIMA_ESFERA-(DIST_Y_ESFERA*3);
     esfera[num_esfera].z = 0;
     esfera[num_esfera].status  = DISPONIVEL;
   }


   


}




