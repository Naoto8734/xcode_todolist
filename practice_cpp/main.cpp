//
//  main.cpp
//  practice_cpp
//
//  Created by Naoto on 2017/08/14.
//  Copyright © 2017年 NYamashita. All rights reserved.
//

#include <iostream>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

//グローバル変数宣言
const char game_title[] = "ziggurat";

//変数宣言
static double xd = 0.0;
static double yd = 0.0;
static double zd = 0.0;
static double rot = 0.0;
static const GLfloat ground[][4] = {
	{ 0.6, 0.6, 0.6, 1.0 },
	{ 0.3, 0.3, 0.3, 1.0 }
};


//プロトタイプ宣言

void init();
void display();
void close();
void reshape(int x, int y);
void keyboard(unsigned char key, int x, int y);
void keyboardup(unsigned char key, int x, int y);
void timer(int value);

int main(int argc, char *argv[]){
	glutInit(&argc, argv);	//glutの初期化
	
	//windowの作成
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);	//バッファの初期化
	glutInitWindowSize(500, 500);
	glutCreateWindow(game_title);
	
	//コールバック関数
	glutDisplayFunc(display);
	glutWMCloseFunc(close);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardup);
	glutTimerFunc(17, timer, 0);
	
	//初期化
	init();
	
	glutMainLoop();
	
	return 0;
}

void init(){
	glClearColor(0.1, 0.6, 0.1, 1.0);	//緑でクリア
	glEnable(GL_DEPTH_TEST);
	
	
	glEnable(GL_LIGHTING);//ライト
	glEnable(GL_LIGHT0);
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void display(){
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();	//行列の初期化
	
	gluLookAt(3.0, 4.0, 5.0,
			  0.0, 0.0, 1.0,
			  0.0, 1.0, 0.0);	//視野変換
	
	glRotated(rot, 0.0, 1.0, 0.0);
	
	//モデリング変換
	glBegin(GL_QUADS);
	glNormal3d(0.0, 1.0, 0.0);
	for (int j = -5; j < 5; ++j) {
		for (int i = -5; i < 5; ++i) {
			glMaterialfv(GL_FRONT, GL_DIFFUSE, ground[(i + j) & 1]);
			glVertex3d((GLdouble)i, -0.5, (GLdouble)j);
			glVertex3d((GLdouble)i, -0.5, (GLdouble)(j + 1));
			glVertex3d((GLdouble)(i + 1), -0.5, (GLdouble)(j + 1));
			glVertex3d((GLdouble)(i + 1), -0.5, (GLdouble)j);
		}
	}
	glEnd();
	glTranslated(0.5, 0.0, 0.5);
	
	glTranslated(xd, yd, zd);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidCube(1.0);
	
	glutSwapBuffers();
}

void close(){
	std::cout << "Game end." << std::endl;
	exit(0);
}

void reshape(int x, int y){
	//ビューポート変換
	glViewport(0.0, 0.0, (GLsizei)x, (GLsizei)y);
//	if (x<y){
//		glViewport(0.0, 0.0, (GLsizei)x, (GLsizei)x);
//	}else{
//		glViewport(0.0, 0.0, (GLsizei)y, (GLsizei)y);
//	}
	
	//投影変換
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	//gluPerspective(45, (double)y/(double)x, 0.1, 1000);
	gluPerspective(45, 1, 0.1, 1000);
	
	//モデリング変換&視野変換
}

void keyboard(unsigned char key, int x, int y){
	//std::cout << key << " is pressed." << std::endl;
	switch ( key ){
		case '\033':	//Esc
		case 'q':
		case 'Q':
			close();
			break;
			
		case 'i':
			zd+=1.0;
			break;
		case 'k':
			zd-=1.0;
			break;
			
		case 'j':
			xd+=1.0;
			break;
		case 'l':
			xd-=1.0;
			break;

		case 'u':
			yd+=1.0;
			break;
		case 'o':
			yd-=1.0;
			break;
			
		case 0x20:
			std::cout << xd << " , " << yd << " , "<< zd << std::endl;
			break;
			
		default:
			break;
	}
}

void keyboardup(unsigned char key, int x, int y){
	//std::cout << key << " is released." << std::endl;
}

void timer(int value){
	glutTimerFunc(17, timer, 0);
	rot+=0.1;
	display();
}
