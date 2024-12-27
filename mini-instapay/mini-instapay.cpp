#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING 1 //this is so it doesn't crash

#include "mini-instapay.h" //this has all the header files
#include <regex>
using namespace std;
using namespace nana;

//create date struct
struct dat {
    int day;
    int month;
    int year;
};

// create banckaccount struct
struct bankaccount {
    string name = "";
    int amount = 0;
    int accountnum = 0;
};

// create user structure
struct user {
    string  name, email, password;
    bankaccount accounts[3];
    int id;
    string Phonenumber;
    int wallet = 0, numofaccounts = 0;
    bool flag = false;
};

// create transcations structure
struct transactions {
    user  SenderAccount, ReceiverAccount;
    dat date_transaction;
    int id = 0;
    //if status = {success = 1, pending = 0, failed = -1}
    long double ammount = 0, status;
};

// create admin structure
struct admin {
    int id;
    // if permissions = { all = 1, view = 2, edit = 3 , lesa mesh 3aref el sara7a ely yemsek el heta deh yezabatha}
    int permissions;
};

// Data Arrays for Storage (fake info)
vector<user> USERS = {
    {"Admin", "Admin@gmail.123", "password", {}, 0, "01000000000", 0, 0, false},
    {"Aiman", "Aiman123@hotmail.com", "pass", {"CIB", 5, 123456789}, 1,"01021473444", 10, 1, false},
    {"Ahmed", "Ahmed89@yahoo.com", "Ahmed89", {"HSBC", 100000, 123 }, 2, "01021473422", 100000000, 1, false}

};

vector<transactions> TRANSACTIONS =
{

    {USERS[2], USERS[1], {13,12,2024}, 0, 100000000, 0},
    {USERS[1], USERS[2], {12,12,2024}, 1, 5, 1},
    {USERS[1], USERS[1], {11,12,2024}, 2, 0, -1}

};

//Global Variables

int user_count = USERS.size();
int transactions_count = TRANSACTIONS.size();
int current_user_id = -1,current_bank = -1;
time_t t = std::time(0);   // get time now
tm* now = std::localtime(&t);
// Functions Declaration
void land_page();
void create_user();
void user_login(string, string, form&, label&, label&);
void OTP_verification(form&, string, string, string, string);
void dashboard(vector<user>);
void transaction(user, user, int, int, int);
void edit_profile(vector<user>);
void admin_work();
void trans_history(vector<user>, vector<transactions>);
void managebankacc(vector<user>);
void show_users();
void suspendaccount();
void trans_wallet();
void Generate_Report();

int main()
{
    land_page();

    return 0;
}

void land_page() //made by wafaey, modified by omar 
{
    // create form aka window, allign it to center with the size (800,600)
    form landing_page{ API::make_center(800,600), appearance(true, true, true, false, true, false, false) }; //appearance changes the appearance of the window
    screen* land_page = nullptr;
    // set background color to the form
    landing_page.bgcolor(color(211, 211, 211));
    // set the name of the window
    landing_page.caption("InstaPay");
    //create a label for each email and password textboxes
    label email_signin_lbl{ landing_page,"Email:" }, password_signin_lbl{ landing_page,"Password:" };
    // positioning
    email_signin_lbl.move(rectangle(250, 150, 400, 17));
    password_signin_lbl.move(rectangle(250, 250, 400, 17));
    //create textboxes to input email and password
    textbox input_email_signin{ landing_page,rectangle(250, 170, 300, 30) }, input_pass_signin{ landing_page,rectangle(250, 270, 300, 30) };
    // enable user input
    input_email_signin.editable(true);
    input_pass_signin.editable(true);
    // set font (optional)
    input_email_signin.typeface(paint::font("Arial", 12));
    input_pass_signin.typeface(paint::font("Arial", 12));
    // disable mutlilines
    input_email_signin.multi_lines(false);
    input_pass_signin.multi_lines(false);
    // hide password
    input_pass_signin.mask('*');
    //form* pointer = &landing_page; this isn't used am pretty sure
    // create signup button
    button signup_btn{ landing_page,"SignUp" };
    signup_btn.move(rectangle(250, 330, 100, 30));
    /*button admin{landing_page,"I am an admin"};
    admin.move(rectangle(300, 370, 200, 40));
    admin.events().click([&] {
        landing_page.close();
        admin_work();
        });*/
    // incase of click event it switches to create user page
    signup_btn.events().click([&landing_page] {
        landing_page.hide();
        create_user(); });
    // login button
    button login_btn{ landing_page,"Login" };
    login_btn.move(rectangle(450, 330, 100, 30));
    login_btn.events().click([&landing_page, &input_email_signin, &input_pass_signin, &email_signin_lbl, &password_signin_lbl] {
        string email = input_email_signin.text(); //variables for email and pass
        string pass = input_pass_signin.text();
        user_login(email, pass, landing_page, email_signin_lbl, password_signin_lbl); });
    // show form
    landing_page.show();
    // switch control from main to nana then back to main when you close the form
    exec();
}

void create_user() // made by youssef shehta and seif shehta, modified by Abderrahman
{
    regex Name_pattern("^[A-Za-z ]{3,20}$");
    regex Email_pattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,63}$)");
    regex pnumber_pattern("^(011|012|010|015)[0-9]{8}$");
    using namespace nana;
    form signup_page{ API::make_center(800,600), appearance(true, true, true, false, true, false, false) };
    signup_page.caption("Sign Up");
    label name_signup_lbl{ signup_page,"Name :" }, email_signup_lbl{ signup_page,"Email :" }, pnumber_signup_lbl{ signup_page , "Phone number :" }, pass_signup_lbl{ signup_page, "Password :" },
        userinfo_signup_lbl{ signup_page, "User Information" }, space_signup_lbl{ signup_page, "----------------------------------------------------------------------------" },
        space2_signup_lbl{ signup_page, "----------------------------------------------------------------------------" },
        note1_signup_lbl{ signup_page, "Name must be the same as in your national ID" }, note2_signup_lbl{ signup_page, "Please enter a valid email address." },
        note3_signup_lbl{ signup_page , "Your password must be at least 8 characters long, include both upper and lowercase letters, contain at least one numeric digit (0–9), and include at least one special character (e.g., !, @, #, $)." };
    name_signup_lbl.move(rectangle(50, 70, 110, 17));
    email_signup_lbl.move(rectangle(50, 140, 110, 17));
    pnumber_signup_lbl.move(rectangle(50, 210, 115, 20));
    pass_signup_lbl.move(rectangle(50, 280, 110, 20));
    userinfo_signup_lbl.move(rectangle(300, 20, 200, 40));
    space_signup_lbl.move(rectangle(200, 0, 400, 20));
    space2_signup_lbl.move(rectangle(200, 50, 400, 40));
    note1_signup_lbl.move(rectangle(50, 115, 400, 20));
    note2_signup_lbl.move(rectangle(50, 185, 400, 17));
    note3_signup_lbl.move(rectangle(50, 330, 400, 60));
    paint::font title_font{ "Times New Roman", 20 };
    paint::font header_font{ "Times New Roman", 14 };
    //paint::font slable_font{ "Times New Roman", 10 }; this isn't used
    nana::color red = color(230, 0, 0); //defines a color red
    nana::color dark_blue = nana::color(0, 0, 139); // Defines a dark blue color
    name_signup_lbl.typeface(header_font);
    email_signup_lbl.typeface(header_font);
    pnumber_signup_lbl.typeface(header_font);
    pass_signup_lbl.typeface(header_font);
    paint::font italic_font{ "Times New Roman", 10, {true, false, false, false} };  // Italic font (bruh that shit not italic -omar)
    note1_signup_lbl.typeface(italic_font);
    note1_signup_lbl.fgcolor(dark_blue);
    note2_signup_lbl.typeface(italic_font);
    note2_signup_lbl.fgcolor(dark_blue);
    note2_signup_lbl.typeface(italic_font);
    note3_signup_lbl.fgcolor(dark_blue);// Set text color to red (RGB)
    userinfo_signup_lbl.typeface(title_font);
    textbox input_name_signup{ signup_page,rectangle(50, 90, 300, 25) }, input_email_signup{ signup_page,rectangle(50, 160, 300, 25) },
        input_pnumber_signup{ signup_page, rectangle(50, 235, 300, 25) }, input_pass_signup{ signup_page, rectangle(50, 305, 300, 25) };
    // enable user input

    input_name_signup.editable(true);
    input_email_signup.editable(true);
    input_pnumber_signup.editable(true);
    input_pass_signup.editable(true);
    input_name_signup.multi_lines(false);
    input_email_signup.multi_lines(false);
    input_pnumber_signup.multi_lines(false);
    input_pass_signup.multi_lines(false);
    input_name_signup.tooltip("Enter a valid User Name (letters only, 3-20 characters)");
    input_email_signup.tooltip("Enter a vaild Email address. Ex: Name@Example.com");
    input_pnumber_signup.tooltip("Enter a valid phone number (must contain 11 numbers)");
    input_pass_signup.mask('*');
    label name_match{ signup_page };
    name_match.move(rectangle(360, 92, 300, 25));
    name_match.fgcolor(colors::red);
    label email_match{ signup_page };
    email_match.move(rectangle(360, 162, 300, 25));
    email_match.fgcolor(colors::red);
    label pnumber_match{ signup_page };
    pnumber_match.move(rectangle(360, 237, 300, 30));
    pnumber_match.fgcolor(colors::red);
    button create_acc{ signup_page, "Create account" };
    create_acc.typeface(header_font);
    create_acc.move(rectangle(350, 400, 120, 40));

    button goback_btn{ signup_page,"go back" };
    goback_btn.move(rectangle(30, 380, 50, 40));
    goback_btn.events().click([&] {
        signup_page.close();
        land_page(); });

    input_name_signup.events().focus([&](const nana::arg_focus& arg) {
        if (!arg.getting) { // Losing focus
            string name = input_name_signup.text();
            if (regex_match(name, Name_pattern))
            {
                name_match.caption("Valid name");
                name_match.fgcolor(colors::green);
            }
            else
            {
                name_match.caption("Invalid name! (Must be alphabetic, 3-20 characters)");
                name_match.fgcolor(colors::red);
            }
        }
        });
    input_email_signup.events().focus([&](const nana::arg_focus& arg) {
        if (!arg.getting) { // Losing focus
            string email = input_email_signup.text();
            if (regex_match(email, Email_pattern))
            {
                email_match.caption("Valid Email address");
                email_match.fgcolor(colors::green);
            }
            else
            {
                email_match.caption("Invalid Email address ");
                email_match.fgcolor(colors::red);
            }
        }
        });
    input_pnumber_signup.events().focus([&](const nana::arg_focus& arg) {
        if (!arg.getting) { // Losing focus
            string phone = input_pnumber_signup.text();
            if (regex_match(phone, pnumber_pattern))
            {
                pnumber_match.caption("Valid phone number");
                pnumber_match.fgcolor(colors::green);
            }
            else
            {
                // If the length is less than 11 digits
                if (phone.length() < 11) {
                    pnumber_match.caption("Invalid phone number. The number must be 11 digits.");
                    pnumber_match.fgcolor(colors::red);
                }
                // If the number length is correct but the prefix is wrong
                else if (!regex_match(phone, regex("^(011|012|010|015).*"))) {
                    pnumber_match.caption("Invalid phone number. The number must start with 011, 012, 010, or 015.");
                    pnumber_match.fgcolor(colors::red);
                }
                // If it's invalid for other reasons
                else {
                    pnumber_match.caption("Invalid phone number. Please check the format.");
                    pnumber_match.fgcolor(colors::red);
                }
            }
        }
        });
    create_acc.events().click([&input_name_signup, &Name_pattern, &name_match, &input_email_signup, &Email_pattern, &email_match, &input_pnumber_signup, &pnumber_match, &pnumber_pattern, &signup_page, &input_pass_signup]
        {
            string name = input_name_signup.text();
            string email = input_email_signup.text();
            string phone = input_pnumber_signup.text();
            string pass = input_pass_signup.text();

            if (regex_match(name, Name_pattern) && regex_match(email, Email_pattern) && regex_match(phone, pnumber_pattern))
            {
                signup_page.hide();
                OTP_verification(signup_page, name, email, phone, pass);
            }
        });
    signup_page.show();
    exec();
}

void OTP_verification(form& signup_page, string name, string email, string phone, string pass) //made by abdelrahman, modified by omar
{
    // Generate OTP
    int OTP[6];
    srand(std::time(0)); // Seed for random OTP generation
    for (int i = 0; i < 6; ++i) {
        OTP[i] = rand() % 10;
    }

    // Convert OTP to string for display
    string otp_string;
    for (int digit : OTP) {
        otp_string += to_string(digit);
    }

    // Create OTP verification form
    form otp_form{ API::make_center(400, 200), appearance(true, true, true, false, true, false, false) };
    otp_form.caption("OTP Verification");

    // Label to display the OTP (simulating sending it to the user)
    label otp_label{ otp_form, "Your OTP is: " + otp_string };
    otp_label.move(rectangle(20, 20, 360, 30));

    // Textbox for user to input OTP
    textbox otp_input{ otp_form, rectangle(20, 60, 360, 30) };
    otp_input.multi_lines(false);
    otp_input.tip_string("Enter your OTP here");

    // Label for feedback
    label feedback_label{ otp_form, "" };
    feedback_label.move(rectangle(20, 100, 360, 30));
    feedback_label.fgcolor(colors::red);

    // Verify button
    button verify_btn{ otp_form, "Verify" };
    verify_btn.move(rectangle(150, 140, 100, 30));

    // Verify button click event
    verify_btn.events().click([&]() {
        string user_otp = otp_input.text();

        if (user_otp.size() == 6 && user_otp == otp_string) {
            feedback_label.caption("Verification successful!");
            feedback_label.fgcolor(colors::green);

            // Create a new user object
            user new_user;
            new_user.name = name;
            new_user.email = email;
            new_user.password = pass;
            new_user.accounts[0] = { "", 0, 0 };
            new_user.id = USERS.size(); // Assign a new unique ID "made it equal to size because admin has id = 0" - omar
            new_user.Phonenumber = phone;
            new_user.wallet = 0;

            // Add the new user to the USERS vector
            USERS.push_back(new_user);

            current_user_id = new_user.id;

            otp_form.close();
            dashboard(USERS);
        }
        else {
            feedback_label.caption("Incorrect OTP. Please try again.");
            feedback_label.fgcolor(colors::red);
        }
        });

    // Show the OTP form
    otp_form.show();
    exec();
}

void user_login(string e, string p, form& landpage, label& email_label, label& pass_label) //made by omar
{

    if (USERS[0].email == e && USERS[0].password == p)
    {
        current_user_id = 0;
        landpage.close();
        admin_work();
    }
    else
    {
        bool noluck = true;

        for (int i = 0; i < USERS.size(); i++)
        {
            if (USERS[i].email == e)
            {
                if (USERS[i].password == p)
                {
                    current_user_id = USERS[i].id;
                    if (USERS[current_user_id].flag)
                    {
                        msgbox success(landpage, "Error");
                        success << "Your account has been suspended.";
                        success.show();
                        noluck = false;
                        break;
                    }
                    else
                    {
                        landpage.close();
                        dashboard(USERS);
                        noluck = false;
                        break;
                    }
                }
                else
                {
                    email_label.caption("Email:");
                    pass_label.caption("Password: Wrong password, please try again.");
                    noluck = false;
                    break;
                }
            }
        }
        if (noluck)
        {
            email_label.caption("Email: USER doesn't exist.");
            pass_label.caption("Password:");
        }
    }
}

void edit_profile(vector<user> users) {
    form edit{ API::make_center(800, 600), appearance(true, true, true, false, true, false, false) };//made by youssif ,modified by:omar&abderhman
    edit.caption("Edit Profile");

    // Labels for display
    label name_lbl{ edit, "Name:" }, email_lbl{ edit, "Email:" }, phone_lbl{ edit, "Phone Number:" },
        pass_lbl{ edit, "Password:" }, wallet_lbl{ edit, "Wallet Balance:" }, id_lbl{ edit, "User ID:" }, bank_lbl{ edit, "Bank Accounts:" };
    button goback_btn{ edit,"go back" };
    goback_btn.move(rectangle(30, 500, 50, 40));
    goback_btn.events().click([&] {
        edit.close();
        dashboard(USERS); });

    name_lbl.move(rectangle(50, 30, 120, 20));
    email_lbl.move(rectangle(50, 80, 120, 20));
    phone_lbl.move(rectangle(50, 130, 120, 20));
    pass_lbl.move(rectangle(50, 180, 120, 20));
    wallet_lbl.move(rectangle(50, 230, 120, 20));
    id_lbl.move(rectangle(50, 280, 120, 20));
    bank_lbl.move(rectangle(50, 330, 120, 20));

    // Display fields for uneditable data
    label wallet_data{ edit, "EGP " + to_string(users[current_user_id].wallet) }, id_data{ edit, to_string(current_user_id) };
    wallet_data.move(rectangle(200, 230, 200, 20));
    id_data.move(rectangle(200, 280, 200, 20));

    string accounts_display = "Accounts:\n";
    for (int i = 0; i < 3; i++) {
        accounts_display += "Bank Name: " + users[current_user_id].accounts[i].name + " Amount: " + to_string(users[current_user_id].accounts[i].amount) + " Account Num: " + to_string(users[current_user_id].accounts[i].accountnum) + "\n";
    }

    label accounts_data{ edit, accounts_display };
    accounts_data.move(rectangle(200, 330, 400, 200));

    // Editable fields with "Edit" buttons
    textbox name_box{ edit }, email_box{ edit }, phone_box{ edit }, pass_box{ edit };
    name_box.move(rectangle(200, 30, 200, 25));
    email_box.move(rectangle(200, 80, 200, 25));
    phone_box.move(rectangle(200, 130, 200, 25));
    pass_box.move(rectangle(200, 180, 200, 25));

    // Initial values for editable fields
    name_box.caption(users[current_user_id].name);
    email_box.caption(users[current_user_id].email);
    phone_box.caption(users[current_user_id].Phonenumber);
    pass_box.caption(users[current_user_id].password);

    // Set textboxes to read-only initially
    name_box.enabled(false);
    email_box.enabled(false);
    phone_box.enabled(false);
    pass_box.enabled(false);

    // "Edit" buttons for each editable field
    button edit_name{ edit, "Edit" }, edit_email{ edit, "Edit" }, edit_phone{ edit, "Edit" }, edit_pass{ edit, "Edit" };
    edit_name.move(rectangle(420, 30, 60, 25));
    edit_email.move(rectangle(420, 80, 60, 25));
    edit_phone.move(rectangle(420, 130, 60, 25));
    edit_pass.move(rectangle(420, 180, 60, 25));

    // Enable editing when "Edit" button is clicked
    edit_name.events().click([&]() { name_box.enabled(true); });
    edit_email.events().click([&]() { email_box.enabled(true); });
    edit_phone.events().click([&]() { phone_box.enabled(true); });
    edit_pass.events().click([&]() { pass_box.enabled(true); });

    // Save changes button
    button save_btn{ edit, "Save Changes" };
    save_btn.move(rectangle(50, 400, 150, 40));
    save_btn.events().click([&]() {
        string new_name = name_box.text();
        string new_email = email_box.text();
        string new_phone = phone_box.text();
        string new_pass = pass_box.text();

        if (regex_match(new_name, regex("^[A-Za-z ]{3,20}$")) &&
            regex_match(new_email, regex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,63}$)")) &&
            regex_match(new_phone, regex("^(011|012|010|015)[0-9]{8}$"))) {

            // Update USERS vector
            for (auto& user : USERS) {
                if (user.id == current_user_id) {
                    user.name = new_name;
                    user.email = new_email;
                    user.Phonenumber = stoi(new_phone);
                    user.password = new_pass;
                    break;
                }
            }

            msgbox success(edit, "Update Successful");
            success << "Your profile has been updated.";
            success.show();
            edit.close();
            dashboard(USERS);
        }
        else {
            msgbox error(edit, "Invalid Input");
            error << "Please ensure all fields are filled in correctly.";
            error.show();
        }
        });

    edit.show();
    exec();
}

void transaction(user sender, user reciever, int day, int month, int year) // made by wafaey
{
    bool nottoday = false;
    transactions transaction;
    int sender_wallet_before, receiver_wallet_before;
    transactions_count++;
    transaction.id = transactions_count;
    transaction.SenderAccount = sender;
    transaction.ReceiverAccount = reciever;
    // get the current date 
    if (now->tm_year + 1900 == year && now->tm_mon + 1 == month && now->tm_mday == day)
    {
        transaction.date_transaction.year = now->tm_year + 1900;
        transaction.date_transaction.month = now->tm_mon + 1;
        transaction.date_transaction.day = now->tm_mday;
    }
    else {
        transaction.date_transaction.year = year;
        transaction.date_transaction.month = month;
        transaction.date_transaction.day = day;
        nottoday = true;
    }
    sender_wallet_before = transaction.SenderAccount.wallet;
    receiver_wallet_before = transaction.ReceiverAccount.wallet;
    //transaction page GUI
    form transaction_window{ API::make_center(800,600), appearance(true, true, true, false, true, false, false) };
    transaction_window.bgcolor(color(211, 211, 211));
    transaction_window.caption("transactions");
    label Ammount{ transaction_window,"Enter Ammount: " };
    Ammount.move(rectangle(250, 150, 110, 17));
    Ammount.show();
    textbox money_ammount{ transaction_window,rectangle(250, 200, 300, 30) };
    money_ammount.editable(true);
    money_ammount.typeface(paint::font("Arial", 12));
    money_ammount.multi_lines(false);
    money_ammount.show();
    label state{ transaction_window,"initial text" };
    state.move(rectangle(250, 150, 200, 17));
    state.hide();
    label error2{ transaction_window,"Insuffecient funds" };
    error2.move(rectangle(250, 170, 200, 17));
    error2.hide();
    // button to return to dashboard
    button close{ transaction_window,"Return to dashboard" };
    close.move(rectangle(400, 300, 150, 40));
    close.events().click([&transaction_window]
        {
            transaction_window.close();
            dashboard(USERS);
        });
    button enter_ammount{ transaction_window, "Confirm" };
    enter_ammount.move(rectangle(250, 300, 150, 40));
    enter_ammount.show();
    enter_ammount.events().click([&transaction, &money_ammount, &Ammount, &transaction_window, &sender_wallet_before, &receiver_wallet_before, &state, &error2, &enter_ammount, &close, &nottoday]
        {
            //validate user input
            bool valid = false;
            try
            {
                transaction.ammount = stod(money_ammount.text());
                valid = true;
            }
            catch (const exception& e)
            {
                valid = false;
                cerr << e.what();
                form popup(nana::API::make_center(400, 200), appearance(true, true, true, false, true, false, false));
                popup.caption("ERROR!!!");
                label error1{ popup, "Invalid input, input must be a number." };
                error1.move(rectangle(180, 100, 110, 17));
                button close{ popup, "Close" };
                close.move(rectangle(250, 210, 100, 30));
                close.events().click([&popup]
                    {
                        popup.close();
                    });
                // Show the popup as modal (blocks other interaction until closed)
                popup.modality();
            }
            if (valid)
            {
                enter_ammount.hide();
                close.move(rectangle(300, 300, 100, 30));
                // if ammount is invalid, transaction fails
                if (transaction.ammount > transaction.SenderAccount.wallet)
                {
                    transaction.status = -1;
                    error2.show();
                }
                else
                {
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
                Ammount.hide();
                money_ammount.hide();
                if (nottoday && transaction.status != -1)
                {
                    transaction.status = 0;
                }
                if (transaction.status == 1)
                {
                    state.caption("Money transfer is complete");
                    state.show();
                }
                else if (transaction.status == 0)
                {
                    state.caption("Money transfer is pending");
                    state.show();
                }
                else
                {
                    state.caption("Money transfer failed");
                    state.show();
                }
                state.move(rectangle(300, 150, 200, 17));
            }
            //add to TRANSACTIONS vector
            transactions_count++;
            TRANSACTIONS.insert(TRANSACTIONS.begin(), { transaction.SenderAccount,transaction.ReceiverAccount,transaction.date_transaction,transaction.id,transaction.ammount,transaction.status });
            USERS[transaction.SenderAccount.id].wallet = transaction.SenderAccount.wallet;
            USERS[transaction.ReceiverAccount.id].wallet = transaction.ReceiverAccount.wallet;
        });
    transaction_window.show();
    exec();
}

void trans_wallet() // by wafaey
{
    transactions transaction;
    bankaccount bank_account;
    int wallet , sender_wallet_before, receiver_wallet_before;
    user user = USERS[current_user_id];
    transactions_count++;
    transaction.id = transactions_count;
    transaction.SenderAccount = user;
    transaction.ReceiverAccount = user;
    // get the current date
    transaction.date_transaction.year = now->tm_year + 1900;
    transaction.date_transaction.month = now->tm_mon + 1;
    transaction.date_transaction.day = now->tm_mday;
    wallet = USERS[current_user_id].wallet;
    bank_account = USERS[current_user_id].accounts[current_bank];
    //transaction page GUI
    form transaction_window{ API::make_center(800,600), appearance(true, true, true, false, true, false, false) };
    transaction_window.bgcolor(color(211, 211, 211));
    transaction_window.caption("add funds");
    label cur_ban{ transaction_window,"Enter Bank number: " };
    cur_ban.move(rectangle(250, 150, 110, 17));
    cur_ban.show();
    textbox bank_num{ transaction_window,rectangle(250, 200, 300, 30) };
    bank_num.editable(true);
    bank_num.typeface(paint::font("Arial", 12));
    bank_num.multi_lines(false);
    bank_num.show();
    label Ammount{ transaction_window,"Enter Ammount: " };
    Ammount.move(rectangle(250, 150, 110, 17));
    Ammount.hide();
    textbox money_ammount{ transaction_window,rectangle(250, 200, 300, 30) };
    money_ammount.editable(true);
    money_ammount.typeface(paint::font("Arial", 12));
    money_ammount.multi_lines(false);
    money_ammount.hide();
    label state{ transaction_window,"initial text" };
    state.move(rectangle(250, 150, 200, 17));
    state.hide();
    label error2{ transaction_window,"Insuffecient funds" };
    error2.move(rectangle(250, 170, 200, 17));
    error2.hide();
    button enter_ammount{ transaction_window, "Confirm" };
    enter_ammount.move(rectangle(250, 300, 150, 40));
    enter_ammount.hide();
    // button to return to dashboard
    button close{ transaction_window,"Return to dashboard" };
    close.move(rectangle(380, 300, 150, 40));
    close.events().click([&]
        {
            transaction_window.close();
            dashboard(USERS);
        });
    button to_wallet{ transaction_window,"to wallet" };
    to_wallet.move(rectangle(150, 300, 150, 40));
    to_wallet.hide();
    button to_bank{ transaction_window,"to bank account" };
    to_bank.move(rectangle(330, 300, 150, 40));
    to_bank.hide();
    button confirm_ban_num{ transaction_window,"confirm" };
    confirm_ban_num.move(rectangle(250, 300, 130, 40));
    confirm_ban_num.events().click([&]
        {
            bool valid_bank_num = false;
            try
            {
                current_bank = stoi(bank_num.text());
                current_bank--;
                valid_bank_num = true;
            }
            catch (const exception& e)
            {
                cerr << e.what();
                valid_bank_num = false;
                form popup(nana::API::make_center(400, 200), appearance(true, true, true, false, true, false, false));
                popup.caption("ERROR!!!");
                label error1{ popup, "Invalid input, input must be a number (1 -> 3)." };
                error1.move(rectangle(180, 100, 110, 17));
                button close{ popup, "Close" };
                close.move(rectangle(250, 210, 100, 30));
                close.events().click([&popup]
                    {
                        popup.close();
                    });
                // Show the popup as modal (blocks other interaction until closed)
                popup.modality();
            }
            if (valid_bank_num && current_bank >= 0 && current_bank <= 2)
            {
                close.move(rectangle(500, 300, 150, 40));
                confirm_ban_num.hide();
                bank_num.close();
                cur_ban.close();
                Ammount.show();
                money_ammount.show();
                enter_ammount.show();
                enter_ammount.events().click([&]
                    {
                        //validate user input
                        bool valid = false;
                        try
                        {
                            transaction.ammount = stoi(money_ammount.text());
                            valid = true;
                        }
                        catch (const exception& e)
                        {
                            valid = false;
                            cerr << e.what();
                            form popup(nana::API::make_center(400, 200), appearance(true, true, true, false, true, false, false));
                            popup.caption("ERROR!!!");
                            label error1{ popup, "Invalid input, input must be a number." };
                            error1.move(rectangle(180, 100, 110, 17));
                            button close{ popup, "Close" };
                            close.move(rectangle(250, 210, 100, 30));
                            close.events().click([&popup]
                                {
                                    popup.close();
                                });
                            // Show the popup as modal (blocks other interaction until closed)
                            popup.modality();
                        }
                        if (valid)
                        {
                            to_wallet.show();
                            to_bank.show();
                            enter_ammount.hide();
                            to_wallet.events().click([&]
                                {
                                    to_wallet.hide();
                                    to_bank.hide();
                                    enter_ammount.hide();
                                    receiver_wallet_before = user.wallet;
                                    sender_wallet_before = user.accounts[current_bank].amount;
                                    // if ammount is invalid, transaction fails
                                    if (transaction.ammount > sender_wallet_before)
                                    {
                                        transaction.status = -1;
                                        error2.show();
                                    }
                                    else
                                    {
                                        transaction.SenderAccount.accounts[current_bank].amount -= transaction.ammount;
                                        transaction.ReceiverAccount.wallet += transaction.ammount;
                                        // check if the balance of both the sender and reciever have changed correctly or no
                                        if (((sender_wallet_before - transaction.SenderAccount.accounts[current_bank].amount) == transaction.ammount) && ((transaction.ReceiverAccount.wallet - receiver_wallet_before) == transaction.ammount))
                                        {
                                            transaction.status = 1;
                                        }
                                        // if one of them is still pending change
                                        else if (transaction.SenderAccount.accounts[current_bank].amount == sender_wallet_before || transaction.ReceiverAccount.wallet == receiver_wallet_before)
                                        {
                                            transaction.status = 0;
                                        }
                                        // if the transaction failed
                                        else
                                        {
                                            transaction.status = -1;
                                        }
                                    }
                                    Ammount.hide();
                                    money_ammount.hide();
                                    if (transaction.status == 1)
                                    {
                                        state.caption("Money transfer is complete");
                                        state.show();
                                    }
                                    else if (transaction.status == 0)
                                    {
                                        state.caption("Money transfer is pending");
                                        state.show();
                                    }
                                    else
                                    {
                                        state.caption("Money transfer failed");
                                        state.show();
                                    }
                                    state.move(rectangle(300, 150, 200, 17));
                                    //add to TRANSACTIONS vector
                                    transactions_count++;
                                    TRANSACTIONS.insert(TRANSACTIONS.begin(), { transaction.SenderAccount,transaction.ReceiverAccount,transaction.date_transaction,transaction.id,transaction.ammount,transaction.status });
                                    USERS[transaction.SenderAccount.id].accounts[current_bank].amount = transaction.SenderAccount.accounts[current_bank].amount;
                                    USERS[transaction.ReceiverAccount.id].wallet = transaction.ReceiverAccount.wallet;
                                });
                            to_bank.events().click([&]
                                {
                                    to_bank.show();
                                    to_wallet.show();
                                    enter_ammount.hide();
                                    sender_wallet_before = user.wallet;
                                    receiver_wallet_before = user.accounts[current_bank].amount;
                                    // if ammount is invalid, transaction fails
                                    if (transaction.ammount > user.wallet)
                                    {
                                        transaction.status = -1;
                                        error2.show();
                                    }
                                    else
                                    {
                                        transaction.SenderAccount.wallet -= transaction.ammount;
                                        transaction.ReceiverAccount.accounts[current_bank].amount += transaction.ammount;
                                        // check if the balance of both the sender and reciever have changed correctly or no
                                        if (((sender_wallet_before - transaction.SenderAccount.wallet) == transaction.ammount) && ((transaction.ReceiverAccount.accounts[current_bank].amount - receiver_wallet_before) == transaction.ammount))
                                        {
                                            transaction.status = 1;
                                        }
                                        // if one of them is still pending change
                                        else if (transaction.SenderAccount.wallet == sender_wallet_before || transaction.ReceiverAccount.accounts[current_bank].amount == receiver_wallet_before)
                                        {
                                            transaction.status = 0;
                                        }
                                        // if the transaction failed
                                        else
                                        {
                                            transaction.status = -1;
                                        }
                                    }
                                    Ammount.hide();
                                    money_ammount.hide();
                                    if (transaction.status == 1)
                                    {
                                        state.caption("Money transfer is complete");
                                        state.show();
                                    }
                                    else if (transaction.status == 0)
                                    {
                                        state.caption("Money transfer is pending");
                                        state.show();
                                    }
                                    else
                                    {
                                        state.caption("Money transfer failed");
                                        state.show();
                                    }
                                    state.move(rectangle(300, 150, 200, 17));
                                    //add to TRANSACTIONS vector
                                    transactions_count++;
                                    TRANSACTIONS.insert(TRANSACTIONS.begin(), { transaction.SenderAccount,transaction.ReceiverAccount,transaction.date_transaction,transaction.id,transaction.ammount,transaction.status });
                                    USERS[transaction.ReceiverAccount.id].accounts[current_bank].amount = transaction.SenderAccount.accounts[current_bank].amount;
                                    USERS[transaction.SenderAccount.id].wallet = transaction.ReceiverAccount.wallet;
                                });
                        }
                    });
            }
            });
                transaction_window.show();
                exec();
        }

void trans_history(vector<user> users, vector<transactions> transaction) // wafaey, help from omar and abdelrahman
{
    form trns_his(API::make_center(800, 600), appearance(true, true, true, false, true, false, false));
    trns_his.caption("Transaction history");
    trns_his.bgcolor(color(211, 211, 211));
    bool swapped = false;
    int n = TRANSACTIONS.size();
    string trns_history_display = "", status;
    for (int i = 0; i < n; i++)
    {
        if (transaction[i].SenderAccount.id == current_user_id || transaction[i].ReceiverAccount.id == current_user_id || current_user_id == 0)
        {
            if (transaction[i].status == 1)
            {
                status = "success";
            }
            else if (transaction[i].status == 0)
            {
                status = "pending";
            }
            else
            {
                status = "failed";
            }
            string DATE = to_string(transaction[i].date_transaction.day) + "/" + to_string(transaction[i].date_transaction.month) + "/" + to_string(transaction[i].date_transaction.year);
            trns_history_display += "Sender: " + transaction[i].SenderAccount.name + " Amount: " + to_string(transaction[i].ammount) + " Receiver: " + transaction[i].ReceiverAccount.name + " date: " + DATE + " Status " + status + "\n";
        }
    }
    label show_history{ trns_his, trns_history_display };
    show_history.move(rectangle(100, 10, 550, 500));
    show_history.show();
    combox dropdown{ trns_his,"filter" };
    dropdown.push_back("Filter by Date");
    dropdown.push_back("Filter by Ammount");
    dropdown.push_back("Filter by Status");
    dropdown.move(rectangle(700, 10, 100, 17));
    dropdown.show();
    dropdown.events().selected([&]()
        {
            trns_history_display = "";
            switch (dropdown.option())
            {
            case 0:
                for (size_t i = 0; i < n - 1; ++i)
                {
                    swapped = false;
                    for (size_t j = 0; j < n - i - 1; ++j) {
                        if (transaction[j].date_transaction.year > transaction[j + 1].date_transaction.year)
                        {
                            if (transaction[j].date_transaction.month > transaction[j + 1].date_transaction.month)
                            {
                                if (transaction[j].date_transaction.day > transaction[j + 1].date_transaction.day)
                                {
                                    swap(transaction[j], transaction[j + 1]);
                                    swapped = true;
                                }
                            }
                        }
                    }
                    if (!swapped) break;
                }
                for (int i = 0; i < n; i++)
                {
                    if (transaction[i].SenderAccount.id == current_user_id || transaction[i].ReceiverAccount.id == current_user_id || current_user_id == 0)
                    {
                        if (transaction[i].status == 1)
                        {
                            status = "success";
                        }
                        else if (transaction[i].status == 0)
                        {
                            status = "pending";
                        }
                        else
                        {
                            status = "failed";
                        }
                        string DATE = to_string(transaction[i].date_transaction.day) + "/" + to_string(transaction[i].date_transaction.month) + "/" + to_string(transaction[i].date_transaction.year);
                        trns_history_display += " Sender: " + transaction[i].SenderAccount.name + " Amount: " + to_string(transaction[i].ammount) + " Receiver: " + transaction[i].ReceiverAccount.name + " date: " + DATE + " Status " + status + "\n";
                    }
                }
                show_history.caption(trns_history_display);
                show_history.show();
                break;
            case 1:
                //bubble sort according to greater ammount of money transferred
                for (size_t i = 0; i < n - 1; ++i)
                {
                    swapped = false;
                    for (size_t j = 0; j < n - i - 1; ++j) {
                        if (transaction[j].ammount < transaction[j + 1].ammount)
                        {
                            swap(transaction[j], transaction[j + 1]);
                            swapped = true;
                        }
                    }
                    if (!swapped) break;
                }
                for (int i = 0; i < n; i++)
                {
                    if (transaction[i].SenderAccount.id == current_user_id || transaction[i].ReceiverAccount.id == current_user_id || current_user_id == 0)
                    {
                        if (transaction[i].status == 1)
                        {
                            status = "success";
                        }
                        else if (transaction[i].status == 0)
                        {
                            status = "pending";
                        }
                        else
                        {
                            status = "failed";
                        }
                        string DATE = to_string(transaction[i].date_transaction.day) + "/" + to_string(transaction[i].date_transaction.month) + "/" + to_string(transaction[i].date_transaction.year);
                        trns_history_display += " Sender: " + transaction[i].SenderAccount.name + " Amount: " + to_string(transaction[i].ammount) + " Receiver: " + transaction[i].ReceiverAccount.name + " date: " + DATE + " Status " + status + "\n";
                    }
                }
                show_history.caption(trns_history_display);
                show_history.show();
                break;
            case 2:
                for (size_t i = 0; i < n - 1; ++i)
                {
                    swapped = false;
                    for (size_t j = 0; j < n - i - 1; ++j) {
                        if (transaction[j].status < transaction[j + 1].status)
                        {
                            swap(transaction[j], transaction[j + 1]);
                            swapped = true;
                        }
                    }
                    if (!swapped) break;
                }
                for (int i = 0; i < n; i++)
                {
                    if (transaction[i].SenderAccount.id == current_user_id || transaction[i].ReceiverAccount.id == current_user_id || current_user_id == 0)
                    {
                        if (transaction[i].status == 1)
                        {
                            status = "success";
                        }
                        else if (transaction[i].status == 0)
                        {
                            status = "pending";
                        }
                        else
                        {
                            status = "failed";
                        }
                        string DATE = to_string(transaction[i].date_transaction.day) + "/" + to_string(transaction[i].date_transaction.month) + "/" + to_string(transaction[i].date_transaction.year);
                        trns_history_display += " Sender: " + transaction[i].SenderAccount.name + " Amount: " + to_string(transaction[i].ammount) + " Receiver: " + transaction[i].ReceiverAccount.name + " date: " + DATE + " Status " + status + "\n";
                    }
                }
                show_history.caption(trns_history_display);
                show_history.show();
                break;
            }
        });
    show_history.show();
    trns_his.show();
    button goback_btn{ trns_his,"go back" };
    goback_btn.move(rectangle(30, 500, 50, 40));
    goback_btn.events().click([&] {

        if (current_user_id == 0)
        {
            trns_his.close();
            admin_work();
        }
        else {
            trns_his.close();
            dashboard(USERS);
        }});
    exec();
}

void managebankacc(vector<user> users) //made by omar and khaled
{
    form manbank{ API::make_center(1000, 300), appearance(true, true, true, false, true, false, false) };
    manbank.caption("Manage Bank Accounts");
    button bankacc1{ manbank, "Edit" };
    bankacc1.move(rectangle(900, 30, 100, 40));
    button bankacc2{ manbank, "Edit" };
    bankacc2.move(rectangle(900, 70, 100, 40));
    button bankacc3{ manbank, "Edit" };
    bankacc3.move(rectangle(900, 110, 100, 40));
    textbox bank1_name{ manbank };
    bank1_name.move(rectangle(50, 30, 200, 40));
    textbox bank2_name{ manbank };
    bank2_name.move(rectangle(50, 70, 200, 40));
    textbox bank3_name{ manbank };
    bank3_name.move(rectangle(50, 110, 200, 40));
    textbox bank1_amount{ manbank };
    bank1_amount.move(rectangle(650, 30, 200, 40));
    textbox bank2_amount{ manbank };
    bank2_amount.move(rectangle(650, 70, 200, 40));
    textbox bank3_amount{ manbank };
    bank3_amount.move(rectangle(650, 110, 200, 40));
    textbox bank1_accnum{ manbank };
    bank1_accnum.move(rectangle(350, 30, 200, 40));
    textbox bank2_accnum{ manbank };
    bank2_accnum.move(rectangle(350, 70, 200, 40));
    textbox bank3_accnum{ manbank };
    bank3_accnum.move(rectangle(350, 110, 200, 40));
    bank1_amount.editable(false);
    bank2_amount.editable(false);
    bank3_amount.editable(false);

    label bankname{ manbank, "Bank Name:" };
    bankname.move(rectangle(50, 5, 300, 20));
    label bankamount{ manbank, "Bank Amount:" };
    bankamount.move(rectangle(650, 5, 300, 20));
    label bankaccnum{ manbank, "Bank Account Num:" };
    bankaccnum.move(rectangle(350, 5, 300, 20));

    button backbtn{ manbank, "Back" };
    backbtn.move(rectangle(450, 160, 100, 20));

    backbtn.events().click([&] {
        manbank.close();
        dashboard(USERS);
        });

    bank1_name.caption(USERS[current_user_id].accounts[0].name);
    bank2_name.caption(USERS[current_user_id].accounts[1].name);
    bank3_name.caption(USERS[current_user_id].accounts[2].name);
    bank1_amount.caption(to_string(USERS[current_user_id].accounts[0].amount));
    bank2_amount.caption(to_string(USERS[current_user_id].accounts[1].amount));
    bank3_amount.caption(to_string(USERS[current_user_id].accounts[2].amount));
    bank1_accnum.caption(to_string(USERS[current_user_id].accounts[0].accountnum));
    bank2_accnum.caption(to_string(USERS[current_user_id].accounts[1].accountnum));
    bank3_accnum.caption(to_string(USERS[current_user_id].accounts[2].accountnum));

    bankacc1.events().click([&] {
        if (bank1_name.text() == USERS[current_user_id].accounts[0].name)
        {
            bank1_name.caption(USERS[current_user_id].accounts[0].name);
            bank1_accnum.caption(to_string(USERS[current_user_id].accounts[0].accountnum));
            bankaccnum.caption("Bank Account Num : Error, Must change both fields.");

        }
        else if (bank1_accnum.text() == to_string(USERS[current_user_id].accounts[0].accountnum))
        {
            bank1_name.caption(USERS[current_user_id].accounts[0].name);
            bank1_accnum.caption(to_string(USERS[current_user_id].accounts[0].accountnum));
            bankname.caption("Bank Name : Error, Must change both fields.");
        }
        else
        {
            srand(std::time(0));
            bank1_amount.caption(to_string((rand() % 10000) + (rand() % 1000)));

            bankname.caption("Bank Name :");
            bankaccnum.caption("Bank Account Num :");
            if (bank1_accnum.text() == "" || bank1_name.text() == "")
            {
                USERS[current_user_id].accounts[0].accountnum = 0;
                USERS[current_user_id].accounts[0].name = "";
                USERS[current_user_id].accounts[0].amount = 0;
                bank1_name.caption("");
                bank1_accnum.caption("");
                bank1_amount.caption("0");

            }
            else {
                USERS[current_user_id].accounts[0].accountnum = stoi(bank1_accnum.text());
                USERS[current_user_id].accounts[0].name = bank1_name.text();
                USERS[current_user_id].accounts[0].amount = stoi(bank1_amount.text());
            }
        }
        });
    bankacc2.events().click([&] {
        if (bank2_name.text() == USERS[current_user_id].accounts[1].name)
        {
            bank2_name.caption(USERS[current_user_id].accounts[1].name);
            bank2_accnum.caption(to_string(USERS[current_user_id].accounts[1].accountnum));
            bankname.caption("Bank Name : Error, Must change both fields.");

        }
        else if (bank2_accnum.text() == to_string(USERS[current_user_id].accounts[1].accountnum))
        {
            bank2_name.caption(USERS[current_user_id].accounts[1].name);
            bank2_accnum.caption(to_string(USERS[current_user_id].accounts[1].accountnum));
            bankaccnum.caption("Bank Account Num : Error, Must change both fields.");
        }
        else
        {
            srand(std::time(0));
            bank2_amount.caption(to_string((rand() % 10000) + (rand() % 1000)));

            bankname.caption("Bank Name :");
            bankaccnum.caption("Bank Account Num :");
            if (bank2_accnum.text() == "" || bank2_name.text() == "")
            {
                USERS[current_user_id].accounts[1].accountnum = 0;
                USERS[current_user_id].accounts[1].name = "";
                USERS[current_user_id].accounts[1].amount = 0;
                bank2_name.caption("");
                bank2_accnum.caption("");
                bank2_amount.caption("0");

            }
            else {
                USERS[current_user_id].accounts[1].accountnum = stoi(bank2_accnum.text());
                USERS[current_user_id].accounts[1].name = bank2_name.text();
                USERS[current_user_id].accounts[1].amount = stoi(bank2_amount.text());
            }
        }
        });
    bankacc3.events().click([&] {
        if (bank3_name.text() == USERS[current_user_id].accounts[2].name)
        {
            bank3_name.caption(USERS[current_user_id].accounts[2].name);
            bank3_accnum.caption(to_string(USERS[current_user_id].accounts[2].accountnum));
            bankname.caption("Bank Name : Error, Must change both fields.");

        }
        else if (bank3_accnum.text() == to_string(USERS[current_user_id].accounts[2].accountnum))
        {
            bank3_name.caption(USERS[current_user_id].accounts[2].name);
            bank3_accnum.caption(to_string(USERS[current_user_id].accounts[2].accountnum));
            bankaccnum.caption("Bank Account Num : Error, Must change both fields.");
        }
        else
        {
            srand(std::time(0));
            bank3_amount.caption(to_string((rand() % 10000) + (rand() % 1000)));

            bankname.caption("Bank Name :");
            bankaccnum.caption("Bank Account Num :");
            if (bank3_accnum.text() == "" || bank3_name.text() == "")
            {
                USERS[current_user_id].accounts[2].accountnum = 0;
                USERS[current_user_id].accounts[2].name = "";
                USERS[current_user_id].accounts[2].amount = 0;
                bank3_name.caption("");
                bank3_accnum.caption("");
                bank3_amount.caption("0");

            }
            else {
                USERS[current_user_id].accounts[2].accountnum = stoi(bank3_accnum.text());
                USERS[current_user_id].accounts[2].name = bank3_name.text();
                USERS[current_user_id].accounts[2].amount = stoi(bank3_amount.text());
            }
        }
        });
    button trans{ manbank, "trans money to wallet/bank"};
    trans.move(rectangle(800,250,200,20));
    trans.events().click([&] 
        {
            manbank.close();
            trans_wallet();
        });
    manbank.show();
    exec();
}

void dashboard(vector<user> users)//made by whole team
{
    form dashboard{ API::make_center(800,400), appearance(true, true, true, false, true, false, false) };
    dashboard.caption("Dashboard");

    button logout_btn{ dashboard,"log out" };
    logout_btn.move(rectangle(30, 350, 50, 40));
    logout_btn.events().click([&] {
        dashboard.close();
        land_page(); });

    button managebanks_btn{ dashboard, "Manage Bank Accounts" };
    managebanks_btn.move(rectangle(160, 120, 200, 40));
    managebanks_btn.events().click([&] {
        dashboard.close();
        managebankacc(USERS);
        });
    button profile_btn{ dashboard, "Profile" };
    profile_btn.move(rectangle(440, 120, 200, 40));
    button tr_btn{ dashboard, "Send Money" };
    tr_btn.move(rectangle(160, 240, 200, 40));
    bool tempbool = false;
    tr_btn.events().click([&dashboard, &tempbool]
        {


            if (!tempbool)
            {
                // Create Transaction form
                form poptrans{ API::make_center(400, 450), appearance(true, true, true, false, true, false, false) };
                poptrans.caption("Transaction");

                // Label to display the OTP (simulating sending it to the user)
                label trans_label{ poptrans, "Reciever: " };
                trans_label.move(rectangle(20, 20, 400, 30));

                // Textbox for user to input OTP
                textbox user_input{ poptrans, rectangle(20, 40, 360, 20) };
                user_input.multi_lines(false);
                user_input.tip_string("Enter user whom you wish to send money to");

                label date_label{ poptrans, "Date of transaction: (Choose today's date for instant transaction)" };
                date_chooser date_choose{ poptrans, rectangle(20, 100, 360, 280) };
                date_label.move(rectangle(20, 80, 500, 20));

                 // Verify button
                button send_btn{ poptrans, "Confirm" };
                send_btn.move(rectangle(150, 400, 100, 30));
                poptrans.show();
                tempbool = true;
                poptrans.events().destroy([&tempbool]
                    {
                        tempbool = false;
                    });

                send_btn.events().click([&user_input, &trans_label, &dashboard, &poptrans, &date_choose]
                    {
                        int d = date_choose.read().read().day;
                        int m = date_choose.read().read().month;
                        int y = date_choose.read().read().year;
                        bool temp = false;
                        string rec = user_input.text();
                        for (int i = 0; i < USERS.size(); i++)
                        {
                            if (USERS[i].name == rec)
                            {
                                if (USERS[current_user_id].id == i)
                                {
                                    trans_label.caption("Reciever: ERROR, can't send money to yourself.");
                                    temp = true;
                                }
                                else if (now->tm_year + 1900 > y)
                                {
                                    trans_label.caption("Reciever: ERROR, can't send money in the past.");
                                    temp = true;
                                }
                                else if (now->tm_mon + 1 > m)
                                {
                                    trans_label.caption("Reciever: ERROR, can't send money in the past.");
                                    temp = true;
                                }
                                else if (now->tm_mday > d)
                                {
                                    trans_label.caption("Reciever: ERROR, can't send money in the past.");
                                    temp = true;
                                }
                                else
                                {
                                    temp = true;
                                    dashboard.close();
                                    poptrans.close();
                                    transaction(USERS[current_user_id], USERS[i], d, m, y);

                                }
                            }
                        }
                        if (!temp) {
                            trans_label.caption("Reciever: ERROR, user doesn't exist.");
                        }
                    });
                exec();
            }
        });

    profile_btn.events().click([&dashboard]
        {
            dashboard.close();
            edit_profile(USERS);
        });

    button trh_btn{ dashboard, "Transaction History" };
    trh_btn.move(rectangle(440, 240, 200, 40));
    trh_btn.events().click([&dashboard]
        {
            dashboard.close();
            trans_history(USERS, TRANSACTIONS);
        });
    dashboard.show();
    exec();
}
void admin_work() { // made by: shehta brothers
    // Main Form
    form adminForm{ API::make_center(800,600), appearance(true, true, true, false, true, false, false) };
    adminForm.caption("Admin Panel");

    label title{ adminForm, "Admin Functions:" }, space1_admin_lbl{ adminForm, "----------------------------------------------------------------------------" },
        space2_admin_lbl{ adminForm, "----------------------------------------------------------------------------" };
    paint::font title_font{ "Times New Roman", 20 };
    space1_admin_lbl.move(rectangle(200, 0, 400, 20));
    space2_admin_lbl.move(rectangle(200, 50, 400, 40));
    title.move(rectangle(300, 20, 200, 40));
    title.typeface(title_font);
    button btnViewProfiles{ adminForm, "View Profiles" };
    btnViewProfiles.move(rectangle(300, 150, 200, 40));
    button btnSuspendAccount{ adminForm, "Suspend Account" };
    btnSuspendAccount.move(rectangle(300, 200, 200, 40));
    btnSuspendAccount.events().click([&] {
        adminForm.close();
        suspendaccount();
        });
    button btnMonitorTransactions{ adminForm, "Monitor Transactions" };
    btnMonitorTransactions.move(rectangle(300, 250, 200, 40));
    btnMonitorTransactions.events().click([&] {
        adminForm.close();
        trans_history(USERS,TRANSACTIONS);
        });
    button btnGenerateReports{adminForm, "Generate Reports"};
    btnGenerateReports.move(rectangle(300, 300, 200, 40));
    btnGenerateReports.events().click([&] {
        adminForm.close();
        Generate_Report();
        });
    btnViewProfiles.events().click([&] {
        adminForm.close();
        show_users();
        });

    button logout{ adminForm, "Logout" };
    logout.move(rectangle(650,450,100,40));

    logout.events().click([&] {
        adminForm.close();
        land_page();
        });
    
    adminForm.show();
    exec();
}

void show_users() //made by yousef shehta, edited by omar
{
    form show{ API::make_center(800,600), appearance(true, true, true, false, true, false, false) };
    show.caption("Show User accounts");
    label profilesTitle{ show, "User Profiles:" };
    profilesTitle.move(rectangle(350, 10, 200, 30));
    paint::font titleFont{ "Times New Roman", 16, true };
    profilesTitle.typeface(titleFont);

    // Header
    label lblHeader{ show, "ID        Name          Email                      Phone Number        Wallet         Bank Accounts" };
    lblHeader.move(rectangle(50, 50, 800, 30));
    paint::font headerFont{ "Times New Roman", 14, true };
    lblHeader.typeface(headerFont);
    int y_spacing = 90;
    vector<label> labels;
    for (int i = 1; i < USERS.size(); i++)
    {
        auto* ID = new label(show, to_string(USERS[i].id)); // Dynamically allocate memory
        ID->move(rectangle(50, y_spacing, 120, 80)); // Use pointer
        auto* Name = new label(show, USERS[i].name);
        Name->move(rectangle(100, y_spacing, 120, 80));
        auto* Email = new label(show, USERS[i].email);
        Email->move(rectangle(200, y_spacing, 150, 80));
        auto* Phone_number = new label(show,(USERS[i].Phonenumber));
        Phone_number->move(rectangle(380, y_spacing, 100, 50));
        auto* wallet = new label(show, to_string(USERS[i].wallet));
        wallet->move(rectangle(530, y_spacing, 120, 80));
        for (int j = 0; j < 3; j++)
        {
            string temp = USERS[i].accounts[j].name + "/" + to_string(USERS[i].accounts[j].accountnum) + "/" + to_string(USERS[i].accounts[j].amount) + " EGP";
            auto* Bank = new label(show, temp);
            Bank->move(rectangle(620, y_spacing, 150, 80));
            y_spacing += 20;
        }
    }
    
    button bck{ show, "Back" };
    bck.move(rectangle(650, 450, 100, 40));
    bck.events().click([&] {
        show.close();
        admin_work();
        });

    show.show();
    exec();
}

void suspendaccount()
{
    form sus{ API::make_center(800,600), appearance(true, true, true, false, true, false, false) };
    sus.caption("Suspend User");

    sus.show();

    textbox txt{ sus, "Insert ID of user"};
    txt.move(rectangle(350,250,100,30));

    button btn{sus, "SUSPEND"};
    btn.move(rectangle(350,350, 100, 40));

    button btn1{ sus, "UNSUSPEND" };
    btn1.move(rectangle(350, 450, 100, 40));

    label zalbl(sus, rectangle(355, 200, 100, 50));
    zalbl.caption("enter ID of user");
    btn.events().click([&] {

        bool error = false;
        int x = -1000;
        try
        {
            x = stoi(txt.text());
            error = false;
        }
        catch (const exception& e)
        {
            error = true;
            cerr << e.what();
            form popup(nana::API::make_center(400, 200), appearance(true, true, true, false, true, false, false));
            popup.caption("ERROR!!!");
            label error{ popup, "Invalid ID, input must be an integer." };
            error.move(rectangle(180, 100, 110, 17));
            button close{ popup, "Close" };
            close.move(rectangle(250, 210, 100, 30));
            close.events().click([&popup]
                {
                    popup.close();
                });
            // Show the popup as modal (blocks other interaction until closed)
            popup.modality();
        }
        
        if (x <= (USERS.size() - 1) && x > 0 && !error)
        {
            USERS[x].flag = true;
            msgbox msg(sus, "SUSPENDED");
            msg << "USER " << USERS[x].name << " HAS BEEN SUSPENDED.";
            msg.show();
        }
        else {
            msgbox msg(sus, "ERROR");
            msg << "USER NOT FOUND.";
            msg.show();
        }
        
        });
    btn1.events().click([&] {

        bool error = false;
        int x = -1000;
        try
        {
            x = stoi(txt.text());
            error = false;
        }
        catch (const exception& e)
        {
            error = true;
            cerr << e.what();
            form popup(nana::API::make_center(400, 200), appearance(true, true, true, false, true, false, false));
            popup.caption("ERROR!!!");
            label error{ popup, "Invalid ID, input must be an integer." };
            error.move(rectangle(180, 100, 110, 17));
            button close{ popup, "Close" };
            close.move(rectangle(250, 210, 100, 30));
            close.events().click([&popup]
                {
                    popup.close();
                });
            // Show the popup as modal (blocks other interaction until closed)
            popup.modality();
        }

        if (x <= (USERS.size() - 1) && x > 0 && !error)
        {
            USERS[x].flag = false;
            msgbox msg(sus, "UNSUSPENDED");
            msg << "USER " << USERS[x].name << " HAS BEEN UNSUSPENDED.";
            msg.show();
        }
        else {
            msgbox msg(sus, "ERROR");
            msg << "USER NOT FOUND.";
            msg.show();
        }

        });

    button back{ sus, "back" };
    back.move(rectangle(650, 450, 100, 40));

    back.events().click([&] {
        sus.close();
        admin_work();
        });

    exec();
}

void Generate_Report()
{
    form Report{ API::make_center(1100,800), appearance(true, true, true, false, true, false, false) };
    Report.caption("Generate Reports");
    button back{ Report, "back" };
    back.move(rectangle(550, 450, 100, 40));
    back.events().click([&] {
        Report.close();
        admin_work();
        });
    Report.show();

    label space1_Report_lbl{ Report, "----------------------------------------------------------------------------" },
        space2_Report_lbl{ Report, "----------------------------------------------------------------------------" }, report{ Report, "Generate Reports" };
    paint::font title_font{ "Times New Roman", 20 };
    space1_Report_lbl.move(rectangle(200, 0, 400, 20));
    space2_Report_lbl.move(rectangle(200, 50, 400, 40));
    report.move(rectangle(500, 15, 200, 40));
    report.typeface(title_font);

    label lblHeader{ Report, "ID       Name           Email                           Phone Number       Wallet             Bank Accounts                                                               Transactions" };
    lblHeader.move(rectangle(10, 70, 800, 30));

    int y_spacing = 100;
    for (int i = 1; i < USERS.size(); i++)
    {
        auto* ID = new label(Report, to_string(USERS[i].id));
        ID->move(rectangle(10, y_spacing, 120, 80));
        auto* Name = new label(Report, USERS[i].name);
        Name->move(rectangle(35, y_spacing, 120, 80));
        auto* Email = new label(Report, USERS[i].email);
        Email->move(rectangle(80, y_spacing, 150, 80));
        auto* Phone_number = new label(Report, (USERS[i].Phonenumber));
        Phone_number->move(rectangle(230, y_spacing, 100, 50));
        auto* wallet = new label(Report, to_string(USERS[i].wallet));
        wallet->move(rectangle(320, y_spacing, 120, 80));

        // Display bank accounts
        for (int j = 0; j < 3; j++)
        {

            string temp = USERS[i].accounts[j].name + "/" + to_string(USERS[i].accounts[j].accountnum) + "/" + to_string(USERS[i].accounts[j].amount) + " EGP";
            auto* Bank = new label(Report, temp);
            Bank->move(rectangle(375, y_spacing, 150, 80));
            y_spacing += 15;
        }

        // Display transactions
        for (const auto& transaction : TRANSACTIONS)
        {
            if (transaction.SenderAccount.id == USERS[i].id || transaction.ReceiverAccount.id == USERS[i].id)
            {
                string status;
                if (transaction.status == 1)
                {
                    status = "success";
                }
                else if (transaction.status == 0)
                {
                    status = "pending";
                }
                else
                {
                    status = "failed";
                }
                string DATE = to_string(transaction.date_transaction.day) + "/" + to_string(transaction.date_transaction.month) + "/" + to_string(transaction.date_transaction.year);
                string transaction_info = "Sender: " + transaction.SenderAccount.name + " Amount: " + to_string(transaction.ammount) + " Receiver: " + transaction.ReceiverAccount.name + " Date: " + DATE + " Status: " + status;
                auto* Transaction_Label = new label(Report, transaction_info);
                Transaction_Label->move(rectangle(500, y_spacing, 800, 30));
                y_spacing += 20;
            }
        }
        y_spacing += 20; // Additional spacing between users
    }
    exec();
}
