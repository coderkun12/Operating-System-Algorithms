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
int get_smallest(int a[], int n, int bt[])
{
    int smallest = 9999, index;
    for (int i = 0; i < n; i++)
    {
        if (bt[a[i]] <= smallest)
        {
            index = a[i];
            smallest = bt[a[i]];
        }
    }
    return index;
}
int main()
{
    int n, i, j, indexes[45], k = 0, flag[10] = {0}, count = 0, bt[50], gchart[200];
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
    bubblesort(o, n);
    cout << "\nP_ID\tAT\tBT" << endl;
    for (i = 0; i < n; i++)
    {
        cout << o[i].proc_num << "\t" << o[i].arrival_time << "\t" << o[i].burst_time << endl;
        bt[i] = o[i].burst_time;
    }
    int fin_tim = 0;
    for (i = 0; i < n; i++)
    {
        if (o[i].arrival_time == 0)
        {
            gchart[k] = o[i].proc_num;
            k++;
            flag[i] = 1;
            fin_tim += 1;
            bt[i] = bt[i] - 1;
            if (bt[i] == 0)
            {
                count += 1;
                o[i].fin_time = fin_tim;
                o[i].ta_time = o[i].fin_time - o[i].arrival_time;
                o[i].wait_time = o[i].ta_time - o[i].burst_time;
            }
            break;
        }
    }
    int g, ind;
    while (count != n)
    {
        g = 0;
        for (i = 0; i < n; i++)
        {
            if ((o[i].arrival_time <= fin_tim) && (bt[i] != 0))
            {
                indexes[g] = i;
                g++;
            }
        }
        ind = get_smallest(indexes, g, bt);
        gchart[k] = o[ind].proc_num;
        k++;
        flag[ind] = 1;
        fin_tim += 1;
        bt[ind] = bt[ind] - 1;
        if (bt[ind] == 0)
        {
            count += 1;
            o[ind].fin_time = fin_tim;
            o[ind].ta_time = o[ind].fin_time - o[ind].arrival_time;
            o[ind].wait_time = o[ind].ta_time - o[ind].burst_time;
        }
    }
    cout << "\nGant Chart:\n  ";
    for (i = 0; i < k; i++)
    {
        cout << gchart[i] << "  ";
    }
    cout << endl;
    for (i = 0; i < k; i++)
    {
        cout << i << "  ";
    }
    cout << "\n\nThe resultant process scheduling is as follows:\nP_ID\tAT\tBT\tFT\tTT\tWT\n";
    for (i = 0; i < n; i++)
    {
        cout << o[i].proc_num << "\t" << o[i].arrival_time << "\t" << o[i].burst_time << "\t" << o[i].fin_time << "\t" << o[i].ta_time << "\t" << o[i].wait_time << endl;
    }
    return 0;
}