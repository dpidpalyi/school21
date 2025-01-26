#ifndef S21_MODEL_H
#define S21_MODEL_H

/**
 * @file model.h
 *
 * @brief MVC model to parse math expressions and calculate result
 *
 */

#include <math.h>

#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

namespace s21 {
class Model {
 private:
  /**
   * @tokens[]
   * @brief Stores tokens to parse through math expression
   */
  inline static const std::string tokens[] = {
      "",      // NUM
      "x",     // VAR
      "(",     // OPEN
      ")",     // CLOSE
      "+",     // SUM
      "-",     // SUB
      "*",     // MUL
      "/",     // DIV
      "^",     // POW
      "mod",   // MOD
      "+",     // UPLUS
      "-",     // UMINUS
      "cos",   // COS
      "sin",   // SIN
      "tan",   // TAN
      "acos",  // ACOS
      "asin",  // ASIN
      "atan",  // ATAN
      "sqrt",  // SQRT
      "ln",    // LN
      "log"    // LOG
  };

  /**
   * @priority[]
   * @brief Stores priority of math operators and functions
   */
  inline static const int priority[] = {
      0, 0, 0, 0, 1, 1, 2, 2, 3, 1, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0,
  };

  /**
   * @enum Lexem
   * @brief Enumerate for different lexems in math expression
   */
  enum Lexem {
    NUM,
    VAR,
    OPEN,
    CLOSE,
    SUM,
    SUB,
    MUL,
    DIV,
    POW,
    MOD,
    UPLUS,
    UMINUS,
    COS,
    SIN,
    TAN,
    ACOS,
    ASIN,
    ATAN,
    SQRT,
    LN,
    LOG
  };

  /**
   * @struct Data
   * @brief Structure of the stack or queue element
   */
  struct Data {
    /**
     * @brief Type of the element (NUM, VAR, COS, etc.)
     */
    enum Lexem type = NUM;
    /**
     * @brief Value of the element
     */
    double value = 0;
  };

 public:
  Model() = default;
  ~Model() = default;

  /**
   * @brief Set input parameters
   *
   * @param s math expression to evaluate
   * @param x value of x operand
   */
  void SetInp(const std::string &s, double x) {
    expr = parsed = s;
    rpn = std::queue<Data>();
    stk = std::stack<Data>();
    value = x;
  }

  /**
   * @brief Gets result of math expression
   *
   * @return result
   */
  double GetRes() { return result; }

  /**
   * @brief Gets any error occured during parsing or evaluation
   *
   * @return error
   */
  bool GetErr() { return error; }

  /**
   * @brief Set minimum X value for graph
   *
   * @param x value
   */
  void SetMnX(double x) { min_x = x; }

  /**
   * @brief Set maximum X value for graph
   *
   * @param x value
   */
  void SetMxX(double x) { max_x = x; }

  /**
   * @brief Set minimum Y value for graph
   *
   * @param y value
   */
  void SetMnY(double y) { min_y = y; }

  /**
   * @brief Set maximum Y value for graph
   *
   * @param y value
   */
  void SetMxY(double y) { max_y = y; }

  /**
   * @brief Gets minimum X value for graph
   *
   * @return min_x
   */
  double GetMnX() { return min_x; }

  /**
   * @brief Gets maximum X value for graph
   *
   * @return max_x
   */
  double GetMxX() { return max_x; }

  /**
   * @brief Gets minimum Y value for graph
   *
   * @return min_y
   */
  double GetMnY() { return min_y; }

  /**
   * @brief Gets maximum Y value for graph
   *
   * @return max_y
   */
  double GetMxY() { return max_y; }

  /**
   * @brief Gets x values for graph
   *
   * @return x
   */
  std::vector<double> &GetX() { return x; }

  /**
   * @brief Gets y values for graph
   *
   * @return y
   */
  std::vector<double> &GetY() { return y; }

  /**
   * @brief Parse and then calculates math expression
   *
   * @return error if occured
   */
  bool Calc() {
    if (Parse()) {
      error = true;
      return error;
    }
    return MakeCalc();
  }

  /**
   * @brief Calculates math expression
   *
   * @return error if occured
   */
  bool MakeCalc() {
    error = false;
    Data a, b, temp;
    stk = std::stack<Data>();
    while (!error && !rpn.empty()) {
      if (rpn.front().type == NUM) {
        a = rpn.front();
        rpn.pop();
        stk.push(a);
      } else if (rpn.front().type == VAR) {
        a.type = VAR;
        a.value = value;
        rpn.pop();
        stk.push(a);
      } else if (IsFunc(rpn.front().type) || rpn.front().type == UMINUS ||
                 rpn.front().type == UPLUS) {
        if (stk.empty())
          error = false;
        else {
          a = stk.top();
          stk.pop();
          a.value = func[rpn.front().type - 10](a.value);
          rpn.pop();
          stk.push(a);
        }
      } else {
        if (stk.size() < 2)
          error = true;
        else {
          b = stk.top();
          stk.pop();
          a = stk.top();
          stk.pop();
          temp = rpn.front();
          rpn.pop();
          a.value = oper[temp.type - 4](a.value, b.value);
          stk.push(a);
        }
      }
    }
    if (!error) {
      if (stk.size() != 1)
        error = true;
      else
        result = stk.top().value;
    }

    return error;
  }

  /**
   * @brief Parse and then fill x and y values for graph
   *
   * @return error if occured
   */
  bool FillVect() {
    if (Parse()) {
      error = true;
      return error;
    }
    if (min_x < max_x) {
      std::queue<Data> rpn_cpy;
      for (int i = 0; i < 101; ++i) {
        x[i] = min_x + i * (max_x - min_x) / 100;
        rpn_cpy = rpn;
        value = x[i];
        if (MakeCalc()) {
          return true;
        } else {
          y[i] = result;
        }
        rpn = rpn_cpy;
      }
    } else {
      return true;
    }

    return false;
  }

 private:
  /*
   * @brief Finds next token if exist and stores in curr element or return error
   *
   * @return true if finds next token
   */
  bool GetToken() {
    bool find = false;
    std::istringstream ss1(parsed);
    for (std::size_t i = 1; !find && i < std::size(tokens); ++i) {
      if (parsed.find(tokens[i]) == 0) {
        parsed.erase(0, tokens[i].size());
        curr.type = Lexem(i);
        find = true;
      }
    }
    if (!find) {
      double d;
      std::size_t pos = 0;
      try {
        d = std::stod(parsed, &pos);
      } catch (const std::invalid_argument &) {
        find = false;
        return find;
      } catch (const std::out_of_range &) {
        find = false;
        return find;
      }
      curr.type = NUM;
      curr.value = d;
      parsed = parsed.substr(pos);
      find = true;
    }

    return find;
  }

  /**
   * @brief Parse math expression
   *
   * @return error if occured
   */
  bool Parse() {
    RemoveSpaces();
    if (parsed.size() == 0) return true;
    bool err = false, find = false;
    bool uno = true;
    while (parsed.size() && !err && (find = GetToken())) {
      if (curr.type == NUM || curr.type == VAR) {
        rpn.push(curr);
        uno = false;
      }
      if (IsFunc(curr.type) || curr.type == OPEN) {
        stk.push(curr);
        uno = true;
      }
      if (IsOperator()) {
        EvaluateOperators(uno);
        uno = true;
      }
      if (curr.type == CLOSE) {
        err = EvaluateBrackets();
        uno = false;
      }
    }
    if (!find || IsFunc(curr.type)) {
      err = true;
    } else {
      err = CleanQueue();
    }

    return err;
  }

  /**
   * @brief Checks if Lexem is function
   *
   * @param Lexem to check
   * @return true if function
   */
  bool IsFunc(enum Lexem t) { return t > 11; }

  /**
   * @brief Checks if Lexem is operator
   *
   * @return true if operator
   */
  bool IsOperator() { return curr.type > 3 && curr.type < 12; }

  /**
   * @brief Checks if Lexem is operator
   *
   * @param uno if unary operation occured
   */
  void EvaluateOperators(bool uno) {
    Data temp_data;
    if (uno) {
      if (curr.type == SUM)
        curr.type = UPLUS;
      else if (curr.type == SUB)
        curr.type = UMINUS;
    }
    while (!stk.empty() &&
           (priority[stk.top().type] > priority[curr.type] ||
            ((priority[stk.top().type] == priority[curr.type] && !uno)))) {
      temp_data = stk.top();
      stk.pop();
      rpn.push(temp_data);
    }
    stk.push(curr);
  }

  /**
   * @brief Checks correctness of brackets
   *
   * @return error if occured
   */
  bool EvaluateBrackets() {
    Data temp_data;
    bool err = false;
    while (!stk.empty() && ((temp_data = stk.top()).type != OPEN)) {
      stk.pop();
      rpn.push(temp_data);
    }
    if (stk.empty() || stk.top().type != OPEN) {
      err = true;
    } else {
      stk.pop();
      if (!stk.empty() && IsFunc(stk.top().type)) {
        temp_data = stk.top();
        stk.pop();
        rpn.push(temp_data);
      }
    }

    return err;
  }

  /**
   * @brief Clean queue and stores in stack
   *
   * @return error if unnecessary lexems finds in queue
   */
  bool CleanQueue() {
    bool err = false;
    Data temp_data;
    while (!err && !stk.empty()) {
      if (stk.top().type == OPEN || stk.top().type == CLOSE)
        err = true;
      else {
        temp_data = stk.top();
        stk.pop();
        rpn.push(temp_data);
      }
    }

    return err;
  }

  /**
   * @brief Remove all unnecessary spaces from expression
   */
  void RemoveSpaces() {
    parsed.erase(std::remove_if(std::begin(parsed), std::end(parsed),
                                [l = std::locale{}](auto ch) {
                                  return std::isspace(ch, l);
                                }),
                 std::end(parsed));
  }

  static double usum(double a, double b) { return a + b; }

  static double usub(double a, double b) { return a - b; }

  static double umul(double a, double b) { return a * b; }

  static double udiv(double a, double b) { return a / b; }

  static double upow(double a, double b) { return pow(a, b); }

  static double umod(double a, double b) { return fmod(a, b); }

  static double uplus(double a) { return a; }

  static double uminus(double a) { return -a; }

  static double ucos(double a) { return cos(a); }

  static double usin(double a) { return sin(a); }

  static double utan(double a) { return tan(a); }

  static double uacos(double a) { return acos(a); }

  static double uasin(double a) { return asin(a); }

  static double uatan(double a) { return atan(a); }

  static double usqrt(double a) { return sqrt(a); }

  static double uln(double a) { return log(a); }

  static double ulog(double a) { return log10(a); }

  using func_handler = double (*)(double);
  using oper_handler = double (*)(double, double);

  /**
   * @func[]
   * @brief Stores pointers to functions
   */
  inline static func_handler func[] = {uplus, uminus, ucos,  usin, utan, uacos,
                                       uasin, uatan,  usqrt, uln,  ulog};

  /**
   * @oper[]
   * @brief Stores pointers to operators
   */
  inline static oper_handler oper[] = {usum, usub, umul, udiv, upow, umod};

  /**
   * @queue rpn
   * @brief Stores Data elements in RPN
   */
  std::queue<Data> rpn;
  /**
   * @stack stk
   * @brief Stores Data elements for temporary parsing
   */
  std::stack<Data> stk;
  std::string expr;
  std::string parsed;
  double value = 0;
  double result = 0;
  bool error = false;
  Data curr = {NUM, 0};

  std::vector<double> x = std::vector<double>(101);
  std::vector<double> y = std::vector<double>(101);
  double min_x;
  double max_x;
  double min_y;
  double max_y;
};
};  // namespace s21

#endif  // S21_MODEL_H
