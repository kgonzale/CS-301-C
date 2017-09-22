/*	File: Lab1.c

	Problem. Design software to find the cycle length of a linear 
	congruential number generator. 
	
	For a positive integer n, an easy way generate random numbers 
	mod n is to use rand() % n, where rand() is C's random number 
	generator. How uniform are these values? Generate a large number 
	L of values. Count the number of times each value occurs and 
	determine how uniform the counts are. 

	@authors: Kevin Gonzalez & Djorjde Djordjevic
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>


/*  The point of this function is to avoid constant repetition of 
	'( a * x + b ) % m,' instead we can call to the function 'numGen.'
	
	This function will create a sequence of pseudo random integers and 
	return that number. 
 
 */

int numGen(int a, int b, int x, int m) {
    return (a * x + b) % m;
}

/*	To find the cycle value, we use the function 'cycleValue' which takes
	in four integers: a, b, c, m. The function will contain the slow generator
	and the fast generator that will call to 'numGen' to perform '(a*x+b)%m.' 
	Now, our logic behind the fast generator is to call for the calculation a 
	second time, where ultimately, one step(one number) will be skipped. Thus
	leading to a shorter cycle length and a faster generator. Taking this into
	consideration, the while loop will start when t1 != t2, meaning slower gen.
	vs. faster gen. and when they do equal, stop looping and return the cycle 
	value. 
 
 */
int cycleValue(int a, int b, int c, int m) {
    int t1 = numGen(a, b, c, m); // slow generator
    int t2 = numGen(a, b, c, m);
    t2 = numGen(a, b, t2, m); // fast generator
    
    while (t1 != t2) { // repeat until cycle value is found
        t1 = numGen(a, b, t1, m);
        t2 = numGen(a, b, t2, m);
        t2 = numGen(a, b, t2, m); // twice as fast
    }
    
    return t1;
}

/*  'cycleLength' will find the cycle length with the provided cycle value from
	'cycleValue.' By definition, the cycle length occurs when the cycle value 
	happens twice. The while loop will take charge of looping through until the
	length of the actual cycle is found. 
	
	'return length' will return the value of the length. 
 */
int cycleLength(int a, int b, int c, int m, int cycleVal) {
    cycleVal = cycleValue(a, b, c, m);
    int t1 = numGen(a, b, cycleVal, m);
    int length = 1;
    
    while (t1 != cycleVal) {
        t1 = numGen(a, b, t1, m);
        length += 1;
    }
    
    return length;
}

/*	This function will be in charge of placing numbers into an array called vec. 
	Then this will be used to track the uniformity of the values. 

	'return vec' returns the array (histogram). 
 */
int * histogram( int x, int n) {
	int * vec = ( int * )calloc( n, sizeof( int ) );
	
	for (int i = 0; i<x; i++) {
	int a = rand()%	n;
	vec[a] = vec[a]+1;
	}
	
	return vec;
	
}


/*	 As taken from the instructions, this function implements the idea of 
	(observed count - expected count)^2 / expected count. Instead of floats,
	this function has floats. Main reason being because when you divide 
	5/3, you want a float and not an int (5/3 being an example).  

  */
float uniformity(int * h, int x, int n) {
	float a = 0;
	float sum = 0;
	
	for(int i = 0; i < n; i++) {
    float value = (float)h[i];
 	a = (value-(float)(x/n))*(value-(float)(x/n))/(float)(x/n);
	sum += a;
	}
	
	return sum;
	
}


/*  In the main, we ask the client for values of a, b, c, m, x, n 
	with scanf. These values will then be processed throughout our
	code to find the cycle value, cycle length, value and occurence,
	and uniformity. 
	
	To print the value and occurence we use a for loop. This will loop
	through our histogram. Aside from this, everything else is just 
	printed without a loop. 

*/
int main() {
	int a = 0, b = 0, c = 0, m = 0, x = 0, n = 0;
   	
	printf("Enter a: \n");
	scanf("%d", &a);
	
	printf("Enter b: \n");
	scanf("%d", &b);
	
	printf("Enter c: \n");
	scanf("%d", &c);
	
	printf("Enter m: \n");
	scanf("%d", &m);
	
	printf("Enter the number of random numbers: \n");
	scanf("%d", &x);
	
	printf("Enter modulus: \n");
	scanf("%d", &n);
	
	
	int cv = cycleValue(a, b, c, m);
	int cycles = cycleLength(a, b, c, m, cv);
	int * hist = histogram(x, n);
    float u = uniformity(hist, x, n);
    printf("The length of the cycle is: %d \n", cycles);
	
	for(int i = 0; i < n; i++) {
     printf("Value and Occurence : %d, %d \n", i, hist[i]);
	}
	
    printf("The deviation of uniformity is %.2f\n", u);
    
    return EXIT_SUCCESS;
}