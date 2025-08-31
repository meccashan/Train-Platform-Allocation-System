#include <iostream>
#include <queue>
#include <algorithm>
#include <limits>
#include <iomanip> 

using namespace std;

const int MAX = 100;

// Function 
void inputTrains(int arrival[], int departure[], int trainID[], int n);
void sortTrains(int arrival[], int departure[], int trainID[], int n);
int allotPlatforms(int arrival[], int departure[], int trainID[], int n);
string formatTime(int time);

// Function to input train details with validation
void inputTrains(int arrival[], int departure[], int trainID[], int n) {
    for (int i = 0; i < n; i++) {
        trainID[i] = i + 1;
        cout << "\nTrain " << trainID[i] << ":\n";

        while (true) {
            cout << "Enter arrival time (0000 to 2359): ";
            cin >> arrival[i];

            cout << "Enter departure time (must be later than arrival): ";
            cin >> departure[i];

            if (cin.fail() || arrival[i] < 0 || arrival[i] > 2359 ||
                departure[i] < 0 || departure[i] > 2359 || arrival[i] >= departure[i]) {
                cout << " Invalid input. Please re-enter.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                break;
            }
        }
    }
}

// Sort trains by arrival time using bubble sort
void sortTrains(int arrival[], int departure[], int trainID[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arrival[i] > arrival[j]) {
                swap(arrival[i], arrival[j]);
                swap(departure[i], departure[j]);
                swap(trainID[i], trainID[j]);
            }
        }
    }
}

// Function to format time as HH:MM
string formatTime(int time) {
    int hours = time / 100;
    int minutes = time % 100;
    char formatted[6];
    snprintf(formatted, sizeof(formatted), "%02d:%02d", hours, minutes);
    return string(formatted);
}

// Allot platforms and return the number of platforms used
int allotPlatforms(int arrival[], int departure[], int trainID[], int n) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    int nextPlatform = 1;

    cout << "\n Platform Allotment:\n";
    cout << "+---------+----------+-----------+-------------+\n";
    cout << "| TrainID | Arrival  | Departure | Platform    |\n";
    cout << "+---------+----------+-----------+-------------+\n";

    for (int i = 0; i < n; i++) {
        int platform;
        bool reused = false;

        if (!pq.empty() && arrival[i] >= pq.top().first) {
            platform = pq.top().second;
            pq.pop();
            reused = true;
        } else {
            platform = nextPlatform++;
        }

        pq.push({departure[i], platform});

        cout << "|   " << setw(5) << trainID[i]
             << " |  " << setw(7) << formatTime(arrival[i])
             << " |  " << setw(8) << formatTime(departure[i])
             << " |   " << platform << "   " << (reused ? "(Reused)" : "(New)") << " |\n";
    }

    cout << "+---------+----------+-----------+-------------+\n";
    return nextPlatform - 1;
}

// Main function
int main() {
    int n;
    int arrival[MAX], departure[MAX], trainID[MAX];

    cout << "Welcome to the Train Platform Allotment System \n";
    cout << "---------------------------------------------------\n";
    cout << "Enter number of trains: ";
    cin >> n;

    if (n <= 0 || n > MAX) {
        cerr << "Invalid number of trains.\n";
        return 1;
    }

    inputTrains(arrival, departure, trainID, n);
    sortTrains(arrival, departure, trainID, n);
    int minPlatforms = allotPlatforms(arrival, departure, trainID, n);

    cout << "\n Minimum Platforms Required = " << minPlatforms << endl;

    return 0;
}
