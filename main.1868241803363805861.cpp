#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       

/*
                         
                    
*/

using namespace std;

enum Action {Encrypt, Decrypt} ;

//                                                     
int seed = 0 ;
void initialise_pseudo_random (int r)
{
//                
    assert (r > 0 && r <= 65536) ;
/*                 
                     
*/
    seed = r ;
}

//                               
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
char rotate_char (char a, int r, Action action)
{
//                
    assert (r > 0 && r <= 65536 && (action == Encrypt || action == Decrypt)) ;
/*                 
                              
*/
    int sub = 0;
    if(a < 32) {
        return a;
    }else {
        if(action == Encrypt) {
            sub = 1;
        }else {
            sub = -1;
        }
        return (a - 32 + sub*(r % (128 - 32)) + (128 - 32)) % (128-32) + 32;
    }
}

//                                                            
void test_rotate_char ()
{
//                
    assert (true);
/*                 
                                    
*/
    int r = 0;
    char a;
    do {
        cout << "Please give a random number between 0 and 65537: " << endl;
        cin >> r;
        a = 'a';
        cout << "The starting character is " << a << endl;
        cout << "The encrypted version is " << rotate_char(a, r, Encrypt) << endl;
        cout << "The encrypted and decrypted version is " << rotate_char(rotate_char(a, r, Encrypt), r, Decrypt) << endl;
        cout << "\n\n";
    } while(r > 0 && r <= 65536);
}

//                                                                
bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert(true);
/*                 
                                              
*/
    string infilename;
    string outfilename;
    cout << "Give the name of the input file: " << endl;
    cin >> infilename;
    cout << "Give the name of the output file: " << endl;
    cin >> outfilename;
    if(infilename == outfilename) {
        return false;
    } else {
        infile.open(infilename.c_str());
        outfile.open(outfilename.c_str());
        if(infile.is_open() && outfile.is_open()) {
            cout << "Files successfully opened" << endl;
            return true;
        } else {
            cout << "Could not open files" << endl;
            return false;
        }
    }
}

//                                
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

//                                    
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

//                                                             
void use_OTP (ifstream& infile, ofstream& outfile, Action action, int initial_value)
{
//                
    assert(infile.is_open() && outfile.is_open() && initial_value > 0 && initial_value <= 65536);
/*                 
                                                                                             
*/
    char c;
    infile.get(c);
    while(infile) {
        outfile.put(rotate_char(c, next_pseudo_random_number(), action));
        infile.get(c);
    }
}

//                                  
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

