#include <bits/stdc++.h>
using namespace std;

// Enable fast I/O
void fastIO() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

const int tableSize = 199; // Hash table size

// Structure to store each student record
struct student {
    string email;
    string name;
    bool isDeleted; // Used for lazy deletion

    // Default constructor
    student() : email(""), name(""), isDeleted(false) {}
};

class hashTable {
private:
    vector<student> hash_table; // Main hash table

    // Hash function: Converts email string into table index
    int convertor(const string &s) {
        int ans = 0;
        for (char ch : s)
            ans += ch;
        return ans % tableSize;
    }

public:
    // Constructor to initialize hash table with empty records
    hashTable() {
        hash_table.resize(tableSize);
    }

    // Insert or update a record using Linear Probing
    int add(string &email, string &name) {
        int index = convertor(email);
        int collision = 0;

        while (collision < tableSize) {
            if (hash_table[index].email == "" || hash_table[index].isDeleted==true) {
                hash_table[index].email = email;
                hash_table[index].name = name;
                hash_table[index].isDeleted = false;
                return collision;
            } 
            else if (hash_table[index].email == email && hash_table[index].isDeleted==false) {
                hash_table[index].name = name;
                return collision;
            }
            else {
                collision++;
                index = (index + collision) % tableSize;
            }
        }
        return tableSize; // Table full
    }

    // Find a record by email
    pair<string, string> find(const string &email) {
        int currentIndex = convertor(email);
        int jumps = 0;

        while (jumps < tableSize) {
            if (hash_table[currentIndex].email == "") {
                return {"", ""};
            } 
            else if (hash_table[currentIndex].email == email && hash_table[currentIndex].isDeleted==false) {
                return {hash_table[currentIndex].email, hash_table[currentIndex].name};
            }
            jumps++;
            currentIndex = (currentIndex + jumps) % tableSize;
        }
        return {"", ""};
    }

    // Get index of a record
    int find_index(string &email) {
        int currentIndex = convertor(email);
        int jumps = 0;

        while (jumps < tableSize) {
            currentIndex = (currentIndex + jumps) % tableSize;
            if (hash_table[currentIndex].email == "")
                return -1;
            else if (hash_table[currentIndex].email == email && !hash_table[currentIndex].isDeleted)
                return currentIndex;
            jumps++;
        }
        return -1;
    }

    // Lazy delete a record
    bool delete_record(string &email) {
        int index = find_index(email);
        if (index != -1) {
            hash_table[index].isDeleted = true;
            return true;
        }
        return false;
    }

    // Print complete hash table
    void printTable() {
        cout << "\nHash Table Contents:\n" << flush;
        cout << "-------------------------------------------------\n" << flush;
        cout << "Index\tEmail\t\tName\t\tDeleted?\n" << flush;
        cout << "-------------------------------------------------\n" << flush;
        for (int i = 0; i < tableSize; ++i) {
            cout << i << "\t" << hash_table[i].email << "\t\t"
                 << hash_table[i].name << "\t\t"
                 << (hash_table[i].isDeleted ? "Yes" : "No") << "\n" << flush;
        }
        cout << "-------------------------------------------------\n" << flush;
    }
};

int main() {
    fastIO();
    hashTable hashObj;

    while (true) {
        cout << "\nChoose operation to perform:\n" << flush;
        cout << "1 :: Add Record\n" << flush;
        cout << "2 :: Find Record\n" << flush;
        cout << "3 :: Get Record Index\n" << flush;
        cout << "4 :: Delete Record\n" << flush;
        cout << "5 :: Print Table\n" << flush;
        cout << "6 :: Exit\n" << flush;
        cout << "Enter choice: " << flush;

        int option;
        cin >> option;

        if (option < 1 || option > 6) {
            cout << "Invalid option.\n" << flush;
            continue;
        }
        if (option == 6) break;

        switch (option) {
            case 1: {
                cout << "Enter the number of records to insert: " << flush;
                int n;
                cin >> n;
                while (n--) {
                    string email, name;
                    cout << "Enter Email and Name: " << flush;
                    cin >> email >> name;
                    int collisions = hashObj.add(email, name);
                    if (collisions == tableSize)
                        cout << "Table full! Cannot insert record.\n" << flush;
                    else
                        cout << "Inserted with " << collisions << " collision(s).\n" << flush;
                }
                break;
            }
            case 2: {
                cout << "Enter email to search: " << flush;
                string email;
                cin >> email;
                auto result = hashObj.find(email);
                if (result.first != "")
                    cout << "Found: " << result.first << " -> " << result.second << "\n" << flush;
                else
                    cout << "Not found.\n" << flush;
                break;
            }
            case 3: {
                cout << "Enter email to find index: " << flush;
                string email;
                cin >> email;
                int index = hashObj.find_index(email);
                if (index != -1)
                    cout << "Found at index: " << index << "\n" << flush;
                else
                    cout << "Not found.\n" << flush;
                break;
            }
            case 4: {
                cout << "Enter email to delete: " << flush;
                string email;
                cin >> email;
                if (hashObj.delete_record(email))
                    cout << "Deleted successfully.\n" << flush;
                else
                    cout << "Deletion failed. Record not found.\n" << flush;
                break;
            }
            case 5:
                hashObj.printTable();
                break;
        }
    }
    return 0;
}
