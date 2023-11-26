#include <GL/glut.h>

int wh = 0;
GLenum mode = GL_CCW;
void init()
{
glClearColor( 0.0, 0.0, 0.0, 0.0 );
glColor3f( 1.0f, 1.0f, 0.0f );

glEnable( GL_CULL_FACE );
glCullFace( GL_BACK );
glPolygonMode( GL_FRONT, GL_FILL );
}

void reshape( int width, int height )
{
glMatrixMode( GL_PROJECTION );
glLoadIdentity();
gluOrtho2D( -1.0, 1.0, -1.0, 1.0 );
glMatrixMode( GL_MODELVIEW );
glLoadIdentity();
glViewport( 0, 0, width, height );

wh = height;
}

void display()
{
glClear( GL_COLOR_BUFFER_BIT );
glFrontFace( mode );
glBegin( GL_POLYGON );
glVertex3f( -0.5, -0.5, 0.0 );
glVertex3f( 0.5, -0.5, 0.0 );
glVertex3f( 0.5, 0.5, 0.0 );
glVertex3f( -0.5, 0.5, 0.0 );
glEnd();
glFlush();
glutSwapBuffers();
}

void idle()
{
glutPostRedisplay();
}
void keyboard( unsigned char key, int x, int y )
{
switch( key )
{
case 'A': case 'a':
mode = GL_CW ;
break;
case 'S': case 's':
mode = GL_CCW;
break;
}

}
int main( int argc, char* argv[] )
{
glutInit( &argc, argv );
glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA );
glutInitWindowSize( 500, 500 );
glutCreateWindow( "BackFace" );
glutDisplayFunc( display );
glutReshapeFunc( reshape );
glutKeyboardFunc( keyboard );
glutIdleFunc( idle );
init();
glutMainLoop();

return 0;
}