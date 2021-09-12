#include "includes.h"


/*
void test_00() {
	puts(" = = = Test 0 (Primitives) = = = ");
	
	AllPrimitives ap = {'D', 0xFF, 0x00, 1, 2, 3l, 4.0f, 5.5};
	char *ap_str = AllPrimitives_to_string(&ap);
	puts(ap_str);
	free(ap_str);
}
//*/

/*
void test_01() {
	puts(" = = = Test 1 (Primitive structure)  = = = ");
	
	Parrot p = {"Tom", 5};
	char *p_str = Parrot_to_string(&p);
	puts(p_str);
	free(p_str);
}
//*/

/*
void test_02() {
	puts(" = = = Test 2 (Array) = = = ");
	
	int a_size = 5;
	Array a = {
		a_size,
		(int *)calloc(a_size, sizeof(int))
	};
	for (int i=0; i<a.arr_n; i++) {
		a.arr[i] = i * 2;
	}
	char *a_str = Array_to_string(&a);
	puts(a_str);
	free(a_str);
}
//*/

/*
void test_03() {
	puts(" = = = Test 3 (Matrix3D) = = = ");
	
	Matrix3D *m3d = (Matrix3D *)malloc(sizeof(Matrix3D));
	m3d->matrix_o = 2;
	m3d->matrix_n = 3;
	m3d->matrix_m = 4;
	m3d->matrix = (int ***)calloc(m3d->matrix_o, sizeof(int **));
	for (int o=0, num=0; o<m3d->matrix_o; o++) {
		m3d->matrix[o] = (int **)calloc(m3d->matrix_n, sizeof(int *));
		for (int n=0; n<m3d->matrix_n; n++) {
			m3d->matrix[o][n] = (int *)calloc(m3d->matrix_m, sizeof(int));
			for (int m=0; m<m3d->matrix_m; m++, num++) {
				m3d->matrix[o][n][m] = ((o==0) ? -1 : +1) * num;
			}
		}
	}
	char *m3d_str = Matrix3D_to_string(m3d);
	puts(m3d_str);
	free(m3d);
}
//*/

/*
void test_04() {
	puts(" = = = Test 4 (Arrays) = = = ");
	
	Arrays *a = (Arrays *)malloc(sizeof(Arrays));
	int num = 0;
	a->arr_a = 5;
	a->arr_b = 5;
	a->arr = (int **)calloc(a->arr_a, sizeof (int *));
	for (int ia=0; ia<a->arr_a; ia++) {
		a->arr[ia] = (int *)calloc(a->arr_b, sizeof(int));
		for (int ib=0; ib<a->arr_b; ib++, num++) {
			a->arr[ia][ib] = num;
		}
	}
	for (int i=0; i<2; i++) {
		for (int j=0; j<3; j++) {
			for (int k=0; k<4; k++) {
				for (int l=0; l<5; l++, num++) {
					a->brr[i][j][k][l] = num;
				}
			}
		}
	}
	a->crr_0 = 3;
	a->crr_1 = 3;
	a->crr_2 = 3;
	for (int i=0; i<a->crr_0; i++) {
		for (int j=0; j<a->crr_1; j++) {
			for (int k=0; k<a->crr_2; k++, num++) {
				a->crr[i][j][k] = num % 25;
			}
		}
	}
	a->drr_2 = 4;
	a->drr_3 = 4;
	a->drr_4 = 4;
	for (int i=0; i<2; i++) {
		for (int j=0; j<3; j++) {
			a->drr[i][j] = (int ***)calloc(a->drr_2, sizeof(int **));
			for (int k=0; k<a->drr_2; k++) {
				a->drr[i][j][k] = (int **)calloc(a->drr_3, sizeof(int *));
				for (int l=0; l<a->drr_3; l++) {
					a->drr[i][j][k][l] = (int *)calloc(a->drr_4, sizeof(int));
					for (int m=0; m<a->drr_4; m++, num++) {
						a->drr[i][j][k][l][m] = num % 25;
					}
				}
			}
		}
	}
	a->err_0 = 2;
	a->err_1 = 2;
	a->err_2 = 2;
	a->err_3 = 2;
	for (int i=0; i<a->err_0; i++) {
		for (int j=0; j<a->err_1; j++) {
			a->err[i][j] = (int **)calloc(a->err_2, sizeof(int *));
			for (int k=0; k<a->err_2; k++) {
				a->err[i][j][k] = (int *)calloc(a->err_3, sizeof(int));
				for (int l=0; l<a->err_3; l++, num++) {
					a->err[i][j][k][l] = num % 15;
				}
			}
		}
	}
	char *a_str = Arrays_to_string(a);
	puts(a_str);
	free(a_str);
}
//*/

/*
char * string_random(size_t string_length_min, size_t string_length_max) {
	size_t string_printable_length = 96;
	char *string_printable = "0123456789qwertyuiopasdfgghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM`~!@#$%^&*()-_=+[{]}\\|;:\'\",<.>/?";
	size_t string_length = string_length_min + random()%(string_length_max+1-string_length_min);
	char *string = (char *)calloc(string_length+1, sizeof(char));
	for (int i=0; i<string_length; i++) {
		string[i] = string_printable[random() % string_printable_length];
	}
	return string;
}

void test_05() {
	puts(" = = = Test 5 (Arrays of Strings) = = = ");
	
	Strings *s = (Strings *)malloc(sizeof(Strings));
	s->stra_0 = 5;
	s->stra_1 = 5;
	s->stra = (char ***)calloc(s->stra_0, sizeof (char **));
	for (int ia=0; ia<s->stra_0; ia++) {
		s->stra[ia] = (char **)calloc(s->stra_1, sizeof(char *));
		for (int ib=0; ib<s->stra_1; ib++) {
			s->stra[ia][ib] = string_random(5, 10);
		}
	}
	for (int i=0; i<4; i++) {
		for (int j=0; j<4; j++) {
			strcpy(s->strb[i][j], string_random(5, 10));
		}
	}
	s->strc_0 = 3;
	s->strc_1 = 3;
	for (int i=0; i<s->strc_0; i++) {
		for (int j=0; j<s->strc_1; j++) {
			strcpy(s->strc[i][j], string_random(5, 10));
		}
	}
	s->strd_2 = 4;
	s->strd_3 = 4;
	for (int i=0; i<6; i++) {
		for (int j=0; j<6; j++) {
			s->strd[i][j] = (char ***)calloc(s->strd_2, sizeof(char **));
			for (int k=0; k<s->strd_2; k++) {
				s->strd[i][j][k] = (char **)calloc(s->strd_3, sizeof(char *));
				for (int l=0; l<s->strd_3; l++) {
					s->strd[i][j][k][l] = string_random(5, 10);
				}
			}
		}
	}
	s->stre_0 = 2;
	s->stre_1 = 2;
	s->stre_2 = 2;
	s->stre_3 = 2;
	for (int i=0; i<s->stre_0; i++) {
		for (int j=0; j<s->stre_1; j++) {
			s->stre[i][j] = (char ***)calloc(s->stre_2, sizeof(char **));
			for (int k=0; k<s->stre_2; k++) {
				s->stre[i][j][k] = (char **)calloc(s->stre_3, sizeof(char *));
				for (int l=0; l<s->stre_3; l++) {
					s->stre[i][j][k][l] = string_random(5, 10);
				}
			}
		}
	}
	
	char *s_str = Strings_to_string(s);
	puts(s_str);
	free(s_str);
}
//*/

/*
void test_06() {
	puts(" = = = Test 6 (Structures) = = = ");
	
	Cat *c0 = Cat_create(10, "Sam", 0.5);
	Cat *c1 = Cat_create(11, "Tom", 0.6);
	Cat *c2 = Cat_create(9, "Vid", 0.9);
	Cat *c3 = Cat_create(7, "Zip", 0.8);
	Cat *c4 = Cat_create(15, "Zap", 0.2);
	Dog *d0 = Dog_create(5, "Rain", "red");
	Dog *d1 = Dog_create(7, "Blizzard", "white");
	Dog *d2 = Dog_create(3, "Thunder", "blue");
	Pets *pets = Pets_create();
	Pets_add_Cat(pets, c0);
	Pets_add_Cat(pets, c1);
	Pets_add_Cat(pets, c2);
	Pets_add_Cat(pets, c3);
	Pets_add_Cat(pets, c4);
	Pets_add_Dog(pets, d0);
	Pets_add_Dog(pets, d1);
	Pets_add_Dog(pets, d2);
	
	char *pets_string = Pets_string(pets);
	puts(pets_string);
	free(pets_string);
	
	pets_string = Pets_to_string(pets);
	puts(pets_string);
	free(pets_string);
		
	Pets_free(pets);
}
//*/


int main(int argc, char *argv[]) {
	/*test_00();
	test_01();
	test_02();
	test_03();
	test_04();
	test_05();
	test_06();*/
	return 0;
}
