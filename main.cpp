#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>
#include <unistd.h>
#include <stdio.h>
#include <GL/freeglut.h>

double camera_angle_h = 90;
double camera_angle_v = 0;

int drag_x_origin;
int drag_y_origin;
int drag_x_final;
int drag_y_final;
int dragging = 0;
int state2 = 1;
int scaleX = 1.0, scaleY = 1.0, scaleZ = 1.0;
int solid = 10;
int sol =0;
int r, g , b =1;
int  especMaterial =60; //

GLfloat angle = 60, fAspect;
// variaveis para controle da câmera
int rodar = 0.0, cam1 = 0.0, cam2 = 1.0, cam3 = 0.0, verifica = 1, andaX;

// classe que define a posição e angulos das partes quando movimentos são realizados
class Movimento
{
public:
    float tx,ty,tz,rodar_corpo,rodar_perna,rodar_joelho,rodar_torno,rodar_perna2,rodar_joelho2,rodar_torno2;
    Movimento()
    {
        tx = ty = tz = rodar_perna = rodar_joelho = rodar_torno = 0.0;

    }
    void set_movimento(float tx1,float ty1,float tz1,float rodar_corpo1,float rodar_perna1,float rodar_joelho1,float rodar_torno1,float rodar_pernaB,float rodar_joelhoB,float rodar_tornoB)
    {
        tx = tx1;
        ty = ty1;
        tz = tz1;
		rodar_corpo = rodar_corpo1;
        rodar_perna = rodar_perna1;
        rodar_joelho = rodar_joelho1;
        rodar_torno = rodar_torno1;
		rodar_perna2 = rodar_pernaB;
        rodar_joelho2 = rodar_joelhoB;
        rodar_torno2 = rodar_tornoB;
    }
};

// classe que realiza a animação criando um objeto do tipo Movimento
class Animacao
{
public:
    Movimento *Quadros;
    int num_quadros;
    int quadro;
    Animacao(int quadros)
    {
        num_quadros = quadros;
        quadro = 0;
        Quadros = new Movimento[num_quadros];
    }
    Movimento* get_movimento()
    {
        return &(Quadros[quadro]);
    }
    void Next_Quadro()
    {
        quadro++;
        quadro = quadro%num_quadros;
        return;

    }
	void Back_Quadro()
	{
		if (quadro > 5);{
        quadro--;
        quadro = quadro%num_quadros;
		}
        return;
    }

    Movimento* get_movimento(int posi)
    {
        if(posi>=0 && posi < num_quadros)
            return &(Quadros[posi]);
        return NULL;
    }


};
Animacao Perna(30);

void DefineIluminacao (void)
{
    GLfloat luzAmbiente[4]= {0.3,0.3,0.3,1.0}; //resultado da luz refletida no ambiente; é uma luz que vem de todas as direções;
    GLfloat luzDifusa[4]= {0.7,0.7,0.7,1.0}; // luz que vem de uma direção, atinge a superfície e é refletida em todas as direções
    GLfloat luzEspecular[4]= {r, g, b, 1.0}; // luz que vem de uma direção e tende a ser refletida numa única direção;
    GLfloat posicaoLuz[4]={0.0, 50.0, 50.0, 1.0};

// Capacidade de brilho do material
    GLfloat especularidade[4]= {1.0,1.0,1.0,1.0}; //incide em um ponto e espalha em uma unica direção
    GLint especMaterial = 60; //intensidade da reflexão do material
// Define a refletância do material
    glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
// Define a concentração do brilho
    glMateriali(GL_FRONT,GL_SHININESS,especMaterial);
// Ativa o uso da luz ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
// Define os parâmetros da luz de número 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
}

void Inicializa(void)
{
    // localização anguloPartesP1
    //xp1 yp1 zp1 rc rp1  rj1  rt1   rp2  rj2 rt2
    Perna.get_movimento(1)->set_movimento(0.0,0.0,0.0,0.0,15.0,-35.0,0.0,-10.0,0.0,0.0);
    Perna.get_movimento(2)->set_movimento(1.0,0.0,0.0,0.0,25.0,-35.0,0.0,-20.0,0.0,0.0);
    Perna.get_movimento(3)->set_movimento(2.0,0.0,0.0,0.0,25.0,-35.0,0.0,-20.0,0.0,0.0);
    Perna.get_movimento(4)->set_movimento(3.0,0.0,0.0,0.0,15.0,0.0,0.0,0.-10,0.0,0.0);
    Perna.get_movimento(5)->set_movimento(3.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
    Perna.get_movimento(6)->set_movimento(4.0,0.0,0.0,0.0,-10.0,0.0,0.0,15.0,-35.0,0.0);
    Perna.get_movimento(7)->set_movimento(5.0,0.0,0.0,0.0,-20.0,0.0,0.0,25.0,-35.0,0.0);
    Perna.get_movimento(8)->set_movimento(6.0,0.0,0.0,0.0,-20.0,0.0,0.0,25.0,-35.0,0.0);
    Perna.get_movimento(9)->set_movimento(7.0,0.0,0.0,0.0,-10.0,0.0,0.0,15.0,0.0,0.0);
    Perna.get_movimento(10)->set_movimento(8.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
    Perna.get_movimento(11)->set_movimento(9.0,0.0,0.0,0.0,15.0,-35.0,0.0,-10.0,0.0,0.0);
    Perna.get_movimento(12)->set_movimento(10.0,0.0,0.0,0.0,25.0,-35.0,0.0,-20.0,0.0,0.0);
    Perna.get_movimento(13)->set_movimento(11.0,0.0,0.0,0.0,25.0,-35.0,0.0,-20.0,0.0,0.0);
    Perna.get_movimento(14)->set_movimento(12.0,0.0,0.0,0.0,15.0,0.0,0.0,0.-10,0.0,0.0);

	Perna.get_movimento(15)->set_movimento(13.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
    Perna.get_movimento(16)->set_movimento(13.0,0.0,0.0,180.0,0.0,0.0,0.0,0.0,0.0,0.0);

	Perna.get_movimento(17)->set_movimento(12.0,0.0,0.0,180.0,15.0,-35.0,0.0,-10.0,0.0,0.0);
    Perna.get_movimento(18)->set_movimento(11.0,0.0,0.0,180.0,25.0,-35.0,0.0,-20.0,0.0,0.0);
    Perna.get_movimento(19)->set_movimento(10.0,0.0,0.0,180.0,25.0,-35.0,0.0,-20.0,0.0,0.0);
    Perna.get_movimento(20)->set_movimento(9.0,0.0,0.0,180.0,15.0,0.0,0.0,0.-10,0.0,0.0);
	Perna.get_movimento(21)->set_movimento(8.0,0.0,0.0,180.0,0.0,0.0,0.0,0.0,0.0,0.0);
    Perna.get_movimento(22)->set_movimento(7.0,0.0,0.0,180.0,-10.0,0.0,0.0,15.0,-35.0,0.0);
    Perna.get_movimento(23)->set_movimento(6.0,0.0,0.0,180.0,-20.0,0.0,0.0,25.0,-35.0,0.0);
    Perna.get_movimento(24)->set_movimento(5.0,0.0,0.0,180.0,-20.0,0.0,0.0,25.0,-35.0,0.0);
    Perna.get_movimento(25)->set_movimento(4.0,0.0,0.0,180.0,-10.0,0.0,0.0,15.0,0.0,0.0);
	Perna.get_movimento(26)->set_movimento(3.0,0.0,0.0,180.0,15.0,-35.0,0.0,-10.0,0.0,0.0);
    Perna.get_movimento(27)->set_movimento(2.0,0.0,0.0,180.0,25.0,-35.0,0.0,-20.0,0.0,0.0);
    Perna.get_movimento(28)->set_movimento(1.0,0.0,0.0,180.0,25.0,-35.0,0.0,-20.0,0.0,0.0);
    Perna.get_movimento(29)->set_movimento(0.0,0.0,0.0,180.0,15.0,0.0,0.0,0.-10,0.0,0.0);

    glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, 1, 0.5, 900);
    glMatrixMode(GL_MODELVIEW);

    glColor3f(0.0, 0.0,0.0);
    angle = 60;

    r = 1.0;
    g = 1.0;
    b = 1.0;
    especMaterial = 60;

// Define a cor de fundo da janela de visualização como branca
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
// Habilita a definição da cor do material a partir da cor corrente
    glEnable(GL_COLOR_MATERIAL);
//Habilita o uso de iluminação
    glEnable(GL_LIGHTING);
// Habilita a luz de número 0
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
// Habilita o depth-buffering
    glEnable(GL_DEPTH_TEST);
// Habilita o modelo de colorização de Gouraud
    glShadeModel(GL_FLAT);
    DefineIluminacao();

    }
/*****************ILUMINACAO*********************************/
// Inicializa parâmetros de rendering

/*****************************************/
void Boneco_Lata()
{

	// cria o chão
    glColor3f(0.0, 1.0, 0.0);
    glPushMatrix();
    glTranslated(0.0, 0.0, 10.0);
    glBegin(GL_POLYGON);
    glVertex3f(50.0, 0.0, 50.0);
    glVertex3f(50.0, 0.0, -50.0);
    glVertex3f(-50.0, 0.0, -50.0);
    glVertex3f(-50.0, 0.0, 50.0);
    glEnd();
    glPopMatrix();

    glTranslatef(Perna.get_movimento()->tx, Perna.get_movimento()->ty, Perna.get_movimento()->tz);

	// roda o corpo todo em todo do y
	glRotated(Perna.get_movimento()->rodar_corpo, 0.0, 1.0, 0.0);

	// tronco - usa uma matrix individual
        glPushMatrix();
        if(sol==0){
	    glColor3f(0.5, 0.5, 0.5);
    	GLUquadricObj* qt = gluNewQuadric();
    	gluQuadricDrawStyle(qt,GLU_LINE);
    	glTranslated(0.0, 5.0, 0.0);
    	glRotated(-90, 1.0, 0.0, 0.0);
    	gluCylinder( qt, 1.3, 1.3, 3.0, solid, solid);
    	gluDeleteQuadric(qt);
        }
        else{
            glColor3f(0.5, 0.5, 0.5);
            glTranslated(0.0, 5.0, 0.0);
            glRotated(-90, 1.0, 0.0, 0.0);
            glutSolidCylinder(1.3, 3.0, solid, solid);
        }
    glPopMatrix();

	// pescoço e cabeça - usam uma matrix para os dois
    glPushMatrix();
		glTranslated(0.0, 8.0, 0.0);
		if(sol==0){
		glColor3f(0.5, 0.5, 0.5);
    	GLUquadricObj* qc = gluNewQuadric();
    	gluQuadricDrawStyle(qc,GLU_LINE);
    	glRotated(-90.0, 1.0, 0.0, 0.0);
    	gluCylinder( qc, 0.2, 0.2, 1.0, solid, solid);
    	gluDeleteQuadric(qc);
		}
		else{
            glColor3f(0.5, 0.5, 0.5);
            glRotated(-90.0, 1.0, 0.0, 0.0);
            glutSolidCylinder(0.2, 0.4, solid, solid);
		}
    	glTranslated(0.0, 0.0, 1.0);
    	glColor3f(0.0, 0.0, 1.0);
    	if(sol==0){
    	glutWireSphere(0.1, solid, solid);
    	glutWireSphere(0.8, solid, solid);
    	}
    	else{
            glutSolidSphere(0.1, solid, solid);
            glutSolidSphere(0.8, solid, solid);
            glColor3f(1.0, 0.0, 0.0);
    	}
    glPopMatrix();

	// perna 1 - uma matrix
	glPushMatrix();
	glTranslated(0.0, 5.0, 0.7);
	glRotated(Perna.get_movimento()->rodar_perna, 0.0, 0.0, 1.0);
	if(sol==0){
	glColor3f(0.0,0.0,1.0);
	GLUquadricObj* qp1 = gluNewQuadric();
	gluQuadricDrawStyle(qp1,GLU_LINE);
	glRotated(90.0, 1.0, 0.0, 0.0);
	gluCylinder(qp1, 0.2, 0.2, 1.5, solid, solid);
	gluDeleteQuadric(qp1);
	}
        else{
            glColor3f(0.0, 0.0, 1.0);
            glRotated(90.0, 1.0,0.0,0.0);
            glutSolidCylinder(0.2, 1.2, solid, solid);  //perna 1 parte cima
        }

		//joelho1 - uma matrix
		glTranslated(0.0, 0.0, 1.5);
		glPushMatrix();
		glColor3f(0.5,0.5,0.5);
		glRotated(Perna.get_movimento()->rodar_joelho, 0.0, 1.0, 0.0);
		if(sol==0){
		glutWireSphere(0.1, solid, solid);
		glutWireSphere(0.5, solid, solid);
		}
		else{
            glutSolidSphere(0.1, solid, solid);
            glutSolidSphere(0.5, solid, solid);
			}
        // batata da perna1 - uma matrix
        glTranslated(0.0,0.0,0.5);
        glPushMatrix();
        if(sol==0){
        glColor3f(0.0,0.0,1.0);
        GLUquadricObj* qbp1 = gluNewQuadric();
        gluQuadricDrawStyle(qbp1,GLU_LINE);
        gluCylinder(qbp1, 0.2, 0.2, 1.0, solid, solid);
        gluDeleteQuadric(qbp1);
        }
            else{
                glColor3f(0.0, 0.0, 1.0);
                glutSolidCylinder(0.2, 1.0, solid, solid);
            }
        // pé1 - uma matrix
        glTranslated(0.4,0.0,1.0);
        glPushMatrix();
        glRotated(90.0,1.0,0.0,0.0);
        glScaled(0.6,0.1,0.3);
				if(sol==0){
				glutWireCube(2.0);
				}
				else
                    glutSolidCube(2.0);
                    glPopMatrix();
                    glPopMatrix();
                    glPopMatrix();
                    glPopMatrix();

	// perna 2 - uma matrix
	glPushMatrix();
	glTranslated(0.0, 5.0, -0.7);
	glRotated(Perna.get_movimento()->rodar_perna2, 0.0, 0.0, 1.0);
	if(sol==0){
	glColor3f(0.0,0.0,1.0);
	GLUquadricObj* qp2 = gluNewQuadric();
	gluQuadricDrawStyle(qp2,GLU_LINE);
	glRotated(90.0, 1.0, 0.0, 0.0);
	gluCylinder(qp2, 0.2, 0.2, 1.5, solid, solid);
	gluDeleteQuadric(qp2);
	}
        else{
            //glTranslated(0.0, 5.0, -0.7);
            glRotated(Perna.get_movimento()->rodar_perna2, 0.0, 0.0, 1.0);
            glColor3f(0.0, 0.0, 1.0);
            glRotated(90.0, 1.0,0.0,0.0);
            glutSolidCylinder(0.2, 1.2, solid, solid); //perna 2 parte cima
        }

		//joelho2 - uma matrix
		glTranslated(0.0, 0.0, 1.5);
		glPushMatrix();
		glColor3f(0.5,0.5,0.5);
		glRotated(Perna.get_movimento()->rodar_joelho2, 0.0, 1.0, 0.0);
		if(sol==0){
		glutWireSphere(0.1, solid, solid);
		glutWireSphere(0.5, solid, solid);
		}
		else{
            glutSolidSphere(0.1, solid, solid);
            glutSolidSphere(0.5, solid, solid);
		}
			// batata da perna2 - uma matrix
			glTranslated(0.0,0.0,0.5);
			glPushMatrix();
			if(sol==0){
			glColor3f(0.0,0.0,1.0);
			GLUquadricObj* qbp2 = gluNewQuadric();
			gluQuadricDrawStyle(qbp2,GLU_LINE);
			gluCylinder(qbp2, 0.2, 0.2, 1.0, solid, solid);
			gluDeleteQuadric(qbp2);
			}
			else{
                glColor3f(0.0, 0.0, 1.0);
                glutSolidCylinder(0.2, 1.0, solid, solid);
			}


				// pé2 - uma matrix
				glTranslated(0.4,0.0,1.0);
				glPushMatrix();
				glRotated(90.0,1.0,0.0,0.0);
				glScaled(0.6,0.1,0.3);
				if(sol==0){
				glutWireCube(2.0);
				}
				else
                    glutSolidCube(2.0);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();

	// ombro e braço 1
        glPushMatrix();
		glTranslated(0.0, 8.0, 1.5);
		glRotated(Perna.get_movimento()->rodar_perna2, 0.0, 0.0, 1.0);
		glColor3f(0.0, 0.0, 1.0);
		if(sol==0){
    	glutWireSphere(0.1, solid, solid);
    	glutWireSphere(0.5, solid, solid);
		}
		else{
            glutSolidSphere(0.1, solid, solid);
            glutSolidSphere(0.5, solid, solid);
		}
		// antebraço 1
		if(sol==0){
		glColor3f(0.5, 0.5, 0.5);
    	GLUquadricObj* qab1 = gluNewQuadric();
    	gluQuadricDrawStyle(qab1,GLU_LINE);
    	glRotated(90.0, 1.0, 0.0, 0.0);
    	gluCylinder( qab1, 0.2, 0.2, 1.0, solid, solid);
    	gluDeleteQuadric(qab1);
		}
		else{
            glColor3f(0.5, 0.5, 0.5);
            glRotated(90.0, 2.0, 0.0, 0.0);
            //glScaled(0.0, 0.0, 1.0);
            glutSolidCylinder(0.2, 1.0, solid, solid);
		}

		// cotovelo 1
		glPushMatrix();
			glTranslated(0.0,0.0,1.0);
			glColor3f(0.0, 0.0, 1.0);
			if(sol==0){
    		glutWireSphere(0.1, solid, solid);
    		glutWireSphere(0.3, solid, solid);
			}
			else{
                glutSolidSphere(0.1, solid, solid);
                glutSolidSphere(0.3, solid, solid);
			}
			// braço 1
			glPushMatrix();
			if(sol==0){
				glColor3f(0.5, 0.5, 0.5);
    			GLUquadricObj* qb1 = gluNewQuadric();
    			gluQuadricDrawStyle(qb1,GLU_LINE);
    			gluCylinder( qb1, 0.1, 0.1, 1.0, solid, solid);
    			gluDeleteQuadric(qb1);
			}
			else{
                glColor3f(0.5, 0.5, 0.5);
                glutSolidCylinder(0.1, 1.0, solid, solid);

			}
				// mao 1
				glTranslated(0.0,0.0,1.0);
				glPushMatrix();
                glColor3f(0.0, 0.0, 1.0);
                glScaled(0.3,0.1,0.3);
                if(sol==0){
                glutWireCube(2.0);
                }
                else
                    glutSolidCube(2.0);
                    glPopMatrix();
                    glPopMatrix();
                    glPopMatrix();
                    glPopMatrix();

	// ombro e braço 2
        glPushMatrix();
		glTranslated(0.0, 8.0, -1.5);
		glRotated(Perna.get_movimento()->rodar_perna, 0.0, 0.0, 1.0);
		glColor3f(0.0, 0.0, 1.0);
		if(sol==0){
    	glutWireSphere(0.1, solid, solid);
    	glutWireSphere(0.5, solid, solid);
		}
		else{
            glutSolidSphere(0.1, solid, solid);
            glutSolidSphere(0.5, solid, solid);
		}
		// antebraço 1
		if(sol==0){
		glColor3f(0.5, 0.5, 0.5);
    	GLUquadricObj* qab2 = gluNewQuadric();
    	gluQuadricDrawStyle(qab2,GLU_LINE);
    	glRotated(90.0, 1.0, 0.0, 0.0);
    	gluCylinder( qab2, 0.2, 0.2, 1.0, solid, solid);
    	gluDeleteQuadric(qab2);
		}
		else{
            glColor3f(0.5, 0.5, 0.5);
            glRotated(90.0, 1.0, 0.0, 0.0);
            glutSolidCylinder(0.2, 1.0, solid, solid);
		}

		// cotovelo 1
		glPushMatrix();
			glTranslated(0.0,0.0,1.0);
			glColor3f(0.0, 0.0, 1.0);
			if(sol==0){
    		glutWireSphere(0.1, solid, solid);
    		glutWireSphere(0.3, solid, solid);
			}
			else{
                glutSolidSphere(0.1, solid, solid);
                glutSolidSphere(0.3, solid, solid);
			}
			// braço 1
			glPushMatrix();
			if(sol==0){
            glColor3f(0.5, 0.5, 0.5);
            GLUquadricObj* qb2 = gluNewQuadric();
            gluQuadricDrawStyle(qb2,GLU_LINE);
            gluCylinder( qb2, 0.1, 0.1, 1.0, solid, solid);
            gluDeleteQuadric(qb2);
			}
                else{
                    glColor3f(0.5, 0.5, 0.5);
                    glutSolidCylinder(0.1, 1.0, solid, solid);
                }
				// mao 1
            glTranslated(0.0,0.0,1.0);
            glPushMatrix();
            glColor3f(0.0, 0.0, 1.0);
            glScaled(0.3,0.1,0.3);
            if (sol ==0){
            glutWireCube(2.0);
            }
            else{
                glutSolidCube(2.0);
            }
            glPopMatrix();
			glPopMatrix();
            glPopMatrix();
            glPopMatrix();
}

void Desenha(void)
{
    //DefineIluminacao();
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glClear (GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(10,10,20, andaX,0,0, 0,1,0);
	if (verifica == 0){
		glRotated(rodar,cam1,cam2,cam3);
		verifica == 1;
	}
	glRotated(camera_angle_v, 1.0, 0.0, 0.0);
    glRotated(camera_angle_h, 0.0, 1.0, 0.0);
    glScalef(scaleX, scaleY, scaleZ);

    glColor3f(0.5, 0.5,0.5);
    glPushMatrix();

		glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);

    Boneco_Lata();

    glPopMatrix();

    glutSwapBuffers();

    Boneco_Lata();
}




void AlteraTamanhoJanela (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    if(h == 0) h = 1;

}

void Timer(int value)
{
    if(value > 0)
    {
        value--;
        Perna.Next_Quadro();
        //glutTimerFunc(200,Timer,value);
        glutPostRedisplay();
    }
	else if(value < 0)
    {
        value++;
        Perna.Back_Quadro();
        //glutTimerFunc(200,Timer,value);
        glutPostRedisplay();
    }
}

void Teclado(unsigned char key, int x, int y)
{

	if (key == '-')
	{
		if(scaleX >= 2.0 && scaleY >= 2.0 && scaleZ >= 2.0)
		scaleX -= 1.0, scaleY -= 1.0, scaleZ -= 1.0;
	}
	if (key == '+')
	{
		if(scaleX <= 3.0 && scaleY <= 3.0 && scaleZ <= 3.0)
		scaleX += 1.0, scaleY += 1.0, scaleZ += 1.0;
	}
	// cameras
	if (key == '1')
	{
		rodar = 0.0;
		cam1 = 0.0;
		cam2 = 1.0;
		cam3 = 0.0;
		verifica = 0;
	}
	if (key == '2')
	{
		rodar = 90.0;
		cam1 = 0.0;
		cam2 = 1.0;
		cam3 = 0.0;
		verifica = 0;
	}
	if (key == '3')
	{
		rodar = 90.0;
		cam1 = 1.0;
		cam2 = 0.0;
		cam3 = 0.0;
		verifica = 0;
	}
	if (key == '4')
	{
		rodar = 90.0;
		cam1 = 0.0;
		cam2 = 1.0;
		cam3 = 1.0;
		verifica = 0;
	}
	if (key == '5')
	{
		rodar = 90.0;
		cam1 = 1.0;
		cam2 = 1.0;
		cam3 = 0.0;
		verifica = 0;
	}
	if (key == '6')
	{
		rodar = 90.0;
		cam1 = 1.0;
		cam2 = 0.0;
		cam3 = 1.0;
		verifica = 0;
	}

	if (key == '>')
	{
		andaX += 1;
	}
	if (key == '<')
	{
		andaX -= 1;
	}

	// padrão
	if (key == 'a')
    {
        rodar -= 5 ;
        rodar = rodar%360;
		verifica = 0;
    }
    if (key == 'd')
    {
        rodar += 5 ;
        rodar = rodar%360;
		verifica = 0;
    }
    if(key == 'w')
    {
        Perna.Next_Quadro();
        glutTimerFunc(200,Timer,Perna.num_quadros);

    }
	/**if(key == 's')
    {
        Perna.Back_Quadro();
        //glutTimerFunc(-200,Timer,Perna.num_quadros);

    }
    **/
    if(key == 'b')
    {
            sol = 0;
    }

    if(key == 'l')
    {

            sol = 1;

    }

    glutPostRedisplay();

}

void MouseClick (int button, int state, int x, int y)
{

    if (state == GLUT_DOWN){
		drag_x_origin = x;
        drag_y_origin = y;
	}
    if (state == GLUT_UP){

	}

}

void MouseAndandoPressionado (int x, int y)
{
    //printf("Mouse ANDANDO pressionado na janela. Posição: (%d, %d)\n", x,y);
	camera_angle_v += (y - drag_y_origin)*0.2;
    camera_angle_h += (x - drag_x_origin)*0.2;
	drag_y_origin = y;
	drag_x_origin = x;
	//printf("(%f, %f)\n", camera_angle_v,camera_angle_h);
	glutPostRedisplay();
}

void mouseWheel(int button, int dir, int x, int y)
{

    if (dir > 0)
    {
        if(scaleX <= 3.0 && scaleY <= 3.0 && scaleZ <= 3.0)
		scaleX += 1.0, scaleY += 1.0, scaleZ += 1.0;
		glutPostRedisplay();
    }
    else
    {
		printf("aumentando");
        if(scaleX >= 2.0 && scaleY >= 2.0 && scaleZ >= 2.0)
		scaleX -= 1.0, scaleY -= 1.0, scaleZ -= 1.0;
		glutPostRedisplay();
    }

    return;
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);

    glutInitWindowSize (800, 800);

    glutInitWindowPosition ((1280 - 800)/2, (800 - 800)/2);

    glutCreateWindow ("Robô");

	//glutBeginText2i(100,10);

    glutDisplayFunc(Desenha);

    glutReshapeFunc(AlteraTamanhoJanela);

    glutKeyboardFunc(Teclado);

	// mouseScroll
	glutMouseWheelFunc(mouseWheel);

    // Click em um botão
    glutMouseFunc(MouseClick);

	// movimento SEM botão pressionado
    glutMotionFunc(MouseAndandoPressionado);



    Inicializa();

    glutMainLoop();
    return 0;
}
