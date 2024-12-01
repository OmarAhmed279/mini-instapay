#include <cstring>
#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

void create_user();
void user_login();
int main()
{
    // create user structure
    struct user {
        string id,name,email,password,ContactInformation,linked_bank_accounts[3];
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
    

    return 0;
}

void create_user()
{
    // type here
}

void user_login()
{
    //type here
}
