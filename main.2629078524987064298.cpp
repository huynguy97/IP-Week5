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

void rotate_char (char a, int r, Action action, int& b)
{
//                
    assert (int(a) >= 0 && int(a) <=127);
    assert (r >0 && r <= 65536);
    assert (action == Encrypt || action == Decrypt);

/*                 
                                                         
*/
    if (action == Encrypt)
    {
        if (int (a) < 32)
            b = a;
        else
            b = (a- 32 + (r % (128-32))) % (128-32) + 32;
    }
    if (action == Decrypt)
    {
        if (a < 32)
            b = a;
        else
            b = (a - 32 - (r % (128-32)) + (128-32)) % (128-32) + 32;
    }
}

void test_rotate_char ()
{
/*                
                               
                   
                                                              
                                                                                  
*/
    int r ;
    cout << "Please insert a value for r with 0<r<65536" << endl;
    cin >> r ;
    cout << "You entered; " << r << endl;
    if (r < 0)
    {
        cout << "You entered an invalid number, the program will stop." << endl;
        return;
    }

    char a;
    a = 0;
    int b = 0;
    while (int(a) >= 0 && int(a) < 128 )
    {
        cout << "ASCII Value of " << a << " is " << int(a) << endl;
        rotate_char (a, r, Encrypt, b);
        rotate_char (a, r, Decrypt, b);
        a = a + 1;
        cout << "Updated value of a = " << a << endl;
    }
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert (true);

/*                 
                                               
                                                                                  
                                                             
*/
    string in_filename;
    string out_filename;
    cout << "Please insert the input file name of your choice " << endl;
    cin >> in_filename;
    cout << "Please insert the output file name of your choice " << endl;
    cin >> out_filename;
    cout << "\nYou selected input file: " << in_filename << "; and output file: " << out_filename << endl;
    if (in_filename == out_filename)
    {
        cout << "\n Something is wrong... The name of your input and output file is identical." << endl;
        cout << "The program will stop now." << endl;
        return false;
    }
    cout << "\n Trying to open files ..." << endl;
    infile.open(in_filename.c_str());
    outfile.open(out_filename.c_str());
    if (infile.is_open())
    {
        cout << "\nYour input file has been opened successfully!" << endl;
    }
    else
    {
        cout << "\nUnfortunately, I am not able to open your input file." << endl;
        cout << "The program will stop now." << endl;
        return false;
    }
    if (outfile.is_open())
    {
        cout << "Your output file has been opened successfully!" << endl;
    }
    else
    {
        cout << "\nUnfortunately, I am not able to open your output file." << endl;
        cout << "The program will stop now." << endl;
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
    assert (initial_value >0 && initial_value <= 65536);
    assert (action == Encrypt || action == Decrypt);

/*                 
                                                                                                 
*/
    initialise_pseudo_random(initial_value);
    int next = next_pseudo_random_number();
    int no_of_chars = 0;
    char a;
    int b;
    infile.get (a);
    while (infile)
    {
        rotate_char (a, next, action, b);
        outfile.put (b);
        no_of_chars ++;
        infile.get(a);
        next = next_pseudo_random_number();
    }
    cout << "\n Check your output file for the encrypted or decrypted message ..." << endl;
}

int main()
{
    const Action ACTION = get_user_action() ;
    ifstream in_filename  ;
    ofstream out_filename ;
    if (!open_input_and_output_file (in_filename,out_filename))
    {
        cout << "Program aborted." << endl ;
        return -1 ;
    }
    const int INITIAL_VALUE = initial_encryption_value () ;
    use_OTP (in_filename,out_filename,ACTION,INITIAL_VALUE);
    in_filename.clear () ;
    out_filename.clear () ;
    in_filename.close () ;
    out_filename.close () ;
    if (!in_filename || !out_filename)
    {
        cout << "Not all files were closed successfully. The output might be incorrect." << endl ;
        return -1 ;
    }
    return 0 ;
}

