#include <iostream>
#include <string>
using namespace std;

struct Task {
    string name;
    bool completed;
    Task* next;
};

Task* head = nullptr;

void add_task(const string& name) {
    Task* newTask = new Task;
    newTask->name = name;
    newTask->completed = false;
    newTask->next = nullptr;

    if (head == nullptr) {
        head = newTask;
    } else {
        Task* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newTask;
    }
    cout << "Task added: " << name << endl;
}

void view_tasks(Task* head) {
    if (head == nullptr) {
        cout << "No tasks available." << endl;
        return;
    }

    Task* temp = head;
    int taskNumber = 1;
    while (temp != nullptr) {
        cout << taskNumber << ". [" << (temp->completed ? "X" : " ") << "] " << temp->name << endl;
        temp = temp->next;
        taskNumber++;
    }
}

void mark_completed(Task* head, int taskNumber) {
    Task* temp = head;
    int currentNumber = 1;
    while (temp != nullptr) {
        if (currentNumber == taskNumber) {
            temp->completed = true;
            cout << "Task marked as completed: " << temp->name << endl;
            return;
        }
        temp = temp->next;
        currentNumber++;
    }
    cout << "Task number not found." << endl;
}

void delete_task(Task*& head, int taskNumber) {
    if (head == nullptr) {
        cout << "No tasks available to delete." << endl;
        return;
    }
    
    Task* temp = head;
    Task* prev = nullptr;
    int currentNumber = 1;

    if (taskNumber == 1) {
        head = head->next;
        delete temp;
        cout << "Task deleted." << endl;
        return;
    }

    while (temp != nullptr && currentNumber < taskNumber) {
        prev = temp;
        temp = temp->next;
        currentNumber++;
    }

    if (temp == nullptr) {
        cout << "Task number not found." << endl;
        return;
    }

    prev->next = temp->next;
    delete temp;
    cout << "Task deleted." << endl;
}

int main() {
    cout << "To-Do-List" << endl;

    char ch;
    do {
        cout << "Enter 1: To add new task" << endl;
        cout << "Enter 2: To view all tasks" << endl;
        cout << "Enter 3: To mark completed task" << endl;
        cout << "Enter 4: To delete task" << endl;
        cout << "Enter any other key to exit" << endl;

        cout << "Enter: ";
        cin >> ch;
        cout << endl;

        switch(ch) {
            case '1': {
                string name;
                cout << "Enter the task: ";
                cin.ignore();
                getline(cin, name);
                add_task(name);
                break;
            }
            case '2':
                view_tasks(head);
                break;

            case '3': {
                int n;
                cout << "Mark as completed the task from the updated view of list" << endl;
                cout << "Enter the task number you want to mark completed: ";
                cin >> n;
                mark_completed(head, n);
                break;
            }

            case '4': {
                int n;
                cout << "Deleting task from the updated view of list" << endl;
                cout << "Enter the task number you want to delete: ";
                cin >> n;
                delete_task(head, n);
                break;
            }

            default:
                cout << "Exiting program." << endl;
                break;
        }
        cout << endl;

    } while (ch >= '1' && ch <= '4'); 
    
    while (head != nullptr) {
        Task* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
