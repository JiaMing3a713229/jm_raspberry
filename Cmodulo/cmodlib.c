#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MOD_SPACE 23
#define DIM 4   // a_4x^4 + a_3x^3 + a_2x^2 + a_1x^1 + a_0  共5個元素 4個階數
typedef struct ploy{

	//int32_t coefficient[DIM + 1];
	int32_t *coefficient;
	int32_t degree;

}poly_t;

void poly_init(poly_t* _poly, int32_t _degree){

	_poly -> degree = _degree;
	_poly -> coefficient = (int32_t *)malloc(DIM * sizeof(int32_t));

}

void poly_set(poly_t* _poly, int32_t coef[DIM]){
	/**
	 *	check the degree of poly
	 *	set number of poly
	 */	
	int i = 0;
	while(coef[DIM-1-i] == 0){
		_poly -> degree--;
		i++;
	}

	for(int i=0; i<DIM; ++i){

		_poly -> coefficient[i] = coef[i];

	}


}
/*------ a^-1 mod b------- */
uint32_t modulo_inv(int32_t a, int32_t b){
	
	if(a < 0){
		a = (a % (int32_t)MOD_SPACE) + b;
	       //printf("a<0 a is %d\r\n", a);	
	}
        int32_t q, r;
        int32_t d1 = 0;
        int32_t d2 = 1;
        int32_t d = -1;
        int32_t mod_space = b;
        while(a != 1){

                int32_t tmp = a;
                q = b / a;
                r = b % a;
                b = tmp;
                a = r;
                d = d1 - (q * d2);
                d1 = d2;
                d2 = d;

                if(r == 0){

                        return -1;

                }

        }

        if(d2 < 0){

                return d2 + mod_space;
        }

        return d2;



}

int32_t mod_division(int32_t dividend, int32_t division, int32_t modulo){

	return (dividend * modulo_inv(division, modulo)) % modulo;

}

void poly_division(poly_t _dividend, poly_t division, poly_t* reminder, poly_t* quotient){
	
	int32_t q;
	
	poly_t ret;
	poly_init(&ret);
	memcpy(&ret, &_dividend, sizeof(poly_t));

	printf("-----------division------------\r\n");
	printf("degree of ret : %d \r\n", ret.degree);
	for(int i=0; i<DIM; ++i){
		
		printf("%d \t", ret.coefficient[i]);
	}
	printf("\r\n");

	printf("degree of division is %d \r\n", division.degree);
	for(int i=0; i<=division.degree; ++i){
		printf("%d \t", division.coefficient[i]);
	}
	printf("\r\n");

	while(ret.degree >= division.degree){
		q = (ret.coefficient[ret.degree] * modulo_inv(division.coefficient[division.degree], (int32_t)MOD_SPACE));		
		printf("q is %d * %d \r\n", ret.coefficient[ret.degree], modulo_inv(division.coefficient[division.degree], (int32_t)MOD_SPACE));
		

		for(int i=0; i<=division.degree; ++i){
			
			printf("org_ret[%d]:%d \t", ret.degree - i, ret.coefficient[ret.degree - i]);
			printf("org_division :%d\t", division.coefficient[division.degree]);	
			ret.coefficient[ret.degree - i] -= division.coefficient[division.degree - i] * q;
			ret.coefficient[ret.degree - i] = ret.coefficient[ret.degree - i] % (int32_t)MOD_SPACE;
			printf("ret[%d] : %d \r\n", ret.degree - i, ret.coefficient[ret.degree - i]);
		
		}
		--ret.degree;
	}

}
	
poly_t poly_exgcd(polt_t f){
	
	poly_t ring = {
		.degree = (int32_t)DIM - 1,
		.coefficient = (int32_t*)malloc((DIM) * sizeof(int32_t))
	};
	poly_t reminder, quotient;
	/* init reminder, quotient;
	 */	   
	reminder.degree = poly1.degree - poly2.degree;
	reminder.coefficient = (int32_t *)malloc((reminder.degree + 1) * sizeof(int32_t));
	for(int i=0; i<=reminder.degree; ++i){
		reminder.coefficient[i] = 0;
	}

	quotient.degree = poly2.degree -1;
	quotient.coefficient = (int32_t *)malloc((quotient.degree + 1) * sizeof(int32_t));
	for(int i=0; i<=quotient.degree; ++i){
		quotient.coefficient[i] = 0;
	}


	for(int i=0; i<=ring.degree; ++i){
		
		if(i == 0){
			ring.coefficient[i] = -1;
		}
		else if(i == ring.degree){
			ring.coefficient[i] = 1;
		}
		else{
			ring.coefficient[i] = 0;
		}

		printf(" %d\t", ring.coefficient[i]);
	}
	printf("\r\n");

	

	


}



int main(void){

	uint32_t _a, _b;
        uint32_t inv_ret;
	uint32_t mod_space = MOD_SPACE;
	poly_t poly1, poly2, reminder, quotient;

        printf("---------a / b mod b--------\r\n");
        printf("please enter number a:");
        scanf("%d", &_a);


        printf("please enter number b:");
        scanf("%d", &_b);


	printf("%d ^-1 = %d mod %d \r\n", _b, modulo_inv(_b, mod_space), mod_space);

        printf("\r\n------check---------\r\n");
        printf("%d / %d = %d mod %d  \r\n", _a, _b, mod_division(_a, _b, mod_space), mod_space);
        printf("------init -----\r\n");

	poly_init(&poly1, (uint32_t)DIM);
	poly_init(&poly2, (uint32_t)DIM);

	reminder.degree = poly1.degree - poly2.degree;
	reminder.coefficient = (int32_t *)malloc((reminder.degree + 1) * sizeof(int32_t));
	for(int i=0; i<=reminder.degree; ++i){
		reminder.coefficient[i] = 0;
	}

	quotient.degree = poly2.degree -1;
	quotient.coefficient = (int32_t *)malloc((quotient.degree + 1) * sizeof(int32_t));
	for(int i=0; i<=quotient.degree; ++i){
		quotient.coefficient[i] = 0;
	}

	for(int i=0; i<DIM; ++i){
		printf("%d \t", poly1.coefficient[i]);
	}
	printf("\r\n");
	for(int i=0; i<DIM; ++i){
		printf("%d \t", poly2.coefficient[i]);
	}
	printf("\r\n");
	
	//冪次順序由小到大
	uint32_t f[] = {1, 1, -1, 0};
	uint32_t fp[] = {0, 2, 0, 0};
	printf("-----set poly------\r\n");

	poly_set(&poly1, f);
	poly_set(&poly2, fp);

	for(int i=0; i<DIM; ++i){
		printf("%d \t", poly1.coefficient[i]);
	}
	printf("\r\n");

	for(int i=0; i<DIM; ++i){
		printf("%d \t", poly2.coefficient[i]);
	}
	printf("\r\n");
	
	printf("the size of f :%d \r\n", sizeof(poly1.coefficient));	
	
	printf("poly1 degree:%d\r\n", poly1.degree);
	printf("poly2 degree:%d\r\n", poly2.degree);
	
	poly_division(poly1, poly2, &reminder, &quotient);
	poly_exgcd();	

	free(quotient.coefficient);
	free(reminder.coefficient);
	free(poly1.coefficient);
	free(poly2.coefficient);
	return 0;
}
