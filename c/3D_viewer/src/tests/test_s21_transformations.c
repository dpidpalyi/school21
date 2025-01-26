#include "test_s21_3DViewer.h"

START_TEST(test_s21_transformations_move_all_0) {
  // Move matrix for 0.0
  matrix_t A = {};
  matrix_t WANT = {};
  s21_create_matrix_old(1, 3, &A);
  s21_create_matrix_old(1, 3, &WANT);
  for (int j = 0; j < 3; ++j) {
    A.matrix[0][j] = 1.0;
    WANT.matrix[0][j] = 1.0;
  }

  move_all(&A, 0.0, 0.0, 0.0);
  ck_assert_int_eq(s21_eq_matrix(&A, &WANT), 1);
  s21_remove_matrix_old(&A);
  s21_remove_matrix_old(&WANT);
}
END_TEST

START_TEST(test_s21_transformations_move_all_1) {
  // Move matrix for 1.0
  matrix_t A = {};
  matrix_t WANT = {};
  s21_create_matrix_old(1, 3, &A);
  s21_create_matrix_old(1, 3, &WANT);
  for (int j = 0; j < 3; ++j) {
    A.matrix[0][j] = 1.0;
    WANT.matrix[0][j] = 2.0;
  }

  move_all(&A, 1.0, 1.0, 1.0);
  ck_assert_int_eq(s21_eq_matrix(&A, &WANT), 1);
  s21_remove_matrix_old(&A);
  s21_remove_matrix_old(&WANT);
}
END_TEST

START_TEST(test_s21_transformations_move_x_0) {
  // Move matrix x coordinate for 0.0
  matrix_t A = {};
  matrix_t WANT = {};
  s21_create_matrix_old(1, 3, &A);
  s21_create_matrix_old(1, 3, &WANT);
  for (int j = 0; j < 3; ++j) {
    A.matrix[0][j] = 1.0;
    WANT.matrix[0][j] = 1.0;
  }

  move_x(&A, 0.0);
  ck_assert_int_eq(s21_eq_matrix(&A, &WANT), 1);
  s21_remove_matrix_old(&A);
  s21_remove_matrix_old(&WANT);
}
END_TEST

START_TEST(test_s21_transformations_move_x_1) {
  // Move matrix x coordinate for 1.0
  matrix_t A = {};
  matrix_t WANT = {};
  s21_create_matrix_old(1, 3, &A);
  s21_create_matrix_old(1, 3, &WANT);
  for (int j = 0; j < 3; ++j) {
    A.matrix[0][j] = 1.0;
    WANT.matrix[0][j] = 1.0;
  }
  WANT.matrix[0][0] = 2.0;

  move_x(&A, 1.0);
  ck_assert_int_eq(s21_eq_matrix(&A, &WANT), 1);
  s21_remove_matrix_old(&A);
  s21_remove_matrix_old(&WANT);
}
END_TEST

START_TEST(test_s21_transformations_move_y_0) {
  // Move matrix y coordinate for 0.0
  matrix_t A = {};
  matrix_t WANT = {};
  s21_create_matrix_old(1, 3, &A);
  s21_create_matrix_old(1, 3, &WANT);
  for (int j = 0; j < 3; ++j) {
    A.matrix[0][j] = 1.0;
    WANT.matrix[0][j] = 1.0;
  }

  move_y(&A, 0.0);
  ck_assert_int_eq(s21_eq_matrix(&A, &WANT), 1);
  s21_remove_matrix_old(&A);
  s21_remove_matrix_old(&WANT);
}
END_TEST

START_TEST(test_s21_transformations_move_y_1) {
  // Move matrix y coordinate for 1.0
  matrix_t A = {};
  matrix_t WANT = {};
  s21_create_matrix_old(1, 3, &A);
  s21_create_matrix_old(1, 3, &WANT);
  for (int j = 0; j < 3; ++j) {
    A.matrix[0][j] = 1.0;
    WANT.matrix[0][j] = 1.0;
  }
  WANT.matrix[0][1] = 2.0;

  move_y(&A, 1.0);
  ck_assert_int_eq(s21_eq_matrix(&A, &WANT), 1);
  s21_remove_matrix_old(&A);
  s21_remove_matrix_old(&WANT);
}
END_TEST

START_TEST(test_s21_transformations_move_z_0) {
  // Move matrix z coordinate for 0.0
  matrix_t A = {};
  matrix_t WANT = {};
  s21_create_matrix_old(1, 3, &A);
  s21_create_matrix_old(1, 3, &WANT);
  for (int j = 0; j < 3; ++j) {
    A.matrix[0][j] = 1.0;
    WANT.matrix[0][j] = 1.0;
  }

  move_z(&A, 0.0);
  ck_assert_int_eq(s21_eq_matrix(&A, &WANT), 1);
  s21_remove_matrix_old(&A);
  s21_remove_matrix_old(&WANT);
}
END_TEST

START_TEST(test_s21_transformations_move_z_1) {
  // Move matrix z coordinate for 1.0
  matrix_t A = {};
  matrix_t WANT = {};
  s21_create_matrix_old(1, 3, &A);
  s21_create_matrix_old(1, 3, &WANT);
  for (int j = 0; j < 3; ++j) {
    A.matrix[0][j] = 1.0;
    WANT.matrix[0][j] = 1.0;
  }
  WANT.matrix[0][2] = 2.0;

  move_z(&A, 1.0);
  ck_assert_int_eq(s21_eq_matrix(&A, &WANT), 1);
  s21_remove_matrix_old(&A);
  s21_remove_matrix_old(&WANT);
}
END_TEST

START_TEST(test_s21_transformations_rotation_x_0) {
  // Rotate matrix x coordinate for 0.0
  matrix_t A = {};
  matrix_t WANT = {};
  s21_create_matrix_old(1, 3, &A);
  s21_create_matrix_old(1, 3, &WANT);
  for (int j = 0; j < 3; ++j) {
    A.matrix[0][j] = 1.0;
    WANT.matrix[0][j] = 1.0;
  }

  rotation_x(&A, 0.0);
  ck_assert_int_eq(s21_eq_matrix(&A, &WANT), 1);
  s21_remove_matrix_old(&A);
  s21_remove_matrix_old(&WANT);
}
END_TEST

START_TEST(test_s21_transformations_rotation_x_1) {
  // Rotate matrix x coordinate for Pi
  matrix_t A = {};
  matrix_t WANT = {};
  s21_create_matrix_old(1, 3, &A);
  s21_create_matrix_old(1, 3, &WANT);
  for (int j = 0; j < 3; ++j) {
    A.matrix[0][j] = 1.0;
    WANT.matrix[0][j] = 1.0;
  }
  WANT.matrix[0][1] = -1.0;
  WANT.matrix[0][2] = -1.0;

  rotation_x(&A, 3.1415926535);
  ck_assert_int_eq(s21_eq_matrix(&A, &WANT), 1);
  s21_remove_matrix_old(&A);
  s21_remove_matrix_old(&WANT);
}
END_TEST

START_TEST(test_s21_transformations_rotation_y_0) {
  // Rotate matrix y coordinate for 0.0
  matrix_t A = {};
  matrix_t WANT = {};
  s21_create_matrix_old(1, 3, &A);
  s21_create_matrix_old(1, 3, &WANT);
  for (int j = 0; j < 3; ++j) {
    A.matrix[0][j] = 1.0;
    WANT.matrix[0][j] = 1.0;
  }

  rotation_y(&A, 0.0);
  ck_assert_int_eq(s21_eq_matrix(&A, &WANT), 1);
  s21_remove_matrix_old(&A);
  s21_remove_matrix_old(&WANT);
}
END_TEST

START_TEST(test_s21_transformations_rotation_y_1) {
  // Rotate matrix y coordinate for Pi
  matrix_t A = {};
  matrix_t WANT = {};
  s21_create_matrix_old(1, 3, &A);
  s21_create_matrix_old(1, 3, &WANT);
  for (int j = 0; j < 3; ++j) {
    A.matrix[0][j] = 1.0;
    WANT.matrix[0][j] = 1.0;
  }
  WANT.matrix[0][0] = -1.0;
  WANT.matrix[0][2] = -1.0;

  rotation_y(&A, 3.1415926535);
  ck_assert_int_eq(s21_eq_matrix(&A, &WANT), 1);
  s21_remove_matrix_old(&A);
  s21_remove_matrix_old(&WANT);
}
END_TEST

START_TEST(test_s21_transformations_rotation_z_0) {
  // Rotate matrix z coordinate for 0.0
  matrix_t A = {};
  matrix_t WANT = {};
  s21_create_matrix_old(1, 3, &A);
  s21_create_matrix_old(1, 3, &WANT);
  for (int j = 0; j < 3; ++j) {
    A.matrix[0][j] = 1.0;
    WANT.matrix[0][j] = 1.0;
  }

  rotation_z(&A, 0.0);
  ck_assert_int_eq(s21_eq_matrix(&A, &WANT), 1);
  s21_remove_matrix_old(&A);
  s21_remove_matrix_old(&WANT);
}
END_TEST

START_TEST(test_s21_transformations_rotation_z_1) {
  // Rotate matrix z coordinate for Pi
  matrix_t A = {};
  matrix_t WANT = {};
  s21_create_matrix_old(1, 3, &A);
  s21_create_matrix_old(1, 3, &WANT);
  for (int j = 0; j < 3; ++j) {
    A.matrix[0][j] = 1.0;
    WANT.matrix[0][j] = 1.0;
  }
  WANT.matrix[0][0] = -1.0;
  WANT.matrix[0][1] = -1.0;

  rotation_z(&A, 3.1415926535);
  ck_assert_int_eq(s21_eq_matrix(&A, &WANT), 1);
  s21_remove_matrix_old(&A);
  s21_remove_matrix_old(&WANT);
}
END_TEST

START_TEST(test_s21_transformations_scale_all_0) {
  // Scale matrix for 0.0
  matrix_t A = {};
  matrix_t WANT = {};
  int want_err = 1;
  s21_create_matrix_old(1, 3, &A);
  s21_create_matrix_old(1, 3, &WANT);
  for (int j = 0; j < 3; ++j) {
    A.matrix[0][j] = 1.0;
    WANT.matrix[0][j] = 1.0;
  }

  int got_err = scale_all(&A, 0.0, 0.0, 0.0);
  ck_assert_int_eq(want_err, got_err);
  ck_assert_int_eq(s21_eq_matrix(&A, &WANT), 1);
  s21_remove_matrix_old(&A);
  s21_remove_matrix_old(&WANT);
}
END_TEST

START_TEST(test_s21_transformations_scale_all_1) {
  // Scale matrix for 2.0
  matrix_t A = {};
  matrix_t WANT = {};
  int want_err = 0;
  s21_create_matrix_old(1, 3, &A);
  s21_create_matrix_old(1, 3, &WANT);
  for (int j = 0; j < 3; ++j) {
    A.matrix[0][j] = 1.0;
    WANT.matrix[0][j] = 2.0;
  }

  int got_err = scale_all(&A, 2.0, 2.0, 2.0);
  ck_assert_int_eq(want_err, got_err);
  ck_assert_int_eq(s21_eq_matrix(&A, &WANT), 1);
  s21_remove_matrix_old(&A);
  s21_remove_matrix_old(&WANT);
}
END_TEST

START_TEST(test_s21_transformations_scale_x_0) {
  // Scale matrix x coordinate for 0.0
  matrix_t A = {};
  matrix_t WANT = {};
  int want_err = 1;
  s21_create_matrix_old(1, 3, &A);
  s21_create_matrix_old(1, 3, &WANT);
  for (int j = 0; j < 3; ++j) {
    A.matrix[0][j] = 1.0;
    WANT.matrix[0][j] = 1.0;
  }

  int got_err = scale_x(&A, 0.0);
  ck_assert_int_eq(want_err, got_err);
  ck_assert_int_eq(s21_eq_matrix(&A, &WANT), 1);
  s21_remove_matrix_old(&A);
  s21_remove_matrix_old(&WANT);
}
END_TEST

START_TEST(test_s21_transformations_scale_x_1) {
  // Scale matrix x coordinate for 2.0
  matrix_t A = {};
  matrix_t WANT = {};
  int want_err = 0;
  s21_create_matrix_old(1, 3, &A);
  s21_create_matrix_old(1, 3, &WANT);
  for (int j = 0; j < 3; ++j) {
    A.matrix[0][j] = 1.0;
    WANT.matrix[0][j] = 1.0;
  }
  WANT.matrix[0][0] = 2.0;

  int got_err = scale_x(&A, 2.0);
  ck_assert_int_eq(want_err, got_err);
  ck_assert_int_eq(s21_eq_matrix(&A, &WANT), 1);
  s21_remove_matrix_old(&A);
  s21_remove_matrix_old(&WANT);
}
END_TEST

START_TEST(test_s21_transformations_scale_y_0) {
  // Scale matrix y coordinate for 0.0
  matrix_t A = {};
  matrix_t WANT = {};
  int want_err = 1;
  s21_create_matrix_old(1, 3, &A);
  s21_create_matrix_old(1, 3, &WANT);
  for (int j = 0; j < 3; ++j) {
    A.matrix[0][j] = 1.0;
    WANT.matrix[0][j] = 1.0;
  }

  int got_err = scale_y(&A, 0.0);
  ck_assert_int_eq(want_err, got_err);
  ck_assert_int_eq(s21_eq_matrix(&A, &WANT), 1);
  s21_remove_matrix_old(&A);
  s21_remove_matrix_old(&WANT);
}
END_TEST

START_TEST(test_s21_transformations_scale_y_1) {
  // Scale matrix y coordinate for 2.0
  matrix_t A = {};
  matrix_t WANT = {};
  int want_err = 0;
  s21_create_matrix_old(1, 3, &A);
  s21_create_matrix_old(1, 3, &WANT);
  for (int j = 0; j < 3; ++j) {
    A.matrix[0][j] = 1.0;
    WANT.matrix[0][j] = 1.0;
  }
  WANT.matrix[0][1] = 2.0;

  int got_err = scale_y(&A, 2.0);
  ck_assert_int_eq(want_err, got_err);
  ck_assert_int_eq(s21_eq_matrix(&A, &WANT), 1);
  s21_remove_matrix_old(&A);
  s21_remove_matrix_old(&WANT);
}
END_TEST

START_TEST(test_s21_transformations_scale_z_0) {
  // Scale matrix z coordinate for 0.0
  matrix_t A = {};
  matrix_t WANT = {};
  int want_err = 1;
  s21_create_matrix_old(1, 3, &A);
  s21_create_matrix_old(1, 3, &WANT);
  for (int j = 0; j < 3; ++j) {
    A.matrix[0][j] = 1.0;
    WANT.matrix[0][j] = 1.0;
  }

  int got_err = scale_z(&A, 0.0);
  ck_assert_int_eq(want_err, got_err);
  ck_assert_int_eq(s21_eq_matrix(&A, &WANT), 1);
  s21_remove_matrix_old(&A);
  s21_remove_matrix_old(&WANT);
}
END_TEST

START_TEST(test_s21_transformations_scale_z_1) {
  // Scale matrix z coordinate for 2.0
  matrix_t A = {};
  matrix_t WANT = {};
  int want_err = 0;
  s21_create_matrix_old(1, 3, &A);
  s21_create_matrix_old(1, 3, &WANT);
  for (int j = 0; j < 3; ++j) {
    A.matrix[0][j] = 1.0;
    WANT.matrix[0][j] = 1.0;
  }
  WANT.matrix[0][2] = 2.0;

  int got_err = scale_z(&A, 2.0);
  ck_assert_int_eq(want_err, got_err);
  ck_assert_int_eq(s21_eq_matrix(&A, &WANT), 1);
  s21_remove_matrix_old(&A);
  s21_remove_matrix_old(&WANT);
}
END_TEST

Suite *test_s21_transformations(void) {
  Suite *s = suite_create("===== S21_3DVIEWER_TRANSFORMATIONS =====");
  TCase *tc = tcase_create("s21_transformations");

  tcase_add_test(tc, test_s21_transformations_move_all_0);
  tcase_add_test(tc, test_s21_transformations_move_all_1);
  tcase_add_test(tc, test_s21_transformations_move_x_0);
  tcase_add_test(tc, test_s21_transformations_move_x_1);
  tcase_add_test(tc, test_s21_transformations_move_y_0);
  tcase_add_test(tc, test_s21_transformations_move_y_1);
  tcase_add_test(tc, test_s21_transformations_move_z_0);
  tcase_add_test(tc, test_s21_transformations_move_z_1);
  tcase_add_test(tc, test_s21_transformations_rotation_x_0);
  tcase_add_test(tc, test_s21_transformations_rotation_x_1);
  tcase_add_test(tc, test_s21_transformations_rotation_y_0);
  tcase_add_test(tc, test_s21_transformations_rotation_y_1);
  tcase_add_test(tc, test_s21_transformations_rotation_z_0);
  tcase_add_test(tc, test_s21_transformations_rotation_z_1);
  tcase_add_test(tc, test_s21_transformations_scale_all_0);
  tcase_add_test(tc, test_s21_transformations_scale_all_1);
  tcase_add_test(tc, test_s21_transformations_scale_x_0);
  tcase_add_test(tc, test_s21_transformations_scale_x_1);
  tcase_add_test(tc, test_s21_transformations_scale_y_0);
  tcase_add_test(tc, test_s21_transformations_scale_y_1);
  tcase_add_test(tc, test_s21_transformations_scale_z_0);
  tcase_add_test(tc, test_s21_transformations_scale_z_1);
  suite_add_tcase(s, tc);

  return s;
}
