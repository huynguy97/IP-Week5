#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       
#define NDEBUG

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
    cout << "Seed: " << seed << endl;
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
    assert(int(a) > 0 && int(a) < 128);
/*                 
                                                                                                                                      
                                                      
*/
    if(a<32)
        return a;
    else if(action == Encrypt)
        return ((a-32+(r%(128-32))+(128-32))%(128-32)+32);
    return ((a-32-(r%(128-32))+(128-32))%(128-32)+32);
}

void test_rotate_char ()
{
//                
    assert (true);
/*                 
                                                                                                                                              
                                                                  
*/
    int r = 0;
    char a = 't';
    while(r > 0)
    {
        cout << "Please enter a value for r: ";
        cin >> r;
        if(r > 0 && r < 65536)
            cout << a << " " << int(a) << " " << int(rotate_char(a,r,Encrypt)) << " " << int(rotate_char(rotate_char(a,r,Encrypt),r,Decrypt)) << endl;
    }
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert(true);
/*                 
                                                                                                                             
*/
    cout << "Please enter the name of the file you would like to open: \n";
    string input_name;
    cin >> input_name;
    infile.open(input_name.c_str());
    string output_name;
    //                                                                                
    do
    {
        cout << "Please enter the name of the file you would like to write the data into: \n";
        cin >> output_name;
        if(input_name == output_name)
        {
            cout << "The input and output file cannot be the same, give it another try. \n";
            cin.ignore(1000 , '\n');
        }
    }while(input_name == output_name);
    outfile.open(output_name.c_str());
    if(infile && outfile)
    {
        cout << "The files have been successfully opened.\n";
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
    assert (true);
/*                 
                                                          
*/
    int initial_value = -1 ;
    while (initial_value < 0 || initial_value > 65535)
    {
        cout << "Please enter the initial coding value (greater or equal to 0 and less than 65536)" << endl ;
        //                                                                                                                                                
                                //                                                                                                 
        cin  >> initial_value ;
    }
    return initial_value ;
}

void use_OTP (ifstream& infile, ofstream& outfile, Action action, int initial_value)
{
//                
    assert(infile.is_open());
    assert(outfile.is_open());
    assert(initial_value > 0 && initial_value < 65536);
/*                 
                                                                           
                                                                          
*/
    char a,b;
    initialise_pseudo_random(initial_value);
    int r = seed;
    infile.get(a);
    while(infile)
    {
        r = next_pseudo_random_number();
        //                             
        b = rotate_char(a, r, action);
        outfile.put(b);
        infile.get(a);
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

