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
    assert (r >= 0);
/*                 
                                           
*/

    if (a < 32)
    {   return a;
    }

    if (!action)
    {   return static_cast<char>((a-32 + (r % (128-32)) + (128-32)) % (128-32) + 32);
    }

    return static_cast<char>((a-32 - (r % (128-32)) + (128-32)) % (128-32) + 32);
}

void test_rotate_char ()
{
//                
    assert(true);
/*                 
                                                                        
*/
    int r;
    cout << "Give a value for r:\n";
    cin >> r;
    while (r>=0)
    {
        for (int i=32; i<128; i++)
        {
            char a = static_cast<char>(i);

            cout << a << "\t" << i << "\t";
            cout << static_cast<int>(rotate_char(a,r,Encrypt)) << "\t";
            cout << static_cast<int>(rotate_char(rotate_char(a,r,Encrypt),r,Decrypt)) << "\n";
        }

        cout << "Give a value for r:\n";
        cin >> r;
    }
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert (infile && outfile);
/*                 
                                                                                                        
*/
    cout << "Give an input file name:\n";
    string ifilename;
    cin >> ifilename;
    infile.open(ifilename.c_str());

    cout << "Give an output file name:\n";
    string ofilename;
    cin >> ofilename;
    outfile.open(ofilename.c_str());

    if (ifilename == ofilename)
    {
        return false;
    }

    if (infile.is_open() && outfile.is_open())
    {
        return true;
    }

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
    assert (infile && outfile);
/*                 
                                                  
*/

    initialise_pseudo_random(initial_value);
    int r = next_pseudo_random_number();

    char c;
    infile.get (c);
    while (infile)
    {
        c = rotate_char(c, r, action);
        outfile.put(c);
        r = next_pseudo_random_number();
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

