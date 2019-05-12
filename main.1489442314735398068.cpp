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

char rotate_char (char a, int r, Action action)
{
//                
    assert(!(a >= 128));
    //                 
    char b;
    if (action == Encrypt){
        if (a < 32){
            b = a;
        }
        else{
            b = (a-32 + (r % (128-32)))%(128-32) + 32;
        }
    }
    if (action == Decrypt){
        if (a < 32){
            b = a;
        }
        else{
            b = (a-32 - (r % (128-32))+(128-32))% (128-32) + 32;
        }
    }
    return b;

}

void test_rotate_char ()
    {
//                
    assert(true);

//                 
    rotate_char('a', 1, Decrypt);
    rotate_char('a', 42, Decrypt);
    rotate_char('a', 96, Decrypt);
    rotate_char('a', 65535, Decrypt);
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
    string in_file;
    string out_file;
    cout << "enter input and output file pls" << endl;
    cin >> in_file >> out_file;
    infile.open(in_file.c_str());
    outfile.open(out_file.c_str());

//                
    assert(infile != outfile && "Input file must not equal out put file");
//                 
     if (infile && outfile){
        return true;
     }
     else{
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

    initialise_pseudo_random(initial_value);
    char character;

    if(action == Encrypt){
        //                    
        infile.get(character);
        while(infile){
            outfile.put(rotate_char(character, next_pseudo_random_number(), Encrypt));
            infile.get(character);
        }
    }
    if (action == Decrypt){
        //                    
        infile.get(character);
        while(infile){
            outfile.put(rotate_char(character, next_pseudo_random_number(), Decrypt));
            infile.get(character);
        }

    }
}

int main()
{
    cout << rotate_char(rotate_char('%',96,Encrypt),96,Decrypt);
    const Action ACTION = get_user_action() ;
    ifstream input_file ;
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

