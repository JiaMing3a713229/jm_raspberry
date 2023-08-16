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

void copy_poly(poly_t* dest, const poly_t* src) {
    // 複製 degree
    dest->degree = src->degree;

    // 為 coef 分配記憶體
    dest->coef = (int32_t *)malloc((dest->degree + 1) * sizeof(int32_t));

    // 確保記憶體分配成功
    if (!dest->coef) {
        printf("Memory allocation error!\n");
    }

    // 複製 coef 的值
    for (int i = 0; i <= dest->degree; i++) {
        dest->coef[i] = src->coef[i];
    }
}

void division_poly(poly_t* _dividend, poly_t* _division, poly_t* _quotient, poly_t* _reminder){
	
	print_poly(_dividend);
	print_poly(_division);

	
	int32_t q_degree = (_dividend -> degree) - (_division -> degree);
	_quotient->degree = q_degree;
	int32_t j = 0;	
	while((_dividend -> degree)>=(_division -> degree)){
	
		//printf("\n --- quotient degree %d \n", q_degree);
		//quotient -> coef[q_degree] = ((dividend -> coef[dividend->degree]) * (inv_mod((division->coef[division->degree]), N))) % N;
		
		
		int32_t q = ((_dividend->coef[_dividend->degree]) * inv_mod((_division->coef[_division->degree]), N) % N);
		_quotient->coef[q_degree - j] = q;
		printf("Q ret %d \n",_quotient->coef[q_degree]);

		
		for(int i=0; i <= _division->degree; ++i){
			
			_dividend -> coef[_dividend -> degree - i] = ((_dividend->coef[_dividend -> degree - i]) - (q * _division->coef[_division->degree - i])) % N;
			printf("%d \t", _dividend -> coef[_dividend -> degree - i]);


		}



		printf("\n");
		
		/****  dividend coef -= division * quotient ***/
	       	(_dividend -> degree)--;
		++j;	

	}	
	
	//print_poly(_quotient);
	//print_poly(dividend);
	copy_poly(_reminder, _dividend);
	//memcpy(_reminder, _dividend, sizeof(_dividend));

}

void multi_poly(poly_t _a, poly_t _b, poly_t* ret){
	
	

}
/*
 *  poly_A ^ -1 mod (x^(N+1) -1));
 */
void exgcd_poly(poly_t* f){
	
	poly_t ring, quotient, reminder;
	init_poly(&ring, f->degree + 1);
	init_poly(&quotient, POLY_DIM - 1);
	init_poly(&reminder, POLY_DIM - 1);

	ring.degree = (f -> degree) + 1;
	ring.coef[ring.degree] = 1;
	ring.coef[0] = -1;

	int32_t d1 = 0;
	int32_t d2 = 1;
	int32_t d = -1;

	division_poly(&ring, f, &quotient, &reminder);	
	print_poly(&quotient);
	print_poly(&reminder);
	



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

	//division_poly(&poly1, &poly2, &quotient, &reminder);
	//test_(0);

	exgcd_poly(&poly2);

	
	free(poly1.coef);
	free(poly2.coef);
	free(quotient.coef);
	free(reminder.coef);
	return 0;
}
