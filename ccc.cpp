#include <iostream>
#include <cstring>
using namespace std;

const int MAX_PATIENTS = 100;


struct Patient {
    int id;
    char name[50];
    int age;
    int severity;
};


Patient heap[MAX_PATIENTS];
int heapSize = 0;
int nextId = 1;


void swap(Patient &a, Patient &b) {
    Patient temp = a;
    a = b;
    b = temp;
}

void heapifyUp(int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (heap[idx].severity > heap[parent].severity) {
            swap(heap[idx], heap[parent]);
            idx = parent;
        } else break;
    }
}


void heapifyDown(int idx) {
    while (true) {
        int largest = idx;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;

        if (left < heapSize && heap[left].severity > heap[largest].severity)
            largest = left;

        if (right < heapSize && heap[right].severity > heap[largest].severity)
            largest = right;

        if (largest != idx) {
            swap(heap[idx], heap[largest]);
            idx = largest;
        } else break;
    }
}


void insertPatient() {
    if (heapSize >= MAX_PATIENTS) {
        cout << "\n[!] Queue Full!\n";
        return;
    }

    Patient p;
    p.id = nextId++;

    cout << "Enter Name: ";
    cin.ignore();
    cin.getline(p.name, 50);

    cout << "Enter Age: ";
    cin >> p.age;
    if (p.age <= 0 || p.age > 150) {
        cout << "[!] Invalid Age!\n";
        return;
    }

    cout << "Enter Severity (1-5): ";
    cin >> p.severity;
    if (p.severity < 1 || p.severity > 5) {
        cout << "[!] Invalid Severity!\n";
        return;
    }

    heap[heapSize] = p;
    heapifyUp(heapSize);
    heapSize++;

    cout << "[+] Patient Added Successfully!\n";
}


void treatPatient() {
    if (heapSize == 0) {
        cout << "\n[!] No patients!\n";
        return;
    }

    Patient treated = heap[0];
    heap[0] = heap[heapSize - 1];
    heapSize--;

    heapifyDown(0);

    cout << "\n--- Treating Patient ---\n";
    cout << "ID: " << treated.id << endl;
    cout << "Name: " << treated.name << endl;
    cout << "Severity: " << treated.severity << endl;
}


void displayQueue() {
    if (heapSize == 0) {
        cout << "\n[!] Queue Empty!\n";
        return;
    }

    Patient temp[MAX_PATIENTS];

    for (int i = 0; i < heapSize; i++) {
        temp[i] = heap[i];
    }

 
    for (int i = 0; i < heapSize - 1; i++) {
        for (int j = i + 1; j < heapSize; j++) {
            if (temp[j].severity > temp[i].severity) {
                swap(temp[i], temp[j]);
            }
        }
    }

    cout << "\n===== Emergency Queue (Sorted by Severity) =====\n";
    cout << "ID\tName\t\tAge\tSeverity\n";

    for (int i = 0; i < heapSize; i++) {
        cout << temp[i].id << "\t" << temp[i].name;

        int len = strlen(temp[i].name);
        if (len < 8) cout << "\t\t";
        else cout << "\t";

        cout << temp[i].age << "\t" << temp[i].severity << endl;
    }
}

void peekMostCritical() {
    if (heapSize == 0) {
        cout << "\n[!] No patients!\n";
        return;
    }

    cout << "\nMost Critical Patient:\n";
    cout << "Name: " << heap[0].name << endl;
    cout << "Severity: " << heap[0].severity << endl;
}


void countPatients() {
    cout << "\nTotal Patients: " << heapSize << endl;
}

void searchById() {
    int id;
    cout << "Enter ID: ";
    cin >> id;

    for (int i = 0; i < heapSize; i++) {
        if (heap[i].id == id) {
            cout << "\nFound: " << heap[i].name << endl;
            return;
        }
    }

    cout << "\nPatient Not Found!\n";
}


void updateSeverity() {
    int id;
    cout << "Enter ID: ";
    cin >> id;

    for (int i = 0; i < heapSize; i++) {
        if (heap[i].id == id) {
            int old = heap[i].severity;

            cout << "Enter New Severity: ";
            cin >> heap[i].severity;

            if (heap[i].severity > old)
                heapifyUp(i);
            else
                heapifyDown(i);

            cout << "\nUpdated Successfully!\n";
            return;
        }
    }

    cout << "\nPatient Not Found!\n";
}


void menu() {
    cout << "\n1. Add Patient";
    cout << "\n2. Treat Patient";
    cout << "\n3. Display Queue";
    cout << "\n4. Peek Critical Patient";
    cout << "\n5. Count Patients";
    cout << "\n6. Search by ID";
    cout << "\n7. Update Severity";
    cout << "\n8. Exit";
    cout << "\nEnter choice: ";
}

int main() {
    int choice;

    while (true) {
        menu();
        cin >> choice;

   
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\n[!] YOU ENTERED WRONG CHOICE\n";
            continue;
        }

        if (choice < 1 || choice > 8) {
            cout << "\n[!] YOU ENTERED WRONG CHOICE\n";
            continue;
        }

        switch (choice) {
            case 1: insertPatient(); break;
            case 2: treatPatient(); break;
            case 3: displayQueue(); break;
            case 4: peekMostCritical(); break;
            case 5: countPatients(); break;
            case 6: searchById(); break;
            case 7: updateSeverity(); break;
            case 8: return 0;
        }
    }
}