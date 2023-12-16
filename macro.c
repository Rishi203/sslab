#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main()
{
 
    FILE *f1, *f2, *f3, *f4, *f5;
    int len, i, pos = 1;
    char arg[20], mne[20], opnd[20], la[20], name[20],
         mne1[20], opnd1[20], pos1[10], pos2[10];
    
    f1 = fopen("input.txt", "r");
    f2 = fopen("namtab.txt", "w+");
    f3 = fopen("deftab.txt", "w+");
    f4 = fopen("argtab.txt", "w+");
    f5 = fopen("op.txt", "w+");
    fscanf(f1, "%s%s%s", la, mne, opnd);

    while (strcmp(mne, "END") != 0)
    {
        if (strcmp(mne, "MACRO") == 0)
        {
            // Write the label (macro name) to "namtab.txt"
            fprintf(f2, "%s\n", la);

            // Move the file pointer to the beginning of "namtab.txt"
            fseek(f2, SEEK_SET, 0);

            // Write the macro definition to "deftab.txt"
            fprintf(f3, "%s\t%s\n", la, opnd);

            // Read the next line of the input file
            fscanf(f1, "%s%s%s", la, mne, opnd);

            while (strcmp(mne, "MEND") != 0)
            {
                if (opnd[0] == '&')
                {
                    // Replace the argument with a positional parameter
                    snprintf(pos1, 10, "%d", pos);
                    strcpy(pos2, "?");
                    strcpy(opnd, strcat(pos2, pos1));
                    pos = pos + 1;
                }
                // Write the macro body to "deftab.txt"
                fprintf(f3, "%s\t%s\n", mne, opnd);
                // Read the next line of the input file
                fscanf(f1, "%s%s%s", la, mne, opnd);
            }
            // Write "MEND" to "deftab.txt"
            fprintf(f3, "%s", mne);
        }
        else
        {
            // If the mnemonic is not "MACRO"
            // Read the macro name from "namtab.txt"
            fscanf(f2, "%s", name);

            // Check if the current mnemonic matches any defined macro
            if (strcmp(mne, name) == 0)
            {
                len = strlen(opnd);
                for (i = 0; i < len; i++)
                {
                    // If the character is not ',', write it to "argtab.txt"
                    if (opnd[i] != ',')
                        fprintf(f4, "%c", opnd[i]);
                    else
                        // If the character is ',', start a new line in "argtab.txt"
                        fprintf(f4, "\n");
                }

                fseek(f3, SEEK_SET, 0);
                fseek(f4, SEEK_SET, 0);

                fscanf(f3, "%s%s", mne1, opnd1);

                // Write the expanded macro to "op.txt"
                fprintf(f5, ".\t%s\t%s\n", mne1, opnd);

                // Read the next line of "deftab.txt"
                fscanf(f3, "%s%s", mne1, opnd1);

                // Continue processing until the mnemonic is "MEND"
                while (strcmp(mne1, "MEND") != 0)
                {
                    // Check if the operand starts with '?'
                    if ((opnd1[0] == '?'))
                    {     
                        // Read the argument from "argtab.txt"
                        fscanf(f4, "%s", arg);

                        // printf("%s",arg);

                        // Write the expanded macro with the argument to "op.txt"
                        fprintf(f5, "-\t%s\t%s\n", mne1, arg);
                    }
                    else
                    {
                        // Write the expanded macro to "op.txt"
                        fprintf(f5, "-\t%s\t%s\n", mne1, opnd1);
                    }
                    // Read the next line of "deftab.txt"
                    fscanf(f3, "%s%s", mne1, opnd1);
                }
            }
            else
            {
                // If the mnemonic is not a macro, write the original line to "op.txt"
                fprintf(f5, "%s\t%s\t%s\n", la, mne, opnd);
            }
        }
        // Read the next line of the input file
        fscanf(f1, "%s%s%s", la, mne, opnd);
    }

    // Write the last line to "op.txt"
    fprintf(f5, "%s\t%s\t%s", la, mne, opnd);
    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    fclose(f5);
    printf("Successful !!!\n");
}
