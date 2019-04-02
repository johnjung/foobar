#include <stdio.h>

int main() {
  char i = 1;
  while (i <= 100) {
    if (i % 15 == 0) {
      printf("foobar\n");
    } else if (i % 5 == 0) {
      printf("bar\n");
    } else if (i % 3 == 0) {
      printf("foo\n");
    } else {
      printf("%d\n", i);
    }
    i++;
  }
  return 0;
}
