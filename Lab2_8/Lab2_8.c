double function(double x) {
    //TODO: create function
}

double getSolution(double a, double b, double eps) {
    if (function(a) == 0) return a;
    if (function(b) == 0) return b;
    if (function(a) * function(b) > 0) return a;
    if (function(b)-function(a) < eps) return (a + b) / 2.0;
    if (function((a + b)/2) == 0) return (a+b)/2;
    if (function((a+b)/2) * function(a) > 0) return getSolution((a+b)/2, b, eps);
    if (function((a+b)/2) * function(a) < 0) return getSolution(a, (a+b)/2, eps);
}