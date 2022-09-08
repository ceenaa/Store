#ifndef STORE_H
#define STORE_H

#include <vector>
#include <string>
#include <map>
#include <utility>
#include "Date.h"

// ------------------------------------------ Product -------------------------------- //

class Product
{
public:
    Product(int, std::string, float, std::string, Date);
    int getID() const;
    void setID(int);
    std::string getName();
    void setName(std::string);
    float getPrice() const;
    void setPrice(float);
    std::string getBrand();
    int getYear();
    int getMonth();
    void setBrand(std::string);
    Date getExpireDate();
    void setExpireDate(Date);
    void printProdDetail() const;

private:
    int id;
    std::string name;
    float price;
    std::string brand;
    Date expire_date;

};

// ------------------------------------------ Stock -------------------------------- //

class Stock
{
public:
    int get_count(int);
    void change_count_by(int, int);
    void addProductToStock(std::pair<int, int>);
    std::map<int, int>& returnRefstockList();
    std::map<int, int> returnStockList();

private:
    std::map<int, int> stockList;

};

// ------------------------------------------ Cart -------------------------------- //

class Cart
{
public:
    float get_total_price(const std::vector<Product>&);
    void addToCart(int product_id, int quantity, const std::map<int, int>&);
    void remove_item(int product_id);
    void print(const std::vector<Product>&);
    void check_out();
    void reset();
    int returnQuantity(int);
    void changeStock(Stock&);
    std::map<int, int> returnItems();
    void setItems(std::map<int, int>);

private:
    std::map<int, int> items;

};

// ------------------------------------------ Receipt -------------------------------- //

class Receipt
{
public:
    // mp = store products map
    float get_total_price(const std::vector<Product>&);
    void setItems(std::map<int, int>);
    std::map<int, int> returnReceipt();
    Date &getDate();
    Date returnDate();
    void setDate(Date);

private:
    Date date;
    std::map<int, int> items;
};

// ------------------------------------------ Customer -------------------------------- //

class Customer
{
public:
    Customer(int, std::string, std::string, std::string, float);
    void convert_cart_to_receipt(const std::vector<Product>&);
    float get_total_purchace_amount(const std::vector<Product>& );
    int getID();
    void setID(int);
    std::string getName();
    void setName(std::string);
    std::string getPhoneNumber();
    void setPhoneNumber(std::string);
    std::string getAddress();
    void setAddress(std::string);
    float getBalance();
    void setBalance(float);
    std::vector<Receipt> getHistory();
    Cart cart;
    void addToHistory(Receipt);

private:
    int id;
    std::string name;
    std::string phone_number;
    std::vector<Receipt> history;
    std::string address;
    float balance;
};

// ------------------------------------------ Store -------------------------------- //

class Store
{
public:
    Store();
    void check_out(int);
    void add_customer();
    void add_product();
    void view_products();
    std::vector<Product> returnProd();
    std::vector<Customer> returnCustomers();
    std::map<int, int>& returnRefStock();
    std::map<int, int> returnStock();
    std::vector<Product>& returnRefProd();
    Customer& returnCus(int id);
    Stock& returnSt();

    void save_to_file();
    void sales_report(Date, Date);
private:
    std::vector<Product> products;
    Stock stock;
    std::vector<Customer> customers;
};
#endif // STORE_H
