#include <bits/stdc++.h>
using namespace std;

// Enable fast I/O
void fastIO() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

const int tableSize = 199; // Size of hash table

// Structure to store one student record
struct student {
    string email;
    string name;

    // Default and parameterized constructors
    student() : email(""), name("") {}
    student(string e, string n) : email(e), name(n) {}
};

class hashTable {
private:
    vector<vector<student>> hash_table; // Each index stores a chain (vector of students)

    // Hash function: converts email into index
    int convertor(const string &s) {
        int ans = 0;
        for (char ch : s)
            ans += ch;
        return ans % tableSize;
    }

public:
    // Constructor to initialize hash table with empty chains
    hashTable() {
        hash_table.resize(tableSize);
    }

    // Insert or update a record
    int add(string &email, string &name) {
        int index = convertor(email);
        auto &chain = hash_table[index];
        int chain_size = chain.size();

        // If email already exists, update name
        for (auto &it : chain) {
            if (it.email == email) {
                it.name = name;
                return chain_size;
            }
        }

        // Otherwise, insert new record
        chain.push_back({email, name});
        return ++chain_size;
    }

    // Find a record by email
    pair<string, string> find(const string &email) {
        int index = convertor(email);
        auto &chain = hash_table[index];

        for (auto &it : chain) {
            if (it.email == email) {
                return {it.email, it.name};
            }
        }
        return {"", ""};
    }

    // Find the chain number and position in chain
    pair<int, int> find_index(string &email) {
        int index = convertor(email);
        auto &chain = hash_table[index];

        for (int i = 0; i < (int)chain.size(); ++i) {
            if (chain[i].email == email)
                return {index, i};
        }
        return {-1, -1};
    }

    // Delete a record
    bool delete_record(string &email) {
        pair<int, int> indices = find_index(email);
        if (indices.first != -1) {
            hash_table[indices.first].erase(hash_table[indices.first].begin() + indices.second);
            return true;
        }
        return false;
    }

    // Print complete hash table
    void printTable() {
        cout << "\nHash Table (Separate Chaining):\n" << flush;
        for (int i = 0; i < tableSize; ++i) {
            cout << i << " : " << flush;
            for (auto &it : hash_table[i]) {
                cout << "[" << it.email << " , " << it.name << "] " << flush;
            }
            cout << "\n" << flush;
        }
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
                cout << "Enter number of records to insert: " << flush;
                int n;
                cin >> n;
                while (n--) {
                    string email, name;
                    cout << "Enter Email and Name: " << flush;
                    cin >> email >> name;
                    int chainSize = hashObj.add(email, name);
                    cout << "Chain size after insertion: " << chainSize << "\n" << flush;
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
                auto index = hashObj.find_index(email);
                if (index.first != -1)
                    cout << "Found at chain: " << index.first << ", position: " << index.second << "\n" << flush;
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
