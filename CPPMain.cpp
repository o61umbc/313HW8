
#include <iostream>
using namespace std;

class Matrix;


class Matrix {
public: 
    Matrix(int numRows,int numColumns,int** theArray) : m_rows(numRows),m_columns(numColumns),m_array(theArray) {

    }
    ~Matrix() {
        clear();
    }
    void clear() {
        if (m_array != nullptr) {
            for (int i = 0; i < m_rows; i++) {
                if (m_array[i] != nullptr) {
                    delete m_array[i];
                    m_array[i] = nullptr;
                }
            }
            delete m_array;
        }
        m_array = nullptr;
        m_rows = 0;
        m_columns = 0;
    }
    void add(Matrix* addingMatrix) {
        if (addingMatrix->m_rows == m_rows && addingMatrix->m_columns == m_columns) {
            //Can add
            for (int i = 0; i < m_rows; i++) {
                for (int v = 0; v < m_columns; v++) {
                    int theirValue = addingMatrix->m_array[i][v];;
                    int ourValue = m_array[i][v];
                    m_array[i][v] = ourValue + theirValue;
                }
            }
        }
    }
    void scalarMultiply(int multiplyValue) {
        for (int i = 0; i < m_rows; i++) {
            for (int v = 0; v < m_columns; v++) {
                m_array[i][v] = m_array[i][v] * multiplyValue;
            }
        }
    }
    void transpose() {
        int prevRows = m_rows;
        int prevColumns = m_columns;
        int** theArray = new int* [m_columns];
        for (int i = 0; i < m_columns; i++) {
            theArray[i] = new int[m_rows];
            for (int v = 0; v < m_rows; v++) {
                theArray[i][v] = m_array[v][i];
            }
        }
        clear();
        m_rows = prevColumns;
        m_columns = prevRows;
        m_array = theArray;
    }
    void multiply(Matrix* multiplyingMatrix) {
        if (m_columns == multiplyingMatrix->m_rows) {
            int ourRows = m_rows;
            int ourColumns = m_columns;
            int theirRows = multiplyingMatrix->m_rows;
            int theirColumns = multiplyingMatrix->m_columns;
            int** theArray = new int* [ourRows];

            for (int i = 0; i < ourRows; i++) {
                theArray[i] = new int[theirColumns];
                for (int v = 0; v < theirColumns; v++) {
                    theArray[i][v] = 0;
                }
            }
            for (int i = 0; i < ourRows; i++) {
                for (int v = 0; v < theirColumns; v++) {
                    theArray[i][v] = 0;
                    for (int a = 0; a < ourColumns; a++) {
                        theArray[i][v] += m_array[i][a] * multiplyingMatrix->m_array[a][v];
                    }
                }
            }
            clear();
            m_array = theArray;
            m_rows = ourRows;
            m_columns = theirColumns;
        }
    }
    void visualize() {
        for (int i = 0; i < m_rows; i++) {
            cout << "{ ";
            for (int v = 0; v < m_columns; v++) {
                cout << m_array[i][v] << " ";
            }
            if (i == m_rows - 1) {
                cout << "};" << endl;
            }
            else {
                cout << "}" << endl;
            }
        }
    }

    int m_rows = 0;
    int m_columns = 0;
    int** m_array = nullptr;
private: 
};

int main()
{
    int numRows = 0;
    int numColumns = 0;

    //A Setup
    numRows = 2;
    numColumns = 2;
    int** arrayA = new int*[numRows];
    for (int i = 0; i < numRows; i++) {
        arrayA[i] = new int[numColumns];
    }
    arrayA[0][0] = 6;
    arrayA[0][1] = 4;
    arrayA[1][0] = 8;
    arrayA[1][1] = 3;
    Matrix* matrixA = new Matrix(numRows, numColumns, arrayA);


    //B Setup
    numRows = 2;
    numColumns = 3;
    int** arrayB = new int* [numRows];
    for (int i = 0; i < numRows; i++) {
        arrayB[i] = new int[numColumns];
    }
    arrayB[0][0] = 1;
    arrayB[0][1] = 2;
    arrayB[0][2] = 3;
    arrayB[1][0] = 4;
    arrayB[1][1] = 5;
    arrayB[1][2] = 6;
    Matrix* matrixB = new Matrix(numRows, numColumns, arrayB);

    //C Setup
    numRows = 2;
    numColumns = 3;
    int** arrayC = new int* [numRows];
    for (int i = 0; i < numRows; i++) {
        arrayC[i] = new int[numColumns];
    }
    arrayC[0][0] = 2;
    arrayC[0][1] = 4;
    arrayC[0][2] = 6;
    arrayC[1][0] = 1;
    arrayC[1][1] = 3;
    arrayC[1][2] = 5;
    Matrix* matrixC = new Matrix(numRows, numColumns, arrayC);
    cout << "CPP:" << endl;
    cout << "The result is: " << endl;
    matrixC->transpose();
    matrixB->scalarMultiply(3);
    matrixB->multiply(matrixC);
    matrixA->add(matrixB);
    matrixA->visualize();
}
