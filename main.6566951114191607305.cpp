//                     

//                       

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

char rotate_char (char a, int r, Action e)

{

//                

    assert (a > 0 && a <= 128);

//                 

    if(e==Decrypt)

    {

        if(a>=32)

        {

            return (a-32 - (r % (128-32)) + (128-32)) % (128-32)+32;

        }

        else

        {

            return a;

        }

    }

    else

    {

        if(a>=32)

            return (a-32 + (r % (128-32)) + (128-32)) % (128-32)+32;

        else

            return a;

    }

}

//                          

//                                                                                 

//                                           

void test_rotate_char ()

{

    char a;

    int r;

//                

    assert (r > 0 && r <= 65536) ;

//                 

    cout << "enter character a = ";

    cin >> a;

    cout << "enter integer r = ";

    cin >> r;

    while(r>0)

    {

        if(r>0)

        {

            cout << "character = " << a << endl;

            cout << "ASCII code = " << int(a) << endl;

            cout << "ASCII code of rotate_char_encrypt = " << rotate_char(a,r,Encrypt) << endl;

            cout << "ASCII code of rotate_char_decrypt = " << rotate_char(rotate_char(a,r,Encrypt),r,Decrypt) << endl;

            return test_rotate_char();

        }

        else

        {

            cout << "terminate" << endl;

        }

    }

}

//                                          

//                                                                                      

//                                                    

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)

{

//                

    assert ( true ) ;

//                 

    if(infile == outfile)

        return false;

    else

    {

        if(infile.is_open()&&outfile.is_open())

            return true;

        else

            return false;

    }

}

//                                                     

//                                                                             

Action get_user_action ()

{

    //               

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

{

    //              

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

    assert (infile.is_open()&&outfile.is_open());

//                 

    initialise_pseudo_random(initial_value);

    int no_of_chars=0 ;

    char c,c2;

    infile.get (c);

    while (infile)

    {

        cout << c2 ;

        c2 = rotate_char(c,next_pseudo_random_number(),action);

        outfile.put(c2);

        infile.get(c);

    }

}

//                                                                 

//                                                                       

//                           

int main()

{

    //                   

    const Action ACTION = get_user_action() ;

    ifstream input_file  ;

    ofstream output_file ;

    string input;

    string output;

    cout << "type the name of infile"<<endl;

    cin >> input;

    input_file.open(input.c_str());

    cout << "type the name of outfile"<<endl;

    cin >> output;

    output_file.open(output.c_str());

    //                                                

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

