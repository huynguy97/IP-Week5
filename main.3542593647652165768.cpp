//                          
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
assert( !(r < 0 && r > 65535));
//                                                                                                                                
//                          

if (action == Encrypt)
{
if (a < 32)
{
    return a;
}

else
{
    return (a-32 + (r % (128-32))) % (128-32) +32;
}
}
if (action == Decrypt)
{
    if (a < 32)
    {
        return a;
    }
    else
    {
        return (a-32 - (r % (128 - 32)) + (128 - 32)) % (128 - 32) +32;
    }
}
}
void test_rotate_char ()
{
//                
assert(true);

//                                       

int r;

cout << "Enter the value of r: " << endl;
cin >> r;
while (r >= 0)
{
    for(char show_a=32; show_a<=127 && show_a>= 0; show_a++)
    {
        int show_ASCII_a, show_ASCII_Enc_a, show_ASCII_Dec_a;
        show_ASCII_a = show_a;
        show_ASCII_Enc_a = rotate_char(show_ASCII_a,r,Encrypt);
        show_ASCII_Dec_a = rotate_char(show_ASCII_Enc_a,r,Decrypt);
        cout << show_a << "\t" << show_ASCII_a << "\t" << show_ASCII_Enc_a << "\t" << show_ASCII_Dec_a << endl;
    }

    cout << "Enter the value of r: " << endl;
    cin >> r;
}

}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
assert(true);
//                 
string inputfile_name;
cout << " Enter inputfile name: " << endl;
cin >> inputfile_name;
string outputfile_name;
cout << " Enter outputfile name: " << endl;
cin >> outputfile_name;

infile.open(inputfile_name.c_str());
outfile.open(outputfile_name.c_str());

if (inputfile_name == outputfile_name)
{
    cout << "ERROR input and output are the same!" << endl;
    return false;
}
else{
if (infile.is_open() && outfile.is_open()) {
        cout << "The files opened correctly!" << endl;
    return true;
} else {
        cout << "ERROR, the files doesn't opened correctly!" << endl;
    return false;
        }
    }
}
Action get_user_action ()
{
    assert ( true ) ;
/*                 
                                                                                              
*/
    cout << "Do you want to encrypt the file? (y/n): " ;
    string answer ;
    cin  >> answer ;
    if (answer == "y"){
        cout << "****ENCRYPTION****" << endl;
        return Encrypt;
        }
    else
        cout << "****DECRYPTION****" << endl;
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
assert(infile.is_open() && outfile.is_open() && !(initial_value < 0 || initial_value > 65535));

//                 
    initialise_pseudo_random(initial_value);
    int Result = next_pseudo_random_number();
    char c;
    infile.get(c);

    while(infile)
    {
        char Encryption = rotate_char(c, Result, action);
        outfile.put(Encryption);
        Result = next_pseudo_random_number();
        infile.get(c);
    }

}

int main()
{
    test_rotate_char();
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

