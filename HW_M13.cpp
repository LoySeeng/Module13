#include <iostream>
#include <string>
#define SIZE 10

using namespace std;

class Network {
public:
    Network();

    void addPerson(string Name);
    void addFriend(string Person, string Friend);

    void printAllPars();
private:
    string name;
    int peopleCount;

    int FindbyName(string);
    bool isFriends(string, string);
    bool isFriends(int, int);
    bool PersonExist(string);

    void printAllPathsUtil(int from, bool visited[], int path[], int& path_index, int count);

    string People[SIZE];
    int matrix[SIZE][SIZE];
};

Network::Network() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            matrix[i][j] = 0;

    peopleCount = 0;
}


void Network::addPerson(string Name) {
    if (peopleCount == 0) {
        People[peopleCount] = Name;
        peopleCount++;
    }
    else if (!PersonExist(Name)) {
        People[peopleCount] = Name;
        peopleCount++;
    }
    else {
        cout << "Person with this name already exist. Please, try add 'Name1'." << endl;
    }
}

void Network::addFriend(string Person, string Friend) {
    if (PersonExist(Person) && PersonExist(Friend)) {
        int P = FindbyName(Person);
        int F = FindbyName(Friend);
        matrix[P][F] = 1;
        matrix[F][P] = 1;
    }
}

int Network::FindbyName(string Name) {
    for (int i = 0; i < SIZE; i++) {
        if (Name == People[i]) {
            return i;
        }
    }
}

bool Network::isFriends(string Person1, string Person2) {
    if (PersonExist(Person1) && PersonExist(Person2)) {
        int P1 = FindbyName(Person1);
        int P2 = FindbyName(Person2);
        if (matrix[P1][P2] != 0) {
            return true;
        }
    }
    else {
        return false;
    }
}

bool Network::isFriends(int P1, int P2) {
    return matrix[P1][P2] > 0;
}

bool Network::PersonExist(string Name) {
    for (int i = 0; i < peopleCount; i++) {
        if (Name == People[i]) {
            return true;
        }
    }
    return false;
}


void Network::printAllPars()
{
    if (People[0].empty()) {
        cout << "No people in the base, add them first" << endl;
    }
    else {
        bool visited[SIZE];
        for (int i = 0; i < SIZE; i++)
            visited[i] = false;

        int path[SIZE];
        int path_index = 0;

        int count = 0;

        for (int j = 0; j < SIZE; j++) {
            int next = j;
            printAllPathsUtil(next, visited, path, path_index, count);
        }
    }
}

void Network::printAllPathsUtil(int next, bool visited[], int path[], int& path_index, int count) {
    visited[next] = true;
    path[path_index] = next;
    path_index++;

    if (count == 3) {
        for (int i = 1; i < path_index; i++) {
            cout << People[path[0]] << " : " << People[path[i]] << endl;
        }
    }
    else {
        for (int i = 0; i < SIZE; i++) {
            if (isFriends(next, i) && !visited[i]) {
                count++;
                printAllPathsUtil(i, visited, path, path_index, count);
            }
        }
    }
    count--;
    path_index--;
    visited[next] = false;
}



int main() {
    Network Test;

    Test.addPerson("Alice");
    Test.addPerson("Henry");
    Test.addPerson("Mary");
    Test.addPerson("Zack");
    Test.addPerson("Nick");

    Test.addFriend("Alice", "Henry");
    Test.addFriend("Henry", "Mary");
    Test.addFriend("Mary", "Zack");
    Test.addFriend("Zack", "Nick");

    Test.printAllPars();
}