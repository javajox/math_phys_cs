#include <stdlib.h>

#include "unity.h"
#include "vectorops.h"

void setUp(void) {}
void tearDown(void) {}

void test_sum_3_sized_vector(void) {
    Vector *u = malloc(sizeof(Vector));
    u->length = 3;
    u->data = malloc(sizeof(double) * u->length);
    u->data[0] = 4;
    u->data[1] = 7;
    u->data[2] = 20;

    Vector *v = malloc(sizeof(Vector));
    v->length = u->length;
    v->data = malloc(sizeof(double) * v->length);
    v->data[0] = 8;
    v->data[1] = 3;
    v->data[2] = 100;

    Vector *result = sum(u, v);

    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_NOT_NULL(result->data);
    TEST_ASSERT_EQUAL(u->length, result->length);
    TEST_ASSERT_EQUAL_DOUBLE(12, result->data[0]);
    TEST_ASSERT_EQUAL_DOUBLE(10, result->data[1]);
    TEST_ASSERT_EQUAL_DOUBLE(120, result->data[2]);

    free(v->data);
    free(v);
    free(u->data);
    free(u);
    free(result->data);
    free(result);
}

void test_scale_vector_3_sized_vector(void) {
    Vector *u = malloc(sizeof(Vector));
    u->length = 3;
    u->data = malloc(sizeof(double) * u->length);
    u->data[0] = 4;
    u->data[1] = 7;
    u->data[2] = 20;

    Vector *result = vector_scale(u, 2);

    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_NOT_NULL(result->data);
    TEST_ASSERT_EQUAL(u->length, result->length);
    TEST_ASSERT_EQUAL_DOUBLE(8, result->data[0]);
    TEST_ASSERT_EQUAL_DOUBLE(14, result->data[1]);
    TEST_ASSERT_EQUAL_DOUBLE(40, result->data[2]);

    free(u->data);
    free(u);
    free(result->data);
    free(result);
}

void test_product_vector_3_sized_vector(void) {
    Vector *u = malloc(sizeof(Vector));
    u->length = 3;
    u->data = malloc(sizeof(double) * u->length);
    u->data[0] = 4;
    u->data[1] = 7;
    u->data[2] = 20;

    Vector *v = malloc(sizeof(Vector));
    v->length = u->length;
    v->data = malloc(sizeof(double) * v->length);
    v->data[0] = 8;
    v->data[1] = 3;
    v->data[2] = 100;

    const double result = product(u, v);

    TEST_ASSERT_EQUAL_DOUBLE(2053, result);

    free(v->data);
    free(v);
    free(u->data);
    free(u);
}

void test_norm_vector_3_sized_vector(void) {
    Vector *u = malloc(sizeof(Vector));
    u->length = 3;
    u->data = malloc(sizeof(double) * u->length);
    u->data[0] = 3;
    u->data[1] = 6;
    u->data[2] = 11;

    const double result = norm(u);
    TEST_ASSERT_DOUBLE_WITHIN(0.00001, 12.8840987, result);

    free(u->data);
    free(u);
}

void test_distance_vector_3_sized_vector(void) {
    Vector *u = malloc(sizeof(Vector));
    u->length = 3;
    u->data = malloc(sizeof(double) * u->length);
    u->data[0] = 1;
    u->data[1] = 3;
    u->data[2] = 9;

    Vector *v = malloc(sizeof(Vector));
    v->length = u->length;
    v->data = malloc(sizeof(double) * v->length);
    v->data[0] = 2;
    v->data[1] = 5;
    v->data[2] = 1;

    const double result = distance(u, v);

    TEST_ASSERT_DOUBLE_WITHIN(0.001, 8.307, result);

    free(v->data);
    free(v);
    free(u->data);
    free(u);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_sum_3_sized_vector);
    RUN_TEST(test_scale_vector_3_sized_vector);
    RUN_TEST(test_product_vector_3_sized_vector);
    RUN_TEST(test_norm_vector_3_sized_vector);
    RUN_TEST(test_distance_vector_3_sized_vector);

    return UNITY_END();
}