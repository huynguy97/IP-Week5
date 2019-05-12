#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       

using namespace std;

//                             

/*
                                                                                            
                                                                                                                                                                                               
                                                                                                                                         
                                                                                     

                            
                     
*/

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

char rotate_char (char a, int r, Action e)
{
//                       
    assert(r >= 0);
//                                                                                                                          

    char b;
    if (a < 32)
        b = a;
    else if (e == Encrypt)
        b = (a - 32 + (r % (128-32))) % (128-32) + 32;
    else
        b = (a - 32 - (r % (128-32)) + (128-32)) % (128-32) + 32;

    return b;
}

void test_rotate_char ()
{
//                
    assert(rotate_char('a', 1, Encrypt) == 'b');
//                                                                                                                               

    int r = 0;
    while (r >= 0)
    {
        cout << "\nRotation-value r: ";
        cin >> r;

        if (r >= 0)
        {
            cout << "\na\t a (ASCII)\t b\t b (ASCII)\t decrypted b (ASCII)" << endl;            //                                                              
            cout << "__________________________________________________________" << endl;       //                                                                                   

            for (int a = 32; a < 127; a++)
            {
                char ch = a, b = rotate_char(a, r, Encrypt);
                int encryptedch = rotate_char(a, r, Encrypt),
                    decryptedch = rotate_char(rotate_char(a, r, Encrypt), r, Decrypt);

                cout << ch << "\t" << a << "\t\t" << b << "\t" << encryptedch << "\t\t" << decryptedch << "\t |" << endl;
            }

            cout << "_________________________________________________________|" << endl;
        }
    }
    cout << endl;
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert(infile && outfile);
//                                                                                                                                      

    string infilename, outfilename;
    cout << "Filename of file to open for input (example.txt): ";
    cin >> infilename;
    cout << "Filename of file to open or create for output: ";
    cin >> outfilename;

    if (infilename == outfilename){
        cout << "Input- and output-filename cannot be the same." << endl;
        return false;
    }

    infile.open(infilename.c_str());
    outfile.open(outfilename.c_str());

    if ((infile) && (outfile)){
        cout << "Files successfully opened." << endl;
        return true;
    }
    else{
        cout << "Failed to open one or more files." << endl;
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
    assert(infile.is_open() && outfile.is_open());
//                                                                                                                                                 
//                                                                     

    initialise_pseudo_random(initial_value);

    char a, b;
    infile.get(a);

    while (infile)
    {
        b = rotate_char(a, next_pseudo_random_number(), action);
        outfile.put(b);
        infile.get(a);
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
        cout << "Not all files were closed successfully. The output might be incorrect." << endl ;
        return -1 ;
    }
    return 0 ;
}

