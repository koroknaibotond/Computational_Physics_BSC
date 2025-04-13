#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "vector.hpp"
#include "odeint.hpp"
using namespace cpl;

const double pi = 4 * atan(1.0);

const double g = 9.8;
double L = 1.0;
double q = 0.5;
double Omega_D = 2.0 / 3.0;
double F_D = 0.9;
bool nonlinear;

Vector f(const Vector &x)
{
    double t = x[0];
    double theta = x[1];
    double omega = x[2];
    Vector f(3);
    f[0] = 1;

    f[1] = omega;
    if (nonlinear)
        f[2] = -(g / L) * sin(theta) - q * omega + F_D * sin(Omega_D * t);
    else
        f[2] = -(g / L) * theta - q * omega + F_D * sin(Omega_D * t);
    return f;
}

void eulerStep(Vector &x, double dt)
{
    x += dt * f(x);
}

void eulerCromerStep(Vector &x, double dt)
{
    x[2] += dt * f(x)[2];
    x[1] += dt * x[2];
    x[0] += dt;
}

int main()
{
    cout << " Nonlinear damped driven pendulum\n"
         << " --------------------------------\n"
         << " Enter linear or nonlinear: ";
    string response;
    cin >> response;
    nonlinear = (response[0] == 'n');
    cout << " Length of pendulum L: ";
    cin >> L;
    cout << " Enter damping coefficient q: ";
    cin >> q;
    cout << " Enter driving frequencey Omega_D: ";
    cin >> Omega_D;
    cout << " Enter driving amplitude F_D: ";
    cin >> F_D;
    cout << " Enter theta(0) and omega(0): ";
    double theta, omega, tMax;
    cin >> theta >> omega;
    cout << " Enter integration time t_max: ";
    cin >> tMax;

    double dt = 0.05;
    string method;
    cout << " Enter method (euler, euler_cromer, runge_kutta, adaptive_rk4): ";
    cin >> method;

    ofstream dataFile;
    if (method == "euler")
    {
        dataFile.open("euler_physical2.data");
    }
    else if (method == "euler_cromer")
    {
        dataFile.open("euler_cromerphysical2.data");
    }
    else if (method == "runge_kutta")
    {
        dataFile.open("runge_physical2.data");
    }
    else if (method == "adaptive_rk4")
    {
        dataFile.open("adaptive2.data");
    }
    else
    {
        cout << "Invalid method. Exiting program." << endl;
        return 1;
    }

    double t = 0;
    Vector x(3);
    x[0] = t;
    x[1] = theta;
    x[2] = omega;

    while (t < tMax)
    {
        if (method == "euler")
        {
            eulerStep(x, dt);
            t = x[0], theta = x[1], omega = x[2];
            if (nonlinear)
            {
                while (theta >= pi)
                    theta -= 2 * pi;

                while (theta < -pi)
                    theta += 2 * pi;
            }
        }
        else if (method == "euler_cromer")
        {
            eulerCromerStep(x, dt);
            t = x[0], theta = x[1], omega = x[2];
            if (nonlinear)
            {
                while (theta >= pi)
                    theta -= 2 * pi;
                while (theta < -pi)
                    theta += 2 * pi;
            }
        }
        else if (method == "runge_kutta")
        {
            RK4Step(x, dt, f);
            t = x[0], theta = x[1], omega = x[2];
            if (nonlinear)
            {
                while (theta >= pi)
                    theta -= 2 * pi;
                while (theta < -pi)
                    theta += 2 * pi;
            }
        }
        else if (method == "adaptive_rk4")
        {
            adaptiveRK4Step(x, dt, 1e-6, f);
            t = x[0], theta = x[1], omega = x[2];
            if (nonlinear)
            {
                while (theta >= pi)
                    theta -= 2 * pi;
                while (theta < -pi)
                    theta += 2 * pi;
            }
        }

        dataFile << t << '\t' << x[1] << '\t' << x[2] << '\n';
        t += dt;
    }

    cout << " Output data to file " << method << ".data" << endl;
    dataFile.close();
}
