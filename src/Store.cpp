#include <iostream>
#include <stdexcept>
#include <fstream>
#include <ctime>
#include "Store.h"

using namespace std;

// ------------------------------------------ Store -------------------------------- //

Store::Store()
{
    ifstream productInFile("Products.txt");
    if(!productInFile)
        throw invalid_argument("Error in openning Product.txt");
    ifstream stockInFile("Stock.txt");
    if(!stockInFile)
        throw invalid_argument("Error in openning Stock.txt");
    ifstream customerInFile("Customers.txt");
    if(!customerInFile)
        throw invalid_argument("Error in openning Customer.txt");
    ifstream ReceiptInFile("Receipt.txt");
    if(!ReceiptInFile)
        throw invalid_argument("Error in openning Receipt.txt");
    ifstream cartInFile("Cart.txt");
    if(!cartInFile)
        throw invalid_argument("Error in openning Cart.txt");

    int id, year, month, st, day;
    float price, balance;
    string name, brand, address, phoneNumber;
    while(productInFile >> id >> name >> price >> brand >> year >> month)
    {
        Date d(year, month);
        Product p(id, name, price, brand, d);
        products.push_back(p);
    }
    pair<int, int> p1;
    while(stockInFile >> id >> st)
    {
        p1.first = id;
        p1.second = st;
        stock.addProductToStock(p1);
    }
    while(customerInFile >> id >> name >> phoneNumber >> address >> balance)
    {
        Customer c(id, name, phoneNumber, address, balance );
        customers.push_back(c);
    }
    while(ReceiptInFile >> id)
    {
        int countOfReceipt, countOfPair;
        ReceiptInFile >> countOfReceipt;
        Customer &t = returnCus(id);
        for(int i = 0; i < countOfReceipt; i++)
        {
            Receipt rt;
            map<int, int> mp;
            pair<int, int> tp;
            ReceiptInFile >> countOfPair;
            for(int j = 0; j < countOfPair; j++)
            {
                ReceiptInFile >> tp.first >> tp.second;
                mp.insert(tp);
            }
            ReceiptInFile >> year >> month >> day;
            Date da(year, month, day);
            rt.setItems(mp);
            rt.setDate(da);
            t.addToHistory(rt);
        }
    }

    while(cartInFile >> id)
    {
        int countOfPair;
        cartInFile >> countOfPair;
        Customer &t = returnCus(id);
        map<int, int> mp;
        for(int i = 0; i < countOfPair; i++)
        {
            Cart ct;
            pair<int, int> tp;
            cartInFile >> tp.first >> tp.second;
            mp.insert(tp);
        }
        t.cart.setItems(mp);
    }

    productInFile.close();
    customerInFile.close();
    stockInFile.close();
    cartInFile.close();
    ReceiptInFile.close();
}

void Store::add_product()
{
    int id, year, month, st;
    float price;
    string name, brand;
    cout << "Add product" << endl;
    cout << "-ID: ";
    cin >> id;
    for(auto itr = products.begin(); itr != products.end(); ++itr)
        if(id == itr->getID())
            throw invalid_argument("Used ID please try again with new ID.");
    cout << "-Name: ";
    cin >> name;
    cout << "-Price: ";
    cin >> price;
    cout << "-Brand: ";
    cin >> brand;
    cout << "-Expire date: ";
    cin >> year >> month;
    cout << "-In stock: ";
    cin >> st;
    Date d(year, month);
    Product p(id, name, price, brand, d);
    products.push_back(p);
    pair<int, int> p1;
    p1.first = id;
    p1.second = st;
    stock.addProductToStock(p1);

}

void Store::add_customer()
{
    int id;
    string phoneNumber, name, address;
    int balance;
    cout << "Add customer" << endl;
    cout << "-ID: ";
    cin >> id;
    for(auto itr = customers.begin(); itr != customers.end(); ++itr)
        if(id == itr->getID())
            throw invalid_argument("Used ID please try again with new ID.");
    cout << "-Name: ";
    cin >> name;
    cout << "-Phone Number: ";
    cin >> phoneNumber;
    cout << "-Address: ";
    cin >> address;
    cout << "-Balance: ";
    cin >> balance;
    Customer c(id, name, phoneNumber, address, balance);
    customers.push_back(c);
}

void Store::check_out(int customer_id)
{
    Customer &t = returnCus(customer_id);
    t.cart.changeStock(returnSt());
    t.convert_cart_to_receipt(returnRefProd());
}

void Store::view_products()
{
    if(products.size() == 0)
        throw invalid_argument("No Product is available.");
    for(auto itr = products.begin(); itr != products.end(); ++itr)
        itr->printProdDetail();
}

map<int, int>& Store::returnRefStock()
{
    return stock.returnRefstockList();
}
map<int, int>Store::returnStock()
{
    return stock.returnStockList();
}
vector<Product>& Store::returnRefProd()
{
    return products;
}

Customer& Store::returnCus(int id)
{
    for(auto itr = customers.begin(); itr != customers.end(); ++itr)
        if(itr->getID() == id)
            return *itr;
    throw
        invalid_argument("Customer is not found.");
}

Stock& Store::returnSt()
{
    return stock;
}

vector<Product> Store::returnProd()
{
    return products;
}
vector<Customer> Store::returnCustomers()
{
    return customers;
}

void Store::save_to_file()
{
    ofstream prodFile("Products.txt", ios::out);
    ofstream customerFile("Customers.txt", ios::out);
    ofstream stockFile("Stock.txt", ios::out);
    ofstream receiptFile("Receipt.txt", ios::out);
    ofstream cartFile("Cart.txt", ios::out);

    vector<Product> sp = returnProd();
    vector<Customer> sc = returnCustomers();
    map<int, int> ss = returnStock();

    for(auto itr = sp.begin(); itr != sp.end(); ++itr)
    {
        prodFile << itr->getID() << endl;
        prodFile << itr->getName() << endl;
        prodFile << itr->getPrice() << endl;
        prodFile << itr->getBrand() << endl;
        prodFile << itr->getYear() << endl;
        prodFile << itr->getMonth() << endl;
    }
    for(auto itr = sc.begin(); itr != sc.end(); ++itr)
    {
        customerFile << itr->getID() << endl;
        customerFile << itr->getName() << endl;
        customerFile << itr->getPhoneNumber() << endl;
        customerFile << itr->getAddress() << endl;
        customerFile << itr->getBalance() << endl;
    }

    for(auto itr = ss.begin(); itr != ss.end(); ++itr)
    {
        stockFile << itr->first << endl;
        stockFile << itr->second << endl;
    }
    for(auto itr = sc.begin(); itr != sc.end(); ++itr)
    {
        receiptFile << itr->getID() << endl;
        vector<Receipt> t = itr->getHistory();
        receiptFile << t.size() << endl;
        for(auto jtr = t.begin(); jtr != t.end(); ++jtr)
        {
            map<int, int> item = jtr->returnReceipt();
            receiptFile << item.size() << endl;
            for(auto ktr = item.begin(); ktr != item.end(); ++ktr)
                receiptFile << ktr->first << " " << ktr->second << endl;
            receiptFile << jtr->getDate().getYear() << " " << jtr->getDate().getMonth() << " " << jtr->getDate().getDay() << endl;
        }
    }

    for(auto itr = sc.begin(); itr != sc.end(); ++itr)
    {
        cartFile << itr->getID() << endl;
        map<int, int> t = itr->cart.returnItems();
        cartFile << t.size() << endl;
        for(auto jtr = t.begin(); jtr != t.end(); ++jtr)
            cartFile << jtr->first << " " << jtr->second << endl;
    }
    prodFile.close();
    customerFile.close();
    receiptFile.close();
    stockFile.close();
    cartFile.close();
}

void Store::sales_report(Date s, Date e)
{
    float p = 0, best = 0, total = 0;
    Date bestDate;
    e++;
    while(!(s == e))
    {
        p = 0;
        for(auto itr = customers.begin(); itr != customers.end(); ++itr)
        {
            vector<Receipt> rt = itr->getHistory();
            for(auto jtr = rt.begin(); jtr != rt.end(); ++jtr)
            {
                if(jtr->returnDate() == s)
                    p += jtr->get_total_price(returnRefProd());
            }
        }
        cout << s << ": ";
        for(int i = 0; i < (int)p/100; i++)
            cout << " ++";
        cout << endl;
        total += p;
        if(p > best)
        {
            best = p;
            bestDate = s;
        }
        s++;
    }
    cout << "Total sell: " << total << endl;
    cout << "The best selling Date: " << bestDate << endl << "With total sell: " << best << endl;

}

// ------------------------------------------ Product -------------------------------- //

Product::Product(int i, string n, float p, string b, Date d)
    :id(i), name(n), price(p), brand(b), expire_date(d) { };

int Product::getID() const
{
    return id;
}
void Product::setID(int i)
{
    id = i;
}
string Product::getName()
{
    return name;
}
string Product::getBrand()
{
    return brand;
}
void Product::setName(string n)
{
    name = n;
}
float Product::getPrice() const
{
    return price;
}
int Product::getYear()
{
   return expire_date.getYear();
}
int Product::getMonth()
{
    return expire_date.getMonth();
}
void Product::printProdDetail() const
{
    cout << "Product Name: " << name << endl;
    cout << "ID: " << id << endl;
    cout << "Brand: " << brand << endl;
    cout << "Expire Date: ";
    expire_date.print();
    cout << "Price: " << price << endl;

}

// ------------------------------------------ Customer -------------------------------- //

Customer::Customer(int i, string n, string p, string a, float b)
    :id(i), name(n), phone_number(p), address(a), balance(b){ }

int Customer::getID()
{
    return id;
}
void Customer::setID(int i)
{
    id = i;
}
string Customer::getName()
{
    return name;
}
void Customer::setName(string n)
{
    name = n;
}
string Customer::getPhoneNumber()
{
    return phone_number;
}
void Customer::setPhoneNumber(string p)
{
    phone_number = p;
}
string Customer::getAddress()
{
    return address;
}
void Customer::setAddress(string a)
{
    address = a;
}
float Customer::getBalance()
{
    return balance;
}
void Customer::setBalance(float b)
{
    balance = b;
}
vector<Receipt> Customer::getHistory()
{
    return history;
}

void Customer::convert_cart_to_receipt(const vector<Product>& vc)
{
    if(balance < cart.get_total_price(vc) )
        throw invalid_argument("Balance is not enough");
    if(cart.get_total_price(vc) == 0)
        throw invalid_argument("Cart is Empty");

    balance -= cart.get_total_price(vc);
    Receipt n;
    n.setItems(cart.returnItems());

    time_t now = time(0);
    tm *ltm = localtime(&now);
    Date d(1900+ltm->tm_year, 1+ltm->tm_mon, ltm->tm_mday);
    n.setDate(d);
    history.push_back(n);
    cart.reset();

}

float Customer::get_total_purchace_amount(const vector<Product>& dq)
{
    float p = 0;
    for(auto itr = history.begin(); itr != history.end(); ++itr)
    {
        p += itr->get_total_price(dq);
    }
    return p;
}

void Customer::addToHistory(Receipt r)
{
    history.push_back(r);
}

// ------------------------------------------ Stock -------------------------------- //

void Stock::addProductToStock(pair<int, int> p1)
{
    stockList.insert(p1);
}

void Stock::change_count_by(int product_id, int count1)
{
    auto itr = stockList.find(product_id);
    if(itr == stockList.end())
        throw invalid_argument("item is not in stock.");
    itr->second += count1;
}

int Stock::get_count(int product_id)
{
    auto itr = stockList.find(product_id);
    if(itr == stockList.end())
        throw invalid_argument("item is not in stock.");
    return itr->second;
}
map<int, int>& Stock::returnRefstockList()
{
    return stockList;
}
map<int, int> Stock::returnStockList()
{
    return stockList;
}

// ------------------------------------------ Cart -------------------------------- //

// mp = store -> stock -> stockList
void Cart::addToCart(int product_id, int quantity, const map<int, int>& mp)
{
    auto itr = mp.find(product_id);
    if(itr == mp.end())
        throw invalid_argument("item is not in stock.");
    if(itr->second < quantity)
        throw invalid_argument("item quantity is less than what you want.");
    pair<int, int> p;
    p.first = product_id;
    p.second = quantity;

    items.insert(p);
}

void Cart::remove_item(int product_id)
{
    auto itr = items.find(product_id);
    if(itr == items.end())
        throw invalid_argument("item is not in card.");
    items.erase(product_id);
}

void Cart::reset()
{
    items.clear();
}

float Cart::get_total_price(const vector<Product>& dq)
{
    float p = 0;
    for(auto mapItr = items.begin(); mapItr != items.end(); ++mapItr)
    {
        for(auto it = dq.begin(); it!= dq.end(); ++it)
        {
            if(it->getID() == mapItr->first)
            {
                p += (it->getPrice() * mapItr->second);
                break;
            }
        }
    }

    return p;
}

void Cart::print(const vector<Product>& dq)
{
    if(items.size() == 0)
        throw invalid_argument("The cart is Empty.");
    for(auto mapItr = items.begin(); mapItr != items.end(); ++mapItr)
        for(auto it = dq.begin(); it!= dq.end(); ++it)
            if(it->getID() == mapItr->first)
            {
                it->printProdDetail();
                cout << "Count: " << mapItr->second << endl;
            }
}

map<int, int> Cart::returnItems()
{
    return items;
}

int Cart::returnQuantity(int i)
{
    auto itr = items.find(i);
    if(itr == items.end())
        throw invalid_argument("item is not in items.");
    return itr->second;
}

void Cart::changeStock(Stock& st)
{
    for(auto itr = items.begin(); itr != items.end(); ++itr)
        st.change_count_by(itr->first, -1*itr->second);
}

void Cart::setItems(map<int, int> mp)
{
    items = mp;
}

// ------------------------------------------ Receipt -------------------------------- //

float Receipt::get_total_price(const vector<Product>& dq)
{
    float p = 0;
    for(auto mapItr = items.begin(); mapItr != items.end(); ++mapItr)
    {
        for(auto it = dq.begin(); it!= dq.end(); ++it)
        {
            if(it->getID() == mapItr->first)
            {
                p += (it->getPrice() * mapItr->second);
                break;
            }
        }
    }
    return p;
}

void Receipt::setItems(map<int, int> mp)
{
    items = mp;
}

map<int, int> Receipt::returnReceipt()
{
    return items;
}

Date& Receipt::getDate()
{
    return date;
}
void Receipt::setDate(Date d)
{
    date.setYear(d.getYear());
    date.setMonth(d.getMonth());
    date.setDay(d.getDay());
}
Date Receipt::returnDate()
{
    return date;
}
