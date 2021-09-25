#ifndef $5_MATRICES_OF_STRUCTURES_H
#define $5_MATRICES_OF_STRUCTURES_H

#include <stdio.h>
#include <stdlib.h>

#include <c_structure_serialization/serializer.h>


#include "structures/figures.h"

void example_of_structure_with_matrices_of_structures() {
	puts(" = = = Example of Structure with Matrices of Structures = = = ");
		
	Serializer *figures_serializer = Serializer_create("./my_lib", "Figures");
	
	Figures *figures;
	{
		figures = (Figures *)malloc(sizeof(Figures));
		figures->circles_0 = 3;
		figures->circles_1 = 4;
		figures->circles = (Circle ***)calloc(figures->circles_0, sizeof(Circle **));
		for (int i=0; i<figures->circles_0; i++) {
			figures->circles[i] = (Circle **)calloc(figures->circles_1, sizeof(Circle *));
			for (int j=0; j<figures->circles_1; j++) {
				figures->circles[i][j] = (Circle *)malloc(sizeof(Circle));
				Point c = {random()%50-25, random()%50-25};
				figures->circles[i][j]->c = c;
				figures->circles[i][j]->r = random()%5;
			}
		}
		for (int i=0; i<5; i++) {
			for (int j=0; j<5; j++) {
				Point a = {random()%50-25, random()%50-25};
				Point b = {random()%50-25, random()%50-25};
				Point c = {random()%50-25, random()%50-25};
				Triangle t = {a, b, c};
				figures->triangles[i][j] = t;
			}
		}
		figures->rectangles_a = 2;
		figures->rectangles_b = 1;
		figures->rectangles_c = 2;
		figures->rectangles_d = 3;
		figures->rectangles_e = 3;
		for (int i=0; i<figures->rectangles_a; i++) {
			for (int j=0; j<figures->rectangles_b; j++) {
				for (int k=0; k<figures->rectangles_c; k++) {
					figures->rectangles[i][j][k] = (Rectangle ***)calloc(figures->rectangles_d, sizeof(Rectangle **));
					for (int l=0; l<figures->rectangles_d; l++) {
						figures->rectangles[i][j][k][l] = (Rectangle **)calloc(figures->rectangles_e, sizeof(Rectangle *));
						for (int m=0; m<figures->rectangles_e; m++) {
							Point a = {random()%50-25, random()%50-25};
							Point b = {random()%50-25, random()%50-25};
							figures->rectangles[i][j][k][l][m] = (Rectangle *)malloc(sizeof(Rectangle));
							figures->rectangles[i][j][k][l][m]->a = a;
							figures->rectangles[i][j][k][l][m]->a = b;
						}
					}
				}
			}
		}
		free(figures->rectangles[0][0][0][1][1]);
		figures->rectangles[0][0][0][1][1] = NULL;
	}
	
	puts("TO_STRING:");
	char *figures_string = figures_serializer->to_string(figures);
	puts(figures_string);
	
	{
		Serializer_free(figures_serializer);
		
		for (int i=0; i<figures->circles_0; i++) {
			for (int j=0; j<figures->circles_1; j++) {
				free(figures->circles[i][j]);
			}
			free(figures->circles[i]);
		}
		figures->circles_0 = 0;
		figures->circles_1 = 0;
		free(figures->circles);
		for (int i=0; i<figures->rectangles_a; i++) {
			for (int j=0; j<figures->rectangles_b; j++) {
				for (int k=0; k<figures->rectangles_c; k++) {
					for (int l=0; l<figures->rectangles_d; l++) {
						for (int m=0; m<figures->rectangles_e; m++) {
							if (figures->rectangles[i][j][k][l][m] != NULL) {
								free(figures->rectangles[i][j][k][l][m]);
							}
						}
						free(figures->rectangles[i][j][k][l]);
					}
					free(figures->rectangles[i][j][k]);
				}
			}
		}
		figures->rectangles_a = 0;
		figures->rectangles_b = 0;
		figures->rectangles_c = 0;
		figures->rectangles_d = 0;
		figures->rectangles_e = 0;
		free(figures);
		
		free(figures_string);
	}
	
	puts(" = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
}

#endif
