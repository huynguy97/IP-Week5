#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       

/*                                                                                
                                                                                            */
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
    assert( a>=0 && a<128);
//                                             
    int b;

    if(a<32)
    {
        b=a;
    }

    else
    {
        switch (action)
        {
            case Encrypt:  b = (a-32 + (r % (128-32)) + (128-32)) % (128-32)+32;   break;
            case Decrypt: b = (a-32 - (r % (128-32)) + (128-32)) % (128-32)+32;    break;
        }
    }
    return b;
}

void test_rotate_char ()
{
//                                                                                          
    int r;
    while(r>=0)
    {
        cout << endl << "Enter pseudo-random initialisation int: " << endl;
        cin >> r;
        assert (  r>=0 );

        //                                                                                                       

        for (int p=0; p<128; p++)
        {
            int a=p;
            char AsciiChar = a;
            initialise_pseudo_random(r);
            r = next_pseudo_random_number();
            cout << "Character: " << AsciiChar;
            cout << "  Asciicode: " << a;
            a = rotate_char(a, r, Encrypt);
            cout << "  Encrypted Asciicode: " << a;
            a = rotate_char(a, r, Decrypt);
            cout << "  Decrypted Asciicode: " << a << endl;
        }
    }
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                      
    assert (true);
//                                                   
    string Filein, Fileout;
    cout << "In stream file name: " << endl;
    cin >> Filein;
    infile.open( Filein.c_str());
    if(infile)
    {
        cout << "file in successfully opened." << endl;
    }
    else
    {
        cout << "file in could not be opened." << endl;
        return false;
    }

    cout << "Out stream file name: " << endl;
    cin >> Fileout;
    assert(Filein!=Fileout);
    outfile.open( Fileout.c_str());
    if (outfile)
    {
        cout << "file out successfully opened." << endl;
    }
    else
    {
        cout << "file out could not be opened." << endl;
        return false;
    }
    cout << endl << "infile and outfile successfully opened." << endl;
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
    assert( infile.is_open() && outfile.is_open());

//                                                                      
    initialise_pseudo_random(initial_value);
    int r = next_pseudo_random_number();
    char Character;
    while(infile)
    {
        infile.get(Character);
        Character = rotate_char(Character, r, action);
        outfile.put(Character);
        r = next_pseudo_random_number();
    }
}

int main()
{
    #include <fstream>;
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

