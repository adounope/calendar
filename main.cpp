#include <iostream>
using namespace std;

//all functions in this program refer monday as week day 0
//and jan as month 0
int ask_range(char prompt[100], int val_min, int val_max){
    //ask_range function can ask the user until have an expected reply in specified integer range
    double x;
    string input;
    restart_func:
    cout << prompt << ": ";
    cin >> input;
    try{
        x = stod(input);
        int temp = x;
        if (x-temp != 0 || x > val_max || x < val_min){//if x is not the desired value
            throw "hi"; //I am not sure about this, but if I just type throw, without "hi"
            //the program will terminate called without an active exception upon input like 3.14
        }
    }
    catch(...){
        goto restart_func;
    }
    return (int)x;
}
char ask_choice(char prompt[100], char keys[2]){
    char input;
    restart_func:
    cout << prompt << ": ";
    cin >> input;
    bool restart = true;
    for(int i = 0; i < 2; i++){
        if(input == keys[i]){
            restart = false;
        }
    }
    if(restart == true){
        goto restart_func;
    }
    return input;
}
int mod(int a, int b){//correct mod function
    int c = a%b;
    return (c >= 0)?c:b+c; 
}
bool leap_year(int yr){
    bool leap = false;
    if(yr%4 == 0){
        leap = true;
    }
    if(yr%100 == 0){
        leap = false;
    }
    if(yr%400 == 0){
        leap = true;
    }
    return leap;
}
char weekday[7][3] = {
    "Mo",
    "Tu",
    "We",
    "Th",
    "Fr",
    "Sa",
    "Su"
};
int _1st_weekmonth(int yr, int month){
    // example: Jan: month = 0, Feb: month = 1
    //return day(mon,tue...sun) of 1st of any month in any year
    //starting date refer to 1st jan 1800,
    //which is wednesday, thus setting day = 2, so that weekday[day] = "We"
    int day = 2;
    int days_in_month[12] = {31,28,31,30,31,30,31,31,30,31,30,31};//local var
    for(int i = 1800; i < yr; i++){//day = weekday of 1st jan of every year
        if(leap_year(i) == false){
            day = (day + 1)%7;
        }
        else{day = (day + 2)%7;}
    }
    if(leap_year(yr)){//february have 29 days in leap year
        days_in_month[1] = 29;
    }
    for(int m = 0; m<month; m++){
        //for example in July, month = 7-1 = 6 (jan is month 0)
        //thus, it have completed days in previous 6 month
        //and so, adding days_in_month[0] to days_in_month[5]
        day = (day + days_in_month[m])%7;
    }
    return day;
}
char dialogue[5][100] = {
    "Enter year (in range 1800-9999)",
    "Enter month (in range 1-12)",
    "Enter the first day of week ('s' for Sunday, 'm' for Monday)",
    "Print horizontally (h) or vertically (v)",
    "Enter the month in the center (in range 1-12)"
};
char month_name[12][20] = {
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
};
char cal_text[3][7][7][3];//a calendar matrix to store char of a calendar, which is at most 7x7 grid (included the mon, tue, wed... bar)
int strlen(char * c_str){//cheating to use strlen function
    int i=0;
    while((int)c_str[i] != 0){
        i++;
    }
    return i;
}
void fill_cal_mat(char cal_mat[7][7][3], int year, int month, char direction, char day){//this function fill the month calendar of a month in specific year
    //cal_mat require a 7*7*3 char sized array
    //month=0 for january and so on
    //direction option 'h'-for horizontal or 'v'-for vertical
    //day is the first day of the week, 'm' for monday, 's' for sunday
    int days_in_month[12] = {31,28,31,30,31,30,31,31,30,31,30,31};//this array is local
    if(leap_year(year)){
        days_in_month[1] = 29;
    }
    else{
        days_in_month[1]=28;
    }
    //defaul: day = 'm', direction = 'h'
    int offset = ( day == 'm')? 0:1;
    //offset the cal by 1 if user want first day as sunday
    //which is equivalent to shifting all days 1 day after (as below code)
    int _1st = (_1st_weekmonth(year, month)+offset)%7;
    if(direction == 'v'){ //vertical case
        for(int i=0; i<7; i++){
            for(int j=0; j<2; j++){
                cal_mat[(i+offset)%7][0][j] = weekday[i][j];
            }
        }
        for(int i=0; i<42; i++){
            if(i < _1st || i >= (_1st + days_in_month[month])){
                cal_mat[i%7][1+(i/7)][0] = ' ';
                cal_mat[i%7][1+(i/7)][1] = ' ';
            }
            else{//when this case is first run, i = _1st
                int date = 1+i-_1st; //so that the date is 1 on the 1st day of the month
                int dec_digit = (int)(date/10);
                cal_mat[i%7][1+(i/7)][1] = date%10 + '0';//this offset from ascii position of char '0'
                if(dec_digit != 0){
                    cal_mat[i%7][1+(i/7)][0] = dec_digit + '0';
                }
                else{
                    cal_mat[i%7][1+(i/7)][0] = ' ';
                }
            }
        }
    }
    else{//horizontal case
        for(int i=0; i<7; i++){
            for(int j=0; j<2; j++){
                cal_mat[0][(i+offset)%7][j] = weekday[i][j];
            }
        }
        for(int i=0; i<42; i++){
            if(i < _1st || i >= (_1st + days_in_month[month])){
                cal_mat[1+(i/7)][i%7][0] = ' ';
                cal_mat[1+(i/7)][i%7][1] = ' ';
            }
            else{//when this case is first run, i = _1st
                int date = 1+i-_1st; //so that the date is 1 on the 1st day of the month
                int dec_digit = (int)(date/10);
                cal_mat[1+(i/7)][i%7][1] = date%10 + '0';//this offset from ascii position of char '0'
                if(dec_digit != 0){
                    cal_mat[1+(i/7)][i%7][0] = dec_digit + '0';
                }
                else{
                    cal_mat[1+(i/7)][i%7][0] = ' ';
                }
            }
        }
    }
    

}
void fill_cal_mat_triple(char cal_mat[3][7][7][3], int year, int center_month, char direction, char day){
    //this function fills the triple month into a calendar text matrix
    int _month;
    for(int i = 0; i <= 2; i++){
        _month = center_month - 1 + i;// center_month -1 is the before month
        fill_cal_mat(cal_text[i], (year-1 + (12+_month)/12), mod(_month,12), direction, day);
        //when _month = -1, (year-1 + (12+_month)/12) = year-1
    }
}
void print_cal(char cal_mat[7][7][3]){
    int temp = 0;
    for(int i = 0; i< 7; i++){
        for(int j = 0; j< 7; j++){
            for(int k = 0; k < 2; k++){
                cout << cal_mat[i][j][k];
                temp++;
                if(temp%2 == 0){//print a space in every 2 char printed
                    cout << ' ';
                }
            }
        }
        cout << endl;
    }
}
void print_cal_triple(char cal_mat[3][7][7][3]){
    int temp=0;
    for(int i = 0; i<7; i++){//print next line
        for(int m = 0; m<3; m++){// print line on another month
            for(int j = 0; j<7; j++){// print grid on each line
                for(int k = 0; k<2; k++){//print text in each grid
                    cout << cal_mat[m][i][j][k];
                    temp++;
                    if(temp%2 == 0){//print a space in every 2 char printed
                        cout << ' ';
                    }
                }
            }//printing next month on the same line
            cout << ' ';//extra space to separate the month
        }
        cout << endl;
    }
    for(int _ = 0; _ < 3; _++){
        if(cal_mat[_][6][0][0] != ' '){
            //if any month of the last line of the calendar matrix is non empty
            cout << endl;
            break;
        }
    }
}



int main(){
    int year = ask_range(dialogue[0], 1800, 9999);
    reask:
    int month = ask_range(dialogue[1], -3, 12);
    char day;//day is the first day of a week, possible answer: 'm' for monday, 's' for sunday
    char direction;
    if(month == 0 || month == -2){//accept range of -3 to 12 includsive, except -2 and 0
        goto reask;
    }
    else if(month >= 1 && month <= 12){//normal mode(non bonus)
        month -= 1;
        //converting month in user input (month = 1 for jan) to program month (0 for jan),
        day = ask_choice(dialogue[2], "sm");
        direction = ask_choice(dialogue[3], "hv");
        fill_cal_mat(cal_text[0], year, month, direction, day);

        cout << month_name[month] << ' ' << year << endl;
        print_cal(cal_text[0]);
    }
    else if(month == -1 || month == -3){//bonus: print whole year or 3 month
        day = 's';//force set day start on sunday and horizontal direction
        direction = 'h';
        if(month == -3){//3 month mode
            int center_month;
            _3month_reask:
            center_month = ask_range(dialogue[4], 1, 12) - 1;//convert user input month (1 for jan) into program month (0 for jan)
            if((center_month == 0 && year == 1800) || (center_month == 11 && year == 9999)){//in case of invalid input
                goto _3month_reask;
            }
            else{//valid input for 3 month mode
                fill_cal_mat_triple(cal_text, year, center_month, day, direction);
            }//finish filling in matrix
            for(int i = -1; i <= 1; i++){
                cout << month_name[mod(center_month+i,12)] << ' ' << (year-1 + (12+center_month+i)/12);
                for(int _ = 0; _ < 21+1-1-4-(strlen(month_name[mod(center_month+i,12)])); _++){
                    cout << ' ';//fill in space
                }
            }//finish printing month name
            cout << endl;
            print_cal_triple(cal_text);//finish printing the matrix
        }
        else{//print whole year mode
            cout << "Year " << year << endl;
            for(int i = 1; i <=10; i += 3){
                fill_cal_mat_triple(cal_text, year, i, day, direction);
                for(int j = -1; j <= 1; j++){// print the month name line
                    cout << month_name[i+j];
                    for(int _ = 0; _ < 21+1-(strlen(month_name[i+j])); _++){
                        cout << ' ';
                    }
                }
                cout << endl;
                print_cal_triple(cal_text);
            }
        }
    }
    return 0;
}