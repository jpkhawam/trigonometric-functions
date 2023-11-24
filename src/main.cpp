#include <GL/glut.h>
#include "functions.h"

constexpr int SCREEN_WIDTH = 1920;
constexpr int SCREEN_HEIGHT = 1080;

bool g_MODE_SIN{};
bool g_MODE_COS{};
bool g_MODE_TAN{};
bool g_MODE_ASIN{};
bool g_MODE_ACOS{};
bool g_MODE_ATAN{};
float g_offset{};

void render();

void reshape(int, int);

void timer(int);

void onKeyboardPress(unsigned char characterPressed, __attribute__((unused)) int x, __attribute__((unused)) int y);

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    // GLUT_DOUBLE means double buffer
    // the front buffer is the buffer shown on the screen, the back buffer is the buffer on which we draw
    // when we want to display the back buffer, we can just swap the two via glutSwapBuffers()
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(0, 0);
    // you can modify these values to match your screen resolution
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("Trigonometric Functions");

    // set the default background color (when color buffer is cleared)
    glClearColor(0.2, 0.2, 0.2, 0.2);
    glPointSize(3);

    // set display function, called when the window is created
    glutDisplayFunc(render);
    // specify viewport, called whenever the window is created, or whenever the window is resized
    glutReshapeFunc(reshape);
    // set a timer function to keep refreshing display
    glutTimerFunc(200, timer, 0);
    // set keyboard event function
    glutKeyboardFunc(onKeyboardPress);

    // tells OpenGL the initialization process is over and tells it to start rendering
    glutMainLoop();
}

void render() {
    // clears the color bits from the framebuffer (effectively clearing the screen)
    glClear(GL_COLOR_BUFFER_BIT);
    // resets all the transformations of the current matrix
    glLoadIdentity();

    drawAxes();
    drawButtons();

    if (g_MODE_SIN)
        drawFunction(g_offset, equations::sine);
    if (g_MODE_COS)
        drawFunction(g_offset, equations::cosine);
    if (g_MODE_TAN)
        drawFunction(g_offset, equations::tangent);
    if (g_MODE_ASIN)
        drawFunction(g_offset, equations::arcSine);
    if (g_MODE_ACOS)
        drawFunction(g_offset, equations::arcCosine);
    if (g_MODE_ATAN)
        drawFunction(g_offset, equations::arcTangent);

    if (g_offset < 8)
        g_offset += 0.1;
    else
        g_offset = 0;

    // swap the back buffer with the front buffer to display what we just drew
    glutSwapBuffers();
}

// the width and height are provided from the api whenever they are changed
void reshape(int windowWidth, int windowHeight) {
    // set the viewport (the area in the window in which to draw)
    // everything outside the viewport will be clipped
    // glViewport(x, y, width, height). The (x, y) coordinates are where in the window to start drawing the viewport
    // aka the coordinates of the bottom left corner of the viewport
    glViewport(0, 0, windowWidth, windowHeight); // full screen

    // set the projection matrix, we are currently in the model view (GL_MODELVIEW) matrix
    // we should always be in the model view matrix when drawing
    // switch to the projection matrix to set the desired projection
    glMatrixMode(GL_PROJECTION);
    // reset the parameters of the projection matrix
    glLoadIdentity();
    // set the projection as a 2-dimensional cartesian orthogonal frame
    // --------------
    // |     ^ y    |
    // |     |      |
    // |-----|----->| x
    // |     |      |
    // |     |      |
    // --------------
    // farthest left,    right,      bottom,     top
    gluOrtho2D(-5, 5, -1.5, 1.5);
    // we are done modifying the projection matrix, go back to model view matrix
    glMatrixMode(GL_MODELVIEW);
}

void timer(int) {
    // ask OpenGL to call the display function again
    glutPostRedisplay();
    // 60 frames per second
    glutTimerFunc(1000 / 60, timer, 0);
}

// x and y are mouse cursor position when key was pressed
void onKeyboardPress(unsigned char characterPressed, __attribute__((unused)) int x, __attribute__((unused)) int y) {
    switch (characterPressed) {
        case 'q':
        case 'Q':
            exit(0);
        case 's':
        case 'S':
            g_MODE_SIN = !g_MODE_SIN;
            return;
        case 'c':
        case 'C':
            g_MODE_COS = !g_MODE_COS;
            return;
        case 't':
        case 'T':
            g_MODE_TAN = !g_MODE_TAN;
            return;
        case 'i':
        case 'I':
            g_MODE_ASIN = !g_MODE_ASIN;
            return;
        case 'o':
        case 'O':
            g_MODE_ACOS = !g_MODE_ACOS;
            return;
        case 'a':
        case 'A':
            g_MODE_ATAN = !g_MODE_ATAN;
            return;
        case 'p':
        case 'P':
            pauseAll();
            return;
        default:
            return;
    }
}
