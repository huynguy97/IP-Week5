//                                     
//                                      

#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       
#include <cstring>

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
    assert (r > 0 && r <= 65536);
/*                 
                                                               
*/
    char b;

    int ascii=(int)(a);

    if(ascii>=32)
    {

        if(action==Encrypt)
            ascii=(ascii-32+(r%(128-32))+(128-32))%(128-32)+32;
        else
            ascii=(ascii-32-(r%(128-32))+(128-32))%(128-32)+32;
    }

    b=char(ascii);

    return b;
}

void test_rotate_char ()
{
//                
    assert(true);
/*                 
                                                                                                                  
                                                                                                 
*/
    int r;
    char a;
    cin>>r;
    initialise_pseudo_random(r);
    while(true)
    {
        cin>>a;
        r=next_pseudo_random_number();
        cout<<a<<" "<<int(a)<<" "<<(int)(rotate_char(a,r,Encrypt))<<" "<<(int)(rotate_char(rotate_char(a,r,Encrypt),r,Decrypt));
    }
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
    string name1, name2;
//                
    assert(true);
/*                 
                                                                                   
*/

    cout<<"Please enter input filename: "; cin>>name1;
    cout<<"Please enter output filename: "; cin>>name2;

    while(name1==name2)
    {
        cout<<"Error: file names should be different."<<endl;
        cout<<"Please enter input filename: "; cin>>name1;
        cout<<"Please enter output filename: "; cin>>name2;
    }

    infile.open(name1.c_str());
    outfile.open(name2.c_str());

    if(!infile||!outfile)
    {
        cout<<"The files could not be opened."<<endl;
        return false;
    }

    cout<<"The files were opened successfully."<<endl;
    return true;
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
    assert (initial_value > 0 && initial_value <= 65536);
/*                 
                                                                   
                                                              
*/
    char c;

    initialise_pseudo_random(initial_value);

    while(infile)
    {
            infile.get(c);
            initial_value=next_pseudo_random_number();
            outfile.put(rotate_char (c, initial_value, action));
    }

    if(infile.eof())
        cout<<"The text was converted successfully.";
}

int main()
{
    //                   
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

