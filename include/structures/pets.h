#ifndef PETS_H
#define PETS_H


typedef struct Cat {
	int age;
	char *name;
	double cute;
	struct Cat *next;
} Cat;

Cat * Cat_create(int age, char *name, double cute);
void Cat_free(Cat *cat);
char * Cat_string(Cat *cat);


typedef struct Dog {
	int age;
	char *name;
	char *color;
	struct Dog *next;
} Dog;

Dog * Dog_create(int age, char *name, char *color);
void Dog_free(Dog *dog);
char * Dog_string(Dog *dog);

typedef struct PetsSizes {
	int total;
	int cats;
	int dogs;
} PetsSizes;


typedef struct Pets {
	PetsSizes size;
	Cat *head_cats;
	Dog *head_dogs;
} Pets;

Pets * Pets_create();
void Pets_free(Pets *pets);
char * Pets_string(Pets *pets);

void Pets_add_Cat(Pets *pets, Cat *cat);
void Pets_add_Dog(Pets *pets, Dog *dog);

#endif
