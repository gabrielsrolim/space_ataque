#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "importar.h"


tPosicao missel_esfera,missel_nave,nave_espacial;
tRegFaces faces;
tRegPoints points;
tEsfera esfera[QTD_ESFERAS+1];
int width_window=800,height_window=650,num_esfera=0;
int time=30,dispara=0,dispara_missel_esfera=0,missel_esfera_habilita=0,missel_selecionado;
double rx = 0.0,ry=0.0,rz=0.0,trans_missel_nave=0.0,trans_missel_esfera=0.0,vez=0.0;
double z=0.5,cor_esferas=0.0,mov_esferas=0.0;
double trans_ini_nave=-15,escala_missel=0.2;//padrão escala 0.2m translação inicial: -19(eixo y)
char aviao,missel;
int num=0; 
int i;

void ResetaJogo(){
   rx = 0.0;ry=0.0;rz=0.0;trans_missel_nave=0.0;trans_missel_esfera=0.0;vez=0.0; dispara=0; mov_esferas=0.0; 
    
    for(i=0;i<QTD_ESFERAS;i++){
        esfera[i].status = DISPONIVEL;
    }
}


void ResetaNave(){
   rx = 0.0;ry=0.0;rz=0.0;vez=0.0; 
}


void iluminacao(void){
    //GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0};
    GLfloat luzAmbiente[4]={1,1,1,1.0}; 
	GLfloat luzDifusa[4]={1,1,1,1.0};	   // "cor" 
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho" 
	GLfloat posicaoLuz[4]={18.0, 0.0, 20, 1};
    GLfloat posicaoLuz2[4]={-18.0, 0.0, 20, 1};

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
   
   //glMatrixMode(GL_VIEWPORT);
   //glViewport(0, 0, 500, 250);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glClearColor(1.0, 1.0, 1.0, 1.0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
      
   glEnable(GL_DEPTH_TEST); 
    
   glTranslated(0, 0, -20);  

   glPushMatrix(); 
    glBegin(GL_LINES);
        glColor3d(1, 0, 0);//red x
        glVertex3d(0,0,0);
        glVertex3d(40,0,0);
        glVertex3d(0,0,0);
        glVertex3d(-40,0,0); 
    glEnd();
    
    //glLoadIdentity();
    
    glBegin(GL_LINES);
        glColor3d(0, 1, 0);//green y
        glVertex3d(0,0,0);
        glVertex3d(0,40,0);
        glVertex3d(0,0,0);
        glVertex3d(0,-40,0);   
    glEnd();
    
    //glLoadIdentity();

    glBegin(GL_LINES);
        glColor3d(0, 0, 1);//blue Z
        glVertex3d(0,0,0);
        glVertex3d(0,0,40);  
    glEnd();
  
  
   Esferas();
   misseis();


    //Aviao
   glPushMatrix();
   glColor3d(0, 0, 1);
   glTranslated(0, -17.5, 5);
   glTranslated(rx,0, 0);
   glRotated(180,0,0,1);
   glRotated(8,1,0,0);
   glScaled(0.5,0.5,0.5);
   
   glCallList(aviao);
   glPopMatrix(); 

   glPopMatrix();       
   
}

void display(void){
      
   Desenha();
  glutSwapBuffers();
  //glFlush();
}

void keyboard(unsigned char k,int x,int y){
    switch(k){
        case ' ':
              dispara=1;
              break;
        case'A':
        case'a':
            rx-=VELOCIDADE_DELC_AVIAO;
            glutPostRedisplay();
        break;
        case'S':
        case's':
            ry-=VELOCIDADE_DELC_AVIAO;
            glutPostRedisplay();
        break;
        case'D':
        case'd':
            rx+=VELOCIDADE_DELC_AVIAO;
            glutPostRedisplay();
        break;
        case'W':
        case'w':
            ry+=VELOCIDADE_DELC_AVIAO;
            glutPostRedisplay();
        break;
        case'F':
        case'f':
            rz-=VELOCIDADE_DELC_AVIAO;
            glutPostRedisplay();
        break;
        case'R':
        case'r':
            rz+=VELOCIDADE_DELC_AVIAO;
            glutPostRedisplay();
        break;
        case'Z':
        case'z':
            z+=0.1;
            printf("z: %f\n",z);
            glutPostRedisplay();
        break;
        case'X':
        case'x':
            
            z-=0.1;
            printf("z: %f\n",z);
            if(z<=0.0){
                z=0.1;            
            }
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

   //Esferas devastadoras linha 5
   /*for(i=0;i<QTD_LINHA_ESFERA;i++,num_esfera++){
     glPushMatrix();
     cor_esferas+=0.001;
     glColor3d(0, cor_esferas, cor_esferas);
     if(esfera[num_esfera].status  == DISPONIVEL){
        glTranslated(esfera[num_esfera].x,esfera[num_esfera].y,esfera[num_esfera].z);
        glTranslated(0,mov_esferas,0);
        glutSolidSphere(1,16,16);
     }
     glPopMatrix();
   }//*/
 
    
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
    
   //missel left  1
   /*glPushMatrix();
   glColor3d(1, 0, 0);
   glTranslated(0, trans_ini_nave, 0);
   glTranslated(-1.7,0 , 0);
   glTranslated(rx, ry, 0);
   glRotated(-90,1,0,0);
   
   glScaled(escala_missel,escala_missel,escala_missel);

   glCallList(missel);
   glPopMatrix();

   //missel left  2
   glPushMatrix();
   glColor3d(1, 0, 0);
   glTranslated(0, trans_ini_nave, 0);
   glTranslated(-1.7,0 , 0);
   glTranslated(-1.2,0 , 0);
   glTranslated(rx, ry, 0);
   glRotated(-90,1,0,0);
   
   glScaled(escala_missel,escala_missel,escala_missel);

   glCallList(missel);
   glPopMatrix();

   //missel right 1
   glPushMatrix();
   glColor3d(1, 0, 0);
   glTranslated(0, trans_ini_nave, 0);
   glTranslated(rx, ry, 0);
   glTranslated(1.7,0 , 0);
   glRotated(-90,1,0,0);
   
   glScaled(escala_missel,escala_missel,escala_missel);

   glCallList(missel);
   glPopMatrix();

   //missel right  2
   glPushMatrix();
   glColor3d(1, 0, 0);
   glTranslated(0, trans_ini_nave, 0);
   glTranslated(1.7,0 , 0);
   glTranslated(1.2,0 , 0);
   glTranslated(rx, ry, 0);
   glRotated(-90,1,0,0);
   
   glScaled(escala_missel,escala_missel,escala_missel);

   glCallList(missel);
   glPopMatrix();//*/


}

void Inicializa(){
   
   //importarBlenderWrl("nave_pronta3.wrl",&faces,&points);
   
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

void ColisoesMisselNave(){
    int i,qtd=0;
    for(i=0;i<QTD_ESFERAS;i++){
        if((rx-esfera[i].x)<=1 && (rx-esfera[i].x)>=-1 && (trans_missel_nave+trans_ini_nave)==(esfera[i].y+mov_esferas)){               
           esfera[i].status = DESTRUIDO;
        }
    }
    for(i=0;i<QTD_ESFERAS;i++){
        if(esfera[i].status == DESTRUIDO)
            qtd++;

    }
    printf("qtd: %d\n",qtd);
    if(qtd==65){
        ResetaJogo();
    }
    
}
void ColisoesMisselEsfera(){
  int i,qtd=0;
  //printf("trans: %f\n",(trans_missel_esfera+8)-(-17.5));
  //printf("diffx: %f diffy: %f\n",(esfera[missel_selecionado].x-rx),(trans_missel_esfera+8)) ;
  if((esfera[missel_selecionado].x-rx)<=4 && (esfera[missel_selecionado].x-rx)>=-4 && (trans_missel_esfera+8)-(-17.5)>=-4 && (trans_missel_esfera+8)-(-17.5)<=4){               
      //perde 1 vida
      trans_missel_esfera=0.0;
      ResetaNave();
  }
     

}

void TimerFunction(int value){
    
    

    //srand(time(NULL));
    num= rand() % 100;
    vez+=1.0;
    if(vez==20.0 && trans_missel_esfera==0){
        dispara_missel_esfera = 1;
        vez=0.0;
        missel_esfera_habilita=1;
        missel_selecionado = num;
       // mov_esferas-=0.1;
        
    }
    if(vez==20.0){
        mov_esferas-=0.5;
    }

    if(dispara_missel_esfera){
     trans_missel_esfera-=VELOCIDADE_MISSEL;
     if(trans_missel_esfera==-30){
       dispara_missel_esfera = 0;
       trans_missel_esfera=0;
       missel_esfera_habilita=0;
       vez=0.0; 
     }
    }

    if(dispara){ 
     trans_missel_nave+=VELOCIDADE_MISSEL;
     //printf("%f\n",trans_missel);
     if(trans_missel_nave==35){
       dispara = 0;
       trans_missel_nave=0;
     }
    }
    ColisoesMisselNave();
    ColisoesMisselEsfera();
    glutPostRedisplay();
    
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
