# testkit
## Introduction
"testkit" is a easy unit test frame for C. In fact, the unit test frame is a practice about c macro and linux's process management. Therefore, It's features are very small.
## Install
input following command in your shell to install "testkit".
please make sure that shell's work directory is testkit's root directory.
```shell
cmake . -B build &&
cmake --build ./build &&
sudo cmake --install ./build
```
## Usage
"testkit" only have two kinds of unit test macro: expection and assertion,
and only support equal test.
### First
first, you need to set up testkit in your `main()`, as following:
```c
int main(void) {
  /* your code else */
  return run_all_tests();
}
``` 
### Create a test
All test statement must write in TEST() "function". 
```c
// in the out of all functions
TEST(test_suite, test_name) {
  /* Convention: test_suite was
   normally named like Test + function name to test.
   such as: TestAdd 
   test_name is a part in test_suite, it represent a test case.
   such as: base case、edge case and so on
   it's name normally is Base or Edge or your test case else.
   */
}
```
### Expect Macro
the statement in `TEST()` will continue to performan when expected value and actual value are different.
expect have two macro in "testkit"
1. `TEST_EXPECT_EQ_BASE(actual, expected)`
2. `TEST_EXPECT_EQ_LIST(actual, expected, list_length)`
```c
int add(int a, int b) {
  return a + b;
}
TEST(TestAdd, Base) {
  TEST_EXPECT_EQ_BASE(add(5, 8), 13);
  int nums1[] = {1, 3, 5, 8};
  int nums2[] = {1, 4, 6, 1};
  int len = sizeof(nums1) / sizeof(int);
  // here occured a error, but program will continue to performan 
  TEST_EXPECT_EQ_LIST(nums1, nums2, len);
  // will be performaned
  TEST_EXPECT_EQ_BASE(add(13, 5), 18);
}
```
### Assert Macro
the statement in `TEST()` will not continue to performan when expected value and actual value are different.
expect have two macro in "testkit"
1. `TEST_ASSERT_EQ_BASE(actual, expected)`
2. `TEST_ASSERT_EQ_LIST(actual, expected, list_length)`
```c
int add(int a, int b) {
  return a + b;
}
TEST(TestAdd, Base) {
  TEST_EXPECT_EQ_BASE(add(5, 8), 13);
  int nums1[] = {1, 3, 5, 8};
  int nums2[] = {1, 4, 6, 1};
  int len = sizeof(nums1) / sizeof(int);
  // Note that here is a assert.
  TEST_ASSERT_EQ_LIST(nums1, nums2, len);
  // will not be performaned
  TEST_EXPECT_EQ_BASE(add(13, 5), 18);
}
```
