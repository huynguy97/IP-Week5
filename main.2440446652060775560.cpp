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
    assert(r > 0 && r <= 65536);
//                                                         
    if(a < 32)
    {
        return a;
    }
    else
    {
        if(action == Encrypt)
        {
            return (a -32 + (r % (128-32)) + (128 -32)) % (128-32)+32;
        }
        else
        {
            return (a -32 - (r % (128-32)) + (128 -32)) % (128-32)+32;
        }
    }
}

void test_rotate_char ()
{
    int r =  - 1;
    while(true)
    {
    //                
        cout << "Please give a value  0 < r < 65536" << endl;
        cin >> r;
        assert(r > 0 && r <= 65536);
    //                                                                        
        for(int i = 0;i < 128; i++)
        {
            cout << char(i) << '\t';
            cout << i << '\t';
            cout << int(rotate_char(char(i),r,Encrypt)) << '\t';
            cout << int(rotate_char(rotate_char(char(i),r,Encrypt),r,Decrypt)) << endl;
        }
    }
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert(!infile.is_open() && !outfile.is_open());
//                                                                          

    string input_filename;
    string output_filename;

    cout << "Please enter a filename for input" << endl;
    cin >> input_filename;
    cout << "Please enter a filename for output" << endl;
    cin >> output_filename;

    assert(input_filename != output_filename);

    infile.open(input_filename.c_str());
    outfile.open(output_filename.c_str());
    if(infile.is_open() && outfile.is_open())
    {
        return true;
    }
    return false;
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
    assert(infile.is_open() && outfile.is_open() && initial_value > 0 && initial_value < 65535);
    //                 
    //                                                                

    initialise_pseudo_random(initial_value);
    char c;
    infile.get(c);
    while(infile)
    {
        next_pseudo_random_number();
        c = rotate_char(c,seed,action);
        outfile.put(c);
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

