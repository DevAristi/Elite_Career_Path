#include "InterestCalculator.h"

double InterestCalculator::calculateTotal(double cap, double tasa, int m) {
    double interest = (cap * tasa * m) / 1200.0; 
    return cap + interest;
}