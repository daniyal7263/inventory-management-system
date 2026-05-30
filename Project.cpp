#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <string>

using namespace std;
class Product {
private:
    int productId;
    string productName;
    int quantityInStock;
    double unitPrice;

public:
    Product() {
        productId = 0;
        productName = "";
        quantityInStock = 0;
        unitPrice = 0.0;
    }
    Product(int id, const string& name, int quantity, double price) {
        productId = id;
        productName = name;
        quantityInStock = quantity;
        unitPrice = price;
    }
    int getId() const {
        return productId;
    }

    string getName() const {
        return productName;
    }

    int getQuantity() const {
        return quantityInStock;
    }

    double getPrice() const {
        return unitPrice;
    }
    void setQuantity(int quantity) {
        quantityInStock = quantity;
    }

    void setPrice(double price) {
        unitPrice = price;
    }

    
    double getTotalValue() const {
        return quantityInStock * unitPrice;
    }

    void display() const {
        cout << left
             << setw(10) << productId
             << setw(25) << productName
             << setw(10) << quantityInStock
             << setw(15) << fixed << setprecision(2) << unitPrice
             << setw(15) << getTotalValue()
             << endl;
    }
};

class InventoryManager {
private:
    vector<Product> products;

  
    int findProductIndexById(int productId) const {
        for (size_t i = 0; i < products.size(); ++i) {
            if (products[i].getId() == productId) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    int readInteger(const string& prompt) {
        int value;

        while (true) {
            cout << prompt;

            if (cin >> value) {
                return value;
            }

            cout << "Invalid input! Please enter a valid integer." << endl;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    double readDouble(const string& prompt) {
        double value;

        while (true) {
            cout << prompt;

            if (cin >> value) {
                return value;
            }

            cout << "Invalid input! Please enter a valid number." << endl;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    string readLine(const string& prompt) {
        cout << prompt;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string value;
        getline(cin, value);

        return value;
    }

public:
    void addProduct() {
        int id = readInteger("\nEnter Product ID: ");

      
        if (findProductIndexById(id) != -1) {
            cout << "A product with this ID already exists." << endl;
            return;
        }

        string name = readLine("Enter Product Name: ");
        int quantity = readInteger("Enter Quantity: ");
        double price = readDouble("Enter Unit Price: ");

        products.push_back(Product(id, name, quantity, price));

        cout << "Product added successfully." << endl;
    }

   
    void displayAllProducts() const {
        if (products.empty()) {
            cout << "\nNo products available in inventory." << endl;
            return;
        }

        cout << "\n========================= INVENTORY =========================" << endl;

        cout << left
             << setw(10) << "ID"
             << setw(25) << "Name"
             << setw(10) << "Qty"
             << setw(15) << "Unit Price"
             << setw(15) << "Total Value"
             << endl;

        cout << string(75, '-') << endl;

        for (size_t i = 0; i < products.size(); ++i) {
            products[i].display();
        }
    }

    void searchProduct() const {
        if (products.empty()) {
            cout << "\nInventory is empty." << endl;
            return;
        }

        int id;

        cout << "\nEnter Product ID to search: ";
        cin >> id;

        int index = findProductIndexById(id);

        if (index == -1) {
            cout << "Product not found." << endl;
            return;
        }

        cout << "\nProduct Found:" << endl;
        cout << string(75, '-') << endl;

        cout << left
             << setw(10) << "ID"
             << setw(25) << "Name"
             << setw(10) << "Qty"
             << setw(15) << "Unit Price"
             << setw(15) << "Total Value"
             << endl;

        cout << string(75, '-') << endl;

        products[index].display();
    }

    void updateProductQuantity() {
        int id = readInteger("\nEnter Product ID: ");

        int index = findProductIndexById(id);

        if (index == -1) {
            cout << "Product not found." << endl;
            return;
        }

        int newQuantity = readInteger("Enter New Quantity: ");

        products[index].setQuantity(newQuantity);

        cout << "Product quantity updated successfully." << endl;
    }

    void deleteProduct() {
        int id = readInteger("\nEnter Product ID to delete: ");

        int index = findProductIndexById(id);

        if (index == -1) {
            cout << "Product not found." << endl;
            return;
        }

        products.erase(products.begin() + index);

        cout << "Product deleted successfully." << endl;
    }

    void sortByName() {
        if (products.empty()) {
            cout << "\nNo products available to sort." << endl;
            return;
        }

        sort(products.begin(), products.end(),
             [](const Product& a, const Product& b) {
                 return a.getName() < b.getName();
             });

        cout << "Products sorted by name successfully." << endl;
    }

    void sortByPrice() {
        if (products.empty()) {
            cout << "\nNo products available to sort." << endl;
            return;
        }

        sort(products.begin(), products.end(),
             [](const Product& a, const Product& b) {
                 return a.getPrice() < b.getPrice();
             });

        cout << "Products sorted by price successfully." << endl;
    }

    void calculateTotalInventoryValue() const {
        if (products.empty()) {
            cout << "\nInventory is empty." << endl;
            return;
        }

        double totalValue = 0.0;

        for (size_t i = 0; i < products.size(); ++i) {
            totalValue += products[i].getTotalValue();
        }

        cout << "\nTotal Inventory Value: Rs. "
             << fixed << setprecision(2)
             << totalValue << endl;
    }

    void showMenu() const {
        cout << "\n==================================================" << endl;
        cout << "          INVENTORY MANAGEMENT SYSTEM" << endl;
        cout << "==================================================" << endl;
        cout << "1. Add Product" << endl;
        cout << "2. Display All Products" << endl;
        cout << "3. Search Product" << endl;
        cout << "4. Update Product Quantity" << endl;
        cout << "5. Delete Product" << endl;
        cout << "6. Sort Products by Name" << endl;
        cout << "7. Sort Products by Price" << endl;
        cout << "8. Calculate Total Inventory Value" << endl;
        cout << "9. Exit" << endl;
        cout << "==================================================" << endl;
    }

    void run() {
        int choice;

        do {
            showMenu();

            choice = readInteger("Enter your choice: ");

            switch (choice) {
                case 1:
                    addProduct();
                    break;

                case 2:
                    displayAllProducts();
                    break;

                case 3:
                    searchProduct();
                    break;

                case 4:
                    updateProductQuantity();
                    break;

                case 5:
                    deleteProduct();
                    break;

                case 6:
                    sortByName();
                    break;

                case 7:
                    sortByPrice();
                    break;

                case 8:
                    calculateTotalInventoryValue();
                    break;

                case 9:
                    cout << "\nThank you for using Inventory Management System." << endl;
                    break;

                default:
                    cout << "Invalid choice. Please try again." << endl;
            }

        } while (choice != 9);
    }
};

int main() {
    InventoryManager inventorySystem;
    inventorySystem.run();

    return 0;
}