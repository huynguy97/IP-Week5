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

    char b;
     if(a<32)
    {
        return a;
    }
    if(action == Encrypt)
    {
       b = (a-32 + (r% (128-32)))%(128-32)+32;
       return b;
    }

    if(action == Decrypt)
    {
     b = (a-32 - (r% (128-32))+ (128-32))%(128-32)+32;
     cout << b << endl;
     return b;
    }

}

void test_rotate_char ()
{
 int r;
 char a;
 cout << "geef  a en r"<<endl;
 cin >> a;
 cin >> r;
 string code = "(a-32 +/- (r% (128-32))+ (128-32))%(128-32)+32";

 if(r < 0)
 {
     cout << "invalid r";
 }
 if(r >= 0 )
    {
     cout << a << " " << code << " "<< rotate_char(a, r, Encrypt)<< " " << rotate_char((rotate_char(a,r,Encrypt)),r,Decrypt);
    }
//                 

}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
    string filename_input;
    string filename_output;
    cout << "Enter a file name for input" << endl;
    cin  >> filename_input;
    cout << "Enter a file name for output" << endl;
    cin  >> filename_output ;
    infile.open(filename_input.c_str());
    outfile.open(filename_output.c_str());
    if (filename_input == filename_output)
        return false;
    return infile.is_open() && outfile.is_open();
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
    initialise_pseudo_random(initial_value);
   char a;
   while(infile.get(a)) {
       outfile.put(rotate_char(a,next_pseudo_random_number(),action));
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

