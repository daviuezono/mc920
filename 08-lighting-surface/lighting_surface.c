#include <math.h>
#include <GL/glut.h>

#define LENGTH 2*M_PI
#define STEP_L M_PI/45
#define HEIGHT 5.0f
#define STEP_H 0.2f

#define TRUE  1
#define FALSE 0

static int camera = 0;
GLfloat angle = 0.0;

GLfloat specular_light[] = {1.0, 1.0, 1.0};
GLfloat ambient_light[] = {0.0, 0.0, 0.0};
GLfloat diffuse_light[] = {1.0, 1.0, 1.0};

GLfloat specular_material[] = {1.0, 1.0, 1.0};
GLfloat diffuse_material[] = {1.0, 0.0, 0.0};
GLfloat emissive_material[] = {0.0, 1.0, 0.0};

GLfloat blank_material[] = {0.0, 0.0, 0.0};

GLfloat shininess[] = {128};

int specular = FALSE;

void renderParametricCilinder(void) {
  float i, j;

  glColor3f(1.0f, 1.0f, 0.0f);
  for (i = 0.0f; i <= floor(HEIGHT); i += STEP_H) {
    for (j = 0.0f; j < LENGTH; j += STEP_L) {
      glBegin(GL_TRIANGLES);
      glVertex3f( (float)cos(j), (float)sin(j), (float)(i + STEP_H) );
      glVertex3f( (float)cos(j), (float)sin(j), (float)i );
      glVertex3f( (float)cos(j + STEP_L), (float)sin(j + STEP_L), (float)i );
      glEnd();

      glBegin(GL_TRIANGLES);
      glVertex3f( (float)cos(j + STEP_L), (float)sin(j + STEP_L), (float)i );
      glVertex3f( (float)cos(j + STEP_L), (float)sin(j + STEP_L), (float)(i + STEP_H) );
      glVertex3f( (float)cos(j), (float)sin(j), (float)(i + STEP_H) );
      glEnd();
    }
  }
}

void init(void) {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
}

void display(void) {
  glClearColor(0.0f, 0.0f, 0.0f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
  glLoadIdentity();
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);

  glTranslatef(0.0f, -2.5f, -10.0f);
  glRotatef((GLfloat) camera, 2.0, 0.0, 0.0);
  gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  renderParametricCilinder();
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

void keyboard (unsigned char key, int x, int y) {
  switch (key) {
    case 'c':
      camera = (camera + 10) % 360;
      break;
    case 'C':
      camera = (camera - 10) % 360;
      break;
    case 's':
      if (specular == FALSE) {
        specular = TRUE;
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
      }
      else if (specular == TRUE) {
        specular = FALSE;
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, blank_material);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, blank_material);
      }
      break;
  }
  glutPostRedisplay();
}

int main(int argc, char **argv) {
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Davi Kooji Uezono - RA:097464 - 26/05");
  
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);


  glutMainLoop();

  return 0;
}
