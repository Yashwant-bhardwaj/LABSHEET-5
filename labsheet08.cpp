/*
Product Class Implementation
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;

class Product {
public:
    int id;
    string name;
    string category;
    float price;
    float rating;

    Product(int id, string name, string category, float price, float rating)
        : id(id), name(name), category(category), price(price), rating(rating) {}

    void display() {
        cout << "ID: " << id << ", Name: " << name
             << ", Category: " << category
             << ", Price: $" << price
             << ", Rating: " << rating << " stars\n";
    }
};

class ProductManager {
private:
    vector<Product> products;

public:
    void addProduct(int id, string name, string category, float price, float rating) {
        products.emplace_back(id, name, category, price, rating);
        cout << "Product added successfully.\n";
    }

    void updateProduct(int id, string name, string category, float price, float rating) {
        for (auto &product : products) {
            if (product.id == id) {
                product.name = name;
                product.category = category;
                product.price = price;
                product.rating = rating;
                cout << "Product updated successfully.\n";
                return;
            }
        }
        cout << "Product with ID " << id << " not found.\n";
    }

    void deleteProduct(int id) {
        auto it = remove_if(products.begin(), products.end(), [&](Product &p) { return p.id == id; });
        if (it != products.end()) {
            products.erase(it, products.end());
            cout << "Product deleted successfully.\n";
        } else {
            cout << "Product with ID " << id << " not found.\n";
        }
    }

    void displayProducts() {
        if (products.empty()) {
            cout << "No products available.\n";
            return;
        }
        for (const auto &product : products) {
            product.display();
        }
    }

    vector<Product>& getProducts() {
        return products;
    }
};
// sorting algorithm implementation 
class Sorting {
public:
    static void bubbleSort(vector<Product>& products, char attribute) {
        for (size_t i = 0; i < products.size() - 1; ++i) {
            for (size_t j = 0; j < products.size() - i - 1; ++j) {
                if (compare(products[j], products[j + 1], attribute)) {
                    swap(products[j], products[j + 1]);
                }
            }
        }
    }

    static void quickSort(vector<Product>& products, int low, int high, char attribute) {
        if (low < high) {
            int pi = partition(products, low, high, attribute);
            quickSort(products, low, pi - 1, attribute);
            quickSort(products, pi + 1, high, attribute);
        }
    }

private:
    static int partition(vector<Product>& products, int low, int high, char attribute) {
        Product pivot = products[high];
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            if (!compare(products[j], pivot, attribute)) {
                ++i;
                swap(products[i], products[j]);
            }
        }
        swap(products[i + 1], products[high]);
        return i + 1;
    }

    static bool compare(const Product& a, const Product& b, char attribute) {
        switch (attribute) {
        case 'p': return a.price > b.price;
        case 'r': return a.rating > b.rating;
        case 'n': return a.name > b.name;
        default: return false;
        }
    }
};
// searching algorithm implementation 
class Searching {
public:
    static int sequentialSearch(const vector<Product>& products, int id) {
        for (size_t i = 0; i < products.size(); ++i) {
            if (products[i].id == id) return i;
        }
        return -1;
    }

    static int binarySearch(const vector<Product>& products, int id, int low, int high) {
        if (low > high) return -1;
        int mid = low + (high - low) / 2;
        if (products[mid].id == id) return mid;
        if (products[mid].id > id) return binarySearch(products, id, low, mid - 1);
        return binarySearch(products, id, mid + 1, high);
    }
};
// main function to run the all class templates 
int main() {
    ProductManager manager;
    vector<Product>& products = manager.getProducts();
    int choice;

    while (true) {
        cout << "\nE-Commerce Product Management System\n";
        cout << "1. Add Product\n";
        cout << "2. Update Product\n";
        cout << "3. Delete Product\n";
        cout << "4. Display Products\n";
        cout << "5. Sort Products\n";
        cout << "6. Search Product by ID\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 7) break;

        switch (choice) {
        case 1: {
            int id;
            string name, category;
            float price, rating;
            cout << "Enter Product ID, Name, Category, Price, Rating: ";
            cin >> id >> name >> category >> price >> rating;
            manager.addProduct(id, name, category, price, rating);
            break;
        }
        case 2: {
            int id;
            string name, category;
            float price, rating;
            cout << "Enter Product ID to Update: ";
            cin >> id;
            cout << "Enter New Name, Category, Price, Rating: ";
            cin >> name >> category >> price >> rating;
            manager.updateProduct(id, name, category, price, rating);
            break;
        }
        case 3: {
            int id;
            cout << "Enter Product ID to Delete: ";
            cin >> id;
            manager.deleteProduct(id);
            break;
        }
        case 4: {
            manager.displayProducts();
            break;
        }
        case 5: {
            char attribute;
            cout << "Sort by Price (p), Rating (r), Name (n): ";
            cin >> attribute;
            Sorting::bubbleSort(products, attribute);
            cout << "Products sorted successfully.\n";
            break;
        }
        case 6: {
            int id;
            cout << "Enter Product ID to Search: ";
            cin >> id;
            int index = Searching::sequentialSearch(products, id);
            if (index != -1) {
                cout << "Product found:\n";
                products[index].display();
            } else {
                cout << "Product not found.\n";
            }
            break;
        }
        default:
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
/*4.E-Commerce System Development:
Develop a user interface (UI) using a framework such as Qt for C++.
Provide functionalities to manage and visualize the product list.
Allow users to perform searches and sorts interactively.*/
// product class impkemetation
#include <iostream>
#include <vector>
#include <QString>

class Product {
public:
    int id;
    std::string name;
    std::string category;
    float price;
    float rating;

    Product(int id, std::string name, std::string category, float price, float rating)
        : id(id), name(name), category(category), price(price), rating(rating) {}

    // Method to display the product details
    QString getDetails() const {
        return QString("ID: %1, Name: %2, Category: %3, Price: %4, Rating: %5")
            .arg(id)
            .arg(QString::fromStdString(name))
            .arg(QString::fromStdString(category))
            .arg(price)
            .arg(rating);
    }
};
// MainWindow GUI Class
#include <QApplication>
#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QLineEdit>
#include <QComboBox>
#include <QHeaderView>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr)
        : QMainWindow(parent) {
        
        // Initialize product list
        productList.push_back(Product(1, "Product A", "Category 1", 10.5, 4.5));
        productList.push_back(Product(2, "Product B", "Category 2", 20.0, 3.8));
        productList.push_back(Product(3, "Product C", "Category 3", 5.0, 4.8));

        // Set up the main layout
        QWidget *centralWidget = new QWidget(this);
        QVBoxLayout *layout = new QVBoxLayout(centralWidget);

        // Product Table
        tableWidget = new QTableWidget(this);
        tableWidget->setRowCount(productList.size());
        tableWidget->setColumnCount(5);
        tableWidget->setHorizontalHeaderLabels({"ID", "Name", "Category", "Price", "Rating"});
        tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        layout->addWidget(tableWidget);

        // Search and Sort Controls
        QLineEdit *searchBox = new QLineEdit(this);
        searchBox->setPlaceholderText("Search by Name or ID");
        layout->addWidget(searchBox);

        QComboBox *sortComboBox = new QComboBox(this);
        sortComboBox->addItem("Sort by Price");
        sortComboBox->addItem("Sort by Rating");
        sortComboBox->addItem("Sort by Name");
        layout->addWidget(sortComboBox);

        // Buttons
        QPushButton *addButton = new QPushButton("Add Product", this);
        QPushButton *deleteButton = new QPushButton("Delete Product", this);
        QPushButton *updateButton = new QPushButton("Update Product", this);

        layout->addWidget(addButton);
        layout->addWidget(deleteButton);
        layout->addWidget(updateButton);

        // Set up the central widget
        setCentralWidget(centralWidget);

        // Connect signals to slots
        connect(addButton, &QPushButton::clicked, this, &MainWindow::addProduct);
        connect(deleteButton, &QPushButton::clicked, this, &MainWindow::deleteProduct);
        connect(updateButton, &QPushButton::clicked, this, &MainWindow::updateProduct);
        connect(searchBox, &QLineEdit::textChanged, this, &MainWindow::searchProduct);
        connect(sortComboBox, &QComboBox::currentIndexChanged, this, &MainWindow::sortProducts);

        // Initialize Table
        populateTable();
    }

private slots:
    void addProduct() {
        // Example: Add product dynamically (for simplicity, we use static values)
        int newId = productList.size() + 1;
        productList.push_back(Product(newId, "New Product", "New Category", 30.0, 4.2));
        populateTable();
    }

    void deleteProduct() {
        int row = tableWidget->currentRow();
        if (row >= 0) {
            int id = tableWidget->item(row, 0)->text().toInt();
            auto it = std::find_if(productList.begin(), productList.end(),
                [id](const Product &p) { return p.id == id; });
            if (it != productList.end()) {
                productList.erase(it);
                populateTable();
            }
        }
    }

    void updateProduct() {
        int row = tableWidget->currentRow();
        if (row >= 0) {
            int id = tableWidget->item(row, 0)->text().toInt();
            auto it = std::find_if(productList.begin(), productList.end(),
                [id](const Product &p) { return p.id == id; });
            if (it != productList.end()) {
                it->name = "Updated Product";
                it->price = 25.0;
                populateTable();
            }
        }
    }

    void searchProduct(const QString &text) {
        // Search products by name or ID
        for (int row = 0; row < tableWidget->rowCount(); ++row) {
            bool matches = false;
            for (int col = 0; col < 5; ++col) {
                QString itemText = tableWidget->item(row, col)->text();
                if (itemText.contains(text, Qt::CaseInsensitive)) {
                    matches = true;
                    break;
                }
            }
            tableWidget->setRowHidden(row, !matches);
        }
    }

    void sortProducts(int index) {
        switch (index) {
            case 0: // Sort by price
                std::sort(productList.begin(), productList.end(),
                    [](const Product &a, const Product &b) { return a.price < b.price; });
                break;
            case 1: // Sort by rating
                std::sort(productList.begin(), productList.end(),
                    [](const Product &a, const Product &b) { return a.rating > b.rating; });
                break;
            case 2: // Sort by name
                std::sort(productList.begin(), productList.end(),
                    [](const Product &a, const Product &b) { return a.name < b.name; });
                break;
        }
        populateTable();
    }

    void populateTable() {
        tableWidget->setRowCount(productList.size());
        for (int row = 0; row < productList.size(); ++row) {
            const Product &product = productList[row];
            tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(product.id)));
            tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(product.name)));
            tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(product.category)));
            tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(product.price)));
            tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(product.rating)));
        }
    }

private:
    QTableWidget *tableWidget;
    std::vector<Product> productList;
};

// Main function
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.setWindowTitle("E-Commerce System");
    window.resize(800, 600);
    window.show();
    return app.exec();
}
