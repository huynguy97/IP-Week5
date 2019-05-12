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
    assert (r >= 0 && r <= 65536 && "ERROR: Invalid r value") ;
//                                                                    
    char b = 0;
    if (action == Encrypt) {
            if (int(a) < 32) {
                b = a;
            } else {
                b = (a-32 + (r % (128-32)) + (128-32)) % (128-32)+32;
            }
           } else {
            if (int(a) < 32) {
                b = a;
            } else {
                b = (a-32 - (r % (128-32)) + (128-32)) % (128-32)+32;
            }
           }
    return b;
    //                                   
}

void test_rotate_char (ifstream& infile)
{
//                
    assert (infile.is_open() && "ERROR: Input file not open");
//                                  
    cout << "When testing is done, enter a negative number." << endl << endl;
    char plain_text = ' ';
    int random = 0;
    while (random >= 0) {
        cout << endl;
        cout << "Enter random number value:" << endl;
        cin >> random;
        cout << endl;
        infile.get (plain_text);
        while (infile && random >= 0) {
            cout << plain_text << " ";
            cout << int(plain_text) << " ";
            cout << int(rotate_char(plain_text, random, Encrypt)) << " ";
            cout << int(rotate_char(rotate_char(plain_text, random, Encrypt), random, Decrypt)) << endl;
            infile.get(plain_text);
        }
    infile.close();
    infile.open("test.txt");
    }
    random = 0;
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert (true);
//                                                                                                                                                                     
    string input_choice = " ";
    string output_choice = " ";
    cout << endl << "Give the input file name (.txt format required, along with no special characters in the name):" << endl;
    cin >> input_choice;
    infile.open (input_choice.c_str());
    cout << endl;
    cout << "Give the output file name (.txt format required, along with no special characters in the name):" << endl;
    cin >> output_choice;
    outfile.open (output_choice.c_str());
    cout << endl;
    if (input_choice == output_choice) {
        cout << "ERROR: File names are the same!" << endl << endl;
        return false;
    }
    if (infile.is_open()) {
        cout << input_choice << " opened successfully" << endl << endl;
    }
    if (outfile.is_open()) {
        cout << output_choice << " opened successfully" << endl << endl;
    }
    if (infile.is_open() && outfile.is_open()) {
        return true;
    }
    return false;

}

Action get_user_action ()
{//               
    assert ( true ) ;
/*                 
                                                                                              
*/  cout << "Do you want to run a test before using the program? (y/n)" << endl;
    string answer ;
    cin >> answer ;
    if (answer == "y"){
        cout << "Testing for test.txt:" << endl <<  endl;
        ifstream test;
        test.open("test.txt");
        test_rotate_char(test);
    }
    cout << "Do you want to encrypt the file? (y/n): " ;
    string answer2 ;
    cin  >> answer2 ;
    if (answer2 == "y")
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
    assert (infile.is_open() && outfile.is_open() && initial_value >= 0 && initial_value <= 65535 && "ERROR: Check function parameters");
//                                                                                                                                                                               
    char letter_output = ' ';
    char letter_input = ' ';
    infile.get(letter_input);
    initialise_pseudo_random(initial_value);
    while (infile) {
       initial_value = next_pseudo_random_number();
       letter_output = rotate_char(letter_input, initial_value, action);
       outfile.put(letter_output);
       infile.get(letter_input);
    }
    cout << "Operation Successful!" << endl;

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

