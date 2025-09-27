/* 
   demo.c
   this is a demo for usage of testkit.
*/
#include "testkit.h"
#include <stdbool.h>

void bubble_sort(int arr[], int len) {
  bool flag;
  for (int i = 0;i < len - 1;++i) {
    flag = true;
    for (int j = 0; j < len - 1 - i;++j) {
      if (arr[j] > arr[j + 1]) {
        int temp = arr[j];
        arr[j]  = arr[j + 1];
        arr[j + 1] = temp;
        flag = false;
      }
    }
    if (flag) { break; }
  }
}

void print_nums(int arr[], int len) {
  for (int i = 0;i < len;++i) {
    printf("%d ", arr[i]);
  }
  putchar('\n');
}

TEST(BubbleSortTest, Base) {
  int arr[] = {4, 5, 1, 6, 4};
  int len = sizeof(arr) / sizeof(int);
  int expected[] = {1, 4, 4, 5, 7};
  bubble_sort(arr, len);
  char *str1 = "abc";
  TEST_ASSERT_EQ_BASE(str1, "abcd");
  TEST_EXPECT_EQ_LIST(arr, expected, len);
}

int main(void) {

  return run_all_tests();
} 
