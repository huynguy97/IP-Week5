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
char rotate_char (char a, int r, Action action)
{
//                
    assert (r >= 0) ;
/*                 
                                                                         
                                                       
*/  char b = a;
    if (b < 32)
        return b;
    if (action == 0)
        b = (a-32 + (r%(128-32)) + (128-32)) % (128-32)+32;
    if (action == 1)
        b = (a-32 - (r%(128-32)) + (128-32)) % (128-32)+32;
    return b;
}
void test_rotate_char ()
{
//                
    assert(true);
/*                 
                                     
                                                                             
                                                          
                                                                                                      
                                                                                                      
*/  int r;
    cout << "Please enter a positive integer for r: ";
    cin >> r;
    if (r<0)
        return;
    for (char a = '!'; a < 127; a++)
        cout << a << "\t" << a+0 << "\t" << rotate_char(a, r, Encrypt)+0 << "\t"
        << rotate_char(rotate_char(a, r, Encrypt), r, Decrypt)+0 << endl;
}
bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert(true);
/*                 
                                                    
                                                        
*/  string in;
    string out;
    cout << "Please enter a filename for input: ";
    cin >> in;
    cout << "Please enter a filename for output: ";
    cin >> out;
    if (in == out)
    {
        cout << "Error: input and output file are the same";
        return false;
    }
    infile.open(in);
    if (!infile)
    {
        cout << "Input file could not be opened" << endl;
        return false;
    }
    outfile.open(out);
    if (!outfile)
    {
        cout << "Output file could not be opened" << endl;
        return false;
    }
    cout << "Input and output files have been opened successfully" << endl;
    return true;
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
    assert (infile && outfile && initial_value > 0) ;
/*                 
                                                                                           
                                                                                      
*/  char a;
    initialise_pseudo_random(initial_value);
    while(infile) {
        infile.get(a);
        outfile << rotate_char(a, next_pseudo_random_number(), action);
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

