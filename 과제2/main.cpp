/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Homework #02
 *
 *        Version:  1.0
 *        Created:  2022-09-15
 *       Revision:  none
 *       Compiler:  g++
 *
 * 	 Student Name: 
 * 	 Student ID: 
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

 /*
 * Input instructions
 * add, sub, addi, sw, lw, beq
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//CA: DO NOT CHANGE
const char *outputFileName="hw02_output.txt";
FILE *fp2 = fopen(outputFileName, "w");



int binTodecimal(int a[], int size) {
    
    int sum = 0;
    int b = 1;


    for (int i = size - 1; i >= 0; i--){
        sum = sum + (a[i] * b);
        b = b * 2;
    }
    return sum;
}



int minusTobosu(int imm[], int size){


    int immTodecimal;
    for (int i = 0; i < 12 ; i++){
        (imm[i] == 0) ? (imm[i] = 1) : (imm[i] = 0);
    }

    imm[11] += 1;


    for (int i = 11; i >= 0; i--){
        if (imm[i] == 2){
            imm[i] = 0;
            if(i != 0){
                imm[i - 1] += 1;
            }
        } else {
            break;
        }
    }
    immTodecimal = binTodecimal(imm, 12) * -1;

    return immTodecimal;
    

}


void add(int rd[5], int rs1[5], int rs2[5]){

    fprintf(fp2,"add x%d,x%d,x%d\n", binTodecimal(rd, 5),binTodecimal(rs1, 5), binTodecimal(rs2, 5));  
}

void sub(int rd[5], int rs1[5], int rs2[5]){
    fprintf(fp2, "sub x%d,x%d,x%d\n", binTodecimal(rd, 5),binTodecimal(rs1, 5), binTodecimal(rs2, 5));
}

void addi(int rd[5], int rs1[5], int fun7[7], int rs2[5]){

    int sign;
    
    int imm[12]; 
    for(int i = 0; i < 12; i++){
        if (i < 7){
            imm[i] = fun7[i];
        } else {
            imm[i] = rs2[i-7];
        }
    }

    sign = binTodecimal(imm, 12);
    if (imm[0] == 1){
        sign = minusTobosu(imm, 12);
        
    }

    fprintf(fp2, "addi x%d,x%d,%d\n",binTodecimal(rd, 5),binTodecimal(rs1, 5), sign);
    
}

void sw(int rs2[5],int fun7[7], int rd[5], int rs1[5]){

    int sign;
    int imm[12]; 
    for(int i = 0; i < 12; i++){
        if (i < 7){
            imm[i] = fun7[i];
        } else {
            imm[i] = rd[i-7];
        }
    }
    
    sign = binTodecimal(imm, 12);
    if (imm[0] == 1){
        sign = minusTobosu(imm, 12);
        
    }


    fprintf(fp2, "sw x%d,%d(x%d)\n",binTodecimal(rs2, 5), sign, binTodecimal(rs1, 5));


}

void lw(int rd[5], int fun7[7], int rs2[5], int rs1[5]){
    int sign;
    int imm[12]; 
    for(int i = 0; i < 12; i++){
        if (i < 7){
            imm[i] = fun7[i];
        } else {
            imm[i] = rs2[i-7];
        }
    }

    sign = binTodecimal(imm, 12);
    if (imm[0] == 1){
        sign = minusTobosu(imm, 12);
        
    }


    fprintf(fp2, "lw x%d,%d(x%d)\n",binTodecimal(rd, 5), sign, binTodecimal(rs1, 5));
    
}

void beq(int rs1[5], int rs2[5], int fun7[7], int rd[5]){   
    int imm[12]; 
    int sign;
    

    imm[0] = fun7[0];
    imm[1] = rd[4];


    for(int i = 2; i < 12; i++){
        if (i <= 7){          
            imm[i] = fun7[i - 1];   
        } else {           
            imm[i] = rd[i - 8];   
        }
    }

    sign = binTodecimal(imm, 12);

    if (imm[0] == 1){
        sign = minusTobosu(imm, 12);
        
    }

    fprintf(fp2, "beq x%d,x%d,%d\n", binTodecimal(rs1, 5), binTodecimal(rs2, 5),  2 * sign);


}



//CA: Please write your code
int main(){
	//CA: YOUR NAME with Student ID
	printf("Jo, Yu Dam (1942051)\n"); 

	int test, a;
    char c;
    char s[25];
    int count = 1;
    

    int op_lw[7] = {0, 0, 0, 0, 0, 1, 1};
    int op_addi[7] = {0, 0, 1, 0, 0, 1, 1};
    int op_sw[7] = {0, 1, 0, 0, 0, 1, 1};
    int op_add_sub[7] = {0, 1, 1, 0, 0, 1, 1};
    int op_beq[7] = {1, 1, 0, 0, 0, 1, 1};
    int sub_fun7[7] = {0, 1, 0, 0, 0, 0, 0};
    

	

    FILE *fp = fopen("input.txt", "r"); 
    


    fscanf(fp, "%d", &test);
    
    while (count <= test){
	
        int A[4] = {0};
        int B[32];
        
        int fun7[7];
        int rs2[5];
        int rs1[5];
        int rd[5];
        int op[7];

        int k = 0;

        for (int i = 0; i < 11; i++){
            // 16진수를 하나씩 char로 읽어낼 거야
            fscanf(fp, "%c", &c);
            // 두 번째짜리까지는 16진수임을 나타내는 수식이기에 의미없어서 무시할거야
            if (i <= 2){
                continue;
            }

            //char을 int로 읽어낸 다음 10진수로 변환할거야
            a = (int)c - 48;
            
            //알파벳들은 숫자가 크니까 빼서 나타내야해 
            if (a > 9){
                a -= 39; 
            }

            // 16진수 한 자리는 2진수 4자리를 의미하니까, A라는 int형 배열에 4자리씩 넣어줄게 
            for (int i = 3; i >= 0; i--){
                A[i] = a % 2;
                a /= 2;
            }

            // 한 instrution이 B라는 배열에 모일 수 있게 합칠거야 
            for (int i = 0; i < 4; i++){
                B[k + i]= A[i];
            }    

            k += 4;  
            // 16진수 8자리를 2진수 32자리로 변환 완료 !  
        }



        for (int i = 0; i < 32; i++){
            //printf("%d", B[i]);
            if(i <= 6){
                fun7[i] = B[i];
                //printf("%d ",fun7[i]);

            } else if (i <= 11){
                rs2[i - 7] = B[i];
                //printf("%d ",rs2[i - 7]);

            } else if (i <= 16){
                rs1[i - 12] = B[i];
                //printf("%d ",rs1[i - 12]);

            } else if (i <= 19){
                continue;

            } else if (i <= 24){
                rd[i - 20] = B[i];
                //printf("%d ",rd[i - 20]);
                
                
            } else {
                op[i - 25] = B[i];
                //printf("%d ",op[i - 25]);
            }

        }


        while (1){
            if(memcmp(op, op_lw, sizeof(op)) == 0){
                lw(rd, fun7, rs2, rs1);
                break;
            } else if(memcmp(op, op_addi, sizeof(op)) == 0){
                addi(rd, rs1, fun7, rs2);
                break;
            } else if(memcmp(op, op_sw, sizeof(op)) == 0){
                sw(rs2, fun7, rd, rs1);
                break;
            } else if(memcmp(op, op_add_sub, sizeof(op)) == 0){
                if (memcmp(fun7, sub_fun7, sizeof(fun7)) == 0){
                    sub(rd, rs1, rs2);
                    break;
                }
                add(rd, rs1, rs2);
                break;
            } else if (memcmp(op, op_beq, sizeof(op)) == 0){
                beq(rs1, rs2, fun7, rd);
                break;
            }
         
        }
    
            

        count++;   
    } 
    fclose(fp);
    fclose(fp2);

    return 0;
}