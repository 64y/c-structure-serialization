#ifndef $3_MATRICES_H
#define $3_MATRICES_H


#include "structures/matrix3d.h"
#include "structures/arrays.h"
#include "structures/strings.h"

#include "examples/example_template.h"

void * Matrix3D_generate(void);
void Matrix3D_free(void *structure);

void * Arrays_generate(void);
void Arrays_free(void *structure);

char * string_random(size_t string_length_min, size_t string_length_max);
void * Strings_generate(void);
void Strings_free(void *structure);


void example_of_structure_with_matrix() {
	example(
		"Structure with Matrix",
		"./my_lib",
		"Matrix3D",
		Matrix3D_generate,
		Matrix3D_free,
		DO_TO_STRING | DO_JSON_ENCODE | DO_JSON_DECODE
	);
}

void example_of_structure_with_matrices() {
	example(
		"Structure with Matrices",
		"./my_lib",
		"Arrays",
		Arrays_generate,
		Arrays_free,
		DO_TO_STRING // | DO_JSON_ENCODE | DO_JSON_DECODE
	);
}

void example_of_structure_with_matrices_of_strings() {
	example(
		"Example of Structure with Matrices of Strings",
		"./my_lib",
		"Strings",
		Strings_generate,
		Strings_free,
		DO_TO_STRING // | DO_JSON_ENCODE | DO_JSON_DECODE
	);
}


void * Matrix3D_generate(void) {
	Matrix3D *matrix3D = (Matrix3D *)malloc(sizeof(Matrix3D));
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
	return matrix3D;
}

void Matrix3D_free(void *structure) {
	Matrix3D *matrix3D = (Matrix3D *)structure;
	if (matrix3D != NULL) {
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
		matrix3D = NULL;
	}
}

void * Arrays_generate(void) {
	int num = 0;
	Arrays *arrays = (Arrays *)malloc(sizeof(Arrays));
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
	return arrays;
}

void Arrays_free(void *structure) {
	Arrays *arrays = (Arrays *)structure;
	if (arrays != NULL) {
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
		arrays = NULL;
	}
}

char * string_random(size_t string_length_min, size_t string_length_max) {
	size_t string_printable_length = 62;
	char *string_printable = "123456789qwertyuiopasdfgghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
	size_t string_length = string_length_min + random()%(string_length_max+1-string_length_min);
	char *string = (char *)calloc(string_length+1, sizeof(char));
	for (int i=0; i<string_length; i++) {
		string[i] = string_printable[random() % string_printable_length];
	}
	return string;
}

void * Strings_generate(void) {
	Strings *strings = (Strings *)malloc(sizeof(Strings));
	strings->stra_0 = 5;
	strings->stra_1 = 5;
	strings->stra = (char ***)calloc(strings->stra_0, sizeof (char **));
	for (int ia=0; ia<strings->stra_0; ia++) {
		strings->stra[ia] = (char **)calloc(strings->stra_1, sizeof(char *));
		for (int ib=0; ib<strings->stra_1; ib++) {
			strings->stra[ia][ib] = string_random(5, 10);
		}
	}
	for (int i=0; i<5; i++) {
		for (int j=0; j<5; j++) {
			for (int k=0; k<32; k++) {
				char *string = string_random(5, 10);
				strings->strb[i][j][k] = string[0];
				free(string);
			}
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
	return strings;
}
	
void Strings_free(void *structure) {
	Strings *strings = (Strings *)structure;
	if (strings != NULL) {
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
		strings = NULL;
	}
}

#endif
