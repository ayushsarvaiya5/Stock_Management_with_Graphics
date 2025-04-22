#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <string>
#include <iomanip>

using namespace std;

struct Product
{
    int id;
    string name;
    float price;
    int quantity;
};

struct BillingItem
{
    Product product;
    int quantity;
};

vector<Product> stock;
vector<BillingItem> bill;

void addProduct();
void updateProduct();
void deleteProduct();
void displayAllProducts();
void searchProduct();
void saveToFile();
void loadFromFile();
void sortByPrice();
void sortByQuantity();
void searchByName();
void restockProduct();
void checkLowStockItems();
void generateReports();
void generateBill();      
void updateStockToFile(); 
float calculateTotalStockValue();
void findHighestPricedItem();
void findLowestPricedItem();
void findTopSellingItems();
bool isProductIDExists(int id);
void displayCustomerMenu();
void displayOwnerMenu();
void addProductToBill();

int main()
{
    loadFromFile();

    int choice;
    string password;

    do
    {
        system("CLS");
        cout << "\n===== Stock Management Menu =====\n";
        cout << "1. Customer Partition\n";
        cout << "2. Owner Partition\n";
        cout << "3. Exit\n";
        cout << "=================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            displayCustomerMenu();
            break;
        case 2:
            cout << "Enter the owner password: ";
            cin >> password;
            if (password == "Hello")
            {
                displayOwnerMenu();
            }
            else
            {
                cout << "Invalid password! Access denied.\n";
            }
            break;
        case 3:
            cout << "Exiting the program. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}

void displayCustomerMenu()
{
    int choice;
    do
    {
        cout << "\n===== Customer Partition =====\n";
        displayAllProducts();
        cout << "1. Add Product to Bill\n";
        cout << "2. Generate Bill\n";
        cout << "3. Back to Main Menu\n";
        cout << "==============================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            addProductToBill();
            break;
        case 2:
            generateBill();
            saveToFile();
            break;
        case 3:
            cout << "Exiting Customer Partition. Returning to Main Menu.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);
}

void displayOwnerMenu()
{
    int choice;
    do
    {
        cout << "\n===== Owner Partition =====\n";
        cout << "1. Add Product\n";
        cout << "2. Update Product\n";
        cout << "3. Delete Product\n";
        cout << "4. Display All Products\n";
        cout << "5. Search Product\n";
        cout << "6. Save to File\n";
        cout << "7. Sort by Price\n";
        cout << "8. Sort by Quantity\n";
        cout << "9. Search by Name\n";
        cout << "10. Restock Product\n";
        cout << "11. Check Low Stock Items\n";
        cout << "12. Reports and Analytics\n";
        cout << "13. Back to Main Menu\n";
        cout << "===========================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            addProduct();
            break;
        case 2:
            updateProduct();
            break;
        case 3:
            deleteProduct();
            break;
        case 4:
            displayAllProducts();
            break;
        case 5:
            searchProduct();
            break;
        case 6:
            saveToFile();
            break;
        case 7:
            sortByPrice();
            break;
        case 8:
            sortByQuantity();
            break;
        case 9:
            searchByName();
            break;
        case 10:
            restockProduct();
            break;
        case 11:
            checkLowStockItems();
            break;
        case 12:
            generateReports();
            break;
        case 13:
            cout << "Exiting Owner Partition. Returning to Main Menu.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 13);
}

void addProductToBill()
{
    int idToAdd, quantityToAdd;
    bool found = false;

    cout << "\nAdding products to the bill. Enter 0 to finish.\n";
    do
    {
        cout << "Enter product ID to add to the bill: ";
        cin >> idToAdd;

        if (idToAdd == 0)
            break;

        auto it = find_if(stock.begin(), stock.end(), [idToAdd](const Product &p)
                          { return p.id == idToAdd; });

        if (it != stock.end())
        {
            cout << "Enter quantity to add: ";
            cin >> quantityToAdd;
            if (quantityToAdd <= it->quantity)
            {
                BillingItem item; 
                item.product = *it;
                item.quantity = quantityToAdd;
                bill.push_back(item);
                it->quantity -= quantityToAdd;
                cout << "Product added to the bill successfully!\n";
            }
            else
            {
                cout << "Insufficient quantity in stock!\n";
            }
            found = true;
        }
        else
        {
            cout << "Product with ID " << idToAdd << " not found in stock!\n";
        }
    } while (true);

    cout << "Products added to the bill. Choose 'Generate Bill' to view the final bill.\n";
}

bool isProductIDExists(int id)
{
    auto it = find_if(stock.begin(), stock.end(), [id](const Product &p)
                      { return p.id == id; });
    return it != stock.end();
}

void addProduct()
{
    Product newProduct;
    cout << "\nEnter Product ID: ";
    cin >> newProduct.id;

    if (isProductIDExists(newProduct.id))
    {
        cout << "Product with ID " << newProduct.id << " already exists. Please enter a different ID.\n";
        return;
    }

    cout << "Enter Product Name: ";
    cin >> newProduct.name;
    cout << "Enter Product Price: ";
    cin >> newProduct.price;
    cout << "Enter Product Quantity: ";
    cin >> newProduct.quantity;

    stock.push_back(newProduct);
    cout << "Product added successfully!\n";
}

void updateProduct()
{
    int idToUpdate;
    cout << "Enter the ID of the product to update: ";
    cin >> idToUpdate;

    auto it = find_if(stock.begin(), stock.end(), [idToUpdate](const Product &p)
                      { return p.id == idToUpdate; });

    if (it != stock.end())
    {
        cout << "Enter new Product Name: ";
        cin >> it->name;
        cout << "Enter new Product Price: ";
        cin >> it->price;
        cout << "Enter new Product Quantity: ";
        cin >> it->quantity;
        cout << "Product updated successfully!\n";
    }
    else
    {
        cout << "Product with ID " << idToUpdate << " not found!\n";
    }

    saveToFile();
}

void deleteProduct()
{
    int idToDelete;
    cout << "Enter the ID of the product to delete: ";
    cin >> idToDelete;

    auto it = find_if(stock.begin(), stock.end(), [idToDelete](const Product &p)
                      { return p.id == idToDelete; });

    if (it != stock.end())
    {
        stock.erase(it);
        cout << "Product deleted successfully!\n";
    }
    else
    {
        cout << "Product with ID " << idToDelete << " not found!\n";
    }

    saveToFile();
}

void displayAllProducts()
{
    if (stock.empty())
    {
        cout << "No products in stock!\n";
    }
    else
    {
        cout << "\n===== Stock List =====\n";
        cout << "ID\tName\t\tPrice\t\tQuantity\n";
        for (const auto &product : stock)
        {
            cout << product.id << "\t" << product.name << "\t\t" << product.price << "\t\t" << product.quantity << "\n";
        }
        cout << "=======================\n";
    }
}

void searchProduct()
{
    int idToSearch;
    cout << "\nEnter the ID of the product to search: ";
    cin >> idToSearch;

    auto it = find_if(stock.begin(), stock.end(), [idToSearch](const Product &p)
                      { return p.id == idToSearch; });

    if (it != stock.end())
    {
        cout << "Product found:\n";
        cout << "ID: " << it->id << "\nName: " << it->name << "\nPrice: " << it->price << "\nQuantity: " << it->quantity << "\n";
    }
    else
    {
        cout << "Product with ID " << idToSearch << " not found!\n";
    }
}

void saveToFile()
{
    ofstream file("stock.txt");
    if (!file)
    {
        cout << "Error opening file for writing!\n";
        return;
    }

    for (const auto &product : stock)
    {
        file << product.id << " " << product.name << " " << product.price << " " << product.quantity << "\n";
    }

    cout << "Stock data saved to file successfully!\n";
}

void loadFromFile()
{
    ifstream file("stock.txt");
    if (!file)
    {
        return;
    }

    stock.clear();
    Product product;
    while (file >> product.id >> product.name >> product.price >> product.quantity)
    {
        stock.push_back(product);
    }

    file.close();
}

void sortByPrice()
{
    sort(stock.begin(), stock.end(), [](const Product &a, const Product &b)
         { return a.price < b.price; });
    cout << "Products sorted by price in ascending order.\n";
}

void sortByQuantity()
{
    sort(stock.begin(), stock.end(), [](const Product &a, const Product &b)
         { return a.quantity < b.quantity; });
    cout << "Products sorted by quantity in ascending order.\n";
}

void searchByName()
{
    string nameToSearch;
    cout << "\nEnter the name of the product to search: ";
    cin >> nameToSearch;

    auto it = find_if(stock.begin(), stock.end(), [&nameToSearch](const Product &p)
                      { return p.name == nameToSearch; });

    if (it != stock.end())
    {
        cout << "Product found:\n";
        cout << "ID: " << it->id << "\nName: " << it->name << "\nPrice: " << it->price << "\nQuantity: " << it->quantity << "\n";
    }
    else
    {
        cout << "Product with name '" << nameToSearch << "' not found!\n";
    }
}

void restockProduct()
{
    int idToRestock, quantityToAdd;
    cout << "\nEnter the ID of the product to restock: ";
    cin >> idToRestock;

    auto it = find_if(stock.begin(), stock.end(), [idToRestock](const Product &p)
                      { return p.id == idToRestock; });

    if (it != stock.end())
    {
        cout << "Enter the quantity to add: ";
        cin >> quantityToAdd;
        it->quantity += quantityToAdd;
        cout << "Product restocked successfully!\n";
    }
    else
    {
        cout << "Product with ID " << idToRestock << " not found!\n";
    }

    saveToFile();
}

void checkLowStockItems()
{
    int threshold;
    cout << "\nEnter the minimum stock threshold: ";
    cin >> threshold;

    cout << "\nLow Stock Items:\n";
    cout << "ID\tName\t\tPrice\t\tQuantity\n";
    for (const auto &product : stock)
    {
        if (product.quantity < threshold)
        {
            cout << product.id << "\t" << product.name << "\t\t" << product.price << "\t\t" << product.quantity << "\n";
        }
    }
    cout << "=======================\n";
}

void generateReports()
{
    int reportChoice;

    cout << "\n===== Reports and Analytics =====\n";
    cout << "1. Total Stock Value\n";
    cout << "2. Highest Priced Item\n";
    cout << "3. Lowest Priced Item\n";
    cout << "4. Top Selling Items\n";
    cout << "5. Back to Main Menu\n";
    cout << "=================================\n";

    cout << "Enter your choice: ";
    cin >> reportChoice;

    switch (reportChoice)
    {
    case 1:
        {
            float totalValue = calculateTotalStockValue();
            cout << "Total Stock Value: " << totalValue << "\n";
            break;
        }
    case 2:
        findHighestPricedItem();
        break;
    case 3:
        findLowestPricedItem();
        break;
    case 4:
        findTopSellingItems();
        break;
    case 5:
        break;
    default:
        cout << "Invalid choice. Please try again.\n";
    }
}

float calculateTotalStockValue()
{
    float totalValue = 0;
    for (const auto &product : stock)
    {
        totalValue += product.price * product.quantity;
    }
    return totalValue;
}

void findHighestPricedItem()
{
    if (stock.empty())
    {
        cout << "No products in stock!\n";
    }
    else
    {
        auto highestPricedItem = max_element(stock.begin(), stock.end(), [](const Product &a, const Product &b)
                                             { return a.price < b.price; });

        cout << "Highest Priced Item:\n";
        cout << "ID: " << highestPricedItem->id << "\nName: " << highestPricedItem->name << "\nPrice: " << highestPricedItem->price << "\nQuantity: " << highestPricedItem->quantity << "\n";
    }
}

void findLowestPricedItem()
{
    if (stock.empty())
    {
        cout << "No products in stock!\n";
    }
    else
    {
        auto lowestPricedItem = min_element(stock.begin(), stock.end(), [](const Product &a, const Product &b)
                                            { return a.price < b.price; });

        cout << "Lowest Priced Item:\n";
        cout << "ID: " << lowestPricedItem->id << "\nName: " << lowestPricedItem->name << "\nPrice: " << lowestPricedItem->price << "\nQuantity: " << lowestPricedItem->quantity << "\n";
    }
}

void findTopSellingItems()
{
    int numTopItems;
    cout << "Enter the number of top-selling items to display: ";
    cin >> numTopItems;

    if (stock.empty())
    {
        cout << "No products in stock!\n";
    }
    else if (numTopItems > stock.size() || numTopItems <= 0)
    {
        cout << "Invalid number of top-selling items to display!\n";
    }
    else
    {
        partial_sort(stock.begin(), stock.begin() + numTopItems, stock.end(), [](const Product &a, const Product &b)
                     { return a.quantity > b.quantity; });

        cout << "Top " << numTopItems << " Selling Items:\n";
        cout << "ID\tName\t\tPrice\t\tQuantity\n";
        for (int i = 0; i < numTopItems; ++i)
        {
            cout << stock[i].id << "\t" << stock[i].name << "\t\t" << stock[i].price << "\t\t" << stock[i].quantity << "\n";
        }
        cout << "=======================\n";
    }
}

#include <fstream>
#include <ctime>
#include <iomanip>

void generateBill()
{
    if (bill.empty())
    {
        std::cout << "No products added to the bill!\n";
        return;
    }

    std::ofstream billFile("bills.txt", std::ios_base::app);
    if (!billFile)
    {
        std::cout << "Error opening file for writing bill!\n";
        return;
    }

    time_t currentTime;
    struct tm *timeInfo;

    currentTime = time(nullptr);
    timeInfo = localtime(&currentTime);

    float totalAmount = 0.0;

    billFile << "\n===== Bill =====\n";
    cout << "\n===== Bill =====\n";

    billFile << "Date: " << std::setfill('0') << std::setw(2) << timeInfo->tm_mday << "/"
             << std::setw(2) << timeInfo->tm_mon + 1 << "/" << std::setw(4) << timeInfo->tm_year + 1900 << "\n";
    cout << "Date: " << std::setfill('0') << std::setw(2) << timeInfo->tm_mday << "/"
         << std::setw(2) << timeInfo->tm_mon + 1 << "/" << std::setw(4) << timeInfo->tm_year + 1900 << "\n";

    billFile << "Day of the Week: ";
    cout << "Day of the Week: ";

    switch (timeInfo->tm_wday)
    {
    case 0:
        billFile << "Sunday\n";
        cout << "Sunday\n";
        break;
    case 1:
        billFile << "Monday\n";
        cout << "Monday\n";
        break;
    case 2:
        billFile << "Tuesday\n";
        cout << "Tuesday\n";
        break;
    case 3:
        billFile << "Wednesday\n";
        cout << "Wednesday\n";
        break;
    case 4:
        billFile << "Thursday\n";
        cout << "Thursday\n";
        break;
    case 5:
        billFile << "Friday\n";
        cout << "Friday\n";
        break;
    case 6:
        billFile << "Saturday\n";
        cout << "Saturday\n";
        break;
    default:
        billFile << "Unknown\n";
        cout << "Unknown\n";
    }

    // For Printing in Console
    cout << "Time: " << setw(2) << setfill('0') << timeInfo->tm_hour << ":"
         << setw(2) << timeInfo->tm_min << ":" << setw(2) << timeInfo->tm_sec << "\n";

    cout << "\nID\tName\t\tPrice\t\tQuantity\tTotal\n";
    for (const auto &item : bill)
    {
        float subTotal = item.product.price * item.quantity;
        cout << item.product.id << "\t" << item.product.name << "\t\t" << item.product.price << "\t\t"
             << item.quantity << "\t\t" << subTotal << "\n";
        totalAmount += subTotal;
    }
    cout << "=========================================\n";
    cout << "Total Amount: " << totalAmount << "\n";

    // For Printing in Bills File
    billFile << "Time: " << std::setw(2) << std::setfill('0') << timeInfo->tm_hour << ":"
             << std::setw(2) << timeInfo->tm_min << ":" << std::setw(2) << timeInfo->tm_sec << "\n";

    billFile << "\nID\tName\tPrice\tQuantity\tTotal\n";
    for (const auto &item : bill)
    {
        float subTotal = item.product.price * item.quantity;
        billFile << item.product.id << "\t" << item.product.name << "\t\t" << item.product.price << "\t\t"
                 << item.quantity << "\t\t\t" << subTotal << "\n";
        totalAmount += subTotal;
    }
    billFile << "=========================================\n";
    billFile << "Total Amount: " << totalAmount << "\n";

    billFile.close();
}

void updateStockToFile()
{
    ofstream file("stock.txt");
    if (!file.is_open())
    {
        cout << "Error opening file for writing!\n";
        return;
    }

    for (const auto &product : stock)
    {
        file << product.id << " " << product.name << " " << fixed << setprecision(2) << product.price << " "
             << product.quantity << "\n";
    }

    file.close();
    cout << "Stock data saved to file successfully!\n";
}