#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

// logistic equation
double logistic_eq(double x, double r)
{
    return r * x * (1 - x);
}

// Euler - Method
void euler(double x0, double r, double dt, int steps, const char *filename)
{
    double x = x0;
    ofstream file(filename);

    for (int i = 0; i < steps; ++i)
    {
        x += dt * logistic_eq(x, r);
        file << i * dt << " " << x << endl;
    }

    file.close();
}

// adaptive Runge-Kutta method
void runge_kutta(double x0, double r, double dt, int steps, const char *filename)
{
    double x = x0;
    ofstream file(filename);

    for (int i = 0; i < steps; ++i)
    {
        double k1 = dt * logistic_eq(x, r);
        double k2 = dt * logistic_eq(x + k1 / 2, r);
        double k3 = dt * logistic_eq(x + k2 / 2, r);
        double k4 = dt * logistic_eq(x + k3, r);
        x += (k1 + 2 * k2 + 2 * k3 + k4) / 6;
        file << i * dt << " " << x << endl;
    }

    file.close();
}

int main()
{
    // parmeters
    double x0 = 0.1;
    double r = 2.5;
    double dt = 0.01;
    int steps = 1000;

    euler(x0, r, dt, steps, "euler_data.txt");

    runge_kutta(x0, r, dt, steps, "runge_kutta_data.txt");

    return 0;
}
