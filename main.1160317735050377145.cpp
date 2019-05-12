#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       
#include <string>
/*                                                                                                                                                                             */
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
    assert(static_cast<int>(a) < 128 && (r > 0 && r <= 65536) && (action == Encrypt || action == Decrypt));
    //                                                                                                                   

    int aCode = static_cast<int>(a);
    char b;

    if (aCode < 32){
        b = a;
    } else {
        if (action == Encrypt){
            b = static_cast<char>((aCode-32 + (r % (128-32)) + (128-32)) % (128-32)+32);
        } else { //       
            b = static_cast<char>((aCode-32 - (r % (128-32)) + (128-32)) % (128-32)+32);
        }
    }

    return b;
}

void test_rotate_char ()
{
    //                
    assert(true);
    //                                                                                                                   
    //                                                   

    bool go = true;
    while (go){
        cout << "Enter a value for r. (A negative r will terminate the program)" << endl;
        int r;
        cin >> r;
        if (r < 1 || r > 65536){
            go = false;
        } else {
            for (int a = 32; a < 127; a++){
                cout << static_cast<char>(a) << " " << a << " " << static_cast<int>(rotate_char(static_cast<char>(a),r,Encrypt)) << " " << static_cast<int>(rotate_char(rotate_char(static_cast<char>(a),r,Encrypt),r,Decrypt)) << endl;
            }
        }
    }

}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
    //                
    assert(true);
    //                                                                                                        
    //                                                                                                
    //                                                               

    cout << "Enter input file name: " << endl;
    string inFileName;
    cin >> inFileName;
    cout << "Enter output file name: " << endl;
    string outFileName;
    cin >> outFileName;
    if (outFileName == inFileName){
        cout << "Names are the same, please enter different filenames" << endl;
        return false;
    }

    infile.open(inFileName.c_str());
    if (!infile.is_open()){
        cout << "Could not open input file" << endl;
        return false;
    }

    outfile.open(outFileName.c_str());
    if (!outfile.is_open()){
        cout << "Could not open output file" << endl;
        return false;
    }

    cout << "Files are opened succesfully" << endl;
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
    while (initial_value < 1 || initial_value > 65535)
    {
        cout << "Please enter the initial coding value (greater or equal to 1 and less than 65536)" << endl ;
        cin  >> initial_value ;
    }
    return initial_value ;
}

void use_OTP (ifstream& infile, ofstream& outfile, Action action, int initial_value)
{
//                
    assert (infile.is_open() && outfile.is_open() && (action == Encrypt || action == Decrypt) && initial_value > 0 && initial_value <= 65535);

//                 
    //                                                        
    char c;
    infile.get (c);
    initialise_pseudo_random (initial_value);
    while (infile) //                                                                                                                
    {
        int r = next_pseudo_random_number();
        char result = rotate_char(c, r, action);
        outfile.put (result);
        infile.get (c);
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

