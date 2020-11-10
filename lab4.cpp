#include <bits/stdc++.h>

using namespace std;
ifstream fin("FA.in");
map< pair <string , char> , vector <string> > transitions;
vector < char > alphabet;
vector < string > states;
vector < string > final_states;
string initial_state;
int number_of_transitions;
bool deterministic = true;



int main()
{
    string line;
    getline(fin , line);

    int  pos ;
    while( pos = line.find(" ") )
    {

        string input = line.substr(0 ,pos);
        states.push_back(input);

        if(pos > -1)
            line.erase(0,pos+1);
        else break;

    }

    getline(fin , line);

    for(int i = 0 ; i< line.size() ; ++i)
        alphabet.push_back(line[i]);


    fin >> number_of_transitions;
    getline(fin , line);
    for(int i = 0 ; i < number_of_transitions ; ++i)
    {   /*
            get transitions
        */
        getline(fin,line);


       pos = line.find(" ");


        string state1 = line.substr(0 ,pos);

        line.erase(0,pos+1);


        pos = line.find(" ");

        string character = line.substr(0,pos);
        char e  =  character[0];

        line.erase(0,pos+1);

        string state2 = line;
        transitions[make_pair(state1,e)].push_back(state2);

    }
    getline(fin,line);
    initial_state = line;

    getline(fin,line);
    while( pos = line.find(" ") )
    {

        string input = line.substr(0 ,pos);
        final_states.push_back(input);


        if(pos > -1)
            line.erase(0,pos+1);
        else break;

    }

    int command;
        while(true)
        {
            cout << " Choose command ( 0 - exit , 1 - show states , 2 - show alphabet , 3 show transitions , 4 show final states ,5 check for DFA): ";
            cin >> command;

            if( command == 0 )
                break;
            else if( command == 1)
                        {
                            for( int i = 0 ; i < states.size() ; ++i)
                                cout << states[i] << " ";
                            cout << "\n";
                        }
                else if(command == 2)
                        {
                            for( int i = 0 ;i < alphabet.size() ; ++i)
                                cout << alphabet[i] <<  " ";
                        cout << "\n";
                }
                else if( command == 3)
                {
                    map< pair <string , char> , vector <string> >::iterator it;
                    for( it = transitions.begin() ; it != transitions.end() ; ++it)
                    {
                        pair<string , char> key = it->first;
                        if(transitions[key].size() > 1)
                                deterministic = false;
                        for( int i = 0 ; i< transitions[key].size() ; ++i)
                        {


                            cout << key.first << " " << key.second << " " << transitions[key][i] << "\n";
                        }
                    }
                    cout << " This FA is ";
                    if( deterministic == false)
                        cout << "a NFA\n";
                    else cout << "a DFA\n";
                }
                else if( command == 4)
                {
                    for( int i = 0 ; i < final_states.size() ; ++i)
                        cout << final_states[i] << " ";
                    cout << "\n";
                }
                else
                {
                    if(deterministic == false)
                    {
                        cout << "Given FA is not a DFA!";
                    }
                    else {

                        cout << " Enter a sequence: ";
                        string sequence;
                        cin >> sequence;

                        string current_state = initial_state;

                        int ok = 1;
                        for( int i = 0 ; i < sequence[i] ; ++i)
                        {
                            pair < string , char > key;

                            key = make_pair(current_state , sequence[i]);

                            if( transitions[key].size() != 1 )
                            {
                                ok = 0;
                                break;
                            }
                            else
                                current_state = transitions[key][0];
                        }

                        if(ok == 1 && find(final_states.begin(),final_states.end() ,current_state) != final_states.end() )
                            cout << " Sequence accepted";
                        else cout << "Sequence not accepted";

                    }
                    cout << "\n";
                }

        }

    return 0;
}
