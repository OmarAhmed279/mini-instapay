// mini-instapay.cpp : Defines the entry point for the application.
//

/*#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING 1 //this is so it doesn't crash

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
void OTP_verification();
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
    user  SenderAccount, ReceiverAccount;
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

void land_page() //created by wafaey 
{
    // include namespace nana 
    using namespace nana;
    // create form aka window, allign it to center with the size (800,600)
    form fm1{API::make_center(800,600), appearance(true, true, true, false, true, false, false)}; //appearance changes the appearance of the window
    screen* land_page = nullptr;
    // set background color to the form
    fm1.bgcolor(color(211, 211, 211));
    // set the name of the window
    fm1.caption("InstaPay");
    //API::effects_edge_nimbus(fm, effects::edge_nimbus::none); don't think this does anything
    //create a label for each email and password textboxes
    label lbl1{ fm1,"Email:" }, lbl2{ fm1,"Password:" };
    // positioning
    lbl1.move(rectangle(250, 150, 110, 17));
    lbl2.move(rectangle(250, 250, 110, 17));
    //create textboxes to input email and password
    textbox txt1{ fm1,rectangle(250, 170, 300, 30) }, txt2{ fm1,rectangle(250, 270, 300, 30) };
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
    form* pointer = &fm1;
    // create signup button
    button signup{ fm1,"SignUp" };
    signup.move(rectangle(250, 330, 100, 30));
    // incase of click event it switches to create user page, and closes landpage window
    signup.events().click([&fm1] {
        fm1.hide();
        create_user(); });
    // login button
    button login{ fm1,"Login" };
    login.move(rectangle(450, 330, 100, 30));
    login.events().click([&fm1] {
        fm1.hide();
        user_login(); });
    // show form
    fm1.show();
    // switch control from main to nana then back to main when you close the form
    exec();
}
void create_user()
{
    using namespace nana;
    form fm2{ API::make_center(800,600), appearance(true, true, true, false, true, false, false) };
    fm2.caption("Sign UP");
    label lbl3{ fm2,"Name :" }, lbl4{ fm2,"Email :" }, lbl5{ fm2 , "phone number :" }, lbl6{ fm2, "password :" },
        lbl7{ fm2, "User Information" };
    lbl3.move(rectangle(50, 70, 110, 17));
    lbl4.move(rectangle(50, 140, 110, 17));
    lbl5.move(rectangle(50, 210, 115, 20));
    lbl6.move(rectangle(50, 280, 110, 20));
    lbl7.move(rectangle(300, 20, 200, 40));
    paint::font my_font{ "Times New Roman", 20 };
    paint::font lable_font{ "Times New Roman", 14 };
    lbl3.typeface(lable_font);
    lbl4.typeface(lable_font);
    lbl5.typeface(lable_font);
    lbl6.typeface(lable_font);
    lbl7.typeface(my_font);
    textbox txt3{ fm2,rectangle(50, 90, 300, 25) }, txt4{ fm2,rectangle(50, 160, 300, 25) },
    txt5{ fm2, rectangle(50, 235, 300, 25) }, txt6{ fm2, rectangle(50, 305, 300, 25) };
    // enable user input
    
    txt3.editable(true);
    txt4.editable(true);
    txt5.editable(true);
    txt6.editable(true);
    txt6.mask('*');
    button btn1{ fm2, "Create account" };
    btn1.typeface(lable_font);
    btn1.move(rectangle(350, 350, 120, 40));
    btn1.events().click([&fm2] { 
        fm2.hide();
        OTP_verification(); });
    fm2.show();
    exec();
}

void OTP_verification()
{
    // type here
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
    int sender_wallet_before = 0, receiver_wallet_before = 0;
    transactions transaction;
    transactions_count++;
    transaction.id = transactions_count ;
    transaction.SenderAccount = sender;
    transaction.ReceiverAccount = reciever;
    sender_wallet_before = transaction.SenderAccount.wallet;
    receiver_wallet_before = transaction.ReceiverAccount.wallet;
    transaction.SenderAccount.wallet -= transaction.ammount;
    transaction.ReceiverAccount.wallet += transaction.ammount;
    if (((transaction.SenderAccount.wallet - sender_wallet_before) == transaction.ammount) && ((transaction.ReceiverAccount.wallet - receiver_wallet_before) == transaction.ammount))
    {
        transaction.status = 1;
    }
    else
    {
        transaction.status = -1;
    }
}*/
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
void OTP_verification();
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
    user  SenderAccount, ReceiverAccount;
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

void land_page() //made by wafaey, modified by omar 
{
    // include namespace nana 
    using namespace nana;
    // create form aka window, allign it to center with the size (800,600)
    form fm1{ API::make_center(800,600), appearance(true, true, true, false, true, false, false) }; //appearance changes the appearance of the window
    screen* land_page = nullptr;
    // set background color to the form
    fm1.bgcolor(color(211, 211, 211));
    // set the name of the window
    fm1.caption("InstaPay");
    //API::effects_edge_nimbus(fm, effects::edge_nimbus::none); don't think this does anything
    //create a label for each email and password textboxes
    label lbl1{ fm1,"Email:" }, lbl2{ fm1,"Password:" };
    // positioning
    lbl1.move(rectangle(250, 150, 110, 17));
    lbl2.move(rectangle(250, 250, 110, 17));
    //create textboxes to input email and password
    textbox txt1{ fm1,rectangle(250, 170, 300, 30) }, txt2{ fm1,rectangle(250, 270, 300, 30) };
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
    form* pointer = &fm1;
    // create signup button
    button signup{ fm1,"SignUp" };
    signup.move(rectangle(250, 330, 100, 30));
    // incase of click event it switches to create user page
    signup.events().click([&fm1] {
        fm1.hide();
        create_user(); });
    // login button
    button login{ fm1,"Login" };
    login.move(rectangle(450, 330, 100, 30));
    login.events().click([&fm1] {
     fm1.hide();
     user_login(); });
    // show form
    fm1.show();
    // switch control from main to nana then back to main when you close the form
    exec();
}
void create_user()
{
    using namespace nana;
    form fm2{ API::make_center(800,600), appearance(true, true, true, false, true, false, false) };
    fm2.caption("Sign UP");
    label lbl3{ fm2,"Name :" }, lbl4{ fm2,"Email :" }, lbl5{ fm2 , "phone number :" }, lbl6{ fm2, "password :" },
        lbl7{ fm2, "User Information" }, lbl8{ fm2, "----------------------------------------------------------------------------" },
        lbl9{ fm2, "----------------------------------------------------------------------------" },
        lbl10{ fm2, "note: provide the same name as in your national ID" }, lbl11{ fm2, "Please enter a valid email address to proceed." },
        lbl12{ fm2 , "Your password must be at least 8 characters long, include both upper and lowercase letters,contain at least one numeric digit (0–9), and include at least one special character (e.g., !, @, #, $)." };
    lbl3.move(rectangle(50, 70, 110, 17));
    lbl4.move(rectangle(50, 140, 110, 17));
    lbl5.move(rectangle(50, 210, 115, 20));
    lbl6.move(rectangle(50, 280, 110, 20));
    lbl7.move(rectangle(300, 20, 200, 40));
    lbl8.move(rectangle(200, 0, 400, 20));
    lbl9.move(rectangle(200, 50, 400, 40));
    lbl10.move(rectangle(50, 115, 400, 20));
    lbl11.move(rectangle(50, 185, 400, 17));
    lbl12.move(rectangle(50, 330, 400, 60));
    paint::font my_font{ "Times New Roman", 20 };
    paint::font lable_font{ "Times New Roman", 14 };
    paint::font slable_font{ "Times New Roman", 10 };
    lbl3.typeface(lable_font);
    lbl4.typeface(lable_font);
    lbl5.typeface(lable_font);
    lbl6.typeface(lable_font);
    paint::font italic_font{ "Times New Roman", 10, {true, false, false, false} };  // Italic font
    lbl10.typeface(italic_font);
    lbl10.fgcolor(color(230, 0, 0));
    lbl11.typeface(italic_font);
    lbl11.fgcolor(color(230, 0, 0));
    lbl11.typeface(italic_font);
    lbl12.fgcolor(color(230, 0, 0));// Set text color to red (RGB)
    lbl7.typeface(my_font);
    textbox txt3{ fm2,rectangle(50, 90, 300, 25) }, txt4{ fm2,rectangle(50, 160, 300, 25) },
        txt5{ fm2, rectangle(50, 235, 300, 25) }, txt6{ fm2, rectangle(50, 305, 300, 25) };
    // enable user input

    txt3.editable(true);
    txt4.editable(true);
    txt5.editable(true);
    txt6.editable(true);
    txt6.mask('*');
    button btn1{ fm2, "Create account" };
    btn1.typeface(lable_font);
    btn1.move(rectangle(350, 400, 120, 40));
    btn1.events().click([] { OTP_verification(); });
    fm2.show();
    exec();
}

void OTP_verification()
{
    // type here
}

void user_login()
{
    // type here
}
void main_menu()
{
    // type here
}
void copydatatodatabase()
{
    // type here
}
void copydatabasetoapp()
{
    // type here
}

void transaction(user sender, user reciever) // made by wafaey
{
    transactions transaction;
    int sender_wallet_before, receiver_wallet_before;
    transactions_count++;
    transaction.id = transactions_count;
    transaction.SenderAccount = sender;
    transaction.ReceiverAccount = reciever;
    sender_wallet_before = transaction.SenderAccount.wallet;
    receiver_wallet_before = transaction.ReceiverAccount.wallet;
    transaction.SenderAccount.wallet -= transaction.ammount;
    transaction.ReceiverAccount.wallet += transaction.ammount;
    // check if the balance of both the sender and reciever have changed correctly or no
    if (((sender_wallet_before - transaction.SenderAccount.wallet) == transaction.ammount) && ((transaction.ReceiverAccount.wallet - receiver_wallet_before) == transaction.ammount))
    {
        transaction.status = 1;
    }
    // if one of them is still pending change
    else if (transaction.SenderAccount.wallet == sender_wallet_before || transaction.ReceiverAccount.wallet == receiver_wallet_before)
    {
        transaction.status = 0;
    }
    // if the transaction failed
    else
    {
        transaction.status = -1;
    }
}


