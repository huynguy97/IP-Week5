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

char rotate_char (int r, char a, Action action)
{

//                
    assert( r >= 0 && r <= 655355);

//                 
//                                                                                                                                          

    int b;

    int ascii = (int) a;
    if(ascii < 32) {
        b = ascii;
    } else if (action == Encrypt){
        b = (a-32 + (r % (128-32))) % (128-32)+32;

    } else {
        b = (a-32 - (r % (128-32)) + (128-32)) % (128-32)+32;

    }

    return char(b);

}

void test_rotate_char ()

{
    //             
    assert (true);

    //               
    //                                                                                       
    int r;
while (r > 0) {
    cout << "Enter random number: ";
    cin >> r;
    for (int i = 0; i < 128; i++) {
        char b = char(i);
        cout << b << " ";
        cout << i << " ";
        cout << (int) rotate_char(r, b, Encrypt) << " ";
        cout << (int) rotate_char(r, (rotate_char(r, b, Encrypt)), Decrypt) << " ";
        cout << "\n";

    }
}

}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{

//                
    assert (true);
//                 
//                                                                                         

string filename_input, filename_output;

cout << "Enter input filename: ";
cin >> filename_input;
cout << "Enter output filename: ";
cin >> filename_output;

if (filename_input == filename_output) {
        cout << "Input filename can't be output file name";
        return false;
}

infile.open(filename_input.c_str() );
outfile.open(filename_output.c_str() );

if (infile.is_open() && outfile.is_open()) {
    cout << "Files opened successfully" << "\n";
    return true;
} else if(!infile.is_open()) {
    cout << filename_input << " could not be opened" << "\n";
    return false;
}
else {
    cout <<  filename_output<< " could not be opened" << "\n";
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
assert (infile.is_open() && outfile.is_open());
//                 
//                                                              

    char c;
    int r;

    while(infile.get(c)){
        r = next_pseudo_random_number();
        outfile.put(rotate_char(r, c, action));

    }

    cout << "Encrypted succesfully";

}

int main()
{

    const Action ACTION = get_user_action() ;

    ifstream input_file;
    ofstream output_file ;

    if (!open_input_and_output_file (input_file,output_file))
    {
        cout << "Program aborted." << endl ;
        return -1 ;
    }
    const int INITIAL_VALUE = initial_encryption_value () ;
    initialise_pseudo_random(INITIAL_VALUE);
    use_OTP (input_file,output_file,ACTION,INITIAL_VALUE);
    //                     
    //                      
    input_file.close () ;
    output_file.close () ;

    if (!input_file || !output_file)
    {
        cout << "Not all files were closed succesfully. The output might be incorrect." << endl ;
        return -1 ;
    }
    return 0 ;

}

