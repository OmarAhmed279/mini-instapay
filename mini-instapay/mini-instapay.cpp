
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING 1 //this is so it doesn't crash

#include "mini-instapay.h" //this has all the header files
#include <regex>
using namespace std;
using namespace nana;
//Global Variables

static int user_count = 0, transactions_count = 0;

// Functions Declaration
void land_page();
void create_user();
void user_login(string, string, form&, label&, label&);
void main_menu();
void OTP_verification(form&, string, string, string, string);
void dashboard();
void transaction(user, user);

// create banckaccount struct
struct bankaccount {
    string name;
    int amount;
    int accountnum;
};

// create user structure
struct user {
    string  name, email, password;
    bankaccount accounts;
    int id, Phonenumber, wallet = 0;
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
// Data Arrays for Storage
vector<user> USERS = {
    {"TheGoat123", "TheGoat123@hotmail.com", "123goat", {"CIB", 5, 123456789}, 1, 123456789, 10},
    {"3am Ahmed", "3amAhmed89@yahoo.com", "Ahmed89", {"Bank Misr", 100000, 123 }, 2, 201148454, 100000000},
    {"Admin", "Admin", "Admin@123", {}, 0, 0, 0}
};



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
void create_user() // made by youssef shehta and seif shehta
{
    regex Name_pattern("^[A-Za-z ]{3,20}$");
    regex Email_pattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,63}$)");
    std::regex pnumber_pattern("^(011|012|010|015)[0-9]{8}$");
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
                                                                         // By 
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
    create_acc.events().click([&input_name_signup, &Name_pattern, &name_match, &input_email_signup, &Email_pattern, &email_match, &input_pnumber_signup, &pnumber_match, &pnumber_pattern,  &signup_page, &input_pass_signup]
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

void OTP_verification(form& signup_page, string name, string email, string phone, string pass)
{
        // Generate OTP
        int OTP[6];
        srand(time(nullptr)); // Seed for random OTP generation
        for (int i = 0; i < 6; ++i) {
            OTP[i] = rand() % 10;
        }

        // Convert OTP to string for display
        string otp_string;
        for (int digit : OTP) {
            otp_string +=to_string(digit);
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

            // Check if user input matches the generated OTP
            if (user_otp.size() == 6 && user_otp == otp_string) {
                feedback_label.caption("Verification successful!");
                feedback_label.fgcolor(colors::green);
                user temp = { name };
                USERS.push_back(temp);
                // Close the OTP form and proceed with signup completion
                otp_form.close();
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
    for (int i = 0; i < USERS.size(); i++)
    {
        if (USERS[i].email == e)
        {
            if (USERS[i].password == p)
            {
                landpage.close();
                dashboard();
            }
            else
            {
                pass_label.caption("Password: Wrong password, please try again.");
            }
        }
        else 
        {
            email_label.caption("Email: Wrong email, please try again.");
        }
    }
}
void main_menu()
{
    // type here
}

void transaction(user sender, user reciever) // made by wafaey
{
    transactions transaction;
    long double ammount = 0.0;
    transaction.ammount = ammount;
    int sender_wallet_before, receiver_wallet_before;
    transactions_count++;
    transaction.id = transactions_count;
    transaction.SenderAccount = sender;
    transaction.ReceiverAccount = reciever;
    sender_wallet_before = transaction.SenderAccount.wallet;
    receiver_wallet_before = transaction.ReceiverAccount.wallet;
    
    form transaction_window{ API::make_center(800,600), appearance(true, true, true, false, true, false, false) };
    transaction_window.bgcolor(color(211, 211, 211));
    transaction_window.caption("transactions");
    label Ammount{ transaction_window,"Enter Ammount: " };
    Ammount.move(rectangle(250, 150, 110, 17));
    textbox money_ammount{ transaction_window,rectangle(250, 170, 300, 30 ) };
    money_ammount.editable(true);
    money_ammount.typeface(paint::font("Arial", 12));
    money_ammount.multi_lines(false);
    button enter_ammount{ transaction_window, "Confirm"};
    enter_ammount.move(rectangle(250, 210, 100, 30));
    enter_ammount.events().click([&ammount, &money_ammount]
        {
            bool valid = false;
            while (!valid)
            {
                try
                {
                    ammount = stod(money_ammount.caption());
                }
                catch (const exception& e)
                {
                    cerr << e.what();
                    form popup(nana::API::make_center(200, 100), appearance(true, true, true, false, true, false, false));
                    popup.caption("ERROR!!!");
                    label error{ popup, "Invalid input, input must be a number." };
                    error.move(rectangle(250, 150, 110, 17));
                    button close{ popup, "Close" };
                    close.move(rectangle(250, 210, 100, 30));
                    close.events().click([&popup]
                        {
                            popup.close();
                        });
                    // Show the popup as modal (blocks other interaction until closed)
                    popup.modality();
                }
            }
        });
    // if ammount is invalid, transaction fails
    if (transaction.ammount > transaction.SenderAccount.wallet)
    {
        transaction.status = -1;
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
    label state{ transaction_window,rectangle(400,300,110, 17) };
    switch (transaction.status)
    {
    case 1:
        state.caption("Money transfer is complete.");
    case 0:
        state.caption("Transfer pending.");
    case -1:
        state.caption("Money transfer failed.");
    }
    button close{ transaction_window,"Return to dashboard" };
    close.move(rectangle(250, 210, 100, 30));
    close.events().click([&transaction_window]
        {
            transaction_window.close();
            dashboard();
        });
    transaction_window.show();
    exec();
}

void dashboard() //made by omar and abdelrahman
{
    form dashboard{ API::make_center(800,400), appearance(true, true, true, false, true, false, false) };
    dashboard.caption("Dashboard");
    button managebanks_btn{dashboard, "Manage Bank Accounts"};
    managebanks_btn.move(rectangle(160, 120, 200, 40));
    button profile_btn{ dashboard, "Profile" };
    profile_btn.move(rectangle(440, 120, 200, 40));
    button tr_btn{ dashboard, "Send Money" };
    tr_btn.move(rectangle(160, 240, 200, 40));
    tr_btn.events().click([&dashboard]
        {
            dashboard.close();
            //transaction( add sender and receiver);
        });
    button trh_btn{ dashboard, "Transaction History" };
    trh_btn.move(rectangle(440, 240, 200, 40));
    dashboard.show();
    exec();
}


