//                              
//                                 

#include <iostream>
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
    int ascii_code = int(a);

//                
    assert((ascii_code >=0 && ascii_code < 128) && (r > 0 && r <= 65536) && (action == Encrypt || action == Decrypt));

//                 
    if (ascii_code < 32)
        return a;

    //                                                                                                                   
    //                                                                                                   
    else if (ascii_code >= 32)
    {
        if (action == Encrypt)
            return char((ascii_code-32+(r%(128-32))+(128-32))%(128-32)+32);

        else if (action == Decrypt)
            return char((ascii_code-32-(r%(128-32))+(128-32))%(128-32)+32);

    }
    return 0;
}

void test_rotate_char ()
{
//                
    assert(true);

//                 
    int r;
    cout << "Enter a non-negative value for r: ";
    cin >> r;

    //                                                                                                                                                                                                                                                                                     
    while (r >=0)
    {
        for (int i=32; i<128; i++)
        {
            cout << char(i) << "\t " << i << "\t " << int(rotate_char(char(i), r, Encrypt)) << "\t " << int(rotate_char(rotate_char(char(i), r, Encrypt), r, Decrypt)) << endl;
        }

        cout << "\n Enter a non-negative value for r: ";
        cin >> r;
    }

}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert (true);

//                 
    string input_file_name;
    string output_file_name;

    cout << "Enter an input file name (without spaces): ";
    cin >> input_file_name;
    cout << "Enter an output file name (without spaces): ";
    cin >> output_file_name;

    if (input_file_name == output_file_name)
    {
        cout << "Input and output file names are identical!" << endl;
        return false;
    }
    else
    {
        infile.open(input_file_name.c_str());
        outfile.open(output_file_name.c_str());

        if (infile.is_open() && outfile.is_open())
        {
            cout << "Both files successfully opened." << endl;
            return true;
        }
        else
        {
            cout << "Input file does not exist!" << endl;
            return false;
        }
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
        cout << "Please enter the initial coding value (greater or equal to 0 and less than 65536): ";
        cin  >> initial_value ;
    }
    return initial_value ;
}

void use_OTP (ifstream& infile, ofstream& outfile, Action action, int initial_value)
{
//                
    assert ((infile.is_open() && outfile.is_open()) && (action == Encrypt || action == Decrypt) && (initial_value > 0 && initial_value <= 65536));

//                 
    char c;
    initialise_pseudo_random(initial_value);

    //                                                                                                                                                                                                                     
    infile.get(c);
    while (infile)
    {
        outfile.put(rotate_char(c, next_pseudo_random_number(),action));
        infile.get(c);
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

