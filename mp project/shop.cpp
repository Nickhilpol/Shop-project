#include<iostream>
#include<mysql.h>
#include<mysqld_error.h>
#include<string.h>
#include<iomanip>
#include<sstream>
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<ctime>
#include<unistd.h>



using namespace std;

MYSQL* conn;
MYSQL_RES *res_set;
MYSQL_ROW row;
stringstream ss;
const char *q;
string query;

time_t now = time(0);
    char *dt = ctime(&now);
typedef struct 
{
	int date;
	int month;
	int yearl;
}date;

class welcome{
	public:
		void home_menu();
		void usr_home();
};
class admin
{
 	 int id;
	 string username;
 	string password;
 public :
  void login();
  void registeration();
  void recover();
};

class user
{
	int id;
	string username;
	string password;
 public:
 	void login();
 	void regster();
};

class main{
 public:
 void main_menu();
};

class usrmain{
public:
void usrmain_menu();
};

class usrdet{
 int id;
 string fname;
 string lname;
 string phone;
 int Invoice_id;
	string addr_line1;
	string addr_line2;
	string addr_city;
	string addr_state;
public:
	void add_usr();
	void show_usr();
	void generate_bill();
	void showbills();
};

class menu
{
	public:
	void product_menu();
	void supplier_menu();
	void employee_menu();
	void customer_menu();
};
class products
{
	public:
    int prod_id;
    string name;
    string manuf;
    float price;
    int qty;
public:
     void add();
     void update_price();
     void search();
     void update();
     void display();  
};

class suppliers
{
	int sup_id;				//Primary Key
	string name;
	string phn;
	string addr_line1;
	string addr_line2;
	string addr_city;
	string addr_state;
public:
	void add_sup();
	void remove_supplier();
	void search_id();
};

class purchases
{
	int ord_id;			//Primary Key
	int prod_id;		//FK ref (books)
	int sup_id;			//FK ref (suppliers)
	int qty;
	date dt_ordered;
	int eta;
	char received;		// Check(T or C or F) def (F)
	int inv;
public:
	void new_ord();
	//void view();
	void mar_cancel();
	void mark_reciv();
};

class employees
{
	int emp_id;				//Primary Key
	string fname;
	string lname;
	string addr_line1;
	string addr_line2;
	string addr_city;
	string addr_state;
	string phone;
	date date_of_joining;
	long int salary;
	string mgr_status;	//check(T or F) def f
public:
	void add_emp();
	void search_emp();
	void assign_mgr_stat();
	void display();
	void update_sal();
};

class customers
{
    int cust_id;				//Primary Key
	string fname;
	string lname;
	string addr_line1;
	string addr_line2;
	string addr_city;
	string addr_state;
	string phone;
	date beg_date;
	date end_date;
	string valid;
public:
	void add_cust();
	void del_cust();
	void refresh();
	void search_cust();
	void display_cust();
};

class sales
{
	int invoice_id;		//Primary key
 	int cust_id;		//FK ref member(id)
	int prod_id;		//FK ref books(id)
	int qty;
	char amount[20];
	date date_s;
public:
	void add();
	void find_total_sales();
};

void products::add()
{
	int choice;
	bool IsOpen = true;
		while (IsOpen)
			{
				
				
				cout << "Enter the Name of the product : ";
					cin >> ws;
	                getline(cin,name);
				
				cout << "price: ";
				cin >> price;
	               

				
				cout << "Enter the name of manufacturer : ";
					cin >> ws;
	                getline(cin,manuf);
				
				cout << "Quantity: ";
				cin >> qty;
				
				
				cout << endl;
				
				ss.str("");
				ss << "INSERT INTO products(name,price,manuf,qty)values('" << name << "'," << price << ",'" << manuf << "'," << qty << ")";
				query = ss.str();
				q = query.c_str();
				 mysql_query(conn,q);
				res_set = mysql_store_result(conn);
				if((res_set)==0)
				{
					cout << endl << "Data inserted successfully."<< endl;
					
				}
				else
				{
					cout << endl << "Data not inserted." << endl;
					
					
		        }
				
				
				cout << endl << "Another?" << endl;
				cout << "[1]: Yes" << endl;
				cout << "[0]: No"  << endl;
				cout << "choice: ";
				cin >> choice; 
				cin.ignore(100,'\n');
				
				if(choice == 0)
				{
					IsOpen = false;
				}
				cout << endl; 
			}
}

void products :: update()
{
	char choice;
	cout << "Enter the id of the product for update in price : ";
	cin >> prod_id;
	ss.str("");
	ss << "Select name,price,manuf from products where id = " << prod_id << ";";
	query = ss.str();
	q = query.c_str();
	mysql_query(conn,q);
    res_set = mysql_store_result(conn);
    if((row = mysql_fetch_row(res_set)) != NULL)
    {
        cout << "The Name of the Product is : " << row[1] << endl ;
        cout << "The current price of the product is : " << row[2] << endl ;
        cout << "Do you Want to Update the Price [y/n] : " ;
    	cin >> choice;
		if (choice == 121 || choice == 89)
		{
			
			cout << "Enter the Name of the product : ";
					cin >> ws;
	                getline(cin,name);
				
				cout << "price: ";
				cin >> price;

				
				cout << "Enter the name of manufacturer : ";
					cin >> ws;
	                getline(cin,manuf);
				
				cout << "Quantity: ";
				cin >> qty;
			ss.str("");
			ss << "Update products SET name = '"<< name << "'+ price = "<<  price << "+ manuf = '"<< manuf << "'+ qty = "<< qty << " + where id = " << prod_id << ";";
			res_set = mysql_store_result(conn);
			if (!(res_set))
        		cout << endl << endl << "Product Price Updated Successfully" << endl << endl << endl;
    		else
        		cout << endl << endl << "Entry ERROR !" << endl << "Contact Technical Team " << endl << endl << endl;
		}
		else
		{
			cout << "No changes Made!!";
		}
	}
	else
	{
		cout << "No Book found!!!";
	}
	
}

void products::search()
{
	cout << "Enter product id for details : ";
	cin >> prod_id;
    ss.str("");
    ss << "Select * from products where id = " << prod_id << ";";
    query = ss.str();
    q = query.c_str();
    mysql_query(conn,q);
    res_set = mysql_store_result(conn);
    if((row = mysql_fetch_row(res_set)) != NULL)
    {
		cout << "The Details of Product Id : " << row[0] << endl;
        cout << "The Name of the product is : " << row[1] << endl ;
		cout << "THE Price of the product " << row[1] << " is " << row[2] << endl;
        cout << "The Manufacturer of the product is : " << row[3] << endl ;
		cout << "The Quantity of product is " << row[4] << endl;
	}
	else
	{
		cout << "No record Found" << endl;
	}
}

void products::update_price()
{
    char choice;
    cout << "Enter the id of the product for update in price : ";
    cin >> prod_id;
    ss.str("");
    ss << "Select name,price from books where id = " << prod_id << ";";
    query = ss.str();
    q = query.c_str();
    mysql_query(conn,q);
    res_set = mysql_store_result(conn);
    if((row = mysql_fetch_row(res_set)) != NULL)
    {
        cout << "The Name of the product is : " << row[1] << endl ;
        cout << "The current price of the product is : " << row[2] << endl ;
        cout << "Do you Want to Update the Price [y/n] : " ;
    	cin >> choice;
		if (choice == 121 || choice == 89)
		{
			cout << "Enter the new price : ";
			cin >> price;
			ss.str("");
			ss << "Update products set price = " << price << " where id = " << prod_id << ";";
			res_set = mysql_store_result(conn);
			if (!(res_set))
        		cout << endl << endl << "Product Price Updated Successfully" << endl << endl << endl;
    		else
        		cout << endl << endl << "Entry ERROR !" << endl << "Contact Technical Team " << endl << endl << endl;
		}
		else
		{
			cout << "No changes Made!!";
		}
	}
	else
	{
		cout << "No Product found!!!";
	}
}

void products::display()
{
	int i = 0;
	query = "Select * from products;";
	q = query.c_str();
	mysql_query(conn,q);
	res_set = mysql_store_result(conn);
	while((row = mysql_fetch_row(res_set)) != NULL)
	{
		cout << "Name for products " << ++i << " : " << row[1] << endl;
		cout << "Price : " << row[2] << endl;
		cout << "Name of Manufacturer : " << row[3] << endl;
		cout << "Quantity : " << row[4] << endl;
		cout << endl << endl << endl << endl ;
	}
}

// class of suppliers.

void suppliers::add_sup()
{
	fflush(stdin);
	//cout << "Enter Supplier Id : ";
	//cin >> sup_id;
	cout << "Enter the Supplier Name : ";
		cin >> ws;
	getline(cin,name);
	cout << "Enter Phone no. : ";
	cin >>phn;
	cout << "Enter the address line1 : ";
		cin >> ws;
	getline(cin,addr_line1);
	cout << "Enter the address line2 : ";
		cin >> ws;
	getline(cin,addr_line2);
	
	cout << "Enter the address city : ";
		cin >> ws;
	getline(cin,addr_city);
	cout << "Enter State : ";
		cin >> ws;
	getline(cin,addr_state);
	ss.str("");
	ss << "INSERT INTO suppliers(name,phone,addr1,addr2,addr_city,addr_state) values('" << name << "','" << phn << "','" << addr_line1 << "','" << addr_line2 << "','" << addr_city << "','" << addr_state << "');";
	query = ss.str();
	q = query.c_str();
	mysql_query(conn,q);
	res_set = mysql_store_result(conn);
	if (!(res_set))
        cout << endl << endl << "Supplier Record Inserted Successfully" << endl << endl << endl;
    else
        cout << endl << endl << "Entry ERROR !" << endl << "Contact Technical Team " << endl << endl << endl;
}

void suppliers::remove_supplier()
{
	cout << "Enter the supplier id to remove the Supplier : ";
	cin >>  sup_id;
	ss.str("");
	ss << "Delete from suppliey where id = " << sup_id << ";";
	query = ss.str();
	q = query.c_str();
	mysql_query(conn,q);
	cout << "Supplier Removed.";
}
void suppliers::search_id()
{
	cout << "Enter the supplier id to find the Supplier details : ";
	cin >>  sup_id;
	ss.str("");
	ss << "Select * from suppliey where id = " << sup_id << ";";
	query = ss.str();
	q = query.c_str();
	mysql_query(conn,q);
	res_set = mysql_store_result(conn);
	if((row = mysql_fetch_row(res_set)) != NULL)
	{
		cout << "Details of Supplier Id : " << row[0] << endl;
		cout << "Name : " << row[1] << endl;
		cout << "Phone no. : " << row[2] << endl;
		cout << "Address Line 1 : " << row[3] << endl;
		cout << "Address Line 2 : " << row[4] << endl;
		cout << "City : " << row[5] << endl;
		cout << "State : " << row[6] << endl;
	}
	else
	{
		cout << "No Supplier Found!!";
	}
}

void purchases::new_ord()
{
	cout << "Enter the Product Id : ";
	cin >> prod_id;
	cout << "Enter Supplier Id : ";
	cin >> sup_id;
	cout << "Enter the Quantity : ";
	cin >> qty;
	cout << "Estimated expected Delivery (in days) : ";
	cin >> eta;
	ss.str("");
	ss << "Insert into purchases (prod_id,sup_id,qty,dt_ord,eta) values ( " << prod_id << "," << sup_id << "," << qty << ",curdate(),Date_add(curdate(), INTERVAL " << eta << " DAY)" << ";";
	query = ss.str();
	q = query.c_str();
	mysql_query(conn,q);
	cout << "New order Added!!";
}	

void purchases::mark_reciv()
{
	cout << "Enter the order id for order recieved : ";
	cin >> ord_id;
	ss.str("");
	ss << "Update puchases set recieved = 'T' where ord_id = " << ord_id << ";";
	query = ss.str();
	q = query.c_str();
	mysql_query(conn,q);
	cout << "Recieved Marked successfully";
}

void purchases::mar_cancel()
{
	cout << "Enter the order id for order cancelled : ";
	cin >> ord_id;
	ss.str("");
	ss << "Update puchases set recieved = 'C' where ord_id = " << ord_id << ";";
	query = ss.str();
	q = query.c_str();
	mysql_query(conn,q);
	cout << "Cancelled Marked successfully";
}

// EMPLOYEE CLASS	
void employees::add_emp()
{
	
	cout << "Enter The details of new employees!!"<<endl<<endl;
	
	cout << "Enter the First name : ";
		cin >> ws;
	getline(cin,fname);
	cout << "Enter the Last name : ";
		cin >> ws;
	getline(cin,lname);
	cout << "Enter the Address line1 : ";
		cin >> ws;
	getline(cin,addr_line1);
	cout << "Enter the Address line2 : ";
		cin >> ws;
	getline(cin,addr_line2);
	cout << "Enter the Address City : ";
		cin >> ws;
	getline(cin,addr_city);
	cout << "Enter State : ";
		cin >> ws;
	getline(cin,addr_state);
	cout << "Enter phone no : ";
	cin >> phone;
	cout << "Enter the salary : ";
	cin >> salary;
	ss.str("");
	ss << "Insert into employees (fname,lname,addr1,addr2,addr_city,addr_state,phone_no,doj,salary) values ('" << fname << "','" << lname << "','" << addr_line1 << "','" << addr_line2 << "','" << addr_city << "','" << addr_state << "','" << phone << "',curdate()," << salary << ");";
	query = ss.str();
	q = query.c_str();
	mysql_query(conn,q);
	cout << "Employee Added successfully" << endl << endl <<"Employee Id : " << row[0];
	cout << endl << endl << endl << endl;
}

void employees::search_emp()
{
	cout << "Enter the id for searching an employee : ";
	cin >> emp_id ;
	ss.str("");
	ss << "Select * from employees where Id  = " << emp_id << ";";
	query = ss.str();
	q = query.c_str();
	mysql_query(conn,q);
	res_set = mysql_store_result(conn);
	if ((row = mysql_fetch_row(res_set)) != NULL)
	{
		cout << "              Employees Details" << endl ;
		cout << "              Employee Id : " << row[0] << endl;
		cout << "              Name : " << row[1] << setw(5)<<" "<< row[2] << endl;
		cout << "              Address : " << row[3] << setw(5) <<""<< row[4] << setw(5)<<""<< row[5] << endl;
		cout << "              State : " << row[6] << endl;
		cout << "              Contact no. : " << row[7] << endl;
		cout << "              Date of Joining" << row[8] << endl;
		cout << "              Salary : " << row[9] << endl << endl << endl;
	}
	else
	{
		cout << "     No Employee Found!!" << endl << endl << endl;
	}
}


void employees::display()
{
	int i = 0;
	query = "Select * from employees;";
	q = query.c_str();
	mysql_query(conn,q);
	res_set = mysql_store_result(conn);
	if((row = mysql_fetch_row(res_set)) != NULL)
    {
       do
       {
    	cout << "              Employees Details of Emp no." << ++i << endl ;
    	cout << "              Employee Id : " << row[0] << endl;
        cout << "              Name : " << row[1] << setw(5)<<" "<< row[2] << endl;
		cout << "              Address : " << setw(5) <<""<< row[3] << setw(5) <<""<< row[4] << setw(5)<<""<< row[5] << endl;
		cout << "              State : " << row[6] << endl;
		cout << "              Contact no. : " << row[7] << endl;
		cout << "              Date of Joining" << row[8] << endl;
		cout << "              Salary : " << row[9] << endl << endl << endl;
		cout << endl << endl << endl << endl;
       }while((row = mysql_fetch_row(res_set)) != NULL);
    }
	else
	{
		cout << "Employees Not found!" << endl;
	}
}

void employees::update_sal()
{
	cout << "Enter the id to update the salary of an employee : ";
	cin >> emp_id ;
	cout << "Enter the updated salary : ";
	cin >> salary;
	ss.str("");
	ss << "Update employees set salary = " << salary << " where id  = " << emp_id << ";";
	query = ss.str();
	q = query.c_str();
	mysql_query(conn,q);
	cout << endl << endl << endl << endl;
	cout << "Salary update Successfully";
	cout << endl << endl << endl << endl;
}

// class of customers
void customers::add_cust()
{
	cout << "Enter the first name of the customer : ";
	cin >> fname;
	cout << "Enter the last name of the customer : ";
	cin >> lname;
	cout << "Enter phone no. : ";
	cin >> phone;
	cout << "Enter address line1 : " << endl;
		cin >> ws;
	getline(cin,addr_line1);
	cout << "Enter address line1 : " << endl;
		cin >> ws;
	getline(cin,addr_line2);
	cout << "Enter address city : " << endl;
		cin >> ws;
	getline(cin,addr_city);
	cout << "Enter the name of the state : " ;
		cin >> ws;
	getline(cin,addr_state);
	ss.str("");
	ss << "insert into customers(fname,lname,addr1,addr2,addr_city,addr_state,beg_date,end_date,phone_no) values ('" << fname << "','" << lname << "','" << addr_line1 << "','" << addr_line2 << "','" << addr_city << "','" << addr_state << "',curdate(),Date_add(curdate(), INTERVAL 1 YEAR),'" << phone << "');";
	query = ss.str();
	q = query.c_str();
	mysql_query(conn,q);
	// fetching member id...
	ss.str("");
	ss << "Select id from customers where phone_no = " << phone << ";";
	query = ss.str();
	q = query.c_str();
	mysql_query(conn,q);
	res_set = mysql_store_result(conn);
	row = mysql_fetch_row(res_set);
	cout << endl << endl << endl << endl;
	cout << "Customer Added successfully" << endl << endl <<"Customer Id : " << row[0];
	cout << endl << endl << endl << endl;
}

void customers::refresh()
{
	query = "Update members set valid = 'invalid' where end_date <= curdate();";
	q = query.c_str();
	mysql_query(conn,q);
}

void customers::search_cust()
{
	cout << "Enter Customer id : ";
	cin >> cust_id;
	ss.str("");
	ss << "Select * from customers where id  = " << cust_id << ";";
	query = ss.str();
	q = query.c_str();
	mysql_query(conn,q);
	res_set = mysql_store_result(conn);
	if ((row = mysql_fetch_row(res_set)) != NULL)
	{
		cout << "Customer Details" << endl ;
		cout << "Name : " << row[1] << setw(5) <<""<< row[2] << endl;
		cout << "Address : " << setw(5) <<""<< row[3] << setw(5) <<""<< row[4] << setw(5)<<""<< row[5] << endl;
		cout << "State : " << row[6] << endl;
		cout << "Contact no. : " << row[9] << endl;
		cout << "Membership begin date : " << row[7] << endl;
		cout << "Membership end date  : " << row[8] << endl;
		//cout << "Membership Status : " << row[9] << endl << endl << endl;
	}
	else
	{
		cout << "No Member Found!!" << endl << endl << endl;
	}
}

void customers::display_cust()
{
	int i = 0;
	query = "Select * from customers;";
	q = query.c_str();
	mysql_query(conn,q);
	res_set = mysql_store_result(conn);
	if((row = mysql_fetch_row(res_set)) != NULL)
    {
       do
       {
    	cout << "         Customer Details of Customer no." << ++i << endl ;
        cout << "Name : " << row[1] << setw(5) <<""<< row[2] << endl;
		cout << "Address : " << setw(5) <<""<< row[3] << setw(5) <<""<< row[4] << setw(5)<<""<< row[5] << endl;
		cout << "State : " << row[6] << endl;
		cout << "Contact no. : " << row[9] << endl;
		cout << "Membership begin date : " << row[7] << endl;
		cout << "Membership end date  : " << row[8] << endl;
		cout << endl << endl << endl << endl;
       }while((row = mysql_fetch_row(res_set)) != NULL);
    }
	else
	{
		cout << "         Customer Not found!" << endl;
	}
}
void customers::del_cust(){
	cout << "        Enter the Customer id to remove the Customer : ";
	cin >>  cust_id;
	ss.str("");
	ss << "          Delete from customers where id = " << cust_id << ";";
	query = ss.str();
	q = query.c_str();
	mysql_query(conn,q);
	cout << "               Customer Removed.";
}


void sales::add()
{
	cout << "Enter Customer id :";
	cin >> cust_id;
	cout << "Enter the product id : ";
	cin  >> prod_id;
	cout << "Enter the quantity : ";
	cin  >> qty;
	ss.str("");
	ss << "select price*" << qty << " from products where id = " << prod_id << ";";
	query = ss.str();
	q = query.c_str();
	mysql_query(conn,q);
	res_set = mysql_store_result(conn);
	if ((row = mysql_fetch_row(res_set)) != NULL)
	{
		cout << "The bill amount : " << row[0] << endl << endl;
	//	amount = (int) row[0];
	}
	else
	{
		cout << "Product Id invalid!!" << endl;
		getch();
		return;
	}
	ss.str("");
	ss << "insert into sales(mem_id,book_id,qty,amt,sales_date) values (" << cust_id << "," << prod_id << "," << qty << "," << amount << ",curdate());";
	query = ss.str();
	q = query.c_str();
	mysql_query(conn,q);
	// fetching invoice id...
	ss.str("");
	ss << "select inv_id from sales where mem_id = " << cust_id << " AND prod_id = " << prod_id << " AND qty = " << qty << " AND sales_date = curdate();";
	query = ss.str();
	q = query.c_str();
	mysql_query(conn,q);
	res_set = mysql_store_result(conn);
	if((row = mysql_fetch_row(res_set)) != NULL)
	{
		cout << "The Invoice id for the bill is " << row[0] << endl << endl << endl;
	}
	else
	{
		cout << "The entered details maybe wrong." << endl << "Please Recheck and Enter again" << endl << endl << endl;
	}
}


void sales::find_total_sales()
{
	query = "select sum(amt) from sales where year(sales_date) = year(curdate());";
	q = query.c_str();
	mysql_query(conn,q);
	res_set = mysql_store_result(conn);
	if((row = mysql_fetch_row(res_set)) != NULL)
	{
		cout << "Total sales this year : " << row[0] << endl << endl << endl << endl;
	}
}

// Admin login page
/*void admin::registeration(){
	welcome w;
	cout << "                                                                  DATE and TIME : " << dt <<endl; 
	
	cout << "                               Enter Username : ";
	cin >> username;
	
	cout << "                               Enter Password : ";
	cin >> password;
     	ss.str("");
				ss << "INSERT INTO logindetails(USERNAME,PASSWORD)values('" << username << "','" << password << "')";
				query = ss.str();
				q = query.c_str();
				 mysql_query(conn,q);
				res_set = mysql_store_result(conn);
				if((res_set)==0)
				{
					cout << endl << "Registered successfully."<< endl;
					sleep(4);
					system("cls");
					w.home_menu();
				}
				else
				{
					cout << endl << "Error: Try again...." << endl;
					sleep(4);
					exit(1);
					
		        }
		        //welcome_menu();
    }*/

void admin::login(){
	char another;
	main me;
	cout << "                                                           DATE and TIME : " << dt <<endl; 
	cout <<" ********************************************************************************************************"<<endl;
	
	cout << "                               Enter Username : ";
	cin >> username;
	cout << "                               Enter Password : ";
	cin >> password;
	cout <<"**********************************************************************************************************"<<endl;
	ss.str("");
	ss << "Select * from logindetails where USERNAME  = '" << username << "' AND PASSWORD = '" << password << "';";
	query = ss.str();
	q = query.c_str();
	mysql_query(conn,q);
	res_set = mysql_store_result(conn);
	if ((row = mysql_fetch_row(res_set)) != NULL)
	{
		cout<<"                                Succesfully Logged In..."<<endl<<endl;
		                  sleep(4);
						  system("cls");
				          me.main_menu();
	}
	else
	{
		cout<<"Incorrect Username Or Password!"<<endl;
		
		
		
	}

	
}

void welcome::home_menu()
{
	admin a;
	char c;
 cout<<"                                                                 DATE and TIME : " << dt <<endl;                         
 //cout<<"                                +------------------+       "<<endl;
 //cout<<"                                |    1: Register   |          "<<endl;
// cout<<"                                +------------------+        "<<endl;
 cout<<"                                +------------------+       "<<endl;
 cout<<"                                |      Login       |        "<<endl;
 cout<<"                                +------------------+      "<<endl<<endl<<endl;
 cout<<"                                   Enter [Y/N]: ";
 cin>>c;
  switch(c)
  {
  	case 'Y': 
  	      system("cls");
  	      a.login();
  	      break;
    case 'y':
    	  system("cls");
    	  a.login();
    	  break;
     case 'N':
    	  system("cls");
    	 // a.login();
    	 exit(1);
    	  break;	  
    default : 
          system("cls");
          cout<< "ERROR !! Invalid choice !! ";
          break;
  }
	
}

void main:: main_menu()
{
	menu m;
	int c;
	cout << "           *****************************************************************************" << endl;
	cout << "                         SHOP MANGEMENT SYSTEM           DATE and TIME : " << dt <<endl; 
	cout << "           *****************************************************************************" << endl;
	cout << "                   1. Products Details" << endl;
	cout << "                   2. Suppliers Details" << endl;
	cout << "                   3. Purchase Details" << endl;
	cout << "                   4. EMPLOYEES DETAILS" << endl;
	cout << "                   5. CUSTOMER DETAILS" << endl;
	cout << "                   6. SALES" << endl;
	cout << "                   7. EXIT" << endl << endl << endl;
	cout << "                      Enter Your Choice : ";
	cin >> c;
	switch (c)
	{
		case 1:
			system("cls");
			m.product_menu();
			getch();
			break;
		case 2:
			system("cls");
			m.supplier_menu();
			getch();
			break;
		case 3:
			system("cls");
			//purchase_menu();
			getch();
			break;
		case 4:
			system("cls");
			m.employee_menu();
			getch();
			break;
		case 5:
			system("cls");
			m.customer_menu();
			getch();
			break;
		case 6:
			system("cls");
			//sales_menu();
			getch();
			break;
		case 7:
			exit(1);
		default:
			system("cls");
			cout << "Wrong Input" << endl << endl << "Invalid input";
			getch();
			break;
	}
	return;
}

void menu :: product_menu()
{
	int c;
	products p;
	cout << "        *******************************************************************************" << endl;
	cout << "                       PRODUCT DETAILS        DATE and TIME :  " << dt <<endl;                     
	cout << "        *******************************************************************************" << endl;
	cout << "                  1. Add a new product" << endl;
	cout << "                  2. Update product price" << endl;
	cout << "                  3. Search a product" << endl;
	cout << "                  4. Update product details" << endl;
	cout << "                  5. Display all products" << endl;
	cout << "                  6. Return to Main Menu" << endl << endl << endl;
	cout << "                      Enter Your Choice : ";
	cin >> c;
	switch (c)
	{
		case 1:
			p.add();
			break;
		case 2:
			p.update_price();
			break;
		case 3:
			p.search();
			break;
		case 4:
			//p.update();
			break;
		case 5:
			p.display();
			break;
		case 6:
			return;
			break;
		default:
			cout << "Wrong Input" << endl << "Invalid input";
			break;
	}
	return;
}

// supp menu

void menu :: supplier_menu()
{
	int c;
	suppliers s;
	cout << "        *******************************************************************************" << endl;
	cout << "                         SUPPLIER MENU                 DATE and TIME : " << dt <<endl;  
	cout << "        *******************************************************************************" << endl;
	cout << "                1. Add a new supplier." << endl;
	cout << "                2. Remove a supplier." << endl;
	cout << "                3. Search a supplier." << endl;
	cout << "                4. Return T0 Main Menu" << endl << endl << endl;
	cout << "                    Enter Your Choice : ";
	cin >> c;
	switch (c)
	{
		case 1:
			s.add_sup();
			break;
			//getch();
		case 2:
		    s.remove_supplier();
			break;
		case 3:
			s.search_id();
			break;
			//getch();
		case 4:
			return;
		default:
			cout << "Wrong Input" << endl << "Invalid input";
			break;
	}
}


// purchase menu

void pur_menu()
{
	int c;
	purchases p;
	cout << "*************************************************" << endl;
	cout << "                PURCHASES MENU" << endl;
	cout << "*************************************************" << endl;
	cout << "   1. New Order" << endl;
	cout << "   2. View All" << endl;
	cout << "   3. Cancel Order" << endl;
	cout << "   4. Recieved Order" << endl;
	cout << "   5. RETURN TO MAIN MENU" << endl << endl << endl;
	cout << "Enter Your Choice : ";
	cin >> c;
	switch (c)
	{
		case 1:
			p.new_ord();
			break;
		case 2:
			//p.view();
			break;
		case 3:
			p.mar_cancel();
			break;
		case 4:
			p.mark_reciv();
			break;
		case 5:
			return;
		default:
			cout << "Wrong Input" << endl << "Invalid input";
			break;
	}
}

// emp_menu

void menu :: employee_menu()
{
	int c;
	employees e;
	cout << "         ***********************************************************************************" << endl;
	cout << "                         EMPLOYEE MENU           DATE and TIME : " << dt <<endl;      
	cout << "         ***********************************************************************************" << endl;
	cout << "                  1. Add a New Employee" << endl;
	cout << "                  2. Search a Employee" << endl;
	cout << "                  3. View All Emloyee " << endl;
	cout << "                  4. Update Salary" << endl;
	cout << "                  5. RETURN TO MAIN MENU" << endl << endl << endl;
	cout << "                      Enter Your Choice : ";
	cin >> c;
	switch (c)
	{
		case 1:
			system("cls");
			e.add_emp();
			//system("cls");
			break;
		case 2:
				system("cls");
			e.search_emp();
			break;
		case 3:
				system("cls");
			e.display();
			break;
		case 4:
			//e.update_sal();
			break;
		case 5:
			return;
		default:
			cout << "Wrong Input" << endl << "Invalid input";
			break;
	}
}

void menu::customer_menu()
{
	int c;
	customers cs;
	cs.refresh();
	cout << "         ************************************************************************************************" << endl;
	cout << "                                    CUSTOMERS MENU           DATE and TIME : " << dt <<endl;        
	cout << "         ************************************************************************************************" << endl;
	cout << "                             1. Add Customer" << endl;
	cout << "                             2. Search Customer" << endl;
	cout << "                             3. Display All Customer" << endl;
	cout << "                             4. Delete Customer" << endl;
	cout << "                             5. RETURN TO MAIN MENU" << endl << endl << endl;
	cout << "                                 Enter Your Choice : ";
	cin >> c;
	switch (c)
	{
		case 1:
			cs.add_cust();
			break;
		case 2:
			cs.search_cust();
			break;
		case 3:
			cs.display_cust();
			break;
		case 4:
			cs.del_cust();
			break;
		case 5:
			return;
		default:
			cout << "Wrong Input" << endl << "Invalid input";
			break;
	}
}


//CUSTOMER PORTAL

void user::regster()
{
	cout<<endl<<endl<<endl;
	welcome w;
	cout <<"        --------------------------------------------------------------------------------"<<endl;
	cout << "                               Enter Username : ";
	cin >> username;
	
	
	cout << "                               Enter Password : ";
	cin >> password;
	cout <<"       ---------------------------------------------------------------------------------"<<endl;
	
     	ss.str("");
				ss << "INSERT INTO loginUSR(USERNAME,PASSWORD)values('" << username << "','" << password << "')";
				query = ss.str();
				q = query.c_str();
				 mysql_query(conn,q);
				res_set = mysql_store_result(conn);
				if((res_set)==0)
				{
					cout << endl << "Registered successfully....";
					//sleep(4);
					system("cls");
					w.usr_home();
				}
				else
				{
					cout << endl << "Error: Try again...." << endl;
					sleep(4);
					exit(1);
					
		        }
		        //welcome_menu();
    }

void user::login()
{
	char another;
	user u;
	usrmain um;
	
	cout << "                            Enter Username : ";
	cin >> username;
	
	
	cout << "                            Enter Password : ";
	cin >> password;
	ss.str("");
	ss << "Select * from loginUSR where USERNAME  = '" << username << "' AND PASSWORD = '" << password << "';";
	query = ss.str();
	q = query.c_str();
	mysql_query(conn,q);
	res_set = mysql_store_result(conn);
	if ((row = mysql_fetch_row(res_set)) != NULL)
	{
		
		cout<<"                                Succesfully Logged In!!..."<<endl<<endl;
		
		sleep(2);
		   system("cls");
				um.usrmain_menu();
	}
	else
	{
		cout << endl<< endl;
		cout<<"                             Incorrect Username Or Password!"<<endl;
		sleep(4);
		system("cls");
		cout <<"Forgot password[Y/N]: ";
		cin >> another;
		
if(another == 'Y' || another =='y'){
			ss.str("");
	ss << "Select * from loginUSR where USERNAME  = '" << username << "';";
	query = ss.str();
	q = query.c_str();
	mysql_query(conn,q);
	res_set = mysql_store_result(conn);
	if ((row = mysql_fetch_row(res_set)) != NULL){
			cout << "Username: " << row[1]<< endl;
			cout << "Password: "<< row[2] << endl;
			sleep(3);
			system("cls");
			u.login();	
		}
		else{
			system("cls");
		cout << "No such user exists!!!"<<endl;
		sleep(3);
		exit(1);
	}
 }

 }
}

void usrdet::add_usr()
{
   	cout << "Enter the first name of the customer : ";
   	cin >> ws;
	getline(cin,fname);
		cout << "Enter the last name of the customer : ";
   	cin >> ws;
	getline(cin,lname);
	cout << "Enter phone no. : ";
	cin >> phone;
	cout << "Enter address line1 : " << endl;
	cin >> ws;
	getline(cin,addr_line1);
	cout << "Enter address line2 : " << endl;
		cin >> ws;
	getline(cin,addr_line2);
	cout << "Enter address city : " << endl;
		cin >> ws;
	getline(cin,addr_city);
	cout << "Enter the name of the state : " ;
	cin >> ws;
	getline(cin,addr_state);
	ss.str("");
	ss << "insert into customers(fname,lname,addr1,addr2,addr_city,addr_state,beg_date,end_date,phone_no) values ('" << fname << "','" << lname << "','" << addr_line1 << "','" << addr_line2 << "','" << addr_city << "','" << addr_state << "',curdate(),Date_add(curdate(), INTERVAL 1 YEAR),'" << phone << "');";
	query = ss.str();
	q = query.c_str();
	mysql_query(conn,q);
	// fetching member id...
	ss.str("");
	ss << "Select id from customers where phone_no = " << phone << ";";
	query = ss.str();
	q = query.c_str();
	mysql_query(conn,q);
	res_set = mysql_store_result(conn);
	row = mysql_fetch_row(res_set);
	cout << endl << endl << endl << endl;
	cout << "Customer Added successfully" << endl << endl <<"Customer Id : " << row[0];
	cout << endl << endl << endl << endl;
}

void usrdet::show_usr()
{
	cout << "Enter Customer id : ";
	cin >> id;
	ss.str("");
	ss << "Select * from customers where id  = " << id << ";";
	query = ss.str();
	q = query.c_str();
	mysql_query(conn,q);
	res_set = mysql_store_result(conn);
	if ((row = mysql_fetch_row(res_set)) != NULL)
	{
		cout << "               Customer Details" << endl ;
	    cout << "               Name : " << row[1] << setw(2) <<""<< row[2] << endl;
		cout << "               Address : " <<  row[3] << setw(2) <<""<< row[4] << setw(2)<<""<< row[5] << endl;
		cout << "               State : " << row[6] << endl;
		cout << "               Contact no. : " << row[9] << endl;
		cout << "               Membership begin date : " << row[7] << endl;
		cout << "               Membership end date  : " << row[8] << endl;
		//cout << "               Membership Status : " << row[9] << endl << endl << endl;
	}
	else
	{
		cout << "               No Member Found!!" << endl << endl << endl;
	}
}
//Function to generate bill
void usrdet::generate_bill(){
	usrdet us;

    struct date
    {
        int day;
        int month;
        int year;
    };

    struct details
    {
        int id;
		string name;
        float price;
        string manuf;
        float qty;
         float amount[50];
    }item[50];
    int n,i;
    
    float total_bill = 0.00;
    float grandTotal;
	float discount = 0.00;
	const int ITEM_NAME_WIDTH = 30; 
                 const int ITEM_PRICE_WIDTH = 12; 
                 const int ITEM_QTY_WIDTH = 8; 
                 const int ITEM_TOTAL_WIDTH = 14; 
                 const int TOTAL_WIDTH = ITEM_NAME_WIDTH + ITEM_PRICE_WIDTH + ITEM_QTY_WIDTH + ITEM_TOTAL_WIDTH; 
    
    time_t now = time(0);
    char *dt = ctime(&now);
   
    cout << "Enter Customer id : ";
	cin >> id;
	cout << "Enter Customer First Name : ";
	cin >> fname;
	//cout << "Enter Customer last Name : ";
	//cin >> lname;
	cout << "Enter number of products : ";
    cin >> n;
    cout << "Enter Invoice_id: ";
    cin >> Invoice_id;
    
    cout << endl << endl;
    for(i=0;i<n;i++)
    {  
        cout << "Product id " << i + 1 << ": ";
        cin >> item[i].id;
        cout << "Product name " << i + 1 << ": ";
        cin >> ws;
		getline(cin,item[i].name);
        cout << "Product price " << i + 1 << ": ";
        cin >> item[i].price;
        fflush(stdin);
        cout << "Quantity " << i + 1 << ": ";
        cin >> item[i].qty;
        item[i].amount[i]= item[i].price*item[i].qty;
        total_bill += item[i].amount[i];
        ss.str("");
    ss <<" insert into bill(Invoice_id,Prod_id,Prod_name,Qty,Price,Amount) values("<< Invoice_id <<","<< item[i].id <<",'"<< item[i].name<<"',"<<item[i].qty<<","<< item[i].price<<","<< item[i].amount[i] <<")";
	query = ss.str();
	q = query.c_str();
	mysql_query(conn,q);
    }
        
     if (total_bill >= 2500)
    {
        discount = (25 * total_bill) / 100;
        grandTotal = total_bill - discount;
         ss.str("");
	ss << "Insert into billdetails(Invoice_id,Cust_id,Cust_name,Prod_no,Total_Bill,Discount,GrandTotal,Bill_date) values ("<< Invoice_id <<","<< id << ",'"<< fname <<"'," << n << "," << total_bill << "," << discount << "," << grandTotal << ",curdate())";
	query = ss.str();
	q = query.c_str();
	mysql_query(conn,q);
	
        cout<<"\nBill is calculated successfully\n";
        
    }
    else if (total_bill >= 1000 && total_bill < 2500)
    {
    	cout << "Total_bill: " << total_bill << endl;
        discount = (10 * total_bill) / 100;
        grandTotal = total_bill - discount;
         ss.str("");
	ss << "Insert into billdetails(Invoice_id,Cust_id,Cust_name,Prod_no,Total_Bill,Discount,GrandTotal,Bill_date) values ("<< Invoice_id <<","<< id << ",'"<< fname <<"'," << n << "," << total_bill << "," << discount << "," << grandTotal << ",curdate())";
	query = ss.str();
	q = query.c_str();
	mysql_query(conn,q);
	
        cout<<"\nBill is calculated successfully\n";
        
    }
    else if (total_bill >= 500 && total_bill < 1000)
    {
    	cout << "Total_bill: " << total_bill << endl;
        discount = (5 * total_bill) / 100;
        grandTotal = total_bill - discount;
         ss.str("");
	ss << "Insert into billdetails(Invoice_id,Cust_id,Cust_name,Prod_no,Total_Bill,Discount,GrandTotal,Bill_date) values ("<< Invoice_id <<","<< id << ",'"<< fname <<"'," << n << "," << total_bill << "," << discount << "," << grandTotal << ",curdate())";
	query = ss.str();
	q = query.c_str();
	mysql_query(conn,q);
	
        cout<<"\nBill is calculated successfully\n";
        
    }
    else{
    	cout << "Total_bill: " << total_bill << endl;
    discount = 0;
    grandTotal = total_bill;
     ss.str("");
	ss << "Insert into billdetails(Invoice_id,Cust_id,Cust_name,Prod_no,Total_Bill,Discount,GrandTotal,Bill_date) values ("<< Invoice_id <<"," << id << ",'"<< fname <<"'," << n << "," << total_bill << "," << discount << "," << grandTotal << ",curdate())";
	query = ss.str();
	q = query.c_str();
	mysql_query(conn,q);
	
    cout<<"\nBill is calculated successfully\n";
    }
    
	ss.str("");
	ss << "Select * from customers where id  = " << id << ";";
	query = ss.str();
	q = query.c_str();
	mysql_query(conn,q);
	res_set = mysql_store_result(conn);
if ((row = mysql_fetch_row(res_set)) != NULL)
{   
    system("cls");
    cout <<"Wait generating your bill..."<<endl<<endl<<endl;
    sleep(5);
cout <<       "   ____________________________________________________________________________________________________________________________________ "<<endl;
cout <<       "                                                     ******   Bill Invoice   ******                                                                     "<<endl;    
cout <<       "   _____________________________________________________________________________________________________________________________________"<<endl;
cout <<       "                                                            MY SHOPPEE                                                                             "<<endl;
cout <<       "                                                 Address:Bharati Vidyapeeth's College of Engineering,                                              "<<endl;
cout <<       "                                                              Karvir,Kolhapur.PIN-416013."<<endl;
cout <<       "                                                               GSTIN - 9876456798092345 "<< endl;                                                               
cout <<       "                                                             Mobile NO - 9876****** "<<endl;
cout <<       "  ______________________________________________________________________________________________________________________________________"<<endl;

cout <<       "    Invoice No :  "<< Invoice_id << setw(ITEM_NAME_WIDTH) << "                                                 DATE and TIME :    "<< dt << endl;
cout << endl;
cout <<       "     Customer Name : " << row[1] << setw(5)<<""<< row[2]<< endl;
cout <<       "     Address : " << row[3] <<setw(5)<< ""<< row[4] << endl; 
cout <<       "     City : " << row[5]  << setw(5)<< "State : " << row[6] << endl;
cout <<       "    Contact no. : " << row[9] << endl;
cout <<       "   ____________________________________________________________________________________________________________________________________ "<<endl;
cout << endl;
cout <<       "   -------------------------------------------------------------------------------------------------------------------------------------"<<endl;
cout << left << setw(ITEM_QTY_WIDTH)<< " "<< setw(ITEM_QTY_WIDTH) << "ID" << setw(ITEM_NAME_WIDTH) << "ITEM" << right << setw(ITEM_PRICE_WIDTH) << "PRICE" << setw(ITEM_QTY_WIDTH) << "QTY" << setw(ITEM_TOTAL_WIDTH) << "TOTAL" << endl; 
cout <<       "   -------------------------------------------------------------------------------------------------------------------------------------"<<endl;
for (i=0;i<n;i++) { 
cout <<  left << setw(ITEM_QTY_WIDTH) <<" "<< setw(ITEM_QTY_WIDTH) << item[i].id << setw(ITEM_NAME_WIDTH) << item[i].name << right << fixed << setprecision(2) << setw(ITEM_PRICE_WIDTH) << item[i].price << setw(ITEM_QTY_WIDTH) << item[i].qty << setw(ITEM_TOTAL_WIDTH) << item[i].amount[i] << endl;
} 
cout <<       "   -------------------------------------------------------------------------------------------------------------------------------------"<<endl; 
cout << left << setw(5)<< right << setw(TOTAL_WIDTH - 10) << "Total:" << setw(ITEM_TOTAL_WIDTH) << fixed << setprecision(2) << total_bill << endl;
cout << left << setw(5)<< right << setw(TOTAL_WIDTH - 10) << "Discount:" << setw(ITEM_TOTAL_WIDTH) << fixed << setprecision(2) << discount << endl;
cout << left << setw(5)<< right << setw(TOTAL_WIDTH - 10) << "Payable Amount:" << setw(ITEM_TOTAL_WIDTH) << fixed << setprecision(2) << grandTotal << endl;
cout <<       "   -------------------------------------------------------------------------------------------------------------------------------------"<<endl;

}
}
void usrdet::showbills(){
	cout << "Enter Customer id : ";
	cin >> id;
	ss.str("");
	ss << "Select * from billdetails where Cust_id = " << id <<";";
	query = ss.str();
	q = query.c_str();
	mysql_query(conn,q);
	res_set = mysql_store_result(conn);
while((row = mysql_fetch_row(res_set)) != NULL){
	       cout << "Invoice id : " << row[1] << endl;
}

	cout << "Enter  Invoice id from above choice: ";
	cin >> Invoice_id;
	ss.str("");
	ss << "Select * from billdetails where Cust_id = " << id << " AND Invoice_id = " << Invoice_id << ";";
	query = ss.str();
	q = query.c_str();
	mysql_query(conn,q);
	res_set = mysql_store_result(conn);
if ((row = mysql_fetch_row(res_set)) != NULL){
	    
	    cout << "               Customer Details" << endl ;
		cout << "               Invoice id : " << row[1] << endl;
		cout << "               Bill Date : " << row[8] << endl;
		cout << "               Customer id : " << row[2] << endl;
		cout << "               Customer Name : " << row[3] << endl;
		cout << "               Number of products : " << row[4] << endl;
		cout << "               Total Bill : " << row[5] << endl;
		cout << "               Discount   : " << row[6] << endl;
		cout << "               Grand Total : " << row[7] << endl << endl << endl;	
		 cout << "               Product Details" << endl ;
	}
	ss.str("");
	ss << "Select * from bill where Invoice_id  = "<< row[1]<< ";";
	query = ss.str();
	q = query.c_str();
	mysql_query(conn,q);
	res_set = mysql_store_result(conn);
	
	
while(true){
if ((row = mysql_fetch_row(res_set)) != NULL){
	    cout << "               Product id : " << row[1] << endl;
		cout << "               Product Name : " << row[2] << endl;
		cout << "               Quantity : " << row[3] << endl;
		cout << "               Price : " << row[4] << endl;
		cout << "               Amount   : " << row[5] << endl << endl;             
}
}	
}
	


void home_menu();
void welcome_menu();
void main_menu();
void usr_home();
void usrmain_menu();
//void customer_menu();
//void product_menu();
//void supplier_menu();
//void purchase_menu();
//void employee_menu();
//void customer_menu();
//void sales_menu();

void welcome ::usr_home() {
	user u;
	int c;
cout<<"                                +------------------+       "<<endl;
cout<<"                                |    1: Register   |          "<<endl;
cout<<"                                +------------------+        "<<endl;
cout<<"                                +------------------+       "<<endl;
cout<<"                                |    2:Login       |        "<<endl;
cout<<"                                +------------------+      "<<endl<<endl<<endl;
cout<<"                                 Your Choice: ";
cin>>c;
  switch(c)
  {
  	case 1: 
  	      system("cls");
  	      u.regster();
  	      break;
    case 2:
    	  system("cls");
    	  u.login();
    	  break;
    default : 
          system("cls");
          cout<< "ERROR !! Invalid choice !! ";
          break;
  }
	
}
void usrmain:: usrmain_menu()
{
	usrdet ud;
	int c;
	cout << "********************************************************************************************" << endl;
	cout << "                           WELCOME TO MYSHOP                   DATE and TIME : " << dt <<endl;
	cout << "********************************************************************************************" << endl;
	cout << "                        1. Add Your Details" << endl;
	cout << "                        2. Show Details" << endl;
	cout << "                        3. Generate Bill" << endl;
	cout << "                        4. Show Past Bills" << endl;
	cout << "                        5. EXIT" << endl << endl << endl;
	cout << "                           Enter Your Choice : ";
	cin >> c;
	switch (c)
	{
		case 1:
			system("cls");
			ud.add_usr();
			getch();
			break;
		case 2:
			system("cls");
			ud.show_usr();
			getch();
			break;
		case 3:
			system("cls");
			ud.generate_bill();
			getch();
			break;
		case 4:
			system("cls");
		   ud.showbills();
			getch();
			break;
		case 5:
			exit(1);
		default:
			system("cls");
			cout << "Wrong Input" << endl << endl << "Invalid input";
			getch();
			break;
	}
	return;
}

// Starting Page for application.
void welcome_menu(){
	
int c;
welcome w;	
	cout << "***************************************************************************************************" << endl;
	cout << "                               WELCOME TO MYSHOP                DATE and TIME : " << dt <<endl;
	cout << "***************************************************************************************************" << endl;
	cout << "                             1. ADMIN PORTAL." << endl;
	cout << "                             2. CUSTOMER PORTAL." << endl;
	cout << "                             3. Return To Main Menu" << endl << endl << endl;
	cout << "                               Enter Your Choice : ";
	cin >> c;
	
switch(c){
	
     case 1:
	        system("cls");
			w.home_menu();
            break;
            getch();

     case 2:
     	    system("cls");
			w.usr_home();
 	       break;
 	       getch();
 	       
 	 case 3:
     	   exit(1);
 	       
     default : 
          cout<<"Invalid choice."<<endl;
          break;
     }
}

int main()
{	
conn =  mysql_init(0);
conn = mysql_real_connect(conn,"localhost","root","pratham@9922","myshop",0,NULL,0);
int choice;
if(conn)
{
		//while(1)
		//{
		          // system("cls");
		           welcome_menu();
		           //menu();
     //	}
}
else
{
	system("cls");
	cout << "Error while connection to database." << endl << "Contact technical team." << endl;
}
	
getch();
return 0;
}

