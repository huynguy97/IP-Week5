#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       

//                                                  

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
    assert (true);
//                                                                                
    if (action == Encrypt)
    {
        if ((int) a < 32)
            return a;
        else
            return ( a - 32 + (r % (128 - 32)) + (128 - 32)) % (128 - 32) + 32;
    }
    if (action == Decrypt)
    {
        if (a < 32)
            return a;
        else
            return (a - 32 - (r % (128 - 32)) + (128 - 32)) % (128 - 32) + 32;
    }
}

void test_rotate_char ()
{
//                  
    assert (true);
//                                                                                                                         
    int r;
    initialise_pseudo_random(10);
    r = next_pseudo_random_number();
    cout << "r is equal to " << r << endl;
    cout << "Enter a character: " << endl;
    char a;
    cin >> a;
    cout << "The ACSII value of a is: " << (int) a << endl;
    cout << "The value of the encrypted character a is: " << (int) rotate_char( (int) a, r, Encrypt) << endl;
    cout << "The value of the decrypted encryption of character a is: " << (int) rotate_char( (int) rotate_char( (int) a, r, Encrypt), r, Decrypt) << endl;
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                  
    assert (true);
//                                                                                           
    cout << "Enter the input file name that you want to open: ";
    string ifilename;
    cin >> ifilename;
    infile.open (ifilename.c_str ());
    cout << "Enter the output file name that you want to open: ";
    string ofilename;
    cin >> ofilename;
   outfile.open (ofilename.c_str ());
    if (ifilename == ofilename)
    {
        cout << "Error" << endl;
        return false;
    }
    if (infile.is_open () && outfile.is_open ())
    {
        cout << "The input file has been opened successfully" << endl;
        return true;
    }
    else
    {
        return false;
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
    assert(infile.is_open() && outfile.is_open());
//                                                                                                           
    char a;
    initialise_pseudo_random(initial_value);
    infile.get (a);
    while (!infile.eof())
    {
        int R;
        R = next_pseudo_random_number();
        outfile.put (rotate_char(a, R, Encrypt));
        infile.get (a);
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

