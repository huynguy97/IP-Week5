#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       
/*
                                
                                
*/

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

char rotate_char (char a, int r, Action ACTION, bool dec)
{
//                
    assert(a>=0 || a<128);
//                 
//                            
    char b;
    if (a<32)
    {
        b=a;
    }
    else
    {
        if (ACTION == 0 && !dec)
        {
            b = (a - 32 + (r % (128 - 32))) % (128 - 32) + 32;

        }
        else
        {
            b = (a - 32 - (r % (128 - 32)) + (128 - 32)) % (128 - 32) + 32;
        }
    }
    return b;
}

void test_rotate_char (char a, int r,Action ACTION, bool dec)
{
//                

    char ASCII = 0;
    for (int i = 0;i<=4;i++)
    {
        while (ASCII < 127)
        {
            cout << ASCII << "\t" << int(ASCII) << "\t";
            a = ASCII;
            cout << int(rotate_char(a, r, ACTION, dec)) << "\t";
            a = int(rotate_char(a, r, ACTION, dec));
            dec = true;
            cout << int(rotate_char(a, r, ACTION, dec)) << endl;
            dec = false;
            ASCII++;
        }
    ASCII = 0;
    }
//                 
}

bool open_input_and_output_file (ifstream& input_file, ofstream& output_file)
{
//                                                                  

    if (input_file.is_open() && output_file.is_open())
    {
        return true;
    }
    else
    {
        return false;
    }
//                                                                         
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
/*                 
                                                                                              
*/
}

int initial_encryption_value ()
{//              
    assert (true) ;

    int initial_value = -1 ;
    while (initial_value < 0 || initial_value > 65535)
    {
        cout << "Please enter the initial coding value (greater or equal to 0 and less than 65536)" << endl ;
        cin  >> initial_value ;
    }
    return initial_value ;
/*                 
                                                          
*/
}

void use_OTP (ifstream& input_file, ofstream& output_file, Action ACTION, int initial_value, char a, int r)
{
//                                               

    char end = '#';
    input_file.get(a);
    while (a != end)
    {
        input_file.get(a);
        a = rotate_char(a,r,ACTION,dec);
        output_file << a;
        r = next_pseudo_random_number();
    }
//                                                                   
}

int main()
{

    char a;
    //                   
    //       

    const Action ACTION = get_user_action() ;
/*        
                       
           
                     
                                
                                     
                                              
*/
    string inputname;
    cout << "What is the name of the inputfile? please make sure you add .txt ";
    cin >> inputname;
    string outputname;
    cout << "What is the name of the outputfile? please make sure you add .txt ";
    cin >> outputname;
    assert(outputname != inputname);
    ifstream input_file ("C:/Users/wardl/OneDrive/Documenten/Universiteit/Jaar 1/Kwartaal 1/Imperative programming/IPC031_2017_assignment_5_files/" + inputname);
    ofstream output_file ("C:/Users/wardl/OneDrive/Documenten/Universiteit/Jaar 1/Kwartaal 1/Imperative programming/IPC031_2017_assignment_5_files/" + outputname);

    if (!open_input_and_output_file (input_file,output_file))
    {
        cout << "Program aborted." << endl ;
        return -1 ;
    }
    const int INITIAL_VALUE = initial_encryption_value () ;
    int r = INITIAL_VALUE;
    initialise_pseudo_random(r);

    use_OTP (input_file,output_file,ACTION,INITIAL_VALUE,a,r);
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

