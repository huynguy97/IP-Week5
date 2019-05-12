#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       

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
    assert(r>0 && r<=65536);

/*                 
                                                        
*/
    if (a<32)
        return a;
    else if (action == Encrypt)
        return (a - 32 + (r % (128 - 32)) + (128 - 32)) % (128 - 32) + 32;
    else
        return (a - 32 - (r % (128 - 32)) + (128 - 32)) % (128 - 32) + 32;

}

void test_rotate_char ()
{
//                
    assert(true);

/*                 
                                                                        
                                                             
*/
    int r = 0;
    char a;
    do {
        cout << "Enter r value: ";
        cin >> r;
        for (char a = 32; a >= 32 && a < 128; a++) {
            cout << "Char:\t\t" << a << endl;
            cout << "Encrypted Char:\t" << rotate_char(a, r, Encrypt) << endl;
            cout << "Decrypted Char:\t" << rotate_char(rotate_char(a, r, Encrypt), r, Decrypt) << endl;
        }
    } while (r >= 0);
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert(!(infile.is_open() || outfile.is_open()));

/*                 
                                                                   
                                                           
*/
    string in;
    string out;

    cout << "Enter input file:\t";
    cin >> in;
    cout << "Enter output file:\t";
    cin >> out;
    if (in == out) {
        cout << "File names are identical" << endl;
        return false;
    }
    infile.open(in.c_str());
    outfile.open(out.c_str());
    if (infile.is_open() && outfile.is_open())
        return true;
    return false;
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
    char character;
    char action_char;
    initialise_pseudo_random(initial_value);
    while (infile) {
        infile.get(character);
        action_char = rotate_char(character, next_pseudo_random_number(), action);
        outfile.put(action_char);
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

