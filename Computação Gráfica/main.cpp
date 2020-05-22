#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
GLfloat escala = 1;
GLfloat rotacaoX,rotacaoY,rotacaoZ  = 0.1;
GLfloat transX,transY,transZ  = 1;
GLfloat aceleracao = 1.0;
GLfloat teta = 0,gama = 0, angulo = 0;
GLint sinal =0;
GLfloat movx, movy = 0;

void cubo()
{
    glBegin(GL_POLYGON);
       glColor3f( 1.0, 1.0, 1.0 );
       glVertex3f(  1.0, -1.0, -1.0 );
       glVertex3f(  1.0,  2.0, -1.0 );
       glVertex3f( -1.0,  2.0, -1.0 );
       glVertex3f( -1.0, -1.0, -1.0 );

  glEnd();

  // farol

      glBegin(GL_LINE_LOOP);
      glLineWidth(40);
       glColor3f( 1.0, 0.0, 0.0 );
       glVertex3f(  0.5, 0.0, -1.0 );
       glVertex3f(  0.5,  1.5, -1.0 );
       glVertex3f( -0.5,  1.5, -1.0 );
       glVertex3f( -0.5, 0.0, -1.0 );

   glEnd();



  // Lado branco - TRASEIRA
 glBegin(GL_POLYGON);
  glColor3f(   1.0,  1.0, 1.0 );
  glVertex3f(  1.0, -1.0, 1.0 );
  glVertex3f(  1.0,  1.0, 1.0 );
  glVertex3f( -1.0,  1.0, 1.0 );
  glVertex3f( -1.0, -1.0, 1.0 );
  glEnd();

  // Lado roxo - DIREITA
 glBegin(GL_POLYGON);
  glColor3f(  0.0,  1.0,  0.0 );
  glVertex3f( 1.0, -1.0, -1.0 );
  glVertex3f( 1.0,  2.0, -1.0 );
  glVertex3f( 1.0,  2.0,  1.0 );
  glVertex3f( 1.0, -1.0,  1.0 );
  glEnd();

  // Lado verde - ESQUERDA
 glBegin(GL_POLYGON);
  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -1.0, -1.0, 1.0 );
  glVertex3f( -1.0,  2.0,  1.0 );
  glVertex3f( -1.0,  2.0, -1.0 );
  glVertex3f( -1.0, -1.0, -1.0 );
  glEnd();

  // Lado azul - TOPO
 glBegin(GL_POLYGON);
  glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  1.0,  1.0,  1.0 );
  glVertex3f(  1.0,  1.0, -1.0 );
  glVertex3f( -1.0,  1.0, -1.0 );
  glVertex3f( -1.0,  1.0,  1.0 );
  glEnd();

  // banco
  glBegin(GL_POLYGON);
  glColor3f(0.0,0.0,0.0);
  glVertex3f(1.0,1.0,0.0);
  glVertex3f(-1.0,1.0,0.0);
  glVertex3f(-1.0,2.0,0.0);
  glVertex3f(1.0,2.0,0.0);
  glEnd();
//
  glBegin(GL_POLYGON);
  glColor3f(1.0,1.0,1.0);
  glVertex3f(1.0,1.0,0.5);
  glVertex3f(-1.0,1.0,0.5);
  glVertex3f(-1.0,4.0,0.5);
  glVertex3f(1.0,4.0,0.5);
  glEnd();
//cima
    glBegin(GL_POLYGON);
  glColor3f(0.0,0.0,0.0);
  glVertex3f(1.0,2.0,0.0);
  glVertex3f(-1.0,2.0,0.0);
  glVertex3f(-1.0,2.0,0.5);
  glVertex3f(1.0,2.0,0.5);
  glEnd();

  //traseira
glBegin(GL_POLYGON);
  glColor3f(0.0,0.0,0.0);
  glVertex3f(1.0,1.0,1.0);
  glVertex3f(-1.0,1.0,1.0);
  glVertex3f(-1.0,5.0,1.0);
  glVertex3f(1.0,5.0,1.0);
  glEnd();

//traseira teto
glBegin(GL_POLYGON);
  glColor3f(1.0,1.0,1.0);
  glVertex3f(1.0,5.0,-0.5);
  glVertex3f(-1.0,5.0,-0.5);
  glVertex3f(-1.0,5.0,1.0);
  glVertex3f(1.0,5.0,1.0);
  glEnd();


  // estrada
  glBegin(GL_POLYGON);
       glColor3f( 0.5, 0.27, 0.07 );
       glVertex3f(  3.0, -1.9, -10.0 );
       glVertex3f(  3.0,  -1.9, 10.0 );
       glVertex3f( -3.0,  -1.9, 10.0 );
       glVertex3f( -3.0, -1.9, -10.0 );

  glEnd();


  glBegin(GL_POLYGON);
       glColor3f( 1.0, 1.0, 1.0 );
       glVertex3f(  1.0, -1.0, -1.0 );
       glVertex3f(  1.0,  1.0, -1.0 );
       glVertex3f( -1.0,  1.0, -1.0 );
       glVertex3f( -1.0, -1.0, -1.0 );
  glEnd();

  // Lado vermelho - BASE
 glBegin(GL_POLYGON);
  glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  1.0, -1.0, -1.0 );
  glVertex3f(  1.0, -1.0,  1.0 );
  glVertex3f( -1.0, -1.0, 1.0 );
  glVertex3f( -1.0, -1.0, -1.0 );
  glEnd();
}
void cilindro()
{
	GLfloat raio = 1.0;
	GLfloat alt = 1.0;
	static GLUquadric* quad;
	quad = gluNewQuadric();
	gluCylinder(quad, raio, raio, alt, 20, 10);
}

void roda()
{
	glPushMatrix();
	glColor3f(0.0,0.0,0.0);
		//gera raio
		glPushMatrix();
			glScalef(0.1,0.1,0.8);
			cilindro();
		glPopMatrix();
		//gera raio
		glPushMatrix();
			glTranslatef(0.4,0.0,0.4);
			glRotatef(-90.0, 0.0, 1.0, 0.0);
			glScalef(0.1,0.1,0.8);
			cilindro();
		glPopMatrix();
		//gera pneu
		glPushMatrix();
			glTranslatef(0.0,-0.1,0.4);
			glRotatef(-90.0, 1.0, 0.0, 0.0);
			glScalef(0.4,0.4,0.2);
			cilindro();
		glPopMatrix();
	glPopMatrix();
}

void volante(){
	glPushMatrix();
		glTranslatef(0.0,0.5,-1.5);
		glRotatef(-45.0, 1.0, 0.0, 0.0);
		glScalef(0.1,0.1,1.5);
		cilindro();
	glPopMatrix();
	glPushMatrix();
		glRotatef(45, 1.0, 0.0, 0.0);
		glTranslatef(0.0,0.9,-1.8);
		glTranslatef(0.0,0.0,0.4);
		glRotatef(angulo, 0.0, 1.0, 0.0);
		glTranslatef(0.0,0.0,-0.4);
		roda();
	glPopMatrix();
}

void eixoRodas()
{
	glPushMatrix();
		glPushMatrix();
			glRotatef(90.0, 0.0, 1.0, 0.0);
			glTranslatef(1.7,-0.4,-1.3);
			glScalef(0.1,0.1,2.6);
			cilindro();
		glPopMatrix();
		glPushMatrix();
			glRotatef(90.0, 0.0, 1.0, 0.0);
			glTranslatef(-1.7,-0.4,-1.3);
			glScalef(0.1,0.1,2.6);
			cilindro();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(1.3,0.0,1.7);
			glRotatef(90, 0.0, 1.0, 0.0);
			glRotatef(90, 1.0, 0.0, 0.0);
			glTranslatef(0.0,0.0,0.4);
			glRotatef(teta, 0.0, 1.0, 0.0);
			glTranslatef(0.0,0.0,-0.4);
			roda();
		glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-1.3,0.0,1.7);
			glRotatef(90, 0.0, 1.0, 0.0);
			glRotatef(90, 1.0, 0.0, 0.0);
			glTranslatef(0.0,0.0,0.4);
			glRotatef(teta, 0.0, 1.0, 0.0);
			glTranslatef(0.0,0.0,-0.4);
			roda();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(1.3,0.0,-1.7);
			glRotatef(90+angulo, 0.0, 1.0, 0.0);
			glRotatef(90, 1.0, 0.0, 0.0);
			glTranslatef(0.0,0.0,0.4);
			glRotatef(teta, 0.0, 1.0, 0.0);
			glTranslatef(0.0,0.0,-0.4);
			roda();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-1.3,0.0,-1.7);
			glRotatef(90+angulo, 0.0, 1.0, 0.0);
			glRotatef(90, 1.0, 0.0, 0.0);
			glTranslatef(0.0,0.0,0.4);
			glRotatef(teta, 0.0, 1.0, 0.0);
			glTranslatef(0.0,0.0,-0.4);
			roda();
		glPopMatrix();
	glPopMatrix();
}

void carrinho()
{
	glPushMatrix();
		glScalef(1.0,0.5,2.0);
		cubo();
	glPopMatrix();
	glPushMatrix();
		volante();
	glPopMatrix();
	glPushMatrix();
		eixoRodas();
	glPopMatrix();

}

void exibe()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*
	glPushMatrix();
   //altera a escala
	glScalef(escala,escala,1);

	//rotaciona objeto X
	glRotatef(rotacaoX,1,0,0);
	//rotaciona objeto Y
	glRotatef(rotacaoY,0,1,0);
	//rotaciona objeto Z
	glRotatef(rotacaoZ,0,0,1);

	//translada objeto
	glTranslatef(movx, movy, 0);
*/
	//cria uma linha
	//glColor3f(1,0,0);
	//glBegin(GL_LINES);
	//	glVertex3f(-10,0,0);
	//	glVertex3f(10,0,0);
	//glEnd();

	//cria uma linha
	//glColor3f(0,1,0);
	//glBegin(GL_LINES);
		//glVertex3f(0,-10,0);
		//glVertex3f(0,10,0);
	//glEnd();

	//cria uma linha
	//glColor3f(0,0,1);
	//glBegin(GL_LINES);
	//	glVertex3f(0,0,-10);
	//	glVertex3f(0,0,10);
	//glEnd();

	//insere carrinho
	glRotatef(angulo/120, 0.0, -aceleracao,0.0);
	glTranslatef(0.0,0.0,aceleracao);
	carrinho();
	//roda();
   //glPopMatrix();
   glFlush();
   glutSwapBuffers();

}

void gira() {
	teta+=3*sinal;
	aceleracao = 0.01*sinal;
	exibe();
}

void janela(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 1.0, 30.0);
    glMatrixMode(GL_MODELVIEW);
}

void inicia()
{
    glClearColor (0.7, 0.7, 1.0, 1.0);
    gluLookAt(8.0, 6.0, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

}
void Teclas(unsigned char tecla, GLint x, GLint y)
{
	switch(tecla){
		case ' ': sinal = 0;
			break;
		case '+' : escala+=0.1;
			break;
		case '-' : escala-=0.1;
			break;
		case '1' : rotacaoX+=1;
			break;
		case '2' : rotacaoX-=1;
			break;
		case '3' : rotacaoY+=1;
			break;
		case '4' : rotacaoY-=1;
			break;
		case '5' : rotacaoZ+=1;
			break;
		case '6' : rotacaoZ-=1;
			break;
		case 's' : sinal=0;
			break;
		case 'q' : transX+=0.1;
		printf("x:%f, y:%f, z:%f\n",transX,transY,transZ);
			break;
		case 'w' : transX-=0.1;
		printf("x:%f, y:%f, z:%f\n",transX,transY,transZ);
			break;
		case 'e' : transY+=0.1;
		printf("x:%f, y:%f, z:%f\n",transX,transY,transZ);
			break;
		case 'r' : transY-=0.1;
		printf("x:%f, y:%f, z:%f\n",transX,transY,transZ);
			break;
		case 't' : transZ+=0.1;
		printf("x:%f, y:%f, z:%f\n",transX,transY,transZ);
			break;
		case 'y' : transZ-=0.1;
		printf("x:%f, y:%f, z:%f\n",transX,transY,transZ);
			break;


	}
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	exibe();
}
void TeclasEspeciais(GLint tecla, GLint x, GLint y)
{
	switch(tecla){
		case GLUT_KEY_UP : sinal = -1;
			break;
		case GLUT_KEY_DOWN : sinal = 1;
			break;
		case GLUT_KEY_LEFT : if(angulo<=48)angulo+=12;
			break;
		case GLUT_KEY_RIGHT : if(angulo>=-48)angulo-=12;
			break;
	}
	exibe();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(400,200);
    glutCreateWindow("Carrinho");
    glEnable(GL_DEPTH_TEST);
    glutReshapeFunc(janela);
    glutDisplayFunc(exibe);
    glutKeyboardFunc(Teclas);
    glutSpecialFunc(TeclasEspeciais);
    glutIdleFunc(gira);
    inicia();
    glutMainLoop();
}
