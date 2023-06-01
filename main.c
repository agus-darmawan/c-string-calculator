#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int it = 0;
char getnonspacechar() {
  char c;
  while ((c = getchar()) == ' ');
  return c;
}
void consume(char c) {
  if (getnonspacechar() != c) {
    printf("expected '%c'\n", c);
    exit(-1);
  }
}
int calc_3(void);
int calc_0() {
  char top = getnonspacechar();
  if (top == '(') {
    int result = calc_3();
    consume(')');
    return result;
  } else {
    int i;
    static char buf[64];
    buf[0] = top;
    for (i = 1; i < 64; i++) {
      buf[i] = getchar();
      if (!isalnum(buf[i])) {
        ungetc(buf[i], stdin);
        buf[i] = '\0';
        break;
      }
    }
    buf[63] = '\0';
    if (isdigit(buf[0]) || buf[0] == '+' || buf[0] == '-') {
      return atoi(buf);
    } else if (!strncmp(buf, "it", i)) {
      return it;
    } else if (!strncmp(buf, "abs", i)) {
      consume('(');
      int arg1 = calc_3();
      consume(')');
      return abs(arg1);
    } else if (!strncmp(buf, "rand", i)) {

      consume('(');
      int arg1 = calc_3();
      consume(')');
      return rand() % arg1;
    }
    printf("Masukan Salah : %s\n", buf);
    exit(-1);
  }
}
int calc_1() {
  int result = calc_0();
  char op = getnonspacechar();
  if (op == '^') {
    return pow((double) result, (double) calc_1());
  } else {
    ungetc(op, stdin);
    return result;
  }
}
int calc_2() {
  int result = calc_1();
  while (1) {
    char op = getnonspacechar();
    switch (op) {
    case '*':
      result *= calc_1();
      break;
    case '/':
      result /= calc_1();
      break;
    default:
      ungetc(op, stdin);
      return result;
    }
  }
}
int calc_3() {
  int result = calc_2();
  while (1) {
    char op = getnonspacechar();
    switch (op) {
    case '+':
      result += calc_2();
      break;
    case '-':
      result -= calc_2();
      break;
    default:
      ungetc(op, stdin);
      return result;

    }
  }
}
int main(int argc, char * argv[]) {
  srand((unsigned int) time(NULL));
  while (1) {
    printf("Masukan angka : ");
    printf("Hasil : %d\n", (it = calc_3()));
    while (getchar() != '\n');
  }
  return 0;
}
