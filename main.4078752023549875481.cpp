/*                                                                    
                                                                      
 */

#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       
#include <string>

using namespace std;

enum Action {Encrypt, Decrypt};

int seed = 0;
void initialise_pseudo_random(int r)
{
//                
    assert(r > 0 && r <= 65536);
/*                 
                     
*/
    seed = r;
}

int next_pseudo_random_number()
{
//                
    assert(seed > 0 && seed <= 65536);
/*                 
                                                                                            
*/
    const int seed75 = seed * 75;
    int next = (seed75 & 65535) - (seed75 >> 16);
    if (next < 0)
        next += 65537;
    seed = next;
    return next;
}

char rotate_char(char a, int r, Action action)
{
//                
    assert(r >= 0 && 0 <= a <= 128);

/*                 
                                                                 
 */
    int b = 0;

    if (action == Encrypt) {
        if (a >= 32) {
            b = (a - 32 + (r % (128 - 32)) + (128 - 32)) % (128 - 32) + 32;
        } else {
            return a;
        }
    } else if (action == Decrypt) {
        if (a >= 32) {
            b = (a - 32 - (r % (128 - 32)) + (128 - 32)) % (128 - 32) + 32;
        } else {
            return a;
        }
    }

    return b;
}

void test_rotate_char()
{
//                
    assert(true);

/*                 
                                                                              
                                                                                
                             
 */

    int value = 0;
    cout << "Give a value for r" << '\n';
    cin >> value;

    while (value >= 0) {
        for (int i = 0; i < 128; i++) {
            char a = static_cast<char>(i);
            cout << "Char a: " << a << '\n';
            cout << "ASCII a: " << i << '\n';
            int b = rotate_char(a, value, Encrypt);
            cout << "ASCII rotate a: " << b << '\n';
            int c = rotate_char(rotate_char(a, value, Encrypt), value, Decrypt);
            cout << "ASCII rotate rotate a: " << c << '\n';
        }

        cout << "Give a value for r" << '\n';
        cin >> value;
    }
}

bool open_input_and_output_file(ifstream& infile, ofstream& outfile)
{
//                
    assert(infile);
    assert(outfile);
/*                 
                                                                            
                                              
 */

    string inputfilepath, outputfilepath;
    cout << "Please give the name of the input file." << endl;
    cin >> inputfilepath;
    cout << "Please give the name of the output file." << endl;
    cin >> outputfilepath;

    if (inputfilepath == outputfilepath) {
        cout << "Error invalid file names." << endl;
        return false;
    } else {
        inputfilepath.append(".txt");
        outputfilepath.append(".txt");
        infile.open(inputfilepath.c_str());
        outfile.open(outputfilepath.c_str());

        if (infile.is_open() && outfile.is_open()){
            cout << "The files are open" << endl;
            return true;
        } else {
            cout << "The files are not open" << endl;
            return false;
        }
    }
}

Action get_user_action()
{//               
    assert(true);
/*                 
                                                                                              
*/
    cout << "Do you want to encrypt the file? (y/n): ";
    string answer;
    cin  >> answer;
    if (answer == "y")
        return Encrypt;
    else
        return Decrypt;
}

int initial_encryption_value()
{//              
    assert(true);
/*                 
                                                          
*/
    int initial_value = -1;
    while (initial_value < 0 || initial_value > 65535)
    {
        cout << "Please enter the initial coding value (greater or equal to 0 and less than 65536)" << endl;
        cin  >> initial_value;
    }
    return initial_value;
}

void use_OTP(ifstream& infile, ofstream& outfile, Action action, int initial_value)
{
//                
    assert(infile);
    assert(outfile);
/*                 
                                                                                
                                        
 */

    int r = initial_value;
    char a = infile.get();
    while(!infile.eof()){
        r = next_pseudo_random_number();
        outfile.put(rotate_char(a, r, action));
        infile.get(a);
    }
}

int main()
{
    const Action ACTION = get_user_action();
    ifstream input_file;
    ofstream output_file;
    if (!open_input_and_output_file(input_file,output_file))
    {
        cout << "Program aborted." << endl;
        return -1;
    }
    const int INITIAL_VALUE = initial_encryption_value();
    initialise_pseudo_random(INITIAL_VALUE);
    use_OTP (input_file,output_file,ACTION,INITIAL_VALUE);
    input_file.clear();
    output_file.clear();
    input_file.close();
    output_file.close();

    if (!input_file || !output_file)
    {
        cout << "Not all files were closed succesfully. The output might be incorrect." << endl;
        return -1;
    }
    return 0;
}

