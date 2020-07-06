

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define GL_SILENCE_DEPRECATION

#define BASE_HEIGHT  0.25
#define BASE_WIDE    0.05
#include <GL/freeglut.h>

#include "RgbImage.h"
#include "RgbImage.h"
#include "materiais.h"

//--------------------------------- Definir cores
#define BLUE     0.0, 0.0, 1.0, 1.0
#define RED		 1.0, 0.0, 0.0, 1.0
#define YELLOW	 1.0, 1.0, 0.0, 1.0
#define GREEN    0.0, 1.0, 0.0, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define PI		 3.14159


//================================================================================
//===========================================================Variaveis e constantes

GLfloat tam = 1.0;
char     texto[300];

static GLfloat vertices[] = {
	//…………………………………………………………………………………………………… x=tam (Costa)
		-tam,  tam,  -tam,	// 0 
		-tam,   tam,  tam,	// 1 
		-tam,   4 * tam, tam,	// 2 
		-tam,  4 * tam, -tam,	// 3 
	//…………………………………………………… Cima inferior
		 -tam,  tam - 0.1,  tam,	// 4
		-tam,  tam - 0.1, -tam,	// 5 
		 tam,  tam - 0.1, -tam,	// 6 
		 tam,  tam - 0.1,  tam,	// 7 
	//……………………………………………………… (Cima
		-tam,  tam,  tam,	// 8 
		-tam,  tam, -tam,	// 9 
		 tam,  tam, -tam,	// 10 
		 tam,  tam,  tam,	// 11 
	//........................ Perna esquerda tras
		 -tam + 0.2,tam,-tam,  //12
		 -tam + 0.4,tam,-tam,  //13
		 -tam + 0.2,tam,-tam + 0.2, //14
		 -tam + 0.4,tam,-tam + 0.2, //15
		 -tam + 0.2,-tam,-tam,  //16
		 -tam + 0.4,-tam,-tam,  //17
		 -tam + 0.2,-tam,-tam + 0.1, //18
		 -tam + 0.4,-tam,-tam + 0.1, //19
	//.......................... Perna direita tras
		 tam - 0.2,tam,-tam,  //20
		 tam - 0.4,tam,-tam,  //21
		 tam - 0.2,tam,-tam + 0.2, //22
		 tam - 0.4,tam,-tam + 0.2, //23
		 tam - 0.2,-tam,-tam,  //24
		 tam - 0.4,-tam,-tam,  //25
		 tam - 0.2,-tam,-tam + 0.1, //26
		 tam - 0.4,-tam,-tam + 0.1, //27
	//........................ Perna esquerda frente
		 -tam + 0.2,tam,tam,  //28
		 -tam + 0.4,tam,tam,  //29
		 -tam + 0.2,tam,tam - 0.2, //30
		 -tam + 0.4,tam,tam - 0.2, //31
		 -tam + 0.2,-tam,tam,  //32
		 -tam + 0.4,-tam,tam,  //33
		 -tam + 0.2,-tam,tam - 0.1, //34
		 -tam + 0.4,-tam,tam - 0.1, //35
	//........................ Perna direita frente
		 tam - 0.2,tam,tam,  //36
		 tam - 0.4,tam,tam,  //37
		 tam - 0.2,tam,tam - 0.2, //38
		 tam - 0.4,tam,tam - 0.2, //39
		 tam - 0.2,-tam,tam,  //40
		 tam - 0.4,-tam,tam,  //41
		 tam - 0.2,-tam,tam - 0.1, //42
		 tam - 0.4,-tam,tam - 0.1, //43
	//........................ COSTA frente

		 -tam+0.2,  tam,  -tam,	//44 
		-tam+0.2,   tam,  tam,	// 45 
		-tam+0.2,   4 * tam, tam,	// 46 
		-tam+0.2,  4 * tam, -tam,	// 47
};

static GLfloat normais[] = {
	//…………………………………………………………………………………………………… x=tam (Esquerda)
	  -1.0,  0.0,  0.0,
	  -1.0,  0.0,  0.0,
	  -1.0,  0.0,  0.0,
	-1.0,  0.0,  0.0,
	//…………………………………………………………………………………………………… x=tam (Cima_inferior)
	  0.0,  1.0,  0.0,
	  0.0,  1.0,  0.0,
	  0.0,  1.0,  0.0,
	  0.0,  1.0,  0.0,
	  //…………………………………………………………………………………………………… y=tam (Cima)
	 0.0,  1.0,  0.0,
	 0.0,  1.0,  0.0,
	 0.0,  1.0,  0.0,
	 0.0,  1.0,  0.0,
	 //.................................................Perna esquerda tras
	 0.0,  1.0,  0.0,
	  0.0,  1.0,  0.0,
	  0.0,  1.0,  0.0,
	  0.0,  1.0,  0.0,
	  0.0,  -1.0,  0.0,
	  0.0,  -1.0,  0.0,
	  0.0,  -1.0,  0.0,
	  0.0,  -1.0,  0.0,
	  //.................................................Perna direita tras
	 0.0,  1.0,  0.0,
	  0.0,  1.0,  0.0,
	  0.0,  1.0,  0.0,
	  0.0,  1.0,  0.0,
	  0.0,  -1.0,  0.0,
	  0.0,  -1.0,  0.0,
	  0.0,  -1.0,  0.0,
	  0.0,  -1.0,  0.0,
	  //.................................................Perna esquerda frente
	 0.0,  1.0,  0.0,
	  0.0,  1.0,  0.0,
	  0.0,  1.0,  0.0,
	  0.0,  1.0,  0.0,
	  0.0,  -1.0,  0.0,
	  0.0,  -1.0,  0.0,
	  0.0,  -1.0,  0.0,
	  0.0,  -1.0,  0.0,
	  //.................................................Perna direita frente
	 0.0,  1.0,  0.0,
	  0.0,  1.0,  0.0,
	  0.0,  1.0,  0.0,
	  0.0,  1.0,  0.0,
	  0.0,  -1.0,  0.0,
	  0.0,  -1.0,  0.0,
	  0.0,  -1.0,  0.0,
	  0.0,  -1.0,  0.0,
	  //…………………………………………………………………………………………………… x=tam (Esquerda)
	  1.0,  0.0,  0.0,
	  1.0,  0.0,  0.0,
	  1.0,  0.0,  0.0,
	1.0,  0.0,  0.0,
};
//------------------------------------------------------------ Cores
static GLfloat cor[] = {
	//…………………………………………………………………………………………………… x=tam (Esquerda) - Blue
	  0.36,  0.25, 0.20,	// 0 
	  0.36,  0.25, 0.20,	// 1 
	  0.36,  0.25, 0.20,	// 2 
	  0.36,  0.25, 0.20,	// 3 
	//…………………………………………………………………………………………………… x=2*tam (Direita) - Green
	  0.36,  0.25, 0.20,	// 0 
	  0.36,  0.25, 0.20,	// 1 
	  0.36,  0.25, 0.20,	// 2 
	  0.36,  0.25, 0.20,	// 3    
	//…………………………………………………………………………………………………… y=tam (Cima) - Blue
	  0.36,  0.25, 0.20,	// 0 
	  0.36,  0.25, 0.20,	// 1 
	  0.36,  0.25, 0.20,	// 2 
	  0.36,  0.25, 0.20,	// 3   

	//…………………………………………………………………………………………………… y=tam (Perna esquerda tras) - Blue
	  0.36,  0.25, 0.20,	// 0 
	  0.36,  0.25, 0.20,	// 1 
	  0.36,  0.25, 0.20,	// 2 
	  0.36,  0.25, 0.20,	// 3 
	  0.36,  0.25, 0.20,	// 0 
	  0.36,  0.25, 0.20,	// 1 
	  0.36,  0.25, 0.20,	// 2 
	  0.36,  0.25, 0.20,	// 3  
	  //…………………………………………………………………………………………………… y=tam (Perna direita tras) - Blue
	  0.36,  0.25, 0.20,	// 0 
	  0.36,  0.25, 0.20,	// 1 
	  0.36,  0.25, 0.20,	// 2 
	  0.36,  0.25, 0.20,	// 3 
	  0.36,  0.25, 0.20,	// 0 
	  0.36,  0.25, 0.20,	// 1 
	  0.36,  0.25, 0.20,	// 2 
	  0.36,  0.25, 0.20,	// 3   

	  //…………………………………………………………………………………………………… y=tam (Perna esquerda frente) - Blue
	  0.36,  0.25, 0.20,	// 0 
	  0.36,  0.25, 0.20,	// 1 
	  0.36,  0.25, 0.20,	// 2 
	  0.36,  0.25, 0.20,	// 3 
	  0.36,  0.25, 0.20,	// 0 
	  0.36,  0.25, 0.20,	// 1 
	  0.36,  0.25, 0.20,	// 2 
	  0.36,  0.25, 0.20,	// 3  

	  //…………………………………………………………………………………………………… y=tam (Perna direita frente) - Blue
	  0.36,  0.25, 0.20,	// 0 
	  0.36,  0.25, 0.20,	// 1 
	  0.36,  0.25, 0.20,	// 2 
	  0.36,  0.25, 0.20,	// 3 
	  0.36,  0.25, 0.20,	// 0 
	  0.36,  0.25, 0.20,	// 1 
	  0.36,  0.25, 0.20,	// 2 
	  0.36,  0.25, 0.20,	// 3 
	  //…………………………………………………………………………………………………… x=tam (Esquerda) - Blue
	  0.36,  0.25, 0.20,	// 0 
	  0.36,  0.25, 0.20,	// 1 
	  0.36,  0.25, 0.20,	// 2 
	  0.36,  0.25, 0.20,	// 3 
};

//-------------------------------------------------------------Textura
static GLfloat arrayTexture[] = {
	//…………………………………………………………………………………………………… x=tam (Costa)
		0,0, 1,0, 1,1, 0,1, //0 1 2 3
		
	//…………………………………………………… Cima inferior
		0,0, 1,0, 1,1, 0,1, //4 5 6 7
	//……………………………………………………… (Cima
		0,0, 1,0, 1,1, 0,1, //8 9 10 11
	//........................ Perna esquerda tras
		0,0, 1,0, 0,0, 1,0, //12 13 14 15
		0,0, 1,0, 0,0, 1,0, //16 17 18 19
	//.......................... Perna direita tras
		1,1, 0,1, 1,1, 0,1, //20 21 22 23
		1,1, 0,1, 1,1, 0,1, //24 25 26 27

	//........................ Perna esquerda frente
		0,0, 1,0, 0,0, 1,0, //28 29 30 31
		0,0, 1,0, 0,0, 1,0, //32 33 34 35

	//........................ Perna direita frente
		1,1, 0,1, 1,1, 0,1, //36 37 38 39
		1,1, 0,1, 1,1, 0,1, //40 41 42 43
		//…………………………………………………………………………………………………… x=tam (Costa)
		0,0, 1,0, 1,1, 0,1, //0 1 2 3
};

//=========================================================== FACES DA CADEIRA
static GLuint     cima[] = { 8, 11, 10,  9 };       // regra da mao direita
static GLuint     costa[] = { 0, 1, 2, 3 };
static GLuint     costafrente[] = { 44, 45, 46, 47 };
static GLuint     costafrente1[] = { 44, 45, 1, 0 };
static GLuint     costafrente2[] = { 44, 47, 3, 0 };
static GLuint     costafrente3[] = { 47, 46, 2, 3 };
static GLuint     costafrente4[] = { 45, 46, 2, 1 };
static GLuint     cima_inferior[] = { 4, 7, 6, 5 };
static GLuint     ligacao_cima_inferior1[] = { 4, 5, 9 , 8 };
static GLuint     ligacao_cima_inferior2[] = { 8, 11, 7, 4 };
static GLuint     ligacao_cima_inferior3[] = { 11, 10, 6, 7 };
static GLuint     ligacao_cima_inferior4[] = { 9, 10, 6, 5 };
static GLuint perna_esquerda_tras1[] = { 12,13,25,24 };
static GLuint perna_esquerda_tras2[] = { 12,14,26,24 };
static GLuint perna_esquerda_tras3[] = { 14,15,27,26 };
static GLuint perna_esquerda_tras4[] = { 13,15,27,25 };
static GLuint perna_direita_tras1[] = { 20,21,17,16 };
static GLuint perna_direita_tras2[] = { 20,22,16,18 };
static GLuint perna_direita_tras3[] = { 22,23,19,18 };
static GLuint perna_direita_tras4[] = { 21,23,19,17 };
static GLuint perna_esquerda_frente1[] = { 28,29,41,40 };
static GLuint perna_esquerda_frente2[] = { 28,40,42,30 };
static GLuint perna_esquerda_frente3[] = { 30,31,43,42 };
static GLuint perna_esquerda_frente4[] = { 29,31,43,41 };
static GLuint perna_direita_frente1[] = { 36,37,33,32 };
static GLuint perna_direita_frente2[] = { 36,38,34,32 };
static GLuint perna_direita_frente3[] = { 38,39,35,34 };
static GLuint perna_direita_frente4[] = { 37,39,35,33 };

//========================================================================== Texturas(2)
GLuint   texture[3];
RgbImage imag;


//------------------------------------------------------------ Objectos (sistema coordenadas)
GLint		wScreen = 1600, hScreen = 800;			//.. janela (pixeis)
GLfloat		xC = 30.0, yC = 30.0, zC = 30.0;		//.. Mundo  (unidades mundo)

//------------------------------------------------------------ Visualizacao/Observador 
GLfloat  rVisao = 20, aVisao = 0.5 * PI, incVisao = 0.05;
GLfloat  obsP[] = { -10.0 + rVisao * cos(aVisao), 25.0,  rVisao * sin(aVisao) };
GLfloat  angZoom = 90;
GLfloat  incZoom = 3;

GLfloat xPosition = 0, yPosition = 0, zPosition = 0, angle = 0;
GLint subir = 1;
GLint incrementaR = 1;
GLint incrementaG = 1;
GLint incrementaB = 1;
GLint incrementaR2 = 1;
GLint incrementaG2 = 1;
GLint incrementaB2 = 1;
GLint chao = 1;

//------------------------------------------------------------ Materiais 
GLint material = 10;
GLint materialcadeira = 16;
GLint incrementamaterial = 0;
GLint incrementador = 0;
GLint incrementador2 = 0;
GLint incrementador3 = 0;
GLint transp = 0;

//------------------------------------------------------------ Iluminacao Ambiente
GLint   dia = 0;
GLfloat intensidade = 0.2;
GLfloat luzGlobalCorAmb[4] = { intensidade,intensidade,intensidade,1.0 };   // 


//…………………………………………………………………………………………………………………………………………… Lanterna (local) - FOCO
GLint   ligaFoco = 1;
GLfloat rFoco = 1.1, aFoco = aVisao;
GLfloat focoPini[] = { xC, 3 * yC / 5, 0.0, 1.0 };
GLfloat focoDir[] = { -xC, -yC/2, 0.0 };
GLfloat focoExp = 30.0;
GLfloat focoCut = 60.0;

GLfloat focoCorDif[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat focoCorEsp[4] = { 1.0, 1.0, 1.0, 1.0 };


//…………………………………………………………………………………………………………………………………………… Lanterna (local) - FOCO2
GLint   ligaFoco2 = 1;
GLfloat focoPini2[] = { -xC, 3*yC / 5, 0.0, 1.0 };
GLfloat focoDir2[] = {xC, -yC/2, 0.0 };
GLfloat focoExp2 = 30.0;
GLfloat focoCut2 = 60.0;

GLfloat focoCorDif2[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat focoCorEsp2[4] = { 1.0, 1.0, 1.0, 1.0 };



//…………………………………………………………………………………………………………………………………………… Luz teto - PONTUAL
GLint   ligaPontual = 1;
GLfloat   linear_attenuation = 1.0f;
GLfloat PontualPini[] = { 0, yC, 0.0, 1.0 };
GLfloat PontualCorAmb[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat PontualCorDif[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat PontualCorEsp[4] = { 1.0, 1.0, 1.0, 1.0 };

//==================================================================================== INICIAR TEXTURA
void initTexturas()
{
	//----------------------------------------- Chao
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	imag.LoadBmpFile("pedra.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	//-----------------------------------------  Cadeira
	glGenTextures(1, &texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	imag.LoadBmpFile("madeira.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	//-----------------------------------------  Quadro
	glGenTextures(1, &texture[2]);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	imag.LoadBmpFile("imag2.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

}


//========================================================= ILUMINACAO                 
void initLights(void) {
	//…………………………………………………………………………………………………………………………………………… Ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCorAmb);
	//…………………………………………………………………………………………………………………………………………… Foco
	glLightfv(GL_LIGHT1, GL_POSITION, focoPini);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, focoDir);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, focoExp);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, focoCut);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, focoCorDif);
	glLightfv(GL_LIGHT1, GL_SPECULAR, focoCorEsp);

	if (ligaFoco)
		glEnable(GL_LIGHT1);
	else
		glDisable(GL_LIGHT1);

	//…………………………………………………………………………………………………………………………………………… Foco2
	glLightfv(GL_LIGHT2, GL_POSITION, focoPini2);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, focoDir2);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, focoExp2);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, focoCut2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, focoCorDif2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, focoCorEsp2);

	if (ligaFoco2)
		glEnable(GL_LIGHT2);
	else
		glDisable(GL_LIGHT2);


	//........................................................ Pontual
	glLightfv(GL_LIGHT3, GL_POSITION, PontualPini);
	glLightfv(GL_LIGHT3, GL_AMBIENT, PontualCorAmb);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, PontualCorDif);
	glLightfv(GL_LIGHT3, GL_SPECULAR, PontualCorEsp);
	glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, linear_attenuation);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.1);

	if (ligaPontual)
		glEnable(GL_LIGHT3);
	else
		glDisable(GL_LIGHT3);

}

//========================================================= MATERIAIS
void initMaterials(int material) {
	
	switch (material) {
	case 0: //……………………………………………………………………………………………esmerald
		glMaterialfv(GL_FRONT, GL_AMBIENT, esmeraldAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, esmeraldDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, esmeraldSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, esmeraldCoef);
		break;
	case 1: //……………………………………………………………………………………………jade
		glMaterialfv(GL_FRONT, GL_AMBIENT, jadeAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, jadeDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, jadeSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, jadeCoef);
		break;
	case 2: //……………………………………………………………………………………………obsidian
		glMaterialfv(GL_FRONT, GL_AMBIENT, obsidianAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, obsidianDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, obsidianSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, obsidianCoef);
		break;
	case 3: //……………………………………………………………………………………………pearl
		glMaterialfv(GL_FRONT, GL_AMBIENT, pearlAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, pearlDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, pearlSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, pearlCoef);
		break;
	case 4: //……………………………………………………………………………………………ruby
		glMaterialfv(GL_FRONT, GL_AMBIENT, rubyAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, rubyDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, rubySpec);
		glMaterialf(GL_FRONT, GL_SHININESS, rubyCoef);
		break;
	case 5: //……………………………………………………………………………………………turquoise
		glMaterialfv(GL_FRONT, GL_AMBIENT, turquoiseAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, turquoiseDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, turquoiseSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, turquoiseCoef);
		break;
	case 6: //……………………………………………………………………………………………brass
		glMaterialfv(GL_FRONT, GL_AMBIENT, brassAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, brassDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, brassSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, brassCoef);
		break;
	case 7: //……………………………………………………………………………………………bronze
		glMaterialfv(GL_FRONT, GL_AMBIENT, bronzeAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, bronzeDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, bronzeSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, bronzeCoef);
		break;
	case 8: //……………………………………………………………………………………………chrome
		glMaterialfv(GL_FRONT, GL_AMBIENT, chromeAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, chromeDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, chromeSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, chromeCoef);
		break;
	case 9: //……………………………………………………………………………………………copper
		glMaterialfv(GL_FRONT, GL_AMBIENT, copperAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, copperDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, copperSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, copperCoef);
		break;
	case 10: //……………………………………………………………………………………………gold
		glMaterialfv(GL_FRONT, GL_AMBIENT, goldAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, goldDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, goldSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, goldCoef);
		break;
	case 11: //……………………………………………………………………………………………silver
		glMaterialfv(GL_FRONT, GL_AMBIENT, silverAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, silverDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, silverSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, silverCoef);
		break;
	case 12: //……………………………………………………………………………………………blackPlastic
		glMaterialfv(GL_FRONT, GL_AMBIENT, blackPlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, blackPlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, blackPlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, blackPlasticCoef);
		break;
	case 13: //……………………………………………………………………………………………cyankPlastic
		glMaterialfv(GL_FRONT, GL_AMBIENT, cyanPlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, cyanPlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, cyanPlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, cyanPlasticCoef);
		break;
	case 14: //……………………………………………………………………………………………greenPlastic
		glMaterialfv(GL_FRONT, GL_AMBIENT, greenPlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, greenPlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, greenPlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, greenPlasticCoef);
		break;
	case 15: //……………………………………………………………………………………………redPlastic
		glMaterialfv(GL_FRONT, GL_AMBIENT, redPlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, redPlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, redPlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, redPlasticCoef);
		break;
	case 16: //……………………………………………………………………………………………yellowPlastic
		glMaterialfv(GL_FRONT, GL_AMBIENT, whitePlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, whitePlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, whitePlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, whitePlasticCoef);
		break;
	case 17: //……………………………………………………………………………………………yellowPlastic
		glMaterialfv(GL_FRONT, GL_AMBIENT, yellowPlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, yellowPlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, yellowPlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, yellowPlasticCoef);
		break;
	case 18: //……………………………………………………………………………………………blackRubber
		glMaterialfv(GL_FRONT, GL_AMBIENT, blackRubberAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, blackRubberDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, blackRubberSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, blackRubberCoef);
		break;
	case 19: //……………………………………………………………………………………………cyanRubber
		glMaterialfv(GL_FRONT, GL_AMBIENT, cyanRubberAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, cyanRubberDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, cyanRubberSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, cyanRubberCoef);
		break;
	case 20: //……………………………………………………………………………………………greenRubber
		glMaterialfv(GL_FRONT, GL_AMBIENT, greenRubberAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, greenRubberDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, greenRubberSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, greenRubberCoef);
		break;
	case 21: //……………………………………………………………………………………………redRubber
		glMaterialfv(GL_FRONT, GL_AMBIENT, redRubberAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, redRubberDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, redRubberSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, redRubberCoef);
		break;
	case 22: //……………………………………………………………………………………………redRubber
		glMaterialfv(GL_FRONT, GL_AMBIENT, whiteRubberAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, whiteRubberDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, whiteRubberSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, whiteRubberCoef);
		break;
	case 23: //……………………………………………………………………………………………redRubber
		glMaterialfv(GL_FRONT, GL_AMBIENT, yellowRubberAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, yellowRubberDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, yellowRubberSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, yellowRubberCoef);
		break;
	}
}



//================================================================================
//=========================================================================== INIT
void inicializa(void)
{
	glClearColor(BLACK);		//………………………………………………………………………………Apagar
	glEnable(GL_DEPTH_TEST);	//………………………………………………………………………………Profundidade
	glShadeModel(GL_SMOOTH);	//………………………………………………………………………………Interpolacao de cores	
	glEnable(GL_NORMALIZE);


	glVertexPointer(3, GL_FLOAT, 0, vertices); //………………………………………VertexArrays: vertices + normais + cores
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normais);
	glEnableClientState(GL_NORMAL_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, cor);
	glEnableClientState(GL_COLOR_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, arrayTexture);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//…………………………………………………………………………………………………………………………… ILUMINACAO
	glEnable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);

	initTexturas();
	initLights();
	initMaterials(1);
}



//------------------------------------------- ESCREVER VALORES DA COR DO FOCO
void desenhaTexto(char* string, GLfloat x, GLfloat y, GLfloat z)
{
	glRasterPos3f(x, y, z);
	while (*string)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *string++);
}

void showInformacao() {
	glDisable(GL_LIGHTING);
	glColor4f(1, 0, 0.4, 1);
	sprintf_s(texto,300, "R - %lf\n G - %lf\n B - %lf\n        R2- %lf\n G2 - %lf\n B2 - %lf", focoCorDif[0], focoCorDif[1], focoCorDif[2], focoCorDif2[0], focoCorDif2[1], focoCorDif2[2]);
	desenhaTexto(texto, -12, 1, -12);
	glEnable(GL_LIGHTING);

}




//========================================================================
//=====================OBJETOS============================================
//=========================================================================

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Chao : poligono regular
void drawChao() {
	int adiciona = 0;
	int adiciona2 = 0;
	int dim = 4;
	int incremento = 2;
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	initMaterials(16);
	//…………………………………………………………………………………………………………………………………………………………Chao com Malha
	if (chao == 1) {
		glNormal3f(0.0, 1.0, 0.0);
		glPushMatrix();
		glTranslatef(0, -tam * 2, 0);
		glBegin(GL_QUADS);
		for(int j=0;j<dim;j++){
			adiciona = 0;
			for (int i = 0; i < dim; i++) {
				glTexCoord2f((float)j/dim, (float)i/dim);  	 glVertex3i(-xC + adiciona, 0, -xC + adiciona2);
				glTexCoord2f((float)(j)/dim, (float)(i+1)/dim); 	 glVertex3i((-xC / incremento) + adiciona, 0, -xC + adiciona2);
				glTexCoord2f((float)(j+1)/dim, (float)(i+1)/dim);    glVertex3i((-xC / incremento) + adiciona, 0, (-xC / incremento) + adiciona2);
				glTexCoord2f((float)(j+1)/dim, (float)(i)/dim);    glVertex3i(-xC + adiciona, 0, (-xC / incremento) + adiciona2);
				
				adiciona += xC / incremento;
			}
		adiciona2 += xC / incremento;
		}
		glEnd();
		glPopMatrix();
		
	}
	//…………………………………………………………………………………………………………………………………………………………Chao sem Malha
	else {
		glNormal3f(0.0, 1.0, 0.0);
		glPushMatrix();
		glTranslatef(0, -tam * 2, 0);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);  	 glVertex3i(-xC , 0, -xC);
		glTexCoord2f(0.0f, 1.0f); 	 glVertex3i(xC , 0, -xC);
		glTexCoord2f(1.0f, 1.0f);    glVertex3i(xC , 0, xC);
		glTexCoord2f(1.0f, 0.0f);    glVertex3i(-xC , 0, xC );
		glEnd();
		glPopMatrix();
	}
	glDisable(GL_TEXTURE_2D);
}

void drawCube() {
	const float sizex = 1.0f;
	const float sizey = 1.0f;
	const float sizez = 1.0f;
	glBegin(GL_QUADS);

	// FRONT
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f(0.0f, 0.0f);  	 glVertex3f(-sizex, -sizey, sizez);
	glTexCoord2f(1.0f, 0.0f);  	 glVertex3f(sizex, -sizey, sizez);
	glTexCoord2f(1.0f, 1.0f);  	 glVertex3f(sizex, sizey, sizez);
	glTexCoord2f(0.0f, 1.0f);  	 glVertex3f(-sizex, sizey, sizez);

	// BACK
	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2f(0.0f, 0.0f);  	 glVertex3f(-sizex, -sizey, -sizez);
	glTexCoord2f(1.0f, 0.0f);  	 glVertex3f(-sizex, sizey, -sizez);
	glTexCoord2f(1.0f, 1.0f);  	 glVertex3f(sizex, sizey, -sizez);
	glTexCoord2f(0.0f, 1.0f);  	 glVertex3f(sizex, -sizey, -sizez);


	// LEFT
	glNormal3f(-1.0, 0.0, 0.0);
	glTexCoord2f(0.0f, 0.0f);  	 glVertex3f(-sizex, -sizey, sizez);
	glTexCoord2f(1.0f, 0.0f);  	 glVertex3f(-sizex, sizey, sizez);
	glTexCoord2f(1.0f, 1.0f);  	 glVertex3f(-sizex, sizey, -sizez);
	glTexCoord2f(0.0f, 1.0f);  	 glVertex3f(-sizex, -sizey, -sizez);

	// RIGHT
	glNormal3f(1.0, 0.0, 0.0);
	glTexCoord2f(0.0f, 0.0f);  	 glVertex3f(sizex, -sizey, -sizez);
	glTexCoord2f(1.0f, 0.0f);  	 glVertex3f(sizex, sizey, -sizez);
	glTexCoord2f(1.0f, 1.0f);  	 glVertex3f(sizex, sizey, sizez);
	glTexCoord2f(0.0f, 1.0f);  	 glVertex3f(sizex, -sizey, sizez);


	// TOP
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(0.0f, 0.0f);  	 glVertex3f(-sizex, sizey, sizez);
	glTexCoord2f(1.0f, 0.0f);  	 glVertex3f(sizex, sizey, sizez);
	glTexCoord2f(1.0f, 1.0f);  	 glVertex3f(sizex, sizey, -sizez);
	glTexCoord2f(0.0f, 1.0f);  	 glVertex3f(-sizex, sizey, -sizez);

	// BOTTOM
	glNormal3f(0.0, -1.0, 0.0);
	glTexCoord2f(0.0f, 0.0f);  	 glVertex3f(-sizex, -sizey, sizez);
	glTexCoord2f(1.0f, 0.0f);  	 glVertex3f(-sizex, -sizey, -sizez);
	glTexCoord2f(1.0f, 1.0f);  	 glVertex3f(sizex, -sizey, -sizez);
	glTexCoord2f(0.0f, 1.0f);  	 glVertex3f(sizex, -sizey, sizez);

	glEnd();

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Paredes : poligono regular
void drawParede() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	initMaterials(16);
	//PAREDE 1
	glNormal3f(-1.0, 0.0, 0.0);
	glPushMatrix();
		glTranslatef(0, 0, 0);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);  	 glVertex3i(-xC, -tam * 2, -xC);
		glTexCoord2f(1.0f, 0.0f); 	 glVertex3i(-xC, -tam * 2, xC);
		glTexCoord2f(1.0f, 1.0f);    glVertex3i(-xC, yC, xC);
		glTexCoord2f(0.0f, 1.0f);    glVertex3i(-xC, yC, -xC);
		glEnd();
	glPopMatrix();
	//PAREDE 2
	initMaterials(16);
	glNormal3f(1.0, 0.0, 0.0);
	glPushMatrix();
		glTranslatef(0, 0, 0);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);  	 glVertex3i(xC, -tam * 2, -xC);
		glTexCoord2f(1.0f, 0.0f); 	 glVertex3i(xC, -tam * 2, xC);
		glTexCoord2f(1.0f, 1.0f);    glVertex3i(xC, yC, xC);
		glTexCoord2f(0.0f, 1.0f);    glVertex3i(xC, yC, -xC);
		glEnd();
	glPopMatrix();
	//PAREDE 3
	initMaterials(16);
	glNormal3f(0.0, 0.0, -1.0);
	glPushMatrix();
		glTranslatef(0, 0, 0);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);  	 glVertex3i(-xC, -tam * 2, -xC);
		glTexCoord2f(1.0f, 0.0f); 	 glVertex3i(xC, -tam * 2, -xC);
		glTexCoord2f(1.0f, 1.0f);    glVertex3i(xC, yC, -xC);
		glTexCoord2f(0.0f, 1.0f);    glVertex3i(-xC, yC, -xC);
		glEnd();
	glPopMatrix();
	//PAREDE 4
	initMaterials(16);
	glNormal3f(0.0, 0.0, 1.0);
	glPushMatrix();
		glTranslatef(0, 0, 0);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);  	 glVertex3i(-xC, -tam * 2, xC);
		glTexCoord2f(1.0f, 0.0f); 	 glVertex3i(xC, -tam * 2, xC);
		glTexCoord2f(1.0f, 1.0f);    glVertex3i(xC, yC, xC);
		glTexCoord2f(0.0f, 1.0f);    glVertex3i(-xC, yC, xC);
		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

//====================================================PORTA
void drawPorta() {
	glColor4f(0.36, 0.25, 0.20, 1);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	initMaterials(9);
	glBindTexture(GL_TEXTURE_2D, texture[1]);

	glPushMatrix();
	glTranslatef(xC-0.8, 0, 0);
	glScalef(.8, .8, .8);
	glRotatef(90, 0, 0, 1);
	glScalef(30, 0.01, 12);
	glBegin(GL_QUADS);
	glTexCoord2d(1, 0);		glVertex3f(-0.5, 0, 0.5);
	glTexCoord2d(0, 0);		glVertex3f(0.5, 0, 0.5);
	glTexCoord2d(0, 1);		glVertex3f(0.5, 0, -0.5);
	glTexCoord2d(1, 1);		glVertex3f(-0.5, 0, -0.5);
	glEnd();
	glPopMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_TEXTURE_2D);
}

//====================================================Lampadas
void drawLampadas(GLint foco) {
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
	glEnable(GL_COLOR_MATERIAL);
	if (foco == 1) {
		glPushMatrix();
		glTranslatef(xC, 3 * yC / 5, 0);
		glScalef(.5, .5, .5);

		glColor3f(focoCorDif[0], focoCorDif[1], focoCorDif[2]);
		if (ligaFoco == 0) {
			glColor3f(0.0, 0.0, 0.0);
		}

		drawCube();
		
		glPopMatrix();
	}
	else if (foco == 2) {
		glPushMatrix();
		glTranslatef(-xC, 3 * yC / 5, 0);
		glScalef(.5,.5,.5);

		

		glColor3f(focoCorDif2[0], focoCorDif2[1], focoCorDif2[2]);
		if (ligaFoco2 == 0) {
			glColor3f(0.0, 0.0, 0.0);
		}

		drawCube();
		glPopMatrix();
	}
	glDisable(GL_COLOR_MATERIAL);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Cadeira
void drawCadeira() {
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	initMaterials(materialcadeira);
	//====================================== PERNA ESQUERDA
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glPushMatrix();

		glTranslatef(xPosition, 0.0, 1+zPosition);
		glRotatef(angle, 0.0, 0.0, 1.0);
		glScalef(2, 2, 2);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, perna_esquerda_tras1);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, perna_esquerda_tras2);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, perna_esquerda_tras3);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, perna_esquerda_tras4);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, perna_esquerda_frente1);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, perna_esquerda_frente2);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, perna_esquerda_frente3);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, perna_esquerda_frente4);

	glPopMatrix();
	//===================================================== PERNA DIREITA
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	initMaterials(materialcadeira);
	glPushMatrix();

	glTranslatef(xPosition, 0.0, 1+zPosition);
	glRotatef(-angle, 0.0, 0.0, 1.0);
	glScalef(2, 2, 2);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, perna_direita_tras1);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, perna_direita_tras2);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, perna_direita_tras3);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, perna_direita_tras4);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, perna_direita_frente1);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, perna_direita_frente2);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, perna_direita_frente3);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, perna_direita_frente4);

	glPopMatrix();

	//========================================================== ASSENTO E COSTAS
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	initMaterials(materialcadeira);
	glPushMatrix();

	glTranslatef(xPosition, yPosition, 1+zPosition);
	glScalef(2, 2, 2);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, costafrente4);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, costafrente3);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, costafrente2);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, costafrente1);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, costafrente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, costa);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima_inferior);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, ligacao_cima_inferior1);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, ligacao_cima_inferior2);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, ligacao_cima_inferior3);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, ligacao_cima_inferior4);

	glPopMatrix();

}

//===============================================================Quadrado Transparente
void drawTransparente() {
	const float sizex = 1.0f;
	const float sizey = 1.0f;
	const float sizez = 1.0f;
	glFrontFace(GL_CW);

	glDisable(GL_TEXTURE_2D);
	initMaterials(10);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPushMatrix();
	glTranslatef(4, 4+0.2, 1);
	glScalef(4, 0.1, 8);
	drawCube();
	glPopMatrix();
	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glFrontFace(GL_CCW);
}

void drawTransparenteCubos() {
	const float sizex = 1.0f;
	const float sizey = 1.0f;
	const float sizez = 1.0f;
	glFrontFace(GL_CW);

	glDisable(GL_TEXTURE_2D);
	initMaterials(0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//=============================================================Cubo1
	glPushMatrix();
	glTranslatef(4, 4 + 1.2, 1);
	drawCube();
	glPopMatrix();

	initMaterials(1);
	//=============================================================Cubo2
	glPushMatrix();
	glTranslatef(4, 4 + 1.2, 5);
	drawCube();
	glPopMatrix();

	initMaterials(2);
	//=============================================================Cubo3
	glPushMatrix();
	glTranslatef(4, 4 + 1.2, -3);
	drawCube();
	glPopMatrix();

	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glFrontFace(GL_CCW);
}


//////////////////////////////////////////
//
//  draw a picture frame 
//
void draw_picture()
{
	glColor4f(1, 1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, texture[2]);

	glPushMatrix();
	glTranslatef(0, yC / 2, zC - 0.8);
	glScalef(.8, .8, .8);
	glRotatef(90, 90, 0, 1);
	glScalef(20, 0.01, 7);
	glBegin(GL_QUADS);
	glTexCoord2d(1, 0);		glVertex3f(-0.5, 0, 0.5);
	glTexCoord2d(0, 0);		glVertex3f(0.5, 0, 0.5);
	glTexCoord2d(0, 1);		glVertex3f(0.5, 0, -0.5);
	glTexCoord2d(1, 1);		glVertex3f(-0.5, 0, -0.5);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

//=====================================PRATELEIRAS
void drawPrateleiras()
{
	glColor4f(0.36, 0.25, 0.20, 1.0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, texture[1]);

	glPushMatrix();
	glTranslatef(-xC+0.8,yC / 4, 0);
	glScalef(.8, .8, .8);
	glRotatef(0, 0, 0, 1);
	glScalef(5, 0.01, 30);
	glBegin(GL_QUADS);
	glTexCoord2d(1, 0);		glVertex3f(-0.5, 0, 0.5);
	glTexCoord2d(0, 0);		glVertex3f(0.5, 0, 0.5);
	glTexCoord2d(0, 1);		glVertex3f(0.5, 0, -0.5);
	glTexCoord2d(1, 1);		glVertex3f(-0.5, 0, -0.5);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_COLOR_MATERIAL);
}

void drawCubosPrateleira() {
	int i;
	int n = 5;
	glFrontFace(GL_CW);

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (i = 0; i < n; i++) {
		initMaterials(i * 3);
		//=============================================================Cubo1
		glPushMatrix();
		glTranslatef(-xC + 0.8, 1 + yC / 4, 10 - (i * 5));
		drawCube();
		glPopMatrix();
	}

	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glFrontFace(GL_CCW);
}



// draw a table leg
void draw_leg(float xt, float yt, float zt)
{
	
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	initMaterials(16);
	glPushMatrix();
	glTranslatef(xt, yt, zt);
	glScalef(0.5, 4.4, 0.5);
	drawCube();
	glPopMatrix();
}


//   draw a table - one table top with four legs
void draw_table()
{
	const float sizex = 1.0f;
	const float sizey = 1.0f;
	const float sizez = 1.0f;
	glColor4f(0.36, 0.25, 0.20,1.0);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	initMaterials(16);
	glEnable(GL_COLOR_MATERIAL);
	glPushMatrix();
	glTranslatef(4, 4, 1);
	glScalef(4, 0.2, 8);
	drawCube();
	glPopMatrix();

	draw_leg(5.95, -0.5, -3.95);
	draw_leg(5.95, -0.5, 5.95);
	draw_leg(1.95, -0.5, -3.95);
	draw_leg(1.95, -0.5, 5.95);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_TEXTURE_2D);
}




void display(void) {

	//================================================================= APaga ecran e lida com profundidade (3D)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//================================================================= Viewport1
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, hScreen / 4, wScreen / 4, hScreen / 4);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-xC, xC, -xC, xC, -zC, zC);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 5, 0, 0, 0, 0, 0, 0, -1);
	//--------------------- desenha objectos
	initLights();
	drawChao();
	drawCadeira();


	//=================================================================  Viewport2
	glEnable(GL_LIGHTING);
	glViewport(wScreen / 5, 0, wScreen , hScreen );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angZoom, (float)wScreen / hScreen, 0.1, 3 * zC);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt( obsP[0], obsP[1], obsP[2], 0, 0, 0, 0, 1, 0);
	//================================================================= Não modificar !!!!!!!!!!!!
	showInformacao();
	initLights();
	//…………………………………………………………………………………………………………………………………………………………Objecto
  
  draw_picture(); 
  drawPrateleiras();
  drawPorta();
	//------------------------------------------------------------------
	drawLampadas(2);
	drawLampadas(1);
	drawChao();
	drawParede();
	draw_table();
	drawCadeira();
	drawTransparente();
	drawTransparenteCubos();
	drawCubosPrateleira();
	//. . . . . . . . . . . . . . . . . . . . .  Actualizacao
	glutSwapBuffers();
}

//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y) {

	//…………………………………………………………………………………………………………………………………………………………Andar
	switch (key) {
	case 'z':
	case 'Z':
		xPosition = xPosition - 0.25;
		if (xPosition < -xC / 2)
			xPosition = -xC / 2;
		glutPostRedisplay();
		break;

	case 'x':
	case 'X':
		xPosition = xPosition + 0.25;
		if (xPosition > 0)
			xPosition = 0;
		glutPostRedisplay();
		break;

	//…………………………………………………………………………………………………………………………………………………………Rodar Pernas
	case 'e':
	case 'E':
		if (subir) {
			angle = angle + 5;
			yPosition -= 0.125;
			if (yPosition < cos(135)) {
				subir = 0;
			}
		}
		else {
			yPosition += 0.125;
			angle = angle - 5;
			if (yPosition > cos(45)) {
				subir = 1;
			}
		}
		glutPostRedisplay();
		break;

	case 'q':
	case 'Q':
		if (subir) {
			angle = angle - 5;
			yPosition += 0.125;
			if (yPosition > cos(45)) {
				subir = 0;
			}
		}
		else {
			yPosition -= 0.125;
			angle = angle + 5;
			if (yPosition <cos(135)) {
				subir = 1;
			}
		}

		glutPostRedisplay();
		break;


		//--------------------------- Ligar/desligar foco
		case 'f':
		case 'F':
			if (ligaFoco == TRUE)
				ligaFoco = FALSE;
			else
				ligaFoco = TRUE;
			glutPostRedisplay();
			break;

		//--------------------------- Ligar/desligar foco2
		case 'd':
		case 'D':
			if (ligaFoco2 == TRUE)
				ligaFoco2 = FALSE;
			else
				ligaFoco2 = TRUE;
			glutPostRedisplay();
			break;

			//--------------------------- Ligar/desligar Pontual
		case 'y':
		case 'Y':
			if (ligaPontual == TRUE)
				ligaPontual = FALSE;
			else
				ligaPontual = TRUE;
			glutPostRedisplay();
			break;

			//--------------------------- Mudar cor foco
		case 'r':
		case 'R':
			if (incrementaR==1) {
				focoCorEsp[0] -= 0.1;
				focoCorDif[0] -= 0.1;
				if (focoCorDif[0] <= 0.0) {
					incrementaR = 0;
				}
			}
			else {
				focoCorEsp[0] += 0.1;
				focoCorDif[0] += 0.1;
				if (focoCorDif[0] >= 1.0) {
					incrementaR = 1;
				}
			}
			glutPostRedisplay();
			break;

		case 'g':
		case 'G':
			if (incrementaG==1) {
				focoCorEsp[1] -= 0.1;
				focoCorDif[1] -= 0.1;
				if (focoCorDif[1] <= 0.0) {
					incrementaG = 0;
				}
			}
			else {
				focoCorEsp[1] += 0.1;
				focoCorDif[1] += 0.1;
				if (focoCorDif[1] >= 1.0) {
					incrementaG = 1;
				}
			}
			glutPostRedisplay();
			break;
		case 'b':
		case 'B':
			if (incrementaB==1) {
				focoCorEsp[2] -= 0.1;
				focoCorDif[2] -= 0.1;
				if (focoCorDif[2] <= 0.0) {
					incrementaB = 0;
				}
			}
			else {
				focoCorEsp[2] += 0.1;
				focoCorDif[2] += 0.1;
				if (focoCorDif[2] >= 1.0) {
					incrementaB = 1;
				}
			}
			glutPostRedisplay();
			break;

			//--------------------------- Mudar cor foco2
		case 't':
		case 'T':
			if (incrementaR2 == 1) {
				focoCorEsp2[0] -= 0.1;
				focoCorDif2[0] -= 0.1;
				if (focoCorDif2[0] <= 0.0) {
					incrementaR2 = 0;
				}
			}
			else {
				focoCorEsp2[0] += 0.1;
				focoCorDif2[0] += 0.1;
				if (focoCorDif2[0] >= 1.0) {
					incrementaR2 = 1;
				}
			}
			glutPostRedisplay();
			break;

		case 'h':
		case 'H':
			if (incrementaG2 == 1) {
				focoCorEsp2[1] -= 0.1;
				focoCorDif2[1] -= 0.1;
				if (focoCorDif2[1] <= 0.0) {
					incrementaG2 = 0;
				}
			}
			else {
				focoCorEsp2[1] += 0.1;
				focoCorDif2[1] += 0.1;
				if (focoCorDif2[1] >= 1.0) {
					incrementaG2 = 1;
				}
			}
			glutPostRedisplay();
			break;
		case 'n':
		case 'N':
			if (incrementaB2 == 1) {
				focoCorEsp2[2] -= 0.1;
				focoCorDif2[2] -= 0.1;
				if (focoCorDif2[2] <= 0.0) {
					incrementaB2 = 0;
				}
			}
			else {
				focoCorEsp2[2] += 0.1;
				focoCorDif2[2] += 0.1;
				if (focoCorDif2[2] >= 1.0) {
					incrementaB2 = 1;
				}
			}
			glutPostRedisplay();
			break;

		//………………………………………………………………………………………………………………………………………………………, Mudar material da cadeira(16-Plastico Branco; 0-Esmeralda)
		case 'm':
		case 'M':
			if (materialcadeira == 16) {
				materialcadeira = 0;
			}
			else {
				materialcadeira = 16;
			}
			glutPostRedisplay();
			break;

		//………………………………………………………………………………………………………………………………………………………… Aticar/ Desativar malha do chao
		case 'c':
		case 'C':
			if (chao == 1) {
				chao = 0;
			}
			else {
				chao = 1;
			}
			glutPostRedisplay();
			break;

			//………………………………………………………………………………………………………………………………………………………… Luz Pontual intensidade
		case '<':
		case '>':
			if (dia==0) {
				linear_attenuation -= 0.1;
				if (linear_attenuation <= 0) {
					linear_attenuation = 0.1;
					dia = 1;
				}
			}
			else {
				linear_attenuation += 0.1;
				if (linear_attenuation >= 1.0) {
					linear_attenuation = 1.0;
					dia = 0;
				}
			}
			glutPostRedisplay();
			break;

			//………………………………………………………………………………………………………………………………………………………… Mete especular do obsidian para (1,0,0)
		case 'i':
		case 'I':
			if (incrementador==0) {
				obsidianSpec[0] = 1.0;
				obsidianSpec[1] = 0.0;
				obsidianSpec[2] = 0.0;
				incrementador = 1;
			}
			else {
				obsidianSpec[0] = 0.332741;
				obsidianSpec[1] = 0.328634;
				obsidianSpec[2] = 0.346435;
				incrementador = 0;
			}
			glutPostRedisplay();
			break;

			//………………………………………………………………………………………………………………………………………………………… Mete difusa do obsidian para (1,0,0)
		case 'o':
		case 'O':
			if (incrementador2 == 0) {
				obsidianDif[0] = 1.0;
				obsidianDif[1] = 0.0;
				obsidianDif[2] = 0.0;
				incrementador2 = 1;
			}
			else {
				obsidianDif[0] = 0.18275;
				obsidianDif[1] = 0.17;
				obsidianDif[2] =0.22525;
				incrementador2 = 0;
			}
			glutPostRedisplay();
			break;

			//………………………………………………………………………………………………………………………………………………………… Mete ambiente do obsidian para (1,0,0)
		case 'p':
		case 'P':
			if (incrementador3 == 0) {
				obsidianAmb[0] = 1.0;
				obsidianAmb[1] = 0.0;
				obsidianAmb[2] = 0.0;
				incrementador3 = 1;
			}
			else {
				obsidianAmb[0] = 0.05375;
				obsidianAmb[1] = 0.05;
				obsidianAmb[2] = 0.06625;
				incrementador3 = 0;
			}
			glutPostRedisplay();
			break;


			//………………………………………………………………………………………………………………………………………………………… Altera coeficiente do material
		case 'U':
		case 'u':
			if (transp == 0) {
				jadeCoef = 128;
				transp = 1;
				
			}
			else {
				jadeCoef = 0;
				transp = 0;
				
			}
			glutPostRedisplay();
			break;



		//--------------------------- Escape
	case 27:
		exit(0);
		break;
	}

}


void teclasNotAscii(int key, int x, int y) {
	//.. observador pode andar à volda da cena  (setas esquerda / direita)
	//.. observador pode andar para cima e para baixo (setas cima / baixo )

	if (key == GLUT_KEY_UP)   obsP[1] = (obsP[1] + 0.1);
	if (key == GLUT_KEY_DOWN) obsP[1] = (obsP[1] - 0.1);
	if (key == GLUT_KEY_LEFT)  aVisao = (aVisao + 0.1);
	if (key == GLUT_KEY_RIGHT) aVisao = (aVisao - 0.1);

	if (obsP[1] > yC)   obsP[1] = yC;   // limita altura
	if (obsP[1] < -yC)  obsP[1] = -yC;

	obsP[0] = rVisao * cos(aVisao);      // actualiza posicao (X,Z)
	obsP[2] = rVisao * sin(aVisao);

	glutPostRedisplay();
}


//======================================================= MAIN
//======================================================= MAIN
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(wScreen, hScreen);
	glutInitWindowPosition(300, 100);
	glutCreateWindow(" |Observador:'SETAS'|        |Andar-'z/x'|        |Rodar -'e/q'|        |Foco -'f'|        |Foco2 -'d'|           |Pontual -'Y'|          |Mudar Cor-'R,G,B'|          |Mudar Cor2-'T,H,N'|     |Malha Chao - 'C'|     |Mudar Material - 'M'|        |Luz Pontual - '</>'|          |Especular Obsidian - 'I'|            |Difusa Obsidian - 'O'|");

	inicializa();

	glutSpecialFunc(teclasNotAscii);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;

}



