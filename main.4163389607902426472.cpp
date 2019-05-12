#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       
//                                        
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
    assert (  r>=0 );
//                 
//                                
    char b;
    switch (action)
        {
        case Encrypt:
            if (a >= 32)
                 b = (a-32 + (r % (128-32)) + (128-32)) % (128-32)+32;
            else b = a;
            break;
        case Decrypt:
            if (a >= 32)
                 b = (a-32 - (r % (128-32)) + (128-32)) % (128-32)+32;
            else b = a;
        }
    return b;

}

void test_rotate_char ()
{
//                
    int r;
    char a;
    assert (r>=0);
//                 
//                                                                                                         
//                                                                            
    cout << "Enter value r: ";
    cin >> r;
    while (r<0)
        {
            cout << "Enter value non-negative r: ";
            cin >> r;
        }
    cout << "Enter text: ";
    cin >> a;
    cout << "The character a is: " << a << endl;
    cout << "The ASCII code of a is: " << int(a) << endl;
    cout << "Encrypted a: " << int(rotate_char (a, r, Encrypt)) << endl;
    cout << "Decrypted a: " << int(rotate_char (rotate_char (a, r, Encrypt), r, Decrypt)) << endl;
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
 //         
//                 
//                                                               
    cout << "Name a file name" << endl;
    string filename;
    cin >> filename;
    cout << "Name an outfile name" << endl;
    string outfilename;
    cin >> outfilename;
    if (filename == outfilename)
        return false;
    else
    {
        infile.open(filename.c_str());
        outfile.open (outfilename.c_str());
        if (infile.is_open() && outfile.is_open())
        return true;
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
    assert (infile.is_open() && outfile.is_open());
//                 
    char a;
    char c;
    infile.get(a);
    while (infile)
    {
        c=rotate_char(a, initial_value, Decrypt);
        outfile.put(c);
        infile.get(a);
    }
}

int main()
{
  //                      
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

