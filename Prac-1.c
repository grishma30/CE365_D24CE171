#include <stdio.h>
#include <string.h>

int main()
{
    char inputString[50];
    int i, countA = 0;

    printf("Enter Input: ");
    scanf("%s", inputString);

    int len = strlen(inputString);

    for (i = 0; i < len && inputString[i] == 'a'; i++)
        countA++;
 
    if (countA <= len - 2 && inputString[len - 2] == 'b'&& inputString[len - 1] == 'b' && countA + 2 == len)
        printf("Valid String");
    else
        printf("Invalid String");

    return 0;
}