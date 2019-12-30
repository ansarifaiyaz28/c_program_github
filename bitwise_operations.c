/* Operations on Bits */

#include<stdio.h>
#include<conio.h>

/*Program 11.2: Program to illustrate bitwise operaors*/
/*
int main(){
	
	unsigned int w1 = 0525u, w2 = 0707u, w3 = 0122u;
	
	printf("%o \t %o \t %o\n", w1 & w2, w1 | w2, w1 ^ w2);
	printf("%o \t %o \t %o\n", ~w1, ~w2, ~w3);
	printf("%o \t %o \t %o\n", w1 ^ w1, w1 & ~w2, w1 | w2 | w3);
	printf("%o \t %o\n", w1 | w2 & w3, w1 | w2 & ~w3);
	printf("%o \t %o\n", ~(~w1 & ~w2), ~(~w1 | ~w2));
	
	w1 ^= w2;
	w2 ^= w1;
	w1 ^= w2;
	
	printf("%o \t %o\n", w1, w2);
	
	getch();
	return 0;
}
*/


/*Program 11.3: Function to shoft an unsigned int left if the count is positive, and right if negative*/
/*
unsigned int shift(unsigned int value, int n){
	unsigned int result;
	
	if (n>0) 	//left shift
		result = value << n;
	else 		//right shift
		result = value >> -n; //-n will change negative value of n to positive n
	return result;
}

int main(){
	
	unsigned int w1 = 0177777u, w2 = 0444u;
	
	printf("%o \t %o\n", shift(w1, 5), w1 << 5); //left shift w1 by 5 bits i.e. 2 octate digits are 40
	printf("%o \t %o\n", shift(w1, -6), w1 >> 6); //ight shift w1 by 6 bits
	printf("%o \t %o\n", shift(w2, 0), w2 >> 0);
	printf("%o\n", shift(shift(w1, -3), 3)); //inner loop shift w1 right by 3 bits and outer loop shift the resulted value left by 3 bits
	printf("%o\n", w1 & ~7);
	
	getch();
	return 0;
}
*/

/*Program 11.4: Pogram to illustrate rotation of integers*/
/*
unsigned int rotate(unsigned int value, int n){
	unsigned int bits, result;
	if(n>0)
		n %= 32;
	else
		n= -(-n%32);
	
	if (n==0)
		result = value;
	else if (n > 0){
		bits = value >> (32-n);
		result = value << n | bits;
	}
	else{
		n = -n;
		bits = value << (32-n);
		result = value >> n | bits;
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
	
	getch();
	return 0;
}
*/

/*Exercise 11.2: Write a program that determines whether your particular computer 
performs an arithematic or a logical right shift*/
/*
int main(){
	
	printf("%o\n", 012u >> 1);
	printf("%o\n", 012u << 1);
	printf("%i\n", 12 >> 1);
	printf("%i\n", 12 << 1);
	
	getch();
	return 0;
}
*/

//Exercise 11.3: Given that the expression ~0 produces and integer that contains all 1s, write a function called int_size()
//that returns the number of bits contained in an int
// on your machine
/*
int int_size(unsigned int value){
	int bit_length = 0;
	do{
		value >>= 1;	//right shift insert 0 to MSB
		bit_length++;	//increament bit_length by 1 each time there is a right-shift
	}while(value !=0);	//when vlaue=0, all the bits are set to zero
	return bit_length;
}

int main(){
	int bit_length = int_size(~0);
	printf("%i", bit_length);
	getch();
	return 0;
}
*/

//Exercise 11.4: Using the result obtaines in exercise 3, modify the rotate() function from thr Program 11.4
//so that it no longer makes any assumptions about the size of an int.

int int_size(unsigned int value){
	int bit_length = 0;
	do{
		value >>= 1;	//right shift insert 0 to MSB
		bit_length++;	//increament bit_length by 1 each time there is a right-shift
	}while(value !=0);	//when vlaue=0, all the bits are set to zero
	return bit_length;
}

unsigned int rotate(unsigned int value, int n){
	unsigned int bits, result;
	int bit_len = int_size(~0);
	
	n = n % bit_len;

	if (n==0)
		result = value;
	else if (n > 0){
		bits = value >> (bit_len - n);
		result = (value << n) | bits;
	}
	else{
		n = -n;
		bits = value << (bit_len - n);
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
	
	getch();
	return 0;
}



