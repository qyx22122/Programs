#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int comp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}
int main(){
	srand(time(0));
	int nums[] = {2,3,5,7,11,13,17,19};
	int ps[10];
	int r1 = rand()%3 + 5;
	int r2 = rand()%2 + 2;
	for(int i = 0; i < r1; i++)
		ps[i] = nums[rand()%3];
	for(int i = r1; i < r1+r2; i++)
 	   ps[i] = nums[rand()%3+6];
	int product = 1;
	qsort(ps, r1+r2, sizeof(int), comp);
	for(int i = 0; i < r1+r2; i++)
		product *= ps[i];
	printf("%d\n",product);
	scanf("%*c");
	for(int i = 0; i < r1+r2; i++)
		printf("%d ",ps[i]);	
}
