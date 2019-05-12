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
    assert(r>=0);
//                 
    //                                                           
    int b;

    switch (action)
    {
    case Encrypt :
    {
        if (a<32)
        {
            b=a;
            return b;
        }
        if (a>=32)
        {
            b =  (a-32 + ( r % (128-32)) +(128-32)) % (128-32) +32 ;
            return b;
        }
    }
    break;

    case Decrypt:

        if (a < 32)
        {
            b=a;
            return b;
        }

        if ( a >= 32 )

        {
            b =  (a-32 - ( r % (128-32)) +(128-32)) % (128-32) +32 ;
            return b;
        }
        break;
    }
    return 0;
}

void test_rotate_char ()
{
//                
    assert(true);
//                                                                                                
    int r;
    cout << "Enter a positive value for r: ";
    cin >> r;

    for (int i = 32; i < 127; i++)
    {
        cout << char(i) << ' ' << rotate_char(char(i), r, Encrypt) << ' ' << rotate_char(rotate_char(char(i), r, Encrypt), r, Decrypt) << endl;
    }
}

bool open_input_and_output_file (ifstream& input_file, ofstream& output_file)
{
//                
    assert(!input_file.is_open() && !output_file.is_open());
//                                                                                                                             
    string i,o;
    cout<<"Enter the input file name"<<endl;
    cin>> i;
    cout<<"Enter the output file name"<<endl;
    cin>> o;
    if (i==o)
    {
        cout<<"Error Filenames cant be the same"<<endl;
        exit(0);
    }
    input_file.open(i);
    output_file.open(o);
    if (input_file.is_open() && output_file.is_open())
        return true;
    else
        return false;

}

Action get_user_action ()
{
    //               
    assert( true ) ;
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
{
    //              
    assert (true) ;
    //               
    //                                                      

    int initial_value = -1 ;
    while (initial_value < 0 || initial_value > 65535)
    {
        cout << "Please enter the initial coding value (greater or equal to 0 and less than 65536)" << endl ;
        cin  >> initial_value ;
    }
    return initial_value ;
}

void use_OTP (ifstream& input_file, ofstream& output_file, Action action, int initial_value)
{
//                
    //                         
//                                                                                               

    initialise_pseudo_random(initial_value);
    while(input_file)
    {
        int c ;
        char e;
        c = next_pseudo_random_number();
        e=rotate_char(input_file.get(),c,action);
        output_file.put(e);

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

