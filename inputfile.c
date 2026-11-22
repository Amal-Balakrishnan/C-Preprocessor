#include <stdio.h>
#include "myheader.h"

#define PI 3.14
#define MAX 100
#define MIN 10
#define SQUARE(x) ((x) * (x))
#define CUBE(x) ((x) * (x) * (x))

// Function to calculate area of circle

float area(float radius)
{
    return PI * radius * radius;
}

/* Main function
starts here */

int main()
{
    int a = 10;
    int b = 20;

    int sum = add(a, b);
    int product = multiply(a, b);

    int square = SQUARE(5);
    int cube = CUBE(3);

    float radius = 5.0;
    float circle_area = area(radius);

    printf("Sum = %d\n", sum);
    printf("Product = %d\n", product);

    printf("Square = %d\n", square);
    printf("Cube = %d\n", cube);

    printf("Circle Area = %f\n", circle_area);

    if(sum > MIN)
    {
        printf("Sum is greater than minimum\n");
    }

    if(product < MAX)
    {
        printf("Product is less than maximum\n");
    }

    display_message();

    return 0;
}
