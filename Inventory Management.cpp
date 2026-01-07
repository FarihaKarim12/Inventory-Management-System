#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <windows.h>
using namespace std;

void showDashboard(int totalProducts, int lowStock) {
    system("cls");
    system("color D0");

    time_t now = time(0);
    char* dt = ctime(&now);

    cout << "=============================================\n";
    cout << "|       INVENTORY MANAGEMENT DASHBOARD      |\n";
    cout << "=============================================\n";

    cout << " Total Products     : " << totalProducts << "\n";
    cout << " Low Stock Items    : " << lowStock << "\n";
    cout << " Last Update        : " << dt;
    cout << "=============================================\n\n";

    cout << " 1. Manage Inventory (Admin)\n";
    cout << " 2. Billing / Search (Cashier)\n";
    cout << " 3. Exit Program\n";

    cout << "\nEnter your choice: ";
}

class Product {
private:
    int id;
    string name;
    float price;
    int quantity;

public:
    Product() {
        id = 0;
        name = "";
        price = 0;
        quantity = 0;
    }

    Product(int id, string name, float price, int quantity) {
        this->id = id;
        this->name = name;
        this->price = price;
        this->quantity = quantity;
    }

    void inputProduct() {
        cout << "Enter Product ID: ";
        cin >> id;

        cout << "Enter Product Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter Price: ";
        cin >> price;

        cout << "Enter Quantity: ";
        cin >> quantity;
    }

    void display() const {
        cout << "ID: " << id << "  Name: " << name
             << "  Price: " << price << "  Qty: " << quantity << endl;
    }

    int getID() const { return id; }
    string getName() const { return name; }
    float getPrice() const { return price; }
    int getQuantity() const { return quantity; }

    void setQuantity(int q) { quantity = q; }

    void saveToFile(ofstream& out) {
        out << id << endl;
        out << name << endl;
        out << price << endl;
        out << quantity << endl;
    }

    void loadFromFile(ifstream& in) {
        in >> id;
        in.ignore();
        getline(in, name);
        in >> price;
        in >> quantity;
    }
};

class Inventory {
public:
    Product products[100];
private:
    int count;

public:
    Inventory() { count = 0; }

    int getCount() { return count; }

    int getLowStock() {
        int low = 0;
        for (int i = 0; i < count; i++)
            if (products[i].getQuantity() <= 5)
                low++;
        return low;
    }

    void addProduct() {
        if (count >= 100) {
            cout << "Inventory Full!" << endl;
            return;
        }
        Product p;
        p.inputProduct();
        products[count++] = p;
        cout << "Product Added!" << endl;
    }

    void showAll() {
        if (count == 0) {
            cout << "No products!" << endl;
            return;
        }
        for (int i = 0; i < count; i++)
            products[i].display();
    }

    int searchProduct(int id) {
        for (int i = 0; i < count; i++) {
            if (products[i].getID() == id) return i;
        }
        return -1;
    }

    void updateQuantity(int id, int newQty) {
        int idx = searchProduct(id);
        if (idx == -1) {
            cout << "Product Not Found!" << endl;
        } else {
            products[idx].setQuantity(newQty);
            cout << "Quantity Updated!" << endl;
        }
    }

    void saveInventory() {
        ofstream out("inventory.txt");
        out << count << endl;
        for (int i = 0; i < count; i++)
            products[i].saveToFile(out);
        out.close();
        cout << "Saved to File!" << endl;
    }

    void loadInventory() {
        ifstream in("inventory.txt");
        if (!in) return;

        in >> count;
        for (int i = 0; i < count; i++)
            products[i].loadFromFile(in);

        in.close();
    }
};

class User {
protected:
    string name;
public:
    User(string n) { name = n; }
    virtual void menu(Inventory& inv) = 0;
};

class Admin : public User {
private:
    string password;
public:
    Admin(string n, string pw) : User(n), password(pw) {}

    bool login() {
        string uname, pw;
        cout << "Enter Admin Username: ";
        cin >> uname;
        cout << "Enter Password: ";
        cin >> pw;

        if (uname == name && pw == password)
            return true;

        cout << "Invalid Credentials!\n";
        return false;
    }

    void menu(Inventory& inv) {
        int choice;
        do {
            cout << "\n--- Admin Menu ---\n";
            cout << "1. Add Product\n2. Show All\n3. Update Quantity\n4. Save\n5. Exit\nEnter choice: ";
            cin >> choice;

            if (choice == 1) inv.addProduct();
            else if (choice == 2) inv.showAll();
            else if (choice == 3) {
                int id, qty;
                cout << "Enter Product ID: "; cin >> id;
                cout << "Enter New Quantity: "; cin >> qty;
                inv.updateQuantity(id, qty);
            }
            else if (choice == 4) inv.saveInventory();

        } while (choice != 5);
    }
};

class Cashier : public User {
public:
    Cashier(string n) : User(n) {}

    void createBill(Inventory& inv) {
        int id, qty;
        float total = 0;
        char more;

        cout << "\n--- Billing ---\n";
        do {
            cout << "Enter Product ID: ";
            cin >> id;

            int idx = inv.searchProduct(id);

            if (idx == -1) {
                cout << "Product Not Found!\n";
            }
            else {
                cout << "Enter Quantity: ";
                cin >> qty;

                if (qty > inv.products[idx].getQuantity()) {
                    cout << "Not enough stock!\n";
                }
                else {
                    float price = inv.products[idx].getPrice() * qty;
                    total += price;

                    cout << inv.products[idx].getName() << " x" << qty << " = " << price << endl;

                    inv.updateQuantity(id, inv.products[idx].getQuantity() - qty);
                }
            }

            cout << "Add more items? (y/n): ";
            cin >> more;

        } while (more == 'y' || more == 'Y');

        cout << "\nTotal Amount: " << total << endl;
    }

    void menu(Inventory& inv) {
        int choice;
        do {
            cout << "\n--- Cashier Menu ---\n";
            cout << "1. Show Products\n2. Search Product\n3. Create Bill\n4. Exit\nEnter choice: ";
            cin >> choice;

            if (choice == 1) inv.showAll();
            else if (choice == 2) {
                int id;
                cout << "Enter ID: ";
                cin >> id;

                int idx = inv.searchProduct(id);

                if (idx == -1) cout << "Not Found!" << endl;
                else cout << "Available!" << endl;
            }
            else if (choice == 3) createBill(inv);

        } while (choice != 4);
    }
};

int main() {
    Inventory inv;
    inv.loadInventory();

    int totalProducts = inv.getCount();
    int lowStock = inv.getLowStock();

    showDashboard(totalProducts, lowStock);

    int dashChoice;
    cin >> dashChoice;

    if (dashChoice == 3) {
        cout << "Exiting...";
        return 0;
    }

    cout << "\nLogin as: 1. Admin  2. Cashier: ";
    int role;
    cin >> role;

    if (role == 1) {
        Admin a("admin", "1234");
        if (a.login()) {
            a.menu(inv);
        }
    }
    else {
        Cashier c("cashier");
        c.menu(inv);
    }

    inv.saveInventory();
    return 0;
}