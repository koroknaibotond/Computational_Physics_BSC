#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

void competitive_exclusion(double n1_0, double n2_0, double r1, double r2, double k1, double k2, double alpha, double beta, double dt, int steps, const char *filename)
{
    double n1 = n1_0;
    double n2 = n2_0;
    ofstream file(filename);

    for (int i = 0; i < steps; ++i)
    {
        double dn1 = r1 * n1 * (1 - (n1 + alpha * n2) / k1);
        double dn2 = r2 * n2 * (1 - (n2 + beta * n1) / k2);
        n1 += dt * dn1;
        n2 += dt * dn2;
        file << i * dt << " " << n1 << " " << n2 << endl;
    }

    file.close();
}

int main()
{
    // Paramters
    double n1_0 = 10;
    double n2_0 = 5;
    double r1 = 0.1;
    double r2 = 0.2;
    double k1 = 30;
    double k2 = 20;
    double alpha = 0.5;
    double beta = 0.6;
    double dt = 0.01;
    int steps = 40000;

    // Simulation of competitive exclusion and stable coexistence.
    competitive_exclusion(n1_0, n2_0, r1, r2, k1, k2, alpha, beta, dt, steps, "competitive_exclusion_data2.txt");

    return 0;
}
