/*
                         
                          
 */

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
//                
    assert(r >= 0 && r <= 65536);
//                 
//                                                                                                                                                                                 

    int b;

    if (a < 32) {
        return a;
    }

    if (action == Encrypt) {
        b = ((a - 32) + (r % (128 - 32)) + (128 - 32)) % (128 - 32) + 32;
    } else {
        b = ((a - 32) - (r % (128 - 32)) + (128 - 32)) % (128 - 32) + 32;
    }

    return char(b);

}

void test_rotate_char ()
{
//                
    assert(true);

//                 
//                                                                                                                                                         

    cout << "Enter integer value for r:" << endl;
    int r;
    cin >> r;
    while (!cin) {
        if (r < 0) {
            return;
        }
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Enter integer value for r:" << endl;
        cin >> r;
    }

    initialise_pseudo_random(r);
    for (int i = 0; i <= 127; i++) {
        int random = next_pseudo_random_number();
        char encrypted = rotate_char(char(i), random, Encrypt);
        char decrypted = rotate_char(encrypted, random, Decrypt);
        cout << char(i) << "," << i << "," << int(encrypted) << "," << int(decrypted) << endl;
    }
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert(!infile.is_open() && !outfile.is_open());
//                 
//                                                                        

    string ifname, ofname;

    do {
        cout << "Enter input file name:" << endl;
        cin >> ifname;
        while (!cin) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Enter input file name:" << endl;
            cin >> ifname;
        }
        cout << "Enter output file name:" << endl;
        cin >> ofname;
        while (!cin) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Enter output file name:" << endl;
            cin >> ofname;
        }
        if (ifname == ofname) {
            cout << "File names are the same! Please try again." << endl;
        }
    } while (ifname == ofname);

    infile.open(ifname.c_str());
    outfile.open(ofname.c_str());

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
    assert(infile.is_open() && outfile.is_open() && (initial_value < 0 || initial_value > 65535));
//                 
//                                                                                     

    char in, out;
    initialise_pseudo_random(initial_value);
    while (infile.get(in)) {
        out = rotate_char(in, next_pseudo_random_number(), action);
        cout << out << " ";
        outfile.put(out);
    }
}

int main()
{
    //               
    assert(true);
    //                
    //                                                                                     

    const Action ACTION = get_user_action() ;
    ifstream input_file;
    ofstream output_file;
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

