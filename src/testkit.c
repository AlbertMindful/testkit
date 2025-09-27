#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>
#define EXTERN_
#include "testkit.h"

int run_all_tests() {
  printf("running %d tests...\n", test_count);
  int passed = 0;
  for (int i = 0; i < test_count; ++i) {
    printf("[ RUN      ] %s.%s\n", tests[i].suite, tests[i].name);
    pid_t pid = fork();
    if (pid == 0) {
      int soft_failed = 0;
      tests[i].test_func(&soft_failed);
      exit(soft_failed);
    } else {
      int status;
      waitpid(pid, &status, 0);
      if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        printf("[       OK ] %s.%s\n", tests[i].suite, tests[i].name);
        passed++;
      } else {
        printf("[  FAILED  ] %s.%s\n", tests[i].suite, tests[i].name);
      }
    }
  }

  printf("\nResults: %d/%d tests passed\n", passed, test_count);
  if (passed == test_count) {
    printf("all tests passed\n");
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

bool _cmp_byte(void *a, void *b, int len, int elem_size) {
  char *ta = a;
  char *tb = b;
  for (int i = 0;i < len * elem_size;++i) {
    if (ta[i] != tb[i]) {
      return true;
    }
  }
  return false;
}