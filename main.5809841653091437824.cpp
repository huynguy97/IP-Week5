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
    assert(action==Encrypt  || action ==Decrypt);
//                                                                                               
    char b;
    if(a>=32)
    {
        if(action==Encrypt)
        {
            b= ((a-32+(r%(128-32))+(128-32))%(128-32)+32) ;//                            
        }
        if(action==Decrypt)
        {
            b= ((a-32-(r%(128-32))+(128-32))%(128-32)+32) ;//                               
        }
    }
    else//                                                                    
    {
        b=a;
    }
    return b;

}

void test_rotate_char ()
{
//                
    assert(true);
//                                                                                       
    int r;
    int a = 32;//                                                                 
    cout << "Please enter r such that 0 <= r < 2^16"<<endl;
    cin >> r;
    while(!cin)//                                                            
    {
        cin.clear()   ;
        cin.ignore( 1000, '\n') ;
        cout<<"No, please enter an integer such that 0 <= r < 2^16" << endl;
        cin>>r ;
    }
    if(r<0)//                                             
    {
        return;//                       
    }
    initialise_pseudo_random(r);//                                                        
    while(a<128)//                                
    {
        r = next_pseudo_random_number();//                       
        cout << char(a) <<"\t"<< a << "\t";//                                                    
        cout << int(rotate_char(a, r, Encrypt))<< "\t";//                                    
        cout << int(rotate_char(rotate_char(a, r, Encrypt), r, Decrypt))<<endl;//                                                       
        a++;//                             
    }

}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert(true);
//                                                                                
    string inputfile;
    string outputfile;
    cout<<"Please enter a filename for the inputfile you want to open" << endl;
    cin >> inputfile;
    while(!cin)//                                                                                   
    {
        //                                          
        cin.clear();
        cin.ignore( 1000, '\n') ;
        cout << "Try again" << endl;
        cin>>inputfile;
    }
    cout<<"\n Please enter a filename for the outputfile you want to open" << endl;
    cin>>outputfile;
    while(!cin)//                                                                                   
    {
        //                                          
        cin.clear();
        cin.ignore( 1000, '\n') ;
        cout << "Try again" << endl;
        cin >> outputfile;
    }
    if(inputfile==outputfile)//                            
    {
        cout<<"It is not possible to open two files with the same name." << endl;
        return false;
    }
    //               
    infile.open(inputfile.c_str());
    outfile.open(outputfile.c_str());
    if(infile.is_open()&&outfile.is_open())//                           
    {
            cout<<"Opening was successful"<<endl;//                                    
            return true;
    }
    else
    {
        cout << "Files could not be opened"<< endl;//                                 
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
    assert(true);
//                                                                                                                                                
    char c;
    initialise_pseudo_random(initial_value);//                                                        
    do
    {
        infile.get(c);//                                    
        outfile<< rotate_char(c, next_pseudo_random_number(), action);//                                                         
    }
    while(infile);//                                     
}

int main()
{
    const Action ACTION = get_user_action() ;
    ifstream input_file  ;
    ofstream output_file ;
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
    ifstream infile;
    ofstream outfile;
    return 0 ;
}

