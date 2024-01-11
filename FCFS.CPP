#include <iostream>
#include <vector>

using namespace std;

// Struct to represent a process
struct Process
{
    int id;
    int arrival_time;
    int burst_time;
};

// Bubble Sort function
void bubbleSort(vector<Process> &processes)
{
    int n = processes.size();
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

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    // Input process information
    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        cout << "Enter arrival time for process " << i + 1 << ": ";
        cin >> processes[i].arrival_time;
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> processes[i].burst_time;
    }

    // Sort processes based on arrival time using bubble sort
    bubbleSort(processes);

    int waitingTime = 0;
    int turnaroundTime = 0;
    int totalTime = 0;

    cout << "Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++)
    {
        int waiting = max(0, totalTime - processes[i].arrival_time);
        int turnaround = waiting + processes[i].burst_time;
        waitingTime += waiting;
        turnaroundTime += turnaround;

        cout << processes[i].id << "\t\t" << processes[i].arrival_time << "\t\t" << processes[i].burst_time << "\t\t" << waiting << "\t\t" << turnaround << endl;

        totalTime += processes[i].burst_time;
    }

    // Display Gantt chart
    cout << "\nGantt Chart:\n";
    totalTime = 0;
    for (int i = 0; i < n; i++)
    {
        cout << "| P" << processes[i].id << " ";
        for (int j = 0; j < processes[i].burst_time; j++)
        {
            cout << " ";
        }
        totalTime += processes[i].burst_time;
    }
    cout << "|\n";
    cout << "0  ";
    for (int i = 0; i < n; i++)
    {
        cout << "   " << totalTime << "  ";
        totalTime += processes[i].burst_time;
    }
    cout << endl;

    cout << "Average Waiting Time: " << static_cast<double>(waitingTime) / n << endl;
    cout << "Average Turnaround Time: " << static_cast<double>(turnaroundTime) / n << endl;

    return 0;
}
