#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       

using namespace std;

//                                          
//                                              
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
assert(action==0||action==1||r > 0 && r <= 65536);
        if(int(a)<32)
        {
            return a;
        }
    else
    {
        switch(action){
    case Encrypt:
        return ((int(a)-32+( r %(128-32)))%(128-32)+32);
    case Decrypt:
        return ((int(a)-32-( r %(128-32))+(128-32))%(128-32)+32);
        }

    }
//                 
//                                                             
}

void test_rotate_char ()
{
//               
assert(true);
    cout << "enter character: " << endl;
    char a;
    int r;
    cin>> a;
    cout << "enter number to shift by: " << endl;
    cin >> r;
    cin>> a;
    cout<< "Entered letter " << a << endl;
    cout << "ASCII value " << int(a) << endl;
    cout << "Encrypted Character " << rotate_char(a,r,Encrypt) << endl;
    cout<< "Decrypted Character " << rotate_char(rotate_char(a,r,Encrypt),r,Decrypt) << endl;

//                 
   //                                                                               
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert(true);
    string infilename, outfilename;
    cin >> infilename >> outfilename;
    infile.open(infilename.c_str());
    outfile.open(outfilename.c_str());
        if(infilename == outfilename)
        {
            return false;
        }
        else
        {
            if(infile && outfile)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
//                 
    //                                                                                                  
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
assert(infile&&outfile);
    char a;
    infile.get(a);
    while(infile)
    {
        outfile.put(rotate_char(a,next_pseudo_random_number(),action));
        infile.get(a);

    }
//                 
//                                                              
}

int main()
{
    const Action ACTION = get_user_action() ;
    ifstream input_file;
    ofstream output_file;
    //                    
    if (!open_input_and_output_file (input_file,output_file))
    {
        cout << "Program aborted." << endl ;
        return -1 ;
    }
    const int INITIAL_VALUE = initial_encryption_value ();
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

