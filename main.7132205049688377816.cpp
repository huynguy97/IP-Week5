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
    assert(a >= 0 & a < 128) ;
    char b ;
    if (a < 32)
    {
        b = a;
        return b ;
    }
    else if (static_cast<Action>(action) == Encrypt)
    {
        b = (a-32 + (r%(128-32)))%(128-32)+32 ;
        return b ;
    }
    else
    {
        b = (a-32 - (r%(128-32))+(128-32))%(128-32)+32 ;
        return b ;
    }
//                 
/*
                                                                   
*/

}

void test_rotate_char ()
{
//                
    assert(true) ;
    int r = 0;
    while(r >= 0)
    {
        char a;
        cout << "Please enter a value between 0 and 65535." << endl ;
        cin >> r ;
        cout << "Please enter a character." << endl;
        cin >> a ;

        char b = rotate_char ( a, r, Encrypt) ;
        char c = rotate_char (b, r, Decrypt) ;
        int asca = a ;
        int ascb = b ;
        int ascc = c ;
        cout << a << "-" << asca << "-" << ascb << "-" << ascc<< endl ;

    }

//                 
/*
                                                                                                                                        
*/
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert(true);
    string filenamein ;
    string filenameout ;
    cout << "Please enter two file names." << endl ;
    cin >> filenamein ;
    cin >> filenameout ;

    if(filenamein != filenameout)
    {

        infile.open(filenamein) ;
        if(infile)
        {
            outfile.open(filenameout) ;
            if(outfile)
            {
                return true ;
            }
            else
            {
                cout << "Error: second file didn't open succesfully" << endl;
                return false ;
            }
        }
        else
        {
            cout << "Error: first file didn't open succesfully" << endl;
            return false ;
        }
    }
    else
    {
        cout << "Error: The file names are the same." << endl ;
        return false ;
    }
//                 
/*
                                                 
*/
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
    assert(true) ;
    char a;
    initialise_pseudo_random(initial_value) ;

    while(infile.get(a))
    {
        int next = next_pseudo_random_number() ;
        outfile<<rotate_char(a, next, action);
    }

//                 
/*
                                                
*/
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

