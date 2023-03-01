/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Homework #01
 *
 *        Version:  1.0
 *        Created:  2022-07-23
 *       Revision:  none
 *       Compiler:  g++
 *
 * 	 Student Name: 조유담
 * 	 Student ID: 1942051
 *   Organization:  Ewha Womans University
 *
 * =====================================================================================
 */

 /*
 * ********** Please read the instructions below carefully ********** 
 * Your name and student ID must be printed when this project is executed
 * Do not print anything other than your name and student ID (Delete printf functions used for debugging when submitting this homework)
 * - If not, there will be 20% penalty
 * Run make clean command before submitting your homework
 * Change this project folder name to studentID_yourname (EX: 1234567_myungkukyoon)
 * You must compress this project folder (not the files in this folder)
 * - If not, there will be 20% penalty
 * - Use ZIP compression utility (DO NOT USE TAR COMMAND)
 * The name of ZIP file must be studentID_yourname.zip (EX: 1234567_myungkukyoon.zip)
 * All the tests must be done in 5 seconds
 * - If not, you will get 0%
 */

#include <stdio.h>

//CA: DO NOT CHANGE
const int MAX = 100;
const char *outputFileName="hw01_output.txt";

//CA: DO NOT CHANGE
int matrixOutput[MAX][MAX] = {0};

//CA: DO NOT CHANGE
void print_output_to_file(FILE *fp, int ROW, int COL){
	for(int y = 0; y < ROW; y++){
		for(int x = 0; x < COL; x++){
			fprintf(fp, "%d ", matrixOutput[y][x]);
		}
		fprintf(fp, "\n");
	}
}


int main(){
	//CA: YOUR NAME with Student ID
	printf("Jo, Yu Dam (1942051)\n"); 

	int test, n, k, m;
    int count = 1;
	
    FILE *fp = fopen("input.txt", "r"); 
    FILE *fp2 = fopen(outputFileName, "w");

    fscanf(fp, "%d", &test);
    
    while (count <= test){
        fscanf(fp, "%d %d %d", &n, &k, &m);
        int A[n][k];
        int B[k][m];

        for (int i = 0; i < n; i++){
            for (int j = 0; j < k; j++){
                fscanf(fp, "%d", &A[i][j]);
            }
        }

        for (int i = 0; i < k; i++){
            for (int j = 0; j < m; j++){
                fscanf(fp, "%d", &B[i][j]);
            }
        }

   
        int sum;


        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                sum = 0;
                for (int l = 0; l < k; l ++){
                    sum += A[i][l] * B[l][j];
                    
                }
                matrixOutput[i][j] = sum;    
            }
        }
        
        count++;

        print_output_to_file(fp2, n, m);
	

    }  
    fclose(fp);
    fclose(fp2);

    




	return true;
    

    }

