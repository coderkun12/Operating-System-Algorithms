#include <iostream>

using namespace std;

struct Process
{
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int turnaround_time;
    int finish_time;
    int wait_time;
    int remaining_time;
    bool executed;

    Process()
    {
        turnaround_time = 0;
        finish_time = 0;
        wait_time = 0;
        remaining_time = 0;
        executed = false;
    }
};

void swap(Process &a, Process &b)
{
    Process temp = a;
    a = b;
    b = temp;
}

void bubbleSort(Process processes[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].arrival_time > processes[j + 1].arrival_time)
            {
                swap(processes[j], processes[j + 1]);
            }
        }
    }
}

int findProcessWithHighestPriority(Process processes[], int n, int currentTime)
{
    int highestPriority = -1;
    int processIndex = -1;

    for (int i = 0; i < n; i++)
    {
        if (!processes[i].executed && processes[i].arrival_time <= currentTime)
        {
            if (highestPriority == -1 || processes[i].priority < highestPriority)
            {
                highestPriority = processes[i].priority;
                processIndex = i;
            }
        }
    }

    return processIndex;
}

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    Process processes[n];
    int currentTime = 0;

    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        cout << "Enter arrival time for process " << i + 1 << ": ";
        cin >> processes[i].arrival_time;
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> processes[i].burst_time;
        cout << "Enter priority for process " << i + 1 << ": ";
        cin >> processes[i].priority;
        processes[i].remaining_time = processes[i].burst_time;
    }

    bubbleSort(processes, n);

    cout << "Process ID\tArrival Time\tBurst Time\tPriority\tTurnaround Time\tFinish Time\tWait Time\n";
    int executedCount = 0;

    while (executedCount < n)
    {
        int processIndex = findProcessWithHighestPriority(processes, n, currentTime);

        if (processIndex != -1)
        {
            Process &currentProcess = processes[processIndex];

            if (currentProcess.remaining_time == currentProcess.burst_time)
            {
                currentProcess.wait_time = currentTime - currentProcess.arrival_time;
            }

            currentProcess.remaining_time--;
            currentTime++;

            if (currentProcess.remaining_time == 0)
            {
                currentProcess.finish_time = currentTime;
                currentProcess.turnaround_time = currentProcess.finish_time - currentProcess.arrival_time;
                currentProcess.executed = true;
                executedCount++;
            }
        }
        else
        {
            currentTime++;
        }
    }

    for (int i = 0; i < n; i++)
    {
        Process &currentProcess = processes[i];
        cout << currentProcess.id << "\t\t" << currentProcess.arrival_time << "\t\t" << currentProcess.burst_time << "\t\t"
             << currentProcess.priority << "\t\t" << currentProcess.turnaround_time << "\t\t" << currentProcess.finish_time << "\t\t"
             << currentProcess.wait_time << endl;
    }

    // Gantt Chart
    cout << "\nGantt Chart:" << endl;
    int time = 0;
    while (executedCount < n)
    {
        int processIndex = findProcessWithHighestPriority(processes, n, time);
        if (processIndex != -1)
        {
            Process &currentProcess = processes[processIndex];
            cout << "| P" << currentProcess.id << " ";
            currentProcess.remaining_time--;
            time++;
            if (currentProcess.remaining_time == 0)
            {
                currentProcess.finish_time = time;
                currentProcess.turnaround_time = currentProcess.finish_time - currentProcess.arrival_time;
                currentProcess.executed = true;
                executedCount++;
            }
        }
        else
        {
            time++;
        }
    }
    cout << "|\n";

    return 0;
}
