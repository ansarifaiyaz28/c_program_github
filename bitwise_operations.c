/* Operations on Bits */

#include<stdio.h>


//Practice Bit_fields

/*To concise data to save memory we use bit fields

Suppose we have five datas among which 
# 3 flags of 32 bits each (if int or 1 byte if bool)
# one type which has values from 1 tp 255 (i.e. 32 bits for int)
# one interger called index which has values from 0 to 100,000 (i.e. 32 bits for int)


But, if we can pack them together than only 29 bits are sufficients, 3 bits for all flags, 8 bit for type and 18 bit for index.
This means, one integer variable of 32 bit (my machine specific) is sufficient.

We define variable to be 
//packed_data = 000f_1   f_2f_3t_7t_6   t_5t_4t_3t_2   t_1t_0i_17i_16   i_15i_14i_13i_12   i_11i_10i_9i_8   i_7i_6i_5i_4   i_3i_2i_2i_1i_0

//Now, we want to set type field (t_7t_6   t_5t_4t_3t_2   t_1t_0) of packed_data to 7( = 00 0001 11) using Bitwise Operators

*/



/*
int main(){
	
	unsigned int packed_data = 0;
	
	printf("%i\n", packed_data);
	packed_data = packed_data | (7<<18);
	
	//the above operation first convert '7' in binary form i.e. '111'
	//then shift the binar number to left for 18 times, 
	//concatenating a 0 (zero) on right at each left shift
	//forming 1 1100 0000 0000 0000 0000 (0x1c0000 in hex)
	//and 111 000 000 000 000 000 000 (07000000 in octal)
	
	printf("%o\n", 7<<18);
	printf("%x\n", packed_data);
	
	//you can genralize above with a variable
	int n=7; //assign type=n
	packed_data = packed_data | (n<<18);
	printf("%x\n", packed_data);
	
	//we want n to be between 0 ~ 255 so 
	
	n = 263 & 0xff; //263 (=1 0000 0111) and 255 (=0 1111 1111), ANDing gives 7(=0 0000 0111). can be used as modulus (%)
	printf("%i\n", n);
	packed_data = packed_data | (n<<18);
	printf("%x\n", packed_data);
	
	//if packet_data = 270532618 f1=1, type=8, index=10 and we want to set type=7
	packed_data = 270532618;	  //301204480 = 0001 0001 1111 0100 0000 0100 0000 0000 (0x11f40400) //270532618 f1=1, type=8, index=10
	printf("%li\n%lx\n", packed_data, packed_data);
	
	n=7;
	packed_data = packed_data | (n<<18); 
	printf("%x\n", packed_data);
	//this will only mask 3 LSBs of type field but 3rd bit is as it is, its better we mask type to zero first then set to 7
	//for this, 
	printf("***                  ***\n");
	packed_data = 270532618;	  
	printf("%li\n%lx\n", packed_data, packed_data);
	packed_data = packed_data & 0xfc03ffff; //ANDing with 1111 1100 0000 0011 1111 1111 1111 1111, all 8-bits of type is zero
	printf("%lx\n", packed_data); //packed_data = 0x1000000a i.e. type fiels is masked (set to zero)
	packed_data = packed_data | (n<<18); ///packed_data = 0x101c000a i.e. type field is set to 7 ('111')
	printf("%lx\n", packed_data);
	
	//to save yourself the bother of having to explicitely calculate the mask each time you can clear specific bits aas below
	printf("\n\n******************\n");
	packed_data = 270532618;	  
	printf("%li\n%lx\n", packed_data, packed_data);
	packed_data = packed_data & ~(0xff << 18); //ANDing with 1111 1100 0000 0011 1111 1111 1111 1111, 
	//but first 1111 1111 is left shifted 18 times forming 11 1111 1100 0000 0000 0000 0000 
	//then inverting it to form ...00 0000 0011 1111 1111 1111 1111
	printf("%lx\n", packed_data); //packed_data = 0x1000000a i.e. type fiels is masked (set to zero)
	packed_data = packed_data | (n<<18); ///packed_data = 0x101c000a i.e. type field is set to 7 ('111')
	printf("%lx\n", packed_data);
	
	
	//assembling above statement as one, we can have
	printf("\n\n******************\n");
	packed_data = 270532618;	  
	printf("%li\n%lx\n", packed_data, packed_data);
	packed_data = (packed_data & ~(0xff << 18)) | ((n & 0xff) << 18);
	printf("%lx\n", packed_data);
	
	//But what if packet_data = 270532618 and we want to set, say f1=1, index has some value, say 1024, and type=125. Then
	printf("\n\n******************\n");
	int f1=1, index=1024,type=125; // 125(=0111 1101); 1024 (=100 0000 0000)
	packed_data = 0; 	//270532618;	  
	printf("%li\n%lx\n", packed_data, packed_data);
	packed_data = (packed_data & ~(0x1 << 28)) | ((f1 & 0x1) << 28);	//gives packed_data = 0x10000000(=0001 0000 0000 0000 0000 0000 0000 0000)
	printf("%lx\n", packed_data);
	packed_data = (packed_data & ~(0xff << 18)) | ((type & 0xff) << 18);//gives packed_data = 0x11f40000(=0001 0001 1111 0100 0000 0000 0000 0000)
	printf("%lx\n", packed_data);
	packed_data = (packed_data & ~0x3ffff) | (index & 0x3ffff); //gives packed_data = 0x11f40400(=0001 0001 1111 0100 0000 0100 0000 0000)
	printf("%lx\n", packed_data);
	
	getch();
	return 0;
}
*/


//But we can perform above problem conveniently by using structure

/*
struct packed_struct{
	unsigned int :3;		//unused bits
	unsigned int f1:1;		//1 bit for flag f1
	unsigned int f2:1;		//1 bit for flag f2
	unsigned int f3:1;		//1 bit for flag f3
	unsigned int type:8;	//8 bits for type field
	unsigned int index:18;	//18 bits for index field
	//Note that there is no guarantee whether the fields are internally assigned 
	//from left-to-right or right-to-left
	//But it would not be a problem because we can directly set or reset the bit field using structure
};

int main(){
	int f1=1, index=1024,type=125; // 125(=0111 1101); 1024 (=100 0000 0000)
	struct packed_struct packed_data ; //initialize the structure
	printf("%i\n", packed_data);
	printf("%x\n", packed_data);
	
	packed_data.f1 = f1;
	packed_data.type = type;		//do not worry if n>255, only 8bit LSB of n will be assigned to type
	packed_data.index = index;
	
	printf("\n\n******************\n");
	
	
	printf("%i\n", packed_data.f1);
	printf("%i\n", packed_data.f2);
	printf("%i\n", packed_data.f3);
	printf("%x\n", packed_data.type);
	printf("%x\n", packed_data.index);
	printf("%i\n", packed_data);	//do be amazed with output because bit fiels are packed into units as they appear in structure definition
	printf("%x\n", packed_data);
	
	getch();
	return 0;
}

*/



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
/*
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
*/


//Exercise 11.5: Write a function called bit_test() that takes two arguments: an unsigned int and a 
//bit number n. Have the function return 1 bit number n if it is on inside the word, and 0
//if it is off. Assume that bit number 0 references the leftmost bit inside the integer. Also
//write a corresponding function called bit_set() that takes two arguments: an unsigned 
//int and a bit number n. Have the function return the result turning bit n on inside the integer.
/*
#include<stdbool.h>

int bit_test(unsigned int value, int n){
//	unsigned int tmp_value;
	
//	value = value >> n;		//right-shift the value n times so that the nth bit is LSB
	//printf("%o\n", value);
//	tmp_value = value | 1;		//ANDing LSB to 1 will result 0 if LSB=0 else 1
	//printf("%o\n", tmp_value);
	//printf("%o\n", value ^ tmp_value);
	
//	if((value ^ tmp_value) == 0)		// XORing with itself gives 0, i.e. if value == tmp_value the result will be zero meaning LSB=1
//		return 1;		//return 1 if nth bit (LSB after right shift by n times) is 1
//	else
//		return 0;		//else return 0	

	//OR,
	if ((value & (1<<n)) >>n ==1)		//shift 1 to nth bit; ANDing with value will yield the bit value; shift right to oth position
		return 1;
	else 
		return 0;
}

int int_size(unsigned int value){
	int bit_length = 0;
	do{
		value >>= 1;	//right shift insert 0 to MSB
		bit_length++;	//increament bit_length by 1 each time there is a right-shift
	}while(value !=0);	//when vlaue=0, all the bits are set to zero
	return bit_length;
}

unsigned int bit_set(unsigned int value, int n){
	/*
//	unsigned int tmp_value;
//	int integer_size = int_size(value);
//	n = n % integer_size;
	
//	tmp_value = value << (integer_size - n);		//tmp = all LSBs after nth bit
//	value = value >> n;								//value is right shifted by n times
//	value = value | 1;								//set nth bit to 1
//	value = value << n;								//value is left shifted by n times to initial position
//	tmp_value = tmp_value >> (integer_size - n);	//tmp is right shifted to init position
//	value = value | tmp_value;						// alligning the position and concatenating the required bits

//	return value;
	//OR,
	return value | (1<<n); // left shift to nth position then ORed with the value will set nth bit to 1
}

int main(){
	unsigned int value = 0123u, final_result;
	int n = 6, result; 		//n starts from zero(0) and from LSB to MSB so will always be positive
	
	result = bit_test(value, n);
	printf("target bit is = %i\n", result);
	
	if (result == 0)
		final_result = bit_set(value, n);
	else
		final_result = value;
	
	printf("final result = %o", final_result);
	
	
	getch();
	return 0;
}
*/


/*
Exercis 11.6:
Write a function called bitpat_search() that looks for the occorance of a specified 
pattern of bits inside an unsigned int. The function should take three arguments and
should be called as shown:

bitpat_search(source, pattern, n)

The function searches the integer source, starting at the leftmost bit, to see if the
rightmost n bits of pattern occur in source. If the pattern is found, have the function 
return the number of the bit at which the pattern begins, where the leftmost bit is bit 
number 0. If the pattern is not found, then have the function return -1. So, for example,
the called

index = bitpat_search(0xe1f4, 0x5, 3);

causes the bitpat_search() function to search the number 0xe1f4 (= 1110 0001 1111 
0100 binary) for the occurance of three-bit pattern 0x5 (= 101 binary). The function 
returns 11 to indicate that the pattern was found in the source begining with bit 
number 11.

Make certain that the function makes no assumptions about the size of an int (see 
exercise 3 in this chapter)
*/
/*
#include <stdbool.h>
#include<math.h>
//gives size of integer in number of bits
int int_size(unsigned int value){
	int bit_length = 0;
	do{
		value >>= 1;	//right shift insert 0 to MSB
		bit_length++;	//increament bit_length by 1 each time there is a right-shift
	}while(value !=0);	//when vlaue=0, all the bits are set to zero
	return bit_length;
}


int bitpat_search (unsigned int source, unsigned int pattern, int n){
	int sou_len, pat_len, i, result;
	unsigned int tmp_sou, pow_er;
	sou_len = int_size(source); 		//get bit length of source
	pat_len = int_size(pattern);		//get bit length of pattern
	//printf("sou_len = %i\t\t pat_len = %i\n", sou_len, pat_len);
	
	//printf("pattern = %x\t", pattern);
	pattern  >>= (pat_len - n);			//right-shift pattern such that only n MSB is remaining
	//printf("pattern = %x\n", pattern);
	
	pow_er = pow(2,n) - 1;				//generate n bits of all 1s
	//printf("masking bit = %x\n", pow_er);
	
	for (i = (sou_len - n); i > 0; i--){
		//printf("i = %i\n", i);
		tmp_sou = (source >> i) & pow_er;	//right shift source for i thimes such that the required LSB bits can be extracted for further processing
		//printf("temporary source = %x\n", tmp_sou);
		
		if ((tmp_sou ^ pattern) == 0){		//if pattern = required bit of source then return the bit number of event occurance
			result = sou_len - (n + i);
			break;
		}
	}
	if (i==0)	//if not bit pattern is found then return -1
		result = -1;
	
	return result;
}

int main(){
	
	printf("\n***********\n\nnumber of bits = %i\n", bitpat_search(0xe1f4, 0x5, 3));
	getch();
	return 0;
}
*/

/*
Exercise 11.7:


*/

/*
#include<math.h>
//gives size of integer in number of bits
int int_size(unsigned int value){
	int bit_length = 0;
	do{
		value >>= 1;	//right shift insert 0 to MSB
		bit_length++;	//increament bit_length by 1 each time there is a right-shift
	}while(value !=0);	//when vlaue=0, all the bits are set to zero
	return bit_length;
}

unsigned int bitpat_get(unsigned int x, int start, int count){
	unsigned int pow_er;
	pow_er = pow(2, count) -1; 		//generate count number of bits of all 1s
	x >>= start;					//right shift x such that stating bit the required LSB
	x &= pow_er;					//extract count number of bits of x
	return x;
}

int main(){
	
	printf("\n***********\n\nnumber of bits = %x\n", bitpat_get(0xe1f4, 3, 5));
	getch();
	return 0;
}
*/


/*
Exercise 11.8:
Write a function called bitpat_set() to set a specified set of bits to a particular value.
The function should take four arguments: a pointer to an unsigned int in which the 
specified bits are to be set; another unsigned int containing the value to which the
apecified bits are to be set, right adjusted in the unsigned int; a third int that specifies
the starting bit number (with the leftmost bit numbered 0); and a fourth int specifying 
the size of the field. So the call 

bitpat_set (&x, 0, 2, 5);

has the effect of setting the five bits contained in x, begining with the third bit from 
the left (bit number 2), to 0. Similarly, the call

bitpat_set (&x, 0x55u, 0, 8);

sets the eight leftmost bits of x to hexadecimal 55.
Make no assumption about the particular size of an int (refer to exercise 3 in this 
chapter)
*/

#include<math.h>

//gives size of integer in number of bits
int int_size(unsigned int value){
	int bit_length = 0;
	do{
		value >>= 1;	//right shift insert 0 to MSB
		bit_length++;	//increament bit_length by 1 each time there is a right-shift
	}while(value !=0);	//when vlaue=0, all the bits are set to zero
	return bit_length;
}

void bitpat_set (unsigned int *xptr, unsigned int set_bit, int start,  int field_size){
	unsigned int pow_er;
	
	pow_er = pow(2, field_size) - 1;	//generate field_size number of bits of all 1s
	printf("power = %i\n", pow_er);
	pow_er <<= start;					//all 1s are left shifted to align the target bits
	printf("power = %i\n", pow_er);
	
	printf("set bit before = %x\n", set_bit);
	set_bit <<= start;					//align setting bits to target bits
	printf("set bit after = %x\n", set_bit);
	
	printf("x before = %x\n", *xptr);
	*xptr &= ~(pow_er);
	printf("x after masking = %x\n", *xptr);
	
	*xptr |= set_bit;
	printf("x after setting bit = %x\n", *xptr);
}

int main(){
	unsigned int x = 0xe1f4;
	bitpat_set(&x, 0, 2, 5);
	printf("\n***********\n\nnumber of bits = %x\n\n", x);

	x = 0xe1f4;
	bitpat_set(&x, 0x55u, 0, 8);
	printf("\n***********\n\nnumber of bits = %x\n\n", x);
//	getch();
	return 0;
}



