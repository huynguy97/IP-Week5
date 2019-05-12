#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       

using namespace std;

/*
                                                  

                                                 

                                                  

                                          
                                          

                                                  
*/

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
    assert(r >= 0 && r <= 65536);
/*                 
                                                   
*/  if (a < 32)
    {
        return a;
    } else {
        if (action == Encrypt)
            return (a-32+(r % (128-32))) % (128-32) + 32;
        else
            return (a-32-(r % (128-32)) + (128-32)) % (128-32) + 32;
    }
}

void test_rotate_char ()
{
//                
    assert(true);
/*                 
                                                                                        
*/  int r;
    do
    {
        cout << "Please enter a non-negative value for r: ";
        cin >> r;

        if (r>=0)
        {
            for (int i=0; i<128; i++)
            {
                char a = i;
                char a_encrypted = rotate_char(a,r,Encrypt);
                char a_decrypted = rotate_char(a_encrypted,r,Decrypt);
                cout << a << "\t" << i << "\t" << static_cast<int>(a_encrypted) << "\t" << static_cast<int>(a_decrypted) << endl;
            }
        }
    } while (r>=0);
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert(true);
/*                 
                                                                               
*/
    string input_filename;
    cout << "Enter input-filename (without spaces): ";
    cin >> input_filename;

    string output_filename;
    cout << "Enter output-filename (without spaces): ";
    cin >> output_filename;

    if (input_filename == output_filename)
    {
        cout << "The input-filename and output-filename can't be the same." << endl;
        return false;
    }

    infile.open(input_filename.c_str());
    outfile.open(output_filename.c_str());

    if (infile.is_open() && outfile.is_open())
    {
        cout << "Files have been opened successfully." << endl;
        return true;
    } else {
        cout << "Files have not been opened successfully." << endl;
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
        cout << "Please enter the initial coding value (greater or equal to 0 and less than 65536): ";
        cin  >> initial_value ;
    }
    return initial_value ;
}

void use_OTP (ifstream& infile, ofstream& outfile, Action action, int initial_value)
{
//                
    assert(infile.is_open() && outfile.is_open());
/*                 
                                                                          
*/
    initialise_pseudo_random(initial_value);
    int r;
    char c;

    infile.get(c);

    while (infile)
    {
        r = next_pseudo_random_number();
        char c_crypted = rotate_char(c, r, action);
        cout << c_crypted;
        outfile.put(c_crypted);
        infile.get(c);
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

