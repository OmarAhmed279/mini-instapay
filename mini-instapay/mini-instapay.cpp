// mini-instapay.cpp : Defines the entry point for the application.
//

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING 1 //this is so it doesn't crash

#include "mini-instapay.h" //this has all the header files

using namespace std;

void create_user();
void user_login();

// create user structure
struct user {
    string id, name, email, password, ContactInformation, linked_bank_accounts[3];
};
// create transcations structure
struct transcations {
    string id, SenderAccount, RecieverAccount, date;
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
    using namespace nana;

    //Define a form.
    form fm;

    //Define a label and display a text.
    label lab{ fm, "Hello, Please Sign in." };
    lab.format(true);

    textbox txt{ fm, rectangle(0,0, 100,100), true }; //an empty textbox for username TODO: learn how to layout elements

    //Define a button and answer the click event.
    button btn{ fm, "Sign in" };
    btn.events().click([&fm]() {
        fm.close();
        }); //currently this just closes the app

    //Layout management
    fm.div("vert <><<><weight=50% text><>><><weight=24<><button><>><>");
    fm["text"] << lab;
    fm["button"] << btn;
    fm.collocate();

    //Show the form
    fm.show();

    //Start to event loop process, it blocks until the form is closed.
    exec();
}

void create_user()
{
    // type here
}

void user_login()
{
    //type here
}
