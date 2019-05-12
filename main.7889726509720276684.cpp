//                        
//                             

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

char rotate_char (char a, int r, Action e)
{
//                
    assert (a >= 0 && r > 0) ;
//                 
//                                           
    switch (e)
    {
    case (Encrypt):
    {
        if (a < 32)
        {
            char b = a ;
        }
        else
        {
            char b = (a - 32 + (r % (128-32)) + (128-32)) % (128-32) + 32 ;
        }
    } ;
    break;

    case (Decrypt):
    {
        if (a < 32)
        {
            char b = a ;
        }
        else
        {
            char b = (a - 32 - (r % (128-32)) + (128-32)) % (128-32) + 32 ;
        }
    } ;
    break;
    }
}

void test_rotate_char (char a, int r, Action e)
{
//                
    assert (r >= 0);
//                 
//                                                                                                                                                                                                                       

    cout << "Input a positive value r: ";
    cin >> r;
    if ( r < 0 || r > 65536)
        return;

    cout << "Character a: "<< '\t' << "ASCII a:"<< " Encrypted ASCCI a, Decrypted ASCCI a" << endl;
    for (char a = 32; a < 127; a = a + 1)
    {
        cout << a << '\t' << '\t' << static_cast<int>(a) << '\t' << '\t'<< static_cast<int>(rotate_char (a, r, Encrypt)) <<  '\t' << static_cast<int>(rotate_char (rotate_char (a, r, Encrypt), r, Decrypt)) << endl;
    }

}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
    //                
        assert(true);
    //                 
    //                                                                                                                                                                                                                                                                           

    cout << "Please enter a file name to be encrypted (without layout symbols): ";
    string infile1;
    cin >> infile1;
    infile.open (infile1.c_str() );
    if (infile)
    {
        cout << "The file is opened successfully." << endl;
    }
    else
    {
        cout << "Could not open the file. Abort mission" << endl;
        return false;
    }

    cout << "Please enter a file name to use for output (without layout symbols): ";
    string outfile2;
    cin >> outfile2;
    outfile.open (outfile2.c_str() );
    if (outfile)
    {
        cout << "The file is opened successfully." << endl;
    }
    else
    {
        cout << "Could not open the file. Abort mission" << endl;
        return false;
    }

    if (infile1 == outfile2)
    {
        return false;
    }
    return true;
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
        cout << "Please enter the initial coding value (greater or equal to 1 and less than 65536)" << endl ;
        cin  >> initial_value ;
    }
    return initial_value ;
}

void use_OTP (ifstream& infile, ofstream& outfile, Action action, int initial_value)
{
//                
    assert(infile.is_open() && outfile.is_open() && initial_value >= 1);
//                 
//                                                                                                                                                                          

    initialise_pseudo_random(initial_value);

    char c;
    infile.get (c);
    while (infile)
    {
        outfile.put (rotate_char (c, next_pseudo_random_number(), action));
        infile.get (c);
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

