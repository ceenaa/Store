#include <iostream>
#include "Store.h"

bool mainPannel(Store &s);
void customerPannel(Store &s);
void cartPannel(Store &s, Customer &c);
void stockPannel(Store &s);

using namespace std;

int main()
{
    Store s;
    bool flag = true;
    while(flag)
    {
        try
        {
            flag = mainPannel(s);
        }
        catch(invalid_argument err)
        {
            system("clear");
            cout << err.what() << endl;
        }

    }

    return 0;
}

bool mainPannel(Store &s)
{
    cout << "---------------------- Main Page ----------------------" << endl;
    int n;
    cout << "1. Add Product" << endl;
    cout << "2. Add Customer" << endl;
    cout << "3. View product" << endl;
    cout << "4. Customer Pannel" << endl;
    cout << "5. Stock Pannel" << endl;
    cout << "6. Check out" << endl;
    cout << "7. Save to file" << endl;
    cout << "8. Sales report" << endl;
    cout << "9. Exit" << endl;
    cin >> n;
    if(n == 1)
    {
        s.add_product();
        system("clear");
        cout << "Item has been successfuly added." << endl;
    }
    if(n == 2)
    {
        s.add_customer();
        system("clear");
        cout << "Customer has been successfuly added." << endl;
    }
    if(n == 3)
    {
        system("clear");
        s.view_products();
    }
    if(n == 4)
    {
        customerPannel(s);
    }
    if( n == 5)
        stockPannel(s);
    if( n == 6)
    {
        system("clear");
        cout << "Please enter ID of Customer that you want to check out." << endl;
        int id;
        cin >> id;
        s.check_out(id);
        cout << "Check out has been successfuly done" << endl;

    }
    if(n == 7)
    {
        s.save_to_file();
        system("clear");
        cout << "Data has been saved to file successfuly." << endl;
    }
    if(n == 8)
    {
        system("clear");
        Date startD, endD;
        cout << "Enter starting date: ";
        cin >> startD;
        cout << "Enter ending date: ";
        cin >> endD;
        s.sales_report(startD, endD);
    }
    if(n == 9)
        return false;
}

void stockPannel(Store &s)
{
    system("clear");
    cout << "---------------------- Stock Page ----------------------" << endl;
    int n;
    cout << "1. Change count" << endl;
    cout << "2. Get count" << endl;
    cout << "3. Main Pannel" << endl;
    cin >> n;
    Stock &st = s.returnSt();
    if(n == 1)
    {
        int n1, n2;
        cout << "Enter Id: ";
        cin >> n1;
        cout << "Enter Count: ";
        cin >> n2;
        st.change_count_by(n1, n2);
        cout << "Change Count has been succsessfuly done" << endl;
    }
    if(n == 2)
    {
        int n1;
        cout << "Enter Id: ";
        cin >> n1;
        cout << "Quantity of product with ID " << n1 << ": "<< st.get_count(n1) << endl;
    }
    if(n == 3)
    {
        system("clear");
        mainPannel(s);
    }
}

void customerPannel(Store &s)
{
    system("clear");
    cout << "---------------------- Customer Page ----------------------" << endl;
    int id;
    cout << "Select your customer ID: " << endl;
    cin >> id;
    Customer &c = s.returnCus(id);
    int n2;
    cout << "1. convert cart to receipt" << endl;
    cout << "2. get total purchase amount" << endl;
    cout << "3. Cart Pannel" << endl;
    cin >> n2;
    if(n2 == 1)
    {
        c.cart.changeStock(s.returnSt());
        c.convert_cart_to_receipt(s.returnRefProd());
        cout << "Convert cart to receipt succeeded" << endl;
    }
    if(n2 == 2)
        cout << "The total purchase amount is : " << c.get_total_purchace_amount(s.returnRefProd()) << endl;
    if(n2 == 3)
        cartPannel(s, c);
}

void cartPannel(Store &s, Customer &c)
{
    system("clear");
    cout << "---------------------- Cart Page ----------------------" << endl;
    int n3;
    cout << "1. Add" << endl;
    cout << "2. Remove item" << endl;
    cout << "3. Print" << endl;
    cout << "4. Reset" << endl;
    cout << "5. Get total price" << endl;
    cout << "6. Main Pannel" << endl;
    cin >> n3;
    if(n3 == 1)
    {
        int i3, q3;
        cout << "Enter the ID of product: ";
        cin >> i3;
        cout << "Enter the quantity of product: ";
        cin >> q3;
        c.cart.addToCart(i3, q3, s.returnRefStock());
        cout << "Item has been added" << endl;
    }
    if(n3 == 2)
    {
        int i3;
        cout << "Enter ID of product: ";
        cin >> i3;
        c.cart.remove_item(i3);
        cout << "Item has been removed" << endl;
    }
    if(n3 == 3)
        c.cart.print(s.returnRefProd());
    if(n3 == 4)
    {
        c.cart.reset();
        cout << "Cart has been reseted" << endl;
    }
    if(n3 == 5)
        cout << "The total cart price is: " << c.cart.get_total_price(s.returnRefProd()) << endl;
    if(n3 == 6)
    {
        system("clear");
        mainPannel(s);
    }

}
