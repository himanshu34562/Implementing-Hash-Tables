#include <bits/stdc++.h>
using namespace std;

// Enable fast I/O
void fastIO() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

const int tableSize = 199; // Prime size for better probing

// Structure to represent a student record
struct student {
    string email;
    string name;
    bool isDeleted;

    student() : email(""), name(""), isDeleted(false) {}
};

class hashTable {
private:
    vector<student> hash_table;

    // Hash function: sum of ASCII values mod table size
    int convertor(const string &s) {
        int ans = 0;
        for (char c : s)
            ans += c;
        return ans % tableSize;
    }

public:
    hashTable() {
        hash_table.resize(tableSize);
    }

    // Insert or update a record using quadratic probing
    int add(string &email, string &name) {
        int index = convertor(email);
        int collision = 0, probing_factor = 0;

        while (collision < tableSize) {
            if (hash_table[index].email == "" || hash_table[index].isDeleted) {
                hash_table[index].email = email;
                hash_table[index].name = name;
                hash_table[index].isDeleted = false;
                return collision;
            }
            else if (hash_table[index].email == email && !hash_table[index].isDeleted) {
                hash_table[index].name = name; // Update
                return collision;
            }
            collision++;
            probing_factor++;
            index = (index + (probing_factor * probing_factor)) % tableSize;
        }
        return collision; // Table full or probing loop
    }

    // Search by email
    pair<string, string> find(const string &email) {
        int currentIndex = convertor(email);
        int jumps = 0, probing_factor = 0;

        while (jumps < tableSize) {
            if (hash_table[currentIndex].email == "")
                return {"", ""}; // Not found
            if (hash_table[currentIndex].email == email && !hash_table[currentIndex].isDeleted)
                return {hash_table[currentIndex].email, hash_table[currentIndex].name}; // Found

            jumps++;
            probing_factor++;
            currentIndex = (currentIndex + (probing_factor * probing_factor)) % tableSize;
        }
        return {"", ""};
    }

    // Find index of email
    int find_index(string &email) {
        int currentIndex = convertor(email);
        int jumps = 0, probing_factor = 0;

        while (jumps < tableSize) {
            currentIndex = (currentIndex + (probing_factor * probing_factor)) % tableSize;
            if (hash_table[currentIndex].email == "")
                return -1;
            if (hash_table[currentIndex].email == email && !hash_table[currentIndex].isDeleted)
                return currentIndex;

            jumps++;
            probing_factor++;
        }
        return -1;
    }

    // Lazy deletion
    bool delete_record(string &email) {
        int index = find_index(email);
        if (index != -1) {
            hash_table[index].isDeleted = true;
            return true;
        }
        return false;
    }

    // Print the table
    void printTable() {
        cout << "\nHash Table Contents:\n" << flush;
        for (int i = 0; i < tableSize; ++i) {
            cout << i << " : " 
                 << hash_table[i].email << "  " 
                 << hash_table[i].name << "  " 
                 << hash_table[i].isDeleted << "\n" << flush;
        }
    }

    // Count current entries
    int checkTableEntries() {
        int NumberOfEntries = 0;
        for (int i = 0; i < tableSize; ++i) {
            if (hash_table[i].email != "")
                NumberOfEntries++;
        }
        return NumberOfEntries;
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
        cout << "Enter your choice: " << flush;

        int option;
        cin >> option;

        if (option < 1 || option > 6) {
            cout << "Invalid operation.\n" << flush;
            break;
        }
        if (option == 6) break;

        switch (option) {
            case 1: {
                cout << "Enter number of records to insert: " << flush;
                int n;
                cin >> n;
                cout << "Enter records (email name):\n" << flush;

                while (n--) {
                    string email, name;
                    cin >> email >> name;
                    int collision = hashObj.add(email, name);

                    if (collision == tableSize) {
                        int entries = hashObj.checkTableEntries();
                        if (entries == tableSize)
                            cout << "Table full — cannot insert record.\n" << flush;
                        else
                            cout << "Quadratic probing loop — cannot insert record.\n" << flush;
                    } else {
                        cout << "Inserted with " << collision << " collision(s).\n" << flush;
                    }
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
                    cout << "Record not found.\n" << flush;
                break;
            }
            case 3: {
                cout << "Enter email to get index: " << flush;
                string email;
                cin >> email;
                int index = hashObj.find_index(email);
                if (index != -1)
                    cout << "Found at index: " << index << "\n" << flush;
                else
                    cout << "Record not found.\n" << flush;
                break;
            }
            case 4: {
                cout << "Enter email to delete: " << flush;
                string email;
                cin >> email;
                if (hashObj.delete_record(email))
                    cout << "Deleted successfully.\n" << flush;
                else
                    cout << "Deletion failed — record not found.\n" << flush;
                break;
            }
            case 5: {
                hashObj.printTable();
                break;
            }
        }
    }
    return 0;
}
