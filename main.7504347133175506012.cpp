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
    assert (r >= 0) ;
//                 
//                                                                                                       
    char b;
    if (a < 32)
        b = a ;
    else
    {
        switch (action)
        {
            case Encrypt: b = ((a-32 + (r % (128-32))) % (128-32)+32) ; break ;
            case Decrypt: b = ((a-32 - (r % (128-32)) + (128-32)) % (128-32)+32) ; break ;
        }
    }
    return static_cast<char>(b);
}

void test_rotate_char ()
{
//                
    assert (true);
//                 
//                                                    
//                                                                                                      
//                                                                                            
//                        
    int r;
    char a;
    while (r>=0)
    {
        cout << "Please enter a value for r between 0 an(initial_value < 0 || initial_value > 65535)d 65536" << endl;
        cin >> r ;
        cout << "Please enter a value for a" << endl;
        cin >> a ;
        cout << a << " " <<  static_cast<int>(a) << " " << rotate_char (a, r, Encrypt) << " " <<  rotate_char (rotate_char (a, r, Encrypt), r, Decrypt) << endl;
    }

}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert (true);
//                 
//                                                                                                                                                                                                                                                
    string name_infile;
    string name_outfile;
    cout << "Please enter a name for the input file" << endl;
    cin >> name_infile ;
    cout << "Please enter a name for the output file (must be different then the input file)" << endl;
    cin >> name_outfile ;
    if (name_infile == name_outfile)
        cout << "Error, the input and output file names are the same." << endl;
    infile.open(name_infile.c_str());
    outfile.open(name_outfile.c_str());
    if (infile.is_open() && outfile.is_open())
    {
        cout << "Both files are opened successfully." << endl;
        return true;
    }
    else
    {
        cout << "There was a problem with opening both files." << endl;
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
    assert (infile.is_open() && outfile.is_open());
//                 
//                                                                                                                                                 
    char a ;
    initialise_pseudo_random(initial_value);
    while (infile)
        {
        infile.get(a) ;
        outfile.put(rotate_char(a, next_pseudo_random_number(), action));
        }
    return ;
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

