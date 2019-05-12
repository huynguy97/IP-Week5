#include <cassert>  //                       
#include <fstream>  //             
#include <iostream>

using namespace std;

/*                                                                   
                
                                 
                              
                                                                   */

enum Action { Encrypt, Decrypt };

int seed = 0;
void initialise_pseudo_random(int r) {
  //                
  assert(r > 0 && r <= 65536);
  /*                 
                       
  */
  seed = r;
}

int next_pseudo_random_number() {
  //                
  assert(seed > 0 && seed <= 65536);
  /*                 
                                                                            
                      
  */
  const int seed75 = seed * 75;
  int next = (seed75 & 65535) - (seed75 >> 16);
  if (next < 0)
    next += 65537;
  seed = next;
  return next;
}

char rotate_char(char a, int r, Action action) {
  //                
  assert(r >= 0);
  //                 
  //                                                 

  int i = (int)a;
  int p = 128 - 32;                             //                                                                            
  if (i < 32) {
    return i;
  } else {
    if (action == Encrypt) {                    //                                  
      return ((a - 32 + (r % p) + p) % p) + 32; //                                      
    } else {
      return ((a - 32 - (r % p) + p) % p) + 32; //                                      
    }
  }
}

void test_rotate_char() {
  //                
  assert(true);
  //                 
  //                                                                           
  //                                        

  cout << "Enter a positive integer for r: ";
  int r;
  cin >> r;
  //                                                                    
  //                
  while (r < 0) {
    cout << "Please enter a positive integer for r: ";
    cin >> r;
  }
  for (int i = 32; i < 128; i++) {
    char a = ((char)i);
    cout << a << "\t" << i << "\t" << (int)rotate_char(a, r, Encrypt) << "\t"
         << (int)rotate_char(rotate_char(a, r, Encrypt), r, Decrypt) << endl;
  }
}

bool open_input_and_output_file(ifstream& infile, ofstream& outfile) {
  //                
  assert(infile && outfile);
  //                 
  //                                                  
  //                                             

  cout << "Enter a file name (without spaced) for input: ";
  string input_name;
  cin >> input_name;
  cout << "Enter a file name (without spaces) for output: ";
  string output_name;
  cin >> output_name;

  if(input_name == output_name){        //                                                          
    cout << "Names for input and output may not be the same!" << endl;
    return false;
  } else {
    infile.open(input_name.c_str());    //                                 
    outfile.open(output_name.c_str());
    if(infile.is_open()){               //                                                             
        cout << input_name << " has opened succesfully" << endl;
    } else {
        cout << input_name << " has not opened succesfully" << endl;
        return false;
    }

    if(outfile.is_open()){              //                                                              
        cout << output_name << " has opened succesfully" << endl;
    } else {
        cout << output_name << " has not opened succesfully" << endl;
        return false;
    }

    return true;
  }
}

Action get_user_action() {  //               
  assert(true);
  /*                 
                                                                              
                      
  */
  cout << "Do you want to encrypt the file? (y/n): ";
  string answer;
  cin >> answer;
  if (answer == "y")
    return Encrypt;
  else
    return Decrypt;
}

int initial_encryption_value() {  //              
  assert(true);
  /*                 
                                                            
  */
  int initial_value = -1;
  while (initial_value < 0 || initial_value > 65535) {
    cout << "Please enter the initial coding value (greater or equal to 0 and "
            "less than 65536)"
         << endl;
    cin >> initial_value;
  }
  return initial_value;
}

void use_OTP(ifstream& infile,
             ofstream& outfile,
             Action action,
             int initial_value) {
  //               
  assert(initial_value >= 0 && initial_value <= 65535 && infile &&  //                                        
         outfile);                                                  //                                               
  //                
  //                                                                       

  initialise_pseudo_random(initial_value);

  while (infile) {
    char c;
    infile.get(c);
    outfile.put(rotate_char(c, next_pseudo_random_number(), action));
  }
}

int main() {
   cout << "For test_rotate_char, press 1\tFor encryption/decryption, press 2" << endl; //                             
   int choice;
   cin >> choice;
   while(!(choice == 1 || choice == 2)){                                                //                                                                               
     cout << "For test_rotate_char, press 1\tFor encryption/decryption, press 2" << endl;
     cin >> choice;
   }

  if(choice == 1){                                                                      //                                                      
     test_rotate_char();
  } else {                                                                              //                                            
    const Action ACTION = get_user_action();
    ifstream input_file;
    ofstream output_file;
    if (!open_input_and_output_file(input_file, output_file)) {
        cout << "Program aborted." << endl;
        return -1;
    }
    const int INITIAL_VALUE = initial_encryption_value();
    use_OTP(input_file, output_file, ACTION, INITIAL_VALUE);
    input_file.clear();
    output_file.clear();
    input_file.close();
    output_file.close();

    if (!input_file || !output_file) {
        cout << "Not all files were closed succesfully. The output might be "
                "incorrect."
            << endl;
        return -1;
    }
  }

  return 0;
}

