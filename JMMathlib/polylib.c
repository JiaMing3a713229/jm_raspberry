#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>


#define TEST_STATUS 1
#define N (int32_t)23
#define P (int32_t)3
#define POLY_DIM (int32_t)7
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
	
	TEST_INVERSE = 0,
	TEST_MULTI_POLY = 1

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
			if(poly_size - i > 0){

				(_poly -> degree)--;

			}
			printf("\n degree: %d \t", _poly -> degree);
		}

		else{
			_poly -> coef[poly_size - i] = coef[poly_size - i];
			cheak_mode = 0;
		}
	}
	/*
	printf("\n set_poly degree: %d \r\n", _poly->degree);
	for(int i=0; i<=_poly->degree; ++i){
		printf("%d \t", _poly->coef[i]);
	}
	printf("\r\n");
	*/

}

void print_poly(poly_t* _poly){

	printf("\n poly degree : %d----\t", _poly -> degree);

	if(_poly -> degree >= POLY_DIM){
		for(int i=0; i<= _poly->degree; ++i){
			printf("%d \t", _poly -> coef[i]);
		}

	}
	else{
		for(int i=0; i < POLY_DIM; ++i){
		
			printf("%d \t", _poly->coef[i]);

		}
	}
	printf("\r\n");

}

void copy_poly(poly_t* dest, poly_t* src) {

	init_poly(dest, POLY_DIM - 1);
    	// 複製 degree
   	dest -> degree = src -> degree;
    	// 為 coef 分配記憶體
    	//dest -> coef = (int32_t *)malloc((POLY_DIM) * sizeof(int32_t));

    	// 確保記憶體分配成功
    	if (!dest->coef) {
        	printf("Memory allocation error!\n");
    	}
    	// 複製 coef 的值
    	for (int i = 0; i <= dest->degree; i++) {
        	dest->coef[i] = src->coef[i];
    	}
	
	while((dest -> coef[dest -> degree] == 0) && dest -> degree > 0){
	
		dest -> degree--;

    	}
}

void division_poly(poly_t* _dividend, poly_t* _division, poly_t* _quotient, poly_t* _reminder, int32_t _modulo){
	
	if(TEST_STATUS){
		printf("------------------poly division:------------------ \r\n");
		printf("dividend:\t");	
		print_poly(_dividend);
		printf("division:\t");
		print_poly(_division);
		printf("quotient:\t");
		print_poly(_quotient);
		printf("reminder:\t");
		print_poly(_reminder);
	}
	int32_t q_degree = (_dividend -> degree) - (_division -> degree);
	_quotient->degree = q_degree;
	int32_t j = 0;	
	while((_dividend -> degree) >= (_division -> degree)){
	
		//printf("\n --- quotient degree %d \n", q_degree);
		//quotient -> coef[q_degree] = ((dividend -> coef[dividend->degree]) * (inv_mod((division->coef[division->degree]), N))) % N;
		
		
		int32_t q = ((_dividend->coef[_dividend->degree]) * inv_mod((_division->coef[_division->degree]), _modulo) % _modulo);
		_quotient->coef[q_degree - j] = q;
		printf("%d / %d : Q ret %d \n",_dividend->coef[_dividend->degree], inv_mod((_division->coef[_division->degree]), _modulo), _quotient->coef[q_degree - j]);

		
		for(int i=0; i <= _division->degree; ++i){
			
			_dividend -> coef[_dividend -> degree - i] = ((_dividend->coef[_dividend -> degree - i]) - (q * _division->coef[_division->degree - i])) % _modulo;
			printf("%d \t", _dividend -> coef[_dividend -> degree - i]);


		}



		printf("\n");
		
		/****  dividend coef -= division * quotient ***/
	       	(_dividend -> degree)--;
		++j;	

	}
	if(TEST_STATUS){	
		printf("quotient:");	
		print_poly(_quotient);
		printf("reminder:");
		print_poly(_dividend);
	}
	copy_poly(_reminder, _dividend);
	print_poly(_reminder);
	//memcpy(_reminder, _dividend, sizeof(_dividend));
	//printf("-------------------------------------------------\r\n");

}

void multi_poly(poly_t* _a, poly_t* _b, poly_t *ret, int32_t _modulo){
	
	

	printf("------------------poly multi:------------------ \r\n");
	if(TEST_STATUS){

		printf("poly a:\t");
		print_poly(_a);
		printf("poly b:\t");
		print_poly(_b);
	}	

	int32_t degree = (_a -> degree) + (_b -> degree); 
	init_poly(ret, degree);
	
	printf("multi degree %d \n", ret -> degree);
	int m = (int)_a -> degree;
	int n = (int)_b -> degree;
	int index = -1;	
	
	for(int i = 0; i <= m; ++i){
		for(int j = 0; j <= n; ++j){
			
			index = (i + j) % POLY_DIM; 
			ret -> coef[index] = ((ret -> coef[index]) + (_a -> coef[i]) * (_b -> coef[j])) % _modulo;		
			printf("ret[%d]=%d \t", index, ret -> coef[(i + j) % POLY_DIM]);
		}
		printf("\n");
	}
	
	print_poly(ret);
	while(ret -> coef[ret -> degree] == 0){

		--(ret -> degree); 
	}
	
	if(TEST_STATUS){
		printf("poly multi ret:\t");
		print_poly(ret);	
	}
}

void sub_poly(poly_t* _a, poly_t* _b, poly_t* ret, int32_t _modulo){

	if(TEST_STATUS){
		printf("------------------poly sub: a - b--------------- \r\n");	
		printf("poly a:\t");
		print_poly(_a);
		printf("ploy b:\t");
		print_poly(_b);

	}

	(ret -> degree) = (_a -> degree) >= (_b -> degree) ? _a -> degree : _b -> degree;

	for(int i=0; i<= (ret->degree); ++i){

		(ret -> coef[i]) = (_a -> coef[i] - _b -> coef[i]) % _modulo;

	}
	
	if(TEST_STATUS){
		printf("sub ret:\t");	
		print_poly(ret);

	}

	


}

void add_poly(poly_t* _a, poly_t* _b, poly_t* ret, int32_t _modulo){
	
	if(TEST_STATUS){
		printf("---------------------add poly-------------------\r\n");
		print_poly(_a);
		print_poly(_b);
	}
	ret -> degree = ((_a -> degree) >= (_b -> degree)) ? _a -> degree : _b -> degree;

	for(int i = 0; i <= ret->degree; ++i){

		ret -> coef[i] = (_a -> coef[i] + _b -> coef[i]) % _modulo;
	}	

}

int8_t check_exgcd(poly_t* _a, int32_t _modulo){
	
	_a -> coef[0] = (_a -> coef[0] > 0) ? _a -> coef[0] : (_a -> coef[0] % _modulo) + _modulo;	
	if((_a -> degree) == 0 && (_a -> coef[0] == 1)){
		
		return 1;

	}

	return -1;
}
/*
 *  poly_A ^ -1 mod (x^(N+1) -1));
 */
void exgcd_poly(poly_t* _f,poly_t* _ret, int32_t _modulo){
	
	poly_t f;
	copy_poly(&f, _f);

	poly_t ring, quotient, reminder;
	poly_t ret;

	init_poly(&ring, POLY_DIM);
	init_poly(&quotient, POLY_DIM - 1);
	init_poly(&reminder, POLY_DIM - 1);
	init_poly(&ret, POLY_DIM - 1);


	ring.degree = POLY_DIM;
	ring.coef[ring.degree] = 1;
	ring.coef[0] = -1;

	poly_t d1,d2,d;
	int32_t d1_coef[] = {0, 0, 0, 0, 0, 0, 0};
	int32_t d2_coef[] = {1, 0, 0, 0, 0, 0, 0};
	
	init_poly(&d1, POLY_DIM - 1);
	init_poly(&d2, POLY_DIM - 1);
	init_poly(&d, POLY_DIM -1);
	set_poly(&d1, d1_coef);
	set_poly(&d2, d2_coef);


	//擴展歐幾里得
	while(check_exgcd(&f, _modul:) != 1){

		division_poly(&ring, &f, &quotient, &reminder, _modulo);	

		if(TEST_STATUS){
			printf("------------------exgcd round:------------------ \r\n");
			printf("quotient:\t");	
			print_poly(&quotient);
			printf("reminder:\t");
			print_poly(&reminder);
		}
	
		multi_poly(&d2, &quotient, &d, _modulo);
		sub_poly(&d1, &d, &ret, _modulo);
	
		copy_poly(&d, &ret);
		copy_poly(&ring, &f);
		copy_poly(&f, &reminder);
		copy_poly(&d1, &d2);
		copy_poly(&d2, &d);
		if(TEST_STATUS){
			printf("poly ring:\t");
			print_poly(&ring);
			printf("poly f:\t");
			print_poly(&f);
			printf("poly d1:\t");
			print_poly(&d1);
			printf("poly d2:\t");
			print_poly(&d2);
	
		}
	}
	//print_poly(&d);	
	//d = d1 - d2 * q
	if(TEST_STATUS){
		printf("f ^ -1 : \t");
		print_poly(&d2);
	}
	copy_poly(_ret , &d2);
	
	if(TEST_STATUS){
		printf("***********************************************************\r\n");
	}


}

void generator_key(poly_t f_q, poly_t g_poly, poly_t* ret, int32_t _p, int32_t _modulo){


	poly_t _p_poly, ret1, ret2;
	init_poly(&_p_poly, POLY_DIM -1);
	int32_t p_coef[] = {_p, 0, 0, 0, 0, 0, 0};
	set_poly(&_p_poly, p_coef);
	multi_poly(&_p_poly, &f_q, &ret1, _modulo);
	multi_poly(&ret1, &g_poly, &ret2, _modulo);

	copy_poly(ret, &ret2);
	print_poly(ret);





}

void encrytp_ntru(poly_t* _pub_key, poly_t* _message, poly_t* _cipher_poly, int32_t _modulo){
	
	if(TEST_STATUS){
		printf("----------Encryption NTRU------------\r\n");
		printf("public key:");
		print_poly(_pub_key);
		printf("message");
		print_poly(_message);

	}	
    	poly_t r_x, temp;
	int32_t r_coef[] = {1, -1, 0, 1, 1, 1, 1};
	init_poly(&r_x, POLY_DIM -1);
	init_poly(&temp, POLY_DIM -1);

	set_poly(&r_x, r_coef);

	multi_poly(_pub_key, &r_x, &temp, 23);
	add_poly(&temp, _message, _cipher_poly, 23);

	print_poly(_cipher_poly);




}

void modulo_poly(poly_t* _poly, int32_t _modulo){

	while(_poly -> coef[_poly -> degree] == 0){
		
		(_poly -> degree)--;

	}

	for(int i = 0; i <= _poly->degree; ++i){

		_poly -> coef[i] = (_poly -> coef[i] > (_modulo / 2)) ? (_poly -> coef[i] - _modulo) % _modulo : _poly -> coef[i] % _modulo;
		_poly -> coef[i] = (_poly -> coef[i] < (-(_modulo) / 2)) ? (_poly -> coef[i] + _modulo) % _modulo : _poly -> coef[i] % _modulo;


	}

	print_poly(_poly);


}

void decrypt_ntru(poly_t* _f, poly_t* _f_p, poly_t* _cipher, poly_t* _plantext, int32_t _p, int32_t _q){

	printf("--------------------Decrypt--------------------\r\n");
	poly_t a_x, b_x;
	init_poly(&a_x, POLY_DIM - 1);
	init_poly(&b_x, POLY_DIM - 1);

	multi_poly(_f, _cipher, &a_x, 23);
	modulo_poly(&a_x, 23);
	copy_poly(&b_x, &a_x);
	modulo_poly(&a_x, 3);

	//Decryption Arithmetic
	
	multi_poly(_f_p, &b_x, _plantext, 3);
	modulo_poly(_plantext, 3);
	



}

void test_(int TEST_MODE){

	int32_t a, b;
	int32_t ret;
	poly_t poly_a, poly_b;
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
		case 1:

			break;
		default:

			break;



	}



}

int main(void){


	poly_t f_poly, quotient, reminder;
	poly_t f_p;
	poly_t f_q;
	poly_t check_fp, check_fq;
	poly_t g_poly;
	poly_t pub_key;
	poly_t message;
	poly_t cipher;
	poly_t plantext;

	int32_t message_emcoding[] = {1, 1, 1, 0, 0, 0, 0};
	int32_t polyf_coeff[] = {-1, 1, -1, 1, 0, 1, 1};
	int32_t polyg_coeff[] = {1, -1, 0, 1, -1, 1, 1};

	init_poly(&f_poly, POLY_DIM - 1);
	init_poly(&g_poly, POLY_DIM - 1);
	init_poly(&quotient, POLY_DIM - 1);
	init_poly(&reminder, POLY_DIM - 1);
	init_poly(&cipher, POLY_DIM - 1);
	init_poly(&message, POLY_DIM -1);
	init_poly(&plantext, POLY_DIM - 1);
	init_poly(&f_p, POLY_DIM - 1);
	init_poly(&f_q, POLY_DIM - 1);

	
	set_poly(&f_poly, polyf_coeff);
	set_poly(&g_poly, polyg_coeff);
	set_poly(&message, message_emcoding);

	//division_poly(&poly1, &poly2, &quotient, &reminder);
	//test_(0);

	exgcd_poly(&f_poly, &f_p, P);
	//exgcd_poly(&f_poly, &f_q, N);
		
	if(TEST_STATUS){
		
		printf("f_p :\t");
		print_poly(&f_p);
		printf("f_q :\t");
		print_poly(&f_q);

		multi_poly(&f_poly, &f_p, &check_fp, P);
		multi_poly(&f_poly, &f_q, &check_fq, N);

		print_poly(&check_fp);
		print_poly(&check_fq);

	}
	
	/*
	generator_key(f_q, g_poly, &pub_key, P, N);
	encrytp_ntru(&pub_key, &message, &cipher, N);



	decrypt_ntru(&f_poly, &f_p, &cipher, &plantext, P, N);
	printf("-----------------Decryption result-------------------\r\n");
	printf("plantext:\t");
	print_poly(&plantext);

	printf("--------------------free memory----------------------\r\n");
	*/
	free(plantext.coef);
	free(message.coef);
	free(cipher.coef);
	free(pub_key.coef);
	free(f_p.coef);
	free(f_q.coef);
	free(f_poly.coef);
	free(g_poly.coef);
	free(quotient.coef);
	free(reminder.coef);
	
	return 0;
}
