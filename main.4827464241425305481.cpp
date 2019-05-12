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
//                                                        
assert (a >= 0 && a < 128);
//                 
//                                                                                     
if (a >= 32) {
    //                                                
    if (action == Encrypt){
        return((a - 32  + (r % (128 - 32)) + (128 - 32)) % (128 - 32) + 32);
    } if (action == Decrypt) {
        return((a - 32  - (r % (128 - 32)) + (128 - 32)) % (128 - 32) + 32);
        }
    }
return a;
}

void test_rotate_char ()
{
    //                   
    cout << "Please enter a value for r" << endl;
    int r;
    cin >> r;
//                
    assert (r > 0 && r <= 65536) ;
//                 
//                                                                                                                                         
//                                                                                              
char a = 32;
while (a < 127) {
    cout << a << " " << (int) a << " " << rotate_char(a, r, Encrypt) + 0 << " " << rotate_char(rotate_char(a, r, Encrypt), r, Decrypt) + 0 << endl;
    a++;
}

}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert (true);
//                 
    cout << "Enter a filename for input" << endl;
    string file_input;
    cin >> file_input;
    cout << "Enter a filename for output" << endl;
    string file_output;
    cin >> file_output;

    if (file_input == file_output) {
        cout << "ERROR: File names are identical" << endl;
        return false;
    } else {
        infile.open (file_input.c_str());
        outfile.open (file_output.c_str());
        if (infile && outfile) {
            cout << "Files were opened successfully" << endl;
        } else {
            cout << "Files could not be opened" << endl;
        }
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
    while (initial_value <= 0 || initial_value > 65535)
    {
        cout << "Please enter the initial coding value (greater than 0 and less than 65536)" << endl ;
        cin  >> initial_value ;
    }
    return initial_value ;
}

void use_OTP (ifstream& infile, ofstream& outfile, Action action, int initial_value)
{
//                
//                                                   
    assert (infile.is_open() && outfile.is_open());
//                 
    char c;
    //                                                                           
    initial_value = next_pseudo_random_number();
    infile.get(c);
    cout << rotate_char(c, initial_value, action);
    outfile.put(rotate_char(c, initial_value, action));
    //                                                                                                                     
    while (infile) {
        initial_value = next_pseudo_random_number();
        infile.get(c);
        cout <<  rotate_char(c, initial_value, action);
        outfile.put(rotate_char(c, initial_value, action));

    }
}

int main()
{
    //                
    //                 
    //                                            

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
    //                                              
    initialise_pseudo_random(INITIAL_VALUE);
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

