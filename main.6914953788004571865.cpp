//                                   
//                                   

#include <iostream>
#include <string>           //                              
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
    assert (a >= 0 && a <= 127);
//                 
//                                  

    char rotated_char;

    if(a < 32){
        rotated_char = a;
    }else{
        if(action == Encrypt){
            rotated_char = (a-32 + (r % (128-32)) + (128-32)) % (128-32)+32;
        }else{
            rotated_char = (a-32 - (r % (128-32)) + (128-32)) % (128-32)+32;
        }
    }
    return rotated_char;
}

void test_rotate_char ()
{
//                
    assert(true);
//                
//                                                
    cout << "Enter a non-negative value for R" << endl;
    int r;
    cin >> r;
    while(r < 0){
        cout << "R must not be negative" << endl;
        cin >> r;
    }
    initialise_pseudo_random(r);
    r = next_pseudo_random_number();
    for(int i=32;i<127;i++){

        cout <<  "Character: " <<(char)i <<  " Ascii code " << i << " Rotated Character: " << rotate_char((char)i,r,Encrypt)  << " Check: " << rotate_char(rotate_char((char)i,r,Encrypt),r,Decrypt) << endl;
        r = next_pseudo_random_number();
    }

}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
//                                                                                    
    assert(!infile.is_open() && !outfile.is_open());
//                 
//                                                                           

    string inp_filename, outp_filename;
    do {
        cout << "Input filename: ";
        cin >> inp_filename;
        cout << "\nOutput filename: ";
        cin >> outp_filename;
        cout << '\n';
    }
    while (inp_filename == outp_filename);

    infile.open(inp_filename.c_str());
    outfile.open(outp_filename.c_str());

    if(infile.is_open() && outfile.is_open()){
        cout << "The files have been opened correctly" << endl;
        return true;
    }
    cout << "The files have not been opened correctly" << endl;
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
    assert(infile.is_open() && outfile.is_open());
//                 
//                                                                                         

    char c;
    initial_value = next_pseudo_random_number();
    infile.get(c);
    while(infile){
        outfile.put(rotate_char(c,initial_value,action));
        initial_value = next_pseudo_random_number();
        infile.get(c);
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
    initialise_pseudo_random(INITIAL_VALUE);
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

