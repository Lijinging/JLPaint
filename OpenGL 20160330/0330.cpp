#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;

int specialKey;
GLfloat red, green, blue;
const int Width = 900;
const int Height = 600;
int points_size = 0;

vector<vector<int*>>points;
typedef vector<int*> POINT;


void destroy()
{
	for (int i = 0; i < points_size; i++)
		points[i].clear();
	points.clear();
	points_size = 0;
}

void renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (points_size != 0)
	{
		
		for (int j = 0; j < points_size; j++)
		{
			int point_size = points[j].size();
			for (int i = 1; i < point_size; i++)
			{
				glBegin(GL_LINES);
				{
					glVertex2i(points[j][i][0], points[j][i][1]);
					glVertex2i(points[j][i - 1][0], points[j][i - 1][1]);

				}
				glEnd();
			}
		}
	}
	glutSwapBuffers();
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, Width, Height, 0.0);
}

void processMouseActiveMotion(int x, int y)
{

	points[points_size - 1].push_back(new int[2]{x, y});

}

void processNormalKeys(unsigned char key, int x, int y)
{
	if (key == 27)
	{
		destroy();
	}
}

void processMouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		vector<int *>point;
		point.push_back(new int[]{x, y});
		points_size++;
		points.push_back(point);
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("Test");

	init();
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);

	//处理鼠标事件
	glutMouseFunc(processMouse);
	glutMotionFunc(processMouseActiveMotion);
	//	glutPassiveMotionFunc(processMousePassiveMotion);

	//处理键盘事件
	glutKeyboardFunc(processNormalKeys);

	glutMainLoop();
	return 0;
}

