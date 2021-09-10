#include <cstdlib>
#include <glut.h>
#include <ctime>
#include <cmath>
#include "compl.h"

struct frame {
	static const int Ws = 100, Hs = 100;
	unsigned char Image[Hs][Ws][3];

	double x1 = 2, y1 = 2, x0 = -2, y0 = -2, t = (double)clock() / CLOCKS_PER_SEC / 3;
	cmpl C = cmpl(cos(t) * cos(t) * cos(t), sin(t)+0.23);

	frame(void) 
	{
		for (int y = 0; y < Hs; y++)
			for (int x = 0; x < Ws; x++)
			{
				cmpl Z = cmpl(x0 + x * (x1 - x0) / Ws, y0 + y * (y1 - y0) / Hs);
				
				int n = Z.Julia(C);
				PutPixel(x, y, n*C.Im/(C.Re + 1), n/Z.Im*(C.Re*sin(t)+5), n*Z.Re/5);
			}
	}
	
	void PutPixel(int x, int y, int r, int g, int b)
	{
		Image[y][x][0] = Clamp(b);
		Image[y][x][1] = Clamp(g);
		Image[y][x][2] = Clamp(r);
	}

	int Clamp(int val, float min = 0, float max = 255)
	{
		if (val < min)
			val = min;
		if (val > max)
			val = max;
		return val;
	}

	void Draw(void)
	{
		glDrawPixels(Ws, Hs, GL_BGR_EXT, GL_UNSIGNED_BYTE, Image);
	}
};

void Display(void)
{
	glClearColor(0.2, 0.3, 0.8, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	double t = (double)clock() / CLOCKS_PER_SEC;

	glPixelZoom(3 - 2*sin(4*t), -3 + 2 * sin(4*t));
	glRasterPos2d(-sin(t)/5, cos(t)/5);

	frame View;
	View.Draw();

	glFinish();
	glutSwapBuffers();
	glutPostRedisplay();
}

void Keyboard(unsigned char Key, int X, int Y)
{
	if (Key == 27)
		exit(30);
}

int main(int ArgC, char* ArgV[])
{
	glutInit(&ArgC, ArgV);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	glutInitWindowPosition(-10, 0);
	glutInitWindowSize(1530, 780);   //Есть размер экрана!!!
	glutCreateWindow("LIFE.exe");

	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);

	glutMainLoop();
}