#include <stdio.h>
#include <iostream>
using namespace std;

struct node
{
    int fin_time, proc_num, burst_time, arrival_time, wait_time, ta_time;
} o[50];
void bubblesort(struct node t[10], int nu)
{
    struct node swap;
    int i, j;
    for (i = 0; i < nu - 1; i++)
    {
        for (j = 0; j < nu - 1; j++)
        {
            if (t[j].burst_time > t[j + 1].burst_time)
            {
                swap = o[j];
                o[j] = o[j + 1];
                o[j + 1] = swap;
            }
        }
    }
}
void bubblesort2(struct node t[], int nu)
{
    struct node swap;
    int i, j;
    for (i = 0; i < nu - 1; i++)
    {
        for (j = 0; j < nu - 1; j++)
        {
            if (t[j].fin_time > t[j + 1].fin_time)
            {
                swap = o[j];
                o[j] = o[j + 1];
                o[j + 1] = swap;
            }
        }
    }
}
int main()
{
    int n, i, j, flag[10] = {0}, count = 0;
    cout << "Enter number of processes:\t";
    cin >> n;
    cout << "Enter the burst time and arrival time of respective processses:\n";
    for (i = 0; i < n; i++)
    {
        o[i].proc_num = i;
        cout << "Enter arrival time for process " << i << " :\t";
        cin >> o[i].arrival_time;
        cout << "Enter burst time for process " << i << " :\t";
        cin >> o[i].burst_time;
    }
    cout << "\nYou have entered following Details:";
    cout << "\nP_ID\tAT\tBT" << endl;
    for (i = 0; i < n; i++)
    {
        cout << o[i].proc_num << "\t" << o[i].arrival_time << "\t" << o[i].burst_time << endl;
    }
    bubblesort(o, n);
    int fin_tim = 0;
    for (i = 0; i < n; i++)
    {
        if (o[i].arrival_time == 0)
        {
            flag[i] = 1;
            fin_tim += o[i].burst_time;
            o[i].fin_time = fin_tim;
            o[i].ta_time = o[i].fin_time - o[i].arrival_time;
            o[i].wait_time = o[i].ta_time - o[i].burst_time;
            count += 1;
            break;
        }
    }
    i = 0;
    while (count != n)
    {
        i = 0;
        while (i < n)
        {
            if (flag[i] != 1 && o[i].arrival_time <= fin_tim)
            {
                flag[i] = 1;
                fin_tim += o[i].burst_time;
                o[i].fin_time = fin_tim;
                o[i].ta_time = o[i].fin_time - o[i].arrival_time;
                o[i].wait_time = o[i].ta_time - o[i].burst_time;
                count += 1;
            }
            i++;
        }
    }
    bubblesort2(o, n);
    cout << "\nThe resultant process scheduling is as follows:\nP_ID\tAT\tBT\tFT\tTT\tWT\n";
    for (i = 0; i < n; i++)
    {
        cout << o[i].proc_num << "\t" << o[i].arrival_time << "\t" << o[i].burst_time << "\t" << o[i].fin_time << "\t" << o[i].ta_time << "\t" << o[i].wait_time << endl;
    }
    cout << "\nThe Gant chart:-\n";
    int spaces;
    for (i = 0; i < n; i++)
    {
        if (o[i].burst_time <= 15)
        {
            spaces = 5;
        }
        else if (o[i].burst_time <= 30)
        {
            spaces = 10;
        }
        else if (o[i].burst_time <= 5)
        {
            spaces = 2;
        }
        else if (o[i].burst_time < 10 && o[i].burst_time > 5)
        {
            spaces = 3;
        }
        cout << " P" << o[i].proc_num;
        for (j = 0; j < spaces; j++)
        {
            cout << " ";
        }
        cout << "| ";
    }
    cout << endl;
    for (i = 0; i < n; i++)
    {
        if (o[i].burst_time <= 15)
        {
            spaces = 5;
        }
        else if (o[i].burst_time <= 30)
        {
            spaces = 10;
        }
        else if (o[i].burst_time <= 5)
        {
            spaces = 2;
        }
        else if (o[i].burst_time < 10 && o[i].burst_time > 5)
        {
            spaces = 3;
        }
        if (i == 0)
        {
            cout << o[i].arrival_time;
        }
        else
        {
            cout << o[i - 1].fin_time;
        }
        for (j = 0; j < spaces + 3; j++)
        {
            cout << " ";
        }
    }
    cout << o[i - 1].fin_time;
    return 0;
}
