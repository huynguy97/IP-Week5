/*
            
                        
                    
*/
#include <iostream>
#include <fstream>          //             
#include <cassert>         //                       

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
    char b = a ;
//                
   assert (r >= 0) ;
//                 
   if (int (a) >= 32)
   {
      if ( action == Encrypt )
          b = (a - 32 + (r % (128 - 32))) % (128 - 32) + 32 ;
      else
          b = (a - 32 - (r % (128 - 32)) + (128 - 32)) % (128 - 32)+ 32 ;
   }
   return b ;
}

void test_rotate_char ()
{
    char check , a ;
    int r ;

    do
     {
       cout << "Enter a number " ;
       cin >> r ;
//                
       assert(r >= 0) ;
//                 

       cout << "Enter a character " ;
       cin >> a ;

       cout << a << " " << (int)a << " " << (int)rotate_char(a,r,Encrypt) << " " << (int)rotate_char (rotate_char (a, r, Encrypt), r, Decrypt) << endl ;

       cout << "Another one? (y/n) " ;
       cin >> check ;

     }while ((int)check == 121) ;
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert(true) ;
//                 
   string infile_name , outfile_name ;
   cout << "Enter input file name: " ;
   cin >> infile_name ;
   cout << "Enter output file name: " ;
   cin >> outfile_name ;

   assert (infile_name != outfile_name) ;

   infile.open(infile_name.c_str()) ;

   if (infile.is_open())
        cout << "input file opened successfully!" << endl ;
    else
        cout << "input file NOT opened successfully!" << endl ;

   outfile.open(outfile_name.c_str()) ;

   if (outfile.is_open())
        cout << "output file opened successfully!" << endl ;
    else
        cout << "output file opened successfully!" << endl ;

if(!outfile.is_open() || !infile.is_open())
    return false ;
  else
    return true ;
}

Action get_user_action ()
{//               
    assert (true) ;
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
    int r = initial_value ;

//                
    assert( infile.is_open() && outfile.is_open() && r >= 0 ) ;
//                  
    initialise_pseudo_random(r) ;
    char c ;
    infile.get(c) ;
    if (action == Encrypt)
    {
        while (infile)
        {
            outfile.put(rotate_char( c, next_pseudo_random_number() , Encrypt ) ) ;
            infile.get(c) ;
        }
    }
    else
    {
        while (infile)
        {
            outfile.put(rotate_char( c, next_pseudo_random_number() , Decrypt ) ) ;
            infile.get(c) ;
        }
    }
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
        cout << "Not all files were closed successfully. The output might be incorrect." << endl ;
        return -1 ;
    }
    return 0 ;
}

