//                       

#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       
#include <string>

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
    assert((int)a >= 0 && (int)a < 128);
//                               

    if(action == Encrypt){
        if((int)a < 32){
            return a;
        }else{
            return (char)(((int)a - 32 + (r % (128 - 32))) % (128-32) + 32);
        }
    }else{
        if((int)a < 32){
            return a;
        }else{
            return (char)(((int)a - 32 - (r % (128 - 32)) + (128 - 32)) % (128-32) + 32);
        }
    }

}

void test_rotate_char ()
{
    int r = 1;

    while(r > 0){
        cout << "Please enter a value for r (bigger than 0): ";
        cin >> r;

    //                       
        assert(r > 0);
    //                                                  

        initialise_pseudo_random (r);

        for(int i = 0; i < 128; i++){
            cout    << "Character: " << (char)i
                    << " ASCII Code: " << i
                    << " Encrypt: " << rotate_char ((char)i, r, Encrypt)
                    << " Encrypt and Decrypt: " << rotate_char (rotate_char ((char)i, r, Encrypt), r, Decrypt) << endl;
        }
    }
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
    string infileName, outfileName;

    cout << "Enter the file name for input: ";
    cin >> infileName;

    cout << "Enter the file name for output: ";
    cin >> outfileName;

//                                                          
    assert(infileName != outfileName);
//                                        

    infile.open(infileName.c_str());
    if(infile.is_open())
        cout << "The input file is opened.\n";
    else
        cout << "The input file cannot be opened.\n";

    outfile.open(outfileName.c_str());
    if(outfile.is_open())
        cout << "The output file is opened.\n";
    else
        cout << "The output file cannot be opened.\n";

    return infile.is_open() && outfile.is_open();
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

    initialise_pseudo_random(initial_value);

    char next;
    infile.get(next);
    while(!infile.eof()){
        outfile << rotate_char (next, next_pseudo_random_number(), action);
        infile.get(next);
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

