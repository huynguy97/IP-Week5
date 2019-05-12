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
assert (true);
//                                                                      
int b;
    if(action == Encrypt)
    {
        if(a >= 32)
            {
            b=(a-32+(r% (128-32))+ (128-32))%(128-32)+32;
            }
        else
            b=a;
    }
    if(action == Decrypt)
    {
        if(a >= 32)
        {
            b=(a-32-(r% (128-32))+ (128-32))%(128-32)+32;
        }
        else
            b=a;
    }
return(static_cast<char>(b));

}

void test_rotate_char ()
{
//                
assert(true);
//                                                                                            

    char a;
    int r;
    cout << "Enter r: ";
    cin >> r;
    while (r<=0 || r>=65536)
    {
        cout << "Please enter a valid number for r: ";
        cin >> r;
    }
    cout << "you entered " << r << endl;
    cout << "Enter a: ";
    cin >> a;
    cout << "You Entered: " << a << " with ASCII: " << static_cast<int>(a) << endl;
    rotate_char(a,r,Encrypt);
    cout << "Encrpytion Result: " << rotate_char(a,r,Encrypt) << " with ASCII: " << static_cast<int>(rotate_char(a,r,Encrypt)) << endl;
    rotate_char(rotate_char(a,r,Encrypt),r,Decrypt);
    cout << "Decryption Result: " << rotate_char(rotate_char(a,r,Encrypt),r,Decrypt) << " with ASCII: " << static_cast<int>(rotate_char(rotate_char(a,r,Encrypt),r,Decrypt)) << endl;

}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
assert(true);
//                                                                                      
string input_file_name;
string output_file_name;

    cout << "Enter the name of Input File: ";
    cin >> input_file_name;
    cout << "Enter a name for Output File: ";
    cin >> output_file_name;
    if (input_file_name==output_file_name)
    {
       return false;
    }
    else {
        infile.open(input_file_name);
        outfile.open(output_file_name);
        if (infile.is_open() && outfile.is_open())
        {return true;}
        else
        {return false;}
    }

}

Action get_user_action ()
{//               
    assert ( true ) ;
/*                 
                                                                                              
*/
    cout << "Do you want to encrypt or decrypt the file? (encrypt/decrypt): " ;
    string answer ;
    cin  >> answer ;
    if (answer == "encrypt")
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
char c;
infile.get(c);
while(infile)
{
    initial_value = next_pseudo_random_number();
    outfile.put(rotate_char(c, initial_value, action));
    infile.get(c);
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
//                       
    return 0 ;
}

