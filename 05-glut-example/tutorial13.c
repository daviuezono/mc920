#include <GL/gl.h>
#include <GL/glut.h>

//angle of rotation
GLfloat angle = 0.0;

//diffuse light color variables
GLfloat dlr = 1.0;
GLfloat dlg = 1.0;
GLfloat dlb = 1.0;

//ambient light color variables
GLfloat alr = 1.0;
GLfloat alg = 1.0;
GLfloat alb = 1.0;

//light position variables
GLfloat lx = 0.0;
GLfloat ly = 0.0;
GLfloat lz = 1.0;
GLfloat lw = 0.0;

//draw the cube
void cube (void) {
  glRotatef(angle, 1.0, 0.0, 0.0); //rotate on the x axis
  glRotatef(angle, 0.0, 1.0, 0.0); //rotate on the y axis
  glRotatef(angle, 0.0, 0.0, 1.0); //rotate on the z axis
  glutSolidCube(2); //draw the cube
}

void init (void) {
  glEnable (GL_DEPTH_TEST); //enable the depth testing
  glEnable (GL_LIGHTING); //enable the lighting
  glEnable (GL_LIGHT0); //enable LIGHT0, our Diffuse Light
  glEnable (GL_LIGHT1); //enable LIGHT1, our Ambient Light
  glShadeModel (GL_SMOOTH); //set the shader to smooth shader
}

void display (void) {
  glClearColor (0.0,0.0,0.0,1.0); 
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
  glLoadIdentity();  
  GLfloat DiffuseLight[] = {dlr, dlg, dlb}; 
  GLfloat AmbientLight[] = {alr, alg, alb}; 
  glLightfv (GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
  glLightfv (GL_LIGHT1, GL_AMBIENT, AmbientLight);
  GLfloat LightPosition[] = {lx, ly, lz, lw};
  glLightfv (GL_LIGHT0, GL_POSITION, LightPosition);
  gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  //camera position, x,y,z, looking at x,y,z, Up Positions of the camera
  cube();
  glutSwapBuffers(); //swap the buffers
  angle++; //increase the angle
}

void reshape (int w, int h) {
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION); 

  glLoadIdentity();
  gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
}

void keyboard (unsigned char key, int x, int y) {
  if (key=='r') {
    dlr = 1.0; //change light to red
    dlg = 0.0;
    dlb = 0.0;
  }
  if (key=='g') {
    dlr = 0.0; //change light to green
    dlg = 1.0;
    dlb = 0.0;
  }
  if (key=='b') {
    dlr = 0.0; //change light to blue
    dlg = 0.0;
    dlb = 1.0;
  }
  if (key=='w') {
    ly += 10.0; //move the light up
  }
  if (key=='s') {
    ly -= 10.0; //move the light down
  }
  if (key=='a') {
    lx -= 10.0; //move the light left
  }
  if (key=='d') {
    lx += 10.0; //move the light right
  }
}

int main (int argc, char **argv) {
  glutInit (&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize (500, 500);
  glutInitWindowPosition (100, 100);
  glutCreateWindow ("A basic OpenGL Window");
  init ();
  glutDisplayFunc (display);
  glutIdleFunc (display);
  glutReshapeFunc (reshape);

  glutKeyboardFunc (keyboard);
  glutMainLoop ();
  return 0;
}