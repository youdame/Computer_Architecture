/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Homework #04
 *
 *        Version:  1.0
 *        Created:  2022-09-17
 *       Revision:  none
 *       Compiler:  g++
 *
 * 	 Student Name: 
 * 	   Student ID: 
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
#include <string.h>
#include <stdlib.h>
#include <math.h>

//CA: DO NOT CHANGE
const char *outputFileName="hw04_output.txt";


const unsigned MAX_ADDRESS_SIZE = 10000;


const unsigned MAX_BLOCK_NUMBER = 512;



unsigned long long cacheHit;
unsigned long long cacheMiss;

void init(){
	cacheHit = 0;
	cacheMiss = 0;
}

void ratio(FILE *fp){
	unsigned long long total = cacheHit + cacheMiss;
	fprintf(fp, "Hit: %3.2f\n", (float)cacheHit/total * 100);
	fprintf(fp, "Miss: %3.2f\n", (float)cacheMiss/total * 100);
}

//CA: Please write your code
int main(){
	//CA: YOUR NAME with Student 	
	printf("Jo, Yu Dam (1942051)\n"); 
	

	int test;
	int count = 1;
	
	int block_number;
	int block_size;
	int address_number;

	
	FILE *input_fp = fopen("input.txt", "r"); 
	FILE *fp = fopen(outputFileName, "w");

	// 테스트 케이스 개수 읽기
	fscanf(input_fp, "%d", &test);
	

	while (count <= test){
		unsigned Address[MAX_ADDRESS_SIZE] = {0};
		unsigned Address_index[MAX_ADDRESS_SIZE] = {0};
		unsigned Cache[MAX_BLOCK_NUMBER] = {70000};
		init();

		// test case 관련 정보 담기
		fscanf(input_fp, "%d", &block_number);
		fscanf(input_fp, "%d", &block_size);
		fscanf(input_fp, "%d", &address_number);
		

		int address_count = 1; // address 개수 카운트
		char chHex[100];  

		fgets(chHex, 100, input_fp);
		int q = 0;


		while(address_count <= address_number) {

			// input 파일에서 읽어서 16진수를 10진수로
			fgets(chHex, 100, input_fp);
			int number = (int)strtol(chHex, NULL, 16);

			//주소 배열에 주소 삽입
			Address[q] = number;


			// block_size로 나눠서 주소를 block_size 단위로 접근
			number = floor (number / block_size);

			// block_number로 나눠서 캐쉬 메모리에서의 인덱스 찾기
			number = number % block_number;

			// 인덱스로 만들어서 Address_index에 인덱스 삽입
			Address_index[q] = number;		
			

			//printf("주소[%d] = %d\n", q, Address[q]);
			//printf("주소 인덱스[%d] = %d\n", q, Address_index[q]);
			q++;
			address_count++;

		} // 주소 배열과 인덱스 배열에 값 삽입


		// 주소 하나 씩 읽어오기 
		for(int i = 0; i < address_number; i++){
			if (Cache[Address_index[i]] == Address[i]){
				//printf("cacheHit = Cache[%d], Address[%d]\n",Address_index[i] ,i);
				cacheHit++;

			} else {
				cacheMiss++;
				Cache[Address_index[i]] = Address[i];
			} 
		}



		count++;

		
		ratio(fp);
	}

	fclose(fp);
	return 1;
}
