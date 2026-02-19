
#include "unity.h"
#include "matrix_sum.h"

void setUp(void) {
    // Runs before each test
}

void tearDown(void) {
    // Runs after each test
}

// ---- create2DArray tests ----

void test_create2DArray_returns_non_null(void) {
    int **arr = create2DArray(3, 3);
    TEST_ASSERT_NOT_NULL(arr);
    destroy2DArray(arr);
}

void test_create2DArray_rows_are_non_null(void) {
    int rows = 4, cols = 5;
    int **arr = create2DArray(rows, cols);
    for (int i = 0; i < rows; i++) {
        TEST_ASSERT_NOT_NULL(arr[i]);
    }
    destroy2DArray(arr);
}

void test_create2DArray_single_element(void) {
    int **arr = create2DArray(1, 1);
    TEST_ASSERT_NOT_NULL(arr);
    TEST_ASSERT_NOT_NULL(arr[0]);
    destroy2DArray(arr);
}

// ---- initialize2DArray tests ----

void test_initialize2DArray_all_zeros(void) {
    int rows = 3, cols = 4;
    int **arr = create2DArray(rows, cols);
    initialize2DArray(arr, rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            TEST_ASSERT_EQUAL_INT(0, arr[i][j]);
        }
    }
    destroy2DArray(arr);
}

void test_initialize2DArray_overwrites_existing_values(void) {
    int rows = 2, cols = 2;
    int **arr = create2DArray(rows, cols);

    arr[0][0] = 42;
    arr[0][1] = -7;
    arr[1][0] = 100;
    arr[1][1] = 999;

    initialize2DArray(arr, rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            TEST_ASSERT_EQUAL_INT(0, arr[i][j]);
        }
    }
    destroy2DArray(arr);
}

void test_initialize2DArray_single_element(void) {
    int **arr = create2DArray(1, 1);
    arr[0][0] = 55;
    initialize2DArray(arr, 1, 1);
    TEST_ASSERT_EQUAL_INT(0, arr[0][0]);
    destroy2DArray(arr);
}

// ---- sum tests ----

void test_sum_basic(void) {
    int rows = 2, cols = 2;
    int **a = create2DArray(rows, cols);
    int **b = create2DArray(rows, cols);

    a[0][0] = 1; a[0][1] = 2;
    a[1][0] = 3; a[1][1] = 4;

    b[0][0] = 5; b[0][1] = 6;
    b[1][0] = 7; b[1][1] = 8;

    int **result = sum(a, b, rows, cols);

    TEST_ASSERT_EQUAL_INT(6,  result[0][0]);
    TEST_ASSERT_EQUAL_INT(8,  result[0][1]);
    TEST_ASSERT_EQUAL_INT(10, result[1][0]);
    TEST_ASSERT_EQUAL_INT(12, result[1][1]);

    destroy2DArray(result);
    destroy2DArray(b);
    destroy2DArray(a);
}

void test_sum_with_zeros(void) {
    int rows = 2, cols = 3;
    int **a = create2DArray(rows, cols);
    int **b = create2DArray(rows, cols);
    initialize2DArray(a, rows, cols);
    initialize2DArray(b, rows, cols);

    a[0][0] = 10; a[0][1] = 20; a[0][2] = 30;
    a[1][0] = 40; a[1][1] = 50; a[1][2] = 60;

    int **result = sum(a, b, rows, cols);

    TEST_ASSERT_EQUAL_INT(10, result[0][0]);
    TEST_ASSERT_EQUAL_INT(20, result[0][1]);
    TEST_ASSERT_EQUAL_INT(30, result[0][2]);
    TEST_ASSERT_EQUAL_INT(40, result[1][0]);
    TEST_ASSERT_EQUAL_INT(50, result[1][1]);
    TEST_ASSERT_EQUAL_INT(60, result[1][2]);

    destroy2DArray(result);
    destroy2DArray(b);
    destroy2DArray(a);
}

void test_sum_both_zero_matrices(void) {
    int rows = 3, cols = 3;
    int **a = create2DArray(rows, cols);
    int **b = create2DArray(rows, cols);
    initialize2DArray(a, rows, cols);
    initialize2DArray(b, rows, cols);

    int **result = sum(a, b, rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            TEST_ASSERT_EQUAL_INT(0, result[i][j]);
        }
    }

    destroy2DArray(result);
    destroy2DArray(b);
    destroy2DArray(a);
}

void test_sum_with_negative_values(void) {
    int rows = 2, cols = 2;
    int **a = create2DArray(rows, cols);
    int **b = create2DArray(rows, cols);

    a[0][0] = -1; a[0][1] = -2;
    a[1][0] = -3; a[1][1] = -4;

    b[0][0] = -5; b[0][1] = -6;
    b[1][0] = -7; b[1][1] = -8;

    int **result = sum(a, b, rows, cols);

    TEST_ASSERT_EQUAL_INT(-6,  result[0][0]);
    TEST_ASSERT_EQUAL_INT(-8,  result[0][1]);
    TEST_ASSERT_EQUAL_INT(-10, result[1][0]);
    TEST_ASSERT_EQUAL_INT(-12, result[1][1]);

    destroy2DArray(result);
    destroy2DArray(b);
    destroy2DArray(a);
}

void test_sum_negative_and_positive_cancel_out(void) {
    int rows = 2, cols = 2;
    int **a = create2DArray(rows, cols);
    int **b = create2DArray(rows, cols);

    a[0][0] = 5;  a[0][1] = 10;
    a[1][0] = 15; a[1][1] = 20;

    b[0][0] = -5;  b[0][1] = -10;
    b[1][0] = -15; b[1][1] = -20;

    int **result = sum(a, b, rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            TEST_ASSERT_EQUAL_INT(0, result[i][j]);
        }
    }

    destroy2DArray(result);
    destroy2DArray(b);
    destroy2DArray(a);
}

void test_sum_single_element_matrices(void) {
    int **a = create2DArray(1, 1);
    int **b = create2DArray(1, 1);

    a[0][0] = 7;
    b[0][0] = 3;

    int **result = sum(a, b, 1, 1);
    TEST_ASSERT_EQUAL_INT(10, result[0][0]);

    destroy2DArray(result);
    destroy2DArray(b);
    destroy2DArray(a);
}

void test_sum_single_row_matrix(void) {
    int rows = 1, cols = 4;
    int **a = create2DArray(rows, cols);
    int **b = create2DArray(rows, cols);

    a[0][0] = 1; a[0][1] = 2; a[0][2] = 3; a[0][3] = 4;
    b[0][0] = 4; b[0][1] = 3; b[0][2] = 2; b[0][3] = 1;

    int **result = sum(a, b, rows, cols);

    TEST_ASSERT_EQUAL_INT(5, result[0][0]);
    TEST_ASSERT_EQUAL_INT(5, result[0][1]);
    TEST_ASSERT_EQUAL_INT(5, result[0][2]);
    TEST_ASSERT_EQUAL_INT(5, result[0][3]);

    destroy2DArray(result);
    destroy2DArray(b);
    destroy2DArray(a);
}

void test_sum_single_column_matrix(void) {
    int rows = 3, cols = 1;
    int **a = create2DArray(rows, cols);
    int **b = create2DArray(rows, cols);

    a[0][0] = 10; a[1][0] = 20; a[2][0] = 30;
    b[0][0] = 1;  b[1][0] = 2;  b[2][0] = 3;

    int **result = sum(a, b, rows, cols);

    TEST_ASSERT_EQUAL_INT(11, result[0][0]);
    TEST_ASSERT_EQUAL_INT(22, result[1][0]);
    TEST_ASSERT_EQUAL_INT(33, result[2][0]);

    destroy2DArray(result);
    destroy2DArray(b);
    destroy2DArray(a);
}

void test_sum_large_values(void) {
    int rows = 2, cols = 2;
    int **a = create2DArray(rows, cols);
    int **b = create2DArray(rows, cols);

    a[0][0] = 1000000; a[0][1] = 2000000;
    a[1][0] = 3000000; a[1][1] = 4000000;

    b[0][0] = 5000000; b[0][1] = 6000000;
    b[1][0] = 7000000; b[1][1] = 8000000;

    int **result = sum(a, b, rows, cols);

    TEST_ASSERT_EQUAL_INT(6000000,  result[0][0]);
    TEST_ASSERT_EQUAL_INT(8000000,  result[0][1]);
    TEST_ASSERT_EQUAL_INT(10000000, result[1][0]);
    TEST_ASSERT_EQUAL_INT(12000000, result[1][1]);

    destroy2DArray(result);
    destroy2DArray(b);
    destroy2DArray(a);
}

void test_sum_is_commutative(void) {
    int rows = 2, cols = 2;
    int **a = create2DArray(rows, cols);
    int **b = create2DArray(rows, cols);

    a[0][0] = 1; a[0][1] = 2;
    a[1][0] = 3; a[1][1] = 4;

    b[0][0] = 10; b[0][1] = 20;
    b[1][0] = 30; b[1][1] = 40;

    int **r1 = sum(a, b, rows, cols);
    int **r2 = sum(b, a, rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            TEST_ASSERT_EQUAL_INT(r1[i][j], r2[i][j]);
        }
    }

    destroy2DArray(r2);
    destroy2DArray(r1);
    destroy2DArray(b);
    destroy2DArray(a);
}

// ---- Runner ----

int main(void) {
    UNITY_BEGIN();

    // create2DArray
    RUN_TEST(test_create2DArray_returns_non_null);
    RUN_TEST(test_create2DArray_rows_are_non_null);
    RUN_TEST(test_create2DArray_single_element);

    // initialize2DArray
    RUN_TEST(test_initialize2DArray_all_zeros);
    RUN_TEST(test_initialize2DArray_overwrites_existing_values);
    RUN_TEST(test_initialize2DArray_single_element);

    // sum
    RUN_TEST(test_sum_basic);
    RUN_TEST(test_sum_with_zeros);
    RUN_TEST(test_sum_both_zero_matrices);
    RUN_TEST(test_sum_with_negative_values);
    RUN_TEST(test_sum_negative_and_positive_cancel_out);
    RUN_TEST(test_sum_single_element_matrices);
    RUN_TEST(test_sum_single_row_matrix);
    RUN_TEST(test_sum_single_column_matrix);
    RUN_TEST(test_sum_large_values);
    RUN_TEST(test_sum_is_commutative);

    return UNITY_END();
}