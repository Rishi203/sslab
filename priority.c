#include <stdio.h>

struct process
{
    int no;
    int at, tt, bt, wt, status, ct, pr;
} p[20], temp;

struct done
{
    int no;
    int st, ct;
} d[20];

void main()
{
    int n, i, j, min, fnd;
    float twt = 0.0, ttt = 0.0;
    

    printf("ENTER THE NUMBER OF PROCESSES: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("\nENTER DETAILS OF PROCESS %d", i + 1);
        printf("\nPROCESS NUMBER: ");
        scanf("%d", &p[i].no);
        printf("ARRIVAL TIME: ");
        scanf("%d", &p[i].at);
        printf("BURST TIME: ");
        scanf("%d", &p[i].bt);
        printf("PRIORITY: ");
        scanf("%d", &p[i].pr);
        p[i].status = 0;
    }
    int ls = 0, num = 0, idle = 0;

    for (i = 0; ls < n;)
    {   
        fnd = 0;
        for (j = 0; j < n; j++)
        {
            if (i >= p[j].at && p[j].status == 0)
            {
                if (fnd == 0)
                {
                    min = j;
                    fnd = 1;
                }
                else if ((p[min].pr > p[j].pr) || (p[min].pr == p[j].pr && p[min].at > p[j].at))
                {
                    min = j;
                }
            }
        }

        if (idle == 0 && fnd == 0)
        {
            d[num].no = 0; 
            d[num].st = i;
            i++;
            idle = 1;
        }
        else if (fnd == 1)
        {
            if (idle == 1)
            {
                d[num].ct = i;
                num++;
                idle = 0;
            }

            p[min].status = 1;
            d[num].no = p[min].no;
            d[num].st = i;
            d[num].ct = i + p[min].bt;
            i = d[num].ct;
            p[min].ct = d[num].ct;
            p[min].tt = p[min].ct - p[min].at;
            p[min].wt = p[min].tt - p[min].bt;
            num++;
            ls++;
        }
        else
        {
            i++;
        }
    }

    printf("\nPROCESS NUMBER\tARRIVAL TIME\tCOMPLETION TIME (ms)\tWAITING TIME (ms)\tTURNAROUND TIME (ms)\n\n");

    for (i = 0; i < n; i++)
    {
        printf("    %d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\n", p[i].no, p[i].at, p[i].ct, p[i].wt, p[i].tt);
        twt += p[i].wt;
        ttt += p[i].tt;
    }
    printf("\nGANTT CHART ");
    printf("\n\t--------------------------------------------------------------------\n\t");

    for (i = 0; i < num; i++)
    {
        printf("|");
        if (d[i].no == 0)
            printf("   Idle\t");
        else
            printf("   %d\t", d[i].no);
    }

    printf(" |");
    printf("\n\t--------------------------------------------------------------------\n\t");

    for (i = 0; i < num; i++)
    {
        printf("%d\t", d[i].st);
    }

    printf("%d\t\n", d[num - 1].ct);
    printf("\nAVERAGE WAITING TIME : %f", (twt / n));
    printf("\nAVERAGE TURNAROUND TIME : %f\n", (ttt / n));
}
