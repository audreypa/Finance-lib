

//abstract base class


/*class BinaryFunction {
public:
    BinaryFunction() {};
    virtual double operator() (double left, double right) = 0;
};

class Add : public BinaryFunction {
public:
    Add() {};
    virtual double operator() (double left, double right) { return left + right;}
};

class Multiply : public BinaryFunction {
public:
    Multiply() {};
    virtual double operator() (double left, double right) { return left * right;}
};


double binary_op(double left, double right, BinaryFunction* bin_func) {
    return (*bin_func)(left, right);
}*/

/*int main() {
    double a = 30.0;
    double b = 10.0;

    BinaryFunction* pAdd = new Add();
    BinaryFunction* pMultiply = new Multiply();


    std::cout << "Add: " << binary_op(a, b, pAdd) << std::endl;
    std::cout << "Multiply: " << binary_op(a, b, pMultiply) << std::endl;


    delete pAdd;
    delete pMultiply;


    return 0;
}*/

/*int main() {

    Eigen::MatrixXd m(3,3);
    m<< 1,2,3,4,5,6,7,8,9;

    std::cout << m << std::endl;

}*/


