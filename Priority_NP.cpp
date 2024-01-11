#include <iostream>
#include <vector>

using namespace std;

// Struct to represent a process
struct Process
{
    int id;
    int arrival_time;
    int burst_time;
    int priority;
};

// Function to calculate waiting time, turnaround time, and finish time for each process
void calculateWaitingTurnaroundFinishTime(vector<Process> &processes, vector<int> &waitingTime, vector<int> &turnaroundTime, vector<int> &finishTime)
{
    int n = processes.size();

    waitingTime[0] = 0;
    turnaroundTime[0] = processes[0].burst_time;
    finishTime[0] = processes[0].burst_time;

    for (int i = 1; i < n; i++)
    {
        finishTime[i] = finishTime[i - 1] + processes[i].burst_time;
        turnaroundTime[i] = finishTime[i] - processes[i].arrival_time;
        waitingTime[i] = turnaroundTime[i] - processes[i].burst_time;
    }
}

// Function to manually sort processes based on priority (higher priority first)
void manualSort(vector<Process> &processes)
{
    int n = processes.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].priority < processes[j + 1].priority)
            {
                swap(processes[j], processes[j + 1]);
            }
        }
    }
}

// Function to display Gantt chart
void displayGanttChart(vector<Process> &processes, vector<int> &finishTime)
{
    cout << "Gantt Chart:\n";

    int totalTime = 0;
    for (const Process &process : processes)
    {
        cout << "| P" << process.id << " ";
        for (int i = 0; i < process.burst_time; i++)
        {
            cout << " ";
        }
        totalTime += process.burst_time;
    }
    cout << "|\n";

    // Display timeline
    cout << "0  ";
    for (int time : finishTime)
    {
        cout << "   " << time << "  ";
    }
    cout << endl;
}

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    vector<int> waitingTime(n, 0);
    vector<int> turnaroundTime(n, 0);
    vector<int> finishTime(n, 0);

    // Input process information
    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        cout << "Enter arrival time for process " << i + 1 << ": ";
        cin >> processes[i].arrival_time;
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> processes[i].burst_time;
        cout << "Enter priority for process " << i + 1 << ": ";
        cin >> processes[i].priority;
    }

    // Manually sort processes based on priority (higher priority first)
    manualSort(processes);

    calculateWaitingTurnaroundFinishTime(processes, waitingTime, turnaroundTime, finishTime);

    // Display Gantt chart
    displayGanttChart(processes, finishTime);

    // Display tabular information
    cout << "Process ID\tArrival Time\tBurst Time\tPriority\tTurnaround Time\tFinish Time\tWaiting Time\n";
    for (int i = 0; i < n; i++)
    {
        cout << processes[i].id << "\t\t" << processes[i].arrival_time << "\t\t" << processes[i].burst_time << "\t\t" << processes[i].priority << "\t\t" << turnaroundTime[i] << "\t\t" << finishTime[i] << "\t\t" << waitingTime[i] << endl;
    }

    return 0;
}
