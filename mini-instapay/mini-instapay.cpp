// mini-instapay.cpp : Defines the entry point for the application.
//

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING 1 //this is so it doesn't crash

#include "mini-instapay.h" //this has all the header files
using namespace std;

//Global Variables

static int user_count = 0, transactions_count = 0;

// Functions Declaration
void land_page();
void create_user();
void user_login();
void main_menu();
void copydatatodatabase();
void copydatabasetoapp();

struct bankaccount {
    string name;
    int amount;
    int accountnum;
};


// create user structure
struct user {
    string  name, email, password, ContactInformation;
    bankaccount accounts[3];
    int id, wallet = 0;
};
// create transcations structure
struct transactions {
    user  SenderAccount, RecieverAccount;
    string date;
    int id = 0;
    //if status = {success = 1, pending = 0, failed = -1}
    int ammount = 0, status;
};
// create admin structure
struct admin {
    string id, name, email;
    // if permissions = { all = 1, view = 2, edit = 3 , lesa mesh 3aref el sara7a ely yemsek el heta deh yezabatha}
    int permissions;
};




int main()
{
    // Initial code for Database creation (First time run only)
    sqlite3* db;
    int rc;
    // Open the SQLite database
    rc = sqlite3_open("mini-instapay.db", &db);
    if (rc) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        return 1;
    }
    // Create table if it doesn't exist
    const char* create_ACC_sql = "CREATE TABLE IF NOT EXISTS USER (id INTEGER PRIMARY KEY, name TEXT, email TEXT, password TEXT, Contactinformation TEXT,  day INTEGER, month INTEGER, year INTEGER, state INTEGER)";
    rc = sqlite3_exec(db, create_ACC_sql, NULL, 0, NULL);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return 1;
    }
    // Create table if it doesn't exist
    const char* create_POST_sql = "CREATE TABLE IF NOT EXISTS Usertrans (id INTEGER PRIMARY KEY, SenderAccount TEXT, RecieverAccount TEXT, date TEXT, Amount INTEGER, Status INTEGER)";
    rc = sqlite3_exec(db, create_POST_sql, NULL, 0, NULL);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return 1;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    land_page();

    return 0;
}

void land_page() {
    // include namespace nana 
    using namespace nana;
    // create form aka window, allign it to center with the size (800,600)
    form fm{API::make_center(800,600), appearance(true, true, true, false, true, false, false)}; //appearance changes the appearance of the window
    // set background color to the form
    fm.bgcolor(color(255, 165, 0));
    // set the name of the window
    fm.caption("InstaPay");
    //API::effects_edge_nimbus(fm, effects::edge_nimbus::none); don't think this does anything
    //create a label for each email and password textboxes
    label lbl1{ fm,"Email:" }, lbl2{ fm,"Password:" };
    // positioning
    lbl1.move(rectangle(250, 150, 110, 17));
    lbl2.move(rectangle(250, 250, 110, 17));
    //create textboxes to input email and password
    textbox txt1{ fm,rectangle(250, 170, 300, 30) }, txt2{ fm,rectangle(250, 270, 300, 30) };
    // enable user input
    txt1.editable(true);
    txt2.editable(true);
    // set font (optional)
    txt1.typeface(paint::font("Arial", 12));
    txt2.typeface(paint::font("Arial", 12));
    // disable mutlilines
    txt1.multi_lines(false);
    txt2.multi_lines(false);
    // hide password
    txt2.mask('*');
    // create signup button
    button signup{ fm,"SignUp" };
    signup.move(rectangle(250, 330, 100, 30));
    // incase of click event it switches to create user page
    signup.events().click([] {create_user(); });
    // login button
    button login{ fm,"Login" };
    login.move(rectangle(450, 330, 100, 30));
    login.events().click([] {user_login(); });
    // show form
    fm.show();
    // switch control from main to nana then back to main when you close the form
    exec();
}
void create_user()
{
    
}

void user_login()
{
    //type here
}
void main_menu()
{
    // typehere
}
void copydatatodatabase()
{
    // type here
}
void copydatabasetoapp()
{
    // type here
}

void transaction(user sender, user reciever)
{
    transactions transaction;
    transactions_count++;
    transaction.id = transactions_count ;
    transaction.SenderAccount = sender;
    transaction.RecieverAccount = reciever;
    transaction.SenderAccount.wallet -= transaction.ammount;
    transaction.RecieverAccount.wallet += transaction.ammount;
}

