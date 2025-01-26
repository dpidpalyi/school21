#include "test_s21_3DViewer.h"

START_TEST(test_s21_check_facets_string_0) {
  // Check correct facets string
  char s[] = "f 1 2 3";
  int want_err = 0;
  int got_err = s21_check_facets_string(s);

  ck_assert_int_eq(want_err, got_err);
}
END_TEST

START_TEST(test_s21_check_facets_string_1) {
  // Check correct facets string
  char s[] = "f 1/2 2/2 3/3";
  int want_err = 0;
  int got_err = s21_check_facets_string(s);

  ck_assert_int_eq(want_err, got_err);
}
END_TEST

START_TEST(test_s21_check_facets_string_2) {
  // Check correct facets string
  char s[] = "f 1//2 2//2 3//3";
  int want_err = 0;
  int got_err = s21_check_facets_string(s);

  ck_assert_int_eq(want_err, got_err);
}
END_TEST

START_TEST(test_s21_check_facets_string_3) {
  // Check correct facets string
  char s[] = "f 1/2/3 2/3/4 3/4/5";
  int want_err = 0;
  int got_err = s21_check_facets_string(s);

  ck_assert_int_eq(want_err, got_err);
}
END_TEST

START_TEST(test_s21_check_facets_string_4) {
  // Check invalid facets string
  char s[] = "f 1.2 2.3 4.5";
  int want_err = 1;
  int got_err = s21_check_facets_string(s);

  ck_assert_int_eq(want_err, got_err);
}
END_TEST

START_TEST(test_s21_check_facets_string_5) {
  // Check invalid facets string
  char s[] = "f 1/2 2/a 3/4";
  int want_err = 1;
  int got_err = s21_check_facets_string(s);

  ck_assert_int_eq(want_err, got_err);
}
END_TEST

START_TEST(test_s21_parse_file_0) {
  // Parse file that doesn't exist
  Data model = {};
  int want_err = NO_FILE;
  int got_err = s21_parse_file("models/incorrect_file", &model);

  ck_assert_int_eq(want_err, got_err);
}
END_TEST

START_TEST(test_s21_parse_file_1) {
  // Parse empty file
  Data model = {};
  int want_err = BAD_FORMAT;
  int got_err = s21_parse_file("models/empty_file", &model);

  ck_assert_int_eq(want_err, got_err);
}
END_TEST

START_TEST(test_s21_parse_file_2) {
  // Parse file with no facets in it
  Data model = {};
  int want_err = BAD_FORMAT;
  int got_err = s21_parse_file("models/no_facets", &model);

  ck_assert_int_eq(want_err, got_err);
}
END_TEST

START_TEST(test_s21_parse_file_3) {
  // Parse file with no vertexes in it
  Data model = {};
  int want_err = BAD_FORMAT;
  int got_err = s21_parse_file("models/no_vertexes", &model);

  ck_assert_int_eq(want_err, got_err);
}
END_TEST

START_TEST(test_s21_parse_file_9) {
  // Parse file with incorrect vertexes format
  Data model = {};
  int want_err = BAD_FORMAT;
  int got_err = s21_parse_file("models/vertex_bad_format", &model);

  ck_assert_int_eq(want_err, got_err);
}
END_TEST

START_TEST(test_s21_parse_file_10) {
  // Parse file with incorrect facets format
  Data model = {};
  int want_err = BAD_FORMAT;
  int got_err = s21_parse_file("models/facets_bad_format_1", &model);

  ck_assert_int_eq(want_err, got_err);
}
END_TEST

START_TEST(test_s21_parse_file_11) {
  // Parse file with incorrect facets format
  Data model = {};
  int want_err = BAD_FORMAT;
  int got_err = s21_parse_file("models/facets_bad_format_2", &model);

  ck_assert_int_eq(want_err, got_err);
}
END_TEST

START_TEST(test_s21_parse_file_12) {
  // Parse file with incorrect facets format
  Data model = {};
  int want_err = BAD_FORMAT;
  int got_err = s21_parse_file("models/facets_bad_format_3", &model);

  ck_assert_int_eq(want_err, got_err);
}
END_TEST

START_TEST(test_s21_parse_file_13) {
  // Parse file with incorrect facets format
  Data model = {};
  int want_err = BAD_FORMAT;
  int got_err = s21_parse_file("models/facets_bad_format_4", &model);

  ck_assert_int_eq(want_err, got_err);
}
END_TEST

START_TEST(test_s21_parse_file_4) {
  // Parse simple correct file
  Data model = {0};
  int want_err = 0, want_vertexes = 3, want_facets = 2;
  double want_matrix[] = {0, 0, 1, 0, 1, 0, 1, 0, 0};
  int v1[] = {1, 2, 3};
  int v2[] = {3, 2, 1};
  polygon_t want_p[2] = {{v1, 3}, {v2, 3}};
  int got_err = s21_parse_file("models/simple", &model);

  ck_assert_int_eq(want_err, got_err);
  ck_assert_int_eq(want_vertexes, model.count_of_vertexes);
  ck_assert_int_eq(want_facets, model.count_of_facets);
  int count = 0;
  for (int i = 1; i < model.count_of_vertexes; i++) {
    ck_assert_double_eq_tol(want_matrix[count++], model.matrix_3d.matrix[i][0],
                            EPS);
    ck_assert_double_eq_tol(want_matrix[count++], model.matrix_3d.matrix[i][1],
                            EPS);
    ck_assert_double_eq_tol(want_matrix[count++], model.matrix_3d.matrix[i][2],
                            EPS);
  }
  for (int i = 0; i < model.count_of_facets; i++) {
    ck_assert_int_eq(want_p[i].vertexes[0], model.polygons[i + 1].vertexes[0]);
    ck_assert_int_eq(want_p[i].vertexes[1], model.polygons[i + 1].vertexes[1]);
    ck_assert_int_eq(want_p[i].vertexes[2], model.polygons[i + 1].vertexes[2]);
  }
  s21_remove_model(&model);
}
END_TEST

START_TEST(test_s21_parse_file_5) {
  // Parse simple square file
  Data model = {0};
  int want_err = 0, want_vertexes = 4, want_facets = 1;
  double want_matrix[] = {0, 2, 0, 0, 0, 0, 2, 0, 0, 2, 2, 0};
  int v1[] = {1, 2, 3, 4};
  polygon_t want_p[1] = {{v1, 4}};
  int got_err = s21_parse_file("models/square", &model);

  ck_assert_int_eq(want_err, got_err);
  ck_assert_int_eq(want_vertexes, model.count_of_vertexes);
  ck_assert_int_eq(want_facets, model.count_of_facets);
  int count = 0;
  for (int i = 1; i < model.count_of_vertexes; i++) {
    ck_assert_double_eq_tol(want_matrix[count++], model.matrix_3d.matrix[i][0],
                            EPS);
    ck_assert_double_eq_tol(want_matrix[count++], model.matrix_3d.matrix[i][1],
                            EPS);
    ck_assert_double_eq_tol(want_matrix[count++], model.matrix_3d.matrix[i][2],
                            EPS);
  }
  ck_assert_int_eq(want_p[0].vertexes[0], model.polygons[1].vertexes[0]);
  ck_assert_int_eq(want_p[0].vertexes[1], model.polygons[1].vertexes[1]);
  ck_assert_int_eq(want_p[0].vertexes[2], model.polygons[1].vertexes[2]);
  ck_assert_int_eq(want_p[0].vertexes[3], model.polygons[1].vertexes[3]);
  s21_remove_model(&model);
}
END_TEST

START_TEST(test_s21_parse_file_6) {
  // Parse simple square file with negative facets
  Data model = {0};
  int want_err = 0, want_vertexes = 4, want_facets = 1;
  double want_matrix[] = {0, 2, 0, 0, 0, 0, 2, 0, 0, 2, 2, 0};
  int v1[] = {1, 2, 3, 4};
  polygon_t want_p[1] = {{v1, 4}};
  int got_err = s21_parse_file("models/square_negate", &model);

  ck_assert_int_eq(want_err, got_err);
  ck_assert_int_eq(want_vertexes, model.count_of_vertexes);
  ck_assert_int_eq(want_facets, model.count_of_facets);
  int count = 0;
  for (int i = 1; i < model.count_of_vertexes; i++) {
    ck_assert_double_eq_tol(want_matrix[count++], model.matrix_3d.matrix[i][0],
                            EPS);
    ck_assert_double_eq_tol(want_matrix[count++], model.matrix_3d.matrix[i][1],
                            EPS);
    ck_assert_double_eq_tol(want_matrix[count++], model.matrix_3d.matrix[i][2],
                            EPS);
  }
  ck_assert_int_eq(want_p[0].vertexes[0], model.polygons[1].vertexes[0]);
  ck_assert_int_eq(want_p[0].vertexes[1], model.polygons[1].vertexes[1]);
  ck_assert_int_eq(want_p[0].vertexes[2], model.polygons[1].vertexes[2]);
  ck_assert_int_eq(want_p[0].vertexes[3], model.polygons[1].vertexes[3]);
  s21_remove_model(&model);
}
END_TEST

START_TEST(test_s21_parse_file_7) {
  // Parse simple cube file
  Data model = {0};
  int want_err = 0, want_vertexes = 8, want_facets = 6;
  double want_matrix[] = {0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 2, 2,
                          0, 2, 0, 0, 0, 0, 2, 0, 0, 2, 2, 0};
  int v1[] = {1, 2, 3, 4};
  int v2[] = {8, 7, 6, 5};
  int v3[] = {4, 3, 7, 8};
  int v4[] = {5, 1, 4, 8};
  int v5[] = {5, 6, 2, 1};
  int v6[] = {2, 6, 7, 3};
  polygon_t want_p[6] = {{v1, 4}, {v2, 4}, {v3, 4}, {v4, 4}, {v5, 4}, {v6, 4}};
  int got_err = s21_parse_file("models/cube", &model);

  ck_assert_int_eq(want_err, got_err);
  ck_assert_int_eq(want_vertexes, model.count_of_vertexes);
  ck_assert_int_eq(want_facets, model.count_of_facets);
  int count = 0;
  for (int i = 1; i < model.count_of_vertexes; i++) {
    ck_assert_double_eq_tol(want_matrix[count++], model.matrix_3d.matrix[i][0],
                            EPS);
    ck_assert_double_eq_tol(want_matrix[count++], model.matrix_3d.matrix[i][1],
                            EPS);
    ck_assert_double_eq_tol(want_matrix[count++], model.matrix_3d.matrix[i][2],
                            EPS);
  }
  for (int i = 0; i < model.count_of_facets; i++) {
    ck_assert_int_eq(want_p[i].vertexes[0], model.polygons[i + 1].vertexes[0]);
    ck_assert_int_eq(want_p[i].vertexes[1], model.polygons[i + 1].vertexes[1]);
    ck_assert_int_eq(want_p[i].vertexes[2], model.polygons[i + 1].vertexes[2]);
    ck_assert_int_eq(want_p[i].vertexes[3], model.polygons[i + 1].vertexes[3]);
  }
  s21_remove_model(&model);
}
END_TEST

START_TEST(test_s21_parse_file_8) {
  // Parse simple cube file with negative facets
  Data model = {0};
  int want_err = 0, want_vertexes = 24, want_facets = 6;
  double want_matrix[] = {0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 0, 0,
                          0, 0, 0, 0, 2, 0, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0,
                          0, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 0, 0, 0, 0,
                          0, 0, 2, 0, 2, 2, 0, 0, 2, 0, 0, 0, 2, 0, 0, 2, 0, 2};
  int v1[] = {1, 2, 3, 4};
  int v2[] = {5, 6, 7, 8};
  int v3[] = {9, 10, 11, 12};
  int v4[] = {13, 14, 15, 16};
  int v5[] = {17, 18, 19, 20};
  int v6[] = {21, 22, 23, 24};
  polygon_t want_p[6] = {{v1, 4}, {v2, 4}, {v3, 4}, {v4, 4}, {v5, 4}, {v6, 4}};
  int got_err = s21_parse_file("models/cube_negate", &model);

  ck_assert_int_eq(want_err, got_err);
  ck_assert_int_eq(want_vertexes, model.count_of_vertexes);
  ck_assert_int_eq(want_facets, model.count_of_facets);
  int count = 0;
  for (int i = 1; i < model.count_of_vertexes; i++) {
    ck_assert_double_eq_tol(want_matrix[count++], model.matrix_3d.matrix[i][0],
                            EPS);
    ck_assert_double_eq_tol(want_matrix[count++], model.matrix_3d.matrix[i][1],
                            EPS);
    ck_assert_double_eq_tol(want_matrix[count++], model.matrix_3d.matrix[i][2],
                            EPS);
  }
  for (int i = 0; i < model.count_of_facets; i++) {
    ck_assert_int_eq(want_p[i].vertexes[0], model.polygons[i + 1].vertexes[0]);
    ck_assert_int_eq(want_p[i].vertexes[1], model.polygons[i + 1].vertexes[1]);
    ck_assert_int_eq(want_p[i].vertexes[2], model.polygons[i + 1].vertexes[2]);
    ck_assert_int_eq(want_p[i].vertexes[3], model.polygons[i + 1].vertexes[3]);
  }
  s21_remove_model(&model);
}
END_TEST

START_TEST(test_s21_parse_file_cube) {
  Data cube = {0};
  getCube(&cube);

  Data parse = {0};
  int want_err = 0;
  int got_err = s21_parse_file("obj/cube._obj", &parse);

  ck_assert_int_eq(want_err, got_err);
  ck_assert_int_eq(cube.count_of_facets, parse.count_of_facets);
  ck_assert_int_eq(cube.count_of_vertexes, parse.count_of_vertexes);
  ck_assert_int_eq(s21_eq_matrix(&cube.matrix_3d, &parse.matrix_3d), 1);

  for (int i = 1; i < cube.count_of_facets + 1; i++) {
    ck_assert_int_eq(cube.polygons[i].number_of_vertexes_in_facets,
                     parse.polygons[i].number_of_vertexes_in_facets);
    for (int j = 0; j < cube.polygons[i].number_of_vertexes_in_facets; j++) {
      ck_assert_int_eq(cube.polygons[i].vertexes[j],
                       parse.polygons[i].vertexes[j]);
    }
  }
  s21_remove_model(&cube);
  s21_remove_model(&parse);
}
END_TEST

Suite *test_s21_parse_file(void) {
  Suite *s = suite_create("===== S21_3DVIEWER_PARSE_FILE =====");
  TCase *tc = tcase_create("s21_parse_file");

  tcase_add_test(tc, test_s21_check_facets_string_0);
  tcase_add_test(tc, test_s21_check_facets_string_1);
  tcase_add_test(tc, test_s21_check_facets_string_2);
  tcase_add_test(tc, test_s21_check_facets_string_3);
  tcase_add_test(tc, test_s21_check_facets_string_4);
  tcase_add_test(tc, test_s21_check_facets_string_5);
  tcase_add_test(tc, test_s21_parse_file_0);
  tcase_add_test(tc, test_s21_parse_file_1);
  tcase_add_test(tc, test_s21_parse_file_2);
  tcase_add_test(tc, test_s21_parse_file_3);
  tcase_add_test(tc, test_s21_parse_file_4);
  tcase_add_test(tc, test_s21_parse_file_5);
  tcase_add_test(tc, test_s21_parse_file_6);
  tcase_add_test(tc, test_s21_parse_file_7);
  tcase_add_test(tc, test_s21_parse_file_8);
  tcase_add_test(tc, test_s21_parse_file_9);
  tcase_add_test(tc, test_s21_parse_file_10);
  tcase_add_test(tc, test_s21_parse_file_11);
  tcase_add_test(tc, test_s21_parse_file_12);
  tcase_add_test(tc, test_s21_parse_file_13);
  tcase_add_test(tc, test_s21_parse_file_cube);
  suite_add_tcase(s, tc);

  return s;
}
