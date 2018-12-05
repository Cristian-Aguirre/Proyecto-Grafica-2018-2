#include "GL/glut.h"
#include <stdio.h>
#include <FreeImage.h>
#include <math.h>

#define DIM 15
#define PI 3.141592

#define numTEXT 16

int texID[numTEXT];
char* textureFileNames[numTEXT] = {"asfalto.jpeg","sky.jpg","stucco_white.jpg","pacman1.jpg","ppp.jpeg","gold.jpg","portal.jpeg","lava.png","plomo.png","edi.jpeg","edi1.jpeg",
"edi2.jpeg", "edi3.jpeg", "edi4.jpeg","cielo.jpg","origen.jpeg"};

float pos[3];
float at[3];
float up[3];
float dir[3];
int angH;
int angV;
float mod,radio=1.0,roty=5.0;
int P=0,M=0;
int life=3;
int flag[5]={0,0,0,0,0};
int nflag[3]={0,0,0};
int point=0,b=0;
int npoint=0;
float posx=0.0,posy=0.0,posz=0.0;
float x=-5.0,y=0.0,z=2.5;
void camara()
{
	mod = sqrt(dir[0]*dir[0] + dir[2]*dir[2]);
	dir[0] = cos(PI*angH/180.0)/100;
	dir[2] = sin(PI*angH/180.0)/100;
	at[0] = pos[0]-dir[0];
	at[1] = pos[1]-mod*sin(PI*angV/180.0);
	at[2] = pos[2]-dir[2];

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	
    glLoadIdentity();
    gluPerspective(60.0,1.0,1.0,100.0);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(pos[0], pos[1], pos[2], at[0], at[1], at[2], up[0], up[1], up[2]);
}
void teclado1(unsigned char key, int x,int y)
{
	switch(key)
	{
		case '1':    //camara avanza
			pos[0]-=dir[0]*10;
			pos[2]-=dir[2]*10;
			break; 
		case '2':    //camara retrocede
			pos[0]+=dir[0]*10;
			pos[2]+=dir[2]*10;
			break;
		case 'd':    
		case 'D':{	
			if(posx<2*DIM){	
			posx+=0.3;}
			break;}
		case 'a':    
		//case 'A':
			if(posx>-2*DIM){		
			posx-=0.3;}
			break;									
		case 's':    
		case 'S':{
			if(posz<2*DIM){
			posz+=0.5;}
			break;
			}	
		case 'w':    
		case 'W':{
			if(posz>-2*DIM){		
			posz-=0.5;}
			break;}							
		
		case 27:   // escape
      			exit(0);
      			break;							
		default:
			break;
	}
	glutPostRedisplay();
}
void teclado2(int key, int x,int y)  // teclas para rotar la camara
{
	switch(key)
	{
		case GLUT_KEY_UP:
			if(angV>-90)
			2*angV--;
			break; 
		case GLUT_KEY_DOWN:
			if(angV<90)
			2*angV++;
			break; 
		case GLUT_KEY_LEFT:
			2*angH--;
			break; 
		case GLUT_KEY_RIGHT:
			2*angH++;
			break; 
		
		default:
			break;
	}
	glutPostRedisplay();
}

//Cargando Texturas
void loadTextures() {
  int i;
  glGenTextures(numTEXT,texID);  // Obtener el Id textura 
  for (i = 0; i < numTEXT; i++) {
     void* imgData;      // Puntero a data del Archivo
     int imgWidth;   // Ancho de Imagen
     int imgHeight;  // Alto de Imagen
     FREE_IMAGE_FORMAT format = FreeImage_GetFIFFromFilename(textureFileNames[i]);
     if (format == FIF_UNKNOWN) {
        printf("Archivo de Imagen desconocido %s\n", textureFileNames[i]);
            continue;
        }
     FIBITMAP* bitmap = FreeImage_Load(format, textureFileNames[i], 0);  //Leer Imagen
     if (!bitmap) {
        printf("Fallo la carga de imagen %s\n", textureFileNames[i]);
        continue;
     }
     FIBITMAP* bitmap2 = FreeImage_ConvertTo24Bits(bitmap);  // Convierte a RGB
     FreeImage_Unload(bitmap);
     imgData = FreeImage_GetBits(bitmap2);
     imgWidth = FreeImage_GetWidth(bitmap2);
     imgHeight = FreeImage_GetHeight(bitmap2);
     if (imgData) {
         printf("Texture cargada %s, tamanio %dx%d\n", 
                                     textureFileNames[i], imgWidth, imgHeight);
         int format; // Formato del color.
         if ( FI_RGBA_RED == 0 )
            format = GL_RGB;
         else
            format = GL_BGR;
            glBindTexture( GL_TEXTURE_2D, texID[i] );  // Cargando textura
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, format,GL_UNSIGNED_BYTE, imgData);
              glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }
        else {
            printf("Fallo la carga de textura %s\n", textureFileNames[i]);
        }
    }
}

void cielotecho()
{	
   float dim = DIM;	
   int num = 4;
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texID[1] );
   glBegin(GL_QUADS);
      glTexCoord2f(0,0);
      glVertex3f(-2*dim,3.8*dim,2*dim);
      glTexCoord2f(0.5,0);
      glVertex3f(2*dim,3.8*dim,2*dim);
      glTexCoord2f(0.5,1);
      glVertex3f(2*dim,3.8*dim,-2*dim);
      glTexCoord2f(0,1);
      glVertex3f(-2*dim,3.8*dim,-2*dim);
   glEnd();
}

void cielo()
{
   float lado = DIM;	
   int num = 4;
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texID[15] );
    glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(-2*lado,0,2*lado);
	glTexCoord2f(0.5,0);
	glVertex3f(-2*lado,0,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,4*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,4*lado,2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(-2*lado,0,-2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,0,-2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,4*lado,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,4*lado,-2*lado);

      glTexCoord2f(1,0);
      glVertex3f(2*lado,0,-2*lado);
      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,0,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,4*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,4*lado,-2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,0,2*lado);
      glTexCoord2f(0,0);
      glVertex3f(-2*lado,0,2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,4*lado,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,4*lado,2*lado);

      glEnd();
   }

void piso()
{	
   float dim = DIM;	
   int num = 4;
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texID[0] );
   glBegin(GL_QUADS);
      glTexCoord2f(0,0);
      glVertex3f(-2*dim,0,2*dim);
      glTexCoord2f(num*dim,0);
      glVertex3f(2*dim,0,2*dim);
      glTexCoord2f(num*dim,num*dim);
      glVertex3f(2*dim,0,-2*dim);
      glTexCoord2f(0,num*dim);
      glVertex3f(-2*dim,0,-2*dim);
   glEnd();
}


void cuerpo()
{
   float lado = DIM/5;
   float dx,dy;
   GLUquadric *quadratic;

   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texID[3]);
   glTranslatef(0.0, 1.5, 0.0);
 

   quadratic = gluNewQuadric();
   gluQuadricNormals(quadratic, GLU_SMOOTH);
   gluQuadricTexture(quadratic, GL_TRUE);
   glPushMatrix();
   glTranslatef(posx,posy,posz);
   gluSphere(quadratic,radio,40,40);
   glPopMatrix();



}
void ControlRaton( int button, int state, int x, int y)
{
if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
{
	 posy = posy + 1.0;
}
else if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
{
	 posy = posy - 1.0;
}
glutPostRedisplay();
}	 

void bloque(){
	float lado = DIM/8;
		
   int num = 4;
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texID[8] );
	glPushMatrix();
	glTranslatef(x, y, z);
    glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(-2*lado,0,2*lado);
	glTexCoord2f(0.5,0);
	glVertex3f(-2*lado,0,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,4*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,4*lado,2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(-2*lado,0,-2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,0,-2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,4*lado,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,4*lado,-2*lado);

      glTexCoord2f(1,0);
      glVertex3f(2*lado,0,-2*lado);
      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,0,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,4*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,4*lado,-2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,0,2*lado);
      glTexCoord2f(0,0);
      glVertex3f(-2*lado,0,2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,4*lado,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,4*lado,2*lado);
	
	glTexCoord2f(0,0);
      glVertex3f(-2*lado,0,2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,0,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,0,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,0,-2*lado);
      glEnd();
      glPopMatrix();
	//printf("%f  y\n",y);
	//printf("%f  x\n",x);
	//printf("%f  z\n",z);
	//printf("%f posy\n",posy);
	//printf("%f posx\n",posx);
	//printf("%f posz\n",posz);	
     
	if (y>=3.5)
	 M=0;
	if (y<=-1.5)
	  M=1;
	
	if (M==1){ 
	  y = y + 0.03;}
	else if(M==0){
	 y = y - 0.03;}

	
	
	
	glutPostRedisplay();
	
	
}
void key(){
	float lado = DIM/5;
   float dx,dy;
   GLUquadric *quadratic;

   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texID[3]);
   glTranslatef(0.0, 1.5, 0.0);
 

   quadratic = gluNewQuadric();
   gluQuadricNormals(quadratic, GLU_SMOOTH);
   gluQuadricTexture(quadratic, GL_TRUE);
   glPushMatrix();
   glRotatef(roty,1.0,0.0,1.0);
   gluSphere(quadratic,radio,40,40);
   glPopMatrix();
	roty += 3.0;
	//glRotatef(roty,1.0,0.0,1.0);	
   	
}

void portal(){
float lado = DIM/8;
		
   int num = 4;
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texID[6] );
	glPushMatrix();
	glTranslatef(-25,0.5,10.5);
	glRotatef(90,0.0,0.0,1.0);    	
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(-2*lado,0,2*lado);
	glTexCoord2f(0.5,0);
	glVertex3f(-2*lado,0,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,4*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,4*lado,2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(-2*lado,0,-2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,0,-2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,4*lado,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,4*lado,-2*lado);

      glTexCoord2f(1,0);
      glVertex3f(2*lado,0,-2*lado);
      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,0,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,4*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,4*lado,-2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,0,2*lado);
      glTexCoord2f(0,0);
      glVertex3f(-2*lado,0,2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,4*lado,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,4*lado,2*lado);
	
	glTexCoord2f(0,0);
      glVertex3f(-2*lado,0,2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,0,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,0,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,0,-2*lado);
      glEnd();
      glPopMatrix();
	
}

void edificio(){
float lado = DIM/8;
		
   int num = 4;
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texID[9] );
	glPushMatrix();
	glTranslatef(25,0.5,10.5);
	glRotatef(0.0,0.0,0.0,1.0);    	
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(-2*lado,-3,2*lado);
	glTexCoord2f(0.5,0);
	glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,8*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,8*lado,2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,8*lado,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,8*lado,-2*lado);

      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,8*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,8*lado,-2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0,0);
      glVertex3f(-2*lado,-3,2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,8*lado,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,8*lado,2*lado);
	
	glTexCoord2f(0,0);
      glVertex3f(-2*lado,8*lado,2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,8*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,8*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,8*lado,-2*lado);
      glEnd();
      glPopMatrix();
	
}

void edificio1(){
float lado = DIM/8;
		
   int num = 4;
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texID[10] );
	glPushMatrix();
	glTranslatef(25,0.5,18.5);
	glRotatef(0.0,0.0,0.0,1.0);    	
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(-2*lado,-3,2*lado);
	glTexCoord2f(0.5,0);
	glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,8*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,8*lado,2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,8*lado,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,8*lado,-2*lado);

      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,8*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,8*lado,-2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0,0);
      glVertex3f(-2*lado,-3,2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,8*lado,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,8*lado,2*lado);
	
	glTexCoord2f(0,0);
      glVertex3f(-2*lado,8*lado,2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,8*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,8*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,8*lado,-2*lado);
      glEnd();
      glPopMatrix();
	
}

void edificio2(){
float lado = DIM/8;
		
   int num = 4;
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texID[11] );
	glPushMatrix();
	glTranslatef(25,0.5,-9.5);
	glRotatef(0.0,0.0,0.0,1.0);    	
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(-2*lado,-3,2*lado);
	glTexCoord2f(0.5,0);
	glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,4*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,4*lado,2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,4*lado,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,4*lado,-2*lado);

      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,4*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,4*lado,-2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0,0);
      glVertex3f(-2*lado,-3,2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,4*lado,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,4*lado,2*lado);
	
	glTexCoord2f(0,0);
      glVertex3f(-2*lado,4*lado,2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,4*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,4*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,4*lado,-2*lado);
      glEnd();
      glPopMatrix();
	
}

void edificio3(){
float lado = DIM/8;
		
   int num = 4;
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texID[12] );
	glPushMatrix();
	glTranslatef(25,0.5,-0.5);
	glRotatef(0.0,0.0,0.0,1.0);    	
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(-2*lado,-3,2*lado);
	glTexCoord2f(0.5,0);
	glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,6*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,6*lado,2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,6*lado,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,6*lado,-2*lado);

      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,6*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,6*lado,-2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0,0);
      glVertex3f(-2*lado,-3,2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,6*lado,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,6*lado,2*lado);
	
	glTexCoord2f(0,0);
      glVertex3f(-2*lado,6*lado,2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,6*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,6*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,6*lado,-2*lado);
      glEnd();
      glPopMatrix();
	
}

void edificio4(){
float lado = DIM/8;
		
   int num = 4;
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texID[13] );
	glPushMatrix();
	glTranslatef(25,0.5,-0.5);
	glRotatef(0.0,0.0,0.0,1.0);    	
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(-2*lado,-3,2*lado);
	glTexCoord2f(0.5,0);
	glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,6*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,6*lado,2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,6*lado,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,6*lado,-2*lado);

      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,6*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,6*lado,-2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0,0);
      glVertex3f(-2*lado,-3,2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,6*lado,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,6*lado,2*lado);
	
	glTexCoord2f(0,0);
      glVertex3f(-2*lado,6*lado,2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,6*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,6*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,6*lado,-2*lado);
      glEnd();
      glPopMatrix();
	
}

void edificio5(){
float lado = DIM/8;
		
   int num = 4;
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texID[9] );
	glPushMatrix();
	glTranslatef(-25,0.5,18.5);
	glRotatef(0.0,0.0,0.0,1.0);    	
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(-2*lado,-3,2*lado);
	glTexCoord2f(0.5,0);
	glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,10*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,10*lado,-2*lado);

      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,10*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0,0);
      glVertex3f(-2*lado,-3,2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,10*lado,2*lado);
	
	glTexCoord2f(0,0);
      glVertex3f(-2*lado,10*lado,2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,10*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,-2*lado);
      glEnd();
      glPopMatrix();
	
}

void edifity(){
float lado = DIM/8;
		
   int num = 4;
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texID[10] );
	glPushMatrix();
	glTranslatef(-25,0.5,-18.5);
	glRotatef(0.0,0.0,0.0,1.0);    	
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(-2*lado,-3,2*lado);
	glTexCoord2f(0.5,0);
	glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,10*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,10*lado,-2*lado);

      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,10*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0,0);
      glVertex3f(-2*lado,-3,2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,10*lado,2*lado);
	
	glTexCoord2f(0,0);
      glVertex3f(-2*lado,10*lado,2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,10*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,-2*lado);
      glEnd();
      glPopMatrix();
	
}

void edifity1(){
float lado = DIM/8;
		
   int num = 4;
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texID[12] );
	glPushMatrix();
	glTranslatef(-5.5,0.5,-18.5);
	glRotatef(0.0,0.0,0.0,1.0);    	
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(-2*lado,-3,2*lado);
	glTexCoord2f(0.5,0);
	glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,10*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,10*lado,-2*lado);

      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,10*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0,0);
      glVertex3f(-2*lado,-3,2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,10*lado,2*lado);
	
	glTexCoord2f(0,0);
      glVertex3f(-2*lado,10*lado,2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,10*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,-2*lado);
      glEnd();
      glPopMatrix();
	
}
void edifity2(){
float lado = DIM/8;
		
   int num = 4;
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texID[12] );
	glPushMatrix();
	glTranslatef(10.5,0.5,-18.5);
	glRotatef(0.0,0.0,0.0,1.0);    	
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(-2*lado,-3,2*lado);
	glTexCoord2f(0.5,0);
	glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,10*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,10*lado,-2*lado);

      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,10*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0,0);
      glVertex3f(-2*lado,-3,2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,10*lado,2*lado);
	
	glTexCoord2f(0,0);
      glVertex3f(-2*lado,10*lado,2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,10*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,-2*lado);
      glEnd();
      glPopMatrix();
	
}
void edifity3(){
float lado = DIM/8;
		
   int num = 4;
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texID[13] );
	glPushMatrix();
	glTranslatef(-15.0,0.5,18.5);
	glRotatef(0.0,0.0,0.0,1.0);    	
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(-2*lado,-3,2*lado);
	glTexCoord2f(0.5,0);
	glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,10*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,10*lado,-2*lado);

      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,10*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0,0);
      glVertex3f(-2*lado,-3,2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,10*lado,2*lado);
	
	glTexCoord2f(0,0);
      glVertex3f(-2*lado,10*lado,2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,10*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,-2*lado);
      glEnd();
      glPopMatrix();
	
}
void edifity4(){
float lado = DIM/8;
		
   int num = 4;
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texID[9] );
	glPushMatrix();
	glTranslatef(-9.0,0.5,18.5);
	glRotatef(0.0,0.0,0.0,1.0);    	
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(-2*lado,-3,2*lado);
	glTexCoord2f(0.5,0);
	glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,10*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,10*lado,-2*lado);

      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,10*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0,0);
      glVertex3f(-2*lado,-3,2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,10*lado,2*lado);
	
	glTexCoord2f(0,0);
      glVertex3f(-2*lado,10*lado,2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,10*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,-2*lado);
      glEnd();
      glPopMatrix();
	
}
void edifity5(){
float lado = DIM/8;
		
   int num = 4;
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texID[11] );
	glPushMatrix();
	glTranslatef(-3.0,0.5,20.0);
	glRotatef(0.0,0.0,0.0,1.0);    	
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(-2*lado,-3,2*lado);
	glTexCoord2f(0.5,0);
	glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,10*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,10*lado,-2*lado);

      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,10*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0,0);
      glVertex3f(-2*lado,-3,2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,10*lado,2*lado);
	
	glTexCoord2f(0,0);
      glVertex3f(-2*lado,10*lado,2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,10*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,-2*lado);
      glEnd();
      glPopMatrix();
	
}
void edifity6(){
float lado = DIM/8;
		
   int num = 4;
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texID[13] );
	glPushMatrix();
	glTranslatef(5.0,0.5,18.5);
	glRotatef(0.0,0.0,0.0,1.0);    	
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(-2*lado,-3,2*lado);
	glTexCoord2f(0.5,0);
	glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,10*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,10*lado,-2*lado);

      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,10*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0,0);
      glVertex3f(-2*lado,-3,2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,10*lado,2*lado);
	
	glTexCoord2f(0,0);
      glVertex3f(-2*lado,10*lado,2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,10*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,-2*lado);
      glEnd();
      glPopMatrix();
	
}
void edifity7(){
float lado = DIM/8;
		
   int num = 4;
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texID[11] );
	glPushMatrix();
	glTranslatef(5.0,0.5,-22.5);
	glRotatef(0.0,0.0,0.0,1.0);    	
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(-2*lado,-3,2*lado);
	glTexCoord2f(0.5,0);
	glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,10*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,10*lado,-2*lado);

      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,10*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0,0);
      glVertex3f(-2*lado,-3,2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,10*lado,2*lado);
	
	glTexCoord2f(0,0);
      glVertex3f(-2*lado,10*lado,2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,10*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,-2*lado);
      glEnd();
      glPopMatrix();
	
}
void edificy(){
float lado = DIM/8;
		
   int num = 4;
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texID[10] );
	glPushMatrix();
	glTranslatef(11.0,0.5,18.5);
	glRotatef(0.0,0.0,0.0,1.0);    	
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(-2*lado,-3,2*lado);
	glTexCoord2f(0.5,0);
	glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,10*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,10*lado,-2*lado);

      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,10*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0,0);
      glVertex3f(-2*lado,-3,2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,10*lado,2*lado);
	
	glTexCoord2f(0,0);
      glVertex3f(-2*lado,10*lado,2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,10*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,-2*lado);
      glEnd();
      glPopMatrix();
	
}
void edificy1(){
float lado = DIM/8;
		
   int num = 4;
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texID[12] );
	glPushMatrix();
	glTranslatef(19.0,0.5,21.0);
	glRotatef(0.0,0.0,0.0,1.0);    	
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(-2*lado,-3,2*lado);
	glTexCoord2f(0.5,0);
	glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,10*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,10*lado,-2*lado);

      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,10*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0,0);
      glVertex3f(-2*lado,-3,2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,10*lado,2*lado);
	
	glTexCoord2f(0,0);
      glVertex3f(-2*lado,10*lado,2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,10*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,-2*lado);
      glEnd();
      glPopMatrix();
	
}
void edificy2(){
float lado = DIM/8;
		
   int num = 4;
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texID[12] );
	glPushMatrix();
	glTranslatef(22.0,0.5,-22.5);
	glRotatef(0.0,0.0,0.0,1.0);    	
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(-2*lado,-3,2*lado);
	glTexCoord2f(0.5,0);
	glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,10*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,10*lado,-2*lado);

      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,10*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0,0);
      glVertex3f(-2*lado,-3,2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,10*lado,2*lado);
	
	glTexCoord2f(0,0);
      glVertex3f(-2*lado,10*lado,2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,10*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,-2*lado);
      glEnd();
      glPopMatrix();
	
}

void edificy3(){
float lado = DIM/8;
		
   int num = 4;
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texID[13] );
	glPushMatrix();
	glTranslatef(-22.0,0.5,-5.5);
	glRotatef(0.0,0.0,0.0,1.0);    	
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(-2*lado,-3,2*lado);
	glTexCoord2f(0.5,0);
	glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,10*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,10*lado,-2*lado);

      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,10*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0,0);
      glVertex3f(-2*lado,-3,2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,10*lado,2*lado);
	
	glTexCoord2f(0,0);
      glVertex3f(-2*lado,10*lado,2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,10*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,-2*lado);
      glEnd();
      glPopMatrix();
	
}

void edificy4(){
float lado = DIM/8;
		
   int num = 4;
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texID[13] );
	glPushMatrix();
	glTranslatef(-22.0,0.5,0.5);
	glRotatef(0.0,0.0,0.0,1.0);    	
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(-2*lado,-3,2*lado);
	glTexCoord2f(0.5,0);
	glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,10*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(-2*lado,-3,-2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(-2*lado,10*lado,-2*lado);

      glTexCoord2f(1,0);
      glVertex3f(2*lado,-3,-2*lado);
      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,10*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);

      glTexCoord2f(0.5,0);
      glVertex3f(2*lado,-3,2*lado);
      glTexCoord2f(0,0);
      glVertex3f(-2*lado,-3,2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,2*lado);
      glTexCoord2f(0.5,1);
      glVertex3f(2*lado,10*lado,2*lado);
	
	glTexCoord2f(0,0);
      glVertex3f(-2*lado,10*lado,2*lado);
      glTexCoord2f(1,0);
      glVertex3f(2*lado,10*lado,2*lado);
      glTexCoord2f(1,1);
      glVertex3f(2*lado,10*lado,-2*lado);
      glTexCoord2f(0,1);
      glVertex3f(-2*lado,10*lado,-2*lado);
      glEnd();
      glPopMatrix();
	
}

void display() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  

    glEnable(GL_TEXTURE_2D);
    camara();
    piso();
    cielo();
    cielotecho();
    //cuerpo();
    //bloque();
    edificio();
    edificio1();
    edificio2();
    edificio3();
    edificio4();
    edificio5();
    edifity();
    edifity1();
    edifity2();
    edifity3();
    edifity4();
    edifity5();
    edifity6();
    edifity7();
    edificy();
    edificy1();
    edificy2();
    edificy3();
    edificy4();
     glPushMatrix();
    //if(flag[0]!=1){
    glTranslatef(-5,0.0,10);
    key();
    	if((posx>=-5-0.3&&posx<=-5+0.3)&&posy==0.0&&(posz>=10-0.3&&posz<=10+0.3)){
		flag[0]=1;
		point=point+10;
			b++;}
    //}
	 glPopMatrix();
	 glPushMatrix();
    //if(flag[1]!=1){
    glTranslatef(10,0.0,-10);
    key();
    	if((posx>=10 -0.3&&posx<=10+0.3)&&posy==0.0&&(posz>=-10-0.3&&posz<=-10+0.3)){
		flag[1]=1;
		point=point+10;
		b++;}
    //}
	 glPopMatrix();
	 glPushMatrix();
    //if(flag[2]!=1){
    glTranslatef(-10,0.0,10);
    key();
    	if((posx>=-10-0.3&&posx<=-10+0.3)&&posy==0.0&&(posz>=10-0.3&&posz<=10+0.3)){
		flag[2]=1;
		point=point+10;
			b++;}
    //}

    	 glPopMatrix();
	 glPushMatrix();
    if(flag[3]!=1){
    glTranslatef(5,0.0,5);
    key();
    	if((posx>=5-0.3&&posx<=5+0.3)&&posy==0.0&&(posz>=5-0.3&&posz<=5+0.3)){
		flag[3]=1;
		point=point+10;
		b++;}}

     glPopMatrix();
  glPushMatrix();
  
   if(flag[4]!=1){
    	glTranslatef(-5,0.0,3);
    	key();
    	if((posx>=-5-0.5&&posx<=-5+0.5)&&posy==0.0&&(posz>=3-0.5&&posz<=3+0.5)){
		flag[4]=1;
		point+=10;
			b++;}
    }
     glPopMatrix();
 glPushMatrix();
      if(nflag[0]!=1){
    glTranslatef(5,0.0,7);
   
    	if((posx>=5-0.3&&posx<=5+0.3)&&posy==0.0&&(posz>=7-0.3&&posz<=7+0.3)){
		nflag[0]=1;
		npoint++;}
    }
 	glPopMatrix();
 glPushMatrix();
 if(nflag[1]!=1){
    glTranslatef(-8,0.0,8);
    
    	if((posx>=-8-0.3&&posx<=-8+0.3)&&posy==0.0&&(posz>=8-0.3&&posz<=8+0.3)){
		nflag[1]=1;
		npoint++;}
    }
 glPopMatrix();
 glPushMatrix();
 if(nflag[2]!=1){
    glTranslatef(8,0.0,-8);
    
    	if((posx>=8-0.3&&posx<=8+0.3)&&posy==0.0&&(posz>=-8-0.3&&posz<=-8+0.3)){
		nflag[2]=1;
		npoint++;}
    }
   
    glPopMatrix();

 
   //portal();
	if(b==5&&(posx>=-25-0.5&&posx<=-25+0.5)&&posy==0.0&&(posz>=10.5-0.5&&posz<=10.5+0.5)){
	printf(" you won total points, %d \n  lifes: %d",point-5*npoint,life-npoint);
	exit(0);	
	}
	else if(npoint==3){
	printf("you lose total points, %d \n",point -5*npoint);
	exit(0);
	}

    glutSwapBuffers();  //Requiere doble buffered en dibujo)
}
void initGL() 
 {
 
	pos[0] = DIM*0.75;
	pos[1] = 1.0;		//no cambia
	pos[2] = DIM*0.75;

	angH = 0;
	angV = 0;
	up[0] = 0.0;
	up[1] = 1.0;
	up[2] = 0.0;
	dir[0] = at[0]-pos[0];
	dir[2] = at[2]-pos[2];
    glClearColor(1.0, 1.0, 1.0, 1.0);
    
    glEnable(GL_DEPTH_TEST);
    
    float white[4] = { 1, 1, 1, 0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(DIM*60,DIM*60); 
    glutInitWindowPosition(100,100);
    glutCreateWindow("Mundo 3");
    initGL();
    loadTextures();
    glutDisplayFunc(display); 
    glutMouseFunc(ControlRaton);
    glutKeyboardFunc(teclado1);
	glutSpecialFunc(teclado2);
    glutMainLoop();
    return 0;
}
