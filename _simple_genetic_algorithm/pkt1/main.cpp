#include <iostream>
#include <string>

using namespace std;

int validator(string * s);
int count_tier(string * s);
int count_range(string * s);
int count_size(string * s);
double count_mutation(string * s);
double count_crossing(string * s);

int main(){

    cout << "Info: Press 'p' to exit." << endl;
    cout << endl;

    while(true){
        string schema;
        cout << "A new scheme: ";
        cin >> schema;

        if ("p" == schema){ //zamkniêcie
            return 0;
        }
        if (!validator(&schema)){
            continue;
        }


        //wyswietlenie rezultatow
        cout << "\tSchema: "<< schema << endl;
        cout << "\tTier:" << count_tier(&schema) << endl;
        cout << "\tRange: " << count_range(&schema) << endl;
        cout << "\tSize: " << count_size(&schema) << endl;
        cout.precision(3);
        cout << "\tThe probability of surviving the mutation: " <<count_mutation(&schema) << endl;
        cout << "\tThe probability of surviving the crossing: " << count_crossing(&schema) << endl;
        cout << endl;


    }
    return 0;
}

//zliczenie rozmiaru schematu
int count_size(string * s){
    return count_range(s) + 1;
}

 //zliczenie rzêdu schematu
int count_tier(string * s){
    int tier = 0;
    for (string::iterator it = s->begin(); it != s->end(); ++it){
        if ((*it == '1') || (*it == '0')){
            tier++;
        }
    }
    return tier;
}

//zliczenie rozpietosci schematu
int count_range(string * s)
{
    string::iterator left_edge  = s->begin();
    string::iterator right_edge = s->begin();
    int result = 0;
    for (string::iterator it = s->begin(); it != s->end(); ++it){
        if ((*it == '1') || (*it == '0')){
            if (!result){
                left_edge = it;
                right_edge = it;
                result++;
            }
            else{
                right_edge = it;
            }
        }
    }

    return right_edge - left_edge;
}

//wyznaczenie prawdopodobienstwa krzyzowania przez schemat
double count_crossing(std::string * s){
    return 1 - (double)count_range(s) / (s->length() - 1);
}

//wyznaczenie prawdopodobienstwa przezycia mutacji przez schemat
double count_mutation(string * s){
    double probability = 0.001;
    return 1 - probability * (double)count_tier(s);
}

//walidator znaków w schemacie
int validator(string * s){
    for (string::iterator it = s->begin(); it != s->end(); ++it){
        if ((*it != '1') && (*it != '0') && (*it != '*')){
            cout << "\tInvalid data! Use only: 0, 1, *" << endl;
            return 0;
        }
    }
    return 1;
}
