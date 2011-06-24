#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "importar.h"



tRegFaces faces;
tRegPoints points;
tEsfera esfera[QTD_ESFERAS+1];
int rx = 0,ry=0,rz=0,p=0,width_window=500,height_window=500,num_esfera=0,qtd_atual_linha1=13,qtd_atual_linha2=13,qtd_atual_linha3=13,qtd_atual_linha4=13,qtd_atual_linha5=13;
double z=0.5,cor_esferas=0.0;
double trans_ini_m=-19,escala_missel=0.2;//padrão escala 0.2m translação inicial: -12(eixo y)
char aviao,missel;
int i;


void iluminacao(void){
    //GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0};
    GLfloat luzAmbiente[4]={1,1,1,1.0}; 
	GLfloat luzDifusa[4]={0.8,0.8,0.8,1.0};	   // "cor" 
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho" 
	GLfloat posicaoLuz[4]={0.0, -10.0, 20.0, 1.0};
    GLfloat posicaoLuz2[4]={-0.0, 10.0, 20.0, 1};

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0}; 
	GLint especMaterial = 60;

 	// Especifica que a cor de fundo da janela sera preta
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
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
   if(p==0){
    glOrtho(-20.0, 20.0, -20.0, 20.0, 1, 60.0);
   }else{
    gluPerspective(-200, 0.5, 1, 300);
   //glFrustum(-2, 2, -2, 2,0.5, 30);
   }
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
   
   //missel center
   glPushMatrix();
   glColor3d(1, 0, 0);
   glTranslated(0, trans_ini_m+4, 0);
   glTranslated(rx, ry, 0);
   glRotated(-90,1,0,0);
   
   glScaled(escala_missel,escala_missel,escala_missel);

   glCallList(missel);
   glPopMatrix();
    
   //missel left  1
   glPushMatrix();
   glColor3d(1, 0, 0);
   glTranslated(0, trans_ini_m, 0);
   glTranslated(-1.7,0 , 0);
   glTranslated(rx, ry, 0);
   glRotated(-90,1,0,0);
   
   glScaled(escala_missel,escala_missel,escala_missel);

   glCallList(missel);
   glPopMatrix();

   //missel left  2
   glPushMatrix();
   glColor3d(1, 0, 0);
   glTranslated(0, trans_ini_m, 0);
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
   glTranslated(0, trans_ini_m, 0);
   glTranslated(rx, ry, 0);
   glTranslated(1.7,0 , 0);
   glRotated(-90,1,0,0);
   
   glScaled(escala_missel,escala_missel,escala_missel);

   glCallList(missel);
   glPopMatrix();

   //missel right  2
   glPushMatrix();
   glColor3d(1, 0, 0);
   glTranslated(0, trans_ini_m, 0);
   glTranslated(1.7,0 , 0);
   glTranslated(1.2,0 , 0);
   glTranslated(rx, ry, 0);
   glRotated(-90,1,0,0);
   
   glScaled(escala_missel,escala_missel,escala_missel);

   glCallList(missel);
   glPopMatrix();
  
   Esferas();


    //Aviao
   glPushMatrix();
   glColor3d(0, 0, 1);
   glTranslated(0, -17.5, 14);
   glTranslated(rx,0, 0);
   glRotated(170,1,0,0);
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
        case'A':
        case'a':
            rx--;
            glutPostRedisplay();
        break;
        case'S':
        case's':
            ry--;
            glutPostRedisplay();
        break;
        case'D':
        case'd':
            rx++;
            glutPostRedisplay();
        break;
        case'W':
        case'w':
            ry++;
            glutPostRedisplay();
        break;
        case'F':
        case'f':
            rz--;
            glutPostRedisplay();
        break;
        case'R':
        case'r':
            rz++;
            glutPostRedisplay();
        break;
        case'Q':
        case'q':
            p = p==0 ? 1 : 0;
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
        glutSolidSphere(1,16,16);
     }
     glPopMatrix();
   }

   //Esferas devastadoras linha 5
   for(i=0;i<QTD_LINHA_ESFERA;i++,num_esfera++){
     glPushMatrix();
     cor_esferas+=0.001;
     glColor3d(0, cor_esferas, cor_esferas);
     if(esfera[num_esfera].status  == DISPONIVEL){
        glTranslated(esfera[num_esfera].x,esfera[num_esfera].y,esfera[num_esfera].z);
        glutSolidSphere(1,16,16);
     }
     glPopMatrix();
   }
 
    
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


int main (int argc,char **argv)
{
  
   
    glutInit(&argc,argv);
    //glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(width_window,height_window);
    glutCreateWindow("Gabriel de Souza Rolim");

    Inicializa();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);   
    glutMainLoop();


    return 0;


}
