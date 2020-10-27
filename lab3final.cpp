#include <bits/stdc++.h>
#define MOD 666013
using namespace std;

/// Paun Tudor
/// Unique symbol table implementation




string line;
const char* separators = " ";

vector < pair < string ,int > > PIF;


int lexicallygood(string identifier , int last)
{
    if( last == 1)
    {
        if( identifier[0] == '"' )
        {
            if( identifier[ identifier.length() -1 ] == '"' )
                return 1;
        }
        else if( identifier[0]== '-' || identifier[0] == '+'  || isdigit(identifier[0]))
        {

            int number = atoi(identifier.c_str());
            char num[5000];
            itoa(number , num , 10);
            if( identifier == string(num) )
                return 1;

            return 0;
        }

    }
    if( isalpha(identifier[0]) )
    {
        int fnumber = 0 , fpar = 0;
        for(int i = 1; i <identifier.length(); ++i )
                if( isdigit(identifier[i]) && fpar == 0 )
        {
            fnumber =1;
        }
        else if( identifier[i] == '[')
            {fpar =1; fnumber = 0; return 1;}
        else if( !isdigit(identifier[i]) && fnumber == 1 )
                return 0;
        else if( fpar == 1 && identifier[i] == ']' && i == identifier.length() - 1 )
            fpar == 2;
        else if( !isdigit(identifier[i]) && fpar == 1  )
            return 0;

        else if( ! isdigit(identifier[i]) && ! isalpha(identifier[i])  )
            {
                return 0;
            }
        if(fpar == 2)
            return 1;
    }
    else return 0;
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
    char cline[5000] , identifier[5000];
    char* parse;

    int pos , last = 0 , linescan = 1;
    for(; getline(fin,line);)
        {

             strcpy(cline,line.c_str());
                string lline = string(cline) , lline2;

             parse = strtok(cline, separators);
            last = 0;
            while(parse!=NULL)
            {




                    it=find(tokens.begin() , tokens.end() , string(parse));
                    pos = -1;
                    if(it == tokens.end())
                    {
                        if(lexically_correct)
                            if( ! lexicallygood(string(parse) , last ) )
                                {
                                    ///cout << string(parse);
                                    lexically_correct = 0;
                                }

                        pos = ST->put(parse,found,index);
                    }
                    PIF.push_back( make_pair(string(parse),pos));



                if( strcmp("=" , string(parse).c_str() ) == 0 || strcmp("==" , string(parse).c_str() ) == 0 || strcmp("+" , string(parse).c_str() ) == 0 || strcmp("-" , string(parse).c_str() ) == 0 || strcmp("show" , string(parse).c_str() ) == 0 )
                    last = 1;
                else last = 0;

                if(strcmp("show" , string(parse).c_str()) == 0 )
                {

                    int posi =lline.find("show") + 5 ;
                    lline2 = lline.substr(posi);
                    if(lexically_correct)
                            if( ! lexicallygood(lline2 , last ) )
                                {

                                    lexically_correct = 0;
                                }

                    break;
                }

                parse =strtok(NULL,separators);
            }
            if(lexically_correct )
                linescan ++ ;

        }

    fin.close();

    if(lexically_correct)
        fout << "all good";
    else fout << " not good error at: " <<linescan;
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
