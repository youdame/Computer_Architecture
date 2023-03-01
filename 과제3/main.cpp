/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Homework #03
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
 * add, sub, addi, sw, lw
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CA: DO NOT CHANGE
const char *inputInstFile="input_inst.txt";
const char *inputRegFile="input_reg.txt";
const char *inputMemFile="input_mem.txt";
const char *outputFileName="hw03_output.txt";

const unsigned MAX_REG_SIZE = 32;
const unsigned MAX_MEM_SIZE = 1024;

// 여기에 순서대로 레지스터 값을 0번부터 31번까지 배열로 저장하면 자동으로 16진수로 변환해서 output 파일에 작성해줌
// 처음에는 전부 input 대로 삽입 후에 명령어로 인한 변경 시 해당 인덱스의 값을 바꾸면 됨
// 어차피 출력은 마지막에 하면 되니까 그렇게 하면 변경 사항이 반영됨  
// 레지스터 0번은 항상 0이어야함 변경 불가능 무조건 0으로 고정되게 조절해줘야함
unsigned Register[MAX_REG_SIZE] = {0};
unsigned Memory[MAX_MEM_SIZE] = {0};

void print_output_to_file(FILE *fp){
	for(unsigned i = 0; i < MAX_REG_SIZE; i++){
		fprintf(fp, "%08x\n", Register[i]);
	}
	for(unsigned i = 0; i < MAX_MEM_SIZE; i++){
		fprintf(fp, "%08x\n", Memory[i]);
	}
}


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

    // printf("add x%d,x%d,x%d\n", binTodecimal(rd, 5),binTodecimal(rs1, 5), binTodecimal(rs2, 5));
    
    // printf("rs1 = %d\n", Register[binTodecimal(rs1, 5)]);
    // printf("rs2 = %d\n", Register[binTodecimal(rs2, 5)]);
    
    Register[binTodecimal(rd, 5)] = Register[binTodecimal(rs1, 5)] + Register[binTodecimal(rs2, 5)];
    //printf("rd = %d\n", Register[binTodecimal(rd, 5)]);
    
}

void sub(int rd[5], int rs1[5], int rs2[5]){
    // printf("sub x%d,x%d,x%d\n", binTodecimal(rd, 5),binTodecimal(rs1, 5), binTodecimal(rs2, 5));
    // printf("rs1 = %d\n", Register[binTodecimal(rs1, 5)]);
    // printf("rs2 = %d\n", Register[binTodecimal(rs2, 5)]);
    Register[binTodecimal(rd, 5)] = Register[binTodecimal(rs1, 5)] - Register[binTodecimal(rs2, 5)];
    //printf("rd = %d\n", Register[binTodecimal(rd, 5)]);

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

    // printf("addi x%d,x%d,%d\n",binTodecimal(rd, 5),binTodecimal(rs1, 5), sign);
    // printf("rs1 = %d\n", Register[binTodecimal(rs1, 5)]);
    
    Register[binTodecimal(rd, 5)] = Register[binTodecimal(rs1, 5)] + sign;
    //printf("rd = %d\n", Register[binTodecimal(rd, 5)]);

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


    //printf("sw x%d,%d(x%d)\n",binTodecimal(rs2, 5), sign, binTodecimal(rs1, 5));
    Memory[(Register[binTodecimal(rs1, 5)] + sign)/ 4] = Register[binTodecimal(rs2, 5)];


}

void lw(int rd[5], int fun7[7], int rs2[5], int rs1[5]){
    int sign;
    int imm[12]; 
    int rs_1;
    int rd_;


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


    // printf("lw x%d,%d(x%d)\n",binTodecimal(rd, 5), sign, binTodecimal(rs1, 5));
    // printf("rs1 = %d\n", Register[binTodecimal(rs1, 5)]);
    
    
    Register[binTodecimal(rd, 5)] = Memory[(Register[binTodecimal(rs1, 5)] + sign) / 4];
    //printf("rd = %d\n", Register[binTodecimal(rd, 5)]);
    
    
}


//CA: Please write your code
int main(){
	//CA: YOUR NAME with Student ID
	printf("Jo, Yu Dam (1942051)\n");




	int test, a;
    char c;
    char s[25];
    int count = 1;
    int reg;
    int mem;

    int op_lw[7] = {0, 0, 0, 0, 0, 1, 1};
    int op_addi[7] = {0, 0, 1, 0, 0, 1, 1};
    int op_sw[7] = {0, 1, 0, 0, 0, 1, 1};
    int op_add_sub[7] = {0, 1, 1, 0, 0, 1, 1};
    int op_beq[7] = {1, 1, 0, 0, 0, 1, 1};
    int sub_fun7[7] = {0, 1, 0, 0, 0, 0, 0};
    
    char chHex[100];        
    // *** input 값 그대로 Register 배열에 삽입 *****
    // 나중에 배열의 값 수정하고 나서 한 번에 결과 출력할 예정    
    FILE *reg_fp = fopen(inputRegFile, "r"); 
    int q = 0;
    while(fgets(chHex, 100, reg_fp) != NULL){
        int number = (int)strtol(chHex, NULL, 16);
        Register[q] = number;
        q++;
    }



    // *** input 값 그대로 Memory 배열에 삽입 *****
    // 나중에 배열의 값 수정하고 나서 한 번에 결과 출력할 예정  
    q = 0;
    FILE *mem_fp = fopen(inputMemFile, "r"); 
    while (fgets(chHex, 100, mem_fp) != NULL){
        int number = (int)strtol(chHex, NULL, 16);
        Memory[q] = number;
        q++;
    }

 
	
    Register[0] = 0;

    FILE *inst_fp = fopen(inputInstFile, "r"); 
    
    fscanf(inst_fp, "%d", &test);
    
    while (count <= test){
        Register[0] = 0;
	
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
            fscanf(inst_fp, "%c", &c);
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
        
        Register[0] = 0;

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
         
        	}
		}
    
        count++;
        Register[0] = 0; 
          
    } 


	FILE *fp2 = fopen(outputFileName, "w");
	print_output_to_file(fp2);



	
    fclose(inst_fp);
	fclose(fp2);

    return 0;
}


