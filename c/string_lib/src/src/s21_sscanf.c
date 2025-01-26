#include <stdio.h>

#include "../s21_string.h"

#define BUFSIZE 256

typedef struct {
  int h;
  int l;
  int L;
  int dot;
} FL;

typedef struct {
  int num;
  int star;
} WP;

int eval_c_sscanf(const char **str, WP *width, va_list *args) {
  int len = 0, spaces = 0;
  if (width->num == 0)
    spaces = width->num;
  else
    spaces = width->num - 1;
  char *temp = (char *)va_arg(*args, int *);
  *temp = **str;
  *str += spaces;
  if (width->star)
    len = 0;
  else
    len = 1;
  return len;
}

int parse_sscanf_spec_sscanf(const char **str, const char **format,
                             va_list *args, WP *width) {
  int len = 0;
  switch (**format) {
    case 'c':
      len = eval_c_sscanf(str, width, args);
      break;
  }
  return len;
}

void parse_sscanf_length_sscanf(const char **format, FL *length) {
  switch (**format) {
    case 'h':
      length->h = 1;
      break;
    case 'l':
      length->l = 1;
      break;
    case 'L':
      length->L = 1;
      break;
    default:
      (*format)--;
      break;
  }
  (*format)++;
}

int s21_atoi_sscanf(const char *s) {
  int num = 0;
  for (; *s; s++) num = num * 10 + *s - '0';
  return num;
}

void parse_sscanf_wp_sscanf(const char **format, va_list *args, FL *dots,
                            WP *wp, int dot) {
  if (dot && (**format == '.')) {
    (*format)++;
    dots->dot = 1;
  }
  if (dots->dot || !dot) {
    if (**format == '*') {
      wp->num = va_arg(*args, int);
      wp->star = 1;
      (*format)++;
    } else if (s21_strchr("0123456789", **format)) {
      char s[BUFSIZE] = "";
      int i = 0;
      for (; **format && i < BUFSIZE && s21_strchr("0123456789", **format);
           i++, (*format)++) {
        s[i] = **format;
      }
      s[i] = '\0';
      wp->num = s21_atoi_sscanf(s);
    }
  }
}

int parse_sscanf(const char **str, const char **format, va_list *args) {
  int len = 0;
  FL flags = {0};
  WP width = {0};
  WP precision = {0};
  parse_sscanf_wp_sscanf(format, args, &flags, &width, 0);
  parse_sscanf_wp_sscanf(format, args, &flags, &precision, 1);
  if (precision.num < 0) precision.num = 0;
  parse_sscanf_length_sscanf(format, &flags);
  len = parse_sscanf_spec_sscanf(str, format, args, &width);
  return len;
}

int s21_sscanf(const char *str, const char *format, ...) {
  int res = 0, count = 0;
  va_list args;
  va_start(args, format);
  for (; *format && *str; format++, str++) {
    count++;
    if (*format == '%' && *str != *format) {
      if ((*str == '\n' || *str == '\t' || *str == ' ')) {
        if (count != 1 && (*(format - 1) == ' ' || *(format - 1) == '\t' ||
                           *(format - 1) == '\n'))
          format--;
        else {
          format++;
          res += parse_sscanf(&str, &format, &args);
        }
      } else {
        format++;
        res += parse_sscanf(&str, &format, &args);
      }
    } else if ((*format == ' ' || *format == '\t' || *format == '\n') &&
               *str != *format) {
      if ((*str == '\n' || *str == '\t' || *str == ' ')) {
      } else {
        str--;
      }
    }
  }
  va_end(args);
  return res;
}
