#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures/pets.h"

Cat * Cat_create(int age, char *name, double cute) {
	Cat *cat = (Cat *)malloc(sizeof(Cat));
	cat->age = age;
	cat->name = (char *)calloc(strlen(name)+1, sizeof(char));
	strcpy(cat->name, name);
	cat->cute = cute;
	cat->next = NULL;
	return cat;
}

void Cat_free(Cat *cat) {
	if (cat != NULL) {
		cat->age = 0;
		if (cat->name != NULL) {
			free(cat->name);
			cat->name = NULL;
		}
		cat->cute = 0.0;
		cat->next = NULL;
		free(cat);
		cat = NULL;
	}
}

char * Cat_string(Cat *cat) {
	size_t string_length;
	char *string;
	FILE *string_stream = open_memstream(&string, &string_length);
	fprintf(string_stream, "Cat:\nage - \'%d\'\nname - \'%s\'\ncute - \'%.1f\'\n", cat->age, cat->name, cat->cute);
	fclose(string_stream);
	return string;
}


Dog * Dog_create(int age, char *name, char *color) {
	Dog *dog = (Dog *)malloc(sizeof(Dog));
	dog->age = age;
	dog->name = (char *)calloc(strlen(name)+1, sizeof(char));
	strcpy(dog->name, name);
	dog->color = (char *)calloc(strlen(color)+1, sizeof(char));
	strcpy(dog->color, color);
	dog->next = NULL;
	return dog;
}

void Dog_free(Dog *dog) {
	if (dog != NULL) {
		dog->age = 0;
		if (dog->name != NULL) {
			free(dog->name);
			dog->name = NULL;
		}
		if (dog->color!=NULL) {
			free(dog->color);
			dog->color = NULL;
		}
		dog->next = NULL;
		free(dog);
		dog = NULL;
	}
}

char * Dog_string(Dog *dog) {
	size_t string_length;
	char *string;
	FILE *string_stream = open_memstream(&string, &string_length);
	fprintf(string_stream, "Dog:\nage - \'%d\'\nname - \'%s\'\ncolor - \'%s\'\n", dog->age, dog->name, dog->color);
	fclose(string_stream);
	return string;
}


Pets * Pets_create() {
	Pets *pets = (Pets *)malloc(sizeof(Pets));
	pets->size.total = pets->size.cats = pets->size.dogs = 0;
	pets->head_cats = NULL;
	pets->head_dogs = NULL;
	return pets;
}

void Pets_free(Pets *pets) {
	if (pets != NULL) {
		pets->size.total = 0;
		pets->size.cats = 0;
		pets->size.dogs = 0;
		Cat *cat_curr=pets->head_cats;
		while (cat_curr != NULL) {
			Cat *prev = cat_curr;
			cat_curr = cat_curr->next;
			Cat_free(prev);
		}
		cat_curr = NULL;
		Dog *dog_curr=pets->head_dogs;
		while (dog_curr != NULL) {
			Dog *prev = dog_curr;
			dog_curr = dog_curr->next;
			Dog_free(prev);
		}
		dog_curr = NULL;
		pets->head_cats = NULL;
		pets->head_dogs = NULL;
		free(pets);
		pets = NULL;
	}
}

char * Pets_string(Pets *pets) {
	size_t string_length;
	char *string;
	FILE *string_stream = open_memstream(&string, &string_length);
	fprintf(string_stream, "Pets [Total - \'%d\' / Cats - \'%d\' / Dog - \'%d\']\n", pets->size.total, pets->size.cats, pets->size.dogs);
	for (Cat *curr=pets->head_cats; curr!=NULL; curr=curr->next) {
		char *cat_string = Cat_string(curr);
		fprintf(string_stream, "|_%s", cat_string);
		free(cat_string);
	}
	for (Dog *curr=pets->head_dogs; curr!=NULL; curr=curr->next) {
		char *dog_string = Dog_string(curr);
		fprintf(string_stream, "|_%s", dog_string);
		free(dog_string);
	}
	fclose(string_stream);
	return string;
}

void Pets_add_Cat(Pets *pets, Cat *cat) {
	pets->size.total = pets->size.total + 1;
	pets->size.cats = pets->size.cats + 1;
	if (pets->head_cats == NULL) {
		pets->head_cats = cat;
	} else {
		Cat *last = pets->head_cats;
		while (last->next != NULL) {
			last = last->next;
		}
		last->next = cat;
	}
}

void Pets_add_Dog(Pets *pets, Dog *dog) {
	pets->size.total = pets->size.total + 1;
	pets->size.dogs = pets->size.dogs + 1;
	if (pets->head_dogs == NULL) {
		pets->head_dogs = dog;
	} else {
		Dog *last = pets->head_dogs;
		while (last->next != NULL) {
			last = last->next;
		}
		last->next = dog;
	}
}

