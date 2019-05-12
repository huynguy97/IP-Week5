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
char rotate_char (char a, int r, Action ACTION)
{
//                
    assert (true);
/*                 
                                                                             
 */
    char b;
    if (ACTION == Encrypt)
    {
        if( a <= 31)
        {
            b = a;
        }
        else
        {
            b = (a - 32 + (r%(128-32))) % (128-32)+32;
        }
    }
    else
    {
        if( a <= 31)
        {
            b = a;
        }
        else
        {
            b = (a - 32 - (r%(128-32))+(128-32)) % (128-32)+32;
        }
    }
    return b;
}

void test_rotate_char ()
{
//                
    int r;
    cout << "Please enter integer number r: ";
    cin >> r;
    while (!cin)
    {
        cin.clear();
        cin.ignore (1000, '\n');
        cout << "Please enter an integer, not anything else: ";
        cin >> r;
    }
    char a;
    cout << "Please enter char a: ";
    cin >> a;
    while (!cin)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Please enter a character, not a string: ";
        cin >>a ;
    }    assert (r >=0);
    
/*                 
                                                                                                                  
*/
    int encryption = rotate_char(a, r, Encrypt);
    int decryption = rotate_char(rotate_char(a, r, Encrypt), r, Decrypt);
    cout << "The character a: "<< a << endl ;
    cout << "the ASCII of a: "<< (int)a<< endl;
    cout << "the ASCII code of encryption of a: " << encryption<< endl;
    cout << "the ASCII code of decryption of a: " << decryption;
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    string filename1, filename2;
    cout << endl;
    cout << "Please enter the name for input-file: ";
    cin >> filename1;
    cout << "Please enter the name for output-file: ";
    cin >> filename2;
    while ( filename1 == filename2)
    {
        cout << "The two filenames are identical. Please re-enter filename2: ";
        cin >> filename2;
    }
    infile.open (filename1.c_str());
    outfile.open (filename2.c_str());
    //                 
//                                                    
    if (infile.is_open() && outfile.is_open())
    {
        cout << " The two files have been successfully opened";
        return true;
    }
    else
    {
        cout << "Couldn't open"<< endl;
        return false;
    }
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
}
int main()
{
    //                                              
    //                                         
    int r;
    const Action ACTION = get_user_action() ;
    ifstream input_file;
    ofstream output_file;
    if (!open_input_and_output_file (input_file,output_file))
    {
        cout << "Program aborted." << endl ;
        return -1 ;
    }
    r = initial_encryption_value();
    initialise_pseudo_random(r);
    
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

