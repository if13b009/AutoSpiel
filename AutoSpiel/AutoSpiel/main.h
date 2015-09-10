#include<iostream>
#include<glut.h>

using namespace std;
int carx = 350, cary = 70;
int npcx[4], npcy[4];
int movement, submenu1, submenu2, submenu3, submenu4, submenu5, menu_id, window, menucar, menunpc, menuroad, menugras;
int i, u, o, menumiddle, submenu0, menucolor;
int value = 0;
bool fullscreen = false;
GLuint cabriotexture, jeeptexture;
GLuint npcbluetexture, npcredtexture;
GLuint roadtexture, roadtexture2;
GLuint grastexture, sandtexture;