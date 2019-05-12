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
    assert (true);
//                 
//                                                                
    int b ;
    int ia = a ;
    if (ia < 32)
    {
        b=a;
    }
    if (ia >= 32 && action == Encrypt)
    {
        b=(ia-32+(r%(128-32))+(128-32))%(128-32)+32;
    }
    if (ia >= 32 && action == Decrypt)
    {
        b=(ia-32-(r%(128-32))+(128-32))%(128-32)+32;
    }

}

void test_rotate_char ()
{
//                
    assert(true);
//                 
//                                                                                                                         
    int r;
    while(true)
    {
        cout << "input value r";
        cin  >> r;

        for (int i = 32; i < 126; i++)
        {
            cout << char(i) << ' ' << rotate_char(char(i), r, Encrypt) << ' ' << rotate_char(rotate_char(char(i), r, Encrypt), r, Decrypt) << endl;
        }
    }
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert(true);
//                 
//                                                                                                                                            
    string i;
    cout << "name input file to open " << endl ;
    cin >> i ;
    string o;
    cout << "name output file to open " << endl ;
    cin >> o;
    if (i != o)
    {
        infile.open(i.c_str()) ;
        outfile.open (o.c_str()) ;
        if (infile.is_open())
        {
            cout << "input opened succesfully " <<endl ;
            if (outfile.is_open())
            {
                cout << "output opened succesfully " << endl ;
                return true ;
            }
        }

    }
    cout << "names should be different ";
    return false ;
}

Action get_user_action ()
{
    //               
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
{
    //              
    assert (true) ;
    /*                 
                                                              
    */
    int initial_value = -1 ;
    while (initial_value < 0 || initial_value > 65535)
    {
        ifstream  input_file ("test.txt");

        cout << "Please enter the initial coding value (greater or equal to 0 and less than 65536)" << endl ;
        cin  >> initial_value ;
    }
    return initial_value ;
}

void use_OTP (ifstream& infile, ofstream& outfile, Action action, int initial_value)
{
//                
    assert(true) ;
//                 
//                                                                                             
    int r;
    initialise_pseudo_random(initial_value);
    char a ;
    infile.get (a) ;

    while (infile)
    {

        outfile.put (rotate_char(char(a), next_pseudo_random_number(), action)) ;
        infile.get (a) ;

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

