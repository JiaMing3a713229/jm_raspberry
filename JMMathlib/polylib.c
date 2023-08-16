#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define N (int32_t)23
#define POLY_DIM 5
#define POLY_SPACE (POLY_DIM + 1)

typedef struct poly{

	int32_t *coef;
	int32_t degree;

}poly_t;

/*** a^-1 mod b ****/
int32_t inv_mod(int32_t a, int32_t b){
	
	
	int32_t q, r;
	int32_t d1 = 0;
	int32_t d2 = 1;
	int32_t d = -1;
	int32_t space_mod = b;
	a = (a > 0)? a: (a+b)%b;
	while((b != 0) && (a != 1)){

		q = b / a;
		r = b % a;
		b = a;
		a = r;
		d = d1 - (d2 * q);
		d1 = d2;
		d2 = d;

	}

	return d2 > 0 ? d2 : (d2 % space_mod) + space_mod;


}

enum TEST_MODE{
	
	TEST_INVERSE = 0

};

void init_poly(poly_t *_poly, int32_t _degree){
	
	_poly -> coef = (int32_t *)malloc(sizeof(int32_t) * (_degree + 1));
	_poly -> degree = _degree;
	for (int i = 0; i <= (_poly->degree); ++i){
		
		_poly -> coef[i] = 0;
		printf("%d \t", _poly->coef[i]);
	}
	printf("\r\n");
	
}

void set_poly(poly_t* _poly, int32_t coef[]){

	int cheak_mode = 1;
	int poly_size = _poly -> degree;
	for(int i = 0; i <= poly_size; ++i){
		
		if(coef[poly_size - i] == 0 && cheak_mode == 1){
			--(_poly -> degree);
		}

		else{
			_poly -> coef[poly_size - i] = coef[poly_size - i];
			cheak_mode = 0;
		}
	}

	printf("set_poly degree: %d \r\n", _poly->degree);
	for(int i=0; i<=_poly->degree; ++i){
		printf("%d \t", _poly->coef[i]);
	}
	printf("\r\n");

}

void print_poly(poly_t* _poly){

	printf("\n poly degree : %d----\t", _poly -> degree);
	for(int i=0; i<= _poly -> degree; ++i){
		
		printf("%d \t", _poly->coef[i]);

	}
	printf("\r\n");

}

void division_poly(poly_t* dividend, poly_t* division, poly_t* quotient, poly_t* reminder){
	
	print_poly(dividend);
	print_poly(division);

	int i = 0;
	
	while((dividend -> degree)>=(division -> degree)){
	
		int32_t q_degree = (dividend -> degree) - (division -> degree);
		printf("\n --- quotient degree %d \n", q_degree);
		//quotient -> coef[q_degree] = ((dividend -> coef[dividend->degree]) * (inv_mod((division->coef[division->degree]), N))) % N;
		
		
		int32_t q = ((dividend->coef[dividend->degree]) * inv_mod((division->coef[division->degree]), N) % N);
		quotient->coef[q_degree] = q;
		printf("Q ret %d \n",quotient->coef[q_degree]);

		
		for(int i=0; i <= division->degree; ++i){

			dividend -> coef[dividend -> degree - i] = ((dividend->coef[dividend -> degree - i]) - (q * division->coef[division->degree - i])) % N;
			printf("%d \t", dividend -> coef[dividend -> degree - i]);


		}



		printf("\n");
		
		/****  dividend coef -= division * quotient ***/
	       	(dividend -> degree)--;	

	}	
	

	print_poly(dividend);




}

void test_(int TEST_MODE){

	int32_t a, b;
	int32_t ret;
	switch(TEST_MODE){
		
		case 0:
			printf("\r\n  Calculate Inverse of modulo \r\n");
			printf("------ a^-1 mod b ------\n");
			printf("Enter a: \t");
			scanf("%d", &a);
			printf("Enter b: \t");
			scanf("%d", &b);
			ret = inv_mod(a, b);
			printf("a^-1 : %d \n", ret);
			printf("----check-----\n");
			printf("%d * %d mod %d = %d \n", a, ret, b, ((a * ret) % b));
			break;
		default:

			break;



	}



}

int main(void){


	poly_t poly1, poly2, quotient, reminder;
	int32_t poly1_coeff[] = {-1, 0, 0, 1, 0};
	int32_t poly2_coeff[] = {1, 1, -1, 0, 0};

	init_poly(&poly1, POLY_DIM - 1);
	init_poly(&poly2, POLY_DIM - 1);
	init_poly(&quotient, POLY_DIM - 1);
	init_poly(&reminder, POLY_DIM - 1);
	
	set_poly(&poly1, poly1_coeff);
	set_poly(&poly2, poly2_coeff);

	division_poly(&poly1, &poly2, &quotient, &reminder);
	test_(0);



	
	free(poly1.coef);
	free(poly2.coef);
	free(quotient.coef);
	free(reminder.coef);
	return 0;
}
