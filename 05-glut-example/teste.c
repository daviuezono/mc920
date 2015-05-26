#include <stdio.h>
#include <GL/glut.h>

#define TRUE  1
#define FALSE 0

char keyStates[256];
int movingUp = FALSE;
float yLocation = 0.0f;
float yRotationAngle = 0.0f;
GLfloat angle = 0.0;

void keyOperations(void) {
  if (keyStates['e']) {
    fprintf(stderr, "EXIT\n");
  }
  /*
  else if (keyStates['r']) {
    glClearColor(1.f, 0.f, 0.f, 1.f);
  }
  else if (keyStates['g']) {
    glClearColor(0.f, 1.f, 0.f, 1.f);
  }
  else if (keyStates['b']) {
    glClearColor(0.f, 0.f, 1.f, 1.f);
  }
  glutPostRedisplay();
  */
  return;
}

void renderPrimitives2D(void) {
  /*
  glColor3f(0.0f, 0.0f, 1.0f);
  glBegin(GL_QUADS);
  glVertex3f(-1.0f, -1.0f, 0.0f);
  glVertex3f(-1.0f, 1.0f, 0.0f);
  glVertex3f(1.0f, 1.0f, 0.0f);
  glVertex3f(1.0f, -1.0f, 0.0f);
  glEnd();
  */

  glColor3f(1.0f, 0.0f, 0.0f);
  glPointSize(20.0f);  
  glBegin(GL_QUAD_STRIP); // Start drawing a point primitive  
  glVertex3f(-1.0f, -1.0f, 0.0f); // The bottom left corner  
  glVertex3f(-1.0f, 1.0f, 0.0f); // The top left corner  
  glVertex3f(1.0f, 1.0f, 0.0f); // The top right corner  
  glVertex3f(1.0f, -1.0f, 0.0f); // The bottom right corner  
  glEnd();  

  /*
  glColor3f(0.0f, 1.0f, 0.0f);
  glBegin(GL_LINE_LOOP); // Start drawing a line primitive  
  glVertex3f(-1.0f, -1.0f, 0.0f); // The bottom left corner  
  glVertex3f(-1.0f, 1.0f, 0.0f); // The top left corner  
  glVertex3f(1.0f, 1.0f, 0.0f); // The top right corner  
  glVertex3f(1.0f, -1.0f, 0.0f); // The bottom right corner  
  glEnd();
  */
}

void renderPrimitives3D(void) {
  // RED CUBE
  //glColor3f(1.0f, 0.0f, 0.0f);
  //glutWireCube(2.0);
  //glutSolidCube(2.0);

  // GREEN SPHERE
  //glColor3f(0.0f, 1.0f, 0.0f);
  //glutWireSphere(1.0, 10, 50);
  //glutSolidSphere(1.0, 50, 50);
  
  // BLUE CONE
  //glColor3f(0.0f, 0.0f, 1.0f);
  //glutWireCone(2.0, 1.0, 10, 50);
  //glutSolidCone(2.0, 1.0, 50, 50);

  // CYAN TORUS
  //glColor3f(0.0f, 1.0f, 1.0f);
  //glutWireTorus(1.0, 0.5, 10, 50);
  //glutSolidTorus(1.0, 0.5, 50, 50);

  // MAGENTA TEAPOT
  glColor3f(1.0f, 0.0f, 1.0f);
  //glutWireTeapot(1.0);
  glutSolidTeapot(1.0);
}

void display(void) {
  keyOperations();

  //glClearColor(0.0f, 0.0f, 0.0f, 1.f);
  //glClear(GL_COLOR_BUFFER_BIT);
  //glLoadIdentity();

  glClearColor (0.0,0.0,0.0,1.0);
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();  
  gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  glTranslatef(0.0f, 0.0f, -5.0f);
  //glTranslatef(0.0f, yLocation, 0.0f);
  glRotatef(yRotationAngle, 0.0f, 1.0f, 0.0f);

  renderPrimitives2D();
  //renderPrimitives3D();
  glFlush();

  if (movingUp) {
    yLocation -= 0.0005f;
  }
  else {
    yLocation += 0.0005f;
  }

  if (yLocation < -3.0f) {
    movingUp = FALSE;
  }
  else if (yLocation > 3.0f) {
    movingUp = TRUE;
  }

  yRotationAngle += 0.5f;
  if (yRotationAngle > 360.0f) {
    yRotationAngle -= 360.0f;
  }

  glutSwapBuffers();
  angle++;
}

void reshape(int width, int height) {
  glViewport(0, 0, (GLsizei) width, (GLsizei) height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
}

void keyPressed(unsigned char key, int x, int y) {
  keyStates[key] = TRUE;
}

void keyUp(unsigned char key, int x, int y) {
  keyStates[key] = FALSE;
}

void init (void) {
  glEnable (GL_DEPTH_TEST);
  glEnable (GL_LIGHTING);
  glEnable (GL_LIGHT0);
}

int main(int argc, char **argv) {
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("My first GLUT example \\o/");

  init();
  //glEnable(GL_COLOR_MATERIAL);  
  
  glutDisplayFunc(display);
  glutIdleFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyPressed);
  glutKeyboardUpFunc(keyUp);

  glutMainLoop();

  return 0;
}
