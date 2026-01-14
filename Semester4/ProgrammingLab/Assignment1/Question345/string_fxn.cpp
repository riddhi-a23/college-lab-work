#include<iostream>
#include "string_fxn.h"
using namespace std;

int length(char s[])
{
    int l = 0;
    while (s[l] != '\0')
    {
        l++;
    }
    return l;
}
int stringComparison(char s1[], char s2[], int i)
{
    if (s1[i] == '\0' && s2[i] == '\0')
    {
        return 0;
    }
    if (s1[i] == '\0')
    {
        return -1;
    }
    if (s2[i] == '\0')
    {
        return 1;
    }
    if (s1[i] < s2[i])
    {
        return -1;
    }
    if (s1[i] > s2[i])
    {
        return 1;
    }
    return stringComparison(s1, s2, i + 1);
}

bool palindrome(char s[], int n, int i)
{
    if (i >= (n / 2))
    {
        return true;
    }
    if (s[i] == s[n - i - 1])
    {
        return palindrome(s, n, i + 1);
    }
    else
    {
        return false;
    }
}

void replaceChars(char s[], char c1, char c2, int i)
{
    if (s[i] == '\0')
    {
        return;
    }
    if (s[i] == c1)
    {
        s[i] = c2;
    }
    replaceChars(s, c1, c2, i + 1);
}

char lexismallest(char s[], int n)
{
    if (n == 1)
    {
        return s[0];
    }
    char restofLexi = lexismallest(s, n - 1);
    if (s[n - 1] < restofLexi)
    {
        return s[n - 1];
    }
    else
    {
        return restofLexi;
    }
}
