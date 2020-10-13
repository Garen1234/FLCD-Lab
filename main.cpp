#include <bits/stdc++.h>
#define MOD 666013
using namespace std;

/// Paun Tudor
/// Unique symbol table implementation


struct LinkedList{
    char sym[50];
    LinkedList* next;
};

class SymbolTable
{
private:
    LinkedList *HT[MOD]; /// HT - hashtable  , MOD prime number

public:

    int h(int a) /// hashes integer code
    {
        return a%MOD;
    }

    int convert(char a[50]) /// converts string to  an integer code
    {
        int s = 0 , p = 1;

        for( int  i  = 0  ; i < strlen(a) ; ++i)
        {
            s +=  (a[i] % 10) * p ;
            p *= 10;
            if( p >= 100000)
                p = 1;
        }

        return s;
    }

    int put ( char a[50] , int& found , int& index ) /// O(1) returns hash code of the given string a  , and  through help of references  we get if the string was found and it's index in the linkedlist
    /// found = 0 means not found  ; found = 1 means found
    /// index will be the position in the linkedlist of the string  in  case it was already added
    {
        int pos  =  h( convert(a) );
        int exists = 0 , position = 1;
        if (  this->HT[pos] != NULL )
        {
            LinkedList* x = HT[pos] ;
            LinkedList* last = NULL;

            while(  x != NULL)
            {   last = x;
                if( strcmp(x->sym, a) == 0)
                {
                    exists = 1;
                    found = 1;
                    index = position;
                    break;

                }
                x= x->next;
                position++;
            }

            if(exists == 0)
            {
                last->next = new LinkedList();
               strcpy(last->next->sym , a);
                last->next->next = NULL;
            }
        }
        else  {

            HT[pos] = new LinkedList();
            strcpy(HT[pos]->sym , a);
            HT[pos]->next = NULL;
        }

        return pos;
    }


};

int main()
{
    SymbolTable* ST = new SymbolTable();
    int foundra = 0 , foundha = 0 , indexra = 0,indexha = 0;
    int x = ST->put("ra" , foundra , indexra) , y = ST->put("ha" , foundha , indexha);
    cout << x << " " << y;
    return 0;
}
