#include <iostream>
#include "matrix.h"

int main()
{
    std::vector<int> datas = {1, 2, 3, 4};
    std::vector<int> datas2 = {5, 6, 7, 8};

    Matrix<int> matrixdefault(4, 4);       // Testing default constructor
    Matrix<int> matrixcopy(matrixdefault); // Testing copy constructor

    std::cout << "Matrix from the default constructor:" << std::endl;
    matrixdefault.print();
    std::cout << '\n';
    std::cout << "Matrix from the copy constructor:" << std::endl;
    matrixcopy.print();

    std::cout << '\n';
    Matrix<int> movematrix(std::move(matrixcopy)); // This step destroys matrixcopy
    std::cout << "Moved matrixcopy into movematrix.\n";
    std::cout << "To verify, we'll print the row and column count of matrixcopy to check if it was truly emptied.\n";
    std::cout << "Number of rows: " << matrixcopy.numRows() << std::endl; // Should return 0,0 if destroyed
    std::cout << "Number of columns: " << matrixcopy.numCols() << std::endl;

    std::cout << '\n';
    std::cout << "Testing assignment (=) operator:" << std::endl;
    Matrix<int> matrixtest1(2, 2, datas);  // Create matrix with 1,2,3,4
    Matrix<int> matrixtest2(2, 2, datas2); // Create matrix with 5,6,7,8
    matrixtest1 = matrixtest2;
    matrixtest1.print();

    std::cout << '\n';
    std::cout << "Testing indexing:" << std::endl;
    int value11 = matrixtest1(1, 1); // Indexing starts at 0
    std::cout << "The value of matrixtest1(2,2) is = " << value11 << std::endl;

    std::cout << '\n';
    std::cout << "Testing addition:" << std::endl;
    Matrix<int> sum = matrixtest1 + matrixtest2;
    sum.print();

    std::cout << '\n';
    std::cout << "Testing subtraction:" << std::endl;
    Matrix<int> matrixdiff1(2, 2, datas);
    Matrix<int> matrixtdiff2(2, 2, datas2);
    Matrix<int> diff = matrixdiff1 - matrixtdiff2;
    diff.print();

    std::cout << '\n';
    std::cout << "Testing scalar multiplication:" << std::endl;
    Matrix<int> product = matrixdefault * 3;
    product.print();

    std::cout << '\n';
    std::cout << "Testing scalar division:" << std::endl;
    std::vector<int> datas3 = {3, 6, 9, 12};
    Matrix<int> divmatrix(2, 2, datas3);
    Matrix<int> divide = divmatrix / 3;
    divide.print();

    std::cout << '\n';
    std::cout << "Testing matrix multiplication:" << std::endl;
    std::vector<int> testdata1 = {2, 2, 2, 2};
    std::vector<int> testdata2 = {3, 3, 3, 3};
    Matrix<int> dot1(2, 2, testdata1);
    Matrix<int> dot2(2, 2, testdata2);
    Matrix<int> dotfinal = dot1.matrixProduct(dot2);
    dotfinal.print();

    return 0;
}
