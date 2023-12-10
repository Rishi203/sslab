#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(){
    int start,locctr,length;
    char label[10],opcode[10],operand[10],code[10],mnemonic[10];
    
    FILE *fp1,*fp2,*fp3,*fp4,*fp5;
    fp1 = fopen("input.txt","r");
    fp2 = fopen("optab.txt","r");
    fp3 = fopen("symtab.txt","w");
    fp4 = fopen("intermediate.txt","w");
    fp5 = fopen("length.txt","w");
    // read first line
    fscanf(fp1, "%s\t%s\t%s",label,opcode,operand);
    printf(label,opcode,operand);
    // check if start
    if(strcmp(opcode,"START")==0){
        start = atoi(operand);
        locctr = start;
        fprintf(fp4,"\t%s\t%s\t%s\n",label,opcode,operand); //intermediate
        fscanf(fp1, "%s\t%s\t%s",label,opcode,operand); // read next line
    }
    else{
        locctr = 0;
    }
    // read while not end
    while(strcmp(opcode,"END")!=0){
        // write line to intermediate file
        fprintf(fp4,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);

        // LABEL undengill write to symtab
        if(strcmp(label,"**")!=0){
            fprintf(fp3,"%s\t%d\n",label,locctr);
        }
        // next opcode innu vendi
        fscanf(fp2,"%s\t%s",code,mnemonic);
        // check if opcode there in optab
        while(strcmp(code,"END")!=0){
            if(strcmp(opcode,code)==0){
                locctr+=3;
                break;
            }
            fscanf(fp2,"%s\t%s",code,mnemonic);        
        }
        // if opcode is not found in the optab then check the following
        if(strcmp(opcode,"WORD")==0){
            locctr+=3;
        }
        else if(strcmp(opcode,"RESW")==0){
            locctr+=(3*(atoi(operand)));
        }
        else if(strcmp(opcode,"BYTE")==0){
            ++locctr;
        }
        else if(strcmp(opcode,"RESB")==0){
            locctr+= atoi(operand);
        }
        // read next line
        fscanf(fp1,"%s\t%s\t%s",label,opcode,operand);
    }
    // write the last line also
    fprintf(fp4,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
    fclose(fp4);
    fclose(fp3);
    fclose(fp2);
    fclose(fp1);

    char str;
    FILE *fp6,*fp7,*fp8;

    printf("\n INPUT FILE\n");
    fp6 = fopen("input.txt","r");
    str = fgetc(fp6);
    while(str!=EOF){
        printf("%c",str);
        str = fgetc(fp6);
    }
    fclose(fp6);

     printf("\n INTERMEDIATE FILE\n");
    fp7 = fopen("intermediate.txt","r");
    str = fgetc(fp7);
    while(str!=EOF){
        printf("%c",str);
        str = fgetc(fp7);
    }
    fclose(fp7);

     printf("\n SYMBOL FILE\n");
    fp8 = fopen("symtab.txt","r");
    str = fgetc(fp8);
    while(str!=EOF){
        printf("%c",str);
        str = fgetc(fp8);
    }
    fclose(fp8);

    length = locctr - start;
    fprintf(fp5, "%d", length);
    fclose(fp5);
    printf("\nThe length of the code : %d\n", length);
    return 0;

}
