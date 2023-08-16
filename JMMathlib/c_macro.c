#include <stdio.h>

#define MAX(x,y) ({     \
	int _x = x;     \
	int _y = y;     \
	(_x) > (_y) ? (_x) : (_y);   \
		})

int main(void){

	int i = 3;
	int j = 7;

	printf("max(x,y)=%d \r\n", MAX(++i, ++j));

	printf("%d %d", i++, ++i);
	return 0;



}
