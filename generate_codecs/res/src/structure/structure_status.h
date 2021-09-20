#ifndef STRUCTURE_STATUS_H
#define STRUCTURE_STATUS_H


extern const int STRUCTURE_STATUS_SIZE;

typedef enum {
	ADDED,
	USED
} StructureStatus;

extern char *STRUCTURE_STATUS_STRING[];

#endif
