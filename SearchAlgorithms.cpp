#include <iostream>
#include <vector>
#include <chrono>
#include <string> 

using namespace std;
using namespace std::chrono;

class Contact {
private:
    string name;
    string phoneNumber;
    string email;

public:
    Contact(string name, string phoneNumber, string email)
        : name(move(name)), phoneNumber(move(phoneNumber)), email(move(email)) {}

    const string& getName() const {
        return name;
    }

    void setName(const string& newName) {
        name = newName;
    }

    const string& getPhoneNumber() const {
        return phoneNumber;
    }

    void setPhoneNumber(const string& newPhoneNumber) {
        phoneNumber = newPhoneNumber;
    }

    const string& getEmail() const {
        return email;
    }

    void setEmail(const string& newEmail) {
        email = newEmail;
    }

    friend ostream& operator<<(ostream& os, const Contact& contact) {
        os << "Contact{name='" << contact.name << "', phoneNumber='" << contact.phoneNumber << "', email='" << contact.email << "'}";
        return os;
    }
};

// Linear Search Function
int linearSearch(const vector<Contact>& contacts, const string& target) {
    int iterations = 0;
    for (size_t i = 0; i < contacts.size(); ++i) {
        iterations++;
        if (contacts[i].getName() == target) {
            cout << "Linear search iterations: " << iterations << endl;
            return i;
        }
    }
    cout << "Linear search iterations: " << iterations << endl;
    return -1;
}

// Recursive Binary Search Function
int binarySearchRecursive(const vector<Contact>& contacts, const string& target, int left, int right, int& iterations) {
    if (left <= right) {
        int mid = left + (right - left) / 2;
        iterations++;

        if (contacts[mid].getName() == target) {
            cout << "Recursive binary search iterations: " << iterations << endl;
            return mid;
        }

        if (contacts[mid].getName() < target) {
            return binarySearchRecursive(contacts, target, mid + 1, right, iterations);
        }
        else {
            return binarySearchRecursive(contacts, target, left, mid - 1, iterations);
        }
    }

    cout << "Recursive binary search iterations: " << iterations << endl;
    return -1;
}

// Binary Search Function
int binarySearch(const vector<Contact>& contacts, const string& target) {
    int left = 0;
    int right = contacts.size() - 1;
    int iterations = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        iterations++;

        if (contacts[mid].getName() == target) {
            cout << "Binary search iterations: " << iterations << endl;
            return mid;
        }

        if (contacts[mid].getName() < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    cout << "Binary search iterations: " << iterations << endl;
    return -1;
}

int main() {
    vector<Contact> contacts;
    contacts.emplace_back("Alice", "123-456-7890", "alice@email.com");
    contacts.emplace_back("Bob", "987-654-3210", "bob@email.com");
    contacts.emplace_back("Charlie", "456-789-1234", "charlie@email.com");

    // Error handling for empty array
    if (contacts.empty()) {
        cout << "Contact list is empty. Exiting program." << endl;
        return 1; // Return a non-zero value to indicate error
    }

    string targetName;
    cout << "Enter the name to search: ";
    getline(cin, targetName);

    // Perform Linear Search
    int resultLinear = linearSearch(contacts, targetName);
    if (resultLinear != -1) {
        cout << "Contact found by linear search at index: " << resultLinear << endl;
    }
    else {
        cout << "Contact not found by linear search." << endl;
    }

    // Perform Binary Search
    int resultBinary = binarySearch(contacts, targetName);
    if (resultBinary != -1) {
        cout << "Contact found by binary search at index: " << resultBinary << endl;
    }
    else {
        cout << "Contact not found by binary search." << endl;
    }

    // Perform Recursive Binary Search
    int iterations = 0;
    int resultRecursiveBinary = binarySearchRecursive(contacts, targetName, 0, contacts.size() - 1, iterations);
    if (resultRecursiveBinary != -1) {
        cout << "Contact found by recursive binary search at index: " << resultRecursiveBinary << endl;
    }
    else {
        cout << "Contact not found by recursive binary search." << endl;
    }

    // Performance Comparison
    auto start = high_resolution_clock::now();
    // Perform Linear Search
    linearSearch(contacts, contacts[0].getName());
    auto end = high_resolution_clock::now();
    auto durationLinear = duration_cast<microseconds>(end - start);
    cout << "Time taken for linear search: " << durationLinear.count() << " microseconds" << endl;

    start = high_resolution_clock::now();
    // Perform Binary Search
    binarySearch(contacts, contacts[0].getName());
    end = high_resolution_clock::now();
    auto durationBinary = duration_cast<microseconds>(end - start);
    cout << "Time taken for binary search: " << durationBinary.count() << " microseconds" << endl;

    return 0;
}
