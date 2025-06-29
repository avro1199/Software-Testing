// Unit test
#include <assert.h>
#include <stdio.h>

#include "Main_Code.c"

// Test valid postal code
void testValidPostalCode()
{
    char postalCode[] = "m2e 4x4";
    assert(isValidPostalCode(postalCode) == 1);
    assert(strcmp(postalCode, "M2E 4X4") == 0);
}

// Test invalid postal code
void testInvalidPostalCode()
{
    char postalCode[] = "1234";
    assert(isValidPostalCode(postalCode) == 0);
}

int main()
{
    testValidPostalCode();
    testInvalidPostalCode();
    printf("All tests passed!\n");
    return 0;
}