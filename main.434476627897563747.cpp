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
    assert(r > 0 && r <= 65536);
//                                                                                     
    char b;

    if(a<32) b=a;
    else
    {
        if (action == Encrypt) b=(((a-32)+(r%96))%96)+32;
        else b=(((a-32)-(r%96)+96)%96)+32;
    }

    return b;
}

void test_rotate_char ()
{
//                
    assert(true);
//                                                                            
//                                                                            
//                                                                   

    int r;
    cout << "Enter a number for r: " << endl;
    cin >> r;

    while(!(r>0))
    {
        cout << "Enter a valid number for r: " << endl;
        cin >> r;
    }

    char a=0;
    for(int i=0; i<128; i++)
    {
        a=i;
        char encr_a = rotate_char(a, r, Encrypt);
        char decr_a = rotate_char(encr_a, r, Decrypt);
        cout << a << " " << i << " " << encr_a << " " << decr_a << endl;
    }

}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert(true);
//                                                                                       

    cout << "Enter a input filename: " << endl;
    string inputfilename;
    cin >> inputfilename;

    cout << "Enter a output filename: " << endl;
    string outputfilename;
    cin >> outputfilename;

    if (inputfilename==outputfilename)
    {
        cout << "Same input and output filename" << endl;
        return false;
    }
     infile.open(inputfilename.c_str());
    outfile.open(outputfilename.c_str());

    cout << infile.is_open()<< " and "<< outfile.is_open()<< endl;

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
//                
    assert(infile.is_open()&& outfile.is_open()&& initial_value > 0);
//                                                                                               

    int no_of_chars = 0;
    initialise_pseudo_random(initial_value);
    char c;
    infile.get(c);
    while (infile)
    {
        outfile.put(rotate_char(c, next_pseudo_random_number(), action));
        no_of_chars++;
        infile.get(c);
    }

    cout << no_of_chars << endl;
    return;
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

