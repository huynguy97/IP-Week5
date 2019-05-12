#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       

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
    assert(a>=0 && a<=127);
//                                                                                                                                                        
    if(a<32)return a;

    int b = a-32;
    if(action==Encrypt)
        b+=(r%(128-32))+(128-32);
    else
        b=b-(r%(128-32))+(128-32);
    b = (b%(128-32))+32;

}

void test_rotate_char ()
{
    int r;
    while(true){
        cout << "\nInput value for r: ";
        cin >> r;
//                
    assert(r>=0);

//                                                                                                                                                                                              
    initialise_pseudo_random(r);
    for(int i=0; i<128;i++){
        int rand=next_pseudo_random_number();
        cout << static_cast<char>(i) << "\t" << i << "\t" << static_cast<int>(rotate_char(i, rand, Encrypt));
        rand=next_pseudo_random_number();
        cout << "\t" << static_cast<int>(rotate_char(rotate_char(i, rand, Encrypt), rand, Decrypt))<< "\n";
        }
    }
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
    string in;
    string out;
    cout << "Enter the name for your input file: ";
    cin >> in;
    cout << "Enter the name for your output file: ";
    cin >> out;

//                
    assert(in!=out && "Input and output files cannot be the same!");

//                 
    infile.open(in.c_str());
    outfile.open(out.c_str());
    if(infile.is_open()&& outfile.is_open()){
        cout<< "The input and output files have been opened successfully!\n";
        return true;
    }else{
        cout<< "The input and output files have NOT been opened successfully!\n";
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

//                 
    initialise_pseudo_random(initial_value);
    char c;
    while(infile){
        infile.get(c);
        outfile.put(rotate_char(c, next_pseudo_random_number(), Encrypt));
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

