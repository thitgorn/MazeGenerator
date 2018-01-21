void initializing_set(int *array, int numElements) {
	int i;
    for (i = 0; i < numElements; i++) {
      array[i] = -1;
    }
}

void q_union(int *array, int root1, int root2) {
    if (array[root2] < array[root1]) {                 // root2 has larger tree
		array[root2] += array[root1];        // update # of items in root2's tree
		array[root1] = root2;                              // make root2 new root
    } else {                                  // root1 has equal or larger tree
		array[root1] += array[root2];        // update # of items in root1's tree
		array[root2] = root1;                              // make root1 new root
    }
}

int find(int *array, int x) {
    if (array[x] < 0) {
		return x;                         // x is the root of the tree; return it
    } else {
		// Find out who the root is; compress path by making the root x's parent.
		array[x] = find(array, array[x]);
		return array[x];                                       // Return the root
    }
}
