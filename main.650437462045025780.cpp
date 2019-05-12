#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       

using namespace std;

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
    assert(a > 0 && r >= 0);
    //                 
    //                                                     
    if(a < 32)
        return a;
    else if (a >= 32) {
        switch(action) {
        case Encrypt:
            return (a-32+(r%(128-32)))%(128-32)+32;
            break;
        case Decrypt:
            return (a-32-(r%(128-32))+(128-32))%(128-32)+32;
            break;
        default:
            cout << "Invalid action.";
            return '\0';
        }
    }
    return '\0';
}

void test_rotate_char ()
{
    //                
    assert(true);
    //                 
    //                                                                             
    //                                                                                 
    //                                                                           
    int r = 1;
    char a = 'a';
    cout << "Enter a value for r: ";
    cin >> r;
    assert(r > 0);
    cout << "Enter a value for a: ";
    cin >> a;
    cout << a << endl << a + 0 << endl << rotate_char(a, r, Encrypt) + 0 << endl << rotate_char(rotate_char(a, r, Encrypt) + 0, r, Decrypt) + 0 << endl;
    }

void ask_for_files(string& ifile, string& ofile)
{
    //               
    assert(true);
    //                
    //                                                                 
    cout << "Please give the input file name (without spaces): ";
    cin >> ifile;
    cout << "Please give the output file name (without spaces): ";
    cin >> ofile;
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
    //                
    assert(true);
    //                 
    //                                                                      
    string ifile = "";
    string ofile = "";
    ask_for_files(ifile, ofile);
    if(ifile == ofile) {
        cout << "Error. The file names are identical." << endl;
        return false;
    }
    infile.open(ifile.c_str());
    outfile.open(ofile.c_str());
    if (infile && outfile) {
        cout << "Successfully opened input file and output file." << endl;
        return true;
    } else {
        cout << "Failed to open input file and output file." << endl;
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
    assert(true);
    //                 
    //                                                                                           
    initialise_pseudo_random(initial_value);
    char c = 'a';
    switch(action) {
        case Encrypt:
            while (infile) {
                infile.get(c);
                char e = rotate_char(c, next_pseudo_random_number(), Encrypt);
                outfile.put(e);
            }
            break;
        case Decrypt:
            while (infile) {
                infile.get(c);
                char d = rotate_char(c, next_pseudo_random_number(), Decrypt);
                outfile.put(d);
            }
            break;
        default:
            cout << "Invalid action. (bug?)";
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

