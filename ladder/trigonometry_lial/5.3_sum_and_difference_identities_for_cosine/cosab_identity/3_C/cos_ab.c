#include <math.h>
#include "cos_ab.h"

double cos_ab(double a, double b) {
    return cos(a) * cos(b) - sin(a) * sin(b);
}
