//                                 
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

//                                       
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

//                                                              
char rotate_char (char a, int r, Action action)
{
//                
    assert (r>=0 && r < 65536);
    assert (int(a) >= 0 && int(a) < 128);
/*                 
                                                                                                  
*/
    if (action == Encrypt)
    {
        if (int(a) < 32)
        {
            return a;
        }
        else
        {
            int a_encrypt = (int(a) - 32 + (r % (128-32)) + (128-32)) % (128-32) + 32;
            return a_encrypt;
        }
    }
    else
    {
        if (int(a) < 32)
        {
            return a;
        }
        else
        {
            int a_decrypt = (int(a) - 32 - (r % (128-32)) + (128-32)) % (128-32) + 32;
            return a_decrypt;
        }
    }
}

//                                                                                 
void test_rotate_char ()
{
/*                 
                                                                       
                                                             
                                             
*/

    char a;
    int r;

    cout << "Give a value for a: " << endl;
    cin >> a;
    //           
    assert (int(a) >= 0 && int(a) < 128);

    string answer = "y";
    while (answer == "y")
    {
        cout << "Give a value for r: " << endl;
        cin >> r;
        //           
        assert (r>0 && r < 65536) ;

        cout << "a\tASCII of a\tASCII of encrypted a\tASCII of decrypted encrypted a" << endl;
        cout << a << "\t" << int(a) << "\t\t" << int(rotate_char(a,r,Encrypt)) << "\t\t\t" << int(rotate_char(rotate_char(a,r,Encrypt),r,Decrypt)) << endl;

        cout << "Do you want to try with another r value? (y/n): " << endl;
        cin >> answer;
    }
}

//                                                 
bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert (!infile.is_open() && !outfile.is_open())
/*                 
                                                                     
                                 
*/
    string input_name,output_name;

    cout << "Enter the input filename: " << endl;
    cin >> input_name;
    cout << "Enter the output filename: " << endl;
    cin >> output_name;

    assert (input_name != output_name) ;

    infile.open(input_name.c_str() );
    outfile.open(output_name.c_str() );

    if (infile.is_open() && outfile.is_open())
    {
        return true;
    }
    return false;
}

//                                                                               
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

//                                                 
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

//                                  
void use_OTP (ifstream& infile, ofstream& outfile, Action action, int initial_value)
{
//                
    assert (initial_value >= 0 && initial_value < 65536);
    assert (infile.is_open() && outfile.is_open());
/*                 
                                                                       
*/

    initialise_pseudo_random (initial_value);
    char a;

    while (infile)
    {
        seed = next_pseudo_random_number();
        infile.get(a);
        //               
        outfile.put(rotate_char (a, seed, action));
    }
}

int main()
{
    cout << "Exercise 1: " << endl;
    test_rotate_char ();

    cout << "Exercise 3: " << endl;
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

