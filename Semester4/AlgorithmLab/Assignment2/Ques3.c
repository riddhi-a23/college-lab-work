#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void matchPattern(char *source, char *pattern)
{
    int n = strlen(source);
    int m = strlen(pattern);
    int found = 0;

    printf("Valid match positions: [ ");
    for (int i = 0; i <= n - m; i++)
    {
        int j;
        for (j = 0; j < m; j++)
        {
            if (pattern[j] != '*' && pattern[j] != source[i + j])
            {
                break;
            }
        }
        if (j == m)
        {
            printf("%d ", i);
            found = 1;
        }
    }
    printf("]\n");

    if (!found)
    {
        printf("No matches found.\n");
    }
}

int main()
{
    char S[1000], P[1000];

    printf("Enter Source String S (only 'c' and 'd'): ");
    scanf("%s", S);

    printf("Enter Pattern String P ('c', 'd', '*'): ");
    scanf("%s", P);

    matchPattern(S, P);

    return 0;
}