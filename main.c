#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "importar.h"


tPosicao missel_esfera,missel_nave,nave_espacial;
tRegFaces faces;
tRegPoints points;
tEsfera esfera[QTD_ESFERAS];
int width_window=800,height_window=650,num_esfera=0;
int time=30,dispara=0,dispara_missel_esfera=0,missel_esfera_habilita=0,missel_selecionado,vidas=3,habilita_desenho=1;
double rx = 0.0,ry=0.0,rz=0.0,trans_missel_nave=0.0,trans_missel_esfera=0.0,vez=0.0,vira_nave=0;
double z=0.5,cor_esferas=0.0,mov_esferas=0.0;
double trans_ini_nave=-15,escala_missel=0.2;//padrão escala 0.2m translação inicial: -19(eixo y)
double tamanho_vida = 5;

char aviao,missel;
int num=0,pontos=0; 
int i;
char textpontos[50],textRodada[50];



// Desenha um texto na janela GLUT
void Texto(){
     int i;
     glColor3f(0,0,0);     
     // Posição onde o textpontos será colocado
     sprintf(textpontos,"Pontos: %d",pontos);
     glRasterPos3d(10, 0, 0);
      for(i=0; textpontos[i] != '\0'; ++i)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,textpontos[i]);
}

void Texto2(){
     int i;
     glColor3f(0,0,0);     
     // Posição onde o textpontos será colocado
     sprintf(textRodada,"%s","Game Over!");
     glRasterPos3d(-4, 0, 0);
      for(i=0; textRodada[i] != '\0'; ++i)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,textRodada[i]);
     sprintf(textRodada,"%s","Para Encerrar o jogo Aperte 'q'.");
     glRasterPos3d(-4, -2, 0);
      for(i=0; textRodada[i] != '\0'; ++i)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,textRodada[i]);
     sprintf(textRodada,"%s","Para Continuar o jogo Aperte 'e'.");
     glRasterPos3d(-4, -4, 0);
      for(i=0; textRodada[i] != '\0'; ++i)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,textRodada[i]);
    if(pontos >20){ 
        sprintf(textRodada,"Parabens! Voce Fez %d pontos.",pontos);
        glRasterPos3d(-4, -6, 0);
        for(i=0; textRodada[i] != '\0'; ++i)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,textRodada[i]);    
    }
     
}

void RecomecaJogo(){
    rx = 0.0;ry=0.0;rz=0.0;trans_missel_nave=0.0;trans_missel_esfera=0.0;vez=0.0; dispara=0; mov_esferas=0.0;
    tamanho_vida = 5;pontos=0;
    vidas=3;
    for(i=0;i<QTD_ESFERAS;i++){
        esfera[i].status = DISPONIVEL;
    }
}




void ResetaJogo(int fim){
   rx = 0.0;ry=0.0;rz=0.0;trans_missel_nave=0.0;trans_missel_esfera=0.0;vez=0.0; dispara=0; mov_esferas=0.0;
   
    if(tamanho_vida<=-5){
     tamanho_vida = 5;
    }
    if(fim){
      habilita_desenho=0;
      Desenha();
      vidas=3;
    }
    
    for(i=0;i<QTD_ESFERAS;i++){
        esfera[i].status = DISPONIVEL;
    }
}


void ResetaNave(){
   rx = 0.0;ry=0.0;vez=0.0; 
}


void iluminacao(void){
    //GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0};
    GLfloat luzAmbiente[4]={1,1,1,1.0}; 
	GLfloat luzDifusa[4]={1,1,1,1};	   // "cor" 
	GLfloat luzEspecular[4]={1, 1, 1, 0.4};// "brilho" 
	GLfloat posicaoLuz[4]={20.0, 0.0, 20, 1};
    GLfloat posicaoLuz2[4]={-20.0, 0.0, 20, 1};

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0}; 
	GLint especMaterial = 60;

 	// Especifica que a cor de fundo da janela sera preta
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
	// Habilita o modelo de colorizacao de Gouraud
	glShadeModel(GL_SMOOTH);

	// Define a refletancia do material 
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentracao do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

   // Define a concentracao do brilho
	glMaterialfv(GL_FRONT,GL_DIFFUSE ,luzDifusa);

   // Define a concentracao do brilho
	glMaterialfv(GL_FRONT,GL_SPECULAR ,luzEspecular);

	// Ativa o uso da luz ambiente 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os par�metros da luz de n�mero 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

    glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbiente); 
	glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT1, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz2 );

	// Habilita a definicao da cor do material a partir da cor corrente
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminacao
	glEnable(GL_LIGHTING);  
	// Habilita a luz de numero 0
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);


     
     
}


void Desenha(){
   
   glDrawBuffer(GL_BACK);
    
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
    glOrtho(-20.0, 20.0, -20.0, 20.0, 1, 60.0);
   
   glMatrixMode(GL_VIEWPORT);
   glViewport(0, 50, width_window, height_window);
   
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glClearColor(0.5, 0.5, 0.5, 0.5);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
      
   glEnable(GL_DEPTH_TEST); 
    
   glTranslated(0, 0, -20);  
  
   if(habilita_desenho){
     Esferas();
     misseis();
     desenha_aviao();
     
   }else{
    Texto2(); 
   }

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-20.0, 20.0, -20.0, 20.0, 1, 60.0);
   
   glViewport(0, 0, width_window, 50);
   
   //glDisable(GL_DEPTH_TEST); 
   glMatrixMode(GL_MODELVIEW);
   
   glDisable(GL_LIGHTING);
   
   barravida();
   chances();
   Texto();
   
   glBegin(GL_QUAD_STRIP);
     //glNormal3d(0.0, 0.0, 1.0);
     glColor3d(0.5, 0.4, 0.3);//vida vermelha
     glVertex3d(-20,20,-10);
     glVertex3d(-20,-20,-10);
     glVertex3d(20,20,-10);
     glVertex3d(20,-20,-10);
     glEnd();
   
   glEnable(GL_LIGHTING);
   //glEnable(GL_DEPTH_TEST);
   
}

void desenha_aviao(){
     //Aviao
   glPushMatrix();
   glColor3d(0, 0.0,0.000001234734 );
   glTranslated(0, -17.5, 5);
   glTranslated(rx,0, 0);
   glRotated(180,0,0,1);
   glRotated(8,1,0,0);
   glRotated(vira_nave,0,1,0);
   glScaled(0.5,0.5,0.5);
   
   glCallList(aviao);
   glPopMatrix(); 

}

void chances(){
   
  //Vida 1
  if (vidas!=0){
   glPushMatrix();
       glColor3d(0, 0, 1);
       glTranslated(-15,0, 0);
       glScaled(0.1,1,1);
       glRotated(90,0,0,1);
       glRotated(180,1,0,0);
       glCallList(aviao);
  glPopMatrix();
 } 
 if(vidas>1){
 //Vida 2
   glPushMatrix();
       glColor3d(0, 0, 1);
       glTranslated(-13.5,0, 0);
       glScaled(0.1,1,1);
       glRotated(90,0,0,1);
       glRotated(180,1,0,0);  
       glCallList(aviao);
   glPopMatrix();
 }
 if(vidas==3){
 //Vida 3
   glPushMatrix();
       glColor3d(0, 0, 1);
       glTranslated(-11.9,0, 0);
       glScaled(0.1,1,1);
       glRotated(90,0,0,1);
       glRotated(180,1,0,0);  
       glCallList(aviao);
   glPopMatrix(); 
  }
}


void barravida(){

   glBegin(GL_QUAD_STRIP);
        glNormal3d(0.0, 0.0, 1.0);
        glColor3d(0, 0, 1);//vida Azul
	    glVertex3d(-5,5,1);
	    glVertex3d(-5,0,1);
	    glVertex3d(tamanho_vida,5,1);
	    glVertex3d(tamanho_vida,0,1);
   glEnd();
   
   glPopMatrix();

   glPushMatrix();
   

   glBegin(GL_QUAD_STRIP);
        glNormal3d(0.0, 0.0, 1.0);
        glColor3d(1, 0, 0);//vida vermelha
	    glVertex3d(-5,5,0);
	    glVertex3d(-5,0,0);
	    glVertex3d(5,5,0);
	    glVertex3d(5,0,0);
   glEnd();
   
   glPopMatrix();
    

}

void display(void){
  
  Desenha();
   
  glutSwapBuffers();
}

void keyboard(unsigned char k,int x,int y){
    switch(k){
        case ' ':
              dispara=1;
              break;
        case'A':
        case'a':
            if(vira_nave<=10){
                vira_nave=14;            
            }else{
             if(rx<=-20.0){
               rx=-20;
             }else{
                rx-=VELOCIDADE_DELC_AVIAO;            
             }
            }
            
            glutPostRedisplay();
            //vira_nave=0;
        break;
        case'S':
        case's':
            ry-=VELOCIDADE_DELC_AVIAO;
            glutPostRedisplay();
        break;
        case'D':
        case'd':
            if(vira_nave>=-10){
                vira_nave=-14;            
            }else{
              if(rx>=20.0){
                rx=20;
              }else{
                rx+=VELOCIDADE_DELC_AVIAO;
              }
            }
            //vira_nave=-20; 
            glutPostRedisplay();
            //vira_nave=0;
        break;
        case'W':
        case'w':
            ry+=VELOCIDADE_DELC_AVIAO;
            glutPostRedisplay();
        break;
        case'R':
        case'r':
            RecomecaJogo();
            
            glutPostRedisplay();
        break;
        case'E':
        case'e':
            if(!habilita_desenho){
             sprintf(textpontos,"%s","Pontos: 0");
             habilita_desenho = 1;
             tamanho_vida = 5;
             pontos = 0;  
            }
            
            glutPostRedisplay();
        break;
        case 't':
        case 'T': rz+=VELOCIDADE_DELC_AVIAO;
                glutPostRedisplay();
              break;
        case 'g':
        case 'G': rz-=VELOCIDADE_DELC_AVIAO;
                glutPostRedisplay();
              break;
        case 'm':
        case 'M': glEnable(GL_LIGHT0);
                glutPostRedisplay();
              break;
        case 'n':
        case 'N': glDisable(GL_LIGHT0);
                glutPostRedisplay();
              break;
        case 'q':
        case 'Q': 
                exit(0);
              break;
        default:
            printf("%c\n",k);
        break;    
    }
}

void Esferas(){

   if(num_esfera!=0 || cor_esferas!=0){
     num_esfera=0;
     cor_esferas=0;
   }

   //Esferas devastadoras linha 1
   for(i=0;i<QTD_LINHA_ESFERA;i++,num_esfera++){
     glPushMatrix();
     cor_esferas+=0.001;
     glColor3d(0, 0, cor_esferas+0.1);
     if(esfera[num_esfera].status  == DISPONIVEL){
        glTranslated(esfera[num_esfera].x,esfera[num_esfera].y,esfera[num_esfera].z);
        glTranslated(0,mov_esferas,0);
        glutSolidSphere(1,16,16);
     }
     glPopMatrix();
   }

   //Esferas devastadoras linha 2
   for(i=0;i<QTD_LINHA_ESFERA;i++,num_esfera++){
     glPushMatrix();
     cor_esferas+=0.001;
     glColor3d(cor_esferas, 0, 0);
     if(esfera[num_esfera].status  == DISPONIVEL){
        glTranslated(esfera[num_esfera].x,esfera[num_esfera].y,esfera[num_esfera].z);
        glTranslated(0,mov_esferas,0);
        glutSolidSphere(1,16,16);
     }
     glPopMatrix();
   }

   //Esferas devastadoras linha 3
   for(i=0;i<QTD_LINHA_ESFERA;i++,num_esfera++){
     glPushMatrix();
     cor_esferas+=0.001;
     glColor3d(cor_esferas, cor_esferas, 0);
     if(esfera[num_esfera].status  == DISPONIVEL){
        glTranslated(esfera[num_esfera].x,esfera[num_esfera].y,esfera[num_esfera].z);
        glTranslated(0,mov_esferas,0);
        glutSolidSphere(1,16,16);
     }
     glPopMatrix();
   }

   //Esferas devastadoras linha 4
   for(i=0;i<QTD_LINHA_ESFERA;i++,num_esfera++){
     glPushMatrix();
     cor_esferas+=0.001;
     glColor3d(cor_esferas, 0, cor_esferas);
     if(esfera[num_esfera].status  == DISPONIVEL){
        glTranslated(esfera[num_esfera].x,esfera[num_esfera].y,esfera[num_esfera].z);
        glTranslated(0,mov_esferas,0);
        glutSolidSphere(1,16,16);
     }
     glPopMatrix();
   }
 
    
}


void misseis(){

    //missel nave center
   glPushMatrix();
   glColor3d(1, 0, 0);
   glTranslated(0, trans_ini_nave, 0);//retirado: +4(-19)
   glTranslated(rx, 0, 0);
   glTranslated(0, trans_missel_nave, 0);
   glRotated(-90,1,0,0);
   missel_nave.translacao_x = rx;
   missel_nave.translacao_y = trans_missel_nave;
   
   glScaled(escala_missel,escala_missel,escala_missel);

   glCallList(missel);
   glPopMatrix();

   if(missel_esfera_habilita){
       //missel esferas
       glPushMatrix();
       glColor3d(1, 0, 0);
       glTranslated(0, 8.0, 0);//retirado: +4(-19) trans_ini_esfera
       glTranslated(esfera[missel_selecionado].x, 0, 0);
       glTranslated(0, trans_missel_esfera, 0);
       glRotated(90,1,0,0);
       
       glScaled(escala_missel,escala_missel,escala_missel);

       glCallList(missel);
       glPopMatrix();//*/
   }


}

void Inicializa(){
   
   //importarBlenderWrl("nave_pronta3.wrl",&faces,&points);
   sprintf(textpontos,"%s","Pontos: 0");
   aviao=glGenLists(1);
   glNewList(aviao,GL_COMPILE);
   importarBlenderWrl("nave_pronta3.wrl",&faces,&points);
   glEndList();

   DestroiRegFaces(&faces);
   DestroiRegPoints(&points);

   //importarBlenderWrl("missel.wrl",&faces,&points);
   
   missel=glGenLists(2);
   glNewList(missel,GL_COMPILE);
    importarBlenderWrl("missel.wrl",&faces,&points);
   glEndList();

   DestroiRegFaces(&faces);
   DestroiRegPoints(&points);

   iluminacao();
   InitEsferas(esfera);
 
   
   
}


/*
*
* Colisão do Missel da Naves com as Esferas.
*
*
*
*/
void ColisoesMisselNave(){
    int i,qtd=0;
    for(i=0;i<QTD_ESFERAS;i++){
        if((rx-esfera[i].x)<=1 && (rx-esfera[i].x)>=-1 && (trans_missel_nave+trans_ini_nave)==(esfera[i].y+mov_esferas)){               
           esfera[i].status = DESTRUIDO;
           pontos+=10;
           sprintf(textpontos,"Pontos: %d",pontos);
        }
    }
    for(i=0;i<QTD_ESFERAS;i++){
        if(esfera[i].status == DESTRUIDO)
            qtd++;

    }
    if(qtd==QTD_ESFERAS){
        ResetaJogo(0);
    }
    
}


/*
*
* Colisão do Missel das Esferas com a Nave.
*
*
*
*/
void ColisoesMisselEsfera(){
 
  if((esfera[missel_selecionado].x-rx)<=4 && (esfera[missel_selecionado].x-rx)>=-4 && (trans_missel_esfera+8)-(-17.5)>=-4 && (trans_missel_esfera+8)-(-17.5)<=4){               
          
    
    num= rand() % 100;    
    if(num>=QTD_ESFERAS){
        missel_selecionado = (num - 49); 
    }else{
        missel_selecionado = num;
    }

    vidas--;
    //perde 1 vida
    if(vidas==0){
       ResetaJogo(1);
    } 
      
      tamanho_vida-= PERDE_VIDA;
      if(tamanho_vida<=-5.0){
        ResetaJogo(1); 
      }
      trans_missel_esfera=0.0;
      ResetaNave();
  }
     

}

/*
*
* Colisão das Esferas com a Nave.
*
*
*
*/

void ColisoesEsferaNave(){
   for(i=0;i<QTD_ESFERAS;i++)
   if((esfera[i].y+mov_esferas)-(-17.5)<=5.0 && esfera[i].status==DISPONIVEL && (esfera[i].y+mov_esferas)-(-17.5)>=-5.0){
     ResetaJogo(1);
   }
}


void TimerFunction(int value){
    //vira_nave=0;
    if(habilita_desenho){
        ColisoesMisselNave();
        ColisoesMisselEsfera();
        ColisoesEsferaNave();

        num= rand() % 100;
        vez+=1.0;
        if(vez==20.0 && trans_missel_esfera==0){
            dispara_missel_esfera = 1;
            vez=0.0;
            missel_esfera_habilita=1;
            if(num>=QTD_ESFERAS){
                missel_selecionado = (num - 49); 
            }else{
                missel_selecionado = num;
            }
        }
        if(vez==20.0){
            mov_esferas-=VELOCIDADE_DESC_ESFERA;
        }

        if(dispara_missel_esfera){
             trans_missel_esfera-=VELOCIDADE_MISSEL;
             if(trans_missel_esfera==-30){
                dispara_missel_esfera = 0;
                trans_missel_esfera=0;
                missel_esfera_habilita=0;
                vez=0.0;
                tamanho_vida-= PERDE_VIDA;
                if(tamanho_vida<=-5.0){
                    ResetaJogo(1); 
                } 
             }
        }

        if(dispara){ 
         trans_missel_nave+=VELOCIDADE_MISSEL;
         if((trans_missel_nave+trans_ini_nave)==(esfera[0].y+mov_esferas+1) || trans_missel_nave==35){
           dispara = 0;
           trans_missel_nave=0;
         }
        }
        
        glutPostRedisplay();
    }
    
  glutTimerFunc(time, TimerFunction, 1); 

}



int main (int argc,char **argv)
{
  
   
    glutInit(&argc,argv);
    //glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(width_window,height_window);
    glutCreateWindow("Gabriel de Souza Rolim");
    glutTimerFunc(time, TimerFunction, 1);

    Inicializa();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);   
    glutMainLoop();


    return 0;


}
