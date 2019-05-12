#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       

using namespace std;

//                                 
//                             

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
    assert (r >= 0);

//                                                                                    

    char b ;
    if (a < 32)
        return a;
    else
        switch(action)
        {
        case Encrypt:
            b = (a-32 + (r % (128-32)) + (128-32)) % (128-32)+32;
            return b;
        case Decrypt:
            b = (a-32 - (r % (128-32)) + (128-32)) % (128-32)+32;
            return b;
        }

}

void test_rotate_char ()
{
//                
    assert (true);
//                                                                                                               
//               
    int r = 0;
    while (r>=0)
    {
        cout << "Please enter a value for r between 0 and 65536. Entering a negative number will terminate the function." << endl;
        cin >> r;
        while (!cin)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "That was not an integer! Please try again." << endl;
            cin >> r;
        }
        if (r >=0)
        {
            cout << "Please enter a char value for a." << endl;
            char a;
            cin >> a;
            cout << "Value a = " << a << "." <<endl;
            cout << "Value of the ASCII code of a = " << static_cast<int>(a) << "." << endl;
            cout << "Value of the encrypted a = " << static_cast<int>(rotate_char (a, r, Encrypt)) << "." <<endl;
            cout << "Value of the decrypted a = " << static_cast<int>(rotate_char (rotate_char (a, r,
                    Encrypt), r, Decrypt)) << "." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert (true);
//                                                                                                        
//                                                                                 
    cout << "Please enter a file to open as input. (no spaces and include file extension)." << endl;
    string input;
    cin >> input;

    cout << "Please enter a file to open as output." << endl;
    string output;
    cin >> output;

    if (infile == outfile)
    {
        cout << "Error: input file and output file are the same. (no spaces and include file extension)" << endl;
        return false;
    }
    infile.open( input.c_str());
    outfile.open( output.c_str());
    if (infile.is_open() && outfile.is_open())
    {
        cout << "Both files have been successfully opened." << endl;
        return true;
    }
    cout << "Error: something went wrong whilst attempting to open the files." << endl;
    return false;
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
assert(true);
//                                                                                                                
//                                                      

initialise_pseudo_random(initial_value);
char a;
infile.get (a);
while (infile)
    {
    outfile.put(rotate_char (a, next_pseudo_random_number(), action));
    infile.get (a);
    }
cout << "Done with use_OTP." << endl;
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
    const int INITIAL_VALUE = initial_encryption_value ();
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

