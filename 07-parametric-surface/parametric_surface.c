#include <math.h>
#include <GL/glut.h>

#define LENGTH 2*M_PI
#define STEP_L M_PI/45
#define HEIGHT 5.0f
#define STEP_H 0.2f

static int camera = 0;

void renderParametricCilinder(void) {
  float i, j;

  glColor3f(1.0f, 1.0f, 1.0f);
  for (i = 0.0f; i <= floor(HEIGHT); i += STEP_H) {
    for (j = 0.0f; j < LENGTH; j += STEP_L) {
      glBegin(GL_LINE_LOOP);
      glVertex3f( (float)cos(j), (float)sin(j), (float)i );
      glVertex3f( (float)cos(j + STEP_L), (float)sin(j + STEP_L), (float)i );
      glEnd();

      glBegin(GL_LINE_LOOP);
      glVertex3f( (float)cos(j), (float)sin(j), (float)(i + STEP_H) );
      glVertex3f( (float)cos(j), (float)sin(j), (float)i );
      glEnd();
    }
  }
  for (j = 0.0f; j < LENGTH; j += STEP_L) {
    glBegin(GL_LINE_LOOP);
    glVertex3f( (float)cos(j), (float)sin(j), (float)i );
    glVertex3f( (float)cos(j + STEP_L), (float)sin(j + STEP_L), (float)i );
    glEnd();
  }
}

void display(void) {
  glClearColor(0.0f, 0.0f, 0.0f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  glTranslatef(0.0f, -2.5f, -10.0f);
  glRotatef((GLfloat) camera, 2.0, 0.0, 0.0);
  renderParametricCilinder();
  glFlush();
}

void reshape(int width, int height) {
  glViewport(0, 0, (GLsizei) width, (GLsizei) height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
}

void keyboard (unsigned char key, int x, int y) {
  switch (key) {
    case 'c':
      camera = (camera + 10) % 360;
      break;
    case 'C':
      camera = (camera - 10) % 360;
      break;
    default:
      return;
  }
  glutPostRedisplay();
}

int main(int argc, char **argv) {
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE);

  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Davi Kooji Uezono - RA:097464 - 19/05");
  
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);


  glutMainLoop();

  return 0;
}
