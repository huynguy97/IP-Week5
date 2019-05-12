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
    assert (a < 128);
/*                
                                          */
    char b;
    switch (action){
    case Encrypt : if (a < 32) {
                        b = a;
                        }else{
                            b = (a-32+(r%(128-32))+(128-32))%(128-32)+32;
                            }
                    return b;
    case Decrypt : if (a < 32) {
                        b = a;
                        }else{
                            b = (a-32-(r%(128-32))+(128-32))%(128-32)+32;
                            }
                        return b;
    }
}

void test_rotate_char ()
{
//                
    assert(true);
/*                                                                                                                           
                                                                                                                              
                                                                         
*/
    int r;
    char a;
    cout << "Please enter an integer value for r: ";
    cin >> r;
    while(r > 0 && r <= 65536){
        for(int counter = 32; counter < 128; counter = counter + 1) {
            a = static_cast<char>(counter);
            cout << "\n\nCharacter: " << a << "\nASCII code: " << static_cast<int>(a);
            cout << "\nEncryption: " << rotate_char (a, r, Encrypt);
            cout << "\nDecription: " << rotate_char (rotate_char(a, r, Encrypt), r, Decrypt);
        }
        cout << "\n\nPlease enter an integer value for r: ";
        cin >> r;
    }
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert (true);
/*                                                                                                                               
                                                                                                                            
*/
    string inputname;
    string outputname;
    cout << "Please enter two file names for input and output.";
    cout << "\nInput file name: ";
    cin >> inputname;
    cout << "Output file name: ";
    cin >> outputname;
    if (inputname != outputname){
        infile.open(inputname);
        outfile.open(outputname);
        if (infile && outfile){
            cout << "\nThe files have been opened succesfully!";
            return true;
        }else{
            cout << "\nThe files could not be opened.";
            return false;
        }
    }else{
        cout << "\nError, these files have the same name...";
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
/*                                                                                                                  
                                                                                                                
                              
*/
    char a;
    initialise_pseudo_random(initial_value);
    infile.get(a);
    while(infile){
        outfile.put(rotate_char(a, next_pseudo_random_number(), action));
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

