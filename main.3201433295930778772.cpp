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

char rotate_char (char a, int r, Action action) {
//                
    assert(r > 0);
//                 
//                                                                         
    char b;

    if (action == Encrypt) {
        if (a < 32) {
            return a;
        } else {
            b = (a - 32 + (r % (128 - 32))) % (128 - 32) + 32;
            return b;
        }
    } else {
        if (a < 32) {
            return a;
        } else {
            b = (a - 32 - (r % (128 - 32)) + (128 - 32)) % (128 - 32) + 32;
            return b;
        }
    }
}

void test_rotate_char ()
{
//                
assert(true);
//                 
//                                                            
int r=0;
char a;
cout << "Please enter a non-negative value for r:"<<endl;
    cin >> r;

    initialise_pseudo_random(r);
    for(int i=0; i<128; i++){
        int c=next_pseudo_random_number();
        a = static_cast<char>(i);
        cout << a << "\t" << static_cast<int>(a) << "\t" << static_cast<int>(rotate_char(a, c, Encrypt))
        << "\t" << static_cast<int>(rotate_char (rotate_char (a, c, Encrypt), c, Decrypt))<<endl;
    }
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert(true);
//                 
//                                                                            
    string infilename;
    string outfilename;
    cout << "Please enter the input filename:"<<endl;
    cin >> infilename;
    cout << "Please enter the output filename:"<<endl;
    cin >> outfilename;
    infilename = infilename + (".txt");
    outfilename = outfilename + (".txt");
    if(infilename != outfilename){
        infile.open(infilename.c_str());
        outfile.open(outfilename.c_str());
    }
    else
    {
        cout << "The filenames are the same!";
    }
    if(infile.is_open() && outfile.is_open()){

        return true;
    }
    else
    {

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
assert(initial_value >= 0 && initial_value  < 128);
//                 
//                                                                                                                                        
char in_c;
char out_c;
initialise_pseudo_random(initial_value);

while(!infile.eof()){
    int t=next_pseudo_random_number();
    in_c = infile.get();
    if(action==Encrypt){
        out_c = rotate_char(in_c, t, Encrypt);
        outfile << out_c;
    }
    else
    {
        out_c = rotate_char(in_c, t, Decrypt);
        outfile << out_c;
    }
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

