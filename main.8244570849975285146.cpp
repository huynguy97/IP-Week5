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
    assert (r >= 0 && r <= 65536 && (int)'a' >= 32);
/*                 
                                     
*/
    if (action == Encrypt)
    {
        int b = (int(a)-32+(r%(128-32))+(128-32))%(128-32)+32;
        return b;
    }
    else if (action == Decrypt)
    {
        int b = (int(a)-32-(r%(128-32))+(128-32))%(128-32)+32;
        return b;
    }
}

void test_rotate_char ()
{
//                
    assert (true);
/*                 
                                                                                               
                               
*/
    int r;
    do
    {
        cout << "Enter a nonnegative integer for r: ";
        cin >> r;
        char a = 'S';
        cout << endl << a << int(a) << int (rotate_char(a, r, Encrypt))
        << int (rotate_char(rotate_char(a, r, Encrypt), r, Decrypt)) << endl;
        //              
    }
    while (r > 0);
}

int count_and_show (ifstream& infile, ofstream& outfile, int r, Action action)
{
//              
    assert (infile.is_open()) ;
  /*                                                                                                */
    int no_of_chars = 0 ;
    char c ;
    infile.get (c) ;
    while (infile)
    {
        //                          
        outfile.put(rotate_char(c, r, action));
        no_of_chars++ ;
        infile.get (c) ;
        r = next_pseudo_random_number();
    }
    return no_of_chars ;
 }

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert (true);
/*                 
                                                                                                                                           
*/
    cout << "Please enter an input file name (without spaces): ";
    string input_filename, output_filename;
    cin >> input_filename;
    cout << endl << "Please enter an output file name (without spaces): ";
    cin >> output_filename;
    if (input_filename != output_filename)
    {
        infile.open(input_filename.c_str());
        outfile.open(output_filename.c_str());
        if (infile.is_open() && outfile.is_open())
        {
            cout << "The files have been opened successfully.";
            return true;
        }
        else
        {
            cout << "The program failed to open the files successfully.";
            return false;
        }
    }
    else
    {
        cout << endl
        << "Error: The program cannot read and write to the same file at the same time.";
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
    assert (true) ;
/*                 
                                                                                                                    
*/
    initialise_pseudo_random(initial_value);
    int next = next_pseudo_random_number();
    count_and_show(infile, outfile, next, action);

}

int main()
{
    const Action ACTION = get_user_action() ;
    ifstream infile  ;
    ofstream outfile ;
    if (!open_input_and_output_file (infile,outfile))
    {
        cout << "Program aborted." << endl ;
        return -1 ;
    }
    const int INITIAL_VALUE = initial_encryption_value () ;
    use_OTP (infile,outfile,ACTION,INITIAL_VALUE);
    infile.clear () ;
    outfile.clear () ;
    infile.close () ;
    outfile.close () ;

    if (!infile || !outfile)
    {
        cout << "Not all files were closed succesfully. The output might be incorrect." << endl ;
        return -1 ;
    }
    return 0 ;
}

