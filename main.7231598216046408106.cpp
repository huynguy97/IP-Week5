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
    assert(a>=0 && a<=128);
//                                                                                              
//                                                                                      

    if (action==Encrypt)
    {
        if (a<32)
            return a;
        else
            return (a-32+(r%(128-32))+(128-32))%(128-32)+32;
    }
    else if (action==Decrypt)
    {
        if (a<32)
            return a;
        else
            return (a-32-(r%(128-32))+(128-32))%(128-32)+32;
    }

}

void test_rotate_char ()
{
//                
    assert(true);
    /*                                                                           
                                                                                                              
                                                                               */
    int c,b,d,e;
    char a=32;
    do
    {
        cout<<"enter your random number: ";
        cin>>c;
        initialise_pseudo_random(c);
        while(a<127)
        {
            b=a;
            cout<<a<<" "<<b<<" "<<(d=rotate_char(a,c,Encrypt))<<" "<<(e=rotate_char(rotate_char(a,c,Encrypt),c,Decrypt))<<endl;
            a++;
        }
        cout<<a<<" "<<b+1<<" "<<(d=rotate_char(a,c,Encrypt))<<" "<<(e=rotate_char(rotate_char(a,c,Encrypt),c,Decrypt))<<endl;
        a=32;
    }
    while(c>0);

}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert(true);
//                                                                                          
    string filename_in,filename_out;
    cout<<"Name of input file: ";
    cin>>filename_in;
    cout<<"Name of output file: ";
    cin>>filename_out;
    infile.open(filename_in.c_str());
    outfile.open(filename_out.c_str());
    if(filename_in==filename_out)
    {
        cout<<"Error! File names are identical"<<endl;
        return false;
    }
    if(infile && outfile)
    {
        cout<<"Files "<<filename_in<<" and "<<filename_out<<" have been opened successfully."<<endl;
        return true;
    }
    else
    {
        return false;
        cout<<"Files could not be opened."<<endl;
    }

}

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
    assert(infile && outfile);
    /*                                                                                                                       
                                                                          */

    char a;
    initialise_pseudo_random(initial_value);

    while(infile)
    {
        next_pseudo_random_number();
        infile.get(a);
        outfile.put(rotate_char(a,seed,action));
    }
}

int main()
{
    const Action ACTION = get_user_action() ;
    ifstream input_file  ;
    ofstream output_file ;
    if (!open_input_and_output_file(input_file,output_file))
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

