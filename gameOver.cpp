#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static void out_string_at(void *font, int x, int y, char *string)
{
#ifdef __FREEGLUT_EXT_H__
    glRasterPos2f((GLfloat)x, (GLfloat)y);
    glutBitmapString( font, (const unsigned char *)string );
#else
    int len, i;
    glRasterPos2f((GLfloat)x, (GLfloat)y);
    len = (int) strlen(string);
    for (i = 0; i < len; i++) {
        glutBitmapCharacter(font, string[i]);
    }
#endif
}

static void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);
    out_string_at( GLUT_BITMAP_TIMES_ROMAN_24, 250, 300, "Game Over" );
    glFlush ();
}
static void reshape(int w, int h){
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluOrtho2D (0.0, (GLdouble) w, 0.0, (GLdouble) h);
}
static void keyboard(unsigned char key, int x, int y)
{
    if((key == 0x1b)||(key == 'q')||(key == 'Q'))
        exit(0);
}
int main (int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (600, 600);
    glutCreateWindow ("");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}