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

//                                                   
char rotate_char(char a, int r, Action action)
{
//                                                                                                                    
    assert(a<=127);
    assert(a>=0);
    assert(action == Encrypt || action == Decrypt);

//                                                                        

    if (a < 32)
    {
        return a;
    }
    else if (action == Encrypt)
    {
        return (a-32+(r%96)+96)%96+32;
    }
    else if (action == Decrypt)
    {
        return (a-32-(r%96)+96)%96+32;
    }
}

void test_rotate_char()
{
//                     
    assert(true);
//                                                                                                               
//                                                                                                                                

    while (true)
    {
        cout << "input r: ";
        int r;
        cin >> r;

        assert(r > 0); //                      

        for (int i = 0; i < 128; i++)
        {
            char a = (char)i;
            cout << a << " " << (int)a << " " << (int)rotate_char(a, r, Encrypt) << " " << (int)rotate_char(rotate_char(a, r, Encrypt), r, Decrypt) << "\n";
        }
    }
}

//                                                                                        
bool open_input_and_output_file(ifstream& infile, ofstream& outfile)
{
//                
    assert(infile && outfile);
//                                                                           

    string infile_name;
    cout << "Please input the input file name (without the \".txt\"):\n";
    cin >> infile_name;
    infile_name += ".txt";
    string outfile_name;
    cout << "Please input the output file name (without the \".txt\"):\n";
    cin >> outfile_name;
    outfile_name += ".txt";

    assert(infile_name != outfile_name); //                                               

    infile.open(infile_name.c_str(), std::fstream::in);
    outfile.open(outfile_name.c_str(), std::fstream::out);

    if (infile.is_open() && outfile.is_open())
    {
        cout << "Files opened successfully.\n";
        return true; //                                                 
    }
    else
    {
        cout << "Could not open file(s)\n";
        return false; //                       
    }
}

Action get_user_action()
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

int initial_encryption_value()
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

void use_OTP(ifstream& infile, ofstream& outfile, Action action, int initial_value)
{
//                
    assert(infile && outfile);
    assert(action == Encrypt || action == Decrypt);
    assert(initial_value > 0);
    assert(initial_value < 65536);
    initialise_pseudo_random(initial_value);
//                                                                                                                               

    while (infile.peek() != EOF)
    {
    outfile << rotate_char(infile.get(), next_pseudo_random_number(), action);
    }
}

int main()
{
    //                   

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

