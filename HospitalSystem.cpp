#include <bits/stdc++.h>
using namespace std;

const int MAX_SPECIALIZATION = 20; 
const int MAX_QUEUE = 5;

class Patient {
public:
    string name;
    bool isUrgent;

    Patient(string name, bool isUrgent) : name(name), isUrgent(isUrgent) {}
};

class PatientQueue {
private:
    vector<Patient> queue;
    int specialization;

public:
    PatientQueue(int specialization) : specialization(specialization) {}

    bool addPatient(const string& name, bool isUrgent) {
        if (queue.size() >= MAX_QUEUE) {
            cout << "Sorry, we can't add more patients for this specialization.\n";
            return false;
        }

        if (isUrgent) {
            queue.insert(queue.begin(), Patient(name, isUrgent)); // if patient is urgent => to front
        } else {
            queue.push_back(Patient(name, isUrgent)); // if patient is not urgent => to back
        }
        return true;
    }

    void printPatients() const {
        if (queue.empty()) {
            return;
        }
        cout << "There are " << queue.size() << " patients in specialization " << specialization << ":\n";
        for (const auto& patient : queue) {
            cout << patient.name << " (" << (patient.isUrgent ? "urgent" : "regular") << ")\n";
        }
    }

    void getNextPatient() {
        if (queue.empty()) {
            cout << "No patients at the moment. Have rest, Doctor.\n";
            return;
        }
        cout << queue.front().name << " please go with the Dr.\n";
        queue.erase(queue.begin()); // Remove first patient
    }
};

class HospitalSystem {
private:
    PatientQueue* specializations[MAX_SPECIALIZATION]; 

public:
    HospitalSystem() {
        for (int i = 0; i < MAX_SPECIALIZATION; ++i) {
            specializations[i] = new PatientQueue(i);
        }
    }

    ~HospitalSystem() {
        for (int i = 0; i < MAX_SPECIALIZATION; ++i) {
            delete specializations[i];
        }
    }

    void run() {
        while (true) {
            int choice = menu();
            if (choice == 1)
                addPatient();
            else if (choice == 2)
                printAllPatients();
            else if (choice == 3)
                getNextPatient();
            else
                break;
        }
    }

private:
    int menu() {
        int choice = -1;
        while (choice == -1) {
            cout << "\nEnter your choice:\n";
            cout << "1) Add new patient\n";
            cout << "2) Print all patients\n";
            cout << "3) Get next patient\n";
            cout << "4) Exit\n";
            cin >> choice;

            if (!(1 <= choice && choice <= 4)) {
                cout << "Invalid choice. Try again\n";
                choice = -1;
            }
        }
        return choice;
    }

    void addPatient() {
        int spec;
        string name;
        int status;

        cout << "Enter specialization (0-" << MAX_SPECIALIZATION - 1 << "), name, and status (0 regular, 1 urgent): ";
        cin >> spec >> name >> status;

        if (spec < 0 || spec >= MAX_SPECIALIZATION) {
            cout << "Invalid specialization. Try again.\n";
            return;
        }

        bool isUrgent = status == 1;
        specializations[spec]->addPatient(name, isUrgent);
    }

    void printAllPatients() {
        cout << "****************************\n";
        for (int i = 0; i < MAX_SPECIALIZATION; ++i) {
            specializations[i]->printPatients();
        }
    }

    void getNextPatient() {
        int spec;
        cout << "Enter specialization: ";
        cin >> spec;

        if (spec < 0 || spec >= MAX_SPECIALIZATION) {
            cout << "Invalid specialization. Try again.\n";
            return;
        }

        specializations[spec]->getNextPatient();
    }
};

int main() {
    HospitalSystem system;
    system.run();
    return 0;
}
