#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct Contact {
    string name;
    string phone;
    string email;
};

vector<Contact> contacts;

void loadContacts(const string& filename) {
    ifstream file(filename);
    if (!file) return;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Contact c;
        getline(ss, c.name, ',');
        getline(ss, c.phone, ',');
        getline(ss, c.email, ',');
        contacts.push_back(c);
    }
    file.close();
}

void saveContacts(const string& filename) {
    ofstream file(filename);
    for (auto& c : contacts) {
        file << c.name << "," << c.phone << "," << c.email << "\n";
    }
    file.close();
}

void addContact() {
    Contact c;
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, c.name);
    cout << "Enter phone: ";
    getline(cin, c.phone);
    cout << "Enter email: ";
    getline(cin, c.email);
    contacts.push_back(c);
    cout << "Contact added successfully.\n";
}

void viewContacts() {
    if (contacts.empty()) {
        cout << "No contacts found.\n";
        return;
    }
    cout << "\nContact List:\n";
    for (size_t i = 0; i < contacts.size(); i++) {
        cout << i+1 << ". " << contacts[i].name << ", "
             << contacts[i].phone << ", " << contacts[i].email << endl;
    }
}

void editContact() {
    viewContacts();
    if (contacts.empty()) return;

    cout << "Enter the number of the contact to edit: ";
    int index;
    cin >> index;
    cin.ignore();
    if (index < 1 || index > (int)contacts.size()) {
        cout << "Invalid contact number.\n";
        return;
    }
    Contact &c = contacts[index -1];
    cout << "Editing contact: " << c.name << endl;
    cout << "Enter new name (or press enter to keep '" << c.name << "'): ";
    string input;
    getline(cin, input);
    if (!input.empty()) c.name = input;

    cout << "Enter new phone (or press enter to keep '" << c.phone << "'): ";
    getline(cin, input);
    if (!input.empty()) c.phone = input;

    cout << "Enter new email (or press enter to keep '" << c.email << "'): ";
    getline(cin, input);
    if (!input.empty()) c.email = input;

    cout << "Contact updated successfully.\n";
}

void deleteContact() {
    viewContacts();
    if (contacts.empty()) return;

    cout << "Enter the number of the contact to delete: ";
    int index;
    cin >> index;
    cin.ignore();
    if (index < 1 || index > (int)contacts.size()) {
        cout << "Invalid contact number.\n";
        return;
    }
    contacts.erase(contacts.begin() + index - 1);
    cout << "Contact deleted successfully.\n";
}

int main() {
    const string filename = "contacts.txt";
    loadContacts(filename);

    int choice;
    do {
        cout << "\nContact Management System\n";
        cout << "1. Add Contact\n";
        cout << "2. View Contacts\n";
        cout << "3. Edit Contact\n";
        cout << "4. Delete Contact\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1: addContact(); break;
            case 2: viewContacts(); break;
            case 3: editContact(); break;
            case 4: deleteContact(); break;
            case 5: saveContacts(filename); cout << "Exiting...\n"; break;
            default: cout << "Invalid choice, try again.\n";
        }
    } while (choice != 5);

    return 0;
}
