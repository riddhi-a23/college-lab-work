#include <iostream>
#include "recursion.h"
using namespace std;

int main()
{
    int choice;
    do
    {
        cout << "\n----------------------------------------\n";
        cout << "1. String Comparison\n";
        cout << "2. Find Largest in Array\n";
        cout << "3. Search for Integer\n";
        cout << "4. Print Array in Reverse\n";
        cout << "5. Palindrome Check\n";
        cout << "6. Replace Character\n";
        cout << "7. Sum of Array Elements\n";
        cout << "8. Find Smallest Char in String\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        char s1[100], s2[100], ch1, ch2;
        int arr[100], n, target, result;
        switch (choice)
        {
        case 1:
            cout << "Enter first string: ";
            cin >> s1;
            cout << "Enter second string: ";
            cin >> s2;
            result = stringComparison(s1, s2, 0);
            cout << "Result: " << result << endl;
            break;
        case 2:
            cout << "Enter size of array: ";
            cin >> n;
            cout << "Enter elements: ";
            for (int j = 0; j < n; j++)
                cin >> arr[j];
            cout << "Largest: " << largest(arr, n) << endl;
            break;
        case 3:
            cout << "Enter size of array: ";
            cin >> n;
            cout << "Enter elements: ";
            for (int j = 0; j < n; j++)
                cin >> arr[j];
            cout << "Enter number to search: ";
            cin >> target;
            if (search(arr, n, target, 0))
                cout << "Found!" << endl;
            else
                cout << "Not Found." << endl;
            break;
        case 4:
            cout << "Enter size of array: ";
            cin >> n;
            cout << "Enter elements: ";
            for (int j = 0; j < n; j++)
                cin >> arr[j];
            cout << "Reverse: ";
            printReverse(arr, n);
            cout << endl;
            break;
        case 5:
            cout << "Enter string: ";
            cin >> s1;
            if (palindrome(s1, length(s1), 0))
                cout << "It is a Palindrome." << endl;
            else
                cout << "Not a Palindrome." << endl;
            break;
        case 6:
            cout << "Enter string: ";
            cin >> s1;
            cout << "Character to replace: ";
            cin >> ch1;
            cout << "New character: ";
            cin >> ch2;
            replaceChars(s1, ch1, ch2, 0);
            cout << "Modified string: " << s1 << endl;
            break;
        case 7:
            cout << "Enter size of array: ";
            cin >> n;
            cout << "Enter elements: ";
            for (int j = 0; j < n; j++)
                cin >> arr[j];
            cout << "Sum: " << sum(arr, n) << endl;
            break;
        case 8:
            cout << "Enter string: ";
            cin >> s1;
            cout << "Smallest character: " << lexismallest(s1, length(s1)) << endl;
            break;
        case 0:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice! Try again." << endl;
        }
    } while (choice != 0);

    return 0;
}
