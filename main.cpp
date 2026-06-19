#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <random>

using namespace std;

// ============================================================
//  UTILITY CLASS
// ============================================================
class ConsoleUtils
{
public:
    static void printLine(char c = '-', int n = 60)
    {
        for (int i = 0; i < n; i++)
            cout << c;
        cout << "\n";
    }

    static void printHeader(const string &title)
    {
        cout << "\n";
        printLine('=');
        cout << "  " << title << "\n";
        printLine('=');
    }

    static bool caseInsensitiveEqual(const string &a, const string &b)
    {
        if (a.length() != b.length())
            return false;
        return equal(a.begin(), a.end(), b.begin(),
                     [](char x, char y)
                     { return tolower(x) == tolower(y); });
    }
};

// ============================================================
//  DATA STRUCTURE CLASSES
// ============================================================

// ---- Task ----
class Task
{
public:
    string id, name, status;
    int priority;

    Task() : id(""), name(""), status(""), priority(0) {}
    Task(string i, string n, int p, string s)
        : id(i), name(n), priority(p), status(s) {}
};

// ---- Worker ----
class Worker
{
public:
    string id, name, skill, project;

    Worker() : id(""), name(""), skill(""), project("") {}
    Worker(string i, string n, string sk, string p)
        : id(i), name(n), skill(sk), project(p) {}
};

// ---- Equipment ----
class Equipment
{
public:
    string id, name, status;

    Equipment() : id(""), name(""), status("") {}
    Equipment(string i, string n, string s)
        : id(i), name(n), status(s) {}
};

// ---- Project ----
class Project
{
public:
    int id, progress;
    string name, status;

    Project() : id(0), name(""), status(""), progress(0) {}
    Project(int i, string n, string s, int p)
        : id(i), name(n), status(s), progress(p) {}
};

// ---- Request ----
class Request
{
public:
    string id, description, project, priority;

    Request() : id(""), description(""), project(""), priority("") {}
    Request(string i, string d, string p, string pr)
        : id(i), description(d), project(p), priority(pr) {}
};

// ============================================================
//  STACK IMPLEMENTATION - Undo Operations
// ============================================================
class OperationStack
{
private:
    stack<string> ops;

public:
    void push(const string &op)
    {
        ops.push(op);
        cout << "  [Stack] Operation recorded: " << op << "\n";
    }

    string pop()
    {
        if (ops.empty())
            return "";
        string top = ops.top();
        ops.pop();
        return top;
    }

    void displayAll() const
    {
        if (ops.empty())
        {
            cout << "  No operations recorded.\n";
            return;
        }
        stack<string> tmp = ops;
        int idx = 1;
        cout << "  Rollback history (most recent first):\n";
        while (!tmp.empty())
        {
            cout << "    " << idx++ << ". " << tmp.top() << "\n";
            tmp.pop();
        }
    }
};

// ============================================================
//  QUEUE IMPLEMENTATION - Resource Requests (FIFO)
// ============================================================
class RequestQueue
{
private:
    queue<Request> rq;

public:
    void enqueue(const Request &r)
    {
        rq.push(r);
    }

    Request dequeue()
    {
        Request r = rq.front();
        rq.pop();
        return r;
    }

    bool empty() const
    {
        return rq.empty();
    }

    void displayAll() const
    {
        if (rq.empty())
        {
            cout << "  No pending requests.\n";
            return;
        }
        queue<Request> tmp = rq;
        cout << "  " << left
             << setw(10) << "Req ID"
             << setw(22) << "Description"
             << setw(14) << "Project"
             << setw(8) << "Priority" << "\n";
        ConsoleUtils::printLine('-', 55);
        while (!tmp.empty())
        {
            Request r = tmp.front();
            tmp.pop();
            cout << "  " << left
                 << setw(10) << r.id
                 << setw(22) << r.description
                 << setw(14) << r.project
                 << setw(8) << r.priority << "\n";
        }
    }
};

// ============================================================
//  BST IMPLEMENTATION - Project Database
// ============================================================
class BSTNode
{
public:
    Project data;
    BSTNode *left;
    BSTNode *right;

    BSTNode(Project p) : data(p), left(nullptr), right(nullptr) {}
};

class BST
{
private:
    BSTNode *root;

    // Builds BST
    BSTNode *insertHelper(BSTNode *node, Project p)
    {
        if (!node)
            return new BSTNode(p);
        if (p.id < node->data.id)
            node->left = insertHelper(node->left, p);
        else if (p.id > node->data.id)
            node->right = insertHelper(node->right, p);
        return node;
    }

    BSTNode *searchHelper(BSTNode *node, int id) const
    {
        if (!node || node->data.id == id)
            return node;
        if (id < node->data.id)
            return searchHelper(node->left, id);
        return searchHelper(node->right, id);
    }

    void inorderHelper(BSTNode *node) const
    {
        if (!node)
            return;
        inorderHelper(node->left);
        cout << "  " << left
             << setw(6) << node->data.id
             << setw(22) << node->data.name
             << setw(12) << node->data.status
             << node->data.progress << "%\n";
        inorderHelper(node->right);
    }

public:
    BST() : root(nullptr) {}

    void insert(Project p)
    {
        root = insertHelper(root, p);
    }

    void display() const
    {
        inorderHelper(root);
    }

    void searchAndDisplay(int id) const
    {
        BSTNode *res = searchHelper(root, id);
        if (res)
            cout << "  Found -> ID: " << res->data.id
                 << "  Name: " << res->data.name
                 << "  Status: " << res->data.status
                 << "  Progress: " << res->data.progress << "%\n";
        else
            cout << "  Project ID " << id << " not found in BST.\n";
    }
};

// ============================================================
//  AVL TREE IMPLEMENTATION - Balanced Project Storage
// ============================================================
class AVLNode
{
public:
    Project data;
    AVLNode *left;
    AVLNode *right;
    int height;

    AVLNode(Project p) : data(p), left(nullptr), right(nullptr), height(1) {}
};

class AVL
{
private:
    AVLNode *root;

    int height(AVLNode *n) const
    {
        return n ? n->height : 0;
    }

    int balanceFactor(AVLNode *n) const
    {
        return n ? height(n->left) - height(n->right) : 0;
    }

    void updateHeight(AVLNode *n)
    {
        if (n)
            n->height = 1 + max(height(n->left), height(n->right));
    }

    AVLNode *rotateRight(AVLNode *y)
    {
        AVLNode *x = y->left;
        AVLNode *T2 = x->right;
        x->right = y;
        y->left = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    AVLNode *rotateLeft(AVLNode *x)
    {
        AVLNode *y = x->right;
        AVLNode *T2 = y->left;
        y->left = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    AVLNode *balance(AVLNode *n)
    {
        updateHeight(n);
        int bf = balanceFactor(n);
        if (bf > 1)
        {
            if (balanceFactor(n->left) < 0)
                n->left = rotateLeft(n->left);
            return rotateRight(n);
        }
        if (bf < -1)
        {
            if (balanceFactor(n->right) > 0)
                n->right = rotateRight(n->right);
            return rotateLeft(n);
        }
        return n;
    }

    // Buids bst
    AVLNode *insertHelper(AVLNode *node, Project p)
    {
        if (!node)
            return new AVLNode(p);
        if (p.id < node->data.id)
            node->left = insertHelper(node->left, p);
        else if (p.id > node->data.id)
            node->right = insertHelper(node->right, p);
        return balance(node);
    }

    void inorderHelper(AVLNode *node) const
    {
        if (!node)
            return;
        inorderHelper(node->left);
        cout << "  " << left
             << setw(6) << node->data.id
             << setw(22) << node->data.name
             << setw(12) << node->data.status
             << "H=" << node->height << "\n";
        inorderHelper(node->right);
    }

public:
    AVL() : root(nullptr) {}

    void insert(Project p)
    {
        root = insertHelper(root, p);
    }

    void display() const
    {
        inorderHelper(root);
    }
};

// ============================================================
//  HASH TABLE IMPLEMENTATION - Workers
// ============================================================
class WorkerHashTable
{
private:
    unordered_map<string, Worker> table;

public:
    void insert(const Worker &w)
    {
        table[w.id] = w;
    }

    Worker *search(const string &id)
    {
        auto it = table.find(id);
        if (it != table.end())
        {
            return &(it->second);
        }
        return nullptr;
    }

    void displaySearchResult(const string &id) const
    {
        auto it = table.find(id);
        if (it != table.end())
        {
            const Worker &w = it->second;
            cout << "  Found -> ID: " << w.id
                 << "  Name: " << w.name
                 << "  Skill: " << w.skill
                 << "  Project: " << w.project << "\n";
        }
        else
        {
            cout << "  Worker ID " << id << " not found.\n";
        }
    }

    void displayAll() const
    {
        cout << "  " << left
             << setw(8) << "ID"
             << setw(18) << "Name"
             << setw(18) << "Skill"
             << setw(10) << "Project" << "\n";
        ConsoleUtils::printLine('-', 55);
        for (auto &kv : table)
        {
            const Worker &w = kv.second;
            cout << "  " << left
                 << setw(8) << w.id
                 << setw(18) << w.name
                 << setw(18) << w.skill
                 << setw(10) << w.project << "\n";
        }
    }
};

// ============================================================
//  HASH TABLE IMPLEMENTATION - Equipment
// ============================================================
class EquipmentHashTable
{
private:
    unordered_map<string, Equipment> table;

public:
    void insert(const Equipment &e)
    {
        table[e.id] = e;
    }

    void search(const string &id) const
    {
        auto it = table.find(id);
        if (it != table.end())
        {
            const Equipment &e = it->second;
            cout << "  Found -> ID: " << e.id
                 << "  Name: " << e.name
                 << "  Status: " << e.status << "\n";
        }
        else
        {
            cout << "  Equipment ID " << id << " not found.\n";
        }
    }

    void displayAll() const
    {
        cout << "  " << left
             << setw(10) << "ID"
             << setw(22) << "Name"
             << setw(12) << "Status" << "\n";
        ConsoleUtils::printLine('-', 45);
        for (auto &kv : table)
        {
            const Equipment &e = kv.second;
            cout << "  " << left
                 << setw(10) << e.id
                 << setw(22) << e.name
                 << setw(12) << e.status << "\n";
        }
    }
};

// ============================================================
//  GRAPH IMPLEMENTATION - Project Dependency (BFS + DFS)
// ============================================================
class Graph
{
private:
    int V;
    vector<vector<int>> adj;
    vector<string> labels;

    void dfsHelper(int v, vector<bool> &visited, bool &first) const
    {
        visited[v] = true;
        if (!first)
            cout << " -> ";
        cout << labels[v];
        first = false;
        for (int n : adj[v])
        {
            if (!visited[n])
            {
                dfsHelper(n, visited, first);
            }
        }
    }

public:
    Graph(int v) : V(v), adj(v), labels(v) {}

    void setLabel(int i, const string &l)
    {
        labels[i] = l;
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
    }

    void bfs(int start) const
    {
        vector<bool> visited(V, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);
        cout << "  BFS Traversal: ";
        bool first = true;
        while (!q.empty())
        {
            int v = q.front();
            q.pop();
            if (!first)
                cout << " -> ";
            cout << labels[v];
            first = false;
            for (int n : adj[v])
            {
                if (!visited[n])
                {
                    visited[n] = true;
                    q.push(n);
                }
            }
        }
        cout << "\n";
    }

    void dfs(int start) const
    {
        vector<bool> visited(V, false);
        bool first = true;
        cout << "  DFS Traversal: ";
        dfsHelper(start, visited, first);
        cout << "\n";
    }
};

// ============================================================
//  TASK SORTING CLASS
// ============================================================
class TaskSorter
{
private:
    static void merge(vector<Task> &arr, int l, int m, int r)
    {
        int n1 = m - l + 1, n2 = r - m;
        vector<Task> L(arr.begin() + l, arr.begin() + m + 1);
        vector<Task> R(arr.begin() + m + 1, arr.begin() + r + 1);
        int i = 0, j = 0, k = l;
        while (i < n1 && j < n2)
        {
            if (L[i].priority <= R[j].priority)
                arr[k++] = L[i++];
            else
                arr[k++] = R[j++];
        }
        while (i < n1)
            arr[k++] = L[i++];
        while (j < n2)
            arr[k++] = R[j++];
    }

    static int partition(vector<Task> &arr, int low, int high)
    {
        int pivot = arr[high].priority;
        int i = low - 1;
        for (int j = low; j < high; j++)
        {
            if (arr[j].priority <= pivot)
            {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }

public:
    static void mergeSort(vector<Task> &arr, int l, int r)
    {
        if (l < r)
        {
            int m = (l + r) / 2;
            mergeSort(arr, l, m);
            mergeSort(arr, m + 1, r);
            merge(arr, l, m, r);
        }
    }

    static void quickSort(vector<Task> &arr, int low, int high)
    {
        if (low < high)
        {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

    static void printTasks(const vector<Task> &tasks)
    {
        cout << "  " << left
             << setw(8) << "Task ID"
             << setw(24) << "Name"
             << setw(10) << "Priority"
             << setw(14) << "Status" << "\n";
        ConsoleUtils::printLine('-', 58);
        for (const Task &t : tasks)
            cout << "  " << left
                 << setw(8) << t.id
                 << setw(24) << t.name
                 << setw(10) << t.priority
                 << setw(14) << t.status << "\n";
    }
};

// ============================================================
//  FILE LOADER CLASS
// ============================================================
class FileLoader
{
public:
    static vector<Project> loadProjects()
    {
        vector<Project> projects;
        ifstream f("projects.txt");
        if (!f)
        {
            cout << "  [Error] Cannot open projects.txt\n";
            return projects;
        }
        string line;
        while (getline(f, line))
        {
            if (line.empty())
                continue;
            istringstream ss(line);
            int id, progress;
            string name, status;
            ss >> id >> name >> status >> progress;
            projects.push_back(Project(id, name, status, progress));
        }
        return projects;
    }

    static vector<Worker> loadWorkers()
    {
        vector<Worker> workers;
        ifstream f("workers.txt");
        if (!f)
        {
            cout << "  [Error] Cannot open workers.txt\n";
            return workers;
        }
        string line;
        while (getline(f, line))
        {
            if (line.empty())
                continue;
            istringstream ss(line);
            string id, name, skill, project;
            ss >> id >> name >> skill >> project;
            workers.push_back(Worker(id, name, skill, project));
        }
        return workers;
    }

    static vector<Equipment> loadEquipment()
    {
        vector<Equipment> eq;
        ifstream f("equipment.txt");
        if (!f)
        {
            cout << "  [Error] Cannot open equipment.txt\n";
            return eq;
        }
        string line;
        while (getline(f, line))
        {
            if (line.empty())
                continue;
            istringstream ss(line);
            string id, name, status;
            ss >> id >> name >> status;
            eq.push_back(Equipment(id, name, status));
        }
        return eq;
    }

    static vector<Task> loadTasks()
    {
        vector<Task> tasks;
        ifstream f("tasks.txt");
        if (!f)
        {
            cout << "  [Error] Cannot open tasks.txt\n";
            return tasks;
        }
        string line;
        while (getline(f, line))
        {
            if (line.empty())
                continue;
            istringstream ss(line);
            string id, name, status;
            int priority;
            ss >> id >> name >> priority >> status;
            tasks.push_back(Task(id, name, priority, status));
        }
        return tasks;
    }

    static vector<Request> loadRequests()
    {
        vector<Request> reqs;
        ifstream f("requests.txt");
        if (!f)
        {
            cout << "  [Error] Cannot open requests.txt\n";
            return reqs;
        }
        string line;
        while (getline(f, line))
        {
            if (line.empty())
                continue;
            istringstream ss(line);
            string id, description, project, priority;
            ss >> id >> description >> project >> priority;
            reqs.push_back(Request(id, description, project, priority));
        }
        return reqs;
    }
};

// ============================================================
//  MAIN MANAGEMENT SYSTEM CLASS
// ============================================================
class ConstructionManagementSystem
{
private:
    // Data containers
    vector<Project> projects;
    vector<Worker> workers;
    vector<Equipment> equipment;
    vector<Request> requests;

    // Data structures
    BST bst;
    AVL avl;
    WorkerHashTable workerHashTable;
    EquipmentHashTable equipmentHashTable;
    RequestQueue requestQueue;
    OperationStack operationStack;

public:
    ConstructionManagementSystem()
    {
        // Load all data from files
        projects = FileLoader::loadProjects();
        workers = FileLoader::loadWorkers();
        equipment = FileLoader::loadEquipment();
        requests = FileLoader::loadRequests();

        // Build BST and AVL
        for (const Project &p : projects)
        {
            bst.insert(p);
            avl.insert(p);
        }

        // Build Hash Tables
        for (const Worker &w : workers)
        {
            workerHashTable.insert(w);
        }
        for (const Equipment &e : equipment)
        {
            equipmentHashTable.insert(e);
        }

        // Populate Queue
        for (const Request &r : requests)
        {
            requestQueue.enqueue(r);
        }

        // Pre-load demo operations
        operationStack.push("Add_Project: Airport_Terminal_P105");
        operationStack.push("Assign_Worker: W001_Ramesh -> Project_101");
    }

    // Menu Handler Methods
    void showProjectStatus()
    {
        ConsoleUtils::printHeader("1. PROJECT STATUS");
        cout << "  Displaying all projects (BST In-Order):\n\n";
        cout << "  " << left
             << setw(6) << "ID"
             << setw(22) << "Name"
             << setw(12) << "Status"
             << "Progress\n";
        ConsoleUtils::printLine('-', 50);
        bst.display();

        cout << "\n  Search project by ID (0 to skip): ";
        int id;
        cin >> id;
        if (id != 0)
            bst.searchAndDisplay(id);
    }

    void showEquipmentUsage()
    {
        ConsoleUtils::printHeader("2. EQUIPMENT USAGE");
        cout << "  Equipment loaded via Hash Table:\n\n";
        equipmentHashTable.displayAll();

        cout << "\n  Search equipment by ID (e.g. E001, 0 to skip): ";
        string id;
        cin >> id;
        if (id != "0")
            equipmentHashTable.search(id);

        cout << "\n  Simulate: Assigning " << id << " to Project_102...\n";
        operationStack.push("Assign_Equipment: " + id + " -> Project_102");
     
    }

    void showWorkforceAllocation()
    {
        ConsoleUtils::printHeader("3. WORKFORCE ALLOCATION");
        cout << "  Workers loaded via Hash Table:\n\n";
        workerHashTable.displayAll();

        cout << "\n  Search worker by ID (e.g. W001, 0 to skip): ";
        string id;
        cin >> id;

        if (id != "0")
        {
            Worker *foundWorker = workerHashTable.search(id);

            if (foundWorker != nullptr)
            {
                workerHashTable.displaySearchResult(id);

                cout << "\n  Simulating worker assignment to their project...\n";
                string assignmentMsg = "Assign_Worker: " + foundWorker->id + "_" + foundWorker->name +
                                       " -> Project_" + foundWorker->project;
                operationStack.push(assignmentMsg);
            }
        }
    }

    void showConstructionSchedule()
    {
        ConsoleUtils::printHeader("4. CONSTRUCTION SCHEDULE");
        vector<Task> tasks = FileLoader::loadTasks();
        if (tasks.empty())
            return;

        vector<Task> shuffled = tasks;
        mt19937 rng(42);
        shuffle(shuffled.begin(), shuffled.end(), rng);

        cout << "  Tasks BEFORE sorting (shuffled):\n";
        TaskSorter::printTasks(shuffled);

        vector<Task> forMerge = shuffled;
        TaskSorter::mergeSort(forMerge, 0, (int)forMerge.size() - 1);
        cout << "\n  Tasks after MERGE SORT (by priority):\n";
        TaskSorter::printTasks(forMerge);

        vector<Task> forQuick = shuffled;
        TaskSorter::quickSort(forQuick, 0, (int)forQuick.size() - 1);
        cout << "\n  Tasks after QUICK SORT (by priority):\n";
        TaskSorter::printTasks(forQuick);
    }

    void showProgressReports()
    {
        ConsoleUtils::printHeader("5. PROGRESS REPORTS");
        if (projects.empty())
            return;

        cout << "  Project completion overview:\n\n";
        cout << "  " << left << setw(22) << "Project" << "Progress\n";
        ConsoleUtils::printLine('-', 50);
        for (const Project &p : projects)
        {
            int bar = p.progress / 5;
            cout << "  " << left << setw(22) << p.name << "[";
            for (int i = 0; i < 20; i++)
                cout << (i < bar ? '#' : '.');
            cout << "] " << p.progress << "%\n";
        }

        cout << "\n  [Linear Search] Looking for COMPLETED projects:\n";
        bool found = false;
        for (const Project &p : projects)
        {
            if (ConsoleUtils::caseInsensitiveEqual(p.status, "COMPLETED"))
            {
                cout << "    -> " << p.name << " (" << p.progress << "%)\n";
                found = true;
            }
        }
        if (!found)
            cout << "    None found.\n";
    }

    void showResourceRequests()
    {
        ConsoleUtils::printHeader("6. RESOURCE REQUESTS");
        cout << "  Pending requests in Queue (FIFO order):\n\n";
        requestQueue.displayAll();

        cout << "\n  Process next request from queue? (1=Yes, 0=No): ";
        int ch;
        cin >> ch;
        if (ch == 1 && !requestQueue.empty())
        {
            Request r = requestQueue.dequeue();
            cout << "  [Queue] Processed: " << r.id << " - " << r.description << "\n";
            operationStack.push("Process_Request: " + r.id + "_" + r.description);
            cout << "  Remaining requests:\n";
            requestQueue.displayAll();
        }
    }

    void showDependencyAnalysis()
    {
        ConsoleUtils::printHeader("7. DEPENDENCY ANALYSIS");

        int N = 7;
        Graph g(N);
        vector<string> stages = {
            "Foundation", "Pillars", "Walls", "Roofing",
            "Electrical_Wiring", "Plumbing", "Interior_Finishing"};
        for (int i = 0; i < N; i++)
            g.setLabel(i, stages[i]);
        g.addEdge(0, 1);
        g.addEdge(1, 2);
        g.addEdge(2, 3);
        g.addEdge(3, 4);
        g.addEdge(3, 5);
        g.addEdge(4, 6);
        g.addEdge(5, 6);

        cout << "  Dependency Graph:\n";
        cout << "  Foundation -> Pillars -> Walls -> Roofing\n";
        cout << "                                      |\n";
        cout << "                         Electrical_Wiring --+\n";
        cout << "                                      |      v\n";
        cout << "                               Plumbing -> Interior_Finishing\n\n";

        g.bfs(0);
        cout << "\n";
        g.dfs(0);
        cout << "\n";

        cout << "  DSA Insight:\n";
        cout << "  - BFS finds shortest dependency path.\n";
        cout << "  - DFS explores all possible construction sequences.\n";
        cout << "  - Critical path: Foundation -> Pillars -> Walls -> Roofing -> Finishing\n";
    }

    void undoLastOperation()
    {
        ConsoleUtils::printHeader("8. UNDO LAST OPERATION");
        cout << "  Full operation history (Stack):\n";
        operationStack.displayAll();

        cout << "\n  Undo last operation? (1=Yes, 0=No): ";
        int ch;
        cin >> ch;
        if (ch == 1)
        {
            string op = operationStack.pop();
            if (!op.empty())
                cout << "  [Stack] Rolled back: " << op << "\n";
            else
                cout << "  [Stack] Nothing to undo.\n";
        }
    }

    void showAVLTree()
    {
        ConsoleUtils::printHeader("9. VIEW AVL TREE");
        cout << "  Projects in AVL (In-Order, showing node height):\n\n";
        cout << "  " << left
             << setw(6) << "ID"
             << setw(22) << "Name"
             << setw(12) << "Status"
             << "Height\n";
        ConsoleUtils::printLine('-', 50);
        avl.display();
        cout << "\n  (Height shows AVL balancing - keeps tree O(log n))\n";
    }

    // Main menu loop
    void run()
    {
        int choice = -1;
        while (choice != 10)
        {
            ConsoleUtils::printLine('=');
            cout << "    SMART CONSTRUCTION PROJECT & RESOURCE MANAGEMENT\n";
            ConsoleUtils::printLine('=');
            cout << "  1. Project Status\n";
            cout << "  2. Equipment Usage\n";
            cout << "  3. Workforce Allocation\n";
            cout << "  4. Construction Schedule\n";
            cout << "  5. Progress Reports\n";
            cout << "  6. Resource Requests\n";
            cout << "  7. Dependency Analysis\n";
            cout << "  8. Undo Last Operation\n";
            cout << "  9. View AVL Tree\n";
            cout << "  10. Exit\n";
            ConsoleUtils::printLine('-');
            cout << "  Enter choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                showProjectStatus();
                break;
            case 2:
                showEquipmentUsage();
                break;
            case 3:
                showWorkforceAllocation();
                break;
            case 4:
                showConstructionSchedule();
                break;
            case 5:
                showProgressReports();
                break;
            case 6:
                showResourceRequests();
                break;
            case 7:
                showDependencyAnalysis();
                break;
            case 8:
                undoLastOperation();
                break;
            case 9:
                showAVLTree();
                break;
            case 10:
                ConsoleUtils::printLine('=');
                cout << "  Exiting system. Goodbye!\n";
                ConsoleUtils::printLine('=');
                break;
            default:
                cout << "  Invalid option. Please enter 1-10.\n";
            }

            if (choice != 10 && choice >= 1 && choice <= 9)
            {
                cout << "\n  Press Enter to return to menu...";
                cin.ignore();
                cin.get();
            }
        }
    }
};

// ============================================================
//  MAIN ENTRY POINT
// ============================================================
int main()
{
    srand(42);
    ConstructionManagementSystem system;
    system.run();
    return 0;
}