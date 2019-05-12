#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       

/*                                                        */

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
    assert (r >= 0) ;
//                 
//                                      

    char b ;
    int Encription_switch = 1 ;
    if ( action==Decrypt )
        Encription_switch = -1 ;
    if (a < 32)
        b = a ;
    else
       b = (a - 32 + Encription_switch * (r % (128-32)) + (128-32)) % (128-32)+32  ;
    return b ;
}

void test_rotate_char ()
{
//                
    assert ( true ) ;
/*                 
                                                                                                              
                                                                                                               
                                        */

    int r ;
    char a ;
    r = -1 ;
    while ( r < 0)
    {
        cout << "Please enter a positive number for value r" << endl;
        cin >> r ;
    }
    cout << "Enter any character you would like to encrypt/decrypt" << endl;
    cin >> a ;
    cout << endl << a << endl;
    int b = a ;
    cout << b << endl ;
    a = rotate_char (a, r, Encrypt) ;
    cout << a << endl;
    a = rotate_char (a, r, Decrypt) ;
    cout << a << endl;
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert (true) ;
//                                                                                    
    string infilename ;
    string outfilename ;
    cout << "please enter a file name for an input file: \n" ;
    cin >> infilename ;
    cout << "please enter a file name for an output file: \n" ;
    cin >> outfilename ;
    while (infilename == outfilename)
    {
        cout << "Error: identical file names will not be accepted! Try again: \n" ;
        cout << "please enter a file name for an input file: \n" ;
        cin >> infilename ;
        cout << "please enter a file name for an output file: \n" ;
        cin >> outfilename ;
    }
    infile.open(infilename.c_str()) ;
    outfile.open(outfilename.c_str()) ;
    if (infile && outfile)
    {
        cout << "files have been opened successfully \n" ;
        return true ;
    }
    else
    {
        cout << "files could not be opened\n" ;
        return false ;
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
    assert( true ) ;
//                                                                                   

    initialise_pseudo_random(initial_value) ;
    int r = next_pseudo_random_number();
    char a ;
    infile.get(a) ;
    while (infile)
    {
        char b = rotate_char(a, r, action) ;
        outfile.put(b);
        infile.get(a) ;
        r = next_pseudo_random_number();
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

