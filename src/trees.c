#include <math.h>
#include <stdlib.h>
#include <stdio.h>

unsigned char *buffer;
unsigned int width;
unsigned int height;

float a[4], b[4], c[4], d[4], e[4], f[4];
int p[4];
float *addresses[6];
int xscale, yscale, xoffset, yoffset;
void tree();
void fern();
void triangle();
void maze();
void koch();
int minx, maxx, miny, maxy;

void plot(int x, int y, char color)
{
    if (x < minx)
    {
        minx = x;
    }
    if (x > maxx)
    {
        maxx = x;
    }
    if (y < miny)
    {
        miny = y;
    }
    if (y > maxy)
    {
        maxy = y;
    }
    if (x < 0 || x >= width)
    {
        return;
    }
    if (y < 0 || y >= height)
    {
        return;
    }
    buffer[x * height + y] = color;
}

float **getAddresses()
{
    addresses[0] = &a[0];
    addresses[1] = &b[0];
    addresses[2] = &c[0];
    addresses[3] = &d[0];
    addresses[4] = &e[0];
    addresses[5] = &f[0];
    return &addresses[0];
}

unsigned char *renderTree(unsigned char *buf,
                          unsigned int inHeight, unsigned int inWidth, int model, int distort)
{

    printf("RenderTree %d %d %d %d\n", inHeight, inWidth, model, distort);

    buffer = buf;
    height = inHeight;
    width = inWidth;
    minx = 32768;
    maxx = -32768;
    miny = 32768;
    maxy = -32768;

    if (distort == 1)
    {
        float *arr;
        int which = rand() % 6;
        switch (which)
        {
        case 0:
            arr = &a[0];
            break;
        case 1:
            arr = &b[0];
            break;
        case 2:
            arr = &c[0];
            break;
        case 3:
            arr = &d[0];
            break;
        case 4:
            arr = &e[0];
            break;
        default:
            arr = &f[0];
        }
        int direction = rand() % 2 == 0 ? -1 : 1;
        int idx = rand() % 4;
        arr[idx] += 0.005 * direction;
    }
    else
    {
        switch (model)
        {
        case 1:
            tree();
            break;
        case 2:
            fern();
            break;
        case 3:
            triangle();
            break;
        case 4:
            maze();
            break;
        default:
            koch();
            break;
        }
    }

    int px, py;
    float x = 0, y = 0;
    for (int i = 0; i <= 99999; i++)
    {
        int j = rand() % 32678;
        int k = (j < p[0]) ? 0 : ((j < p[1]) ? 1 : ((j < p[2]) ? 2 : 3));
        float newx = (a[k] * x + b[k] * y + e[k]);
        y = (c[k] * x + d[k] * y + f[k]);
        x = newx;
        px = x * xscale + xoffset;
        py = y * yscale + yoffset;
        plot(px, py, 0x01);
    }

    printf("x: %d - %d y: %d - %d\n", minx, maxx, miny, maxy);
    return &buffer[0];
}

void tree()
{
    a[0] = 0;
    a[1] = 0.1;
    a[2] = 0.42;
    a[3] = .42;
    b[0] = 0;
    b[1] = 0;
    b[2] = -0.42;
    b[3] = 0.42;
    c[0] = 0;
    c[1] = 0;
    c[2] = 0.42;
    c[3] = -0.42;
    d[0] = 0.5;
    d[1] = 0.1;
    d[2] = 0.42;
    d[3] = 0.42;
    e[0] = 0;
    e[1] = 0;
    e[2] = 0;
    e[3] = 0;
    f[0] = 0;
    f[1] = 0.2;
    f[2] = 0.2;
    f[3] = 0.2;
    p[0] = 1638;
    p[1] = 6553;
    p[2] = 19660;
    p[3] = 32767;
    xscale = width * 2;
    yscale = height * 2;
    xoffset = width / 2;
    yoffset = 0;
}

void fern()
{
    a[0] = 0;
    a[1] = 0.2;
    a[2] = -0.15;
    a[3] = .85;
    b[0] = 0;
    b[1] = -0.26;
    b[2] = 0.28;
    b[3] = 0.04;
    c[0] = 0;
    c[1] = 0.23;
    c[2] = 0.26;
    c[3] = -0.04;
    d[0] = 0.16;
    d[1] = 0.22;
    d[2] = 0.24;
    d[3] = 0.85;
    e[0] = 0;
    e[1] = 0;
    e[2] = 0;
    e[3] = 0;
    f[0] = 0;
    f[1] = 0.2;
    f[2] = 0.2;
    f[3] = 0.2;
    p[0] = 328;
    p[1] = 2621;
    p[2] = 4915;
    p[3] = 32767;
    xscale = width * 1.2;
    yscale = height * 0.7;
    xoffset = width / 2;
    yoffset = 0;
}

void triangle()
{
    a[0] = a[1] = a[2] = 0.5;
    b[0] = b[1] = b[2] = 0;
    c[0] = c[1] = c[2] = 0;
    d[0] = d[1] = d[2] = 0.5;
    e[0] = 0;
    e[1] = 0.25;
    e[2] = 0.5;
    f[0] = f[2] = 0;
    f[1] = 0.5;
    p[0] = 32767 / 3;
    p[1] = p[0] * 2;
    p[2] = 32768;
    xscale = width;
    yscale = height;
    xoffset = 0;
    yoffset = 0;
}

void maze()
{
    a[0] = 0.33;
    a[1] = a[2] = 0;
    b[0] = 0;
    b[1] = 0.33;
    b[2] = -0.33;
    c[0] = 0;
    c[1] = c[2] = 1;
    d[0] = 0.33;
    d[1] = d[2] = 0;
    e[0] = e[2] = 0.33;
    e[1] = 0.66;
    f[0] = 0.66;
    f[1] = f[2] = 0;
    p[0] = 32767 / 7;
    p[1] = p[0] * 4;
    p[2] = 32768;
    xscale = width;
    yscale = height;
    xoffset = 0;
    yoffset = 0;
}

void koch()
{
    a[0] = 0.33;
    a[1] = a[2] = 0.16;
    a[3] = 0.33;
    b[0] = 0;
    b[1] = -0.2887;
    b[2] = 0.2887;
    b[3] = 0;
    c[0] = 0;
    c[1] = 0.2887;
    c[2] = -0.2887;
    c[3] = 0;
    d[0] = 0.33;
    d[1] = d[2] = 0.16;
    d[3] = 0.33;
    e[0] = 0;
    e[1] = 0.33;
    e[2] = 0.5;
    e[3] = 0.667;
    f[0] = f[1] = f[3] = 0;
    f[2] = 0.2887;
    p[0] = 8192;
    p[1] = 8192 * 2;
    p[2] = 8192 * 3;
    p[3] = 8192 * 4;
    xscale = width * 2;
    yscale = height * 3;
    xoffset = 0;
    yoffset = 0;
}