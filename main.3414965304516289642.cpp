/*                                    
                  
                        
                      
   */

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
    assert(r >= 0);

/*                 
                                                                       */
    int character = int(a);
    int b = character;

    if (character >= 32 && action == Encrypt)
        b = (character - 32 + (r % (128 - 32)) + (128 - 32)) % (128 - 32) + 32;
    else if (character >= 32 && action == Decrypt)
        b = (character - 32 - (r % (128 - 32)) + (128 - 32)) % (128 - 32) + 32;
    return char(b);
}

void test_rotate_char ()
{
//                
    assert(true);

//                 
    int r;
    cout << "Fill in r:";
    cin >> r;
    while (r >= 0){
        for (int i = 32; i < 128; ++i) {
            char a = char(i);
            cout << a <<  "\t" << i << "\t" << rotate_char (a, r, Encrypt) <<
                 "\t" << rotate_char (rotate_char (a, r, Encrypt), r, Decrypt) << endl;
        }
        cout << "Fill in another r:";
        cin >> r;
    }
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile) {
//                
    assert(true);

/*                 
                                                                                         
    */
    string file_name_input;
    string file_name_output;

    cout << "Enter an input file name (without spaces):" << endl;
    cin >> file_name_input;
    cout << "Enter an output file name (without spaces):" << endl;
    cin >> file_name_output;

    while (file_name_input == file_name_output)
    {
        cout << "Input and output file names are identical. Enter another file name." << endl;
        cin >> file_name_output;
    }

    infile.open(file_name_input);
    outfile.open(file_name_output);

    if (infile && outfile) {
        cout << "Files opened successfully" << endl;
        return true;
    } else {
        cout << "Files could not be opened" << endl;
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
/*                 
                                                                                           */
    char c;
    initialise_pseudo_random (initial_value);

    infile.get(c);
    while(infile)
    {
        outfile.put(rotate_char(c, next_pseudo_random_number(), action));
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
        cout << "Not all files were closed successfully. The output might be incorrect." << endl ;
        return -1 ;
    }
    return 0 ;
}

