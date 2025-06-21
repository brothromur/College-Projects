#include <iostream>
#include <string>

using namespace std;

string series(string resist); // function that solves series connections
string parallel(string resist); // function that solves parallel connections

int main()
{
    string input; // getting circuit description from user
    getline(cin, input); // saving the input within a variable called "input"

    string par_inp = ""; // a string variable "partial input" to take the series or paralle inputs and solve them seperately

    string REQ; // to save the equivalence of each partial input
    int m_check = 0, n_check = 0; // error handling variables for circuits exceeding limit
 
    for(int i = input.length() - 1; i >= 0; i--){
        if(isalpha(input[i]) && input[i] != 'e' ){ // iterating from left to right until an 'S' or 'P' is found 
            for(int j = i; j < input.length(); j++){ // iterating from that 'S' or 'P'
                if(input[j] == 'e'){ // an 'e' is found

                     par_inp = input.substr(i, j - i + 1); // the connection is saved withtin "par_inp"

                    if(input[i] == 'S' || input[i] == 's'){
                        REQ = series(par_inp); // "par_inp" is sent to the "series" function if the connections with an 'S' 
                    }
                    else if(input[i] == 'P' || input[i] == 'p'){
                        REQ = parallel(par_inp); // "par_inp" is sent to the "parallel" function if the connections with an 'P'
                    }
                    else{
                        cout << "Wrong Description"; // if no 's' or 'p' are found, therefore the input is incorrect
                        exit(0); // terminates
                    }
                    input.replace(i, j - i + 1, REQ); // the saved connection gets replaced with its equivalent value
                    par_inp = ""; // resetting "par_inp" to accept new input
                    break; // breaking the inner loop 
                }

            }
        }

    }
    cout << "The total resistance = " << stof(input); // output once the full connection is solved
}

string series(string resist)
{
    float req = 0; // float for the connection equivalent resistance
    string tmp = ""; // stores the digits within the resistance
    int check = 0; // checker for valid input

    for(int i = 0; i < resist.length(); i++){
        if(isdigit(resist[i]) || resist[i] == '.'){
            tmp += resist[i]; // popualting "tmp" with the found digit, accounting for decimals too
        }
        else if(resist[i] == ' ' && !tmp.empty()){
            check++; //  incrementing check after every conversion 
            req += stof(tmp); // "req" gets the float value of "tmp"
            tmp = ""; // "tmp" is reset to accept new number
        }
    }
    if(check < 1){
        cout << "Incorrect Input"; // if no conversions have been made, no reistors in the connection, therefore invalid
        exit(0); // terminates program
    }
    if(check == 1){ 
        if(resist.find("0") != string::npos){ // if only 1 conversion has been made, and the string only has a 0 resistor (S 0 e)
            cout << "Incorrect Input"; // prints "Incorrect Input"
            exit(0); // terminates program
        }
    }
    return to_string(req); // returns the equivalent of the connection to the function 
}

string parallel(string resist)
{
    float req = 0; // float for the connection equivalent resistance
    float req_inv = 0; // float for the reciprocal while calculating
    string tmp = ""; // stores the digits within the resistance
    int check = 0; // checker for valid input

    for(int i = 0; i < resist.length(); i++){
        if(isdigit(resist[i]) || resist[i] == '.'){ 
            tmp += resist[i]; // popualting "tmp" with the found digit, accounting for decimals too
        }
        else if(resist[i] == ' ' && !tmp.empty()){
            check++; //  incrementing check after every conversion 
            req_inv += (float) 1 / stof(tmp); // calculating the reciprocal of req
            tmp = ""; // "tmp" is reset to accept new number
        }
    }
    if(check < 2){
        cout << "Incorrect Input"; // if less than 2 conversions have been made, 1 reistor in the connection, invalid
        exit(0); // terminates
    }
    req = 1 / req_inv; // flipping "req_inv" for the actual equivalent resistance
    return to_string(req); // returns the equivalent of the connection to the function 
}