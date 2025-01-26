#include "test_s21_string.h"

#define D 10
#define U 10
#define S 4
#define C 4
#define F 13
#define oxX 3
#define FLOAT 5
#define FMT 5
#define D_FLAG 16
#define U_FLAG 16
#define X_FLAG 25
#define P_FLAG 2
#define F_FLAG 25
#define S_FLAG 2
#define C_FLAG 2
#define PERCENT_FLAG 7
#define N_FLAG 6
#define SPEC 5
#define WIDTH 10
#define LENGTH 3

START_TEST(test_s21_sprintf_spec_di) {
  int d[D] = {0, 1, -1, 100, -100, 999, -1799, 1234567890, INT_MAX, -INT_MAX};
  char flag[D_FLAG][10] = {"",    "0",   "-",   " ",   "+",  "0-",
                           "0 ",  "0+",  "- ",  "-+",  " +", "0- ",
                           "0-+", "0 +", "- +", "0- +"};
  char width[WIDTH][4] = {"", "0", "1", "2", "3", "4", "5", "*", "50", "100"};
  char dot[2][2] = {"", "."};
  char precision[WIDTH][4] = {"",  "0", "1", "2",  "3",
                              "4", "5", "*", "50", "100"};
  char length[LENGTH][2] = {"", "h", "l"};
  char fmt[2][2] = {"d", "i"};
  char want[4096];
  char got[4096];
  char format[20];
  int want_i;
  int got_i;
  int tests = 0;
  for (int i = 0; i < D; i++)
    for (int j = 0; j < D_FLAG; j++)
      for (int k = 0; k < WIDTH; k++)
        for (int l = 0; l < WIDTH; l++)
          for (int m = 0; m < 2; m++)
            for (int o = 0; o < LENGTH; o++)
              for (int p = 0; p < 2; p++) {
                strcpy(format, "%");
                strcat(format, flag[j]);
                strcat(format, width[k]);
                // To evade very big formats like "%5050d", "%100100d" etc.
                if ((k > 6 || l > 6) && m == 0) m++;
                strcat(format, dot[m]);
                strcat(format, precision[l]);
                strcat(format, length[o]);
                strcat(format, fmt[p]);
                tests++;
                if (k == 7 && l == 7) {
                  want_i = sprintf(want, format, i * 4, i * 3, d[i]);
                  got_i = s21_sprintf(got, format, i * 4, i * 3, d[i]);
                } else if (k == 7 || l == 7) {
                  want_i = sprintf(want, format, i * 5, d[i]);
                  got_i = s21_sprintf(got, format, i * 5, d[i]);
                } else {
                  want_i = sprintf(want, format, d[i]);
                  got_i = s21_sprintf(got, format, d[i]);
                }
                ck_assert_msg(
                    !strcmp(want, got) && want_i == got_i,
                    "format = \"%s\", '*' = '%d', '*.*' = '%d.%d', d = \"%d\", "
                    "sprintf returns \"%d\":\"%s\", s21_sprintf returns "
                    "\"%d\":\"%s\"",
                    format, i * 5, i * 4, i * 3, d[i], want_i, want, got_i,
                    got);
              }
  printf("All d, i spec sprintf tests = %d\n", tests);
}
END_TEST

START_TEST(test_s21_sprintf_spec_u) {
  int u[U] = {0, 1, 25, 100, 779, 3999, 50001, 100000, 2345678912, UINT_MAX};
  char flag[U_FLAG][10] = {"",    "0",   "-",   " ",   "+",  "0-",
                           "0 ",  "0+",  "- ",  "-+",  " +", "0- ",
                           "0-+", "0 +", "- +", "0- +"};
  char width[WIDTH][4] = {"", "0", "1", "2", "3", "4", "5", "*", "50", "100"};
  char dot[2][2] = {"", "."};
  char precision[WIDTH][4] = {"",  "0", "1", "2",  "3",
                              "4", "5", "*", "50", "100"};
  char length[LENGTH][2] = {"", "h", "l"};
  char want[4096];
  char got[4096];
  char format[20];
  int want_i;
  int got_i;
  int tests = 0;
  for (int i = 0; i < U; i++)
    for (int j = 0; j < U_FLAG; j++)
      for (int k = 0; k < WIDTH; k++)
        for (int l = 0; l < WIDTH; l++)
          for (int m = 0; m < 2; m++)
            for (int o = 0; o < LENGTH; o++) {
              strcpy(format, "%");
              strcat(format, flag[j]);
              strcat(format, width[k]);
              // To evade very big formats like "%5050u", "%100100u" etc.
              if ((k > 6 || l > 6) && m == 0) m++;
              strcat(format, dot[m]);
              strcat(format, precision[l]);
              strcat(format, length[o]);
              strcat(format, "u");
              tests++;
              if (k == 7 && l == 7) {
                want_i = sprintf(want, format, i * 4, i * 3, u[i]);
                got_i = s21_sprintf(got, format, i * 4, i * 3, u[i]);
              } else if (k == 7 || l == 7) {
                want_i = sprintf(want, format, i * 5, u[i]);
                got_i = s21_sprintf(got, format, i * 5, u[i]);
              } else {
                want_i = sprintf(want, format, u[i]);
                got_i = s21_sprintf(got, format, u[i]);
              }
              ck_assert_msg(
                  !strcmp(want, got) && want_i == got_i,
                  "format = \"%s\", '*' = '%d', '*.*' = '%d.%d', u = "
                  "\"%d\", "
                  "sprintf returns \"%d\":\"%s\", s21_sprintf returns "
                  "\"%d\":\"%s\"",
                  format, i * 5, i * 4, i * 3, u[i], want_i, want, got_i, got);
            }
  printf("All u spec sprintf tests = %d\n", tests);
}
END_TEST

START_TEST(test_s21_sprintf_spec_oxX) {
  int u[U] = {0, 1, 14, 100, 779, 3999, 50001, 100000, 2345678912, UINT_MAX};
  char flag[X_FLAG][10] = {"",    "0",   "-",   " ",   "+",   "#",
                           "0-",  "0 ",  "0+",  "0#",  "- ",  "-+",
                           "-#",  " +",  " #",  "+#",  "0- ", "0-+",
                           "0 +", "- +", "#0-", "#0 ", "#0+", "#0- +"};
  char width[WIDTH][4] = {"", "0", "1", "2", "3", "4", "5", "*", "50", "100"};
  char dot[2][2] = {"", "."};
  char precision[WIDTH][4] = {"",  "0", "1", "2",  "3",
                              "4", "5", "*", "50", "100"};
  char length[LENGTH][2] = {"", "h", "l"};
  char fmt[oxX][2] = {"o", "x", "X"};
  char want[4096];
  char got[4096];
  char format[20];
  int want_i;
  int got_i;
  int tests = 0;
  for (int i = 0; i < U; i++)
    for (int j = 0; j < X_FLAG; j++)
      for (int k = 0; k < WIDTH; k++)
        for (int l = 0; l < WIDTH; l++)
          for (int m = 0; m < 2; m++)
            for (int o = 0; o < LENGTH; o++)
              for (int p = 0; p < oxX; p++) {
                strcpy(format, "%");
                strcat(format, flag[j]);
                strcat(format, width[k]);
                // To evade very big formats like "%5050o", "%100100x" etc.
                if ((k > 6 || l > 6) && m == 0) m++;
                strcat(format, dot[m]);
                strcat(format, precision[l]);
                strcat(format, length[o]);
                strcat(format, fmt[p]);
                tests++;
                if (k == 7 && l == 7) {
                  want_i = sprintf(want, format, i * 4, i * 3, u[i]);
                  got_i = s21_sprintf(got, format, i * 4, i * 3, u[i]);
                } else if (k == 7 || l == 7) {
                  want_i = sprintf(want, format, i * 5, u[i]);
                  got_i = s21_sprintf(got, format, i * 5, u[i]);
                } else {
                  want_i = sprintf(want, format, u[i]);
                  got_i = s21_sprintf(got, format, u[i]);
                }
                ck_assert_msg(
                    !strcmp(want, got) && want_i == got_i,
                    "format = \"%s\", '*' = '%d', '*.*' = '%d.%d', uns = "
                    "\"%d\", "
                    "sprintf returns \"%d\":\"%s\", s21_sprintf returns "
                    "\"%d\":\"%s\"",
                    format, i * 5, i * 4, i * 3, u[i], want_i, want, got_i,
                    got);
              }
  printf("All o, x, X spec sprintf tests = %d\n", tests);
}
END_TEST

START_TEST(test_s21_sprintf_spec_p) {
  int u[U] = {0, 1, 14, 100, 779, 3999, 50001, 100000, 2345678912, UINT_MAX};
  char flag[P_FLAG][10] = {"", "-"};
  char width[WIDTH][4] = {"", "0", "1", "2", "3", "4", "5", "*", "50", "100"};
  char dot[2][2] = {"", "."};
  char precision[WIDTH][4] = {"",  "0", "1", "2",  "3",
                              "4", "5", "*", "50", "100"};
  char length[LENGTH][2] = {"", "h", "l"};
  char want[4096];
  char got[4096];
  char format[20];
  int want_i;
  int got_i;
  int tests = 0;
  for (int i = 0; i < U; i++)
    for (int j = 0; j < P_FLAG; j++)
      for (int k = 0; k < WIDTH; k++)
        for (int l = 0; l < WIDTH; l++)
          for (int m = 0; m < 2; m++)
            for (int o = 0; o < LENGTH; o++) {
              strcpy(format, "%");
              strcat(format, flag[j]);
              strcat(format, width[k]);
              // To evade very big formats like "%5050o", "%100100x" etc.
              if ((k > 6 || l > 6) && m == 0) m++;
              strcat(format, dot[m]);
              strcat(format, precision[l]);
              strcat(format, length[o]);
              strcat(format, "p");
              tests++;
              if (k == 7 && l == 7) {
                want_i = sprintf(want, format, i * 4, i * 3, &u[i]);
                got_i = s21_sprintf(got, format, i * 4, i * 3, &u[i]);
              } else if (k == 7 || l == 7) {
                want_i = sprintf(want, format, i * 5, &u[i]);
                got_i = s21_sprintf(got, format, i * 5, &u[i]);
              } else {
                want_i = sprintf(want, format, &u[i]);
                got_i = s21_sprintf(got, format, &u[i]);
              }
              ck_assert_msg(
                  !strcmp(want, got) && want_i == got_i,
                  "format = \"%s\", '*' = '%d', '*.*' = '%d.%d', ptr = "
                  "\"%p\", "
                  "sprintf returns \"%d\":\"%s\", s21_sprintf returns "
                  "\"%d\":\"%s\"",
                  format, i * 5, i * 4, i * 3, &u[i], want_i, want, got_i, got);
            }
  printf("All p spec sprintf tests = %d\n", tests);
  want_i = sprintf(want, "%p", S21_NULL);
  got_i = s21_sprintf(got, "%p", S21_NULL);
  ck_assert_msg(!strcmp(want, got) && want_i == got_i,
                "format = \"%p\", ptr = "
                "\"%p\", "
                "sprintf returns \"%d\":\"%s\", s21_sprintf returns "
                "\"%d\":\"%s\"",
                format, S21_NULL, want_i, want, got_i, got);
}
END_TEST

START_TEST(test_s21_sprintf_spec_feE_dbl) {
  double f[F] = {0.,
                 2.500000000001,
                 -0.00000004321565356,
                 9.999999999,
                 -0.999999999999,
                 M_PI,
                 5999.49999,
                 100.123456789,
                 0.0000000123456789,
                 12674.4513471512,
                 -123412.31241278694,
                 1234567891234.999999999,
                 -1234567891234.999999999};
  char flag[F_FLAG][10] = {"",    "0",   "-",   " ",   "+",   "#",
                           "0-",  "0 ",  "0+",  "0#",  "- ",  "-+",
                           "-#",  " +",  " #",  "+#",  "0- ", "0-+",
                           "0 +", "- +", "#0-", "#0 ", "#0+", "#0- +"};
  char width[WIDTH][4] = {"", "0", "1", "2", "3", "4", "5", "*", "20", "30"};
  char dot[2][2] = {"", "."};
  char precision[WIDTH][4] = {"", "0", "1", "2", "3", "4", "5", "*", "9", "12"};
  char spec[FLOAT][2] = {"f", "e", "E", "g", "G"};
  // char spec[FLOAT][2] = {"f", "e", "E"};
  char want[4096];
  char got[4096];
  char format[20];
  int want_i;
  int got_i;
  int tests = 0;
  for (int i = 0; i < F; i++)
    for (int j = 0; j < F_FLAG; j++)
      for (int k = 0; k < WIDTH; k++)
        for (int l = 0; l < WIDTH; l++)
          for (int m = 0; m < 2; m++)
            for (int p = 0; p < FLOAT; p++) {
              strcpy(format, "%");
              strcat(format, flag[j]);
              strcat(format, width[k]);
              // To evade very big formats like "%2012f", etc.
              if ((k > 6 || l > 6) && m == 0) m++;
              strcat(format, dot[m]);
              strcat(format, precision[l]);
              strcat(format, spec[p]);
              tests++;
              if (k == 7 && l == 7) {
                want_i = sprintf(want, format, i * 2, i, f[i]);
                got_i = s21_sprintf(got, format, i * 2, i, f[i]);
              } else if (k == 7 || l == 7) {
                want_i = sprintf(want, format, i, f[i]);
                got_i = s21_sprintf(got, format, i, f[i]);
              } else {
                want_i = sprintf(want, format, f[i]);
                got_i = s21_sprintf(got, format, f[i]);
              }
              ck_assert_msg(
                  !strcmp(want, got) && want_i == got_i,
                  "format = \"%s\", '*' = '%d', '*.*' = '%d.%d', float = "
                  "\"%.40lf\", sprintf returns \"%d\":\"%s\", s21_sprintf "
                  "returns "
                  "\"%d\":\"%s\"",
                  format, i * 2, i * 2, i * 2, f[i], want_i, want, got_i, got);
            }
  printf("All f, e, E, g, G(dbl) spec sprintf tests = %d\n", tests);
}
END_TEST

START_TEST(test_s21_sprintf_spec_feE_Ldbl) {
  long double f[F] = {0.,
                      0.000627813483,
                      -0.0004321565356,
                      1.,
                      -1.,
                      M_PI,
                      -M_PI,
                      100.123456789,
                      -100.123456789,
                      12674.4513471512,
                      -123412.31241278694,
                      1234567891234.999999999,
                      -1234567891234.999999999};
  char flag[F_FLAG][10] = {"",    "0",   "-",   " ",   "+",   "#",
                           "0-",  "0 ",  "0+",  "0#",  "- ",  "-+",
                           "-#",  " +",  " #",  "+#",  "0- ", "0-+",
                           "0 +", "- +", "#0-", "#0 ", "#0+", "#0- +"};
  char width[WIDTH][4] = {"", "0", "1", "2", "3", "4", "5", "*", "20", "30"};
  char dot[2][2] = {"", "."};
  char precision[WIDTH][4] = {"", "0", "1", "2", "3", "4", "5", "*", "9", "12"};
  char spec[FLOAT][2] = {"f", "e", "E", "g", "G"};
  // char spec[FLOAT][2] = {"f", "e", "E"};
  char want[4096];
  char got[4096];
  char format[20];
  int want_i;
  int got_i;
  int tests = 0;
  for (int i = 0; i < F; i++)
    for (int j = 0; j < F_FLAG; j++)
      for (int k = 0; k < WIDTH; k++)
        for (int l = 0; l < WIDTH; l++)
          for (int m = 0; m < 2; m++)
            for (int p = 0; p < FLOAT; p++) {
              strcpy(format, "%");
              strcat(format, flag[j]);
              strcat(format, width[k]);
              // To evade very big formats like "%2012f", etc.
              if ((k > 6 || l > 6) && m == 0) m++;
              strcat(format, dot[m]);
              strcat(format, precision[l]);
              strcat(format, "L");
              strcat(format, spec[p]);
              tests++;
              if (k == 7 && l == 7) {
                want_i = sprintf(want, format, i * 2, i, f[i]);
                got_i = s21_sprintf(got, format, i * 2, i, f[i]);
              } else if (k == 7 || l == 7) {
                want_i = sprintf(want, format, i, f[i]);
                got_i = s21_sprintf(got, format, i, f[i]);
              } else {
                want_i = sprintf(want, format, f[i]);
                got_i = s21_sprintf(got, format, f[i]);
              }
              ck_assert_msg(
                  !strcmp(want, got) && want_i == got_i,
                  "format = \"%s\", '*' = '%d', '*.*' = '%d.%d', float = "
                  "\"%.20Lf\", sprintf returns \"%d\":\"%s\", s21_sprintf "
                  "returns "
                  "\"%d\":\"%s\"",
                  format, i * 2, i * 2, i * 2, f[i], want_i, want, got_i, got);
            }
  printf("All f, e, E, g, G(Ldbl) spec sprintf tests = %d\n", tests);
}
END_TEST

START_TEST(test_s21_sprintf_spec_s) {
  char s[S][20] = {"", "H", "Hello", "Hello World!"};
  char flag[S_FLAG][2] = {"", "-"};
  char width[WIDTH][3] = {"", "1", "2", "3", "5", "6", "7", "*", "12", "20"};
  char dot[2][2] = {"", "."};
  char precision[WIDTH][3] = {"",  "1", "2", "3",  "5",
                              "6", "7", "*", "12", "20"};
  char want[4096];
  char got[4096];
  char format[20];
  int want_i = 0;
  int got_i = 0;
  int tests = 0;
  for (int i = 0; i < S; i++)
    for (int j = 0; j < S_FLAG; j++)
      for (int k = 0; k < WIDTH; k++)
        for (int l = 0; l < WIDTH; l++)
          for (int m = 0; m < 2; m++) {
            strcpy(format, "%");
            strcat(format, flag[j]);
            strcat(format, width[k]);
            // To evade very big formats like "%1212s", "%2020s" etc.
            if ((k > 6 || l > 6) && m == 0) m++;
            strcat(format, dot[m]);
            strcat(format, precision[l]);
            strcat(format, "s");
            tests++;
            if (k == 7 && l == 7) {
              want_i = sprintf(want, format, i * 4, i * 3, s[i]);
              got_i = s21_sprintf(got, format, i * 4, i * 3, s[i]);
            } else if (k == 7 || l == 7) {
              want_i = sprintf(want, format, i * 5, s[i]);
              got_i = s21_sprintf(got, format, i * 5, s[i]);
            } else {
              want_i = sprintf(want, format, s[i]);
              got_i = s21_sprintf(got, format, s[i]);
            }
            ck_assert_msg(
                !strcmp(want, got) && want_i == got_i,
                "format = \"%s\", '*' = '%d', '*.*' = '%d.%d', s = \"%s\", "
                "sprintf returns \"%d\":\"%s\", s21_sprintf returns "
                "\"%d\":\"%s\"",
                format, i * 5, i * 4, i * 3, s[i], want_i, want, got_i, got);
          }
  printf("All s spec sprintf tests = %d\n", tests);
}
END_TEST

START_TEST(test_s21_sprintf_spec_c) {
  char c[C] = {'A', '9', '\0', '\n'};
  char flag[C_FLAG][2] = {"", "-"};
  char width[WIDTH][3] = {"", "1", "2", "3", "5", "6", "7", "*", "12", "20"};
  char want[4096];
  char got[4096];
  char format[20];
  int want_i;
  int got_i;
  int tests = 0;
  for (int i = 0; i < C; i++)
    for (int j = 0; j < C_FLAG; j++)
      for (int k = 0; k < WIDTH; k++) {
        strcpy(format, "%");
        strcat(format, flag[j]);
        strcat(format, width[k]);
        strcat(format, "c");
        tests++;
        if (k == 7) {
          want_i = sprintf(want, format, i * 4, c[i]);
          got_i = s21_sprintf(got, format, i * 4, c[i]);
        } else {
          want_i = sprintf(want, format, c[i]);
          got_i = s21_sprintf(got, format, c[i]);
        }
        ck_assert_msg(
            !strcmp(want, got) && want_i == got_i,
            "format = \"%s\", c = \"%d\", '*' = '%d', sprintf "
            "returns \"%d\":\"%s\", s21_sprintf returns \"%d\":\"%s\"",
            format, c[i], i * 4, want_i, want, got_i, got);
      }
  printf("All c spec sprintf tests = %d\n", tests);
}
END_TEST

START_TEST(test_s21_sprintf_spec_percent) {
  char str1[50];
  char str2[50];

  ck_assert_int_eq(sprintf(str1, "%%"), s21_sprintf(str2, "%%"));
  ck_assert_pstr_eq(str1, str2);

  ck_assert_int_eq(sprintf(str1, "%%H"), s21_sprintf(str2, "%%H"));
  ck_assert_pstr_eq(str1, str2);

  ck_assert_int_eq(sprintf(str1, "H%%"), s21_sprintf(str2, "H%%"));
  ck_assert_pstr_eq(str1, str2);

  ck_assert_int_eq(sprintf(str1, "%%Hello world"),
                   s21_sprintf(str2, "%%Hello world"));
  ck_assert_pstr_eq(str1, str2);

  ck_assert_int_eq(sprintf(str1, "Hello %% world"),
                   s21_sprintf(str2, "Hello %% world"));
  ck_assert_pstr_eq(str1, str2);

  ck_assert_int_eq(sprintf(str1, "Hello world%%"),
                   s21_sprintf(str2, "Hello world%%"));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(test_s21_sprintf_spec_n) {
  char want[4096];
  char got[4096];
  int want_i, want_n;
  int got_i, got_n;
  char format[N_FLAG][20] = {
      "%n", "%nH", "H%n", "%nHello world", "Hello %n world", "Hello world%n"};
  int tests = 0;
  for (int i = 0; i < N_FLAG; i++) {
    want_i = sprintf(want, format[i], &want_n);
    got_i = s21_sprintf(got, format[i], &got_n);
    tests++;
    ck_assert_msg(!strcmp(want, got) && want_i == got_i && want_n == got_n,
                  "format = \"%s\", sprintf returns \"%d\":\"%s\", "
                  "s21_sprintf returns \"%d\":\"%s\"",
                  format[i], want_i, want, got_i, got);
  }
  printf("All n spec sprintf tests = %d\n", tests);
}
END_TEST

START_TEST(test_s21_sprintf_spec_all) {
  char s[S][20] = {"", "H", "Hello", "Hello World!"};
  char c[C] = {'A', '9', '\0', '\n'};
  char format[FMT][256] = {"%s%c%%", "%sHi my dear %%, this is char %c",
                           "Hello%s%c! And %% percent!",
                           "%4s%-4cAll letters%%%% at the end",
                           "All letters at the start%-4s%%%5c"};
  char want[4096] = {0};
  char got[4096] = {0};
  int want_i;
  int got_i;
  int tests = 0;
  for (int i = 0; i < S; i++)
    for (int j = 0; j < C; j++)
      for (int k = 0; k < FMT; k++) {
        want_i = sprintf(want, format[k], s[i], c[i]);
        got_i = s21_sprintf(got, format[k], s[i], c[i]);
        tests++;
        ck_assert_msg(
            !strcmp(want, got) && want_i == got_i,
            "format = \"%s\", s = \"%s\", sprintf "
            "returns \"%d\":\"%s\", s21_sprintf returns \"%d\":\"%s\"",
            format[k], s[i], want_i, want, got_i, got);
      }
  printf("All 'integration' spec sprintf tests = %d\n", tests);
}
END_TEST

START_TEST(test_s21_sprintf_all) {
  char str1[50];
  char str2[50];
  char *str3 = "%20.10g\n%-20.5g", *str4 = "%lx HELLO %hx World",
       *str5 = "World: %+-14f&\nhello: %- 18f!", *str6 = "Hello %p World %p",
       *str7 = "%6.5o hello %.23o world";

  double num = -76.756791;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);

  unsigned short num1 = 120;
  long int num2 = 3088675711223344;
  ck_assert_int_eq(sprintf(str1, str4, num2, num1),
                   s21_sprintf(str2, str4, num2, num1));
  ck_assert_pstr_eq(str1, str2);

  double num3 = -657633.33;
  ck_assert_int_eq(sprintf(str1, str5, num3, num3),
                   s21_sprintf(str2, str5, num3, num3));
  ck_assert_pstr_eq(str1, str2);

  char *num4 = "0p111cd223f";
  ck_assert_int_eq(sprintf(str1, str5, num4, num4),
                   s21_sprintf(str2, str5, num4, num4));
  ck_assert_pstr_eq(str1, str2);

  unsigned int num5 = 712;
  unsigned int num6 = 3562;
  ck_assert_int_eq(sprintf(str1, str6, num5, num6),
                   s21_sprintf(str2, str6, num5, num6));
  ck_assert_pstr_eq(str1, str2);

  int num8 = 45;
  int num7 = 999;
  ck_assert_int_eq(sprintf(str1, str7, num7, num8),
                   s21_sprintf(str2, str7, num7, num8));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

Suite *test_s21_sprintf(void) {
  Suite *s = suite_create("===== S21_SPRINTF =====");
  TCase *tc = tcase_create("s21_sprintf_tc");

  tcase_add_test(tc, test_s21_sprintf_spec_di);
  tcase_add_test(tc, test_s21_sprintf_spec_u);
  tcase_add_test(tc, test_s21_sprintf_spec_oxX);
  tcase_add_test(tc, test_s21_sprintf_spec_p);
  tcase_add_test(tc, test_s21_sprintf_spec_feE_dbl);
  tcase_add_test(tc, test_s21_sprintf_spec_feE_Ldbl);
  tcase_add_test(tc, test_s21_sprintf_spec_s);
  tcase_add_test(tc, test_s21_sprintf_spec_c);
  tcase_add_test(tc, test_s21_sprintf_spec_percent);
  tcase_add_test(tc, test_s21_sprintf_spec_n);
  tcase_add_test(tc, test_s21_sprintf_spec_all);
  tcase_add_test(tc, test_s21_sprintf_all);
  suite_add_tcase(s, tc);

  return s;
}
