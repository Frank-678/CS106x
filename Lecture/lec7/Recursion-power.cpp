int power(int base, int exponent) {
    if (exponent < 0) {
        throw exponent;
    } else if (exponent == 0) {
        return base;
    } else {
        return power(base, exponent - 1) * base;
    }  
}
