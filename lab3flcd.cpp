#include <bits/stdc++.h>
#define MOD 666013
using namespace std;

/// Paun Tudor
/// Unique symbol table implementation




string line;
const char* separators = " ";
vector < pair < string ,int > > PIF;


int lexicallygood(string indentifier)
{
    return 1;
}

struct LinkedList{
    char sym[50];
    LinkedList* next;
};

class SymbolTable
{



public:

    LinkedList *HT[MOD]; /// HT - hashtable  , MOD prime number

    int h(int a) /// hashes integer code
    {
        return a%MOD;
    }

    int convert( const char a[50]) /// converts string to  an integer code
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

    int put ( const char a[50] , int& found , int& index ) /// O(1) returns hash code of the given string a  , and  through help of references  we get if the string was found and it's index in the linkedlist
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
    int found,index , lexically_correct = 1 , wrongline = -1;
    SymbolTable* ST = new SymbolTable();
    SymbolTable* Tokens = new SymbolTable();
    vector <string> tokens;
    vector <string>::iterator it;
    ifstream fin("token.in");
    ofstream fout("msg.out");
    for( ; getline(fin, line); )
    {
        Tokens->put(line.c_str(),found,index);
        tokens.push_back(line);

    }
    fin.close();

    fin.open("program.in");
    char cline[5000] ;
    char* parse;
    int pos;
    for(; getline(fin,line);)
        {

             strcpy(cline,line.c_str());

             parse = strtok(cline, separators);

            while(parse!=NULL)
            {

                    it=find(tokens.begin() , tokens.end() , string(parse));
                    pos = -1;
                    if(it == tokens.end())
                    {
                        if(lexically_correct)
                            if( ! lexicallygood(string(parse) ) )
                                lexically_correct = 0;
                        pos = ST->put(parse,found,index);
                    }
                    PIF.push_back( make_pair(string(parse),pos));
                cout << parse ;



                parse =strtok(NULL,separators);
            }

            cout << "\n";
        }

    fin.close();

    if(lexically_correct)
        fout << "all good";
    else fout << " not good error at: " <<wrongline;
    fout.close();

    fout.open("PIF.out");
    fout << "token" << " " << "id"<< "\n";
    for( int i = 0 ; i < PIF.size(); ++i  )
    {
        fout << PIF[i].first << " " << PIF[i].second << "\n";
    }

    fout.close();
    fout.open("ST.out");

    fout << "ST_POS" << "                           ;" << "Symbol\n";
    for( int i = 0 ; i< 666013 ; ++i)
        if( ST->HT[i] != NULL)
    {   int j=1;
        LinkedList* x = ST->HT[i] ;
         while(  x != NULL)
            {

                fout <<"linked list " << i << " pos " << j << " in linked list"  << "  ; " <<x->sym << "\n";
                x= x->next;
                ++j;
            }

    }

    fout.close();
    return 0;
}
