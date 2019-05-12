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

char rotate_char (char a, int r, Action action) //                                               
{//                
    assert (action == Encrypt || action == Decrypt);
//                 
    if (action == Encrypt) {
        if (a < 32) {
            return (a);
        } else {
            return (char)((a - 32 + (r % (128 - 32)) + (128 - 32)) % (128 - 32) + 32);
        }
    }
    else {
        if (a < 32) {
            return a;
        } else {
            return (char )((a + 32 + (r % (128 - 32)) + (128 - 32)) % (128 - 32) + 32);
        }
    }
}

void test_rotate_char () //                             
{
//                
    int r;
    cout << "Fill in a r ";
//                 
    while (true) {
        cin >> r;
        if (r < 0) {
            cout << "r is lower then 0";
            break;
        }
        for (int a = 0; a < 128; ++a) {
            int ASCII = rotate_char((char) a, r, Encrypt);
            cout << (char) a ;
            cout << " ";
            cout << a;
            cout << " ";
            cout << ASCII;
            cout << " ";
            cout << (int) rotate_char((char) ASCII, r, Decrypt);
            cout << "\n";
        }
    }

}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile) //                                                                                                                                                                               
{
    string inputfile;
    string outputfile;
    cout << "Give an inputfile ";
    cin >> inputfile;
    cout << "Give an outputfile ";
    cin >> outputfile ;
    infile.open (inputfile.c_str());
    outfile.open (outputfile.c_str());

    if (infile.is_open() && outfile.is_open() && inputfile != outputfile)
    {
        return true;
    }
    else {
        cout << "Error: One of the 2 or both files didn't open ";
        cout << "\n";
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

void use_OTP (ifstream& infile, ofstream& outfile, Action action, int initial_value) //                                                                                
{
//                
assert (true );
//                 
char a;
infile.get(a);
int r = initial_encryption_value();
char b = rotate_char(a, r, Encrypt);
outfile.put (b);

while (infile)
{
    outfile.put (b);
    infile.get (a);
}
infile.close();
outfile.close();
}

int main()
{
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

