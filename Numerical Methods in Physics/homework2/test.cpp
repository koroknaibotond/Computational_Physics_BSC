#include "vector2.h"
#include <iostream>

int main()
{
    // Testing addition with internal and external functions:
    std::cout << "The two vectors used for testing addition:" << std::endl;
    std::cout << "u = (1,1), and v = (2,2)" << std::endl;
    std::cout << "\n";
    std::cout << "Testing addition - with new vector: w = u + v" << std::endl;
    Vector2<int> u(1, 1);
    Vector2<int> v(2, 2);
    Vector2<int> w = u + v;
    std::cout << "w = (" << w.x << ", " << w.y << ")" << std::endl;
    std::cout << "Testing addition - with modification: w += u" << std::endl;
    w += u;
    std::cout << "w = (" << w.x << ", " << w.y << ")" << std::endl;

    // Testing subtraction with internal and external functions:
    std::cout << "\n";
    std::cout << "Testing subtraction - with new vector: w2 = u - v" << std::endl;
    Vector2<int> w2 = u - v;
    std::cout << "w2 = (" << w2.x << ", " << w2.y << ")" << std::endl;
    std::cout << "Testing subtraction - with modification: w2 -= u" << std::endl;
    w2 -= u;
    std::cout << "w2 = (" << w2.x << ", " << w2.y << ")" << std::endl;

    // Testing length calculation:
    std::cout << "\n";
    std::cout << "To test length calculation, I used vector v = (2,2)," << std::endl;
    std::cout << "whose length is: |v| = " << length(v) << std::endl;

    // Testing square of length:
    std::cout << "\n";
    std::cout << "To test the square of the length, I used the vector v = (2,2)," << std::endl;
    std::cout << "whose squared length is: |v|^2 = " << sqlength(v) << std::endl;

    // Testing normalization:
    std::cout << "\n";
    std::cout << "To test normalization, I again used the vector v = (2,2)." << std::endl;
    Vector2<double> normalized_v = normalized(v);
    std::cout << "The normalized vector is: vnorm = (" << normalized_v.x << ',' << normalized_v.y << ")" << std::endl;
    std::cout << "\n";

    // Scalar multiplication - external/internal functions:
    Vector2<int> v_scalar_int(2, 2);
    Vector2<double> v_scalar_double(1.5, 1.5);
    std::cout << "To test scalar multiplication, I used v_scalar_int = (2,2) and v_scalar_double = (1.5,1.5)." << std::endl;
    // Right-side multiplication:
    std::cout << "\n";
    std::cout << "Right-side multiplication:" << std::endl;
    std::cout << "I multiplied the first by 2, and the second by 2.5:" << std::endl;
    Vector2<int> v_right_int = v_scalar_int * 2;
    Vector2<double> v_right_double = v_scalar_double * 2.5;
    std::cout << "v_right_int = (" << v_right_int.x << ',' << v_right_int.y << ")" << std::endl;
    std::cout << "v_right_double = (" << v_right_double.x << ',' << v_right_double.y << ")" << std::endl;
    std::cout << "\n";
    // Left-side multiplication:
    std::cout << "Left-side multiplication:" << std::endl;
    std::cout << "I multiplied the first by 3, and the second by 3.5:" << std::endl;
    Vector2<int> v_left_int = v_scalar_int * 3;
    Vector2<double> v_left_double = v_scalar_double * 3.5;
    std::cout << "v_left_int = (" << v_left_int.x << ',' << v_left_int.y << ")" << std::endl;
    std::cout << "v_left_double = (" << v_left_double.x << ',' << v_left_double.y << ")" << std::endl;
    // Internal scalar multiplication - modifying the vector:
    std::cout << "\n";
    std::cout << "Scalar multiplication - modifying the vector:" << std::endl;
    std::cout << "I multiplied the first by 4, and the second by 4.5:" << std::endl;
    v_scalar_int *= 4;
    v_scalar_double *= 4.5;
    std::cout << "v_scalar_int = (" << v_scalar_int.x << ',' << v_scalar_int.y << ")" << std::endl;
    std::cout << "v_scalar_double = (" << v_scalar_double.x << ',' << v_scalar_double.y << ")" << std::endl;

    // Scalar division - external function
    std::cout << "\n";
    Vector2<int> v_divide_int(4, 4);
    Vector2<double> v_divide_double(6.5, 6.5);
    std::cout << "To test scalar division, I defined v_divide_int = (4,4), and v_divide_double = (6.5,6.5)." << std::endl;
    std::cout << "I divided the first by 2, and the second by 2.5:" << std::endl;
    Vector2<int> v_final_int = v_divide_int / 2;
    Vector2<double> v_final_double = v_divide_double / 2.5;
    std::cout << "v_final_int = (" << v_final_int.x << ',' << v_final_int.y << ")" << std::endl;
    std::cout << "v_final_double = (" << v_final_double.x << ',' << v_final_double.y << ")" << std::endl;
    // Internal scalar division - modifying the vector:
    std::cout << "\n";
    std::cout << "Scalar division - modifying the vector:" << std::endl;
    std::cout << "I divided the first by 4, and the second by 4.5:" << std::endl;
    v_divide_int /= 4;
    v_divide_double /= 4.5;
    std::cout << "v_divide_int = (" << v_divide_int.x << ',' << v_divide_int.y << ")" << std::endl;
    std::cout << "v_divide_double = (" << v_divide_double.x << ',' << v_divide_double.y << ")" << std::endl;

    // Dot product:
    std::cout << "\n";
    std::cout << "To test the dot product, the vectors used: test_v1 = (5,5), test_v2 = (10,10)" << std::endl;
    Vector2<int> test_1(5, 5);
    Vector2<int> test_2(10, 10);
    int test_result = dot(test_1, test_2);
    std::cout << "The result of the dot product is: " << test_result << std::endl;
}
