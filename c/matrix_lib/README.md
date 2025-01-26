# matrix_lib

Реализация библиотеки для обработки числовых матриц.

- Программа разработана на языке Си стандарта C11 с использованием компилятора gcc
- Программа разработана в соответствии с принципами структурного программирования
- Код написан с использованием Google Style
- Подготовлено полное покрытие unit-тестами c помощью библиотеки Check

### Информация:

Матрица - это набор чисел, расположенных в фиксированном количестве строк и столбцов.
Матрица A - прямоугольная таблица чисел, расположенных в `m` строках и `n` столбцах:

```
    1 2 3
A = 4 5 6
    7 8 9
```

### Структура матрицы на языке C:

```c
typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;
```

### Реализованы следующие функции:

| № | Функция | Описание |
| ------ | ------ | ------ |
| 1 | `int create_matrix(int rows, int columns, matrix_t *result)` | Создание матриц. |
| 2 | `void remove_matrix(matrix_t *A)` | Очистка матриц. |
| 3 | `int eq_matrix(matrix_t *A, matrix_t *B)` | Сравнение матриц. |
| 4 | `int sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result)` | Сложение матриц. |
| 5	| `int sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result)` | Вычитание матриц. |
| 6 | `int mult_number(matrix_t *A, double number, matrix_t *result)` | Умножение матрицы на число. |
| 7 | `int mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result)` | Умножение двух матриц. |
| 8 | `int transpose(matrix_t *A, matrix_t *result)` | Транспонирование матрицы. |
| 9 | `int calc_complements(matrix_t *A, matrix_t *result)` | Минор матрицы и матрица алгебраических дополнений. |
| 10 | `int determinant(matrix_t *A, double *result)` | Определитель матрицы. |
| 11 | `int inverse_matrix(matrix_t *A, matrix_t *result)` | Обратная матрица. |

### Так же, для реализации, были написаны следующие вспомогательные функции:

| № | Функция | Описание |
| ------ | ------ | ------ |
| 1 | `int is_valid(matrix_t *A)` | Выполняет проверку, является ли матрица валидной. |
| 2 | `int is_equal(matrix_t *A, matrix_t *B)` | Выполняет сравнение двух матриц. |
| 3 | `void get_minor(int rows, int columns, matrix_t *A, matrix_t *result)` | Функция для нахождения минора матрицы. |
| 4 | `double get_determinant(matrix_t *A)` | Вспомогательная функция для нахождения определителя матрицы. |
| 5 | `void fill(matrix_t *matrix, double value)` | Заполнение матрицы значениями (используется в тестах). |
