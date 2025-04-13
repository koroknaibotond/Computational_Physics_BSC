#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

// Lotka-Volterra modell a módosított feltételekkel
vector<double> lotka_volterra_modified(double t, vector<double> y, double a, double b, double c, double d, double k, double S)
{
    double nR = y[0];
    double nF = y[1];
    double a_modified = a * (1 - nR / k);
    double nRF_modified = nR * nF / (1 + nR * S);
    double dnR = a_modified * nR - b * nRF_modified;
    double dnF = c * nRF_modified - d * nF;
    return {dnR, dnF};
}

void runge_kutta_adaptive_modified(double t, vector<double> &y, double dt, double a, double b, double c, double d, double k, double S, const char *filename)
{
    ofstream file(filename);
    file << t << " " << y[0] << " " << y[1] << endl;
    while (t < 100)
    {
        vector<double> k1 = lotka_volterra_modified(t, y, a, b, c, d, k, S);
        vector<double> k2 = lotka_volterra_modified(t + 0.5 * dt, {y[0] + 0.5 * dt * k1[0], y[1] + 0.5 * dt * k1[1]}, a, b, c, d, k, S);
        vector<double> k3 = lotka_volterra_modified(t + 0.5 * dt, {y[0] + 0.5 * dt * k2[0], y[1] + 0.5 * dt * k2[1]}, a, b, c, d, k, S);
        vector<double> k4 = lotka_volterra_modified(t + dt, {y[0] + dt * k3[0], y[1] + dt * k3[1]}, a, b, c, d, k, S);
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
    double k = 800; // nyulak táplálékforrásának korlátja
    double S = 0;   // rókák nyúlfogyasztási képességének korlátja
    double dt = 0.01;
    vector<double> y = {600, 600};
    double t = 0;

    // adaptív Runge-Kutta módszerrel számolt módosított modell adatok
    runge_kutta_adaptive_modified(t, y, dt, a, b, c, d, k, S, "lotka_volterra_modified_data.txt");

    return 0;
}
