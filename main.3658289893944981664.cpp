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
    assert(a < 128);
    /*                 
                                                              
    */

    if(action == Encrypt)
    {
        if(a < 32)
            return a;
        else
            return ((a-32 + (r % (128-32)) + (128-32)) % (128-32)+32);
    }
    else
    {
        if (a < 32)
            return a;
        else
            return ((a-32 - (r % (128-32)) + (128-32)) % (128-32)+32);
    }
}

void test_rotate_char ()
{
//                
    assert(true);
    /*                 
                                                                 
    */

    int r = 0;
    while(r >= 0)
    {
        cout << "enter a value for r\n" << endl;
        cin >> r ;
        for(int a = 0; a < 128; a++)
        {
            char ca = a;
            cout << ca << " - " << a << " - " << rotate_char(a, r, Encrypt) << " - " << rotate_char((rotate_char(a, r, Encrypt)), r, Decrypt) << endl;
        }
    }
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert(infile != outfile);
    /*                 
                                                                            
                                               
    */
    string input, output;
    do
    {
        cout << "enter the filename of the input file" << endl;
        cin >> input;
        cout << "enter the filename of the output file" << endl;
        cin >> output;
        if(input == output)
            cout << "Error, the input file can't be the same as the output file.";
    }
    while(input == output);
    infile.open(input.c_str());
    outfile.open(output.c_str());
    return infile && outfile;

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

void use_OTP (ifstream& infile, ofstream& outfile, Action action, int initial_value)
{
//                
    assert(true);
    /*                 
                                                                                                           
    */
    initialise_pseudo_random(initial_value);
    char c;
    while(infile.get(c))
    {
        c = rotate_char(c, next_pseudo_random_number(), action);
        outfile << c;
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

