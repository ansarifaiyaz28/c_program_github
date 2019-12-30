#include<stdio.h>
unsigned int rotate(unsigned int value, int n){
	unsigned int bits, result;
	if (n>0)
		n %= 32;
	else
		n = -(-n%32);
	
	if (n==0)
		result = value;
	else if (n > 0){
		bits = value >> (32-n);
		result = (value << n) | bits;
	}
	else{
		bits = value << (32-n);
		result = (value >> n) | bits;
	}
	
	return result;
}

int main(){
	
	unsigned int w1 = 0xabcdef00u, w2 = 0xffff1122u;
	
	printf("%x\n", rotate(w1, 8));
	printf("%x\n", rotate(w1, -16));
	printf("%x\n", rotate(w2, 4));
	printf("%x\n", rotate(w2, -2));
	printf("%x\n", rotate(w1, 0));
	printf("%x\n", rotate(w1, 44));
	
	return 0;
}
