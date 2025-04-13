#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
using namespace std;

#include "vector.hpp"
#include "odeint.hpp"
using namespace cpl;

// Gravitational constant
const double G = 1;
double m1, m2, m3;

// Function to compute derivatives for the three-body problem
Vector f(const Vector &x)
{
    double r1x = x[0], r1y = x[1]; // Position of body 1
    double v1x = x[2], v1y = x[3]; // Velocity of body 1

    double r2x = x[4], r2y = x[5]; // Position of body 2
    double v2x = x[6], v2y = x[7]; // Velocity of body 2

    double r3x = x[8], r3y = x[9];   // Position of body 3
    double v3x = x[10], v3y = x[11]; // Velocity of body 3

    double r12_squared = (r1x - r2x) * (r1x - r2x) + (r1y - r2y) * (r1y - r2y);
    double r13_squared = (r1x - r3x) * (r1x - r3x) + (r1y - r3y) * (r1y - r3y);
    double r23_squared = (r2x - r3x) * (r2x - r3x) + (r2y - r3y) * (r2y - r3y);

    double r12_cubed = r12_squared * sqrt(r12_squared);
    double r13_cubed = r13_squared * sqrt(r13_squared);
    double r23_cubed = r23_squared * sqrt(r23_squared);

    Vector f(12);

    // Derivatives for body 1
    f[0] = v1x;
    f[1] = v1y;
    f[2] = -G * m2 * (r1x - r2x) / fabs(r12_cubed) - G * m3 * (r1x - r3x) / fabs(r13_cubed);
    f[3] = -G * m2 * (r1y - r2y) / fabs(r12_cubed) - G * m3 * (r1y - r3y) / fabs(r13_cubed);

    // Derivatives for body 2
    f[4] = v2x;
    f[5] = v2y;
    f[6] = -G * m3 * (r2x - r3x) / fabs(r23_cubed) - G * m1 * (r2x - r1x) / fabs(r12_cubed);
    f[7] = -G * m3 * (r2y - r3y) / fabs(r23_cubed) - G * m1 * (r2y - r1y) / fabs(r12_cubed);

    // Derivatives for body 3
    f[8] = v3x;
    f[9] = v3y;
    f[10] = -G * m1 * (r3x - r1x) / fabs(r13_cubed) - G * m2 * (r3x - r2x) / fabs(r23_cubed);
    f[11] = -G * m1 * (r3y - r1y) / fabs(r13_cubed) - G * m2 * (r3y - r2y) / fabs(r23_cubed);

    return f;
}

int main()
{
    cout << "The three-body problem\n"
         << " -----------------------------------------------------\n";

    // Assign masses
    m1 = 1; // Mass of Body 1 *kg * 10^23
    m2 = 1; // Mass of Body 2 *kg *10^23
    m3 = 1; // Mass of Body 3 example: Ceres - *kg*10^23

    Vector x0(12);
    // Initial conditions for a stable figure-eight orbit
    // Body 1
    x0[0] = -0.97000436;  // x-coordinate of Body 1
    x0[1] = 0.24308753;   // y-coordinate of Body 1
    x0[2] = -0.466203685; // initial velocity in x-direction of Body 1
    x0[3] = -0.43236573;  // initial velocity in y-direction of Body 1

    // Body 2
    x0[4] = 0.97000436;   // x-coordinate of Body 2
    x0[5] = -0.24308753;  // y-coordinate of Body 2
    x0[6] = -0.466203685; // initial velocity in x-direction of Body 2
    x0[7] = -0.43236573;  // initial velocity in y-direction of Body 2

    // Body 3
    x0[8] = 0.0;         // x-coordinate of Body 3
    x0[9] = 0.0;         // y-coordinate of Body 3
    x0[10] = 0.93240737; // initial velocity in x-direction of Body 3
    x0[11] = 0.86473146; // initial velocity in y-direction of Body 3

    double dt = 0.001;
    double total_time = 10.0; // Example: integrate for 10 seconds

    ofstream dataFile("L1.data");
    Vector x = x0;
    double t = 0.0;
    cout << "\n Integrating with fixed step size" << endl;
    while (t < total_time)
    {
        for (int i = 0; i < 12; i++)
            dataFile << x[i] << '\t';
        dataFile << '\n';

        RK4Step(x, dt, f);
        t += dt;
    }

    dataFile.close();
}