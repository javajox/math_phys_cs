#ifndef VECTOROPS_LIBRARY_H
#define VECTOROPS_LIBRARY_H
#include <stddef.h>

typedef struct {
    double *data;
    size_t length;
} Vector;

/**
 * Implements sum of two Euclidean vectors
 * @param u
 * @param v
 * @return sum of u and v
 */
Vector *sum(const Vector *u, const Vector *v);
Vector *vector_scale(const Vector *u, double c);
double product(const Vector *u, const Vector *v);
double norm(const Vector *u);
double distance(const Vector *u, const Vector *v);

#endif