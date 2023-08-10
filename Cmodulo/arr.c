#include <stdio.h>
#include <stdint.h>
int main(void){

	uint8_t arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};     /*宣告arr變數為uint8_t型態之變數，
																																		*所以每個元素皆由8bit來表示，
																										  								*共10個元素
																										  								*/
	for(int i=0; i<10; ++i){
		printf("第%d個元素%d\t位址%p\r\n", i, arr[i], &(arr[i]));
	}

	return 0;


}
