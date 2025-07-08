# 📄 CPU_Scheduling_Algorithms

This is a **C++ program** that simulates multiple **CPU scheduling algorithms** for Operating Systems coursework or practice. It implements **FCFS**, **SPN**, **Preemptive Priority**, and **Priority Round Robin (PRR)** scheduling with dispatcher (context switching) time.

---

## ✅ Features

- Implements:
  - **First Come First Serve (FCFS)**
  - **Shortest Process Next (SPN)**
  - **Preemptive Priority (PP)**
  - **Priority Round Robin (PRR)** with High/Low Priority classes
- Handles **dispatcher time** (context switching delay)
- Accepts input **manually** or from a **structured input file**
- Generates detailed logs with:
  - Process timeline
  - Average **Turnaround Time**
  - Average **Waiting Time**
- Saves output in a text file for easy comparison

---

## 📥 Input Format

Input can be given **manually** or via a **file**.

**Each input must contain:**

1. For Dispatcher time:
     - DISP: <value>
2. For each process:
     - ID: <ProcessID>
     - Arrive: <ArrivalTime>
     - ExecSize: <BurstTime>
     - Priority: <Priority>
     
---

## ⚙️ Dispatcher Rules

- The dispatcher runs to select the next process to run.  
- **Rules:**
  1. Dispatcher time is fixed (`DISP`). No extra time is wasted other than this.
  2. If only one process is running and no other is waiting, dispatcher does **not** run.
  3. In PRR, if time quantum expires, dispatcher runs to pick next process.
  4. Dispatcher only considers processes that arrived **before or at dispatch time**.
  5. If multiple processes arrive at the same time, tie is broken by ID (lex order).

---

## 🔄 Scheduling Algorithms

**✔ FCFS (First Come First Serve)**  
- Simple non-preemptive scheduling.
- Processes run in arrival order. Priority is ignored.

**✔ SPN (Shortest Process Next)**  
- Non-preemptive.
- Process with **shortest execution time** runs next. Priority is ignored.

**✔ PP (Preemptive Priority)**  
- Preemptive.
- Process with **highest priority** runs first.
- A running process can be interrupted by a new higher-priority arrival.

**✔ PRR (Priority Round Robin)**  
- Variant of standard Round Robin.
- Processes split into two classes:
  - **Higher Priority Class (HPC)**: priority 0, 1, 2 → quantum = 4 units
  - **Lower Priority Class (LPC)**: priority 3, 4, 5 → quantum = 2 units
- Same as RR but quantum depends on priority class.

---



## 🚀 Run

''' bash
- ./CPU_Scheduling_Algorithms

---

## 🗂️ Output
- Displays timeline for each algorithm:

  - When each process starts and finishes

  - Which process is running at each timestamp

- Computes for each process:

  - Turnaround Time for each process

  - Waiting Time for each process

- Calculates average Turnaround Time and Waiting Time for each algorithm

- Results are saved in: dataFileOutput.txt

---

## 👨‍💻 Author
Sarthak Narula

---

## 📄 License
For educational use only.


