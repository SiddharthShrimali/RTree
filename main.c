#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define MAX_ENTRIES 4      // maximum entries in a node
#define MIN_ENTRIES 2      // minimum entries in a node

typedef struct Data {
    float x, y;
} Point;

typedef struct RTreeNode {
    int isLeaf;                // 1=leaf, 0=internal
    int size;            // number of entries
    float xmin, xmax;
    float ymin, ymax;
    struct RTreeNode *children[MAX_ENTRIES];  // child node pointers
    Point *points[MAX_ENTRIES];               // leaf data points
} node;

typedef struct RTree {
    node *root;
} rTree;

void swapPoints(Point* a, Point* b) {
    Point temp = *a;
    *a = *b;
    *b = temp;
}

int partitionX(Point points[], int first, int last) {
    float pivot = points[last].x;
    int i = first-1;
    for (int j = first; j < last; j++) {
        if (points[j].x <= pivot) {
            i++;
            swapPoints(&points[i], &points[j]);
        }
    }
    swapPoints(&points[i+1], &points[last]);
    return i+1;
}

void quickSortX(Point points[], int first, int last) {
    if (first < last) {
        int pivot = partitionX(points, first, last);
        quickSortX(points, first, pivot-1);
        quickSortX(points, pivot+1, last);
    }
}

int partitionY(Point points[], int first, int last) {
    float pivot = points[last].y;
    int i = first-1;
    for (int j = first; j < last; j++) {
        if (points[j].y <= pivot) {
            i++;
            swapPoints(&points[i], &points[j]);
        }
    }
    swapPoints(&points[i+1], &points[last]);
    return i+1;
}

void quickSortY(Point points[], int first, int last) {
    if (first < last) {
        int pivot = partitionY(points, first, last);
        quickSortY(points, first, pivot-1);
        quickSortY(points, pivot+1, last);
    }
}

int main() {
    Point *points;
    int pointCount, leafPages, slices, sliceSize;

    pointCount=11;
    points=(Point*)calloc(pointCount, sizeof(Point)); //input array for points

    for(int i=0; i<pointCount; i++) {
        points[i].x=i*1.2;
        points[i].y=i*1.5;
    }
    quickSortX(points, 0, pointCount-1);  //sorting the points in x-axis

    leafPages=(int)ceil((double)pointCount/MAX_ENTRIES); //making leaf level pages(no of leaves) (P)
    slices=(int)ceil(sqrt(leafPages)); //making slices (S)
    sliceSize=MAX_ENTRIES*slices; //each slice contains how many points (S*n=points per slice)

    for(int i=0; i<slices; i++) {
        int start=i*sliceSize; //incrementing start to a multiple of sliceSize
        int end=start+sliceSize-1; //incrementing end to sliceSize-1 for 0 based indexing
        if(start>=pointCount) break; //to handle overflow
        if(end>=pointCount) end=pointCount-1;
        quickSortY(points, start, end); //sorting the points in y-axis
    }

    int leafCount=0;
    node **leafNodeAddresses=calloc(leafPages, sizeof(node*)); //to reduce stack storage
    for(int i=0; i<pointCount; i+=MAX_ENTRIES) {
        node *leaf=(node*)malloc(1*sizeof(node));
        leafNodeAddresses[leafCount++]=leaf;
        leaf->isLeaf=1;
        leaf->size=0;
        leaf->xmax=leaf->ymax=__FLT_MIN__;
        leaf->xmin=leaf->ymin=__FLT_MAX__;
        for(int j=0; j<MAX_ENTRIES && (i+j)<pointCount; j++) {
            Point *p=&points[i+j];
            leaf->points[j]=p;
            leaf->size++;
            if(p->x<leaf->xmin) leaf->xmin=p->x;
            if(p->x>leaf->xmax) leaf->xmax=p->x;
            if(p->y<leaf->ymin) leaf->ymin=p->y;
            if(p->y>leaf->ymax) leaf->ymax=p->y;
        }
    }
    free(points);
    for(int i=0; i<leafCount; i++) free(leafNodeAddresses[i]);
    free(leafNodeAddresses);
    return 0;
}