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

char rotate_char (char a, int r, Action action)
{
//                
    assert (true) ;
//                                                                  
    int b;
    if (a<32)
    {
        b = a;
    }
    else
    {
        if (action == Encrypt)
        {
            b = (a-32 + (r % (128-32)) + (128-32)) % (128-32)+32;
        }

        else
        {
            b = (a-32 - (r % (128-32)) + (128-32)) % (128-32)+32;
        }
    }
    return b;
}

void test_rotate_char ()
{
//                
    assert(true);
//                                                                                                                 
    int r;

    char a;
    cout << "Enter a number for 'r': ";
    cin >> r ;
    while (!cin || r < 0)
    {
        cin.clear();
        cin.ignore(1000, '\n' );
        cout << "Please enter an integer bigger than or equal to 0: " ;
        cin >> r ;
    }
    cout << "Enter a character: ";
    cin >> a ;
    while (!cin)
    {
        cin.clear();
        cin.ignore(1000, '\n' );
        cout << "Please enter a letter: " ;
        cin >> a ;
    }
    char b = (rotate_char(a, r, Encrypt));
    cout << "You have entered " << a << endl;
    cout << "The ASCII code of " << a << " = "  << (int)a << endl;
    cout << "The encrypted character of " << a << " = " << b << endl;
    cout << "The decrypted character of " << b << " = " << rotate_char((int)(b), r, Decrypt) << endl;
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile, string inputfilename, string outputfilename)
{
//                
    assert(true);
//                                                                                                                                   
    if (inputfilename == outputfilename)
    {
        cout << "ERROR; Please give two different files.";
        return false;
    }
    if (infile.is_open() || outfile.is_open())
    {
        return true;
    }
    else
    {
        return false;
    }
}

Action get_user_action ()
{
    //               
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
{
    //              
    assert (true);
    /*                     
                                                              
    */
    int initial_value = -1 ;
    while (initial_value < 0 || initial_value > 65535)
    {
        cout << "Please enter the initial coding value (greater or equal to 0 and less than 65536)" << endl;
        cin  >> initial_value;
    }
    return initial_value ;
}

void use_OTP (ifstream& infile, ofstream& outfile, Action action, int initial_value)
{
//                
    assert(infile.is_open() || outfile.is_open());
//                                                                                           
    char a;

    initialise_pseudo_random(initial_value);
    infile.get(a);

    if (action == Encrypt)
    {
        while (infile)
        {
            next_pseudo_random_number();
            outfile.put(rotate_char(a,seed,Encrypt));
            cout << rotate_char(a,seed,Encrypt);
            infile.get(a);
        }
    }
    else if (action == Decrypt)
    {
        while (infile)
        {
            next_pseudo_random_number();
            outfile.put(rotate_char(a,seed,Decrypt));
            cout << rotate_char(a,seed,Decrypt);
            infile.get(a);

        }
    }
}

int main()
{
    const Action ACTION = get_user_action() ;
    cout << "Please enter the input file name (without spaces): ";
    string inputfilename ;
    cin >> inputfilename ;

    cout << "Please enter the output file name (without spaces): ";
    string outputfilename ;
    cin >> outputfilename ;

    ifstream input_file (inputfilename.c_str());
    ofstream output_file (outputfilename.c_str());
    if (!open_input_and_output_file (input_file,output_file, inputfilename, outputfilename))
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
        cout << "Not all files were closed successfully. The output might be incorrect." << endl ;
        return -1 ;
    }
    return 0 ;
}

