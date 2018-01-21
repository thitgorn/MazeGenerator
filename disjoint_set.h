#ifndef DISJOINT_SET_H /* include guard */
#define DISJOINT_SET_H

void initializing_set(int *array, int numElements);

void q_union(int *array, int root1, int root2);

int find(int *array, int x);

#endif
