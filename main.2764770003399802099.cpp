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
    int b;
    int i;
/*                 
                                                                                                                               
*/
    if (i < 32){
        b = a;
    }
    else if (i >= 32){
        if (action == Encrypt){
            b = (a-32 + (r % (128-32)) + (128-32)) % (128-32)+32;
        }
        else{
            b = (a-32 - (r % (128-32)) + (128-32)) % (128-32)+32;
        }

    }

}

void test_rotate_char ()
{
    int r = 0;
    cout << "Give an r: " << "\n";
    cin >> r;
    cout << "If r has a value of " << r << "Then encrypting and decrypting goes as following: "<< "\n";

    for (int i=0;((i >= 0)&&(i <= 32)); i++){
    char a = i;
    cout << "Ascii code: " << i << ". Ascii: " << a;
     a = rotate_char (a, r, Encrypt);
     int EncryptA = a;
    cout << ". Encrypted: " << EncryptA;
     a = i;
     a =  rotate_char (rotate_char (a, r, Encrypt), r, Decrypt);
     EncryptA = a;
    cout << ". Decrypted: " << EncryptA << "\n";
    }

    for (int i=33;((i > 32)&&(i < 128)); i++){
    char a = i;
    cout << "Ascii code: " << i << ". Ascii: " << a;
     a = rotate_char (a, r, Encrypt);
     int EncryptA = a;
    cout << ". Encrypted: " << EncryptA;
     a = i;
     a =  rotate_char (rotate_char (a, r, Encrypt), r, Decrypt);
     EncryptA = a;
    cout << ". Decrypted: " << EncryptA << "\n";
    }

}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
    string x;
    string y;
    cout << "Give filenames"<< "\n";
    cin >> x >> y;
/*                 
                                                                                                                                                                            
*/
    if (x == y){
        cout << "Ërror: filenames can't be the same";
    }
    else{
        infile.open(x.c_str());
        if (infile.is_open()){
            outfile.open(y.c_str());
                if(outfile.is_open()){
                    return infile.is_open() && outfile.is_open();
                }

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
int r = initial_value;
while (infile){
    infile.get(c);
    r = next_pseudo_random_number();
    outfile.put(rotate_char(c,r,action));
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

