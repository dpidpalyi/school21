#include "../s21_string.h"

#define BUFSIZE 256
#define DEC 10
#define OCT 8
#define HEX 16

// Flags and Length fields
typedef struct {
  int hash;
  int zero;
  int minus;
  int space;
  int plus;
  int h;
  int l;
  int L;
  int dot;
  int int_num;
  int hex;
} FL;

// Width or Precision fields
typedef struct {
  int num;
  int star;
} WP;

int s21_sprintf(char *str, const char *format, ...);
int parse(char **str, const char **format, va_list *args);
void parse_flags(const char **format, FL *flags);
void parse_wp(const char **format, va_list *args, FL *flags, WP *wp, int dot);
int s21_atoi(const char *s);
void parse_length(const char **format, FL *flags);
int parse_spec(char **str, const char **format, va_list *args, FL *flags,
               WP *width, WP *precision);
int nums_len(char **str, char *s, FL *flags, WP *width, WP *precision,
             int sign);
int eval_d(char **str, va_list *args, FL *flags, WP *width, WP *precision);
int eval_u(char **str, va_list *args, FL *flags, WP *width, WP *precision,
           int base);
int eval_x(char **str, va_list *args, FL *flags, WP *width, WP *precision,
           char spec);
int s21_dtoa(char *s, long int num, int base);
void s21_itoa(char *s, unsigned long int num, int base);
void s21_xtoa(char *s, unsigned long int num, int low);
void reverse(char *s);
int eval_f(char **str, va_list *args, FL *flags, WP *width, WP *precision);
int eval_eE(char **str, va_list *args, FL *flags, WP *width, WP *precision,
            char spec);
int eval_gG(char **str, va_list *args, FL *flags, WP *width, WP *precision,
            char spec);
int s21_ftoa(long double num, int precision, int *decpt, char *buf, int eflag,
             int gflag, int *e);
void operate_floats(char *buf, char *s, int decpt, WP *precision);
long double find_e(long double *num);
void add_exp(char *s, int e, char spec);
void trim_trail_zeros(char *s);
void trim_lead_zeros(char *s, int precision);
void add_dot(char *s, int hash);
int eval_s(char **str, const char *s, FL *flags, WP *width, WP *precision);
int eval_c(char **str, int c, FL *flags, WP *width);

int s21_sprintf(char *str, const char *format, ...) {
  int res = 0;
  va_list args;
  va_start(args, format);
  for (; *format; format++, str++) {
    *str = '\0';
    if (*format == '%' && *(format + 1) != '\0') {
      format++;
      switch (*format) {
        case '%':
          res++;
          *str = '%';
          break;
        case 'n':
          *va_arg(args, int *) = res;
          str--;
          break;
        default:
          res += parse(&str, &format, &args);
          break;
      }
    } else {
      res++;
      *str = *format;
    }
  }
  *str = '\0';
  va_end(args);

  return res;
}

int parse(char **str, const char **format, va_list *args) {
  int len = 0;
  FL flags = {0};
  WP width = {0};
  WP precision = {0};
  parse_flags(format, &flags);
  parse_wp(format, args, &flags, &width, 0);
  parse_wp(format, args, &flags, &precision, 1);
  if (precision.num < 0) precision.num = 0;
  parse_length(format, &flags);
  len = parse_spec(str, format, args, &flags, &width, &precision);

  return len;
}

void parse_flags(const char **format, FL *flags) {
  int end_of_flags = 1;
  for (; **format && end_of_flags; (*format)++) {
    switch (**format) {
      case '#':
        flags->hash = 1;
        break;
      case '0':
        flags->zero = 1;
        break;
      case '-':
        flags->minus = 1;
        break;
      case ' ':
        flags->space = 1;
        break;
      case '+':
        flags->plus = 1;
        break;
      default:
        end_of_flags = 0;
        (*format)--;
        break;
    }
  }
}

void parse_wp(const char **format, va_list *args, FL *flags, WP *wp, int dot) {
  if (dot && (**format == '.')) {
    (*format)++;
    flags->dot = 1;
  }
  if (flags->dot || !dot) {
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
      wp->num = s21_atoi(s);
    }
  }
}

int s21_atoi(const char *s) {
  int num = 0;
  for (; *s; s++) num = num * 10 + *s - '0';

  return num;
}

void parse_length(const char **format, FL *flags) {
  switch (**format) {
    case 'h':
      flags->h = 1;
      break;
    case 'l':
      flags->l = 1;
      break;
    case 'L':
      flags->L = 1;
      break;
    default:
      (*format)--;
      break;
  }
  (*format)++;
}

int parse_spec(char **str, const char **format, va_list *args, FL *flags,
               WP *width, WP *precision) {
  int len = 0;
  switch (**format) {
    case 'i':
    case 'd':
      flags->int_num = 1;
      len = eval_d(str, args, flags, width, precision);
      break;
    case 'u':
      flags->int_num = 1;
      flags->hash = 0;
      len = eval_u(str, args, flags, width, precision, DEC);
      break;
    case 'o':
      flags->int_num = 1;
      len = eval_u(str, args, flags, width, precision, OCT);
      break;
    case 'x':
    case 'X':
      flags->int_num = 1;
      len = eval_x(str, args, flags, width, precision, **format);
      break;
    case 'f':
      len = eval_f(str, args, flags, width, precision);
      break;
    case 'e':
    case 'E':
      len = eval_eE(str, args, flags, width, precision, **format);
      break;
    case 'g':
    case 'G':
      len = eval_gG(str, args, flags, width, precision, **format);
      break;
    case 's':
      len = eval_s(str, va_arg(*args, char *), flags, width, precision);
      break;
    case 'c':
      len = eval_c(str, va_arg(*args, int), flags, width);
      break;
    case 'p':
      flags->int_num = 1;
      flags->l = 1;
      flags->h = 0;
      flags->hash = 1;
      len = eval_x(str, args, flags, width, precision, 'p');
      break;
  }

  return len;
}

int nums_len(char **str, char *s, FL *flags, WP *width, WP *precision,
             int sign) {
  int len = 0, spaces = 0, left = 0, right = 0, zeros = 0;
  if (flags->minus) flags->zero = 0;
  if (flags->dot && flags->int_num) flags->zero = 1;
  int n = s21_strlen(s);

  char c = ' ';
  if ((flags->plus || flags->space) && !sign) {
    sign++;
    if (flags->plus) c = '+';
  } else
    c = '-';

  if (flags->zero) {
    if (flags->int_num) {
      if (flags->dot) {
        if (precision->num > n) zeros = precision->num - n;
      } else if (width->num > n + sign)
        zeros = width->num - n - sign;
    } else {
      if (width->num > n + sign) zeros = width->num - n - sign;
    }
  }

  if (width->num > sign + zeros + n) spaces = width->num - sign - zeros - n;
  if (flags->minus)
    right = spaces;
  else
    left = spaces;

  s21_memset(*str, ' ', left);
  s21_memset(*str + left, c, sign);
  if (flags->hex) {
    s21_memset(*str + left, '0', 1);
    s21_memset(*str + left + 1, flags->hex, 1);
    *str += 2;
    len += 2;
  }
  s21_memset(*str + left + sign, '0', zeros);
  s21_memcpy(*str + left + sign + zeros, s, n);
  s21_memset(*str + sign + zeros + n, ' ', right);
  *str += spaces + sign + zeros + n - 1;
  len += spaces + sign + zeros + n;

  return len;
}

int eval_d(char **str, va_list *args, FL *flags, WP *width, WP *precision) {
  int sgn = 0;
  char s[BUFSIZE] = "";
  if (flags->h)
    sgn = s21_dtoa(s, (short int)va_arg(*args, int), DEC);
  else if (flags->l)
    sgn = s21_dtoa(s, va_arg(*args, long int), DEC);
  else
    sgn = s21_dtoa(s, va_arg(*args, int), DEC);
  if (flags->dot && precision->num == 0 && !s21_strncmp(s, "0", 2)) s[0] = '\0';

  return nums_len(str, s, flags, width, precision, sgn);
}

int eval_u(char **str, va_list *args, FL *flags, WP *width, WP *precision,
           int base) {
  unsigned long int num;
  if (flags->h)
    num = (short unsigned int)va_arg(*args, int);
  else if (flags->l)
    num = va_arg(*args, unsigned long int);
  else
    num = va_arg(*args, unsigned int);

  char s[BUFSIZE] = "";
  if (flags->dot && precision->num == 0 && num == 0 && !flags->hash)
    s[0] = '\0';
  else {
    char *sp = s;
    if (flags->hash && num != 0) *(sp++) = '0';
    s21_itoa(sp, num, base);
  }
  flags->space = flags->plus = 0;

  return nums_len(str, s, flags, width, precision, 0);
}

int eval_x(char **str, va_list *args, FL *flags, WP *width, WP *precision,
           char spec) {
  unsigned long int num;
  if (flags->h)
    num = (short unsigned int)va_arg(*args, int);
  else if (flags->l)
    num = va_arg(*args, unsigned long int);
  else
    num = va_arg(*args, unsigned int);

  char s[BUFSIZE] = "";
  if (spec == 'p' && num == 0)
    s21_strncat(s, "(nil)", 5);
  else if (flags->dot && precision->num == 0 && num == 0)
    s[0] = '\0';
  else {
    if (spec == 'p') spec = 'x';
    int low = 0;
    if (spec == 'x') low = 32;
    s21_xtoa(s, num, low);
    if (flags->hash && num != 0) {
      flags->hex = spec;
      width->num -= 2;
    }
  }
  flags->space = flags->plus = 0;

  return nums_len(str, s, flags, width, precision, 0);
}

int s21_dtoa(char *s, long int num, int base) {
  long int sign;
  if ((sign = num) < 0) num = -num;
  s21_itoa(s, num, base);

  return sign < 0;
}

void s21_itoa(char *s, unsigned long int num, int base) {
  s21_size_t i = 0;
  do {
    s[i++] = num % base + '0';
  } while ((num /= base) > 0);
  s[i] = '\0';
  reverse(s);
}

void s21_xtoa(char *s, unsigned long int num, int low) {
  s21_size_t i = 0;
  unsigned long int div;
  do {
    div = num % HEX;
    switch (div) {
      case 0:
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
      case 6:
      case 7:
      case 8:
      case 9:
        s[i++] = div + '0';
        break;
      case 10:
        s[i++] = 'A' + low;
        break;
      case 11:
        s[i++] = 'B' + low;
        break;
      case 12:
        s[i++] = 'C' + low;
        break;
      case 13:
        s[i++] = 'D' + low;
        break;
      case 14:
        s[i++] = 'E' + low;
        break;
      case 15:
        s[i++] = 'F' + low;
        break;
    }
  } while ((num /= HEX) > 0);
  s[i] = '\0';
  reverse(s);
}

void reverse(char *s) {
  int i = 0, j = s21_strlen(s) - 1;
  char c;
  for (; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

int eval_f(char **str, va_list *args, FL *flags, WP *width, WP *precision) {
  int sgn = 0, e = 0, decpt;
  long double num;

  if (flags->L)
    num = va_arg(*args, long double);
  else
    num = va_arg(*args, double);

  if (flags->dot) {
    if (width->num == 0 && !precision->num) precision->num = 0;
  } else
    precision->num = 6;

  char buf[BUFSIZE] = "";
  char s[BUFSIZE] = "";
  sgn = s21_ftoa(num, precision->num, &decpt, buf, 0, 0, &e);

  operate_floats(buf, s, decpt, precision);
  add_dot(s, flags->hash);

  return nums_len(str, s, flags, width, precision, sgn);
}

int eval_eE(char **str, va_list *args, FL *flags, WP *width, WP *precision,
            char spec) {
  int sgn = 0, e = 0, decpt;
  long double num;

  if (flags->L)
    num = va_arg(*args, long double);
  else
    num = va_arg(*args, double);

  if (num < 0) {
    num = -num;
    sgn++;
  }
  e = find_e(&num);

  if (flags->dot) {
    if (width->num == 0 && !precision->num) precision->num = 0;
  } else
    precision->num = 6;

  char buf[BUFSIZE] = "";
  char s[BUFSIZE] = "";
  s21_ftoa(num, precision->num, &decpt, buf, 1, 0, &e);

  operate_floats(buf, s, decpt, precision);
  add_dot(s, flags->hash);
  add_exp(s, e, spec);

  return nums_len(str, s, flags, width, precision, sgn);
}

int eval_gG(char **str, va_list *args, FL *flags, WP *width, WP *precision,
            char spec) {
  int sgn = 0, e = 0, decpt;
  long double num;
  if (flags->L)
    num = va_arg(*args, long double);
  else
    num = va_arg(*args, double);

  char buf[BUFSIZE] = "";
  char s[BUFSIZE] = "";
  if (!flags->hash && num == 0.) {
    s[0] = '0';
  } else {
    if (flags->dot) {
      if (precision->num == 0) precision->num = 1;
    } else
      precision->num = 6;
    if (num < 0) {
      num = -num;
      sgn++;
    }
    long double temp = num;
    if (temp > 1)
      temp = roundl(num * powl(10, precision->num)) / powl(10, precision->num);
    e = find_e(&temp);

    if (e >= -4 && e < precision->num) {
      if (precision->num && num == 0.) precision->num--;
      s21_ftoa(num, precision->num, &decpt, buf, 0, 1, &e);

      operate_floats(buf, s, decpt, precision);
      if (!flags->hash && s21_strchr(s, '.'))
        trim_trail_zeros(s);
      else
        trim_lead_zeros(s, precision->num);
      add_dot(s, flags->hash);
    } else {
      num = temp;
      s21_ftoa(num, precision->num, &decpt, buf, 1, 1, &e);

      operate_floats(buf, s, decpt, precision);
      if (!flags->hash) {
        trim_trail_zeros(s);
      }
      add_dot(s, flags->hash);
      add_exp(s, e, spec);
    }
  }

  return nums_len(str, s, flags, width, precision, sgn);
}

int s21_ftoa(long double num, int precision, int *decpt, char *buf, int eflag,
             int gflag, int *e) {
  int r2 = 0, sign = 0;
  long double fi, fj;
  char *p = &buf[0], *p1 = &buf[BUFSIZE];

  if (precision < 0) precision = 0;
  if (precision >= BUFSIZE - 1) precision = BUFSIZE - 2;
  if (num < 0) {
    sign = 1;
    num = -num;
  }
  num = modfl(num, &fi);
  if (fi != 0) {
    while (fi != 0) {
      fj = modfl(fi / 10, &fi);
      *--p1 = (int)((fj + .03) * 10) + '0';
      r2++;
    }
    while (p1 < &buf[BUFSIZE]) *p++ = *p1++;
  } else if (num > 0) {
    while ((fj = num * 10) < 1) {
      num = fj;
      r2--;
      if (eflag) precision++;
    }
  }
  *decpt = r2;
  p1 = &buf[precision];
  if (gflag == 0) p1 += r2;
  if (p1 < &buf[0]) {
    buf[0] = '\0';
  } else {
    while (p <= p1 && p < &buf[BUFSIZE]) {
      num *= 10;
      num = modfl(num, &fj);
      *p++ = (int)fj + '0';
    }
    if (p1 >= &buf[BUFSIZE]) {
      buf[BUFSIZE - 1] = '\0';
    } else {
      p = p1;
      *p1 += 5;
      while (*p1 > '9') {
        *p1 = '0';
        if (p1 > buf) {
          ++*--p1;
        } else {
          *p1 = '1';
          if (eflag == 0) {
            (*decpt)++;
            if (p > buf) *p = '0';
            p++;
          } else
            (*e)++;
        }
      }
      *p = '\0';
    }
  }
  return sign;
}

void operate_floats(char *buf, char *s, int decpt, WP *precision) {
  char *sp = s;
  char *bf = buf;
  if (decpt > 0) {
    for (; *bf; bf++, sp++, --decpt) {
      if (decpt == 0) *sp++ = '.';
      *sp = *bf;
    }
  } else {
    *sp++ = '0';
    if (*bf) {
      *sp++ = '.';
      for (; decpt < 0; sp++, decpt++) *sp = '0';
      for (; *bf; sp++, bf++) *sp = *bf;
    } else if (precision->num) {
      *sp++ = '.';
      for (; precision->num; precision->num--) *sp++ = '0';
    }
  }
}

long double find_e(long double *num) {
  long double e = 0;
  if (*num > 1) {
    while (*num / 10 >= 1) {
      *num /= 10;
      e++;
    }
  } else if (*num > 1e-12) {
    while (*num < 1) {
      *num *= 10;
      e--;
    }
  }

  return e;
}

void add_exp(char *s, int e, char spec) {
  int n = s21_strlen(s);
  if (spec == 'g' || spec == 'e')
    s[n++] = 'e';
  else
    s[n++] = 'E';
  if (e < 0) {
    s[n++] = '-';
    e = -e;
  } else
    s[n++] = '+';
  if (e > 9) {
    char b[BUFSIZE] = "";
    s21_itoa(b, e, DEC);
    for (char *bp = b; *bp; bp++) s[n++] = *bp;
  } else {
    s[n++] = '0';
    s[n++] = e + '0';
  }
}

void trim_trail_zeros(char *s) {
  for (int i = s21_strlen(s) - 1; i > 0; i--) {
    if (s[i] != '0') {
      if (s[i] == '.') s[i] = '\0';
      break;
    }
    s[i] = '\0';
  }
}

void trim_lead_zeros(char *s, int precision) {
  int n = s21_strlen(s);
  int i = 0;
  for (; i < n; i++) {
    if (s[i] != '0' && s[i] != '.') break;
  }
  for (int len = precision; i < n && len > 0; i++) {
    if (s[i] != '.') len--;
  }
  s[i] = '\0';
  s[i + 1] = '\0';
}

void add_dot(char *s, int hash) {
  int n = s21_strlen(s);
  if (hash && !s21_strchr(s, '.')) s[n] = '.';
}

int eval_s(char **str, const char *s, FL *flags, WP *width, WP *precision) {
  int len = 0, spaces = 0, left = 0, right = 0;
  int n = s21_strlen(s);
  if (flags->dot && precision->num < n) n = precision->num;
  if (width->num > n) spaces = width->num - n;
  if (flags->minus)
    right = spaces;
  else
    left = spaces;
  s21_memset(*str, ' ', left);
  s21_memcpy(*str + left, s, n);
  s21_memset(*str + n, ' ', right);
  // Move pointer -1 cause of str++ in main func
  *str += spaces + n - 1;
  len = spaces + n;

  return len;
}

int eval_c(char **str, int c, FL *flags, WP *width) {
  int len = 0, spaces = 0, left = 0, right = 0;
  if (width->num) spaces = width->num - 1;
  if (flags->minus)
    right = spaces;
  else
    left = spaces;
  s21_memset(*str, ' ', left);
  s21_memset(*str + left, c, 1);
  s21_memset(*str + 1, ' ', right);
  *str += spaces;
  len = spaces + 1;

  return len;
}
