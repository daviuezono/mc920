#include <stdio.h>
#include <GL/glut.h>

#define TRUE  1
#define FALSE 0
/*
char keyStates[256];
int movingUp = FALSE;
float yLocation = 0.0f;
float yRotationAngle = 0.0f;
*/
GLfloat angle = 0.0;

GLfloat redDiffuseMaterial[] = {1.0, 0.0, 0.0}; //set the material to red
GLfloat whiteSpecularMaterial[] = {1.0, 1.0, 1.0}; //set the material to white
GLfloat greenEmissiveMaterial[] = {0.0, 1.0, 0.0}; //set the material to green
GLfloat whiteSpecularLight[] = {1.0, 1.0, 1.0}; //set the light specular to white
GLfloat blackAmbientLight[] = {0.0, 0.0, 0.0}; //set the light ambient to black
GLfloat whiteDiffuseLight[] = {1.0, 1.0, 1.0}; //set the diffuse light to white
GLfloat blankMaterial[] = {0.0, 0.0, 0.0}; //set the diffuse  light to white
GLfloat mShininess[] = {128}; //set the shininess of the material

int diffuse = FALSE;
int emissive = FALSE;
int specular = FALSE;
/*
void keyOperations(void) {
  if (keyStates[GLUT_KEY_LEFT]) {
    // TODO something.
  }
  glutPostRedisplay();
}
*/
void cube() {
  glRotatef(angle, 1.0, 0.0, 0.0);
  glRotatef(angle, 0.0, 1.0, 0.0);
  glRotatef(angle, 0.0, 0.0, 1.0);
  glColor3f(1.0, 0.0, 0.0);
  glutSolidCube(2.0f);
}

void init (void) {
  glEnable (GL_DEPTH_TEST);
  glEnable (GL_LIGHTING);
  glEnable (GL_LIGHT0);
}

void light (void) {
  glLightfv(GL_LIGHT0, GL_SPECULAR, whiteSpecularLight);
  glLightfv(GL_LIGHT0, GL_AMBIENT, blackAmbientLight);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteDiffuseLight);
}

void display(void) {
  /*
  keyOperations();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  */
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  light();
  /*
  gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  */
  glTranslatef(0.0f, 0.0f, -5.0f);
  /*
  glTranslatef(0.0f, yLocation, 0.0f);
  glRotatef(yRotationAngle, 0.0f, 1.0f, 0.0f);

  glScalef(0.5f, 1.0f, 2.0f);
  glutWireCube(2.0f);
  */
  glRotatef(angle, 1, 1, 1);
  //glutSolidTeapot(2.0f);
  cube();
  glutSwapBuffers();
  /*
  if (movingUp)
    yLocation -= 0.05f;
  else
    yLocation += 0.05f;

  if (yLocation < -3.0f)
    movingUp = FALSE;
  else if (yLocation > 3.0f)
    movingUp = TRUE;

  yRotationAngle += 0.1f;
  if (yRotationAngle > 360.0f)
    yRotationAngle -= 360.0f;
  */
  angle++;
}

void reshape(int width, int height) {
  glViewport(0, 0, (GLsizei) width, (GLsizei) height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
}

/*
void keyPressed(unsigned char key, int x, int y) {
  keyStates[key] = TRUE;
}

void keyUp(unsigned char key, int x, int y) {
  keyStates[key] = FALSE;
}
*/

void keyboard (unsigned char key, int x, int y) {
  if (key == 's') {
    if (specular == FALSE) {
      specular = TRUE;
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, whiteSpecularMaterial);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
    }
    else if (specular == TRUE) {
      specular = FALSE;
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, blankMaterial);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, blankMaterial);
    }
  }
  if (key == 'd') {
    if (diffuse == FALSE) {
      diffuse = TRUE;
      glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, redDiffuseMaterial);
    }
    else if (diffuse == TRUE) {
      diffuse = FALSE;
      glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blankMaterial);
    }
  }
  if (key == 'e') {
    if (emissive == FALSE) {
      emissive = TRUE;
      glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, greenEmissiveMaterial);
    }
    else if (emissive == TRUE) {
      emissive = FALSE;
      glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, blankMaterial);
    }
  }
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
  //glutKeyboardFunc(keyPressed);
  glutKeyboardFunc(keyboard);
  //glutKeyboardUpFunc(keyUp);

  glutMainLoop();

  return 0;
}
