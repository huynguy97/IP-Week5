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

//                                                
int input()
{
//              
    assert( true );
//                                                                        
    int r;
    cout << "pick a number between 0 and 65536: ";
    cin >> r;

    while(r<=0)
    {
        cout << "please pick a positive number: ";
        cin >> r;
    }

    return r;
}

//                                                                   
char rotate_char (char a, int r, Action action)
{
//                
    assert (r > 0);
//                                                            
    int b;

    if(a < 32)
    {
        b = a;
    }

    else
    {
        if(action == 0)
        {
            b = (a-32 + (r % (128-32))) % (128-32)+32;
        }
        else
        {
            b = (a-32 - (r % (128-32)) + (128-32)) % (128-32)+32;
        }
    }
    return b;
}

//                                                                                           
void test_rotate_char ()
{
//                
    assert( true );
//                                                                                  

    int r = input();
    int a = 0;

    while(a < 128)
    {
        int enc = rotate_char(a, r, Encrypt);
        int dec = rotate_char(enc, r, Decrypt);

        cout << char(a) << "    " << a << "    " << enc << "    " << dec << "\n";
        a++;
    }
}

//                                                                                              
bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert(true);
/*                 
                                                                                               
*/
    string inputfile;
    string outputfile;
    cout << "Give an filename for input: ";
    cin >> inputfile;
    cout << "Give an filename for output: ";
    cin >> outputfile;

    if(inputfile == outputfile)
    {
        cout << "error: The given filenames are the same!\n";
    }

    bool inopen;
    bool outopen;

    infile.open (inputfile);
    if(infile)
    {
        inopen = true;
    }
    else
    {
        inopen = false;
    }

    outfile.open (outputfile);
     if(outfile)
    {
        outopen =true;
    }
    else
    {
        outopen = false;
    }

    if(inopen && outopen)
    {
        cout << "Files opened succesfully!\n";
        return true;
    }
    else
    {
        cout << "Files couldn't be opened!\n";
        return false;
    }
}

Action get_user_action ()
{
    //               
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

//                                                                                                                               
void use_OTP (ifstream& infile, ofstream& outfile, Action action, int initial_value)
{
//                
    assert(initial_value > 0);
//                                                                                   
    int r = initial_value;
    char c;
    infile.get(c);
    initialise_pseudo_random(r);
    r = next_pseudo_random_number();
    while(infile)
    {
        outfile.put(rotate_char(c, r, action));
        r = next_pseudo_random_number();
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
    return 0 ;
}

