#include <cmath>
#include <iostream>
#include <vector>

/*void thomas_algorithm(const std::vector<double>& a,
                      const std::vector<double>& b,
                      const std::vector<double>& c,
                      const std::vector<double>& d,
                      std::vector<double>& f) {

    size_t N = d.size();

    //create c* and d* vector (temporary vectors)

    std::vector<double> c_star(N, 0.0);
    std::vector<double> d_star(N, 0.0);

    c_star[0] = c[0] / b[0];
    d_star[0] = d[0] / b[0];

    for (int i=1; i<N; i++) {
        double m = 1.0 / (b[i] - a[i] * c_star[i-1]);
        c_star[i] = c[i] * m;
        d_star[i] = (d[i] - a[i] * d_star[i-1]) * m;
    }

    // This is the reserve sweep, used to update the solution of vector f
    for (int i=N-1; i--> 0;) {
        f[i] = d_star[i] - c_star[i] * d[i+1];
    }

    }

int main(int argc, char **argv) {
    //example by solving the 1D heat equation
    // firstly we create a finite difference method (FDM) with 13 points using the Crank-Nicolson method

    size_t N = 13;
    double delta_x = 1.0/static_cast<double>(N);
    double delta_t = 0.001;
    double r = delta_t/(delta_x*delta_x);

    //creating vector for the Coeff

    std::vector<double> a(N-1, -r/2.0);
    std::vector<double> b(N, 1.0+r);
    std::vector<double> c(N-1, -r/2.0);
    std::vector<double> d(N, 0.0);
    std::vector<double> f(N, 0.0);

    //vector using three peaks with various amplitudes
    f[5] = 1; f[6] = 2; f[7] = 1;

    std::cout << " f (";
    for (int i=0; i<N; i++) {
        std::cout << f[i];
        if (i < N-1) {
            std::cout << ", ";
        }
    }
    std::cout << ")" << std::endl << std::endl;

    // fill in the current time step vector d
    for (int i=1; i<N-1; i++) {
        d[i] = r*0.5*f[i+1] + (1.0-r)*f[i] + r*0.5*f[i-1];
    }

    //solving tridiagonal system
    thomas_algorithm(a, b, c, d, f);

    //we output the solution of vector f
    std::cout << "f = (";
    for (int i=0; i<N; i++) {
        std::cout << f[i];
        if (i < N-1) {
            std::cout << ", ";
        }
    }
    std::cout << ")" << std::endl;

    return 0;
}*/
