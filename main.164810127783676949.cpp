#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       
#include <cstring>
#include <string>

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

//                           
//                         
char rotate_char (char a, int r, Action action)
{
//                
    assert( a >= 0 && a <128 );
//                                                                                                             
//                                                                                                                        
//                                                                                                                                    
//                                    
//                                                
    int b;
    if (a<32)
        return a;

    if (action == Encrypt)
    {
        b = (a-32 + (r % (128-32)) + (128-32)) % (128-32)+32;
        return b;

    }

    else if (action == Decrypt)
    {
        b = (a - 32 - (r % (128-32)) + (128-32)) % (128-32)+32;
        return b;
    }
}

void test_rotate_char ()
{
    char a = 'a';
    int r = 0;

//                
    assert(r>=0);
//                                                                                                                                                                                                                        
//                                                                               
    /*

                                 
                  
                       
                                         
                                         
                                  
                  
                       
                                         
                                         
                                  
                  
                       
                                         
                                         
                                     
                  
                       
                                         
                                         
    */
    while (r >= 0)
    {
        cout << "Please enter a value for r: " ;
        cin >> r;
        cout << "Character a: " << a << endl;
        cout << "ASCII code of a: " << static_cast<int>(a) << endl;
        cout << "ASCII code of rotate_char(Encrypt): " << rotate_char(a, r, Encrypt) << endl;
        cout << "ASCII code of rotate_char(Decrypt): " << rotate_char(rotate_char(a,r, Encrypt),r, Decrypt) << endl;
    }
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
    string input;
    string output;

    cout << "Please enter two different input and output file names" << endl;
    cout << "Input file: ";
    cin >> input;
    cout << "Output file: ";
    cin >> output;
//                

    assert(input != output);
//                                                                                                     
//                                                                                                     
//                                                               
    infile.open(input.c_str());
    outfile.open(output.c_str());

    if (infile.is_open() && outfile.is_open())
        //                                 
        return true;
    else
        //                                           
        return false;
}

Action get_user_action ()
{
    //               
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
{
    //              
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
    char a;
    int r;
    assert(infile.is_open() && outfile.is_open() /*                   */);
//                                                                                                                                                                               
//                                                         

    initialise_pseudo_random(initial_value);

    while (infile)
    {
        r = next_pseudo_random_number();
        infile.get(a);
        outfile.put(rotate_char(a,r, action));
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
    cout << "All files have been encrypted!" << endl;
    if (!input_file || !output_file)
    {
        cout << "Not all files were closed succesfully. The output might be incorrect." << endl ;
        return -1 ;
    }
    return 0 ;
    //                                                         
    //                   
}

