#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       
#include <string>           //                   

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
    assert(r >= 0);

    return (char) (a < 32 ? a : (a-32 + (action == Encrypt ? 1 : -1) * (r % (128-32)) + (128-32)) % (128-32) + 32);
//                 
    //                                                                 
}

void test_rotate_char ()
{
    cout << "Please enter the value of r, terminate by entering a value < 0:" << endl;

    int r;
    while (true) {
        cin >> r;
        if (r < 0) {
            break;
        }
        for (int a = 0; a < 128; ++a) {
            int encrypted = rotate_char((char) a, r, Encrypt);
            cout << (char) a << '\t' << a << '\t' << encrypted << '\t' << (int) rotate_char((char) encrypted, r, Decrypt) << endl;
        }
    }
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    string input;  //                           
    string output;
    cout << "Please enter input file name: " << endl;
    cin >> input; //                             
    cout << "Please enter output file name: " << endl;
    cin >> output; //                              

    infile.open(input.c_str()); //               
    outfile.open(output.c_str()); //               

//                                                                   
    assert(infile.is_open() && outfile.is_open() && input != output); //                                                                              
    return true; //                                        
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

    initialise_pseudo_random(initial_value);

    for (int i; (i = infile.get()) != EOF; ) {
        outfile << rotate_char((char) i, next_pseudo_random_number(), action);
    }

//                 
    //                                                               
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

