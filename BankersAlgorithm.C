#include <stdio.h>

int main()
{
    int processes, resources;

    printf("Enter the number of processes: ");
    scanf("%d", &processes);
    printf("Enter the number of resources: ");
    scanf("%d", &resources);

    int max[processes][resources];
    int allocated[processes][resources];
    int need[processes][resources];
    int available[resources];
    int work[resources];
    int finish[processes];

    // Input the maximum resource allocation for each process
    for (int i = 0; i < processes; i++)
    {
        printf("Enter the maximum resource allocation for Process %d: ", i);
        for (int j = 0; j < resources; j++)
        {
            scanf("%d", &max[i][j]);
        }
        finish[i] = 0;
    }

    // Input the allocated resources for each process
    for (int i = 0; i < processes; i++)
    {
        printf("Enter the allocated resource for Process %d: ", i);
        for (int j = 0; j < resources; j++)
        {
            scanf("%d", &allocated[i][j]);
            need[i][j] = max[i][j] - allocated[i][j];
        }
    }

    // Input the available resources
    printf("Enter the available resources: ");
    for (int i = 0; i < resources; i++)
    {
        scanf("%d", &available[i]);
        work[i] = available[i];
    }

    int safe = 0;
    while (safe < processes)
    {
        int found = 0;
        for (int i = 0; i < processes; i++)
        {
            if (finish[i] == 0)
            {
                int j;
                for (j = 0; j < resources; j++)
                {
                    if (need[i][j] > work[j])
                        break;
                }
                if (j == resources)
                {
                    for (int k = 0; k < resources; k++)
                    {
                        work[k] += allocated[i][k];
                    }
                    finish[i] = 1;
                    printf("Process %d is safe.\n", i);
                    safe++;
                    found = 1;
                }
            }
        }
        if (found == 0)
        {
            printf("The system is in an unsafe state.\n");
            break;
        }
    }
    return 0;
}
