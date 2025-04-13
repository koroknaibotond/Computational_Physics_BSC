#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

// Lotka-Volterra modell
vector<double> lotka_volterra(double t, vector<double> y, double a, double b, double c, double d)
{
    double nR = y[0];
    double nF = y[1];
    double dnR = a * nR - b * nF * nR;
    double dnF = c * nF * nR - d * nF;
    return {dnR, dnF};
}

// adaptív Runge-Kutta módszer
void runge_kutta_adaptive(double t, vector<double> &y, double dt, double a, double b, double c, double d, const char *filename)
{
    ofstream file(filename);
    file << t << " " << y[0] << " " << y[1] << endl;
    while (t < 100)
    {
        vector<double> k1 = lotka_volterra(t, y, a, b, c, d);
        vector<double> k2 = lotka_volterra(t + 0.5 * dt, {y[0] + 0.5 * dt * k1[0], y[1] + 0.5 * dt * k1[1]}, a, b, c, d);
        vector<double> k3 = lotka_volterra(t + 0.5 * dt, {y[0] + 0.5 * dt * k2[0], y[1] + 0.5 * dt * k2[1]}, a, b, c, d);
        vector<double> k4 = lotka_volterra(t + dt, {y[0] + dt * k3[0], y[1] + dt * k3[1]}, a, b, c, d);
        for (int i = 0; i < y.size(); ++i)
        {
            y[i] += dt * (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]) / 6;
        }
        t += dt;
        file << t << " " << y[0] << " " << y[1] << endl;
    }
    file.close();
}

int main()
{
    // paraméterek
    double a = 0.4;
    double b = 0.004;
    double c = 0.004;
    double d = 0.9;
    double dt = 0.01;
    vector<double> y = {500, 500}; // kezdeti populációk
    double t = 0;

    runge_kutta_adaptive(t, y, dt, a, b, c, d, "lotka_volterra_data2.txt");

    return 0;
}