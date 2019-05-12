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

char rotate_char(char a, int r, Action action)
{
//                
    assert(r >= 0);
/*                 
                                                                
*/
    int operation = 1;
    if (action == Decrypt)
        operation = -1;

    if (a < 32)
        return(a);
    else
        return((a - 32 + operation * (r % (128 - 32)) + (128 - 32)) % (128 - 32) + 32);
}

void ask_for_r(int& r)
{
//                
    assert(true);
/*                 
                 
*/

    cout << "Please enter a non-negative value for r or a negative value if you want to terminate: ";
    cin >> r;
    cout << '\n';
}

void test_rotate_char ()
{
//                
    assert(true);
/*                 
                                        
                                                                                                         
                                                                       
*/

    int r;
    ask_for_r(r);
    while (r >= 0) {
        for (int i = 0; i < 128; i++) {
            char c = static_cast<char>(i);
            cout << c << ' ' << static_cast<int>(c) << ' ' << static_cast<int>(rotate_char(c, r, Encrypt)) << ' ' << static_cast<int>(rotate_char(rotate_char(c, r, Encrypt), r, Decrypt)) << '\n';
        }
        ask_for_r(r);
    }
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert(true);
/*                 
                                                       
                                                                                 
                                                                 
*/
    string infile_name, outfile_name;
    cout << "Please enter a filename for input: ";
    cin >> infile_name;
    cout << "\nPlease enter a filename for output: ";
    cin >> outfile_name;

    if (infile_name == outfile_name) {
        cout << "\nERROR the names have to be different\n";
        return false;
    } else {
        infile.open(infile_name.c_str());
        outfile.open(outfile_name.c_str());
        return infile && outfile;
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
    assert(infile.is_open() && outfile.is_open() && initial_value >= 0 && initial_value < 65536);
/*                 
                                                                              
*/
    initialise_pseudo_random(initial_value);
    char a, b;
    int r;
    infile.get(a);
    while (infile) {
        r = next_pseudo_random_number();
        b = rotate_char(a, r, action);
        outfile.put(b);
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
        cout << "Not all files were closed succesfully. The output might be incorrect." << endl ;
        return -1 ;
    }
    return 0 ;
}

