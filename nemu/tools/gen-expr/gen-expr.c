#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

#define random(x) (rand()%x)

// this should be enough
static char buf[65536] = "";

int random_prob() {
  int a[10] = {0, 0, 0, 1, 1, 2, 2, 2, 2, 2};
  int k = random(10);
  return a[k];
}

static inline void gen_rand_op() {
  switch (random(4)) {
    case 0: { strcat(buf, "+"); break; }
    case 1: { strcat(buf, "-"); break; }
    case 2: { strcat(buf, "*"); break; }
    case 3: { strcat(buf, "/"); break; }
    default: assert(0);
  }
}

static int sign = 0;
static inline void gen_rand_expr() {
  int opt = random_prob();
  if (sign > 50) opt = 0;
  sign++;
  switch (opt) {
    case 0: {
      char s[4];
      int a = random(100);
      while (a == 0) {
        a = random(100);
      }
      sprintf(s, "%d", a);
      strcat(buf, s);
      break;
    }
    case 1: {
      strcat(buf, "(");
      gen_rand_expr();
      strcat(buf, ")");
      break;
    }
    default: {
      gen_rand_expr();
      gen_rand_op();
      gen_rand_expr();
      break;
    }
  }
}

static char code_buf[65536];
static char *code_format =
"#include <stdio.h>\n"
"int main() { "
"  unsigned result = %s; "
"  printf(\"%%u\", result); "
"  return 0; "
"}";

int main(int argc, char *argv[]) {
  srand((unsigned)time(NULL));
  int loop = 1;
  if (argc > 1) {
    sscanf(argv[1], "%d", &loop);
  }
  int i;
  for (i = 0; i < loop; i++) {
    memset(buf, 0, sizeof(buf));
    gen_rand_expr();

    sprintf(code_buf, code_format, buf);

    FILE *fp = fopen("/tmp/.code.c", "w");
    assert(fp != NULL);
    fputs(code_buf, fp);
    fclose(fp);

    int ret = system("gcc /tmp/.code.c -o /tmp/.expr");
    if (ret != 0) continue;

    fp = popen("/tmp/.expr", "r");
    assert(fp != NULL);

    int result;
    ret = fscanf(fp, "%d", &result);
    assert(ret >= 0);
    pclose(fp);
    if (result != atoi(buf))
      printf("%u %s\n",result, buf);
  }
  return 0;
}
