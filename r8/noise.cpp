/* coherent noise function over 1, 2 or 3 dimensions */
/* (copyright Ken Perlin) */

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#pragma warning(disable:4244)

#define B 0x100
#define BM 0xff

#define N 0x1000
#define NP 12   /* 2^N */
#define NM 0xfff

static p[B + B + 2];
static double g3[B + B + 2][3];
static double g2[B + B + 2][2];
static double g1[B + B + 2];
static start = 1;

static void init(void);
int random() { return rand(); }

inline int isprime(long i)
{
	long si,j;

	si = (long)sqrt((double)i);

	for (j = 2; (j <= si); j++) {
		if (i % j == 0)
			return 0;
	}

	return 1;
}


#define s_curve(t) ( t * t * (3. - 2. * t) )

#define lerp(t, a, b) ( a + t * (b - a) )

double cerp(double t, double a, double b)
{
	double f;
	f = (1 - cos(t * 3.141592653)) * .5;
	return  a * (1 - f) + b * f;
}

double interpolate(double x, double y, double a)
{
	double fac1 = 3 * pow(1 - a, 2) - 2 * pow(1 - a, 3);
	double fac2 = 3 * pow(a, 2) - 2 * pow(a, 3);

	return x * fac1 + y * fac2; //add the weighted factors
}
#define setup(i,b0,b1,r0,r1)\
	t = vec[i] + N;\
	b0 = ((int)t) & BM;\
	b1 = (b0+1) & BM;\
	r0 = t - (int)t;\
	r1 = r0 - 1.;

double noise1(double arg)
{
	int bx0, bx1;
	double rx0, rx1, sx, t, u, v, vec[1];

	vec[0] = arg;
	if (start) {
		start = 0;
		init();
	}

	setup(0, bx0,bx1, rx0,rx1);

	sx = s_curve(rx0);

	u = rx0 * g1[ p[ bx0 ] ];
	v = rx1 * g1[ p[ bx1 ] ];

	return lerp(sx, u, v);
}

double noise2(double vec[2])
{
	int bx0, bx1, by0, by1, b00, b10, b01, b11;
	double rx0, rx1, ry0, ry1, *q, sx, sy, a, b, t, u, v;
	register i, j;

	if (start) {
		start = 0;
		init();
	}

	setup(0, bx0,bx1, rx0,rx1);
	setup(1, by0,by1, ry0,ry1);

	i = p[ bx0 ];
	j = p[ bx1 ];

	b00 = p[ i + by0 ];
	b10 = p[ j + by0 ];
	b01 = p[ i + by1 ];
	b11 = p[ j + by1 ];

	sx = s_curve(rx0);
	sy = s_curve(ry0);

#define at2(rx,ry) ( rx * q[0] + ry * q[1] )

	q = g2[ b00 ] ; u = at2(rx0,ry0);
	q = g2[ b10 ] ; v = at2(rx1,ry0);
	a = lerp(sx, u, v);

	q = g2[ b01 ] ; u = at2(rx0,ry1);
	q = g2[ b11 ] ; v = at2(rx1,ry1);
	b = lerp(sx, u, v);

	return lerp(sy, a, b);
}

double base_noise(int x, int y)
{
	int n = x + y * 57;//12983;
    n = (n << 13) ^ n;
	return (1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
}

double smooth_noise(double x, double y)
{
	double corners = (base_noise(x - 1, y - 1) + 
					 base_noise(x + 1, y - 1) + 
					 base_noise(x - 1, y + 1) + 
					 base_noise(x + 1, y + 1)) / 16;
    double sides   = (base_noise(x - 1, y) + 
					 base_noise(x + 1, y) + 
					 base_noise(x, y - 1) + 
					 base_noise(x, y + 1)) /  8;
    double center  =  base_noise(x, y) / 4;
    return corners + sides + center;
}

double interp_noise(double x, double y)
{
	int intX    = (int)x;
	double fractional_X = x - intX;

	int integer_Y    = (int)y;
	double fractional_Y = y - integer_Y;

	double v1 = base_noise(intX,     integer_Y);
	double v2 = base_noise(intX + 1, integer_Y);
	double v3 = base_noise(intX,     integer_Y + 1);
	double v4 = base_noise(intX + 1, integer_Y + 1);

	double i1 = interpolate(v1, v2, fractional_X);
	double i2 = interpolate(v3, v4, fractional_X);

	return interpolate(i1, i2, fractional_Y);
}

double interp_noisexy(double x, double y)
{
	int bx0, bx1, by0, by1, b00, b10, b01, b11;
	double rx0, rx1, ry0, ry1, *q, sx, sy, a, b, t, u, v;
	register i, j;

	if (start) {
		start = 0;
		init();
	}

	t = x + N;
	bx0 = ((int)t) & BM;
	bx1 = (bx0+1) & BM;
	rx0 = t - (int)t;
	rx1 = rx0 - 1.;

	t = y + N;
	by0 = ((int)t) & BM;
	by1 = (by0+1) & BM;
	ry0 = t - (int)t;
	ry1 = ry0 - 1.;

	i = p[bx0];
	j = p[bx1];

	b00 = p[i + by0];
	b10 = p[j + by0];
	b01 = p[i + by1];
	b11 = p[j + by1];

	sx = s_curve(rx0);
	sy = s_curve(ry0);

#define at2(rx,ry) (rx * q[0] + ry * q[1])

	q = g2[b00]; u = at2(rx0,ry0);
	q = g2[b10]; v = at2(rx1,ry0);
	a = cerp(sx, u, v);

	q = g2[b01]; u = at2(rx0,ry1);
	q = g2[b11]; v = at2(rx1,ry1);
	b = cerp(sx, u, v);

	return cerp(sy, a, b);
}

double noisexy(double x, double y, int octaves)
{
	double noise = 0.0;
	double frequency = 1.0 / 64.0;
	double amplitude = 1.0;
	double p = 2;

	for (int i = 0; i < octaves; i++) {
		noise += interp_noise(x * frequency, y * frequency) * amplitude;
		amplitude /= p;
		frequency *= 2;
	}

	int rval = (int)(noise * 255.0);
	if (rval < 0) rval = 0;
	rval = (int)(255 - pow((double)0.99, (double)rval) * 255);

	return rval;
}


double noise3(double vec[3])
{
	int bx0, bx1, by0, by1, bz0, bz1, b00, b10, b01, b11;
	double rx0, rx1, ry0, ry1, rz0, rz1, *q, sy, sz, a, b, c, d, t, u, v;
	register i, j;

	if (start) {
		start = 0;
		init();
	}

	setup(0, bx0,bx1, rx0,rx1);
	setup(1, by0,by1, ry0,ry1);
	setup(2, bz0,bz1, rz0,rz1);

	i = p[ bx0 ];
	j = p[ bx1 ];

	b00 = p[ i + by0 ];
	b10 = p[ j + by0 ];
	b01 = p[ i + by1 ];
	b11 = p[ j + by1 ];

	t  = s_curve(rx0);
	sy = s_curve(ry0);
	sz = s_curve(rz0);

#define at3(rx,ry,rz) ( rx * q[0] + ry * q[1] + rz * q[2] )

	q = g3[ b00 + bz0 ] ; u = at3(rx0,ry0,rz0);
	q = g3[ b10 + bz0 ] ; v = at3(rx1,ry0,rz0);
	a = lerp(t, u, v);

	q = g3[ b01 + bz0 ] ; u = at3(rx0,ry1,rz0);
	q = g3[ b11 + bz0 ] ; v = at3(rx1,ry1,rz0);
	b = lerp(t, u, v);

	c = lerp(sy, a, b);

	q = g3[ b00 + bz1 ] ; u = at3(rx0,ry0,rz1);
	q = g3[ b10 + bz1 ] ; v = at3(rx1,ry0,rz1);
	a = lerp(t, u, v);

	q = g3[ b01 + bz1 ] ; u = at3(rx0,ry1,rz1);
	q = g3[ b11 + bz1 ] ; v = at3(rx1,ry1,rz1);
	b = lerp(t, u, v);

	d = lerp(sy, a, b);

	return lerp(sz, c, d);
}

static void normalize2(double v[2])
{
	double s;

	s = sqrt(v[0] * v[0] + v[1] * v[1]);
	v[0] = v[0] / s;
	v[1] = v[1] / s;
}

static void normalize3(double v[3])
{
	double s;

	s = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	v[0] = v[0] / s;
	v[1] = v[1] / s;
	v[2] = v[2] / s;
}

static void init(void)
{
	int i, j, k;

	srand(GetTickCount());

	for (i = 0 ; i < B ; i++) {
		p[i] = i;

		g1[i] = (double)((random() % (B + B)) - B) / B;

		for (j = 0 ; j < 2 ; j++)
			g2[i][j] = (double)((random() % (B + B)) - B) / B;
		normalize2(g2[i]);

		for (j = 0 ; j < 3 ; j++)
			g3[i][j] = (double)((random() % (B + B)) - B) / B;
		normalize3(g3[i]);
	}

	while (--i) {
		k = p[i];
		p[i] = p[j = random() % B];
		p[j] = k;
	}

	for (i = 0 ; i < B + 2 ; i++) {
		p[B + i] = p[i];
		g1[B + i] = g1[i];
		for (j = 0 ; j < 2 ; j++)
			g2[B + i][j] = g2[i][j];
		for (j = 0 ; j < 3 ; j++)
			g3[B + i][j] = g3[i][j];
	}
}

