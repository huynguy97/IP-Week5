#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       

//                   
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
    assert(r > 0 && r < 65537 && a >=0 && a < 128);
    //                                                                                                     
    int sgn;
    if(action == Encrypt) {
        sgn = 1;
    } else {
        sgn = -1;
    }
    if(a < 32) {
        return a;
    } else {
        return (a - 32 + sgn * (r % 96) + 96) % 96 + 32;
    }

}

void test_rotate_char ()
{
    int r;
    while(true) {
        cout << "Enter a value for r: ";
        cin >> r;
        //                
        assert(r >= 0);
        //                                                                                                   
        //                                                           
        for(int i = 0; i < 128; i++) {
            char a = i;
            cout << a << " " << i << " " << rotate_char(a, r, Encrypt) - 0 << " " << rotate_char(rotate_char(a, r, Encrypt), r, Decrypt) - 0 << endl;
        }
    }

}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
    string input_file, output_file;
    cout << "Enter input file name: ";
    cin >> input_file;
    cout << endl << "Enter output file name: ";
    cin >> output_file;
    //                
    assert(input_file != output_file);
    //                                 
    infile.open(input_file.c_str());
    outfile.open(output_file.c_str());
    if (infile.is_open() && outfile.is_open()) {
        cout << "Succesfully opened files '" << input_file << "' and '" << output_file << "'" << endl;
        return true;
    }
    else {
        if(!infile.is_open() && outfile.is_open()) {
            cout << "Could not open file '" << input_file << "'" << endl;
        } else if(infile.is_open() && !outfile.is_open()) {
            cout << "Could not open file '" << output_file << "'" << endl;
        } else {
            cout << "Could not open files '" << input_file << "' and '" << output_file << "'" << endl;
        }
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

    char c;
    infile.get(c);
    while(infile) {
        outfile.put(rotate_char(c, next_pseudo_random_number(), action));
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

