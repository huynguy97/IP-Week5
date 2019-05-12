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
    assert ( r >= 0 && a>=0 && a<128 && (action == Encrypt || action == Decrypt));
//                 
//                                                                                                      
    if (a<32)//                                                           
        return a;

    if (action == Encrypt)
        return (a-32+(r%(128-32)) + (128-32))%(128-32)+32;//                         
    return (a-32-(r%(128-32)) + (128-32))%(128-32)+32;//                         
}

void test_rotate_char ()
{
//                
    assert (true);
/*                 
                                                                                                                
                                                                                                                                      
*/
    int r;
    cout << "Please enter an integer. If the integer is negative this function will terminate. (This is just for the test_rotate_char)";
    cin >> r;
    while (!cin)//                                                                
    {

        cin.clear();
        cin.ignore(1000, '\n');
        cout << "That's not an integer. Try again. ";
        cin >> r;
    }
    cin.ignore(1000, '\n');
    if (r<0)
        return;
    for(int i = 0; i<128; i++)//                                                            
    {
        char a = static_cast<char>(i);
        cout << a << ", " << i << ", " << rotate_char(a,r,Encrypt) << ", " << rotate_char(rotate_char(a,r,Encrypt),r,Decrypt) << endl;
    }

}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert ( true );
/*                 
                                                                          
                                                               
                                                                                             
*/
    string input_name;
    string output_name;

    cout << "Please enter the name of the input file. ";
    cin >> input_name;
    cin.ignore(1000, '\n');

    cout << "Please enter the name of the output file. ";
    cin >> output_name;
    cin.ignore(1000, '\n');
    cin.clear();

    if (input_name == output_name )
    {
        cout << "The file names are the same!" << endl;
        return false;
    }
    infile.open( input_name.c_str() );
    outfile.open( output_name.c_str() );
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
    assert( infile.is_open() && outfile.is_open() && initial_value > 0 && initial_value <= 65536 && (action == Encrypt || action == Decrypt));

//                 
//                                                              
    initialise_pseudo_random(initial_value);

    char c;
    while (infile)//                                                                                                                                              
    {
        infile.get( c );
        outfile.put( rotate_char(c, next_pseudo_random_number(), action) );
    }
}

int main()
{
    test_rotate_char();

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

