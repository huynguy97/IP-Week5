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

char rotate_char (char a, int r, Action e)
{
//                
    assert((r >= 0) &&  (a < 128) && (a >= 0));
//                                                  

    if ( a < 32)
    {
         return static_cast<char>(a);
    }
    else
    {
        switch (e)
        {
            case Encrypt: return static_cast<char>((a-32  + (r%(128-32))+ (128-32))% (128-32) +32);
            case Decrypt: return static_cast<char>((a-32  - (r%(128-32))+ (128-32))% (128-32) +32);
        }
    }
}

void test_rotate_char ()
{
//                
    assert(true);
//                                                                                  
    int r;
    char a;
    cout << "Enter a character: " << endl;
    cin >> a;
    r == 0;
    while ( r >= 0 )
    {
        cout << "Enter a value for r: " << endl;
        cin >> r;
        cout << "The character is: " << a << endl;
        cout << "The ASCII code of the character is: " << static_cast<int>(a) << endl;
        cout << "The ASCII code of rotate_char(encryption) is: " << static_cast<int>(rotate_char (a, r, Encrypt)) << endl;
        cout << "The ASCII code of rotate_char(decryption) is: " << static_cast<int>(rotate_char (rotate_char (a, r, Encrypt), r, Decrypt )) << endl;
    }
    return;

}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert(true);

//                                                 
    string inputfilename ;
    string outputfilename ;
    cout << "Enter an input file name without layout symbols: " << endl;
    cin >> inputfilename;
    cout << "Enter an output file name without layout symbols: " << endl;
    cin >> outputfilename;
    infile.open(inputfilename.c_str());
    outfile.open(outputfilename.c_str());
    if( inputfilename != outputfilename)
    {
        if ( infile.is_open() && outfile.is_open())
        {
            cout << "The file opened successfully." << endl;
            return true;
        }
        else
        {
            cout << "The file could not open." << endl;
            return false;
        }

    }
    else
    {
        cout << "The input and output file names are identical." << endl;
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

    initialise_pseudo_random(initial_value);

    char a;
    char b;
    int r = next_pseudo_random_number();

    infile.get(a);
    while (infile)
    {
        b = rotate_char(a, r, action);
        outfile.put(b);
        infile.get(a);
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

