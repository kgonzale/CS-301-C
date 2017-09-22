/*	File: Lab0.c

	Problem: Design software to find amicable numbers. 
	
	To tackle this problem we followed the three steps of
	standard software phases: input, process, and output. 
	For the input phase, we allowed the user to input an
	integer, where if the user inputted a negative or less
	than 284, we would ask for a new input. For the process
	phase, we used a recursion-like method: sumOfTheDivisors.
	First, we move into the for loop with the user input,
	call sumOfTheDivisors and figure out if two numbers are amicable.
	For our output, we simply place the amicable pairs in slots in the 
	array (indexes) and increase the index by two everytime we find an
	amicable pair. 

	@authors: Kevin Gonzalez
 */

#include <stdio.h>

/*  This is where the processing of the addition of the divisors
	occurs. First, we declare sum to 0 because we need a counter
	to be looking through the loop each time we have a divisor. 
	Then in the while loop, we want to make sure that the number
	entered is not added in the count, so we divide it by 2. Then 
	we check if there are any remainders, if there are don't add 
	it to the counter, add only the integers without remainders into
	the counter. Reminder that b will keep incrementing, thus finding
	the divisors of the inputted number. 

	Finally, we return the sum. 

*/	
long sumOfTheDivisors(long i) {
	long sum = 0;
	long b = 1;
	
	while(b <= i / 2) {
		if(i % b == 0) {
			sum += b;
		}
		b++;
	}
	return sum; 
}

/*	This function is in charge of asking for input, part of the
	processing, and the output. First we initialize an array, 
	this array is static and can be given any amount of slots.
	For this assignment, we thought that 100 would be sufficient.
	We initialize an index for the array, lowestInt which would
	be in charge of looping through the highestInt checking for
	amicable pairs. 
	
	The first for loop checks for amicable pairs by calling 
	sumOfTheDivisors and comparing the value inputted to the sum.
	We do this for i and for j, which would ultimately give us our 
	amicable pairs. 
	
	For the second for loop, we are simply printing out the values
	that are in the array. Since the first for loop takes care of 
	setting each amicable pair in its own index, we don't have to 
	worry about that in the second for loop. 

*/	 	

int main(void) {
	long array[100];
	int index = 0;
	long lowestInt = 1; 
	long highestInt;

	printf("Enter a large positive integer: ");
	scanf("%ld", &highestInt);

	if (highestInt < 0) {
		printf("Enter a large non-negative integer: ");
		scanf("%ld", &highestInt);
	}
	else if (highestInt < 284){
		printf("There are no amicable pairs under %ld.\n", highestInt);
	}

	for (long i = lowestInt; i <= highestInt; i++) {
		long j = sumOfTheDivisors(i); 
		if ((i < j) && (j <= highestInt) && sumOfTheDivisors(j) == i) {
			array[index] = i;
			array[index + 1] = j; 
			index += 2;
		}
	}

	for (int x = 0; x < index; x += 2) {
		printf("(%ld, %ld) \n" , array[x], array[x + 1]);
	}

}