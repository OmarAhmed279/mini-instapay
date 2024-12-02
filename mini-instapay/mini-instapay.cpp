// mini-instapay.cpp : Defines the entry point for the application.
//

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING 1 //this is so it doesn't crash

#include "mini-instapay.h" //this has all the header files
using namespace std;

void land_page();
void create_user();
void user_login();
void main_menu();
void copydatatodatabase();
void copydatabasetoapp();

// create user structure
struct user {
    string  name, email, password, ContactInformation, linked_bank_accounts[3];
    int id;
};
// create transcations structure
struct transcations {
    string  SenderAccount, RecieverAccount, date;
    int id;
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
    land_page();

    return 0;
}

void land_page() {
    // include namespace nana 
    using namespace nana;
    // create form aka window, allign it to center with the size (800,600)
    form fm{ API::make_center(800,600) };
    // set background color to the form
    fm.bgcolor(color(255, 165, 0));
    // set the name of the window
    fm.caption("InstaPay");
    //close resize attribute
    API::effects_edge_nimbus(fm, effects::edge_nimbus::none);
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
    cout << "Omak Ar3a!! HEHE" << endl;
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

