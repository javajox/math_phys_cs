#include "vectorops.h"

#include <math.h>
#include <stdlib.h>

#include "assert.h"

Vector *sum(const Vector *u, const Vector *v) {
    assert(u != NULL);
    assert(v != NULL);
    assert(u->length > 0);
    assert(v->length > 0);
    assert(u->length == v->length);
    Vector *result = malloc(sizeof(Vector));
    result->length = u->length;
    result->data = malloc(sizeof(double) * result->length);

    for (int i = 0; i < u->length; i++) {
        result->data[i] = u->data[i] + v->data[i];
    }

    return result;
}

Vector *vector_scale(const Vector *u, const double c) {
    assert(u != NULL);
    assert(c != 0);
    Vector *result = malloc(sizeof(Vector));
    result->length = u->length;
    result->data = malloc(sizeof(double) * result->length);
    for (int i = 0; i < u->length; i++) {
        result->data[i] = u->data[i] * c;
    }

    return result;
}

double product(const Vector *u, const Vector *v) {
    assert(u != NULL);
    assert(v != NULL);
    assert(u->length > 0);
    assert(v->length > 0);
    assert(u->length == v->length);

    double result = 0.0;
    for (int i = 0; i < u->length; i++) {
        result += u->data[i] * v->data[i];
    }

    return result;
}

double norm(const Vector *u) {
    assert(u != NULL);
    assert(u->length > 0);
    double square_sum = 0.0;
    for (int i = 0; i < u->length; i++) {
        square_sum += pow(u->data[i], 2);
    }
    const double result = sqrt(square_sum);
    return result;
}

double distance(const Vector *u, const Vector *v) {
    assert(u != NULL);
    assert(v != NULL);
    assert(u->length > 0);
    assert(v->length > 0);
    assert(u->length == v->length);

    Vector *scaled = vector_scale(v, -1);
    Vector *summed = sum(u, scaled);

    const double result = norm(summed);

    free(summed);
    free(scaled);

    return result;
}