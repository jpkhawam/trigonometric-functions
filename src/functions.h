#ifndef TRIGONOMETRICFUNCTIONS_FUNCTIONS_H
#define TRIGONOMETRICFUNCTIONS_FUNCTIONS_H

#include <GL/glut.h>
#include <cmath>
#include <string>
#include "types.h"

bool allPaused() {
    return g_MODE_SIN || g_MODE_COS || g_MODE_TAN || g_MODE_ASIN || g_MODE_ACOS || g_MODE_ATAN;
}

void pauseAll() {
    g_MODE_SIN = false;
    g_MODE_COS = false;
    g_MODE_TAN = false;
    g_MODE_ASIN = false;
    g_MODE_ACOS = false;
    g_MODE_ATAN = false;
    g_offset = 0;
}

void drawString(float x, float y, const std::string &string, RGB rgb) {
    glColor3f(rgb.red, rgb.green, rgb.blue);
    glRasterPos2f(x, y);
    for (char i: string) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, i);
    }
}

void drawFunctionBox(float x, float y, const std::string &string, RGB rgb, float margin) {
    glBegin(GL_POLYGON);
    // draw polygons counter clock wise to make sure you draw the front face
    // so top left, bottom left, bottom right, top right
    glVertex2f(-3.4f + margin, 1.4);
    glVertex2f(-3.4f + margin, 1.25);
    glVertex2f(-2.6f + margin, 1.25);
    glVertex2f(-2.6f + margin, 1.4);
    glEnd();

    drawString(x, y, string, rgb);
}

void drawAxes() {
    glLineWidth(2);
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    // X-AXIS
    glVertex2f(-4, 0);
    glVertex2f(4, 0);
    // draw > at the end of X-axis
    // bottom line
    glVertex2f(4, 0.1);
    glVertex2f(4 + 0.4, 0);
    // top line
    glVertex2f(4, -0.1);
    glVertex2f(4 + 0.4, 0);

    // Y-AXIS
    glVertex2f(0, -1);
    glVertex2f(0, 1);
    // draw ^ at the top of Y-axis
    // left line
    glVertex2f(0 - 0.2, 1);
    glVertex2f(0, 1 + 0.15);
    // right line
    glVertex2f(0 + 0.2, 1);
    glVertex2f(0, 1 + 0.15);
    glEnd();

    // draw ---|---|---|--- marks on the x axis
    for (int i = -4; i < 4; i++) {
        if (i == 0) {
            continue;
        }

        drawString(static_cast<float>(i), 0.05, std::to_string(i), RGB(1, 1, 1));
        glBegin(GL_LINES);
        glVertex2f(static_cast<float>(i), -0.04);
        glVertex2f(static_cast<float>(i), 0.04);
        glEnd();
    }

    for (float i = -4; i < 4; i = i + 0.2f) {
        glBegin(GL_LINES);
        glVertex2f(i, -0.02);
        glVertex2f(i, 0.02);
        glEnd();
    }

    // 4 and 0 need to be written a little away, so they don't coincide with the axes
    drawString(3.9, 0.05, "4", RGB(1, 1, 1));

    // draw marks on the y-axis
    for (float i = -1; i <= 1; i = i + 0.1f) {
        glBegin(GL_LINES);
        glVertex2f(-0.05, i);
        glVertex2f(0.05, i);
        glEnd();
    }

    for (float i = -1; i <= 1; i = i + 0.5f) {
        std::string value;
        if (i == 0)
            // already drawn for x
            continue;
        if (i < 0)
            // account for -
            value = std::to_string(i).substr(0, 4);
        if (i > 0)
            value = std::to_string(i).substr(0, 3);

        drawString(0.06, i, value, RGB(1, 1, 1));
    }
}

void drawButtons() {
    float numberOfButtonsDrawn{};
    int maxNumberOfButtons{7};

    float buttonWidth{0.85};
    float spacing{0.15};

    float y{1.3};
    float x{-3.33};

    RGB white = RGB(1, 1, 1);
    RGB black = RGB(0, 0, 0);

    glColor3f(1, 1, 1);

    for (int i = 0; i < maxNumberOfButtons; i++) {
        float margin = numberOfButtonsDrawn * (buttonWidth + spacing);
        RGB textColor = white;
        glColor3f(0.3, 0.3, 0.3);

        switch (i) {
            case equations::sine:
                if (g_MODE_SIN) {
                    glColor3f(1, 0, 0);
                }
                drawFunctionBox(x + margin + .1f, y, "sine (s)", textColor, margin);
                break;

            case equations::cosine:
                if (g_MODE_COS) {
                    glColor3f(0, 1, 0);
                    textColor = black;
                }
                drawFunctionBox(x + margin + .052f, y, "cosine (c)", textColor, margin);
                break;

            case equations::tangent:
                if (g_MODE_TAN) {
                    glColor3f(0, 0, 1);
                }
                drawFunctionBox(x + margin, y, "tangent (t)", textColor, margin);
                break;

            case equations::pause:
                if (!allPaused()) {
                    glColor3f(0, 0, 0);
                }
                drawFunctionBox(x + margin + .06f, y, "pause (p)", textColor, margin);
                break;

            case equations::arcSine:
                if (g_MODE_ASIN) {
                    glColor3f(1, 1, 0);
                    textColor = black;
                }
                drawFunctionBox(x + margin, y, "arc sine (i)", textColor, margin);
                break;

            case equations::arcCosine:
                if (g_MODE_ACOS) {
                    glColor3f(1, 0, 1);
                    textColor = black;
                }
                drawFunctionBox(x + margin, y, "arc cos (o)", textColor, margin);
                break;

            case equations::arcTangent:
                if (g_MODE_ATAN) {
                    glColor3f(0, 1, 1);
                    textColor = black;
                }
                drawFunctionBox(x + margin, y, "arc tan (a)", textColor, margin);
                break;

            default:
                break;
        }

        numberOfButtonsDrawn++;
    }
}

void drawFunction(float offset, equations equation) {
    int numberOfPoints{};
    int pointsToDraw{static_cast<int>(300 - offset * 4)};
    if (offset < 1)
        pointsToDraw = 250;
    if (offset < 0.5)
        pointsToDraw = 200;

    for (float i = -5; numberOfPoints < pointsToDraw; i = i + 0.01f) {
        glBegin(GL_POINTS);

        switch (equation) {
            case equations::sine:
                glColor3f(1, 0, 0);
                if (i + offset < 4 && i + offset > -4)
                    glVertex2f(i + offset, std::sin(i + offset));
                break;

            case equations::cosine:
                glColor3f(0, 1, 0);
                if (i + offset < 4 && i + offset > -4)
                    glVertex2f(i + offset, std::cos(i + offset));
                break;

            case equations::tangent:
                glColor3f(0, 0, 1);
                if (std::tan(i + offset) < 1.15 && std::tan(i + offset) > -1.35)
                    glVertex2f(i + offset, std::tan(i + offset));
                break;

            case equations::arcSine:
                glColor3f(1, 1, 0);
                if (std::asin(i + offset) < 1.15 && std::asin(i + offset) > -1.35)
                    glVertex2f(i + offset, std::asin(i + offset));
                break;

            case equations::arcCosine:
                glColor3f(1, 0, 1);
                if (std::acos(i + offset) < 1.15 && std::acos(i + offset) > -1.35)
                    glVertex2f(i + offset, std::acos(i + offset));
                break;

            case equations::arcTangent:
                glColor3f(0, 1, 1);
                if (std::atan(i + offset) < 1.15 && std::atan(i + offset) > -1.35)
                    glVertex2f(i + offset, std::atan(i + offset));
                break;

            default:
                break;
        }

        glEnd();
        numberOfPoints++;
    }
}

#endif //TRIGONOMETRICFUNCTIONS_FUNCTIONS_H
