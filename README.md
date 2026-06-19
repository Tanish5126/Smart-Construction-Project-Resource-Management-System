# Smart Construction Project & Resource Management System

## 🏗️ Project Overview

A comprehensive **Data Structures & Algorithms (DSA)** project that implements a complete construction project management system. The system efficiently manages projects, workers, equipment, tasks, and resource requests using advanced data structures and algorithms.

**Institution:** ITM Skills University  
**Program:** B.Tech CSE (2025-2029)  
**Course:** Data Structures & Algorithms - Semester II  
**Industry:** Construction & Infrastructure  
**Date:** June 2026

---

## 🎯 Project Highlights

### Key Features
- **9 Interactive Menu Options** for complete project management
- **Real-time Data Structures** demonstrating 8 different DSA concepts
- **Efficient Searching & Sorting** with O(log n) and O(n log n) complexity
- **Undo/Rollback Functionality** using Stack
- **Queue-based Request Processing** in FIFO order
- **Project Dependency Analysis** using Graph algorithms
- **Worker & Equipment Lookup** with O(1) average hash table performance

### Technologies Used
- **Language:** C++ (C++11 Standard)
- **Development Environment:** Linux/Unix with G++ Compiler
- **Data Structures:** Stack, Queue, BST, AVL Tree, Hash Tables, Graph
- **Algorithms:** Merge Sort, Quick Sort, BFS, DFS, Linear Search, BST Search

---

## 📋 Data Structures & Algorithms Implemented

| Data Structure | Purpose | Time Complexity | Application |
|---|---|---|---|
| **Stack** | Operation History & Undo | O(1) | Track and rollback operations |
| **Queue** | Resource Requests | O(1) | FIFO request processing |
| **BST** | Project Database | O(log n) avg | Fast project lookup |
| **AVL Tree** | Balanced Project Storage | O(log n) | Guaranteed efficiency |
| **Hash Tables** | Worker/Equipment Lookup | O(1) avg | Instant ID-based search |
| **Graph** | Dependency Analysis | O(V+E) | Critical path analysis |
| **Merge Sort** | Task Sorting | O(n log n) | Priority-based scheduling |
| **Quick Sort** | Task Sorting | O(n log n) avg | Alternative sorting |

---

## 🚀 Getting Started

### Prerequisites
- **C++ Compiler:** GCC 7.0 or higher
- **Operating System:** Linux/Unix/Mac
- **Build Tool:** Make or direct compilation with g++
- **Memory:** Minimum 256MB RAM

### Installation & Compilation

1. **Clone or Download the Project:**
   ```bash
   # Copy all project files to your directory
   cd ~/construction-management-system
   ```

2. **Compile the Program:**
   ```bash
   g++ -std=c++11 main.cpp -o construction_system
   ```

   Or using Make (if Makefile is provided):
   ```bash
   make
   ```

3. **Verify Data Files:**
   Ensure the following files are in the same directory as the executable:
   - `projects.txt`
   - `workers.txt`
   - `equipment.txt`
   - `tasks.txt`
   - `requests.txt`

---

## 📖 How to Run

### Basic Execution
```bash
./construction_system
```

### Interactive Menu
Once the program starts, you'll see a menu with 10 options:

```
    SMART CONSTRUCTION PROJECT & RESOURCE MANAGEMENT
============================================================
  1. Project Status
  2. Equipment Usage
  3. Workforce Allocation
  4. Construction Schedule
  5. Progress Reports
  6. Resource Requests
  7. Dependency Analysis
  8. Undo Last Operation
  9. View AVL Tree
  10. Exit
------------------------------------------------------------
  Enter choice:
```

### Menu Options Explained

#### 1️⃣ Project Status
- Displays all projects in sorted order (using BST in-order traversal)
- Search for specific project by ID
- Shows: ID, Name, Status, Progress %

#### 2️⃣ Equipment Usage
- Lists all equipment with availability status
- Fast lookup using Hash Table (O(1) average)
- Shows equipment assignments

#### 3️⃣ Workforce Allocation
- Displays all workers with skills and assigned projects
- Search workers by ID
- Records worker assignments

#### 4️⃣ Construction Schedule
- Demonstrates Merge Sort and Quick Sort on tasks
- Sorts tasks by priority level
- Compares sorting algorithm performance

#### 5️⃣ Progress Reports
- Visual progress bars for each project
- Linear search for completed projects (case-insensitive)
- Project completion overview

#### 6️⃣ Resource Requests
- Manages queue of resource requests (FIFO order)
- Display pending requests
- Process requests and track operations

#### 7️⃣ Dependency Analysis
- Graph visualization of construction stages
- BFS traversal for shortest path
- DFS traversal for all possible sequences
- Critical path identification

#### 8️⃣ Undo Last Operation
- View complete operation history (Stack)
- Undo any previous operation
- Rollback functionality demonstration

#### 9️⃣ View AVL Tree
- Display projects in AVL tree structure
- Shows node heights
- Demonstrates tree balancing

#### 🔟 Exit
- Gracefully exit the program

---

## 📁 File Structure

```
construction-management-system/
├── main.cpp                    # Main program with all implementations
├── projects.txt               # Project data (ID, Name, Status, Progress)
├── workers.txt               # Worker data (ID, Name, Skill, Project)
├── equipment.txt             # Equipment data (ID, Name, Status)
├── tasks.txt                 # Task data (ID, Name, Priority, Status)
├── requests.txt              # Resource request data (ID, Desc, Project, Priority)
├── README.md                 # This file
├── Construction_Management_System_Report.docx  # Full project report
└── Construction_Management_System_Report.pdf   # PDF version of report
```

---

## 📊 Sample Data Format

### projects.txt
```
101 CityMall_Complex ONGOING 65
102 Highway_Bridge PLANNING 10
103 Residential_Tower ONGOING 80
104 Office_Park COMPLETED 100
105 Airport_Terminal PLANNING 20
```

### workers.txt
```
W001 Ramesh_Kumar Mason 101
W002 Suresh_Singh Electrician 103
W003 Anita_Sharma Plumber 101
W004 Vikram_Patel Carpenter 102
```

### equipment.txt
```
E001 Tower_Crane IN_USE
E002 Excavator AVAILABLE
E003 Concrete_Mixer IN_USE
E004 Bulldozer MAINTENANCE
```

### tasks.txt
```
T001 Site_Survey 1 DONE
T002 Foundation_Laying 2 DONE
T003 Pillar_Construction 3 IN_PROGRESS
```

### requests.txt
```
REQ001 Crane_Request Project_101 HIGH
REQ002 Excavator_Request Project_102 MEDIUM
REQ003 Electrician_Request Project_103 HIGH
```

---

## 🎓 Learning Outcomes

This project demonstrates:

1. **Linear Data Structures:**
   - Stack operations (Push, Pop, Display)
   - Queue operations (Enqueue, Dequeue, Display)

2. **Hierarchical Data Structures:**
   - Binary Search Tree (BST) insertion and search
   - AVL Tree with rotations and balancing

3. **Hash-based Data Structures:**
   - Hash table implementation using unordered_map
   - O(1) average-case lookup performance

4. **Graph Algorithms:**
   - BFS (Breadth-First Search)
   - DFS (Depth-First Search)
   - Dependency and critical path analysis

5. **Sorting Algorithms:**
   - Merge Sort implementation
   - Quick Sort implementation
   - Performance comparison

6. **Searching Techniques:**
   - Linear search with case-insensitive comparison
   - Binary search tree search
   - Hash table search

7. **Software Engineering:**
   - Modular code design
   - File I/O handling
   - Error handling
   - User-friendly interface

---

## 💡 Algorithm Complexity Analysis

| Operation | Data Structure | Time | Space |
|---|---|---|---|
| Insert/Search | BST | O(log n) avg | O(n) |
| Insert/Search | AVL | O(log n) | O(n) |
| Insert/Search | Hash Table | O(1) avg | O(n) |
| Sort | Merge Sort | O(n log n) | O(n) |
| Sort | Quick Sort | O(n log n) avg | O(log n) |
| Traverse | Graph BFS/DFS | O(V + E) | O(V) |
| Push/Pop | Stack | O(1) | O(n) |
| Enqueue/Dequeue | Queue | O(1) | O(n) |

---

## 🔧 Code Organization

### Main Components in `main.cpp`

1. **Utility Functions**
   - `printLine()`: Print formatted lines
   - `printHeader()`: Print section headers
   - `caseInsensitiveEqual()`: String comparison

2. **Data Structures**
   - `Task`: Represents construction tasks
   - `Worker`: Represents workforce
   - `Equipment`: Represents machinery
   - `Project`: Represents construction projects
   - `Request`: Represents resource requests

3. **Core Classes**
   - `OperationStack`: Stack implementation for undo
   - `RequestQueue`: Queue implementation for requests
   - `BST`: Binary Search Tree for projects
   - `AVL`: AVL Tree for balanced storage
   - `WorkerHashTable`: Hash table for workers
   - `EquipmentHashTable`: Hash table for equipment
   - `Graph`: Graph for dependency analysis

4. **Sorting Algorithms**
   - `merge()`: Merge operation for merge sort
   - `mergeSort()`: Merge sort implementation
   - `partition()`: Partition for quick sort
   - `quickSort()`: Quick sort implementation

5. **File Loading Functions**
   - `loadProjects()`: Load project data
   - `loadWorkers()`: Load worker data
   - `loadEquipment()`: Load equipment data
   - `loadTasks()`: Load task data
   - `loadRequests()`: Load request data

6. **Menu Handlers** (9 functions)
   - `showProjectStatus()`
   - `showEquipmentUsage()`
   - `showWorkforceAllocation()`
   - `showConstructionSchedule()`
   - `showProgressReports()`
   - `showResourceRequests()`
   - `showDependencyAnalysis()`
   - `undoLastOperation()`
   - `showAVLTree()`

---

## 📝 Example Workflow

### Scenario: Manage Project 101 Resources

```
1. Select Option 1 (Project Status)
   → View CityMall_Complex (Project 101) - 65% complete

2. Select Option 3 (Workforce Allocation)
   → Search for W001 (Ramesh_Kumar - Mason)
   → Confirm assignment to Project 101

3. Select Option 2 (Equipment Usage)
   → Search for E001 (Tower_Crane)
   → Check availability and status

4. Select Option 6 (Resource Requests)
   → Process pending crane request for Project 101
   → Queue removes and processes request

5. Select Option 5 (Progress Reports)
   → View Project 101 progress: 65% (████████░░░░░░)

6. Select Option 8 (Undo Last Operation)
   → Review operation history
   → Rollback if needed
```

---

## 🐛 Error Handling

The system handles:
- **Missing Files:** Displays error message and continues
- **Invalid Input:** Re-prompts for correct input
- **Search Not Found:** Displays "not found" message gracefully
- **Empty Queues/Stacks:** Handles empty collection operations

---

## 🚀 Performance Notes

- **Project Lookup:** O(log n) using BST
- **Equipment Lookup:** O(1) using Hash Table
- **Task Sorting:** O(n log n) using Merge/Quick Sort
- **Dependency Analysis:** O(V + E) using BFS/DFS
- **Overall Memory:** Efficient with dynamic allocation

---

## 📌 Key Features Implementation

### ✅ Stack (Undo Functionality)
```cpp
OperationStack ops;
ops.push("Add_Project: Airport_Terminal_P105");
ops.pop();  // Undo last operation
```

### ✅ Queue (FIFO Request Processing)
```cpp
RequestQueue rq;
rq.enqueue(request);
Request r = rq.dequeue();  // Process next request
```

### ✅ BST (Project Management)
```cpp
BST bst;
bst.insert(project);
bst.searchAndDisplay(101);  // Find project by ID
```

### ✅ AVL Tree (Balanced Storage)
```cpp
AVL avl;
avl.insert(project);
avl.display();  // Show balanced tree structure
```

### ✅ Hash Tables (Fast Lookup)
```cpp
WorkerHashTable wht;
wht.insert(worker);
Worker* found = wht.search("W001");  // O(1) lookup
```

### ✅ Graph (Dependency Analysis)
```cpp
Graph g(7);
g.addEdge(0, 1);  // Foundation -> Pillars
g.bfs(0);  // Shortest path
g.dfs(0);  // All sequences
```

---

## 🎯 Real-World Applications

This system can be extended for:
- **Actual Construction Companies:** Real project management
- **Manufacturing:** Production scheduling
- **Software Projects:** Task and resource management
- **Healthcare:** Patient and resource scheduling
- **Logistics:** Delivery route optimization

---

## 📚 Resources & References

### Data Structures Concepts
- Binary Search Trees
- AVL Trees and Rotations
- Hash Tables and Collision Resolution
- Graph Representation and Traversal
- Stack and Queue Operations

### Algorithms Concepts
- Sorting: Merge Sort, Quick Sort
- Searching: Linear, Binary Search
- Graph Algorithms: BFS, DFS
- Tree Operations: Insertion, Deletion, Balancing

---

## 👥 Contributors

**Project Developers:** B.Tech CSE Students  
**Institution:** ITM Skills University  
**Academic Year:** 2025-2029  
**Semester:** II

---

## 📄 Documentation

- **Full Report:** See `Construction_Management_System_Report.docx` or `.pdf`
- **Code Comments:** Inline comments in `main.cpp`
- **Data Formats:** Described in File Structure section above

---

## 🔐 License & Acknowledgments

This project is developed as part of the Data Structures & Algorithms curriculum at ITM Skills University.

**Acknowledgments:**
- Course Faculty for guidance on DSA concepts
- ITM Skills University for providing resources
- Open-source C++ libraries and tools

---

## 🤝 Support & Contribution

For questions or improvements:
1. Review the code comments in `main.cpp`
2. Check the full report for detailed explanations
3. Refer to the sample data files for format specifications

---

## 📋 Checklist for Running the Project

- [ ] Install C++ compiler (GCC 7.0+)
- [ ] Download all project files
- [ ] Verify all 5 data files are present:
  - [ ] projects.txt
  - [ ] workers.txt
  - [ ] equipment.txt
  - [ ] tasks.txt
  - [ ] requests.txt
- [ ] Compile: `g++ -std=c++11 main.cpp -o construction_system`
- [ ] Run: `./construction_system`
- [ ] Test all 9 menu options
- [ ] Review operation history with Undo feature

---

**Last Updated:** June 2026  
**Project Status:** ✅ Complete & Tested

---

**Happy Building! 🏗️**

For more information, refer to the comprehensive project report included in this package.