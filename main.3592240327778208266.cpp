#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       

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
    assert(r >= 0);
/*                 
                                                                                                                    
*/
    char b;
    if((int)a < 32){
        b = a;
    }else if(action == Encrypt){
        b = (char)(((int)a - 32 + (r % 96)  + 96) % 96 + 32);
    }else{
        b = (char)(((int)a - 32 - (r % 96)  + 96) % 96 + 32);
    }
    return b;
}

void test_rotate_char ()
{
//                
    assert(true);
/*                 
                                                                                                                                      
                                                                                               

*/
    int r = 0;
    char a;
    cout << "For what value of r do you want to test?" << endl;
    cin >> r;
    for(int i = 1; i <= 128; i++){
        a = (char)i;
        cout << a << " , " << i << " , " << (int)rotate_char(a, r, Encrypt) << " , " << (int)rotate_char(rotate_char(a, r, Encrypt), r, Decrypt) << endl;
    }
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert(true);
/*                 
                                                                                                         
*/
    string infile_name;
    string outfile_name;
    cout << "what will be the filename for the input and the filename for the output?" << endl;
    cin >> infile_name >> outfile_name;
    if(infile_name == outfile_name){
        cout << "Error, input filename and output filename are the same" << endl;
        return false;
    }else{
        infile.open(infile_name.c_str());
        outfile.open(outfile_name.c_str());
        if(infile.is_open() && outfile.is_open()){
            cout << "All is well" << endl;
            return true;
        }else{
            cout << "Something went wrong with file opening" << endl;
            return false;
        }

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
    assert(action == Encrypt || action == Decrypt);
/*                 
                                                                                                                  
*/
    char c;
    initialise_pseudo_random(initial_value);
    while(infile){
        infile.get(c);
        outfile.put(rotate_char(c, next_pseudo_random_number(), action));

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

