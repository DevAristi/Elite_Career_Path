#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    vector<int> my_numbers;
    my_numbers.push_back(10);
    my_numbers.push_back(20);
    my_numbers.push_back(30);

    cout << "--- Using a FOR loop with a Vector ---" << endl;
    for (int i = 0; i < my_numbers.size(); i++) {
        cout << "Index " << i << " holds the value: " << my_numbers[i] << endl;
    }

    unordered_map<string, int> grades;
    grades["Calculus"] = 10;
    grades["OOP"] = 9;

    cout << "\n--- Searching in the Map ---" << endl;
    cout << "My grade in Calculus is: " << grades["Calculus"] << endl;

    return 0;
}