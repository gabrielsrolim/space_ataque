#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        while(*aux=='\t'){
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
   tTipo tipo;

    TamanhoRegFaces(faces,&qtd_f);
    //printf("tamanho faces: %d\n",qtd);
    
    //glBegin(GL_LINES);
        for(i=0;i<qtd_f;i++){
            elementoRegFaces (faces,i+1,&tipo,&qtd);
            
            switch (qtd){
        
            case 4:
                glBegin(GL_QUADS);
                    elementoRegPoints (points,tipo.point1+1,&tipo2);
                    glVertex3d(tipo2.x,tipo2.y,tipo2.z);
                    

                    //elementoRegPoints (points,tipo.point2+1,&tipo2);
                    //glVertex3d(tipo2.x,tipo2.y,tipo2.z);

                    elementoRegPoints (points,tipo.point2+1,&tipo2);
                    glVertex3d(tipo2.x,tipo2.y,tipo2.z);
                    

                    elementoRegPoints (points,tipo.point3+1,&tipo2);
                    glVertex3d(tipo2.x,tipo2.y,tipo2.z);
                   

                    //elementoRegPoints (points,tipo.point3+1,&tipo2);
                    //glVertex3d(tipo2.x,tipo2.y,tipo2.z);
        

                    //elementoRegPoints (points,tipo.point4+1,&tipo2);
                    //glVertex3d(tipo2.x,tipo2.y,tipo2.z);

                    elementoRegPoints (points,tipo.point4+1,&tipo2);
                    glVertex3d(tipo2.x,tipo2.y,tipo2.z);
                    
                    //elementoRegPoints (points,tipo.point1+1,&tipo2);
                   // glVertex3d(tipo2.x,tipo2.y,tipo2.z);
                glEnd();
                 
                break;
            case 3:
                glBegin(GL_TRIANGLES);
                    elementoRegPoints (points,tipo.point1+1,&tipo2);
                    glVertex3d(tipo2.x,tipo2.y,tipo2.z);
                    

                    elementoRegPoints (points,tipo.point2+1,&tipo2);
                    glVertex3d(tipo2.x,tipo2.y,tipo2.z);
                    
                    //elementoRegPoints (points,tipo.point2+1,&tipo2);
                    //glVertex3d(tipo2.x,tipo2.y,tipo2.z);
                  
                    elementoRegPoints (points,tipo.point3+1,&tipo2);
                    glVertex3d(tipo2.x,tipo2.y,tipo2.z);
                    
                    //elementoRegPoints (points,tipo.point3+1,&tipo2);
                    //glVertex3d(tipo2.x,tipo2.y,tipo2.z);

                    //elementoRegPoints (points,tipo.point1+1,&tipo2);
                    //glVertex3d(tipo2.x,tipo2.y,tipo2.z);
                glEnd();
                break;
                    
        
            }
        
      
            
        }//for        



    //glEnd();

}


