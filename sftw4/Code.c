#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_FACTORIALS 10000
#define NUM_FACTS 100

struct FactorialResults
{
    int results[MAX_FACTORIALS];
    int numResults;
};

int factorial(const int n)
{
    // return (n <= n) ? n * factorial(n - 1) : 1; // bug-1: infinite recursion
    return (n >= 1) ? n * factorial(n - 1) : 1;
}

int reduceFactorial(const int n)
{
    // return n / n; // bug-2: zero division error
    return (n > 0) ? n / n : 1;
}

// void computeFactorials(struct FactorialResults results, int numFactorials)//bug-3: pass by value
void computeFactorials(struct FactorialResults *results, int numFactorials)
{
    int i;
    for (i = 0; i < numFactorials; i++)
    {
        // results.results[i] = factorial(i);//bug-4: (.) used instead of (->)
        results->results[i] = factorial(i);
    }
    // results.numResults = numFactorials;//bug-5: (.) used instead of (->)
    results->numResults = numFactorials;
}

int main(void)
{
    struct FactorialResults results = {{0}, 0};
    int i;
    // computeFactorials(results, NUM_FACTS);//bug-6: call by valur
    computeFactorials(&results, NUM_FACTS);
    for (i = 0; i < NUM_FACTS; i++)
    {
        results.results[i] = reduceFactorial(results.results[i]);
        printf("%5d %12d\n", i, results.results[i]);
    }
    return 0;
}