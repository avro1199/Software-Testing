#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME_LENGTH 50
#define MAX_ADDRESS_LENGTH 100
#define MAX_CITY_LENGTH 50
#define MAX_PROVINCE_LENGTH 20
#define MAX_POSTAL_CODE_LENGTH 7

struct Customer
{
    char firstName[MAX_NAME_LENGTH + 1];
    char lastName[MAX_NAME_LENGTH + 1];
    char streetAddress[MAX_ADDRESS_LENGTH];
    char city[MAX_CITY_LENGTH];
    char province[MAX_PROVINCE_LENGTH];
    char postalCode[MAX_POSTAL_CODE_LENGTH];
};

int isValidPostalCode(char *postalCode)
{

    char temp[MAX_POSTAL_CODE_LENGTH+20];
    int j = 0;

    // remove spaces and convert to uppercase
    for (int i = 0; postalCode[i] != '\0'; i++)
    {
        if (postalCode[i] != ' ')
        {
            if (postalCode[i] >= '0' && postalCode[i] <= '9')
            {
                temp[j++] = postalCode[i];//no change for digits
            }
            else
            {
                temp[j++] = postalCode[i] & 0b1011111;//converting to uppercase
            }
        }
    }

    temp[j] = '\0';

    // validate format: A1A 1A1
    if (strlen(temp) != 6)
    {
        return 0;
    }
    //matching the pattern
    if (!isalpha(temp[0]) || !isdigit(temp[1]) || !isalpha(temp[2]) ||
        !isdigit(temp[3]) || !isalpha(temp[4]) || !isdigit(temp[5]))
    {
        return 0;
    }

    // Format to A1A 1A1
    postalCode[0] = temp[0];
    postalCode[1] = temp[1];
    postalCode[2] = temp[2];
    postalCode[3] = ' '; // dividing into two parts by space
    postalCode[4] = temp[3];
    postalCode[5] = temp[4];
    postalCode[6] = temp[5];
    postalCode[7] = '\0';

    return 1;
}

//function to get input and ensure it's not empty
void getInput(char *prompt, char *input, int maxLength)
{
    while (1)
    {
        printf("%s", prompt);
        fgets(input, maxLength, stdin);
        input[strcspn(input, "\n")] = '\0'; // Remove newline character
        if(strlen(input) != 0){
            break;
        }
        printf("Invalid Input!\n");
    }
}

struct Customer getCustomerInfo()
{
    struct Customer customer;
    char buffer[MAX_ADDRESS_LENGTH];

    getInput("Enter your first name: ", customer.firstName, MAX_NAME_LENGTH);
    getInput("Enter your last name: ", customer.lastName, MAX_NAME_LENGTH);
    getInput("Enter your street address: ", customer.streetAddress, MAX_ADDRESS_LENGTH);
    getInput("Enter your city: ", customer.city, MAX_CITY_LENGTH);
    getInput("Enter your province: ", customer.province, MAX_PROVINCE_LENGTH);

    while (1)
    {
        getInput("Enter your postal code: ", buffer, MAX_POSTAL_CODE_LENGTH + 20);//extra length for spaces
        if (isValidPostalCode(buffer))
        {
            strcpy(customer.postalCode, buffer);
            break;
        }
        printf("Invalid Format!\n");
    }

    return customer;
}

int main()
{
    struct Customer customer = getCustomerInfo();
    printf("\nYou entered:\n");
    printf("%s %s\n", customer.firstName, customer.lastName);
    printf("%s\n", customer.streetAddress);
    printf("%s, %s\n", customer.city, customer.province);
    printf("%s\n", customer.postalCode);
    return 0;
}
