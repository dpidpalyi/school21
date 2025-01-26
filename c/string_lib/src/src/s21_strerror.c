#include "s21_strerror.h"

char *s21_strerror(int errnum) {
  static char res[50];
  static const char *err_array[] = s21_error;
  if (errnum >= 0 && errnum < STR_N) {
    s21_sprintf(res, "%s", err_array[errnum]);
  } else if (errnum < 0 || errnum >= STR_N) {
#ifdef __APPLE__
    s21_sprintf(res, "Unknown error: %d", errnum);
#elif __linux__
    s21_sprintf(res, "Unknown error %d", errnum);
#endif
  }
  return res;
}
