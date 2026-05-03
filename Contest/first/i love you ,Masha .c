#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main() {
    char inputLine[100000];
    fgets(inputLine, sizeof(inputLine), stdin);
    inputLine[strcspn(inputLine, "\n")] = '\0'; // убрать \n

    int i = 0, j = 0, n = strlen(inputLine);
    while (i < n) {
        if (tolower(inputLine[i]) >= 'a' && tolower(inputLine[i]) <= 'z') {
            j = i;
            while (j < n && tolower(inputLine[j]) >= 'a' && tolower(inputLine[j]) <= 'z') {
                j++;
            }
            int left = i, right = j - 1;
            while (left < right) {
                char temp = inputLine[left];
                inputLine[left] = inputLine[right];
                inputLine[right] = temp;
                left++;
                right--;
            }
            i = j;
        } else {
            i++;
        }
    }
    printf("%s\n", inputLine);
}
