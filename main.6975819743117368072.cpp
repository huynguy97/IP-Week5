//                                                           
//                                               

#include <string> //                                             
#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       
#include <limits> //                                                                    

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

//                                                                
char rotate_char (char a, int r, Action action) {
//                                                                         
    assert (r >= 0 && static_cast<int>(a) >= 0);
//                                                                   
    if (static_cast<int>(a) >= 32){
        switch (action) { //                                                                      
            case Encrypt: return static_cast<char>(((static_cast<int>(a) - 32 + r%96 + 96)%96) + 32);
            case Decrypt: return static_cast<char>(((static_cast<int>(a) - 32 - r%96 + 96)%96) + 32);
        }
    }
    return a; //                          
}

//                                                         
//                                                                                                         
int take_input_r(string message){
    //                    
    assert(true);
    //                                                                                               
    int r = 0;
    cout << message << endl;
    while (!(cin >> r) || r < 0 || r > 65535){ //                                                                                                                                 
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Invalid input. " << message << endl;
    }
    cout << endl; //                                    
    return r;
}

//                                                                                                                 
void test_rotate_char () {
//                      
    assert(true);
//                                                                                                                                                   
    int r = take_input_r("Please input an integer key (0 <= r <= 65535):");
    cout << "a" << '\t' << "int(a)" << '\t' << "enc(a)" << '\t' << "dec(enc(a))" << endl;
    for (int character = 0; character < 128; character++) {
        if (character >= 32 && character < 127) { //                                                   
            cout << static_cast<char>(character) << '\t' << character << '\t'
            << static_cast<int>(rotate_char(static_cast<char>(character), r, Encrypt)) << '\t'
            << static_cast<int>(rotate_char(rotate_char(static_cast<char>(character), r, Encrypt), r, Decrypt)) << endl;
        } else { //                                                                      
            cout << '\t' << character << '\t'
            << static_cast<int>(rotate_char(static_cast<char>(character), r, Encrypt)) << '\t'
            << static_cast<int>(rotate_char(rotate_char(static_cast<char>(character), r, Encrypt), r, Decrypt)) << endl;
        }
    }
}

//                                                                            
bool contains_illegal_character(string text){
    //                    
    assert(true);
    //                                                               
    string illegal[8] = {"/","\\","*","\?","\"","<",">","|"}; //                                                 
    for (int i = 0; i < 8; i++){
        if (static_cast<int>(text.find(illegal[i])) != -1){ //                                                                                                                 
            return true; //                     
        }
    }
    return false; //                   
}

//                                                                                                                                   
string take_input_filename(string message){
    //                   
    assert(true);
    //                                                                                         
    string filename = "";
    cout << message << endl;
    while (!(cin >> filename) || contains_illegal_character(filename)){ //                                                                                                                                 
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Invalid input. " << message << endl;
    }
    cout << endl; //                                    
    return filename;
}

//                                                                                                                              
//                                                                             
bool open_input_and_output_file (ifstream& infile, ofstream& outfile) {
//                     
    assert(true);
//                                                                                     
    string infile_name = "";
    string outfile_name = "";
    infile_name = take_input_filename("Please enter the input file (no spaces). Illegal characters: / \\ * \" < > |");
    outfile_name = take_input_filename("Please enter the output file (no spaces). Illegal characters: / \\ * \" < > |");

    if (infile_name == outfile_name) { //                             
        cout << "Error: Input and output files cannot be identical." << endl;
        return false;
    }
    infile.open(infile_name.c_str());
    if (!infile.is_open()) {
        cout << "Error: Input file " << infile_name << " could not be opened." << endl;
        return false;
    }
    outfile.open(outfile_name.c_str());
    if (!outfile.is_open()) {
        cout << "Error: Output file " << outfile_name << " could not be opened." << endl;
        return false;
    }
    cout << "The files " << infile_name << " and " << outfile_name << " have been opened successfully." << endl;
    return true;
}

//                                                                                            
Action get_user_action ()
{//               
    assert ( true ) ;
/*                 
                                                                                              
*/
    cout << "Do you want to encrypt the file? (y/n): " ;
    string answer ;
    cin  >> answer ;
    if (answer == "y" || answer == "Y" || answer == "yes" || answer == "Yes")
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

//                                                                                        
void use_OTP (ifstream& infile, ofstream& outfile, Action action, int initial_value){
//                                                                                   
    assert(infile.is_open() && outfile.is_open() && initial_value >= 0 && initial_value <= 65535);
//                                               
    initialise_pseudo_random(initial_value);
    char a;
    int r = initial_value;
    infile.get(a);
    while (infile) {
        r = next_pseudo_random_number();
        outfile.put(rotate_char(a, r, action)); //                                   
        infile.get(a);
    }
    cout << endl;
}

//                                                                                                                    
int main() {
    /*                                    
                       
             
    */
    const Action ACTION = get_user_action() ;
    switch (ACTION) {
        case Encrypt:   cout << "Chosen action: Encrypt." << endl << endl;
                        break;
        case Decrypt:   cout << "Chosen action: Decrypt." << endl << endl;
                        break;
    }
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
    switch (ACTION) {
        case Encrypt:   cout << "The file has been encrypted successfully." << endl << endl;
                        break;
        case Decrypt:   cout << "The file has been decrypted successfully." << endl << endl;
                        break;
    }
    return 0 ;
}

