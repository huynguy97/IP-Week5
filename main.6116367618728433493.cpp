#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       

/* 
                             
                        
*/

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
    assert(true);
/*                 
                          
                            */
    if(a < 32)
        return a;
    if(action == Encrypt)
        return (a + r % 96 + 64) % 96 + 32;
    return (a - r % 96 + 64) % 96 + 32;
}

void test_rotate_char ()
{
//                
    assert(true);
/*                 
                                                                                      */

    cout << "Enter test key. to stop, enter a negative value\n";
    int r;
    cin >> r;
    while(r >= 0)
    {
        for(int i = 32; i < 128; i++)
        {
            cout << (char)i << '\t' << i << '\t' << rotate_char(i, r, Encrypt) << '\t' << rotate_char(rotate_char(i, r, Encrypt), r, Decrypt) << '\n';
        }
        cin >> r;
    }

}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert(true);
/*                 
                                                                                 
                                                       
                                         */

    string i_name;
    string o_name;
    cout << "Enter input filename and output filename\n";
    cin >> i_name;
    cin >> o_name;
    if(i_name == o_name)
    {
        cout << "File not opened: Cannot read from and write to the same file\n";
        return false;
    }
    infile.open(i_name.c_str());
    if(!infile.is_open())
    {
        cout << "Could not open infile\n";
        return false;
    }
    outfile.open(o_name.c_str());
    if(!outfile.is_open())
    {
        cout << "Could not open outfile\n";
        return false;
    }
    return true;
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

    cout << infile;

    initialise_pseudo_random(initial_value);

    char c;
    while(infile)
    {
        infile.get(c);
        cout << c;
        c = rotate_char(c, next_pseudo_random_number(), action);
        outfile.put(c);
    }
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

