#include <iostream>
#include <iomanip> //Library for formatted (table view) display
using namespace std;

class Student
{
public:
    int student_id;
    string name;
    int age;
    string department;
    double gpa;
    Student *next;

    Student(int id, string n, int a, string d, double g)
    {
        student_id = id;
        name = n;
        age = a;
        department = d;
        gpa = g;
        next = NULL;
    }
};

void display(Student *head)
{
    cout << "================================================================" << endl;
    cout << left << setw(10) << "ID" << setw(15) << "Name" << setw(5) << "Age"
         << setw(20) << "Department" << setw(5) << "GPA" << endl;
    cout << "================================================================" << endl;
    Student *temp = head;
    while (temp != NULL)
    {
        cout << left << setw(10) << temp->student_id << setw(15) << temp->name << setw(5) << temp->age
             << setw(20) << temp->department << setw(5) << fixed << setprecision(2) << temp->gpa << endl;
        temp = temp->next;
    }
}

void insertAthead(Student *&head, int id, string name, int age, string department, double gpa)
{
    Student *newstudent = new Student(id, name, age, department, gpa);
    newstudent->next = head;
    head = newstudent;
}

void insertAtend(Student *&head, int id, string name, int age, string department, double gpa)
{
    Student *newstudent = new Student(id, name, age, department, gpa);
    if (head == NULL)
    {
        insertAthead(head, id, name, age, department, gpa);
        return;
    }

    Student *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = newstudent;
}

void insertAtposition(Student *&head, int pos, int id, string name, int age, string department, double gpa)
{
    Student *newstudent = new Student(id, name, age, department, gpa);

    if (pos == 1)
    {
        insertAthead(head, id, name, age, department, gpa);
        return;
    }

    Student *prev = head;
    int count = 1;

    while (count < (pos - 1))
    {
        prev = prev->next;
        count++;
    }

    if (prev == NULL)
    {
        cout << "Position out of range." << endl;
        free(newstudent);
        return;
    }
    newstudent->next = prev->next;
    prev->next = newstudent;
}

void deleteAthead(Student *&head)
{
    if (head == NULL)
    {
        return;
    }

    Student *temp = head;
    head = head->next;
    free(temp);
}

void deleteAtend(Student *&head)
{
    if (head == NULL)
    {
        return;
    }

    if (head->next == NULL)
    {
        deleteAthead(head);
        return;
    }

    Student *secondLastnode = head;

    while (secondLastnode->next->next)
    {
        secondLastnode = secondLastnode->next;
    }

    Student *lastNode = secondLastnode->next;
    secondLastnode->next = NULL;
    free(lastNode);
}

void deleteAtposition(Student *&head, int pos)
{
    if (pos == 1)
    {
        deleteAthead(head);
    }

    Student *prev = head;
    int count = 1;
    while (count < (pos - 1))
    {
        prev = prev->next;
        count++;
    }

    Student *curr = prev->next;
    prev->next = curr->next;
    free(curr);
}

void search(Student *&head, int id)
{
    if (head == NULL)
    {
        cout << "List is empty." << endl;
        return;
    }
    Student *temp = head;
    bool found = false;

    while (temp != NULL)
    {
        if (temp->student_id == id)
        {
            cout << "Found." << endl;
            cout << "================================================================" << endl;
            cout << left << setw(10) << "ID" << setw(15) << "Name" << setw(5) << "Age"
                 << setw(20) << "Department" << setw(5) << "GPA" << endl;
            cout << "================================================================" << endl;

            cout << left << setw(10) << temp->student_id << setw(15) << temp->name << setw(5) << temp->age
                 << setw(20) << temp->department << setw(5) << fixed << setprecision(2) << temp->gpa << endl;

            found = true;
            break;
        }

        temp = temp->next;
    }
    if (!found)
    {
        cout << "Student not found." << endl;
    }
}

void bubbleSort(Student *head)
{
    if (head == NULL)
        return;

    bool swapped;
    do
    {
        swapped = false;
        Student *curr = head;

        while (curr->next != NULL)
        {
            Student *next = curr->next;

            if (curr->student_id > next->student_id)
            {

                int temp_id = curr->student_id;
                string temp_name = curr->name;
                int temp_age = curr->age;
                string temp_dep = curr->department;
                double temp_gpa = curr->gpa;

                curr->student_id = next->student_id;
                curr->name = next->name;
                curr->age = next->age;
                curr->department = next->department;
                curr->gpa = next->gpa;

                next->student_id = temp_id;
                next->name = temp_name;
                next->age = temp_age;
                next->department = temp_dep;
                next->gpa = temp_gpa;

                swapped = true;
            }
            curr = curr->next;
        }
    } while (swapped);
}

void insertionSort(Student *&head)
{
    if (head == NULL)
    {
        return;
    }

    Student *sorted = NULL;
    Student *curr = head;

    while (curr != NULL)
    {
        Student *next = curr->next;

        if (sorted == NULL || sorted->student_id >= curr->student_id)
        {
            curr->next = sorted;
            sorted = curr;
        }
        else
        {
            Student *temp = sorted;
            while (temp->next != NULL && temp->next->student_id < curr->student_id)
            {
                temp = temp->next;
            }
            curr->next = temp->next;
            temp->next = curr;
        }
        curr = next;
    }
    head = sorted;
}

void selectionSort(Student *head)
{
    if (head == NULL)
    {
        return;
    }

    Student *curr = head;

    while (curr != NULL)
    {
        Student *minNode = curr;
        Student *next = curr->next;

        while (next != NULL)
        {
            if (minNode->student_id > next->student_id)
            {
                minNode = next;
            }
            next = next->next;
        }

        if (minNode != curr)
        {
            int temp_id = curr->student_id;
            string temp_name = curr->name;
            int temp_age = curr->age;
            string temp_dep = curr->department;
            double temp_gpa = curr->gpa;

            curr->student_id = minNode->student_id;
            curr->name = minNode->name;
            curr->age = minNode->age;
            curr->department = minNode->department;
            curr->gpa = minNode->gpa;

            minNode->student_id = temp_id;
            minNode->name = temp_name;
            minNode->age = temp_age;
            minNode->department = temp_dep;
            minNode->gpa = temp_gpa;
        }
        curr = next;
    }
}

class Student_double
{
public:
    int student_id;
    string name;
    int age;
    string department;
    double gpa;
    Student_double *next;
    Student_double *prev;
};

void insertAtheadDouble(Student_double *&head, int id, string name, int age, string department, double gpa)
{
    Student_double *S = new Student_double();
    S->student_id = id;
    S->name = name;
    S->age = age;
    S->department = department;
    S->gpa = gpa;
    S->next = head;
    S->prev = NULL;
    if (head != NULL)
    {
        head->prev = S;
    }
    head = S;
}

void insertAtEndDouble(Student_double *&head, int id, string name, int age, string department, double gpa)
{
    Student_double *newNode = new Student_double();
    newNode->student_id = id;
    newNode->name = name;
    newNode->age = age;
    newNode->department = department;
    newNode->gpa = gpa;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (head == NULL)
    {
        head = newNode;
        return;
    }

    Student_double *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = newNode;
    newNode->prev = temp;
}

void insertAtPositionDouble(Student_double *&head, int pos, int id, string name, int age, string department, double gpa)
{
    Student_double *newNode = new Student_double();
    newNode->student_id = id;
    newNode->name = name;
    newNode->age = age;
    newNode->department = department;
    newNode->gpa = gpa;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (pos == 1)
    {
        newNode->next = head;
        if (head != NULL)
        {
            head->prev = newNode;
        }
        head = newNode;
        return;
    }

    Student_double *temp = head;
    int count = 1;

    while (temp != NULL && count < pos - 1)
    {
        temp = temp->next;
        count++;
    }

    if (temp == NULL)
    {
        cout << "Position out of range." << endl;
        free(newNode);
        return;
    }

    newNode->next = temp->next;
    newNode->prev = temp;

    if (temp->next != NULL)
    {
        temp->next->prev = newNode;
    }

    temp->next = newNode;
}

void deleteAtHeadDouble(Student_double *&head)
{
    if (head == NULL)
        return;

    Student_double *temp = head;
    head = head->next;

    if (head != NULL)
    {
        head->prev = NULL;
    }

    free(temp);
}

void deleteAtEndDouble(Student_double *&head)
{
    if (head == NULL)
        return;

    if (head->next == NULL)
    {
        deleteAtHeadDouble(head);
        return;
    }

    Student_double *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->prev->next = NULL;
    free(temp);
}

void deleteAtPositionDouble(Student_double *&head, int pos)
{
    if (head == NULL)
        return;

    if (pos == 1)
    {
        deleteAtHeadDouble(head);
        return;
    }

    Student_double *temp = head;
    int count = 1;

    while (temp != NULL && count < pos)
    {
        temp = temp->next;
        count++;
    }

    if (temp == NULL)
    {
        cout << "Position out of range." << endl;
        return;
    }

    if (temp->next != NULL)
    {
        temp->next->prev = temp->prev;
    }
    if (temp->prev != NULL)
    {
        temp->prev->next = temp->next;
    }

    free(temp);
}

void displayDouble(Student_double *head)
{
    cout << "================================================================" << endl;
    cout << left << setw(10) << "ID" << setw(15) << "Name" << setw(5) << "Age"
         << setw(20) << "Department" << setw(5) << "GPA" << endl;
    cout << "================================================================" << endl;

    Student_double *temp = head;
    while (temp != NULL)
    {
        cout << left << setw(10) << temp->student_id << setw(15) << temp->name << setw(5) << temp->age
             << setw(20) << temp->department << setw(5) << fixed << setprecision(2) << temp->gpa << endl;
        temp = temp->next;
    }
}

void bubbleSortDouble(Student_double *head)
{
    if (head == NULL)
        return;

    bool swapped;
    do
    {
        swapped = false;
        Student_double *curr = head;

        while (curr->next != NULL)
        {
            Student_double *next = curr->next;

            if (curr->student_id > next->student_id)
            {
                // Swap data fields
                int temp_id = curr->student_id;
                string temp_name = curr->name;
                int temp_age = curr->age;
                string temp_dep = curr->department;
                double temp_gpa = curr->gpa;

                curr->student_id = next->student_id;
                curr->name = next->name;
                curr->age = next->age;
                curr->department = next->department;
                curr->gpa = next->gpa;

                next->student_id = temp_id;
                next->name = temp_name;
                next->age = temp_age;
                next->department = temp_dep;
                next->gpa = temp_gpa;

                swapped = true;
            }
            curr = curr->next;
        }
    } while (swapped);
}

void insertionSortDouble(Student_double *&head)
{
    if (head == NULL)
        return;

    Student_double *sorted = NULL;
    Student_double *curr = head;

    while (curr != NULL)
    {
        Student_double *next = curr->next;

        if (sorted == NULL || sorted->student_id >= curr->student_id)
        {
            curr->next = sorted;
            if (sorted != NULL)
            {
                sorted->prev = curr;
            }
            curr->prev = NULL;
            sorted = curr;
        }
        else
        {
            Student_double *temp = sorted;
            while (temp->next != NULL && temp->next->student_id < curr->student_id)
            {
                temp = temp->next;
            }
            curr->next = temp->next;
            if (temp->next != NULL)
                temp->next->prev = curr;
            temp->next = curr;
            curr->prev = temp;
        }
        curr = next;
    }
    head = sorted;
}

void selectionSortDouble(Student_double *head)
{
    if (head == NULL)
        return;

    Student_double *curr = head;

    while (curr != NULL)
    {
        Student_double *minNode = curr;
        Student_double *next = curr->next;

        while (next != NULL)
        {
            if (next->student_id < minNode->student_id)
            {
                minNode = next;
            }
            next = next->next;
        }

        if (minNode != curr)
        {
            // Swap data fields
            int temp_id = curr->student_id;
            string temp_name = curr->name;
            int temp_age = curr->age;
            string temp_dep = curr->department;
            double temp_gpa = curr->gpa;

            curr->student_id = minNode->student_id;
            curr->name = minNode->name;
            curr->age = minNode->age;
            curr->department = minNode->department;
            curr->gpa = minNode->gpa;

            minNode->student_id = temp_id;
            minNode->name = temp_name;
            minNode->age = temp_age;
            minNode->department = temp_dep;
            minNode->gpa = temp_gpa;
        }
        curr = curr->next;
    }
}

void searchDouble(Student_double *head, int id)
{
    if (head == NULL)
    {
        cout << "List is empty." << endl;
        return;
    }

    Student_double *temp = head;
    bool found = false;

    while (temp != NULL)
    {
        if (temp->student_id == id)
        {
            cout << "Found student:\n";
            cout << "================================================================" << endl;
            cout << left << setw(10) << "ID" << setw(15) << "Name" << setw(5) << "Age"
                 << setw(20) << "Department" << setw(5) << "GPA" << endl;
            cout << "================================================================" << endl;
            cout << left << setw(10) << temp->student_id << setw(15) << temp->name
                 << setw(5) << temp->age << setw(20) << temp->department
                 << setw(5) << fixed << setprecision(2) << temp->gpa << endl;
            found = true;
            break;
        }
        temp = temp->next;
    }

    if (!found)
    {
        cout << "Student not found." << endl;
    }
}

class Student_stack
{
public:
    int top = -1;
    int student_id[100];
    string name[100];
    int age[100];
    string department[100];
    double gpa[100];

    Student_stack()
    {
        top = -1;
    }

    void push(int id, string n, int a, string dep, double gp)
    {
        if (top == 99)
        {
            cout << "Stack overflow" << endl;
        }
        else
        {
            top++;
            student_id[top] = id;
            name[top] = n;
            age[top] = a;
            department[top] = dep;
            gpa[top] = gp;
        }
    }

    void pop()
    {
        if (top == -1)
        {
            cout << "Stack underflow" << endl;
        }
        else
        {
            cout << "Removed" << endl;
            cout << "Student id: " << student_id[top] << endl;
            cout << "Name: " << name[top] << endl;
            cout << "Age: " << age[top] << endl;
            cout << "Department: " << department[top] << endl;
            cout << "GPA: " << gpa[top] << endl;
            top--;
        }
    }

    void peek()
    {
        if (top == -1)
        {
            cout << "Stack empty" << endl;
        }
        else
        {
            cout << "Top element" << endl;
            cout << "Student id: " << student_id[top] << endl;
            cout << "Name: " << name[top] << endl;
            cout << "Age: " << age[top] << endl;
            cout << "Department: " << department[top] << endl;
            cout << "GPA: " << gpa[top] << endl;
        }
    }

    void display()
    {
        if (top == -1)
        {
            cout << "Stack empty" << endl;
            return;
        }

        cout << "================================================================" << endl;
        cout << left << setw(10) << "ID" << setw(15) << "Name" << setw(5) << "Age"
             << setw(20) << "Department" << setw(5) << "GPA" << endl;
        cout << "================================================================" << endl;

        for (int i = top; i >= 0; i--)
        {
            cout << left << setw(10) << student_id[i] << setw(15) << name[i] << setw(5) << age[i]
                 << setw(20) << department[i] << setw(5) << fixed << setprecision(2) << gpa[i] << endl;
        }
    }

    void search(int value)
    {
        if (top == -1)
        {
            cout << "Stack empty" << endl;
            return;
        }
        for (int i = top; i >= 0; i--)
        {
            if (student_id[i] == value)
            {
                cout << "-------------------------------------" << endl;
                cout << "Name: " << name[i] << endl;
                cout << "Age: " << age[i] << endl;
                cout << "Department: " << department[i] << endl;
                cout << "GPA: " << gpa[i] << endl;
                break;
            }
        }
    }
};

class Student_queue
{
public:
    int student_id[100];
    string name[100];
    int age[100];
    string department[100];
    double gpa[100];
    int front, rear;

    Student_queue()
    {
        front = 0;
        rear = -1;
    }

    void enquque(int id, string n, int a, string dep, double gp)
    {
        if (rear == 99)
        {
            cout << "Queue overflow" << endl;
        }
        else
        {
            rear++;
            student_id[rear] = id;
            name[rear] = n;
            age[rear] = a;
            department[rear] = dep;
            gpa[rear] = gp;
        }
    }

    void dequeue()
    {
        if (front > rear)
        {
            cout << "Queue underflow" << endl;
        }
        else
        {
            cout << "Removed " << endl;
            cout << "Student id: " << student_id[front] << endl;
            cout << "Name: " << name[front] << endl;
            cout << "Age: " << age[front] << endl;
            cout << "Department: " << department[front] << endl;
            cout << "GPA: " << gpa[front] << endl;
            front++;
        }
    }

    void peek()
    {
        if (front > rear)
        {
            cout << "Queue empty" << endl;
        }
        else
        {
            cout << "Front element " << endl;
            cout << "Student id: " << student_id[front] << endl;
            cout << "Name: " << name[front] << endl;
            cout << "Age: " << age[front] << endl;
            cout << "Department: " << department[front] << endl;
            cout << "GPA: " << gpa[front] << endl;
        }
    }

    void display_queue()
    {
        if (front > rear)
        {
            cout << "Queue empty" << endl;
            return;
        }
        cout << "================================================================" << endl;
        cout << left << setw(10) << "ID" << setw(15) << "Name" << setw(5) << "Age"
             << setw(20) << "Department" << setw(5) << "GPA" << endl;
        cout << "================================================================" << endl;
        for (int i = front; i <= rear; i++)
        {
            cout << left << setw(10) << student_id[i] << setw(15) << name[i] << setw(5) << age[i]
                 << setw(20) << department[i] << setw(5) << fixed << setprecision(2) << gpa[i] << endl;
        }
    }

    void search(int value)
    {
        if (front > rear)
        {
            cout << "Queue empty" << endl;
        }
        for (int i = front; i <= rear; i++)
        {
            if (student_id[i] == value)
            {
                cout << "Name: " << name[i] << endl;
                cout << "Age: " << age[i] << endl;
                cout << "Department: " << department[i] << endl;
                cout << "GPA: " << gpa[i] << endl;
                break;
            }
        }
    }
};

class Student_tree
{
public:
    int student_id;
    string name;
    int age;
    string department;
    double gpa;
    Student_tree *right;
    Student_tree *left;

    Student_tree(int id, string n, int a, string dep, double gp)
    {
        student_id = id;
        name = n;
        age = a;
        department = dep;
        gpa = gp;
        right = NULL;
        left = NULL;
    }
};

Student_tree *insert_tree(Student_tree *root, int id, string n, int a, string dep, double gp)
{
    if (root == NULL)
        return new Student_tree(id, n, a, dep, gp);

    if (id == root->student_id)
    {
        cout << "Student with this ID already exists." << endl;
        return root;
    }

    if (id < root->student_id)
        root->left = insert_tree(root->left, id, n, a, dep, gp);
    else
        root->right = insert_tree(root->right, id, n, a, dep, gp);

    return root;
}

Student_tree *findMin(Student_tree *node)
{
    while (node->left != NULL)
    {
        node = node->left;
    }
    return node;
}

Student_tree *delete_node(Student_tree *root, int id, bool &found)
{

    if (root == NULL)
    {
        cout << "Student not found" << endl;
        return NULL;
    }

    if (id < root->student_id)
    {
        root->left = delete_node(root->left, id, found);
    }
    else if (id > root->student_id)
    {
        root->right = delete_node(root->right, id, found);
    }
    else
    {
        found = true;
        // 1. Leaf node
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }

        // 2. Only right child
        else if (root->left == NULL)
        {
            Student_tree *temp = root->right;
            free(root);
            return temp;
        }

        // 3. Only left child
        else if (root->right == NULL)
        {
            Student_tree *temp = root->left;
            free(root);
            return temp;
        }

        // 4. Two children
        else
        {
            // Find the smallest one in right subtree
            Student_tree *successor = findMin(root->right);

            root->student_id = successor->student_id;
            root->name = successor->name;
            root->age = successor->age;
            root->department = successor->department;
            root->gpa = successor->gpa;

            // Delete the successor from the right subtree
            root->right = delete_node(root->right, successor->student_id, found);
        }
    }
    return root;
}

void display_tree_preorder(Student_tree *root)
{
    if (root == NULL)
    {
        return;
    }          
    cout << "================================================================" << endl;
    cout << left << setw(10) << "ID" << setw(15) << "Name" << setw(5) << "Age"
         << setw(20) << "Department" << setw(5) << "GPA" << endl;
    cout << "================================================================" << endl;

    cout << left << setw(10) << root->student_id << setw(15) << root->name << setw(5) << root->age
         << setw(20) << root->department << setw(5) << fixed << setprecision(2) << root->gpa << endl;

    display_tree_preorder(root->left);
    display_tree_preorder(root->right);
}

void display_tree_inorder(Student_tree *root)
{
    if (root == NULL)
    {
        return;
    }
    display_tree_inorder(root->left);
    cout << "================================================================" << endl;
    cout << left << setw(10) << "ID" << setw(15) << "Name" << setw(5) << "Age"
         << setw(20) << "Department" << setw(5) << "GPA" << endl;
    cout << "================================================================" << endl;

    cout << left << setw(10) << root->student_id << setw(15) << root->name << setw(5) << root->age
         << setw(20) << root->department << setw(5) << fixed << setprecision(2) << root->gpa << endl;

    display_tree_inorder(root->right);
}

void display_tree_postorder(Student_tree *root)
{
    if (root == NULL)
    {
        return;
    }
    
    display_tree_postorder(root->left);
    display_tree_postorder(root->right);
    cout << "================================================================" << endl;
    cout << left << setw(10) << "ID" << setw(15) << "Name" << setw(5) << "Age"
         << setw(20) << "Department" << setw(5) << "GPA" << endl;
    cout << "================================================================" << endl;

    cout << left << setw(10) << root->student_id << setw(15) << root->name << setw(5) << root->age
         << setw(20) << root->department << setw(5) << fixed << setprecision(2) << root->gpa << endl;
}

void search_tree(Student_tree *root, int value)
{
    if (root == NULL)
    {
        cout << "Empty tree" << endl;
        return;
    }
    if (root->student_id == value)
    {
        cout << "================================================================" << endl;
        cout << left << setw(10) << "ID" << setw(15) << "Name" << setw(5) << "Age"
             << setw(20) << "Department" << setw(5) << "GPA" << endl;
        cout << "================================================================" << endl;

        cout << left << setw(10) << root->student_id << setw(15) << root->name << setw(5) << root->age
             << setw(20) << root->department << setw(5) << fixed << setprecision(2) << root->gpa << endl;
        return;
    }
    if (value > root->student_id)
    {
        search_tree(root->right, value);
    }
    else
    {
        search_tree(root->left, value);
    }
}

int main()
{
    int id, age, choice, position;
    string name, department;
    double gpa;

    Student *S = NULL;
    Student_double *D = NULL;
    Student_stack *S1 = new Student_stack();
    Student_queue *Q = new Student_queue();
    Student_tree *root = NULL;

    do
    {
        cout << "=========================================================================" << endl;
        cout << "================= Student Information Management System =================" << endl;
        cout << "=========================================================================" << endl;
        cout << "1. Singly Linked List" << endl;
        cout << "2. Doubly Linked List" << endl;
        cout << "3. Stack" << endl;
        cout << "4. Queue" << endl;
        cout << "5. Tree" << endl;
        cout << "6. Exit" << endl;
        cout << "=========================================================================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "=============================================" << endl;
            cout << "               Single Linked List            " << endl;
            cout << "=============================================" << endl;
            int choice1;
            cout << "1. Insert at head" << endl;
            cout << "2. Insert at position" << endl;
            cout << "3. Insert at end" << endl;
            cout << "4. Delete at head" << endl;
            cout << "5. Delete at position" << endl;
            cout << "6. Delete at end" << endl;
            cout << "7. Sort (Bubble)" << endl;
            cout << "8. Sort (Insertion)" << endl;
            cout << "9. Sort (Selection)" << endl;
            cout << "10. Search" << endl;
            cout << "11. Display" << endl;
            cout << "12. Return to main menu" << endl;
            do
            {
                cout << "choice: ";
                cin >> choice1;
                switch (choice1)
                {
                case 1:
                    cout << "Enter id: ";
                    cin >> id;
                    cout << "Enter name: ";
                    cin >> name;
                    cout << "Enter age: ";
                    cin >> age;
                    cout << "Enter department: ";
                    cin.ignore();
                    getline(cin, department);
                    cout << "Enter GPA: ";
                    cin >> gpa;
                    insertAthead(S, id, name, age, department, gpa);
                    break;
                case 2:
                    cout << "Enter position: ";
                    cin >> position;
                    cout << "Enter id: ";
                    cin >> id;
                    cout << "Enter name: ";
                    cin >> name;
                    cout << "Enter age: ";
                    cin >> age;
                    cout << "Enter department: ";
                    cin.ignore();
                    getline(cin, department);
                    cout << "Enter GPA: ";
                    cin >> gpa;
                    insertAtposition(S, position, id, name, age, department, gpa);
                    break;
                case 3:
                    cout << "Enter id: ";
                    cin >> id;
                    cout << "Enter name: ";
                    cin >> name;
                    cout << "Enter age: ";
                    cin >> age;
                    cout << "Enter department: ";
                    cin.ignore();
                    getline(cin, department);
                    cout << "Enter GPA: ";
                    cin >> gpa;
                    insertAtend(S, id, name, age, department, gpa);
                    break;
                case 4:
                    deleteAthead(S);
                    break;
                case 5:
                    cout << "Enter Position: ";
                    cin >> position;
                    deleteAtposition(S, position);
                    break;
                case 6:
                    deleteAtend(S);
                    break;
                case 7:
                    bubbleSort(S);
                    break;
                case 8:
                    insertionSort(S);
                    break;
                case 9:
                    selectionSort(S);
                    break;
                case 10:
                    cout << "Enter id: ";
                    cin >> id;
                    search(S, id);
                    break;
                case 11:
                    display(S);
                    break;
                default:
                    break;
                }
            } while (choice1 != 12);

            break;
        case 2:
            cout << "=============================================" << endl;
            cout << "               Double Linked List            " << endl;
            cout << "=============================================" << endl;
            int choice2;
            cout << "1. Insert at head" << endl;
            cout << "2. Insert at position" << endl;
            cout << "3. Insert at end" << endl;
            cout << "4. Delete at head" << endl;
            cout << "5. Delete at position" << endl;
            cout << "6. Delete at end" << endl;
            cout << "7. Sort (Bubble)" << endl;
            cout << "8. Sort (Insertion)" << endl;
            cout << "9. Sort (Selection)" << endl;
            cout << "10. Search" << endl;
            cout << "11. Display" << endl;
            cout << "12. Return to main menu" << endl;
            do
            {
                cout << "choice: ";
                cin >> choice2;
                switch (choice2)
                {
                case 1:
                    cout << "Enter id: ";
                    cin >> id;
                    cout << "Enter name: ";
                    cin >> name;
                    cout << "Enter age: ";
                    cin >> age;
                    cout << "Enter department: ";
                    cin.ignore();
                    getline(cin, department);
                    cout << "Enter GPA: ";
                    cin >> gpa;
                    insertAtheadDouble(D, id, name, age, department, gpa);
                    break;
                case 2:
                    cout << "Enter position: ";
                    cin >> position;
                    cout << "Enter id: ";
                    cin >> id;
                    cout << "Enter name: ";
                    cin >> name;
                    cout << "Enter age: ";
                    cin >> age;
                    cout << "Enter department: ";
                    cin.ignore();
                    getline(cin, department);
                    cout << "Enter GPA: ";
                    cin >> gpa;
                    insertAtPositionDouble(D, position, id, name, age, department, gpa);
                    break;
                case 3:
                    cout << "Enter id: ";
                    cin >> id;
                    cout << "Enter name: ";
                    cin >> name;
                    cout << "Enter age: ";
                    cin >> age;
                    cout << "Enter department: ";
                    cin.ignore();
                    getline(cin, department);
                    cout << "Enter GPA: ";
                    cin >> gpa;
                    insertAtEndDouble(D, id, name, age, department, gpa);
                    break;
                case 4:
                    deleteAtHeadDouble(D);
                    break;
                case 5:
                    cout << "Enter position: ";
                    cin >> position;
                    deleteAtPositionDouble(D, position);
                    break;
                case 6:
                    deleteAtEndDouble(D);
                    break;
                case 7:
                    bubbleSortDouble(D);
                    break;
                case 8:
                    insertionSortDouble(D);
                    break;
                case 9:
                    selectionSortDouble(D);
                    break;
                case 10:
                    cout << "Enter id: ";
                    cin >> id;
                    searchDouble(D, id);
                    break;
                case 11:
                    displayDouble(D);
                    break;
                default:
                    break;
                }
            } while (choice2 != 12);
            break;
        case 3:
            cout << "=============================================" << endl;
            cout << "                    Stack                    " << endl;
            cout << "=============================================" << endl;
            int choice3;
            cout << "1. Push" << endl;
            cout << "2. Pop" << endl;
            cout << "3. Peek" << endl;
            cout << "4. Display" << endl;
            cout << "5. Search" << endl;
            cout << "6. Return to main menu" << endl;

            do
            {
                cout << "choice: ";
                cin >> choice3;
                switch (choice3)
                {
                case 1:
                    cout << "Enter id: ";
                    cin >> id;
                    cout << "Enter name: ";
                    cin >> name;
                    cout << "Enter age: ";
                    cin >> age;
                    cout << "Enter department: ";
                    cin.ignore();
                    getline(cin, department);
                    cout << "Enter GPA: ";
                    cin >> gpa;
                    S1->push(id, name, age, department, gpa);
                    break;
                case 2:
                    S1->pop();
                    break;
                case 3:
                    S1->peek();
                    break;
                case 4:
                    S1->display();
                    break;
                case 5:
                    cout << "Enter id: ";
                    cin >> id;
                    S1->search(id);
                    break;
                default:
                    break;
                }
            } while (choice3 != 6);
            break;
        case 4:
            cout << "=============================================" << endl;
            cout << "                    Queue                    " << endl;
            cout << "=============================================" << endl;
            int choice4;
            cout << "1. Enqueue" << endl;
            cout << "2. Dequeue" << endl;
            cout << "3. Peek" << endl;
            cout << "4. Display" << endl;
            cout << "5. Search" << endl;
            cout << "6. Return to main menu" << endl;

            do
            {
                cout << "Choice: ";
                cin >> choice4;
                switch (choice4)
                {
                case 1:
                    cout << "Enter id: ";
                    cin >> id;
                    cout << "Enter name: ";
                    cin >> name;
                    cout << "Enter age: ";
                    cin >> age;
                    cout << "Enter department: ";
                    cin.ignore();
                    getline(cin, department);
                    cout << "Enter GPA: ";
                    cin >> gpa;
                    Q->enquque(id, name, age, department, gpa);
                    break;
                case 2:
                    Q->dequeue();
                    break;
                case 3:
                    Q->peek();
                    break;
                case 4:
                    Q->display_queue();
                    break;
                case 5:
                    cout << "Enter id: ";
                    cin >> id;
                    Q->search(id);
                    break;
                default:
                    break;
                }
            } while (choice4 != 6);
            break;
        case 5:
            cout << "=============================================" << endl;
            cout << "                     Tree                    " << endl;
            cout << "=============================================" << endl;

            int choice5;
            do
            {
                cout << "1. Insert" << endl;
                cout << "2. Delete" << endl;
                cout << "3. Display Pre-order" << endl;
                cout << "4. Display In-order" << endl;
                cout << "5. Display Post-order" << endl;
                cout << "6. Search" << endl;
                cout << "7. Return to main menu" << endl;

                cout << "Choice: ";
                cin >> choice5;

                switch (choice5)
                {
                case 1:
                    cout << "Enter id: ";
                    cin >> id;
                    cout << "Enter name: ";
                    cin >> name;
                    cout << "Enter age: ";
                    cin >> age;
                    cout << "Enter department: ";
                    cin.ignore();
                    getline(cin, department);
                    cout << "Enter GPA: ";
                    cin >> gpa;
                    root = insert_tree(root, id, name, age, department, gpa);
                    break;

                case 2:
                {
                    cout << "Enter id: ";
                    cin >> id;
                    bool found = false;
                    root = delete_node(root, id, found);
                    if (!found)
                    {
                        cout << "Student not found." << endl;
                    }
                    else
                    {
                        cout << "Student deleted successfully." << endl;
                    }
                    break;
                }

                case 3:
                    display_tree_preorder(root);
                    break;

                case 4:
                    display_tree_inorder(root);
                    break;

                case 5:
                    display_tree_postorder(root);
                    break;

                case 6:
                    cout << "Enter id: ";
                    cin >> id;
                    search_tree(root, id);
                    break;

                case 7:
                    cout << "Returning to main menu..." << endl;
                    break;

                default:
                    cout << "Invalid choice." << endl;
                    break;
                }
            } while (choice5 != 7);
            break;

        case 6:
            cout << "Exiting program" << endl;
            break;
        default:
            cout << "Invalid choice" << endl;
            break;
        }
    } while (choice != 6);
}
