#include <iostream>
#include <Eigen/Dense>

/*int main() {
    //Declare 3x3 matrices
    Eigen::MatrixXf p(3,3);
    p << 12, -51, 4,
        6, 167, -68,
        -4, 24, -41;

    std::cout << "Matrix P:\n" << p << std::endl << std::endl;

    //Create the Householder QR Matrix
    Eigen::HouseholderQR<Eigen::MatrixXf> qr(p);
    Eigen::MatrixXf q = qr.householderQ();

    //Output Q, the Householder matrix
    std::cout << "Q Matrix:\n" << q << std::endl << std::endl;

    return 0;
}*/
