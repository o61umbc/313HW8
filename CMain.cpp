#include <stdio.h>
#include <stdlib.h>

void clear(int** theArray, int numRows, int numColumns) {
    for (int i = 0; i < numRows; i++) {
        free(theArray[i]);
    }
    free(theArray);
}
void add(int** array1, int rows1, int columns1, int** array2, int rows2, int columns2) {
    if (rows1 == rows2 && columns1 == columns2) {
        for (int i = 0; i < rows1; i++) {
            for (int v = 0; v < columns1; v++) {
                int theirValue = array2[i][v];
                int ourValue = array1[i][v];
                array1[i][v] = ourValue + theirValue;
            }
        }
    }
}
void scalarMultiply(int** array1, int rows1, int columns1, int theMult) {
    for (int i = 0; i < rows1; i++) {
        for (int v = 0; v < columns1; v++) {
            array1[i][v] = array1[i][v] * theMult;
        }
    }
}
int** transpose(int** array1, int rows1, int columns1) {
    int prevRows = rows1;
    int prevColumns = columns1;

    int** theArray = (int**)malloc(prevColumns * sizeof(int*));
    if (theArray == NULL) {
        return NULL;
    }
    for (int i = 0; i < prevColumns; i++) {
        theArray[i] = (int*)malloc(prevRows * sizeof(int));
        if (theArray[i] == NULL) {
            return NULL;
        }
    }
    for (int i = 0; i < columns1; i++) {
        for (int v = 0; v < rows1; v++) {
            theArray[i][v] = array1[v][i];
        }
    }
    return theArray;
}
int** multiply(int** array1, int rows1, int columns1, int** array2, int rows2, int columns2) {
    if (columns1 == rows2) {
        int ourRows = rows1;
        int ourColumns = columns1;
        int theirRows = rows2;
        int theirColumns = columns2;

        int** theArray = (int**)malloc(ourRows * sizeof(int*));
        if (theArray == NULL) {
            return NULL;
        }
        for (int i = 0; i < ourRows; i++) {
            theArray[i] = (int*)malloc(theirColumns * sizeof(int));
            if (theArray[i] == NULL) {
                return NULL;
            }
            for (int v = 0; v < theirColumns; v++) {
                theArray[i][v] = 0;
            }
        }
        for (int i = 0; i < ourRows; i++) {
            for (int v = 0; v < theirColumns; v++) {
                theArray[i][v] = 0;
                for (int a = 0; a < ourColumns; a++) {
                    theArray[i][v] += array1[i][a] * array2[a][v];
                }
            }
        }
        return theArray;
    }
    else {
        return NULL;
    }
}
void visualize(int** array1, int m_rows, int m_columns) {
    for (int i = 0; i < m_rows; i++) {
        printf("{ ");
        for (int v = 0; v < m_columns; v++) {
            printf("%d",array1[i][v]);
            printf(" ");
        }
        if (i == m_rows - 1) {
            printf("};\n");
        }
        else {
            printf("}\n");
        }
    }
}

int main() {
    int numRows = 0;
    int numColumns = 0;

    //A Setup
    numRows = 2;
    numColumns = 2;
    int** arrayA = (int**)malloc(numRows * sizeof(int*));
    if (arrayA == NULL) {
        return 1;
    }
    for (int i = 0; i < numRows; i++) {
        arrayA[i] = (int*)malloc(numColumns * sizeof(int));
        if (arrayA[i] == NULL) {
            return 1;
        }
    }
    arrayA[0][0] = 6;
    arrayA[0][1] = 4;
    arrayA[1][0] = 8;
    arrayA[1][1] = 3;



    //B Setup
    numRows = 2;
    numColumns = 3;
    int** arrayB = (int**)malloc(numRows * sizeof(int*));
    if (arrayB == NULL) {
        return 1;
    }
    for (int i = 0; i < numRows; i++) {
        arrayB[i] = (int*)malloc(numColumns * sizeof(int));
        if (arrayB[i] == NULL) {
            return 1;
        }
    }
    arrayB[0][0] = 1;
    arrayB[0][1] = 2;
    arrayB[0][2] = 3;
    arrayB[1][0] = 4;
    arrayB[1][1] = 5;
    arrayB[1][2] = 6;


    //C Setup
    numRows = 2;
    numColumns = 3;
    int** arrayC = (int**)malloc(numRows * sizeof(int*));
    if (arrayC == NULL) {
        return 1;
    }
    for (int i = 0; i < numRows; i++) {
        arrayC[i] = (int*)malloc(numColumns * sizeof(int));
        if (arrayC[i] == NULL) {
            return 1;
        }
    }
    arrayC[0][0] = 2;
    arrayC[0][1] = 4;
    arrayC[0][2] = 6;
    arrayC[1][0] = 1;
    arrayC[1][1] = 3;
    arrayC[1][2] = 5;

    int** transposedC = transpose(arrayC, 2, 3);
    scalarMultiply(arrayB, 2, 3, 3);
    int** multiplyResult = multiply(arrayB, 2, 3, transposedC, 3, 2);
    add(arrayA, 2, 2, multiplyResult, 2, 2);
    printf("The result is:\n");
    visualize(arrayA, 2, 2);

    clear(arrayA,2,2);
    clear(arrayB, 2, 2);
    clear(transposedC, 3,2);
    clear(arrayC, 2,3);
}
