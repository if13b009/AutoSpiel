#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "main.h"


//bmp texture load function
//Credits: https ://github.com/OpenGLInsights/OpenGLInsightsCode

GLuint loadBMP_custom(const char * imagepath)
{
	// Data read from the header of the BMP file
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int width, height;
	unsigned int imageSize;
	// Actual RGB data
	unsigned char * data;

	// Open the file
	FILE * file = fopen(imagepath, "rb");
	if (!file)
	{
		printf("Image could not be opened\n");
		return 0;
	}
	// Read the header, i.e. the 54 first bytes

	// If less than 54 byes are read, problem
	if (fread(header, 1, 54, file) != 54)
	{
		// If not 54 bytes read : problem
		printf("Not a proper BMP file\n");
		return false;
	}
	// A BMP files always begins with "BM"
	if (header[0] != 'B' || header[1] != 'M')
	{
		printf("Not a proper BMP file\n");
		return 0;
	}

	// Read ints from the byte array
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (imageSize == 0)    imageSize = width*height * 3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0)      dataPos = 54;

	// Create a buffer
	data = new unsigned char[imageSize];

	// Read the actual data from the file into the buffer
	fread(data, 1, imageSize, file);

	// Everything is in memory now, the file wan be closed
	fclose(file);

	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture as a 2D texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// Return the ID of the texture we just created
	return textureID;
}

void resize(int width, int height){

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1);
	glMatrixMode(GL_MODELVIEW);
}

void init()
{

	for (i = 0; i < 4; i++)
	{
		o = rand() % 4 + 1;

		switch (o)
		{
		case 1:
			npcx[i] = 250;  //fahrt links

			break;
		case 2:
			npcx[i] = 350;  //fahrt rechts
			break;
		case 3:
			npcx[i] = 450;  //fahrt rechts

			break;
		case 4:
			npcx[i] = 550;  //fahrt rechts

			break;
		}
		npcy[i] = 1500 - i * 230;

	}
	resize(800, 600);

}
void car(int num){
	menucar = num;
	glutPostRedisplay();
}
void road(int num){
	menuroad = num;

	glutPostRedisplay();
}

void npccar(int num){
	menunpc = num;
	glutPostRedisplay();
}

void gras(int num){
	menugras = num;
	glutPostRedisplay();
}

void middle(int num){
	menumiddle = num;
	glutPostRedisplay();
}


void menu(int num){
	if (num == 0){
		glutDestroyWindow(window);
		exit(0);
	}
	else{
		value = num;
	}
	glutPostRedisplay();
}

void color(int num){
	menucolor = num;
	glutPostRedisplay();
}
void createMenu(void){

	submenu0 = glutCreateMenu(color);
	glutAddMenuEntry("Black", 1);
	glutAddMenuEntry("Yellow", 2);
	glutAddMenuEntry("Red", 3);
	glutAddMenuEntry("Green", 4);
	glutAddMenuEntry("Blue", 5);
	submenu1 = glutCreateMenu(road);
	glutAddMenuEntry("Road", 1);
	glutAddMenuEntry("dirty Road", 2);
	submenu2 = glutCreateMenu(car);
	glutAddMenuEntry("Cabrio", 1);
	glutAddMenuEntry("Jeep", 2);
	submenu3 = glutCreateMenu(npccar);
	glutAddMenuEntry("Red Car", 1);
	glutAddMenuEntry("Blue Car", 2);
	submenu4 = glutCreateMenu(gras);
	glutAddMenuEntry("Gras", 1);
	glutAddMenuEntry("Sand", 2);
	submenu5 = glutCreateMenu(middle);
	glutAddMenuEntry("Yes", 1);
	glutAddMenuEntry("No", 2);
	glutAddSubMenu("Color", submenu0);


	menu_id = glutCreateMenu(menu);
	glutAddMenuEntry("Garage", 1);
	glutAddSubMenu("Change Road", submenu1);
	glutAddSubMenu("Change my Car", submenu2);
	glutAddSubMenu("Change Npc Car", submenu3);
	glutAddSubMenu("Change OffRoad", submenu4);
	glutAddSubMenu("Show Middle-Line", submenu5);
	glutAddMenuEntry("Quit Game", 0);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void keyPressed(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		carx = carx - 100;
		if (carx < 250) carx = 250;
		break;
	case 'd':
		carx = carx + 100;
		if (carx > 550) carx = 550;

		break;
	case 'e':
		carx = carx + 100;
		if (carx > 550) carx = 550;
		cary = cary + 30;
		break;
	case 'q':
		carx = carx - 100;
		if (carx > 550) carx = 550;
		cary = cary + 30;
		break;
	case 's':

		cary = cary - 30;
		break;
	case 'w':

		cary = cary + 30;
		break;
	case 32:
		for (i = 0; i < 4; i++)
		{
			npcy[i] = npcy[i] - 10;
		}
		movement = movement - 20;
		break;


	case 70:
	case 102:
		fullscreen = !fullscreen;
		if (fullscreen)
		{
			glutFullScreen();
		}
		else
		{
			glutReshapeWindow(800, 600);
			glutPositionWindow(100, 100);
		}
		break;
	case 27:exit(0);


	}
}



void display(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//gras linke seite

	if (menugras == 1 || menugras == 0) glBindTexture(GL_TEXTURE_2D, grastexture);
	else if (menugras == 2)  glBindTexture(GL_TEXTURE_2D, sandtexture
		);
	glBegin(GL_QUADS);

	glTexCoord2f(0, 1);
	glVertex2f(0, 600);
	glTexCoord2f(0, 0);
	glVertex2f(0, 0);
	glTexCoord2f(1, 0);
	glVertex2f(200, 0);
	glTexCoord2f(1, 1);
	glVertex2f(200, 600);
	glEnd();

	//gras rechte seite

	glBegin(GL_QUADS);

	glTexCoord2f(0, 1);
	glVertex2f(600, 600);
	glTexCoord2f(0, 0);
	glVertex2f(600, 0);
	glTexCoord2f(1, 0);
	glVertex2f(800, 0);
	glTexCoord2f(1, 1);
	glVertex2f(800, 600);
	glEnd();

	//strasse ausgehen von mitte
	if (menuroad == 1 || menuroad == 0) glBindTexture(GL_TEXTURE_2D, roadtexture);
	else if (menuroad == 2)  glBindTexture(GL_TEXTURE_2D, roadtexture2);
	glBegin(GL_QUADS);

	glTexCoord2f(0, 1);
	glVertex2f(400 - 200, 600);
	glTexCoord2f(0, 0);
	glVertex2f(400 - 200, 0);
	glTexCoord2f(1, 0);
	glVertex2f(400 + 200, 0);
	glTexCoord2f(1, 1);
	glVertex2f(400 + 200, 600);
	glEnd();

	// Mittellinie 
	int a = 300;
	if (menumiddle == 0 || menumiddle == 1){
		for (int j = 0; j < 3; j++){  // 3 Mittellinien zeichnen
			glLoadIdentity();
			glTranslatef(a, movement, 0);
			a += 100;
			for (i = 1; i <= 10; i++)     //Mittelstriche zeichnen
			{

				switch (menucolor)
				{
				case 0:
					glColor3f(1, 1, 0);
					break;
				case 1:
					glColor3f(0, 0, 0);
					break;
				case 2:
					glColor3f(1, 1, 0);
					break;
				case 3:
					glColor3f(1, 0, 0);
					break;
				case 4:
					glColor3f(0, 1, 0);
					break;
				case 5:
					glColor3f(0, 0, 1);
					break;
				}


				glBegin(GL_QUADS);
				glVertex2f(-5, 60 * i + 15);
				glVertex2f(-5, 60 * i - 15);
				glVertex2f(5, 60 * i - 15);
				glVertex2f(5, 60 * i + 15);
				glEnd();
			}
		} // j ende
	}
	glLoadIdentity();

	if (menucar == 0 || menucar == 1){
		glBindTexture(GL_TEXTURE_2D, cabriotexture);
	}
	else if (menucar == 2)
	{
		glBindTexture(GL_TEXTURE_2D, jeeptexture);
	}
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 1);
	glVertex2f(carx - 25, cary + 50);
	glTexCoord2f(0, 0);
	glVertex2f(carx - 25, cary - 50);
	glTexCoord2f(1, 0);
	glVertex2f(carx + 25, cary - 50);
	glTexCoord2f(1, 1);
	glVertex2f(carx + 25, cary + 50);
	glEnd();


	for (i = 0; i < 4; i++)
	{
		glBindTexture(GL_TEXTURE_2D, npcredtexture);
		if (menunpc == 0 || menunpc == 1){
			glBindTexture(GL_TEXTURE_2D, npcredtexture);

		}
		else if (menunpc == 2){
			glBindTexture(GL_TEXTURE_2D, npcbluetexture);

		}


		glBegin(GL_QUADS);

		glTexCoord2f(0, 1);
		glVertex2f(npcx[i] - 25, npcy[i] + 50);
		glTexCoord2f(0, 0);
		glVertex2f(npcx[i] - 25, npcy[i] - 50);
		glTexCoord2f(1, 0);
		glVertex2f(npcx[i] + 25, npcy[i] - 50);
		glTexCoord2f(1, 1);
		glVertex2f(npcx[i] + 25, npcy[i] + 50);
		glEnd();
		npcy[i] = npcy[i] - 6;
		if (npcy[i] > cary - 45 - 45 && npcy[i] < cary + 45 + 45 && npcx[i] == carx)
		{

			exit(0);
		}

		if (npcy[i] < -50)
		{
			u = rand() % 4 + 1;
			switch (u)
			{
			case 1:
				npcx[i] = 250;  //fahrt links
				break;
			case 2:
				npcx[i] = 350;  //fahrt links mitte
				break;
			case 3:
				npcx[i] = 450;  //fahrt rechts mitte
				break;
			case 4:
				npcx[i] = 550;  //fahrt rechts
				break;

			}
			npcy[i] = 900;   //Abstand zwischen den 4 Autos
		}
	}

	movement = movement - 10;
	if (movement < -65)
	{
		movement = 0;
	}

	glutSwapBuffers();


}

void main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	window = glutCreateWindow("Autospiel");
	createMenu();
	glEnable(GL_TEXTURE_2D);
	roadtexture = loadBMP_custom("road.bmp");
	roadtexture2 = loadBMP_custom("dirtyroad.bmp");
	grastexture = loadBMP_custom("gras.bmp");
	sandtexture = loadBMP_custom("sand.bmp");
	cabriotexture = loadBMP_custom("mycar.bmp");
	jeeptexture = loadBMP_custom("jeep.bmp");
	npcredtexture = loadBMP_custom("npcred.bmp");
	npcbluetexture = loadBMP_custom("npcblue.bmp");
	init();
	glutDisplayFunc(&display);
	glutKeyboardFunc(&keyPressed);
	
	glutIdleFunc(&display);

	glutMainLoop();
}