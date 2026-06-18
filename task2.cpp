#include <iostream>
using namespace std;

enum problem {
    E,
    B,
    T,
    G,
    S,
    O
};
enum status {
    waiting,
    inProgress,
    done
};
struct Query {
    string licensePlate;
    char problem;
    int urgency;
    int status = waiting;
    void update() {
        if (status == waiting) {
            status = inProgress;
            cout << "Started working on " << licensePlate << endl;
        }
        else if (status == inProgress) {
            status = done;
            cout << "Finished working on " << licensePlate << endl;
        }
        else {
            cout << "Error, already finished!" << endl;
        }
    }
};
int main() {
    int n;
    cin >> n;
    Query* q = new Query[n];
    for (int i = 0; i < n; i++) {
        cin >> q[i].licensePlate;
        cin >> q[i].problem;
        cin >> q[i].urgency;
    }
    string licensePlate;
    cin >> licensePlate;
    for (int i = 0; i < n; i++) {
        if (q[i].licensePlate == licensePlate) {
            q[i].update();
        }
    }
    cout << "Waiting: " << endl;
    for (int i = 0; i < n; i++) {
        if (q[i].status == waiting) {
            cout << q[i].licensePlate << " " << q[i].problem << " " << q[i].urgency << endl;
        }
    }
    cout << "In progress: " << endl;
    for (int i = 0; i < n; i++) {
        if (q[i].status == inProgress) {
            cout << q[i].licensePlate << " " << q[i].problem << " " << q[i].urgency << endl;
        }
    }
    cout << "Done: " << endl;
    for (int i = 0; i < n; i++) {
        if (q[i].status == done) {
            cout << q[i].licensePlate << endl;
        }
    }
    cout << endl;
    cout << endl;
    for (int i = 5; i > 0; i--) {
        for (int j = 0; j < n; j++) {
            if (q[j].urgency == i) {
                cout << q[j].licensePlate << endl;
            }
        }
    }
    cout << endl;
    cout << "Engine problem: " << endl;
    for (int i = 0; i < n; i++) {
        if (q[i].problem == 'e') {
            cout << q[i].licensePlate << endl;
        }
    }
    cout << "Brakes problem: " << endl;
    for (int i = 0; i < n; i++) {
        if (q[i].problem == 'b') {
            cout << q[i].licensePlate << endl;
        }
    }
    cout << "Tires problem: " << endl;
    for (int i = 0; i < n; i++) {
        if (q[i].problem == 't') {
            cout << q[i].licensePlate << endl;
        }
    }
    cout << "Gearbox problem: " << endl;
    for (int i = 0; i < n; i++) {
        if (q[i].problem == 'g') {
            cout << q[i].licensePlate << endl;
        }
    }
    cout << "Suspension problem: " << endl;
    for (int i = 0; i < n; i++) {
        if (q[i].problem == 's') {
            cout << q[i].licensePlate << endl;
        }
    }
    cout << "Other problem: " << endl;
    for (int i = 0; i < n; i++) {
        if (q[i].problem == 'o') {
            cout << q[i].licensePlate << endl;
        }
    }
    delete[] q;
}