//                                                 
//                                            

#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       

using namespace std;

enum Action {Encrypt, Decrypt} ;
Action get_user_action();

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
    assert (a >= 0 && a <=128);
//                 
//                                                                                        

    if (a < 32) {
        return a;
    }
    else {
        switch (action) {
            case Encrypt: return (a-32 + (r % (128-32))) % (128-32)+32;
            case Decrypt: return (a-32 - (r % (128-32)) + (128-32)) % (128-32)+32;
            default: return 0;
        }
    }
}

void test_rotate_char ()
{
//                
    assert (true);

//                 
//                                         
//                                                                                                 

    int r;
    cout << "Please give a value for r: "<<endl;
    cin >> r;

    if (r < 0)
    {
        cout << "Invalid value for r.";
        return;
    }

    for (int a = 0; a < 128; a++) {
        cout << char(a) << " " << a << " " << rotate_char(char(a), r, Encrypt) << " " << rotate_char(rotate_char(char(a), r, Encrypt), r, Decrypt) << endl;
    }
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert (true);

//                 
//                               
//                                           

    cout << "Please enter two file names. The file names may not contain layout symbols." <<endl;
    cout <<"Enter name of input file: ";
    string file1;
    cin >> file1;
    cout <<"Enter name of output file: ";
    string file2;
    cin >> file2;

    if (file1 == file2)
    {
        cout << "Error. Files are identical." << endl;
        return false;
    }
    infile.open (file1.c_str());
    outfile.open (file2.c_str());

    if (infile.is_open() && outfile.is_open()) {
        cout << "Files opened" << endl;
        return true;
    }
    else {
        cout << "Error.";
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
        cout << "\nPlease enter the initial coding value (greater or equal to 0 and less than 65536)" << endl ;
        cin  >> initial_value ;
    }
    return initial_value ;
}

void use_OTP (ifstream& infile, ofstream& outfile, Action action, int initial_value)
{
//                
    assert ( infile.is_open() && outfile.is_open() );

//                 
//                                                                               

    initialise_pseudo_random(initial_value);
    int random = next_pseudo_random_number();
    char c;
    infile.get(c);
    while (infile)
    {
        outfile.put(rotate_char(c, random, action));
        infile.get(c);
        random = next_pseudo_random_number();
    }
    cout << "File is successfully created."<<endl;
}

int main()
{
    cout << "*****Part 1*****" << endl;
    test_rotate_char();

//                                                                 
//                                       
//                        
//                        
//                                                           
//   
//                                          
//                 
//   

    cout << "\n\n*****Part 2 & 3*****" << endl;

    ifstream input_file  ;
    ofstream output_file ;

    if (!open_input_and_output_file (input_file,output_file))
    {
        cout << "Program aborted." << endl ;
        return -1 ;
    }

    const int INITIAL_VALUE = initial_encryption_value () ;
    use_OTP (input_file,output_file,get_user_action(),INITIAL_VALUE);
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

