#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "disjoint_set.h"

#define MAX 100

void print_maze(int num_rows, int num_cols, int *v_wall, int *h_wall) {
	int i, j;

	printf("*");
	for (j=0; j<num_cols; j++)
		printf("**");
	printf("\n");

	for (i=0; i<num_rows; i++) {
		printf("*");
		for (j=0; j<num_cols; j++)
			if (v_wall[i*num_cols + j] == 0)
				printf(" *");
			else
				printf("  ");
		printf("\n");
		printf("*");
		for (j=0; j<num_cols; j++)
			if (h_wall[i*num_cols + j] == 0)
				printf("**");
			else
				printf(" *");
		printf("\n");
	}
}

void print_2Darray(int *A, int r, int c) {
	int i, j;
	for (i=0; i<r; i++) {
		for (j=0; j<c; j++)
			printf("%d ", A[i*c + j]);
		printf("\n");
	}
}

// swaps array elements i and j
void exch(int *a, int i, int j) {
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

// take as input an array of int and rearrange them in random order
void shuffle(int *a, int N) {
	if(N==0) {
		return;
	}
	int r = (rand() % (N));
	exch(a , 0 , r);
	shuffle(a+1 , N-1);
}

// take as input an array of int and print them out to standard output
void show(int *a, int N) {
	int i;
    for (i = 0; i < N; i++) {
		printf("%d ", a[i]);
    }
	printf("\n");
}

void generate_maze(int *maze_array, int maze_size, int *v_wall_num,
	int *v_wall, int *h_wall_num,
	int *h_wall, int num_rows,
	int num_cols) {
		// for run every array
		for(int i = 0 ; i < maze_size ; i++) {
			int v_wall_i;
			// find where is v_wall_i
			for(int j = 0 ; j < maze_size ; j++) {
				if(v_wall_num[j]==i) {
					v_wall_i = j;
				}
			}
			// check is not bound right
			if( (v_wall_i + 1) % num_cols != 0 ) {
				// check can open gate or not
				if( find(maze_array , v_wall_i) != find(maze_array , v_wall_i + 1 ) ) {
					// open if can
					v_wall[v_wall_i] = 1;

					q_union(maze_array, find(maze_array , v_wall_i) , find(maze_array , v_wall_i + 1 ));
				}
			}

			int h_wall_i;
			// find where is h_wall_i
			for(int j = 0 ; j < maze_size ; j++) {
				if(h_wall_num[j] == i) {
					h_wall_i = j;
				}
			}

			// check is not bound bot
			if( h_wall_i < (num_cols * (num_rows-1))) {
				// can open bot gate
				if( find(maze_array , h_wall_i) != find(maze_array, num_cols + h_wall_i )) {
					// open it
					h_wall[h_wall_i] = 1;

					q_union(maze_array, find(maze_array , h_wall_i) , find(maze_array, num_cols + h_wall_i ));
				}
			}
		}
}

int main(int argc, char **argv) {
	int i, j;
	int num_rows, num_cols;
	int v_wall[MAX*MAX], h_wall[MAX*MAX];
	int v_wall_num[MAX*MAX], h_wall_num[MAX*MAX];
	int maze_array[MAX*MAX];
	int maze_size;

	srand(time(NULL));
	num_rows = atoi(argv[1]);
	num_cols = atoi(argv[2]);
	maze_size = num_rows*num_cols;
	for (i=0; i<num_rows; i++)
		for (j=0; j<num_cols; j++) {
			v_wall[i*num_cols + j] = 0;
			h_wall[i*num_cols + j] = 0;
		}
	print_maze(num_rows, num_cols, v_wall, h_wall);
	for (i=0; i<num_rows; i++)
		for (j=0; j<num_cols; j++) {
			v_wall_num[i*num_cols + j] = i*num_cols + j;
			h_wall_num[i*num_cols + j] = i*num_cols + j;
		}
	shuffle(v_wall_num, maze_size);
	shuffle(h_wall_num, maze_size);
	initializing_set(maze_array, maze_size);
	generate_maze(maze_array, maze_size, v_wall_num, v_wall, h_wall_num, h_wall, num_rows, num_cols);
	printf("\n");
	printf("Generated maze:\n");
	print_maze(num_rows, num_cols, v_wall, h_wall);
	return 0;
}
