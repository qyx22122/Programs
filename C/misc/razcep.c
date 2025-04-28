#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	int nums[10] = {7*7,7*13,7*17,7*19,13*13,13*17,13*19,17*19,17*17,19*19};
	srand(time(0));
	int streak = 0;
	while(1){
		int p1, p2;
		char _c;
		int x = nums[rand()%10];
		printf("%d\n",x);
		int _ = scanf("%d%c%d", &p1,&_c, &p2);
		if(x == p1 * p2) printf("Good\n");
		else break;
		streak++;
	}
	printf("Wrong!!\n");
	printf("Streak : %d",streak);
}
