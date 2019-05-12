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
    seed = r;
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
//                                                                                                                                              
char rotate_char (char a, int r, Action action)
{
//                
    assert(true);
/*                 
                             
*/
    int b = a;

    if(a >= 32)
    {
        if(action == Encrypt)
            b = (a-32+(r%(128-32)))%(128-32)+32;
        else
            b = (a-32-(r%(128-32))+(128-32))%(128-32)+32;
    }
    return b;

}

//                                                                                                                                    
void test_rotate_char ()
{
//                
    assert(true);
/*                 
                       
*/
    char a = 'q';
    int r;
    while(true)
    {
        cout << "Give r: ";
        cin >> r;
        initialise_pseudo_random (r);

        cout << a << "\t" << a+0 << "\t" << rotate_char(a,r,Encrypt)+0 << "\t" << rotate_char(rotate_char(a,r,Encrypt),r,Decrypt)+0 << "\n";
    }

}

//                                                                                                                                                                         
bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert(true);
/*                 
                           
*/
    cout << "Please, enter a file name to insert: ";
    string filename_in;
    string filename_out;

    cin >> filename_in;
    infile.open(filename_in.c_str());

    cout << "\nPlease, enter an output file: ";
    cin >> filename_out;
    outfile.open(filename_out.c_str());

    if(filename_in == filename_out)
    {
        cout <<"\t \t \t \tError with code: 666 \n \t \t \t \tFiles have the same name\n \t \t \t \tYou nitwit" << endl << endl;
    }

    if(infile.is_open() && outfile.is_open())
    {
        cout << "Files have been opened successfully\n";
        return true;
    }
    else
    {
        cout << "Opening files has failed\n";
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

//                                                                                                                     
void use_OTP (ifstream& infile, ofstream& outfile, Action action, int initial_value)
{
//                
    assert(infile.is_open() && outfile.is_open());
/*                 
                                     
*/
    int r;
    initialise_pseudo_random(initial_value);
    char character;

    while(infile)
    {
    r = next_pseudo_random_number();
    infile.get(character);
    outfile.put(rotate_char (character, r, action));
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
        cout << "Not all files were closed successfully. The output might be incorrect." << endl ;
        return -1 ;
    }
    return 0 ;
}

