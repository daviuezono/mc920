#include <GL/glut.h>

void display(void) {
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  glTranslatef(0.0f, 0.0f, -5.0f);
  
  // BLUE CONE
  glColor3f(0.0f, 0.0f, 1.0f);
  glRotatef(180.0, 0.0, 1.0, 0.0); // will rotate all elements from now on.
  glutWireCone(1.0, 0.5, 10, 50); 

  // GREEN SPHERE
  glColor3f(0.0f, 1.0f, 0.0f);
  glTranslatef(-2.0f, -2.0f, 0.0f);
  glutWireSphere(1.0, 10, 50);
  
  // RED CUBE
  glColor3f(1.0f, 0.0f, 0.0f);
  glTranslatef(0.0f, 4.0f, 0.0f);
  glutWireCube(2.0);
  
  // CYAN TORUS
  glColor3f(0.0f, 1.0f, 1.0f);
  glTranslatef(4.0f, 0.0f, 0.0f);
  glutWireTorus(1.0, 0.5, 10, 50);
  
  // MAGENTA TEAPOT
  glColor3f(1.0f, 0.0f, 1.0f);
  glTranslatef(0.0f, -4.0f, 0.0f);
  glRotatef(180.0, 0.0, 1.0, 0.0); // will rotate this element 180 degrees.
  glutWireTeapot(1.0);

  glFlush();
}

void reshape(int width, int height) {
  glViewport(0, 0, (GLsizei) width, (GLsizei) height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE);

  glutInitWindowSize(500, 500);
  glutInitWindowPosition(50, 50);
  glutCreateWindow("Davi Kooji Uezono - RA:097464 - 12/05");

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);

  glutMainLoop();

  return 0;
}
