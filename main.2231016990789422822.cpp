#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       

using namespace std;

//                      
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
    assert(a >= 0 && a < 128 && r >= 0) ;

//                 
//                                                                                      
    if (a < 32)
    {
        return a ;
    }
    else
    {
        if (action == Encrypt)
        {
            return (a-32+(r%(128-32)))%(128-32)+32 ;
        }
        else
        {
            return (a-32-(r%(128-32))+(128-32))%(128-32)+32 ;
        }
    }
}

void test_rotate_char ()
{
//                
    assert(true) ;
//                 
//                                                                                                                                                                            
//                                                                              
    int r = 0 ;
    while (r >= 0)
    {
        cout << "Enter a nonnegative value for r.\n" ;
        cin >> r ;
        cout << "The characters and integers mean the following, respectively: the character a, the ASCII code of a, the ASCII code of rotate_char (a, r, Encrypt) and the ASCII code of rotate_char (rotate_char (a, r, Encrypt), r, Decrypt).\n" ;
        for (int ascii = 32 ; ascii < 128 ; ascii++)
        {
            char character = ascii ;
            cout << character << "\t" << ascii << "\t" << rotate_char(ascii, r, Encrypt) << "\t" << rotate_char(rotate_char(ascii, r, Encrypt), r, Decrypt) << "\n" ;
        }
    }
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert( true ) ;
//                 
//                                                                                                                                                  
    cout << "Enter the input file.\n" ;
    string input_file ;
    cin >> input_file ;
    cout << "Enter the output file.\n" ;
    string output_file ;
    cin >> output_file ;
    if (input_file == output_file)
    {
        cout << "Error: The input file and the output file can not have the same name." ;
        return false ;
    }
    infile.open(input_file.c_str()) ;
    outfile.open(output_file.c_str()) ;
    if (infile.is_open() && outfile.is_open())
    {
        cout << "The files have been opened successfully." ;
        return true ;
    }
    return false ;
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
    assert(infile != outfile && initial_value > 0 && initial_value < 65536) ;
//                 
//                                                                                                                                                     
    initialise_pseudo_random(initial_value) ;
    char c ;
    while (infile.get(c))
    {
        outfile.put(rotate_char(c, next_pseudo_random_number(), action));
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
    input_file.clear() ;
    output_file.clear() ;
    input_file.close () ;
    output_file.close () ;

    if (!input_file || !output_file)
    {
        cout << "Not all files were closed successfully. The output might be incorrect." << endl ;
        return -1 ;
    }
    return 0 ;
}

