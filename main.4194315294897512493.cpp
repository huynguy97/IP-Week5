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
    assert (0 <= a < 128) ;
/*                 
                                                  
*/
    char b ;

    r = next_pseudo_random_number();

    if (a < 32)
    {
        b = a ;
    }
    else if (a >= 32 && e == 0 ) //           
    {
        b = (a - 32 + (r % (128-32)) + (128 - 32)) % (128-32) + 32 ;
    }
    else //           
    {
        b = (a - 32 - (r % (128-32)) + (128 - 32)) % (128-32) + 32 ;
    }

    return b ;
}

void test_rotate_char ()
{
//                
    assert (true);
//                 
/*                                                            
                                                  
*/

    char a;
    int r;
    char encrypt_value;
    char decrypt_value;

    cout << "Enter char a: ";
    cin >> a;
    cout << "Enter int r: ";
    cin >> r;

    initialise_pseudo_random(r); //                                                          
    encrypt_value = rotate_char (a, r, Encrypt);

    initialise_pseudo_random(r); //                                                          
    decrypt_value = rotate_char (encrypt_value, r, Decrypt);

    cout << "Character a: " << a << "\nASCII code a: " << static_cast<int>(a) << "\nASCII code encrypt: " << encrypt_value << "\nASCII code encrypt decrypt: " << decrypt_value;
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert (true);
//                 
    //                                                       
    string inputfilename;
    string outputfilename;
    cout << "Enter input filename: "; //                                                  
    cin >> inputfilename;
    cout << "Enter output filename: ";
    cin >> outputfilename;
    if (inputfilename == outputfilename)
        return false;

    infile.open(inputfilename.c_str());
    outfile.open(outputfilename.c_str());

    if (infile.is_open()&&outfile.is_open()) //                                 
        return true;
    else
        return false;

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

//                 
    initialise_pseudo_random(initial_value); //                                                            

    int pseudo = next_pseudo_random_number();
    int no_of_chars = 0;
    char a;

    infile.get(a);
    initialise_pseudo_random(initial_value);
    while (infile) //                    
    {
        outfile.put (rotate_char(a, pseudo, action));
        no_of_chars++;
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
        cout << "Not all files were closed successfully. The output might be incorrect." << endl ;
        return -1 ;
    }

    return 0 ;
}

