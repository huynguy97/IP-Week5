#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       

using namespace std;

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
/*                 
                                                                                            
*/
    const int seed75 = seed * 75 ;
    int next = (seed75 & 65535) - (seed75 >> 16) ;
    if (next < 0)
        next += 65537 ;
    seed = next ;
    return next ;
}

char rotate_char (char a, int r , Action action)
{
//                
    assert (r>=0 && r<65536);
/*                 
                                                     
*/
    int b;
    if (32<a<128)
    {
        Action Encrypt,Decrypt;
        if (Encrypt)
        {
            b=(a-32 + (r % (128-32)) + (128-32)) % (128-32)+32;
            cout << b << endl;
            return 0;
        }
        else if (Encrypt,Decrypt)
        {
            b=(a-32 + (r % (128-32)) + (128-32)) % (128-32)+32;
            a=b;
            b=(a-32 - (r % (128-32)) + (128-32)) % (128-32)+32;
            cout << b << endl;
            return 0;
        }
    }
    else
    {
        b=a;
        cout << b << endl;
    }

}

void test_rotate_char ()
{
//                
    assert ("r>=0 && r<65536 && a>0 && a<128");
/*                 
                                                  
*/
    int r;
    cout << "please enter r" << endl;
    cin >> r;
    int a;
    cout << "please enter a" << endl;
    cin >> a;
    cout << "a" << endl;
    cout << "this is your number in ASCII: " << a << endl;
    if (32<a && a<128)
    {
    cout << "this is your encrypted number" << endl;
    cout << rotate_char(a , r , Encrypt) << endl;
    cout << "this is your decrypted number after encryption" << endl;
    cout << rotate_char(a,r,Decrypt) << endl;
    }
    else
    {
        cout << "this is your encrypted number: " << a << endl;
    }
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert (true);
/*                 
                                                   
*/
    cout << "enter a input file name (without spaces)" << endl;
    string filename_1;
    cin >> filename_1;
    ifstream input_file (filename_1.c_str());
    cout << "enter a output file name (without spaces)" << endl;
    string filename_2;
    cin >> filename_2;
    ofstream output_file (filename_2.c_str());
    if (filename_1 == filename_2)
    {
        cout << "error" << endl;
    }
    else if (input_file.is_open()&& output_file.is_open())
    {
        cout << "both files were succesfully opened" << endl;
        return true;
    }
    else
    {
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
    assert (true);
//                 
//                                    
    char a;
    int b;
    int seed=initial_value;
    next_pseudo_random_number();
    while (infile)
    {infile >> a;
    int r;
    rotate_char(a,r,action);
    outfile << b;
    }

}

int main()
{
    cout << "test_rotate_char=1, else 2" << endl;
    int choice;
    cin >> choice;
    if (choice==1)
    {
        test_rotate_char();
    }
    else {const Action ACTION = get_user_action() ;
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
}

