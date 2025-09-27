#ifndef __TEST_KIT_H__
#define __TEST_KIT_H__
#define MAX_TEST_NUM 128
#include <stdio.h>
#include <string.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

struct TestCase {
  const char *suite;
  const char *name;
  void (*test_func)(int *soft_failed);
};

#ifndef EXTERN_
extern struct TestCase tests[MAX_TEST_NUM];
extern int test_count;
#else 
struct TestCase tests[MAX_TEST_NUM];
int test_count;
#endif

#define _CMP_BASE(a, b) \
  _Generic((a), \
    char*: strcmp((char*)(a), (char*)(b)) != 0, \
    const char*: strcmp((const char*)(a), (const char*)(b)) != 0, \
    default: ((a) != (b)))

bool _cmp_byte(void *a, void *b, int len, int elem_size);

#define _PRINT_NUMS(nums, len) \
  do { \
    for (int i = 0;i < len;++i) {\
      printf(_Generic((nums), \
      int*: "%d", \
      double*: "%.2lf", \
      float*: "%.2lf"), nums[i]);\
      if (i != len - 1) {\
        printf(" ,");\
      }\
    }\
 } while(0)

#define _PRINT_LIST_ERROR(actual, expected, line, len) \
  do {\
    char fmt[64] = "[FAIL] %s:%d Expected {"; \
    printf(fmt, __FILE__, line); \
    _PRINT_NUMS(expected, len);\
    printf("} got {");\
    _PRINT_NUMS(actual, len);\
    printf("}\n");\
  } while(0)

#define _PRINT_BASE_ERROR(actual, expected, line) \
  do { \
    printf("[FAIL] %s:%d Expected ", __FILE__, line); \
    const char *fmt = _Generic((actual), \
        char*: "\"%s\", but got \"%s\"\n", \
        const char*: "\"%s\", but got \"%s\"\n", \
        double: "%.2lf, but got %.2lf\n", \
        float: "%.2f, but got %.2f\n", \
        char: "%c, but got %c\n", \
        default: "%d, but got %d\n"); \
   printf(fmt, expected, actual);\
  } while (0)
  
#define _TEST_EXPECT_EQ_BASE(actual, expected, line) \
  do { \
    if (_CMP_BASE(actual, expected)) { \
      _PRINT_BASE_ERROR(actual, expected, line); \
      *soft_failed = 1; \
    } \
  } while(0) 

#define _TEST_EXPECT_EQ_LIST(actual, expected, len, line) \
  do { \
    if (_cmp_byte(actual, expected, len, sizeof(*actual))) { \
      _PRINT_LIST_ERROR(actual, expected, line, len); \
      *soft_failed = 1; \
    } \
  } while(0) 


#define _TEST_ASSERT_EQ_LIST(actual, expected, len, line) \
  do { \
    if (_cmp_byte(actual, expected, len, sizeof(*actual))) { \
      _PRINT_LIST_ERROR(actual, expected, line, len); \
      exit(1); \
    } \
  } while(0) 

#define _TEST_ASSERT_EQ_BASE(actual, expected, line) \
  do { \
    if (_CMP_BASE(actual, expected)) { \
      _PRINT_BASE_ERROR(actual, expected, line); \
      exit(1); \
    } \
  } while(0) 

#define TEST_EXPECT_EQ_BASE(actual, expected) \
  _TEST_EXPECT_EQ_BASE(actual, expected, __LINE__)

#define TEST_EXPECT_EQ_LIST(actual, expected, len) \
  _TEST_EXPECT_EQ_LIST(actual, expected, len, __LINE__)

#define TEST_ASSERT_EQ_BASE(actual, expected) \
  _TEST_ASSERT_EQ_BASE(actual, expected, __LINE__)

#define TEST_ASSERT_EQ_LIST(actual, expected, len) \
  _TEST_ASSERT_EQ_LIST(actual, expected, len, __LINE__)

#define TEST(suite_name, test_name) \
    static void suite_name##test_name##_test(int *); \
    __attribute__((constructor)) \
    static void suite_name##test_name##_register() { \
      if (test_count >= MAX_TEST_NUM) { \
          printf("too many tests was registered\n"); \
      } \
      tests[test_count].name = #test_name; \
      tests[test_count].suite = #suite_name; \
      tests[test_count++].test_func = suite_name##test_name##_test; \
    } \
    static void suite_name##test_name##_test(int *soft_failed) 


int run_all_tests(void);

#endif
