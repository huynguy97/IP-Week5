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
    assert(r > 0 && r <= 65536 && a >= 0);
/*                 
                                                               
*/

if (a < 32)
    return a;
else
    if (action == Encrypt)
        return ((a-32 + (r % (128-32)) + (128-32)) % (128-32)+32);
    else
        return ((a-32 - (r % (128-32)) + (128-32)) % (128-32)+32);
}

void test_rotate_char (int& r)
{
//                
    assert(r > 0 && r < 65536);
/*                 
                                                                                                
                                                                                              
                                                                                             
                                          
*/
    cout << "Enter a r between 0 and 65536 ";
    cin >> r;
    if (r<0 || r > 65536)
        cout << "This r is not valid";
    else
        for (char a = 0; a < 127; a = a + 1)
        cout << a << " , " << static_cast<int> (a) << " , " << rotate_char( a, r, Encrypt) << " , " << rotate_char (rotate_char (a, r, Encrypt), r, Decrypt) << endl;
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert(true);
/*                
                                                                                         
*/
string input;
string output;

cout << "Enter the name of your input file." ;
cin >> input;
cout << "Enter the name of your output file." ;
cin >> output ;

if (infile == outfile)
    {
        cout << "ERRROR: Your input file is the same as your output file." ;
        return false;
    }
else
    {
        infile.open(input.c_str());
        outfile.open(output.c_str());
    }
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
/*                
                                                                                                           
                                                                             
*/

char c;
infile.get(c);
initialise_pseudo_random ( initial_value);

while (infile)
{
    initial_value = next_pseudo_random_number();
    rotate_char (c, initial_value, action);
    outfile.put(rotate_char (c, initial_value, action));
    c = c + 1 ;
    infile.get(c);
}

}

int main()
{
/*          
                        
             
*/

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

