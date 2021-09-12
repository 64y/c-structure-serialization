#ifndef MATRICES_H
#define MATRICES_H

#include <stdio.h>
#include <string.h>

#include "utils/basic_defines.h"
#include "serialization/registrate.h"
#include "serialization/serialize.h"


#include "structures/matrix3d.h"

void example_of_structure_with_matrix() {
	puts(" = = = Example of Structure with Matrix = = = ");
	
	Serialize_registrate_structure("Matrix3D", "structures/matrix3d.h");
	Serialize *matrix3D_serialize = Serialize_create("Matrix3D");
	
	Matrix3D *matrix3D;
	{
		matrix3D = (Matrix3D *)malloc(sizeof(Matrix3D));
		matrix3D->matrix_o = 2;
		matrix3D->matrix_n = 3;
		matrix3D->matrix_m = 4;
		matrix3D->matrix = (int ***)calloc(matrix3D->matrix_o, sizeof(int **));
		for (int o=0, num=0; o<matrix3D->matrix_o; o++) {
			matrix3D->matrix[o] = (int **)calloc(matrix3D->matrix_n, sizeof(int *));
			for (int n=0; n<matrix3D->matrix_n; n++) {
				matrix3D->matrix[o][n] = (int *)calloc(matrix3D->matrix_m, sizeof(int));
				for (int m=0; m<matrix3D->matrix_m; m++, num++) {
					matrix3D->matrix[o][n][m] = ((o==0) ? -1 : +1) * num;
				}
			}
		}
	}
	
	puts("TO_STRING:");
	char *matrix3D_string;
	matrix3D_string = matrix3D_serialize->to_string(matrix3D);
	puts(matrix3D_string);
	
	{
		Serialize_free(matrix3D_serialize);
		
		for (int o=0; o<matrix3D->matrix_o; o++) {
			for (int n=0; n<matrix3D->matrix_n; n++) {
				free(matrix3D->matrix[o][n]);
			}
			free(matrix3D->matrix[o]);
		}
		matrix3D->matrix_o = 0;
		matrix3D->matrix_n = 0;
		matrix3D->matrix_m = 0;
		free(matrix3D->matrix);
		free(matrix3D);
		
		free(matrix3D_string);
	}
	puts(" = = = = = = = = = = = = = = = = = = = = = = =\n");
}


#include "structures/arrays.h"

void example_of_structure_with_matrices() {
	puts(" = = = Example of Structure with Matrices = = = "); // 13 bytes in 5 blocks in Serialize_registrate_structure
	
	Serialize_registrate_structure("Arrays", "structures/arrays.h");
	Serialize *arrays_serialize = Serialize_create("Arrays");
	
	Arrays *arrays;
	{
		int num = 0;
		arrays = (Arrays *)malloc(sizeof(Arrays));
		arrays->arr_a = 5;
		arrays->arr_b = 5;
		arrays->arr = (int **)calloc(arrays->arr_a, sizeof (int *));
		for (int ia=0; ia<arrays->arr_a; ia++) {
			arrays->arr[ia] = (int *)calloc(arrays->arr_b, sizeof(int));
			for (int ib=0; ib<arrays->arr_b; ib++, num++) {
				arrays->arr[ia][ib] = num;
			}
		}
		for (int i=0; i<2; i++) {
			for (int j=0; j<3; j++) {
				for (int k=0; k<4; k++) {
					for (int l=0; l<5; l++, num++) {
						arrays->brr[i][j][k][l] = num;
					}
				}
			}
		}
		arrays->crr_0 = 3;
		arrays->crr_1 = 3;
		arrays->crr_2 = 3;
		for (int i=0; i<arrays->crr_0; i++) {
			for (int j=0; j<arrays->crr_1; j++) {
				for (int k=0; k<arrays->crr_2; k++, num++) {
					arrays->crr[i][j][k] = num % 25;
				}
			}
		}
		arrays->drr_2 = 4;
		arrays->drr_3 = 4;
		arrays->drr_4 = 4;
		for (int i=0; i<2; i++) {
			for (int j=0; j<3; j++) {
				arrays->drr[i][j] = (int ***)calloc(arrays->drr_2, sizeof(int **));
				for (int k=0; k<arrays->drr_2; k++) {
					arrays->drr[i][j][k] = (int **)calloc(arrays->drr_3, sizeof(int *));
					for (int l=0; l<arrays->drr_3; l++) {
						arrays->drr[i][j][k][l] = (int *)calloc(arrays->drr_4, sizeof(int));
						for (int m=0; m<arrays->drr_4; m++, num++) {
							arrays->drr[i][j][k][l][m] = num % 25;
						}
					}
				}
			}
		}
		arrays->err_0 = 2;
		arrays->err_1 = 2;
		arrays->err_2 = 2;
		arrays->err_3 = 2;
		for (int i=0; i<arrays->err_0; i++) {
			for (int j=0; j<arrays->err_1; j++) {
				arrays->err[i][j] = (int **)calloc(arrays->err_2, sizeof(int *));
				for (int k=0; k<arrays->err_2; k++) {
					arrays->err[i][j][k] = (int *)calloc(arrays->err_3, sizeof(int));
					for (int l=0; l<arrays->err_3; l++, num++) {
						arrays->err[i][j][k][l] = num % 15;
					}
				}
			}
		}
	}
	
	puts("TO_STRING:");
	char *arrays_string = arrays_serialize->to_string(arrays);
	puts(arrays_string);
	
	{
		Serialize_free(arrays_serialize);
		
		for (int ia=0; ia<arrays->arr_a; ia++) {
			free(arrays->arr[ia]);
		}
		arrays->arr_a = 0;
		arrays->arr_b = 0;
		free(arrays->arr);
		arrays->crr_0 = 0;
		arrays->crr_1 = 0;
		arrays->crr_2 = 0;
		for (int i=0; i<2; i++) {
			for (int j=0; j<3; j++) {
				for (int k=0; k<arrays->drr_2; k++) {
					for (int l=0; l<arrays->drr_3; l++) {
						free(arrays->drr[i][j][k][l]);
					}
					free(arrays->drr[i][j][k]);
				}
				free(arrays->drr[i][j]);
			}
		}
		arrays->drr_2 = 0;
		arrays->drr_3 = 0;
		arrays->drr_4 = 0;
		for (int i=0; i<arrays->err_0; i++) {
			for (int j=0; j<arrays->err_1; j++) {
				for (int k=0; k<arrays->err_2; k++) {
					free(arrays->err[i][j][k]);
				}
				free(arrays->err[i][j]);
			}
		}
		arrays->err_0 = 0;
		arrays->err_1 = 0;
		arrays->err_2 = 0;
		arrays->err_3 = 0;
		free(arrays);
		
		free(arrays_string);

	}
	puts(" = = = = = = = = = = = = = = = = = = = = = = = =\n");
}


#include "structures/strings.h"

void example_of_structure_with_matrices_of_strings() {
	puts(" = = = Example of Structure with Matrices of Strings = = = "); // 16 bytes in 5 blocks in Serialize_registrate_structure
	
	Serialize_registrate_structure("Strings", "structures/strings.h");
	Serialize *strings_serialize = Serialize_create("Strings");
	
	
	Strings *strings;
	{
		strings = (Strings *)malloc(sizeof(Strings));
		strings->stra_0 = 5;
		strings->stra_1 = 5;
		strings->stra = (char ***)calloc(strings->stra_0, sizeof (char **));
		for (int ia=0; ia<strings->stra_0; ia++) {
			strings->stra[ia] = (char **)calloc(strings->stra_1, sizeof(char *));
			for (int ib=0; ib<strings->stra_1; ib++) {
				strings->stra[ia][ib] = string_random(5, 10);
			}
		}
		for (int i=0; i<4; i++) {
			for (int j=0; j<4; j++) {
				char *string = string_random(5, 10);
				strcpy(strings->strb[i][j], string);
				free(string);
			}
		}
		strings->strc_0 = 3;
		strings->strc_1 = 3;
		for (int i=0; i<strings->strc_0; i++) {
			for (int j=0; j<strings->strc_1; j++) {
				char *string = string_random(5, 10);
				strcpy(strings->strc[i][j], string);
				free(string);
			}
		}
		strings->strd_2 = 4;
		strings->strd_3 = 4;
		for (int i=0; i<6; i++) {
			for (int j=0; j<6; j++) {
				strings->strd[i][j] = (char ***)calloc(strings->strd_2, sizeof(char **));
				for (int k=0; k<strings->strd_2; k++) {
					strings->strd[i][j][k] = (char **)calloc(strings->strd_3, sizeof(char *));
					for (int l=0; l<strings->strd_3; l++) {
						strings->strd[i][j][k][l] = string_random(5, 10);
					}
				}
			}
		}
		strings->stre_0 = 2;
		strings->stre_1 = 2;
		strings->stre_2 = 2;
		strings->stre_3 = 2;
		for (int i=0; i<strings->stre_0; i++) {
			for (int j=0; j<strings->stre_1; j++) {
				strings->stre[i][j] = (char ***)calloc(strings->stre_2, sizeof(char **));
				for (int k=0; k<strings->stre_2; k++) {
					strings->stre[i][j][k] = (char **)calloc(strings->stre_3, sizeof(char *));
					for (int l=0; l<strings->stre_3; l++) {
						strings->stre[i][j][k][l] = string_random(5, 10);
					}
				}
			}
		}
	}
	
	puts("TO_STRING:");
	char *strings_string = strings_serialize->to_string(strings);
	puts(strings_string);
	{
		Serialize_free(strings_serialize);
		
		for (int ia=0; ia<strings->stra_0; ia++) {
			for (int ib=0; ib<strings->stra_1; ib++) {
				free(strings->stra[ia][ib]);
			}
			free(strings->stra[ia]);
		}
		strings->stra_0 = 0;
		strings->stra_1 = 5;
		free(strings->stra);
		strings->strc_0 = 0;
		strings->strc_1 = 0;
		for (int i=0; i<6; i++) {
			for (int j=0; j<6; j++) {
				for (int k=0; k<strings->strd_2; k++) {
					for (int l=0; l<strings->strd_3; l++) {
						free(strings->strd[i][j][k][l]);
					}
					free(strings->strd[i][j][k]);
				}
				free(strings->strd[i][j]);
			}
		}
		strings->strd_2 = 0;
		strings->strd_3 = 0;
		for (int i=0; i<strings->stre_0; i++) {
			for (int j=0; j<strings->stre_1; j++) {
				for (int k=0; k<strings->stre_2; k++) {
					for (int l=0; l<strings->stre_3; l++) {
						free(strings->stre[i][j][k][l]);
					}
					free(strings->stre[i][j][k]);
				}
				free(strings->stre[i][j]);
			}
		}
		strings->stre_0 = 0;
		strings->stre_1 = 0;
		strings->stre_2 = 0;
		strings->stre_3 = 0;
		free(strings);
		
		free(strings_string);
	}
	puts(" = = = = = = = = = = = = = = = = = = = = = = = = = = = = = \n");
}

#endif
