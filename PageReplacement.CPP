#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <queue>

using namespace std;

queue<int> myqueue;

void print(int buff_size, int g[][4], int p[], int n, char l[])
{
    int count = 0, i, j = 0;
    for (i = 0; i < n; i++)
    {
        cout << p[i] << "\t";
    }
    cout << endl;
    while (j < buff_size)
    {
        for (i = 0; i < n; i++)
        {
            if (g[i][j] == -1)
            {
                cout << "-"
                     << "\t";
            }
            else
            {
                cout << g[i][j] << "\t";
            }
        }
        cout << endl;
        j++;
    }
    for (i = 0; i < n; i++)
    {
        if (l[i] == 'P')
        {
            count++;
        }
        cout << l[i] << "\t";
    }

    cout << "Number of page faults:\t" << count << endl;
}

void LRU(int p[], int n, int buff_size)
{
    int a[buff_size];
    char happ[30];
    int g[40][4], count, j = 0, i, flag, k, min;
    while (j < buff_size)
    {
        g[0][j] = -1;
        j++;
    }
    for (i = 0; i < n; i++)
    {
        flag = 0;
        if (i < buff_size)
        {
            for (j = 0; j < buff_size; j++)
            {
                if (p[i] == g[i][j])
                {
                    flag = 1;
                }
            }
            if (flag == 1)
            {
                for (j = 0; j < buff_size; j++)
                {
                    g[i + 1][j] = g[i][j];
                }
                happ[i] = 'H';
            }
            else
            {
                for (j = 0; j < buff_size; j++)
                {
                    if (g[i][j] == -1)
                    {
                        break;
                    }
                }
                g[i][j] = p[i];
                for (j = 0; j < buff_size; j++)
                {
                    g[i + 1][j] = g[i][j];
                }
                happ[i] = 'P';
            }
        }
        else
        {
            for (j = 0; j < buff_size; j++)
            {
                if (g[i][j] == p[i])
                {
                    flag = 1;
                }
            }
            if (flag == 1)
            {
                for (j = 0; j < buff_size; j++)
                {
                    g[i + 1][j] = g[i][j];
                }
                happ[i] = 'H';
            }
            else
            {
                for (k = 0; k < buff_size; k++)
                {
                    for (j = i; j >= 0; j--)
                    {
                        if (g[i][k] == p[j])
                        {
                            a[k] = j;
                            break;
                        }
                    }
                }
                min = 999;
                for (j = 0; j < buff_size; j++)
                {
                    if (min > a[j])
                    {
                        min = a[j];
                    }
                }
                for (j = 0; j < buff_size; j++)
                {
                    if (p[min] == g[i][j])
                    {
                        break;
                    }
                }
                g[i][j] = p[i];
                for (j = 0; j < buff_size; j++)
                {
                    g[i + 1][j] = g[i][j];
                }
                happ[i] = 'P';
            }
        }
    }
    print(buff_size, g, p, n, happ);
}

void OPT(int p[], int n, int buff_size)
{
    int a[buff_size] = {-1};
    char happ[30];
    int g[40][4], count, j = 0, i, flag, k, min;
    while (j < buff_size)
    {
        g[0][j] = -1;
        j++;
    }
    for (i = 0; i < n; i++)
    {
        a[buff_size] = {-1};
        flag = 0;
        if (i < buff_size)
        {
            for (j = 0; j < buff_size; j++)
            {
                if (p[i] == g[i][j])
                {
                    flag = 1;
                }
            }
            if (flag == 1)
            {
                for (j = 0; j < buff_size; j++)
                {
                    g[i + 1][j] = g[i][j];
                }
                happ[i] = 'H';
            }
            else
            {
                for (j = 0; j < buff_size; j++)
                {
                    if (g[i][j] == -1)
                    {
                        break;
                    }
                }
                g[i][j] = p[i];
                for (j = 0; j < buff_size; j++)
                {
                    g[i + 1][j] = g[i][j];
                }
                happ[i] = 'P';
            }
        }
        else
        {
            for (j = 0; j < buff_size; j++)
            {
                if (g[i][j] == p[i])
                {
                    flag = 1;
                }
            }
            if (flag == 1)
            {
                for (j = 0; j < buff_size; j++)
                {
                    g[i + 1][j] = g[i][j];
                }
                happ[i] = 'H';
            }
            else
            {
                for (k = 0; k < buff_size; k++)
                {
                    for (j = i + 1; j < n; j++)
                    {
                        if (g[i][k] == p[j])
                        {
                            a[k] = j;
                        }
                    }
                }
                min = -1;
                for (j = 0; j < buff_size; j++)
                {
                    if (min <= a[j])
                    {
                        min = a[j];
                        if (min == -1)
                        {
                            break;
                        }
                    }
                }
                if (min != -1)
                {
                    for (j = 0; j < buff_size; j++)
                    {
                        if (p[min] == g[i][j])
                        {
                            break;
                        }
                    }
                    g[i][j] = p[i];
                    for (j = 0; j < buff_size; j++)
                    {
                        g[i + 1][j] = g[i][j];
                    }
                    happ[i] = 'P';
                }
                else
                {
                    if (i == n - 1)
                    {
                        j = 0;
                        g[i][j] = p[i];
                        for (j = 0; j < buff_size; j++)
                        {
                            g[i + 1][j] = g[i][j];
                        }
                        happ[i] = 'P';
                    }
                    else
                    {
                        for (j = 0; j < buff_size; j++)
                        {
                            if (a[j] == -1)
                            {
                                break;
                            }
                        }
                        g[i][j] = p[i];
                        for (j = 0; j < buff_size; j++)
                        {
                            g[i + 1][j] = g[i][j];
                        }
                        happ[i] = 'P';
                    }
                }
            }
        }
    }
    print(buff_size, g, p, n, happ);
}

// Use Queue.
void FIFO(int p[], int n, int buff_size)
{
    char happ[30];
    int g[40][4];
    int i, j, k, index;
    j = 0;
    while (j < buff_size)
    {
        g[i][j] = -1;
        j++;
    }
    for (i = 0; i < n; i++)
    {
        if (i < buff_size)
        {
            myqueue.push(p[i]);
            j = 0;

            while (j < buff_size)
            {
                if (g[i][j] == -1)
                {
                    g[i + 1][j] = p[i];
                    g[i][j] = p[i];
                    break;
                }
                j++;
            }
            for (j = 0; j < buff_size; j++)
            {
                g[i + 1][j] = g[i][j];
            }
            happ[i] = 'P';
        }
        else
        {
            index = -2;
            for (j = 0; j < buff_size; j++)
            {
                if (g[i][j] == p[i])
                {
                    index = j;
                    break;
                }
            }
            if (index != -2)
            {
                j = 0;
                while (j < buff_size)
                {
                    g[i + 1][j] = g[i][j];
                    j++;
                }
                happ[i] = 'H';
            }
            else
            {
                k = myqueue.front();
                for (j = 0; j < buff_size; j++)
                {
                    if (g[i][j] == k)
                    {
                        index = j;
                        break;
                    }
                }
                g[i][index] = p[i];
                for (j = 0; j < buff_size; j++)
                {
                    g[i + 1][j] = g[i][j];
                }
                happ[i] = 'P';
                myqueue.pop();
                myqueue.push(p[i]);
            }
        }
    }
    print(buff_size, g, p, n, happ);
}

int main()
{
    int pages[30], n, i, frame_buffer_size;
    cout << "Enter number of pages you wish to include:\t";
    cin >> n;
    for (i = 0; i < n; i++)
    {
        cout << "Enter page identification for page " << i + 1 << " :\t";
        cin >> pages[i];
    }
    cout << "Enter the frame buffer size:\t";
    cin >> frame_buffer_size;
    cout << "\n\nThe output of FIFO page replacement algorithm is as follows:\n";
    FIFO(pages, n, frame_buffer_size);
    cout << "\n\nThe output of LRU page replacement algorithm is as follows:\n";
    LRU(pages, n, frame_buffer_size);
    cout << "\n\nThe output of OPT page replacement algorithm is as follows:\n";
    OPT(pages, n, frame_buffer_size);
    return 0;
}