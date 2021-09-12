#ifndef FIGURES_H
#define FIGURES_H


typedef struct Point {
	int x;
	int y;
} Point;

typedef struct Circle {
	Point c;
	int r;
} Circle;

typedef struct Rectangle {
	Point a;
	Point b;
} Rectangle;

typedef struct Triangle {
	Point a;
	Point b;
	Point c;
} Triangle;


typedef struct Figures {
	
	int circles_0;
	int circles_1;
	Circle ***circles;
	
	Triangle triangles[5][5];
	
	int rectangles_a;
	int rectangles_b;
	int rectangles_c;
	int rectangles_d;
	int rectangles_e;
	Rectangle*** rectangles[10][10][10];
} Figures;

#endif
