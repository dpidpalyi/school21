#include "calc.h"

int eval(stack *rpn, double *result, double var) {
  int err = 0;
  double (*const func[])(double a) = {uplus, uminus, ucos,  usin, utan, uacos,
                                      uasin, uatan,  usqrt, uln,  ulog};
  double (*const oper[])(double a, double b) = {usum, usub, umul,
                                                udiv, upow, umod};
  stack *res = init();
  enum type_t type;
  double a, b;
  while (!err && rpn->top) {
    if (rpn->top->type == NUM) {
      pop(rpn, &type, &a);
      push(res, NUM, &a);
    } else if (rpn->top->type == VAR) {
      pop(rpn, &type, &a);
      push(res, NUM, &var);
    } else if (is_func(rpn->top->type) || rpn->top->type == UMINUS ||
               rpn->top->type == UPLUS) {
      if (pop(res, &type, &a))
        err = 1;
      else {
        pop(rpn, &type, NULL);
        a = func[type - 10](a);
        push(res, NUM, &a);
      }
    } else {
      if (pop(res, &type, &b) || pop(res, &type, &a))
        err = 1;
      else {
        pop(rpn, &type, NULL);
        a = oper[type - 4](a, b);
        push(res, NUM, &a);
      }
    }
  }

  if (!err) {
    err = pop(res, &type, result);
    if (err || res->top) err = 1;
  }

  destroy_stack(res);
  free(res);

  return err;
}

double usum(double a, double b) { return a + b; }

double usub(double a, double b) { return a - b; }

double umul(double a, double b) { return a * b; }

double udiv(double a, double b) { return a / b; }

double upow(double a, double b) { return pow(a, b); }

double umod(double a, double b) { return fmod(a, b); }

double uplus(double a) { return a; }

double uminus(double a) { return -a; }

double ucos(double a) { return cos(a); }

double usin(double a) { return sin(a); }

double utan(double a) { return tan(a); }

double uacos(double a) { return acos(a); }

double uasin(double a) { return asin(a); }

double uatan(double a) { return atan(a); }

double usqrt(double a) { return sqrt(a); }

double uln(double a) { return log(a); }

double ulog(double a) { return log10(a); }
