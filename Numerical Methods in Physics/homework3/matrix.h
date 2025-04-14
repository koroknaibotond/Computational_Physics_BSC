#include <cmath>
#include <iostream>
#include <vector>

template <typename T>
class Matrix
{
private:
    std::vector<std::vector<T>> data; // 2D vector to store the matrix
    int rows;                         // number of rows and columns
    int cols;

public:
    Matrix(int numRows, int numCols)                                              // Default constructor fills the matrix with ones
        : data(numRows, std::vector<T>(numCols, 1)), rows(numRows), cols(numCols) // Initialize rows and columns
    {
    }

    Matrix(Matrix const &cpy)                            // Copy constructor
        : data(cpy.data), rows(cpy.rows), cols(cpy.cols) // Copy data and dimensions
    {
    }

    Matrix(Matrix &&mv)                                          // Move constructor
        : data(std::move(mv.data)), rows(mv.rows), cols(mv.cols) // Transfer ownership
    {
        mv.rows = 0; // Nullify the original matrix dimensions
        mv.cols = 0;
    }

    Matrix<T> &operator=(Matrix<T> const &cpy) // Copy assignment operator
    {
        if (this != &cpy) // Only copy if the matrices are different
        {
            data = cpy.data;
            rows = cpy.rows;
            cols = cpy.cols;
        }
        return *this;
    }

    Matrix<T> &operator=(Matrix<T> &&mv) // Move assignment operator
    {
        if (this != &mv)
        {
            data = std::move(mv.data);
            rows = mv.rows;
            cols = mv.cols;
        }
        return *this;
    }

    T &operator[](int i)
    {
        return data[i]; // Access the specified row
    }

    const T &operator[](int i) const
    {
        return data[i];
    }

    T &operator()(int i, int j)
    {
        return data[i][j]; // Access element at (i,j)
    }

    const T &operator()(int i, int j) const
    {
        return data[i][j];
    }

    // + Operator
    Matrix<T> operator+(const Matrix<T> &other) const // Classic version
    {
        if (rows != other.rows || cols != other.cols) // Check for dimension match
        {
            std::cout << ("Dimension mismatch!");
        }

        Matrix<T> sum(rows, cols);

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                sum.data[i][j] = data[i][j] + other.data[i][j]; // Add elements
            }
        }

        return sum;
    }

    Matrix<T> operator+(Matrix<T> &&other) // R-value reference version
    {
        if (rows != other.rows || cols != other.cols)
        {
            std::cout << ("Dimension mismatch!");
        }

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                other.data[i][j] += data[i][j]; // Add and move into right-hand matrix
            }
        }

        return data = std::move(other.data);
    }

    // - Operator
    Matrix<T> operator-(const Matrix<T> &other) const // Classic version
    {
        if (rows != other.rows || cols != other.cols) // Dimension check
        {
            std::cout << ("Dimension mismatch!");
        }

        Matrix<T> diff(rows, cols);

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                diff.data[i][j] = data[i][j] - other.data[i][j]; // Subtract elements
            }
        }

        return diff;
    }

    Matrix<T> operator-(Matrix<T> &&other) // R-value reference version
    {
        if (rows != other.rows || cols != other.cols)
        {
            std::cout << ("Dimension mismatch.");
        }

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                other.data[i][j] -= data[i][j]; // Subtract and move into result
            }
        }

        return data = std::move(other.data);
    }

    // Scalar multiplication
    Matrix<T> operator*(const T &scalar) const
    {
        Matrix<T> result(rows, cols);

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                result.data[i][j] = data[i][j] * scalar; // Multiply each element
            }
        }

        return result;
    }

    Matrix<T> operator*(Matrix<T> &&scalar) // R-value reference for scalar
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                data[i][j] *= scalar;
            }
        }

        return data = std::move(data); // Move result into current matrix
    }

    // Scalar division
    Matrix<T> operator/(const T &scalar) const
    {
        Matrix<T> result(rows, cols);

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                result.data[i][j] = data[i][j] / scalar; // Divide each element
            }
        }

        return result;
    }

    Matrix<T> operator/(Matrix<T> &&scalar) // R-value reference for scalar division
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                data[i][j] /= scalar;
            }
        }

        return data = std::move(data);
    }

    // Matrix multiplication
    Matrix<T> matrixProduct(const Matrix<T> &other) const
    {
        if (cols != other.rows)
        {
            std::cout << ("Dimension mismatch!");
        }

        Matrix<T> result(rows, other.cols); // Create result matrix with appropriate dimensions

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < other.cols; ++j)
            {
                T sum = 0;
                for (int k = 0; k < cols; ++k)
                {
                    sum += data[i][k] * other.data[k][j]; // Dot product
                }
                result(i, j) = sum;
            }
        }

        return result;
    }

    Matrix<T> matrixProduct(const Matrix<T> &&other) // R-value reference version
    {
        if (cols != other.rows)
        {
            std::cout << ("Dimension mismatch!");
        }

        Matrix<T> result(rows, other.cols);

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < other.cols; ++j)
            {
                T sum = 0;
                for (int k = 0; k < cols; ++k)
                {
                    sum += data[i][k] * other.data[k][j];
                }
                result(i, j) = sum;
            }
        }

        return data = std::move(result); // Move result into current matrix
    }

    Matrix(int numRows, int numCols, const std::vector<T> &values)
        : data(numRows, std::vector<T>(numCols)), rows(numRows), cols(numCols)
    {
        int index = 0;
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j) // Fill row-wise
            {
                data[i][j] = values[index++];
            }
        }
    } // Allows filling the matrix with values from an external vector

    int numRows() const // Helper function to return number of rows
    {
        return rows;
    }

    int numCols() const // Helper function to return number of columns
    {
        return cols;
    }

    void print() const // Print function for inspection
    {
        for (const auto &row : data) // Loop through rows
        {
            for (const auto &element : row) // Loop through elements in each row
            {
                std::cout << element << " ";
            }
            std::cout << std::endl; // New line after each row
        }
    }
};
