#include<bits/stdc++.h>
using namespace std;
ifstream infile("datafile.txt");
ofstream outfile("dataFileOutput.txt");

pair<float, float> Output(map<string, vector<int>> Process, map<string, int> ct)
{
    float avgtat = 0;
    float avgwt = 0;
    outfile << "Process\t\tTurnaround Time\t\tWaiting Time\n";
    for (auto i : Process)
    {
        string pid = i.first;
        int at = i.second[0];
        int bt = i.second[1];
        int prior = i.second[2];

        outfile << pid << "\t\t\t";
        outfile << ct[pid]-at << "\t\t\t\t\t";
        outfile << ct[pid]-at-bt << endl;

        avgtat += ct[pid]-at;
        avgwt += ct[pid]-at-bt;
    }
    outfile << endl << endl;
    avgtat /= ct.size();
    avgwt /= ct.size();
    return make_pair(avgtat, avgwt);
}

void Summary(pair<float, float> FCFS, pair<float, float> SPN, pair<float, float> PP, pair<float, float> PRR)
{
    outfile << "Summary\n";
    outfile << "Algorithm\tAverage Turnaround Time\t\tAverage Waiting Time\n";

    outfile << "FCFS" << "\t\t" << fixed << setprecision(2) << FCFS.first << "\t\t\t\t\t\t"<< fixed << setprecision(2) << FCFS.second << endl;
    outfile << "SPN" << " \t\t" << fixed << setprecision(2) << SPN.first << "\t\t\t\t\t\t"<< fixed << setprecision(2) << SPN.second << endl;
    outfile << "PP" << "  \t\t" << fixed << setprecision(2) << PP.first << "\t\t\t\t\t\t"<< fixed << setprecision(2) << PP.second << endl;
    outfile << "PRR" << " \t\t" << fixed << setprecision(2) << PRR.first << "\t\t\t\t\t\t"<< fixed << setprecision(2) << PRR.second << endl;
}

pair<float, float> FCFS (map<string, vector<int>> Process, int dispatcher)
{
    outfile << "FCFS:\n";
    int time = 0;
    int P_remain = Process.size();
    map<string, int> ct;
    

    while (P_remain)
    {
        string store_id = "\0";
        int at = INT_MAX, prior = 5;
        for (auto i : Process)
        {
            string pid = i.first;
            int temp_at = i.second[0];
            int temp_prior = i.second[2];

            if (temp_at <= time && ct.find(pid) == ct.end() && temp_at < at )
            {
                at = temp_at;
                prior = temp_prior;

                store_id = pid;
            }
        }
        if (store_id != "\0")
        {
            time += dispatcher;
            outfile << "T" << time << ": " << store_id << "(" << Process[store_id][2] << ")\n";
            time += Process[store_id][1];
            ct[store_id] = time ;
            P_remain--;
        }
        else time++;
    }

    pair<float, float> p = Output(Process, ct);
    return p;
}

pair<float, float> SPN(map<string, vector<int>> Process, int dispatcher)
{
    outfile << "SPN:\n";
    int time = 0;
    int P_remain = Process.size();
    map<string, int> ct;

    while (P_remain)
    {
        string store_id = "\0";
        int at = INT_MAX, bt = INT_MAX, prior = INT_MAX;
        for (auto i : Process)
        {
            string pid = i.first;
            int temp_at = i.second[0];
            int temp_bt = i.second[1];

            if (ct.find(pid) == ct.end() && temp_at <= time && (temp_bt < bt || (temp_bt == bt && temp_at < at)))
            {
                store_id = pid;
                at = temp_at;
                bt = temp_bt;
            }
        }

        if (store_id != "\0")
        {
            time += dispatcher;
            outfile << "T" << time << ": " << store_id << "(" << Process[store_id][2] << ")\n";
            time += Process[store_id][1];
            ct[store_id] = time;
            P_remain--;
        }
        else time++;
    }

    pair<float, float> p = Output(Process, ct);
    return p;
}

pair<float, float> PP(map<string, vector<int>> Process, int dispatcher)
{
    outfile << "PP:\n";
    int time = 0;
    int P_remain = Process.size();
    map<string, int> ct;
    string prev_store = "\0";
    map<string, vector<int>> dummy = Process;

    while (P_remain)
    {
        string store_id = "\0";
        int at = INT_MAX, bt = INT_MAX, prior = INT_MAX;
        for (auto i : Process)
        {
            string pid = i.first;
            int temp_at = i.second[0];
            int temp_bt = i.second[1];
            int temp_prior = i.second[2];

            if (ct.find(pid) == ct.end() && temp_at <= time && (temp_prior < prior || (temp_prior == prior && temp_at < at)))
            {
                store_id = pid;
                at = temp_at;
                prior = temp_prior;                
            }
        }

        if (store_id != "\0")
        {
            if (prev_store == store_id) time++;
            else {
                time += dispatcher+1;
                outfile << "T" << time-1 << ": " << store_id << "(" << Process[store_id][2] << ")\n";
            }
            prev_store = store_id;

            Process[store_id][1]--;
            if (Process[store_id][1] == 0)
            {
                ct[store_id] = time;
                P_remain--;
            }
        }
        else time++;
    }

    pair<float, float> p = Output(dummy, ct);
    return p;    
}

pair<float, float> PRR  (map<string, vector<int>> Process, int dispatcher)
{
    outfile << "PRR:\n";
    int time = 0;
    int P_remain = Process.size();
    map<string, int> ct;
    map<string, int> turn;
    string prev_store = "\0";
    map<string, vector<int>> dummy = Process;

    for (auto i : Process) turn[i.first] = i.second[0];

    while (P_remain)
    {
        string store_id = "\0";
        int at = INT_MAX, bt = INT_MAX, prior = INT_MAX, turn_final = INT_MAX;
        for (auto i : Process)
        {
            string pid = i.first;
            int temp_at = i.second[0];
            int temp_bt = i.second[1];
            int temp_prior = i.second[2];

            if (ct.find(pid) == ct.end() && temp_at <= time && (turn[pid] < turn_final || (turn[pid] == turn_final && temp_at < at) || (turn[pid] == turn_final && temp_at == at && temp_prior < prior)))  
            {
                store_id = pid;
                at = temp_at;
                prior = temp_prior;
                turn_final = turn[pid];
            }
        }

        if (store_id != "\0")
        {
            if (prev_store != store_id) 
            {
                time += dispatcher;
                outfile << "T" << time << ": " << store_id << "(" << Process[store_id][2] << ")\n";
            }
            prev_store = store_id;

            if (Process[store_id][2] < 3) {
                int t = min(Process[store_id][1], 4);
                Process[store_id][1] -= t, time += t;
            }
            else {
                int t = min(Process[store_id][1], 2);
                Process[store_id][1] -= t, time += t;
            }
            turn[store_id] = time+1;

            if (Process[store_id][1] == 0)
            {
                ct[store_id] = time;
                P_remain--;
            }
        }
        else time++;
    }

    pair<float, float> p = Output(dummy, ct);
    return p;
}

int main()
{
    map<string, vector<int>> Process; // Store A.T, B.T. and Priority for process Pi
    string s = "";
    int dispatcher = 0;

    int ch;
    cout << "\nDO you want to provide an input file or give input manually (0: input file, else: manual): ";
    cin >> ch;

    if (ch == 0) {
    cout << "Enter the File to input : ";
    string file_name;
    cin >> file_name;
    ifstream infile(file_name);

    if (!infile || !outfile) {
        cerr << "Error: Unable to open file!" << endl;
        return 1;
    }

    do {
        infile >> s;

        if (s == "DISP:")
        {
            infile >> s;
            int Size = s.size(), i = 0;
            while (i != Size)
            {
                dispatcher += (s[Size-1-i]-'0')*pow(10, i);
                i++;
            }
        }

        if (s == "ID:")
        {
            infile >> s;
            string s1, s2;
            int j = 3;
            while (j) {
                infile >> s1 >> s2;
                int Size = s2.size(), i = 0;
                int value = 0;
                while (i != Size)
                {
                    value += (s2[Size-1-i]-'0')*pow(10, i);
                    i++;
                }
                Process[s].push_back(value);
                j--;
            }
        }
    }while (s != "EOF");
    }

    else {
        cout << "Dispatcher Time: ";
        cin >> dispatcher;

        int total = 0;
        cout << "Enter the total Number of processes: ";
        cin >> total;

        while (total--) {
            string s;
            int a, b, c;
            cout << "Process ID: ";
            cin >> s;
            cout << "Arrival Time: ";
            cin >> a;
            cout << "Execution Time: ";
            cin >> b;
            cout << "Priority: ";
            cin >> c;
            Process[s].push_back(a);
            Process[s].push_back(b);
            Process[s].push_back(c);
            cout << endl;
        }
    }

    pair<float, float> ct_FCFS, ct_SPN, ct_PP, ct_PRR;

    ct_FCFS = FCFS(Process, dispatcher);
    ct_SPN = SPN(Process, dispatcher);
    ct_PP = PP(Process, dispatcher);
    ct_PRR = PRR(Process, dispatcher);

    Summary(ct_FCFS, ct_SPN, ct_PP, ct_PRR);
    
    cout << "\nYour Output have been successfully printed in file 'dataFileOutput.txt'\n\n";



    return 0;
}