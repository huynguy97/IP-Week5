#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       

using namespace std;

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
    assert (r >= 0 && a >= 0 && (action == Encrypt || action == Decrypt));
/*
                                                                      
                                                                                  
                                                                                       
*/

    int aNum = static_cast<int>(a);
    int b;
    if (aNum < 32)
    {
        b = a;
    }
    else
    {
        if (action == Encrypt)
        {
            b = (a-32 + (r%(128-32))+(128-32))%(128-32)+32;
        }
        if (action == Decrypt)
        {
            b = (a-32 - (r%(128-32))+(128-32))%(128-32)+32;
        }
    }
    return static_cast<char>(b);
}

int getR ()
{
//                
    assert(true);
/*
                                                                            
*/
    int r;
    cout << "Please enter a random nonnegative number: ";
    cin >> r;
    if (r >= 0)
    {
        return r;
    }
}

string askRepeat ()
{
//                
    assert (true);
/*
                   
                                                                                                       
*/
    string answer;
    cout << "Do you want to execute rotate_char (y/n)? ";
    cin >> answer;
    return answer;
}

void test_rotate_char ()
{
//                
    assert(true);
/*
                   
                                                                                                                                 
*/
    string answer = askRepeat();
    while (answer == "y")
    {
        int r = getR();
        int a = 0;
        while (a < 128)
        {
            char A = static_cast<char>(a);
            char b = rotate_char(A, r, Encrypt);
            cout << "Character " << A << " has ASCII code " << a << ", the ASCII code after encryption is " << static_cast<int>(b) <<
                 " and the ASCII code after decryption " << static_cast<int>(rotate_char((rotate_char(A, r, Encrypt)), r, Decrypt)) << "." << endl;
            a = a+1;
        }
        answer = askRepeat();
    }
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert (true);
/*
                   
                                                                                                         
*/
    cout << "Please type the name of the file with your input (without any layout symbols): " ;
    string input_file;
    cin >> input_file;
    cout << endl << "Please type the name of the file you want to add the output (without any layout symbols): " ;
    string output_file;
    cin >> output_file;
    if (input_file == output_file)
    {
        return false;
    }
    infile.open(input_file.c_str());
    outfile.open(output_file.c_str());
    if (infile && outfile)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Action get_user_action ()
{
//                
    assert (true) ;
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
{
//              
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
    assert((action == Encrypt || action == Decrypt) && initial_value >= 0 && initial_value <= 65535);
/*
                   
                                                                               
*/
    initialise_pseudo_random(initial_value);
    char a;
    int r = next_pseudo_random_number();
    infile.get(a);
    while (infile)
    {
        outfile.put(rotate_char(a, r, action));
        infile.get(a);
        r = next_pseudo_random_number();
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

