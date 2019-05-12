//                            
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
//                
assert (r >= 0 && a >= 0 && (action == Encrypt || action == Decrypt));
    if (a < 32) {
        return a;
    }

    switch(action) {
        case Encrypt: return (a-32 + (r % (128-32)) + (128-32)) % (128-32) +32;
        case Decrypt: return (a-32 - (r % (128-32)) + (128-32)) % (128-32) +32;
        default: return -1;
    }
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
string inputfile;
string outputfile;

cout <<"please enter filename to be opened:" <<endl;
cin >> inputfile;
cout <<"please enter filename to be outputted" <<endl;
cin >> outputfile;
if (inputfile == outputfile)
{
    return false;
}
infile.open(inputfile.c_str());
outfile.open(outputfile.c_str());
if (infile && outfile)
{
    return true;
}
else
{
    return false;

}
//                 

return 0;}

Action get_user_action ()
{//               
    assert ( true ) ;
/*                 
                                                                                              
*/
    cout << "Do you want to encrypt the file? (y/n): " << endl ;
    string answer ;
    cin  >> answer ;
    if (answer == "y")
        return Encrypt;
    else
        return Decrypt;
}

void test_rotate_char() {

//                
    int r;
    assert(r >= 0);

        char a;

        cout << "please enter a valid value for r." << endl;
        cin >> r;

        Action answer;
        cout << "please enter a valid printable ASCII character" << endl;
        cin >> a;

        answer = get_user_action();

        cout<< "character a is: " << a <<endl;
        cout << " ASCII code of a is: " << static_cast<int>(a) << endl;
        cout << "the value of the encrypted integer is: " <<  int(rotate_char(a, r, answer)) <<endl;
        cout << "the value of the decrypted integer is: " <<  int(rotate_char((rotate_char(a, r, Encrypt)),r,Decrypt)) << endl;

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
assert( action == Encrypt || action == Decrypt );

initialise_pseudo_random(initial_value);
char a;
int r = next_pseudo_random_number();
infile.get(a);
while (infile)
{
    outfile.put (rotate_char(a, r, action));
    infile.get(a);
    r = next_pseudo_random_number();

}

//                 

}

int main()
{
    //                   
    const Action ACTION = get_user_action() ;
    ifstream inputfile  ;
    ofstream outputfile ;
    if (!open_input_and_output_file (inputfile,outputfile))
    {
        cout << "Program aborted." << endl ;
        return -1 ;
    }
    const int INITIAL_VALUE = initial_encryption_value () ;
    use_OTP (inputfile,outputfile,ACTION,INITIAL_VALUE);
    inputfile.clear () ;
    outputfile.clear () ;
    inputfile.close () ;
    outputfile.close () ;

    if (!inputfile || !outputfile)
    {
        cout << "Not all files were closed succesfully. The output might be incorrect." << endl ;
        return -1 ;
    }
    return 0 ;
}

