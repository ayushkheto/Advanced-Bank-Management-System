// Advanced Bank Management System
// Features:
// Create Account, Login, Deposit, Withdraw, Search,
// Update Account, Change Password, Delete Account,
// File Handling, Duplicate Account Check

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Account {
public:
    int accNo;
    string name;
    string password;
    float balance;
};

void saveAccounts(Account a[], int count){
    ofstream file("accounts.txt");
    for(int i=0;i<count;i++){
        file<<a[i].accNo<<" "<<a[i].name<<" "<<a[i].password<<" "<<a[i].balance<<endl;
    }
}

int loadAccounts(Account a[]){
    ifstream file("accounts.txt");
    int count=0;
    while(file>>a[count].accNo>>a[count].name>>a[count].password>>a[count].balance){
        count++;
    }
    return count;
}

int findAccount(Account a[], int count, int acc){
    for(int i=0;i<count;i++){
        if(a[i].accNo==acc) return i;
    }
    return -1;
}

int main(){
    Account accounts[100];
    int count = loadAccounts(accounts);
    int choice;

    do{
        cout<<"\n===== ADVANCED BANK MANAGEMENT =====\n";
        cout<<"1. Create Account\n";
        cout<<"2. Login\n";
        cout<<"3. Display Accounts\n";
        cout<<"4. Deposit\n";
        cout<<"5. Withdraw\n";
        cout<<"6. Search Account\n";
        cout<<"7. Update Name\n";
        cout<<"8. Change Password\n";
        cout<<"9. Delete Account\n";
        cout<<"10. Exit\n";
        cout<<"Choice: ";
        cin>>choice;

        switch(choice){
        case 1:{
            int acc;
            cout<<"Enter Account Number: ";
            cin>>acc;

            if(findAccount(accounts,count,acc)!=-1){
                cout<<"Account Number Already Exists!\n";
                break;
            }

            accounts[count].accNo=acc;
            cout<<"Name: ";
            cin>>accounts[count].name;
            cout<<"Password: ";
            cin>>accounts[count].password;
            cout<<"Initial Balance: ";
            cin>>accounts[count].balance;

            count++;
            saveAccounts(accounts,count);
            cout<<"Account Created!\n";
            break;
        }

        case 2:{
            int acc;
            string pass;
            cout<<"Account Number: ";
            cin>>acc;
            cout<<"Password: ";
            cin>>pass;

            int idx=findAccount(accounts,count,acc);

            if(idx!=-1 && accounts[idx].password==pass)
                cout<<"Login Successful!\n";
            else
                cout<<"Invalid Credentials!\n";
            break;
        }

        case 3:{
            for(int i=0;i<count;i++){
                cout<<"\nAcc No: "<<accounts[i].accNo;
                cout<<"\nName: "<<accounts[i].name;
                cout<<"\nBalance: "<<accounts[i].balance<<"\n";
            }
            break;
        }

        case 4:{
            int acc; float amt;
            cout<<"Account Number: ";
            cin>>acc;
            cout<<"Amount: ";
            cin>>amt;

            int idx=findAccount(accounts,count,acc);
            if(idx!=-1){
                accounts[idx].balance+=amt;
                saveAccounts(accounts,count);
                cout<<"New Balance: "<<accounts[idx].balance<<endl;
            }else cout<<"Account Not Found!\n";
            break;
        }

        case 5:{
            int acc; float amt;
            cout<<"Account Number: ";
            cin>>acc;
            cout<<"Amount: ";
            cin>>amt;

            int idx=findAccount(accounts,count,acc);
            if(idx!=-1){
                if(accounts[idx].balance>=amt){
                    accounts[idx].balance-=amt;
                    saveAccounts(accounts,count);
                    cout<<"New Balance: "<<accounts[idx].balance<<endl;
                }else cout<<"Insufficient Balance!\n";
            }else cout<<"Account Not Found!\n";
            break;
        }

        case 6:{
            int acc;
            cout<<"Account Number: ";
            cin>>acc;

            int idx=findAccount(accounts,count,acc);
            if(idx!=-1){
                cout<<"Name: "<<accounts[idx].name<<endl;
                cout<<"Balance: "<<accounts[idx].balance<<endl;
            }else cout<<"Account Not Found!\n";
            break;
        }

        case 7:{
            int acc;
            string newName;
            cout<<"Account Number: ";
            cin>>acc;

            int idx=findAccount(accounts,count,acc);
            if(idx!=-1){
                cout<<"New Name: ";
                cin>>newName;
                accounts[idx].name=newName;
                saveAccounts(accounts,count);
                cout<<"Updated!\n";
            }else cout<<"Account Not Found!\n";
            break;
        }

        case 8:{
            int acc;
            string oldPass,newPass;
            cout<<"Account Number: ";
            cin>>acc;

            int idx=findAccount(accounts,count,acc);
            if(idx!=-1){
                cout<<"Old Password: ";
                cin>>oldPass;

                if(accounts[idx].password==oldPass){
                    cout<<"New Password: ";
                    cin>>newPass;
                    accounts[idx].password=newPass;
                    saveAccounts(accounts,count);
                    cout<<"Password Changed!\n";
                }else cout<<"Wrong Password!\n";
            }
            break;
        }

        case 9:{
            int acc;
            cout<<"Account Number to Delete: ";
            cin>>acc;

            int idx=findAccount(accounts,count,acc);
            if(idx!=-1){
                for(int i=idx;i<count-1;i++)
                    accounts[i]=accounts[i+1];

                count--;
                saveAccounts(accounts,count);
                cout<<"Account Deleted!\n";
            }else cout<<"Account Not Found!\n";
            break;
        }

        case 10:
            cout<<"Goodbye!\n";
            break;

        default:
            cout<<"Invalid Choice!\n";
        }

    }while(choice!=10);

    return 0;
}
