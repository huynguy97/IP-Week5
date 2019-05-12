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
    assert(a >= 0 && a < 128);
    assert(r >= 0);
/*                 
                         
                                       
*/
    if (a < 32 )
        return a;
    else
    {
        int temp_int = r% (128-32);
        if( action == Decrypt)
            temp_int *= -1;

        return ((a-32+ temp_int)+ (128-32)) %(128-32)+32;
    }
}

void test_rotate_char ()
{
//                
    assert(true);
/*                 
                                     
                                         
*/
    int r = 1;
    cin >> r;
    while (r >= 0)
    {
        for (int i = 0; i < 128; i++)
        {
            char ascii_char = i;
            int encrypt_int = rotate_char(ascii_char, r, Encrypt);
            int decrypt_int = rotate_char(encrypt_int, r, Decrypt);

            cout << ascii_char << "    " << i << "    " << encrypt_int << "    " << decrypt_int << endl;
        }

        cin >> r;
    }

}

void read_file_names (string& input_name, string& output_name )
{
//                
    assert(true);
/*                 
                                                              
*/
    cout << "Enter a name for the input file (with extension): ";
    cin >> input_name;
    cout << "Enter a name for the output file (with extension) : ";
    cin >> output_name;
}

void feedback_open_files (ifstream& infile, ofstream& outfile)
{
//                
    assert(true);
/*                 
                                                            
*/

    string temp_name = "Input";
    if (infile)
        cout << temp_name << " file has been opened successfully" << endl;
    else
        cout << temp_name << "file could not been opened" << endl;

    temp_name = "Output";
    if (outfile)
        cout << temp_name << " file has been opened successfully" << endl;
    else
        cout << temp_name << " file could not been opened" << endl;
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert(true);
/*                 
                                                            
                                                                                                                  
*/
    string infile_name = "input.dat";
    string outfile_name = "output.dat";
    read_file_names(infile_name, outfile_name);

    if (infile_name == outfile_name)
    {
        cout << "Input and Output file names are the same." << endl;
        return false;
    }
    else
    {
        infile.open(infile_name.c_str());
        outfile.open(outfile_name.c_str());
        feedback_open_files(infile, outfile);

        if (infile && outfile)
            return true;
        else
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
    assert(infile && outfile);
    assert(initial_value >= 0 && initial_value <= 65535);
/*                 
                                                                                   
*/
    char c = ' ';
    while (infile.get(c))
    {
        outfile.put(rotate_char(c, initial_value, action));
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

