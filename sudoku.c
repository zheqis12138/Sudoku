/* Program to assist in the challenge of solving sudoku puzzles.

   Skeleton program written by Alistair Moffat, ammoffat@unimelb.edu.au,
   August 2021, with the intention that it be modified by students
   to add functionality, as required by the assignment specification.

   Student Authorship Declaration:

   (1) I certify that except for the code provided in the initial skeleton
   file, the  program contained in this submission is completely my own
   individual work, except where explicitly noted by further comments that
   provide details otherwise.  I understand that work that has been developed
   by another student, or by me in collaboration with other students, or by
   non-students as a result of request, solicitation, or payment, may not be
   submitted for assessment in this subject.  I understand that submitting for
   assessment work developed by or in collaboration with other students or
   non-students constitutes Academic Misconduct, and may be penalized by mark
   deductions, or by other penalties determined via the University of
   Melbourne Academic Honesty Policy, as described at
   https://academicintegrity.unimelb.edu.au.

   (2) I also certify that I have not provided a copy of this work in either
   softcopy or hardcopy or any other form to any other student, and nor will I
   do so until after the marks are released. I understand that providing my
   work to other students, regardless of my intention or any undertakings made
   to me by that other student, is also Academic Misconduct.

   (3) I further understand that providing a copy of the assignment
   specification to any form of code authoring or assignment tutoring service,
   or drawing the attention of others to such services and code that may have
   been made available via such a service, may be regarded as Student General
   Misconduct (interfering with the teaching activities of the University
   and/or inciting others to commit Academic Misconduct).  I understand that
   an allegation of Student General Misconduct may arise regardless of whether
   or not I personally make use of such solutions or sought benefit from such
   actions.

   Signed by: Zheqi Shen 1254834
   Dated:     12/09/2021

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* these #defines provided as part of the initial skeleton */

#define NDIM 3		/* sudoku dimension, size of each inner square */
#define NDIG (NDIM*NDIM)
            /* total number of values in each row */
#define NGRP 3		/* number of sets each cell is a member of */
#define NSET (NGRP*NDIG)
            /* total number of sets in the sudoku */
#define NCLL (NDIG*NDIG)
            /* total number of cells in the sudoku */

#define ERROR	(-1)	/* error return value from some functions */

/* these global constant arrays provided as part of the initial skeleton,
   you may use them in your code but must not alter them in any way,
   regard them as being completely fixed. They describe the relationships
   between the cells in the sudoku and provide a basis for all of the
   sudoku processing loops */

   /* there are 27 different different sets of elements that need to be
      checked against each other, this array converts set numbers to cells,
      that's why its called s2c */
int s2c[NSET][NDIM * NDIM] = {
    /* the first group of nine sets describe the sudoku's rows */
    {  0,  1,  2,  3,  4,  5,  6,  7,  8 },
    {  9, 10, 11, 12, 13, 14, 15, 16, 17 },
    { 18, 19, 20, 21, 22, 23, 24, 25, 26 },
    { 27, 28, 29, 30, 31, 32, 33, 34, 35 },
    { 36, 37, 38, 39, 40, 41, 42, 43, 44 },
    { 45, 46, 47, 48, 49, 50, 51, 52, 53 },
    { 54, 55, 56, 57, 58, 59, 60, 61, 62 },
    { 63, 64, 65, 66, 67, 68, 69, 70, 71 },
    { 72, 73, 74, 75, 76, 77, 78, 79, 80 },
    /* the second group of nine sets describes the sudoku's columns */
    {  0,  9, 18, 27, 36, 45, 54, 63, 72 },
    {  1, 10, 19, 28, 37, 46, 55, 64, 73 },
    {  2, 11, 20, 29, 38, 47, 56, 65, 74 },
    {  3, 12, 21, 30, 39, 48, 57, 66, 75 },
    {  4, 13, 22, 31, 40, 49, 58, 67, 76 },
    {  5, 14, 23, 32, 41, 50, 59, 68, 77 },
    {  6, 15, 24, 33, 42, 51, 60, 69, 78 },
    {  7, 16, 25, 34, 43, 52, 61, 70, 79 },
    {  8, 17, 26, 35, 44, 53, 62, 71, 80 },
    /* the last group of nine sets describes the inner squares */
    {  0,  1,  2,  9, 10, 11, 18, 19, 20 },
    {  3,  4,  5, 12, 13, 14, 21, 22, 23 },
    {  6,  7,  8, 15, 16, 17, 24, 25, 26 },
    { 27, 28, 29, 36, 37, 38, 45, 46, 47 },
    { 30, 31, 32, 39, 40, 41, 48, 49, 50 },
    { 33, 34, 35, 42, 43, 44, 51, 52, 53 },
    { 54, 55, 56, 63, 64, 65, 72, 73, 74 },
    { 57, 58, 59, 66, 67, 68, 75, 76, 77 },
    { 60, 61, 62, 69, 70, 71, 78, 79, 80 },
};


/* there are 81 cells in a dimension-3 sudoku, and each cell is a
   member of three sets, this array gets filled by the function
   fill_c2s(), based on the defined contents of the array s2c[][] */
int c2s[NCLL][NGRP];

void
fill_c2s() {
    int s = 0, d = 0, c;
    for (; s < NSET; s++) {
        /* record the first set number each cell is part of */
        for (c = 0; c < NDIM * NDIM; c++) {
            c2s[s2c[s][c]][d] = s;
        }
        if ((s + 1) % (NGRP * NDIM) == 0) {
            d++;
        }
    }
#if 0
    /* this code available here if you want to see the array
       cs2[][] that gets created, just change that 0 two lines back
       to a 1 and recompile */
    for (c = 0; c < NCLL; c++) {
        printf("cell %2d: sets ", c);
        for (s = 0; s < NGRP; s++) {
            printf("%3d", c2s[c][s]);
        }
        printf("\n");
    }
    printf("\n");
#endif
    return;
}

/* find the row number a cell is in, counting from 1
*/
int
rownum(int c) {
    return 1 + (c / (NDIM * NDIM));
}

/* find the column number a cell is in, counting from 1
*/
int
colnum(int c) {
    return 1 + (c % (NDIM * NDIM));
}

/* find the minor square number a cell is in, counting from 1
*/
int
sqrnum(int c) {
    return 1 + 3 * (c / NSET) + (c / NDIM) % NDIM;
}

/* If you wish to add further #defines, put them below this comment,
   then prototypes for the functions that you add

   The only thing you should alter above this line is to complete the
   Authorship Declaration
*/


/****************************************************************/


/****************************************************************/

/* main program controls all the action
*/
#include <string.h>
#define LIST_LENGTH 10    /* How many numbers are there in interval [0,9] */
#define SET_SIZE 6    /* The size of string which is needed to store string of
                         "row 1"(for example) pattern */
#define COL_SEPERATOR "| "
#define ROW_SEPERATOR "------+-------+------\n"
#define MISS_NUM ". "
#define LAST_ITEM_MISS_NUM "."
#define TRUE 1
#define FALSE 0
#define OCUPY_SPACE 2   /* The amount of space a number or "." is needed to
                           print the formatted sudoku */
#define NUMBER_OF_VERTICAL_LINE 2    /* How many "|" is needed in each row to
                                        print the formatted sudoku */
#define NUMBER_SIZE 2    /* The size of string to store a single digit*/
#define ROW 0
#define COL 1
#define SQR 2


int formatted_input(int input_array[]);
int grid_checking(int input_array[]);
void get_set_name(int, char set_name[]);
int strategy_one(int input_array[], int*);


int
main(int argc, char* argv[]) {
    /* Read all input number into a one-dimentional array */
    int input_array[NCLL], i = 0, unknown = 0;
    while (scanf("%d", &input_array[i]) && i < NCLL) {
        i++;
    }

    /* Fill the c2s array */
    fill_c2s();
    printf("\n");
    unknown = formatted_input(input_array);   
    /* Continue if the sudoku is valid */
    if (!grid_checking(input_array)) {
        /* Run strategy one until no cell can be filled or all cell has
           been filled */
        while (strategy_one(input_array, &unknown)) {
        }

        printf("\n");
        unknown = formatted_input(input_array);
        if (!unknown) {
            printf("\n\nta daa!!!\n");
        }
        else {
            printf("\n");
        }
    }

    /* all done, so pack up bat and ball and head home */
    return 0;
}

/****************************************************************/

/* Print the formatted sudoku from input array*/
int formatted_input(int input_array[]) {
    int j = 0, unknown = 0;
    for (int row = 0;row < NDIG;row++) {
        /* Print "-" character */
        if (row != 0 && row % NDIM == 0) {
            printf(ROW_SEPERATOR);
        }

        /* Print "|" and new line character */
        for (int col = 0;col < NDIG;col++) {
            if (col != 0 && col % NDIM == 0) {
                printf(COL_SEPERATOR);
            }

            /* Print number and ".", exclude the whitespace if reach the end
               of the row */
            if (col == NDIG - 1) {
                if (input_array[j]) {
                    printf("%d", input_array[j]);
                }

                else {
                    printf(LAST_ITEM_MISS_NUM);
                    unknown += 1;
                }
            }

            /* Include the whitespace if not reach the end of the row */
            else {
                if (input_array[j]) {
                    printf("%d ", input_array[j]);
                }

                else {
                    printf(MISS_NUM);
                    unknown += 1;
                }
            }
            j++;
        }
        printf("\n");
    }

    /* Print the summary line */
    printf("\n%2d cells are unknown", unknown);
    return unknown;
}


/* Do stage2 grid checking*/
int grid_checking(int input_array[]) {
    int value = 0, set = 0, violations = 0, violation_sets = 0;
    char set_name[SET_SIZE];
    printf("\n");
    /* Go through every set and check if there is duplication inside */
    for (;set < NSET;set++) {
        /* Initialise a tally A to count how many times each number appear
           in the set */
        int A[LIST_LENGTH] = { 0 }, is_violation_set = FALSE;
        for (int j = 0;j < NDIG;j++) {
            /* Check which value is inside the set, add one for the coresponding
               index in A */
            int index = s2c[set][j];
            value = input_array[index];
            A[value]++;
        }

        /* Check is there is a number appears more than once in one set and
           print the information */
        for (int k = 0;k < LIST_LENGTH;k++) {
            if (k > 0 && A[k] > 1) {
                violations++;
                is_violation_set = TRUE;
                get_set_name(set, set_name);
                printf("\nset %2d (%s): %d instances of %d", set, set_name, \
                    A[k], k);
            }
        }

        /* Count the total number of violation set */
        if (is_violation_set) {
            violation_sets++;
        }
    }

    if (violations) {
        printf("\n\n%d different sets have violations\n%d violations in total\n", \
            violation_sets, violations);
    }

    return violations;
}


/* The function recieve the index of a set and find which specific
       row/column/square the set is in and store the information in set_name
       string */
void get_set_name(int set_num, char set_name[]) {
    int index = (set_num) % (NDIM * NDIM) + 1;
    char num_to_str[NUMBER_SIZE];
    if ((set_num) / (NDIM * NDIM) == ROW) {
        strcpy(set_name, "row ");
        sprintf(num_to_str, "%d", index);
        strcat(set_name, num_to_str);
    }

    else if ((set_num) / (NDIM * NDIM) == COL) {
        strcpy(set_name, "col ");
        sprintf(num_to_str, "%d", index);
        strcat(set_name, num_to_str);
    }

    else {
        strcpy(set_name, "sqr ");
        sprintf(num_to_str, "%d", index);
        strcat(set_name, num_to_str);
    }
}


/* Do strategy to the sudoku array */
int strategy_one(int input_array[], int* unknown) {
    int row_located = 0, col_located = 0, sqr_located = 0,
        exist_num1 = 0, exist_num2 = 0, exist_num3 = 0, amount_filled = 0,
        row_index = 0, col_index = 0, filled_number[NCLL] = { 0 };
    /* Go through every unfilled cell and find the possible number remaining */
    for (int cell = 0;cell < NCLL;cell++) {
        int candidate_array[LIST_LENGTH] = { 0 },
            number_available = 0, available_amount = 0;
        /*Get the set number of row, column and square which contain the cell */
        if (input_array[cell] == 0) {
            row_located = c2s[cell][ROW];
            col_located = c2s[cell][COL];
            sqr_located = c2s[cell][SQR];
            /* Check which number has appeared in its cellmate */
            for (int i = 0;i < NDIG;i++) {
                exist_num1 = input_array[s2c[row_located][i]];
                exist_num2 = input_array[s2c[col_located][i]];
                exist_num3 = input_array[s2c[sqr_located][i]];
                candidate_array[exist_num1]++;
                candidate_array[exist_num2]++;
                candidate_array[exist_num3]++;
            }

            /* Check how which number and how many numbers are available
               to the cell */
            for (int j = 0;j < LIST_LENGTH;j++) {
                if (candidate_array[j] == 0 && j != 0) {
                    number_available = j;
                    available_amount++;
                }
            }

            /* If there is exactly one number available to the cell, store the
               number in the corresponding index in a temporary array and
               record a successful fill in amount_filled variable*/
            if (available_amount == 1) {
                filled_number[cell] = number_available;
                amount_filled++;
                *unknown = *unknown - 1;
            }
        }
    }

    /* Print strategy if there exists some cells which can be filled */
    if (amount_filled) {
        printf("\nstrategy one\n");
    }

    /* Fill the sudoku array from the temporary array and print the
       information */
    for (int k = 0;k < NCLL;k++) {
        if (filled_number[k]) {
            row_index = rownum(k);
            col_index = colnum(k);
            printf("row %d col %d must be %d\n", row_index, col_index, \
                filled_number[k]);
            input_array[k] = filled_number[k];
        }
    }

    return amount_filled;
}

/* algorithms are fun! */




