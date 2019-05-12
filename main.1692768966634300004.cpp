#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       
#include <string>           //                     

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
    assert(r >= 0);
/*                 
                                                                                                                                                         
*/
    if(a < 32) {
        return a;
    } else {
        if(action == Encrypt) {
            return (a-32+(r%(128-32))+(128-32))%(128-32)+32;
        } else {
            return (a-32-(r%(128-32))+(128-32))%(128-32)+32;
        }
    }
}

void test_rotate_char ()
{
//                
    assert (true);
//                 
    char ans = 'y';
    while(ans == 'y') {
        int r;
        cin >> r;
        assert(r>=0);
        for (int i = 0; i < 128; i++) {
            char a = (char)i;
            int aValue = (int)a;
            char b = rotate_char(a,r,Encrypt);
            int bDecrypted = (int)rotate_char(b,r,Decrypt);

            cout << a << "\t" << aValue << "\t" << (int)b << "\t" << bDecrypted << endl;
        }
        cout << "Another one? (y/n)";
        cin >> ans;
    }
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert(true);
/*                 
                                                                         
*/
    string input_file_name;
    string output_file_name;
    cout << "input file: ";
    cin >> input_file_name;
    cout << "output file: ";
    cin >> output_file_name;

    infile.open(input_file_name.c_str());
    outfile.open(output_file_name.c_str());

    if(input_file_name == output_file_name) {
        return false;
    } else {
        return true;
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
    assert(true);
/*                 
                                                                                                       
*/
    initialise_pseudo_random(initial_value);
    char c;
    string rotated_text = "";
    infile.get (c);
    while (infile){
        next_pseudo_random_number();
        rotated_text += rotate_char(c,seed,action);
        outfile.put (rotate_char(c,seed,action));
        infile.get (c);
    }
    //                                                     
    cout << rotated_text;
}

int main()
{
    const Action ACTION = get_user_action() ;
    ifstream input_file ;
    ofstream output_file ;
    if (!open_input_and_output_file (input_file,output_file))
    {
        cout << "Program aborted." << endl ;
        return -1 ;
    }
    const int INITIAL_VALUE = initial_encryption_value () ;
    use_OTP (input_file,output_file,ACTION,INITIAL_VALUE) ;
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

