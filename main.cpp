#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Expense {
public:
    string title;
    float amount;
    string date;

    void input() {
        cout << "Enter Title: ";
        cin >> title;

        cout << "Enter Amount: ";
        cin >> amount;

        cout << "Enter Date (DD-MM-YYYY): ";
        cin >> date;
    }

    void display(int index) {
        cout << index + 1 << ". "
             << title << " | "
             << amount << " | "
             << date << endl;
    }
};

void addExpense(vector<Expense>& expenses) {
    Expense e;
    e.input();
    expenses.push_back(e);
    cout << "Expense added successfully!\n";
}

void viewExpenses(vector<Expense>& expenses) {

    if (expenses.empty()) {
        cout << "No expenses recorded.\n";
        return;
    }

    cout << "\n---- Expense List ----\n";
    for (int i = 0; i < expenses.size(); i++) {
        expenses[i].display(i);
    }
}

void deleteExpense(vector<Expense>& expenses) {

    int index;

    viewExpenses(expenses);

    if (expenses.empty())
        return;

    cout << "Enter expense number to delete: ";
    cin >> index;

    if (index < 1 || index > expenses.size()) {
        cout << "Invalid choice!\n";
        return;
    }

    expenses.erase(expenses.begin() + (index - 1));

    cout << "Expense deleted successfully!\n";
}

void saveToFile(vector<Expense>& expenses) {

    ofstream file("expenses.txt");

    for (auto &e : expenses) {
        file << e.title << " "
             << e.amount << " "
             << e.date << endl;
    }

    file.close();
}

void loadFromFile(vector<Expense>& expenses) {

    ifstream file("expenses.txt");

    Expense e;

    while (file >> e.title >> e.amount >> e.date) {
        expenses.push_back(e);
    }

    file.close();
}

int main() {

    vector<Expense> expenses;

    loadFromFile(expenses);

    int choice;

    do {

        cout << "\n===== Expense Tracker =====\n";
        cout << "1. Add Expense\n";
        cout << "2. View Expenses\n";
        cout << "3. Delete Expense\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice) {

            case 1:
                addExpense(expenses);
                break;

            case 2:
                viewExpenses(expenses);
                break;

            case 3:
                deleteExpense(expenses);
                break;

            case 4:
                saveToFile(expenses);
                cout << "Data saved. Exiting program.\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 4);

    return 0;
}
