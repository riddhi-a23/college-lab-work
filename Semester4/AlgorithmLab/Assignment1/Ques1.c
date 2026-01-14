#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    int n = 0;
    printf("Enter the value of n:");
    scanf("%d", &n);
    FILE *fp;
    fp = fopen("integers.txt", "w");
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return 0;
    }
    for (int i = 0; i < n; i++)
    {
        int rand_num = rand();
        fprintf(fp, "%d ", rand_num);
    }
    fclose(fp);
    fp = fopen("integers.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return 0;
    }
    int min = RAND_MAX;
    int max = 0;
    int num = 0;
    printf("Reading elements from the file:\n");
    while (fscanf(fp, "%d", &num) != EOF)
    {
        printf("%d ", num);
        if (num > max)
        {
            max = num;
        }
        if (num < min)
        {
            min = num;
        }
    }
    fclose(fp);
    printf("\nMaximum value = %d.\n", max);
    printf("Minimum value = %d.\n", min);

    return 0;
}
