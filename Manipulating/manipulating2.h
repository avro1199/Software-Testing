#include "manipulating.h"

/* Version 1 */
// MANIPULATING SOURCE
#define _CRT_SECURE_NO_WARNINGS
#define BUFFER_SIZE 80

// Version 1 (Manipulating) Concatenating strings Demo
void manipulating(void)
{
	printf("*** Start of Concatenating Strings Demo ***\n");
	char string1[BUFFER_SIZE]; // Declare string1 as a array with macro size
	char string2[BUFFER_SIZE]; // Declare string2 as a array with macro size
	do
	{
		printf("Type the 1st string (q -to quit) : \n");
		fgets(string1, BUFFER_SIZE, stdin);	 // The library function gets reads the line from the stdin and stores it in string1
		string1[strlen(string1) - 1] = '\0'; // Remove newline character
		if ((strcmp(string1, "q") != 0))
		{
			printf("Type the 2nd string: \n");
			fgets(string2, BUFFER_SIZE, stdin); // The library function gets reads the line from the stdin and stores it in string2
			string2[strlen(string2) - 1] = '\0';
			strcat(string1, string2);							// Concatenate string2 to string1
			printf("Concatenated string is \'%s\'\n", string1); // Print concatenated string1
		}

	} while (strcmp(string1, "q") != 0); // Exit 'while' loop while user input 'q'
	printf("*** End of Concatenating Strings Demo ***\n\n"); // After exit message is passed through printf function

	/* Version 2 */
	//>> insert here
	
	printf("*** Start of Comparing Strings Demo ***\n");
	char compare1[BUFFER_SIZE]; // Declare 1st string named compare1 as a array with macro size
	char compare2[BUFFER_SIZE]; // Declare 2nd string named compare2 as a array with macro size
	int result;
	do
	{
		printf("Type the 1st string to compare (q -to quit) : \n");
		fgets(compare1, BUFFER_SIZE, stdin);   // The library function gets reads the line from the stdin and stores it in compare1
		compare1[strlen(compare1) - 1] = '\0'; // Remove newline character
		if (strcmp(compare1, "q") != 0)
			printf("Type the 2nd string to compare: \n");
		fgets(compare2, BUFFER_SIZE, stdin); // The library function gets reads the line from the stdin and stores it in compare2
		compare2[strlen(compare2) - 1] = '\0';
		result = strcmp(compare1, compare2); //
		if (result < 0)
			printf("\'%s\' string is less than \'%s\'\n", compare1, compare2);
		else if (result == 0)
			printf("\'%s\' string is equal to \'%s\'\n", compare1, compare2);
		else
			printf("\'%s\' string is greater than \'%s\'\n", compare1, compare2);
	} while (strcmp(compare1, "q") != 0); // Exit 'while' loop while user input 'q'
	printf("*** End of Comparing Strings Demo ***\n\n"); // After exit message is passed through printf function

	/* Version 3 */
	//>> insert here
}
