// Yingge He
// 1560733
// heyingge@uw.edu
// "Copyright [2018] <Yingge He>"  [legal/copyright]
#include <stdio.h>
#include <inttypes.h>
#define LENGTH 11

void CopyAndSort(int32_t n1[], int32_t n2[], uint32_t length);
void PrintResult(int32_t n2[], uint32_t length);


int main() {
  int32_t n1[] = {3, 2, -5, 7, 13, 4, 1, 7, 8, -8, 6};
  int32_t n2[LENGTH];
  if (n1 == NULL) {
    printf("Invalid Array\n");
  } else if (LENGTH < 0) {
    printf("Invalid Length\n");
  } else {
    CopyAndSort(n1, n2, LENGTH);
    PrintResult(n2, LENGTH);
  }
}

void CopyAndSort(int32_t n1[], int32_t n2[], uint32_t length) {
  n2[0] = n1[0];
  for (int i = 1; i < length; i++) {
    int32_t curr = n1[i];

    int index = i;
    for (int j = 0; j < i; j++) {
      if (n2[j] > curr) {
        index = j;
        break;
      }
    }
    for (int j = i; j > index; j--)
      n2[j] = n2[j - 1];
    n2[index] = curr;
  }
}

void PrintResult(int32_t n2[], uint32_t length) {
  for (int i = 0; i < length; i++)
    printf("%" PRId32 " ", n2[i]);
  printf("\n");
}
