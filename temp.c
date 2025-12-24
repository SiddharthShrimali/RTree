#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 10 //max no of entries in a node
#define m 4  //min no of entries in a node

typedef struct boundingBox { //to define box in 2d (xmin, ymin) to (xmax, ymax) [diagonally opposite sides-can calculate area]
	float xmin, xmax;
	float ymin, ymax;
} box;

typedef struct point {
	float x, y;
} Point;

typedef struct leafTuple { //leaf tuple(calls box and stores the actual object pointer)
	box I;
	Point p;
} RTreeLeafEntry;

typedef struct RTreeNode node; //for declaration

typedef struct internalTuple { //internal tuple(calls box and stores the child pointer)
	box I;
	node *child; 
} RTreeInternalEntry;

typedef struct RTreeNode {
	int isLeaf; //1 for leaf, 0 for nonLeaf
	int count; //to count no of entries/children
	RTreeLeafEntry leaf[M]; //array of type leaf that stores entries of leaf
	RTreeInternalEntry internal[M]; //array of type nonLeaf that stores entries of nonLeaf
} node;

typedef struct RTree {
	node *root; //pointer to the root of the rTree which is of the type node
} rt;

int main() {
	
	
	return 0;
} 
		
	
	
	
	
		
	
		
	
	
	
	
	
	
		
	
		
	
	
	
	
	
	
	
