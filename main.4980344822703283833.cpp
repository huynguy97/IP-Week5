#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       

using namespace std;

enum Action {Encrypt, Decrypt} ;

int seed = 0 ;
void initialise_pseudo_random (int r)
{
//                
    assert (r > 0 && r <= 65536) ;
/*                 
                     
*/
    seed = r ;
}

int next_pseudo_random_number ()
{
//                
    assert (seed > 0 && seed <= 65536) ;
/*                 
                                                                                            
*/
    const int seed75 = seed * 75 ;
    int next = (seed75 & 65535) - (seed75 >> 16) ;
    if (next < 0)
        next += 65537 ;
    seed = next ;
    return next ;
}
//                                                        
//                     

char rotate_char (char a, int r, Action action)
{
//                
    assert(a >= 0 && a < 128 && r >= 0);
//                                                                                                           
    int inta = a;
    int b;
    switch(action)
    {
        case Encrypt:
            if(inta>=32)
            {
                b = ((inta-32+(r%(128-32)))%(128-32))+32;
                return b;
            }
            else
            {
                return a;
            }
        break;
        case Decrypt:
            if (inta>=32)
            {
                b = ((inta-32-(r%(128-32))+(128-32))%(128-32))+32;
                return b;
            }
            else
            {
                return a;
            }
        break;
    }
}

void test_rotate_char ()
{
//                
    assert(true);
//                                                                                                                             
    bool test = true;
    while(test)
    {
        int r;
        cout << "Geef een waarde voor r:\n";
        cin >> r;
        if (r > 0)
        {
            for (int i = 0; i < 128; i++)
            {
                char a = i;
                int b = rotate_char(a, r, Encrypt) ;
                int c = rotate_char(rotate_char(a, r, Encrypt), r, Decrypt);
                cout << a << "\t" << i << "\t" << b << "\t" << c << "\n";
            }
        }
        else
        {
            test = false;
        }
    }
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert(infile && outfile);
//                                                                                                                                                   
    string input_name, output_name;
    cout << "Name your input file:\n";
    cin >> input_name;
    cout << "Name your output file:\n";
    cin >> output_name;
    if(input_name == output_name)
    {
        cout << "The files could not be opened because they have the same name.\n";
        return false;
    }
    else
    {
        infile.open (input_name.c_str());
        outfile.open (output_name.c_str());
        if (infile.is_open() && outfile.is_open())
        {
            cout << "The files have been opened succesfully.\n";
            return true;
        }
        else
        {
            cout << "The files could not be opened.\n";
            return false;
        }
    }
}

Action get_user_action ()
{//               
    assert ( true ) ;
/*                 
                                                                                              
*/
    cout << "Do you want to encrypt the file? (y/n): " ;
    string answer ;
    cin  >> answer ;
    if (answer == "y")
        return Encrypt;
    else
        return Decrypt;
}

int initial_encryption_value ()
{//              
    assert (true) ;
/*                 
                                                                                                             
*/
    int initial_value = -1 ;
    while (initial_value < 0 || initial_value > 65535)
    {
        cout << "Please enter the initial coding value (greater or equal to 0 and less than 65536)" << endl ;
        cin  >> initial_value ;
    }
    return initial_value ;
}

void use_OTP (ifstream& infile, ofstream& outfile, Action action, int initial_value)
{
//                
    assert(infile && outfile && initial_value > 0 && initial_value <65536);
//                 
    initialise_pseudo_random(initial_value);
    int r;
    char a;
    infile.get(a);
    while (infile)
    {
        r = next_pseudo_random_number();
        char b = rotate_char(a, r, action);
        outfile.put(b);
        infile.get(a);
    }
}

int main()
{
    const Action ACTION = get_user_action() ;
    ifstream input_file  ;
    ofstream output_file ;
    if (!open_input_and_output_file (input_file,output_file))
    {
        cout << "Program aborted." << endl ;
        return -1 ;
    }
    const int INITIAL_VALUE = initial_encryption_value () ;
    use_OTP (input_file,output_file,ACTION,INITIAL_VALUE);
    input_file.clear () ;
    output_file.clear () ;
    input_file.close () ;
    output_file.close () ;

    if (!input_file || !output_file)
    {
        cout << "Not all files were closed succesfully. The output might be incorrect." << endl ;
        return -1 ;
    }
    return 0 ;
}

