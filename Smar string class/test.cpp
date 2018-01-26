#include <iostream>
#include "mystring.hpp"
using namespace std;

int main()
{
    {
        //c'tor
        MyString ures;

        //c'tor from character array
        MyString tomb = "hello";

        //assignment op
        ures = tomb;

        //copy on write
        tomb[0] ='H';
        cout << ures << endl;
        cout << tomb << endl;
        cout << "-------" <<endl;
    }
    {
        //c'tor
        MyString sztring1 = "hello";

        //copy c'tor
        MyString sztring2 = sztring1;

        //c'tor
        MyString sztring3("world");

        //operator+ MyString
        MyString sztring4 = sztring1 + sztring3;
        cout << sztring4 << endl;

        //operator += char
        sztring4 += '!';
        cout << sztring4 << endl;

        //operator+ strings + char
        sztring4 = sztring1 + sztring2 + sztring3 + '?';
        cout << sztring4 << endl;

        //operator += string + char
        sztring4 += sztring3 += '!';
        cout << sztring4 << endl;

        //input
        cout << "What's your name?" << endl;
        cin >> sztring4;
        cout << sztring1 + " " + sztring4 + '!'<<endl;
    }
    {
        cout << "-------" <<endl;
        MyString stomb [4] = { MyString("Aladar"), MyString("Bela"), MyString("Cecil"), MyString("Daniella")};
        for(int i = 0; i < 4; i++)
        {
            //length
            cout << stomb[i] << ", length: " << stomb[i].length()<< endl;
            //indexing
            stomb[i][i] = '?';
            cout << stomb[i] << endl;
        }

    }
    return 0;
}
