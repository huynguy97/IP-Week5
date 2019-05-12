#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       
#include <cmath>
#include <string>

using namespace std;

/*
                                                             
            
                                                             
                          
                        
                                                              */

enum Action {Encrypt, Decrypt} ;

int seed = 0 ;
void initialise_pseudo_random (int r)
{
/*                 */
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
    assert (a >= 0 && r > 0 && r < 65536) ;
//                 
    switch (action)
        {
        case Encrypt :
            if (a < 32)
            {
                char b = a;
            }
            else
                char b = (a-32 + (r % (128-32)) + (128-32)) % (128-32)+32;
            break;
        case Decrypt :
            if (a < 32)
            {
                char b = a;
            }
            else
                char b = (a-32 - (r % (128-32)) + (128-32)) % (128-32)+32;
            break;
    }
}
void test_rotate_char (char a, int r, Action action)
{
/*                 */
    assert (a >= 0 && r > 0 && r < 65536) ;
/*                 
                                                                                                                                                         
                  */
    cout << "Input a value for r (1-65535): " ;
    cin >> r ;
    cout << endl;
    if ( r < 0 || r > 65535)
    {
        cout << "Entered an invalid r, Error TERMINATING PROGRAM" << endl;
        return ;
    }

    for (char a = 32; a < 127; a++)
    {
        cout << "The character is " << a << endl;
        cout << "with the ASCII value " <<
             static_cast<int> (a) << endl;
        cout << "The ASCII after encryption is " << static_cast<int> (rotate_char(a, r, Encrypt)) << endl;
        cout << "The ASCII after decryption is " << static_cast<int> (rotate_char (rotate_char (a, r, Encrypt), r, Decrypt)) << endl << endl;

    }
}
bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
/*                */
    assert (true) ;
/*                 
                                                                                               */

    cout << "Enter the input filename (without spaces): " ;
    string filename1, filename2 ;
    cin >> filename1 ;
    infile.open (filename1.c_str()) ;

    cout << "Enter a output filename (without spaces): " ;
    cin >> filename2 ;
    if (filename1 != filename2)
    {
        outfile.open (filename2.c_str ()) ;
        return true;
    }
    else
    {
        cout << "Error! Files names are identical. " ;
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
    /*                */
    assert (true) ;
    /*                 
                                                              
    */
    int initial_value = -1 ;
    while (initial_value < 0 || initial_value > 65535)
    {
        cout << "Please enter the initial coding value (0 - 65535): " ;
        cin  >> initial_value ;
    }
    return initial_value ;
}

void use_OTP (ifstream& infile, ofstream& outfile, Action action, int initial_value)
{
/*                 */
    assert (infile.is_open() && outfile.is_open() && initial_value > 0) ;
/*                  */
    char c ;
    initialise_pseudo_random(initial_value);
    infile.get(c) ;
    while (infile)
    {
        int r = next_pseudo_random_number();
        c = rotate_char(c, r, action) ;
        outfile.put (c) ;
        infile.get (c) ;
    }
}

int main()
{
    char a ;
    int r ;
    Action action ;
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
    else
        cout << "Succesful <(^_^)>" << endl;
    return 0 ;
}

