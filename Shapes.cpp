#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>
#include "Shapes.h"
#include "Log.h"

void drawCircle(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_LINE_LOOP);
        for (int i = 0; i < num_segments; i++)
        {
            float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle
            float x = r * cosf(theta);//calculate the x component
            float y = r * sinf(theta);//calculate the y component
            glVertex2f(x + cx, y + cy);//output vertex
        }
    glEnd();
}

void drawCircleFilled(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx,cy);
        for (int i = 0; i <= num_segments; i++)
        {
            float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle
            float x = r * cosf(theta);//calculate the x component
            float y = r * sinf(theta);//calculate the y component
            glVertex2f(x + cx, y + cy);//output vertex
        }
    glEnd();
}

void drawRectangleFilled(float x, float y, float w, float h, bool originAtCenter)
{
    if(originAtCenter)
    {
        x = x - w*0.5f;
        y = y - h*0.5f;
    }
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y + h);
        glVertex2f(x, y + h);
    glEnd();
}

void drawRectangle(float x, float y, float w, float h, bool originAtCenter)
{
    if(originAtCenter)
    {
        x = x - w*0.5f;
        y = y - h*0.5f;
    }
    glBegin(GL_LINE_LOOP);
        glVertex2f(x, y);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y + h);
        glVertex2f(x, y + h);
    glEnd();
}

void drawKing(float x, float y, float size)
{
    //glPushMatrix();

    float px[6] = {x, x+size*0.5f, x-size*0.5f, x+size*0.7f, x,x-size*0.7f};
    float py[6] = {y+size*1.f, y, y, y+size*0.66f, y, y+size*0.66f};

    glBegin(GL_TRIANGLES);
        glVertex2f(px[0], py[0]);
        glVertex2f(px[1], py[1]);
        glVertex2f(px[2], py[2]);

        glVertex2f(px[1], py[1]);
        glVertex2f(px[3], py[3]);
        glVertex2f(px[4], py[4]);

        glVertex2f(px[4], py[4]);
        glVertex2f(px[5], py[5]);
        glVertex2f(px[2], py[2]);
    glEnd();

    drawCircleFilled(px[0], py[0]+size*0.06f, size*0.08f, 15);
    drawCircleFilled(px[3], py[3]+size*0.06f, size*0.08f, 15);
    drawCircleFilled(px[5], py[5]+size*0.06f, size*0.08f, 15);

    glBegin(GL_QUADS);
        glVertex2f(px[2], py[2]-size*0.1f);
        glVertex2f(px[2], py[2]-size*0.2f);
        glVertex2f(px[1], py[1]-size*0.2f);
        glVertex2f(px[1], py[1]-size*0.1f);
    glEnd();

    //glPopMatrix();
}


