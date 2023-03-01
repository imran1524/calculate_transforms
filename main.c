#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

#define MAX 100000

unsigned int p = 7;
time_t t;
int N = 8;
//int N = 16;
int *input_block_in_elements;

int *calculate_NMNT(int *plaintext, int N, int M_p);
int *calculate_ONMNT(int *plaintext, int N, int M_p);
int *calculate_O2NMNT(int *plaintext, int N, int M_p);
int *calculate_FNT(char *plaintext[N], int t);

//FUNCTION SIGNATURES
//FUNCTION SIGNATURE TO ALLOCATE 2D ARRAY
int **memory_allocation_for_2D_array(int row_numbers, int column_numbers);

//FUNCTION SIGNATURE OF FREE 2D ARRAY POINTER
void free_2D_array(int **array_2D, int x_length);

int mod(int input, int Mp);
//THIS FUNCTION CONVERTS STRING OR CHARACTER ARRAY INTO BINARY STRINGS

char* string_to_binary(char* s);

//FNT
int *alpha_n_k;
struct array_object {
    int *array;
    int array_size;
};
struct array_object power(int x, int n);
int multiply(int x, int res[], int res_size);
struct array_object multiply_two_arrays(int *a,int l1, char *plaintext);
int *reverse_array(int *array, int array_size);
struct array_object add_two_arrays(int *array_1, int array_1_size, int *array_2, int array_2_size);
int calculate_module(int *X_k, int array_size, int F_t);
struct array_object divide_arrays(int *dividend, int dividend_size, int divisor);

//FNT

int main() {
    int Mp = (1 << p)-1;
    //char message[8] = {'A','n', 'a','l','y','s','i','s'};
//    char message[8] = {0,' ',' ',' ',' ',' ',' ',' '};
    //    char *plaintext_FNT[8] = {"65", "110", "97", "108", "121", "115", "105", "115"};

int x_n[8] = {65, 110, 97, 108, 121, 115, 105, 115};
//int x_n[16] = {0, 106, 36, 68, 116, 26, 0, 50, 100, 13, 50,  93, 107, 9, 9, 36};

    int *plaintext = x_n;


//    output_FNT[0] = 110
//    output_FNT[1] = 77
//    output_FNT[2] = 166
//    output_FNT[3] = 6
//    output_FNT[4] = 66
//    output_FNT[5] = 204
//    output_FNT[6] = 8
//    output_FNT[7] = 227

//    char plaintext[3][8] =
//{
//  {'6','5','\0'},
//  {'1','1','0'\0'},
//  {'9','7'\0'},
//  {'1','0','8'\0'},
//  {'1','2','1'\0'},
//  {'1','1','5'\0'},
//  {'1','0','5'\0'},
//  {'1','1','5'\0'},
//};

    //TESTING THE NMNT FUNCTION
    int *output_NMNT = (int *) calloc(N, sizeof(int));

    for(int i = 0; i < N; i++){
        printf("plaintext = %d\n", plaintext[i]);
    }

    //CALCULATE NMNT
    output_NMNT = calculate_NMNT(plaintext, N, Mp);

    printf("NMNT:\n");
    for(int i = 0; i < N; i++){
        printf("output_NMNT[%d] = %d\n", i, output_NMNT[i]);
    }
    printf("\n");

    int *output_ONMNT = (int *) calloc(N, sizeof(int));

    //CALCULATE ONMNT
    output_ONMNT = calculate_ONMNT(plaintext, N, Mp);

    printf("ONMNT:\n");
    for(int i = 0; i < N; i++){
        printf("output_ONMNT[%d] = %d\n", i, output_ONMNT[i]);
    }

    printf("\n");

    int *output_O2NMNT = (int *) calloc(N, sizeof(int));

    //CALCULATE O2NMNT
    output_O2NMNT = calculate_O2NMNT(plaintext, N, Mp);

    printf("O2NMNT:\n");
    for(int i = 0; i < N; i++){
        printf("output_O2NMNT[%d] = %d\n", i, output_O2NMNT[i]);
    }
    printf("\n");

    //CALCULATE FNT
    //CALCULATE FNT
    printf("FNT:\n");
    char** plaintext_FNT = memory_allocation_for_2D_array(N,N);

    for(int index = 0; index < N; index++){
//            printf("test_plaintext[%d] = %d\n", index, test_plaintext[index]);
        sprintf(plaintext_FNT[index], "%d", plaintext[index]);
//            printf("%s\n", plaintext_FNT[i]);
    }

    for(int i = 0; i < N ; i++){
        for(int j = 0; j < 3; j++){
                printf("plaintext_FNT[%d][%d] = %c\n", i, j, plaintext_FNT[i][j]);
        }
//            printf("\n");
    }


//    char **output_FNT = calculate_FNT(plaintext_FNT, 3);

    printf("FNT:\n");
    int *X_k = (int *) calloc(N, sizeof(int));
    X_k = calculate_FNT(plaintext_FNT, 3);
    for(int i = 0; i < N; i++){
        printf("output_FNT[%d] = %d\n", i, X_k[i]);
    }
    return 0;

}

//THIS FUNCTION CONVERTS STRING OR CHARACTER ARRAY INTO BINARY STRINGS
char* string_to_binary(char* s) {
    if(s == NULL){
        return 0; /* no input string */
    }
    size_t len = strlen(s); //Length of the string
    char *binary = malloc(len*8 + 1); // each char is one byte (8 bits) and + 1 at the end for null terminator
    binary[0] = '\0';

    for(size_t i = 0; i < len; ++i) {
        char ch = s[i];
        for(int j = 7; j >= 0; --j){
            if(ch & (1 << j)) {
                strcat(binary,"1");
            } else {
                strcat(binary,"0");
            }
        }
    }
    return binary;
}

    //FUNCTION DECLARATION TO ALLOCATE MEMORY FOR 2D ARRAY
    int **memory_allocation_for_2D_array(int row_numbers, int column_numbers){
        int **ptr_2D_array;
        ptr_2D_array = (int **) calloc(row_numbers, sizeof(int *));
        for(int i = 0; i < row_numbers; i++){
            ptr_2D_array[i] = (int *) calloc(column_numbers, sizeof(int));
        }
        return ptr_2D_array;
    }

    //FUNCTION DECLARATION OF FREE 2D ARRAY POINTER
    void free_2D_array(int **array_2D, int x_length){
        size_t i;
        for(i = 0; i < x_length; i++){
            if(array_2D != NULL){
                free(array_2D[i]);
            }
        }
        free(array_2D);
    }

    int *calculate_NMNT(int *plaintext, int N, int M_p) {
        int *output = (int *) calloc(N, sizeof(int));
        int **ptr_NMNT = memory_allocation_for_2D_array(N,N);
        if(N == 8) {
            int NMNT[8][8] = {
                    {1, 1,   1,   1,   1,   1,   1,   1},
                    {1, 111, 1,   0,   126, 16,  126, 0},
                    {1, 1,   126, 126, 1,   1,   126, 126},
                    {1, 0,   126, 111, 126, 0,   1,   16},
                    {1, 126, 1,   126, 1,   126, 1,   126},
                    {1, 16,  1,   0,   126, 111, 126, 0},
                    {1, 126, 126, 1,   1,   126, 126, 1},
                    {1, 0,   126, 16,  126, 0,   1,   111}
            };
            for(int i = 0; i < N; i++){
                for(int j = 0; j < N; j++){
                    ptr_NMNT[i][j] = NMNT[i][j];
//                    printf("ptr_NMNT[%d][%d] = %d\n", i,j,ptr_NMNT[i][j]);
                }
            }

    }else if(N == 16) {
//ONMNT matrix for p = 7 and N = 16
            int NMNT[16][16] = {
                    {1, 1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1},
                    {1, 82,  111, 82,  1,   3,   0,   124, 126, 45,  16,  45,  126, 124, 0,   3},
                    {1, 111, 1,   0,   126, 16,  126, 0,   1,   111, 1,   0,   126, 16,  126, 0},
                    {1, 82,  0,   45,  126, 3,   111, 3,   126, 45,  0,   82,  1,   124, 16,  124},
                    {1, 1,   126, 126, 1,   1,   126, 126, 1,   1,   126, 126, 1,   1,   126, 126},
                    {1, 3,   16,  3,   1,   45,  0,   82,  126, 124, 111, 124, 126, 82,  0,   45},
                    {1, 0,   126, 111, 126, 0,   1,   16,  1,   0,   126, 111, 126, 0,   1,   16},
                    {1, 124, 0,   3,   126, 82,  16,  82,  126, 3,   0,   124, 1,   45,  111, 45},
                    {1, 126, 1,   126, 1,   126, 1,   126, 1,   126, 1,   126, 1,   126, 1,   126},
                    {1, 45,  111, 45,  1,   124, 0,   3,   126, 82,  16,  82,  126, 3,   0,   124},
                    {1, 16,  1,   0,   126, 111, 126, 0,   1,   16,  1,   0,   126, 111, 126, 0},
                    {1, 45,  0,   82,  126, 124, 111, 124, 126, 82,  0,   45,  1,   3,   16,  3},
                    {1, 126, 126, 1,   1,   126, 126, 1,   1,   126, 126, 1,   1,   126, 126, 1},
                    {1, 124, 16,  124, 1,   82,  0,   45,  126, 3,   111, 3,   126, 45,  0,   82},
                    {1, 0,   126, 16,  126, 0,   1,   111, 1,   0,   126, 16,  126, 0,   1,   111},
                    {1, 3,   0,   124, 126, 45,  16,  45,  126, 124, 0,   3,   1,   82,  111, 82}
            };
            for(int i = 0; i < N; i++){
                for(int j = 0; j < N; j++){
                    ptr_NMNT[i][j] = NMNT[i][j];
//                    printf("ptr_NMNT[%d][%d] = %d\n", i,j,ptr_NMNT[i][j]);
                }
            }
    }

    for (int row = 0; row < N; row++) {
        signed long long result = 0;
        signed long long sum = 0;
        for (int col = 0; col < N; col++) {
//        printf("plaintext[%d] = %d\n", row, plaintext[col]);
//                 printf("ptr_NMNT[%d][%d] = %d\n", row, col, ptr_NMNT[row][col]);
                sum = plaintext[col] * ptr_NMNT[row][col];
                result = result + sum;
//                printf("result = %d\n", result);
        }
        output[row] = mod(result, M_p);

//        output[row] = result % 127;
    }
    return output;
}


//CALCULATING ONMNT
int *calculate_ONMNT(int *plaintext, int N, int M_p) {
    int *output = (int *) calloc(N, sizeof(int));
    int **ptr_ONMNT = memory_allocation_for_2D_array(N,N);

    //ONMNT matrix for p = 7 and N = 8
    if(N == 8) {
        int ONMNT[8][8] = {
                {1, 1, 1, 1, 1, 1, 1, 1},
                {72, 19, 19, 72, 5, 99, 28, 122},
                {82, 82, 3, 124, 45, 45, 124, 3},
                {19, 5, 122, 108, 28, 72, 72, 28},
                {111, 0, 16, 0, 111, 0, 16, 0},
                {19, 122, 122, 19, 28, 55, 72, 99},
                {82, 45, 3, 3, 45, 82, 124, 124},
                {72, 108, 19, 55, 5, 28, 28, 5}
        };
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                ptr_ONMNT[i][j] = ONMNT[i][j];
//                    printf("ptr_NMNT[%d][%d] = %d\n", i,j,ptr_NMNT[i][j]);
            }
        }

    }else if(N == 16) {

        int ONMNT[16][16] = {
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                {72, 19, 19, 72, 5, 99, 28, 122, 55, 108, 108, 55, 122, 28, 99, 5},
                {82, 82, 3, 124, 45, 45, 124, 3, 82, 82, 3, 124, 45, 45, 124, 3},
                {19, 5, 122, 108, 28, 72, 72, 28, 108, 122, 5, 19, 99, 55, 55, 99},
                {111, 0, 16, 0, 111, 0, 16, 0, 111, 0, 16, 0, 111, 0, 16, 0},
                {19, 122, 122, 19, 28, 55, 72, 99, 108, 5, 5, 108, 99, 72, 55, 28},
                {82, 45, 3, 3, 45, 82, 124, 124, 82, 45, 3, 3, 45, 82, 124, 124},
                {72, 108, 19, 55, 5, 28, 28, 5, 55, 19, 108, 72, 122, 99, 99, 122},
                {1, 126, 1, 126, 1, 126, 1, 126, 1, 126, 1, 126, 1, 126, 1, 126},
                {5, 28, 28, 5, 55, 19, 108, 72, 122, 99, 99, 122, 72, 108, 19, 55},
                {3, 3, 45, 82, 124, 124, 82, 45, 3, 3, 45, 82, 124, 124, 82, 45},
                {99, 72, 55, 28, 19, 122, 122, 19, 28, 55, 72, 99, 108, 5, 5, 108},
                {0, 111, 0, 16, 0, 111, 0, 16, 0, 111, 0, 16, 0, 111, 0, 16},
                {28, 72, 72, 28, 108, 122, 5, 19, 99, 55, 55, 99, 19, 5, 122, 108},
                {124, 3, 82, 82, 3, 124, 45, 45, 124, 3, 82, 82, 3, 124, 45, 45},
                {122, 28, 99, 5, 72, 19, 19, 72, 5, 99, 28, 122, 55, 108, 108, 55}
        };


        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                ptr_ONMNT[i][j] = ONMNT[i][j];
//                    printf("ptr_NMNT[%d][%d] = %d\n", i,j,ptr_NMNT[i][j]);
            }
        }
    }

    for (int row = 0; row < N; row++) {
        signed long long result = 0;
        signed long long sum = 0;
        for (int col = 0; col < N; col++) {
//        printf("plaintext[%d] = %d\n", row, plaintext[col]);
//                 printf("ptr_NMNT[%d][%d] = %d\n", row, col, ptr_NMNT[row][col]);
            sum = plaintext[col] * ptr_ONMNT[row][col];
            result = result + sum;
//                printf("result = %d\n", result);
        }
        output[row] = mod(result, M_p);
//        output[row] = result % 127;
    }
    return output;
}

//CALCULATING ONMNT
int *calculate_O2NMNT(int *plaintext, int N, int M_p) {
    int *output = (int *) calloc(N, sizeof(int));
    int **ptr_O2NMNT = memory_allocation_for_2D_array(N,N);

    //ONMNT matrix for p = 7 and N = 8
    if(N == 8) {
        int O2NMNT[8][8] =
                    {
                        {72, 19, 19, 72, 5, 99, 28, 122},
                        {19, 5, 122, 108, 28, 72, 72, 28},
                        {19, 122, 122, 19, 28, 55, 72, 99},
                        {72, 108, 19, 55, 5, 28, 28, 5},
                        {5, 28, 28, 5, 55, 19, 108, 72},
                        {99, 72, 55, 28, 19, 122, 122, 19},
                        {28, 72, 72, 28, 108, 122, 5, 19},
                        {122, 28, 99, 5, 72, 19, 19, 72}
                    };
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                ptr_O2NMNT[i][j] = O2NMNT[i][j];
//                    printf("ptr_NMNT[%d][%d] = %d\n", i,j,ptr_NMNT[i][j]);
            }
        }

    }else if(N == 16) {
//O2NMNT matrix for p = 7 and N = 16
        int O2NMNT[16][16] = {
                            {15, 56, 106, 105, 105, 106, 56, 15, 83, 26, 14, 36, 91, 113, 101, 44},
                            {56, 105, 15, 14, 113, 112, 22, 71, 101, 36, 83, 106, 106, 83, 36, 101},
                            {106, 15, 91, 71, 71, 91, 15, 106, 14, 44, 22, 101, 26, 105, 83, 113},
                            {105, 14, 71, 44, 83, 56, 113, 22, 91, 106, 26, 112, 112, 26, 106, 91},
                            {105, 113, 71, 83, 83, 71, 113, 105, 91, 21, 26, 15, 112, 101, 106, 36},
                            {106, 112, 91, 56, 71, 36, 15, 21, 14, 83, 22, 26, 26, 22, 83, 14},
                            {56, 22, 15, 113, 113, 15, 22, 56, 101, 91, 83, 21, 106, 44, 36, 26},
                            {15, 71, 106, 22, 105, 21, 56, 112, 83, 101, 14, 91, 91, 14, 101, 83},
                            {83, 101, 14, 91, 91, 14, 101, 83, 112, 56, 21, 105, 22, 106, 71, 15},
                            {26, 36, 44, 106, 21, 83, 91, 101, 56, 22, 15, 113, 113, 15, 22, 56},
                            {14, 83, 22, 26, 26, 22, 83, 14, 21, 15, 36, 71, 56, 91, 112, 106},
                            {36, 106, 101, 112, 15, 26, 21, 91, 105, 113, 71, 83, 83, 71, 113, 105},
                            {91, 106, 26, 112, 112, 26, 106, 91, 22, 113, 56, 83, 44, 71, 14, 105},
                            {113, 83, 105, 26, 101, 22, 44, 14, 106, 15, 91, 71, 71, 91, 15, 106},
                            {101, 36, 83, 106, 106, 83, 36, 101, 71, 22, 112, 113, 14, 15, 105, 56},
                            {44, 101, 113, 91, 36, 14, 26, 83, 15, 56, 106, 105, 105, 106, 56, 15}
        };

        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                ptr_O2NMNT[i][j] = O2NMNT[i][j];
//                    printf("ptr_NMNT[%d][%d] = %d\n", i,j,ptr_NMNT[i][j]);
            }
        }
    }

    for (int row = 0; row < N; row++) {
        signed long long result = 0;
        signed long long sum = 0;
        for (int col = 0; col < N; col++) {
//        printf("plaintext[%d] = %d\n", row, plaintext[col]);
//                 printf("ptr_NMNT[%d][%d] = %d\n", row, col, ptr_NMNT[row][col]);
            sum = plaintext[col] * ptr_O2NMNT[row][col];
            result = result + sum;
//                printf("result = %d\n", result);
        }
        output[row] = mod(result, M_p);
//        output[row] = result % 127;
    }
    return output;
}

int mod(int input, int Mp){
    int result = input % Mp;
    if (result < 0) {
        result += Mp;
    }
    return result;
}


//FNT FUNCTION DECLARATIONS
//Function of multiplying two arrays
struct array_object multiply_two_arrays(int *a,int l1, char *plaintext){

    struct array_object product_of_array;
//        int a[100],b[100];
    int b[100];
//        int ans[200] = {0};

    int i, j, tmp;
    int l2 = strlen(plaintext);

//
    for(i = l2-1,j=0;i>=0;i--,j++){
        b[j] = plaintext[i]-'0';
    }

    for(i = 0; i < l1; i++){
//            printf("alpha_n_k[%d] = %d\n", i, a[i]);
    }

    for(i = 0; i < l2; i++){
//            printf("x_n[%d] = %d\n", i, b[i]);
    }
    int *ans = (int *)calloc((l1+l2), sizeof (int));
    for(i = 0;i < l2;i++){
        for(j = 0;j < l1;j++){
            ans[i+j] += b[i]*a[j];
        }
    }

    for(i = 0;i < l1+l2;i++){
        tmp = ans[i]/10;
        ans[i] = ans[i]%10;
        ans[i+1] = ans[i+1] + tmp;
    }

    for(i = l1+l2; i>= 0;i--){
        if(ans[i] > 0){
            break;
        }
    }
    product_of_array.array = ans;
    product_of_array.array_size = l1+l2;
    return product_of_array;
}

// This function multiplies x with the number represented by res[].
// res_size is size of res[] or
// number of digits in the number
// represented by res[].
// This function uses simple school mathematics for multiplication.
// This function may value of res_size and returns the new value of res_size
int multiply(int x, int res[], int res_size){
    // Initialize carry
    int carry = 0;

    // One by one multiply n with
    // individual digits of res[]
    for (int i = 0; i < res_size; i++){
        int prod = res[i] * x + carry;

        // Store last digit of 'prod' in res[]
        res[i] = prod % 10;

        // Put rest in carry
        carry = prod / 10;
    }

    // Put carry in res and increase result size
    while (carry){
        res[res_size] = carry % 10;
        carry = carry / 10;
        res_size++;
    }
    return res_size;
}

//FUNCTION TO CALCULATE POWER OF A NUMBER x
struct array_object power(int x, int n) {
    struct array_object array_input;
    array_input.array = (int *) calloc(MAX, sizeof(int));
    array_input.array_size = 0;
    int *res = (int *) calloc(MAX, sizeof(int));
    int res_size = 0;
    int temp = x;

    // Initialize result
    while (temp != 0) {
        res[res_size++] = temp % 10;
        temp = temp / 10;
    }

    // printing value "1" for power = 0
    if (n == 0) {
        res[0] = 1;
    }
    // Multiply x n times (x^n = x*x*x....n times)
    // The loop start from 2 as i = 2, it means x^2 = x * x
    // i = 0: x^0 = 1
    // i = 1: x ^ 1 = x

    for (int i = 2; i <= n; i++) {
        res_size = multiply(x, res, res_size);
    }
    array_input.array = res;
    array_input.array_size = res_size;
    return array_input;
}
//FUNCTION DECLARATION TO REVERSE THE ARRAY
int *reverse_array(int *array, int array_size){
    int *temp_array = (int *) calloc(array_size, sizeof(int));
    for(int  i = 0; i < array_size; i++){
        temp_array[array_size-1-i] = array[i];
    }
    for(int  i = 0; i < array_size; i++){
        array[i] = temp_array[i];
    }
    return array;
}

//FUNCTION DECLARATION TO ADD TWO DYNAMIC ARRAYS
struct array_object add_two_arrays(int *array_1, int array_1_size, int *array_2, int array_2_size){
    int carry = 0;
    int temp_sum = 0;
    int *sum = (int *) calloc(100, sizeof(int));
    int sum_size;
    int index;

    struct array_object result;
//    printf("array_1_size = %d\n", array_1_size);
//    printf("array_2_size = %d\n", array_2_size);
    if(array_1_size <= array_2_size){
        //ADDING TWO ARRAYS WHEN SIZE OF FIRST ARRAY IS EQUAL OR SMALLER THAN SECOND ARRAY
//        printf("Condition #1: array_1_size <= array_2_size\n");
        array_1 = reverse_array(array_1, array_1_size);
        array_2 = reverse_array(array_2, array_2_size);

        for(index = 0; index < array_1_size; index++){
            temp_sum = ((array_1[index] + array_2[index]) + carry);
//            printf("%d + %d + %d = %d\n", array_1[index], array_2[index], carry, temp_sum);
            sum[index] = temp_sum % 10;
//            printf("sum[%d] = %d\n", index, sum[index]);
            carry = (temp_sum >= 10)? 1:0;
//            printf("carry = %d\n", carry);
        }

        for(index = array_1_size; index < array_2_size; index++){
            temp_sum = (array_2[index] + carry);
//            printf("temp_sum = %d\n", temp_sum);
            sum[index] = temp_sum % 10;
//            printf("sum[%d] = %d\n", index, sum[index]);
            carry = (temp_sum >= 10)? 1:0;
        }

        if(carry){
//            printf("carry = %d\n", carry);
//            printf("index = %d\n", index);
            sum[index] = carry;
//            printf("sum[%d] = %d\n", index, sum[index]);
            result.array_size = index + 1;
        } else{
            result.array_size = index;
        }
    }else if(array_1_size > array_2_size){
        //ADDING TWO ARRAYS WHEN SIZE OF FIRST ARRAY IS SMALLER THAN SECOND ARRAY
//        printf("Condition #2: array_1_size > array_2_size\n");//
        array_1 = reverse_array(array_1, array_1_size);
        array_2 = reverse_array(array_2, array_2_size);

        for(index = 0; index < array_2_size; index++){
            temp_sum = ((array_1[index] + array_2[index]) + carry);
            sum[index] = temp_sum % 10;
            carry = (temp_sum >= 10)? 1:0;
        }

        for(index = array_2_size; index < array_1_size; index++){ //i = 1, 2
            temp_sum = (array_1[index] + carry);
            sum[index] = temp_sum % 10;
            carry = (temp_sum >= 10)? 1:0;
        }

        if(carry){
//            printf("carry = %d\n", carry);
            sum[index] = carry;
//            printf("sum[%d] = %d\n", index, sum[index]);
            result.array_size = index + 1;
        } else{
            result.array_size = index;
        }

//        printf("result.array_size = %d\n", result.array_size);
    }

    for(int i = 0; i < result.array_size; i++){
//        printf("sum[%d] = %d\n", i, sum[i]);
    }
    result.array = reverse_array(sum, result.array_size);
    result.array = sum;
    return result;
}

//FUNCTION DECLARATION OF CALCULATING MOD Ft
int calculate_module(int *X_k, int array_size, int F_t){
    long long int temp = 0;
    for(int i = 0; i < array_size; i++){
        temp = (10 * temp) + X_k[i];
        //printf("%d = 10 * %d + %d\n", temp, temp, X_k[i]);
        temp %= F_t;
//        printf("temp = %d\n", temp);
    }
    return  temp;
}

struct array_object divide_arrays(int *dividend, int dividend_size, int divisor){
    struct array_object result_array;
    int *result = (int *)calloc(dividend_size, sizeof(int));
    int index = 0;
    for(int i = 0; i < dividend_size; i++){
        result[index] = dividend[i]/divisor;
        dividend[i+1] = dividend[i+1] + ((dividend[i] % divisor) * 10);
        index++;
    }
    result_array.array_size = index;
    result_array.array = result;
    return result_array;
}

int* calculate_FNT(char *plaintext[N], int t){
    int F_t = (1 << (1 << t)) + 1;// Ft = 2^(2^t)
    int *X_k = (int *) calloc(N, sizeof(int));
    //    printf("F_t = %d\n", F_t);
    int *temp_X;
    int temp_X_size;
    int alpha = 4;


    //     char *plaintext[N] = {"65", "119", "16", "238", "197", "27", "209", "163"};
    struct array_object sum_result;
    int alpha_nk_size;
    int product_size;
    struct array_object output_from_function;
    struct array_object output_of_product;
    struct array_object temp_sum;
    //---------------------
    for (int k = 0; k < N; k++) {
        //        printf("k = %d\n", k);
        //ASSIGNMENT OF INITIAL VALUES FOR temp_sum FOR ADDING TWO ARRAYS
        temp_sum.array_size = 2;
        temp_sum.array = (int *) calloc(temp_sum.array_size, sizeof(int));
        for (int i = 0; i < temp_sum.array_size; i++) {
            temp_sum.array[i] = 0;
        }
        for (int n = 0; n < N; n++) {
            //calculation of alpha^(n*k)
            //            printf("n = %d\n", n);
            //            printf("nk = %d\n", n * k);

            //CALCULATION OF alpha_n_k
            output_from_function = power(alpha, n * k);
            alpha_nk_size = output_from_function.array_size;
            alpha_n_k = (int *) calloc(alpha_nk_size, sizeof(int));
            alpha_n_k = output_from_function.array;

            for (int i = 0; i < alpha_nk_size; i++) {
                //                printf("alpha_n_k[%d] = %d\n", i, alpha_n_k[i]);
            }

            //CALCULATE THE MULTIPLICATION OF EACH PRODUCT TERM FOR X(k)]
            output_of_product = multiply_two_arrays(alpha_n_k, alpha_nk_size, plaintext[n]);
            temp_X_size = output_of_product.array_size;
            temp_X = (int *) calloc(temp_X_size, sizeof(int));
            temp_X = output_of_product.array;

            //CALLING REVERSE FUNCTION TO REVERSE temp_X TO MATCH WITH PLAINTEXT ARRAY INDEXING e.g. MSB AT O ARRAY INDEX
            temp_X = reverse_array(temp_X, temp_X_size);
            //            printf("temp_X_size = %d\n", temp_X_size);
            for (int i = 0; i < temp_X_size; i++) {
                //                printf("temp_X[%d] = %d\n", i, temp_X[i]);
            }

            //CALLING FUNCTION TO ADD TWO DYNAMIC ARRAYS
            temp_sum = add_two_arrays(temp_X, temp_X_size, temp_sum.array, temp_sum.array_size);
            temp_sum.array = temp_sum.array;
            temp_sum.array_size = temp_sum.array_size;

            for (int i = 0; i < temp_sum.array_size; i++) {
                //                printf("temp_sum.array[%d] = %d\n", i, temp_sum.array[i]);
            }
            //            printf("--------------------------------------------------------------------------------\n");
        }
        //        struct array_object i_temp_sum;
        //        i_temp_sum = divide_arrays(temp_sum.array, temp_sum.array_size, N);
        X_k[k] = calculate_module(temp_sum.array, temp_sum.array_size, F_t);
        //        X_k = calculate_module( i_temp_sum.array,  i_temp_sum.array_size, F_t);

//        printf("X_k[%d] = %d\n",k, X_k[k]);
    }
    return X_k;
} //END OF MAIN FUNCTION