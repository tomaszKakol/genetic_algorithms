#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <time.h>
#include <math.h>

const int N = 6; // wielkość ciągu
const int population_size = 1000; // wielkość populacji
const int schema = pow(3, N); //3 do n
const int measurements = 125;//wyznaczona ilość pomiarów (wyznaczona z instrukcji)
int patterns[schema] = {0};

std::vector<std::array<int, N>> population;
std::vector<std::array<int, measurements>> schema_measurement;
int measurement_points[measurements] = {0};
int measurements_avg[measurements] = {0};

void schemas_all(int individual[], int * ptr[], int while_number, int pointer_number, int individual_number);
int schemas_count();
void population_create(int pop_number);
void population_create_copy(int individual[], int individual_number);
void patterns_clear();
void patterns_set(int individual[]);
void save();

int main()
{
    srand(time(NULL));

    int single[N];
    for (int i = 0; i < 10; ++i) // uśrenienia wyników z 10 prób
    {
        std::cout << "Measurement counter: " << i + 1 << std::endl;
        population_create(population_size);
        std::array<int, measurements> current_measurements;

        int measurement_counter = 0;
        for (int j = 0; j < population_size; ++j) // przejści po każdym osobniku
        {
            population_create_copy(single, j);
            patterns_set(single);

            for (int k = 1; k < N + 1; ++k) // tutaj jest tworzone wszystkie schematy z populacji
            {
                population_create_copy(single, j);

                int ** ptr = new int * [k];// wskaźniki na stosie
                for (int l = 0; l < k; ++l){
                    ptr[l] = &single[l];
                }

                schemas_all(single, ptr, k, k, j);
                delete [] ptr;
            }

            // przejście zgodne z instrukcją do ćwiczeń
            //n w zakresie od 1 do 100
            //W zakresie od 100 do 250 co 10
            //W zakresie od 300 do 500 co 50
            //W zakresie od 500 do 1000 co 100
            if (j == 0){
                current_measurements[measurement_counter] = pow(2, N); // 2 do n to wszystkie możliwości dla pojedynczego schematu
                measurement_points[measurement_counter] = j + 1;
                measurement_counter++;
            }
            else if ((j > 0) && (j < 100)){
                current_measurements[measurement_counter] = schemas_count();
                measurement_points[measurement_counter] = j + 1;
                measurement_counter++;
            }
            else if ((j > 100) && (j < 251)){
                    //sprawdzenie modulo
                if (((j + 1) % 10) == 0){
                    current_measurements[measurement_counter] = schemas_count();
                    measurement_points[measurement_counter] = j + 1;
                    measurement_counter++;
                }
            }
            else if ((j > 251) && (j < 501)){
                if (((j + 1) % 50) == 0){
                    current_measurements[measurement_counter] = schemas_count();
                    measurement_points[measurement_counter] = j + 1;
                    measurement_counter++;
                }
            }
            else {
                if (((j + 1) % 100) == 0){
                    current_measurements[measurement_counter] = schemas_count();
                    measurement_points[measurement_counter] = j + 1;
                    measurement_counter++;
                }
            }
        }

        schema_measurement.push_back(current_measurements);
        patterns_clear();
    }

    //zliczenie schematów
    for (int i = 0; i < 125; ++i){
        int sum = 0;
        for (int j = 0; j < 10; ++j){
            sum = sum + schema_measurement[j][i];
        }
        measurements_avg[i] = roundf((double)sum / 10.0);
    }
    save();

    return 0;
}

//tworzenie populacji
void population_create(int pop_number)
{
    for (int i = 0; i < pop_number; ++i){
        std::array<int, N> pop;
        for (int j = 0; j < N; ++j){
            pop[j] = rand() % 2;
        }
        population.push_back(pop);
    }
}

//wyznazenie wszystkich schmatów
void schemas_all(int individual[], int * ptr[], int while_number, int pointer_number, int individual_number)
{
    if (while_number <= 0) {
        for (int i = 0; i < pointer_number; ++i) {
            *ptr[i] = 2;
        }
        patterns_set(individual);
        population_create_copy(individual, individual_number);
        return;
    }

    while (ptr[pointer_number - while_number] != &individual[N - while_number + 1]){
        schemas_all(individual, ptr, while_number - 1, pointer_number, individual_number);

        int count = 1;
        for (int i = pointer_number - while_number; i < pointer_number; ++i){
            if (count == 1){
                ptr[i]++;
            }
            else{
                ptr[i] = ptr[i - 1] + 1;
            }
            count++;
        }
    }
}

//kopia do przechowania schematów podczas wyznacznia wszystkich schematów dla osobnika
void population_create_copy(int individual[], int individual_number)
{
    for (int i = 0; i < N; ++i) {
        individual[i] = population[individual_number][i];
    }
}

//wyczyszczenie naszego stosu 0-728
void patterns_clear()
{
    for (int i = 0; i < schema; ++i){
        patterns[i] = 0;
    }
}

//wyznaczenie schematu na naszym stosie 0-728 i ustawienie obecności schematu jako '1'
void patterns_set(int individual[])
{
    int schema = 0;
    for (int i = 0; i < N; ++i) {
        schema = schema + individual[i] * pow(3, N - i - 1);
    }
    patterns[schema] = 1;
}

//zapisanie wyników do pliku txt
void save()
{
    char filename[ ] = "data.txt";
    std::fstream file;

    file.open(filename, std::fstream::out | std::fstream::trunc);
    for (int i = 0; i < measurements; ++i){
        file << measurement_points[i] << " " << measurements_avg[i] << " \n";
    }
    file.close();
}

//ilość schematów na naszym stosie 0-728
int schemas_count()
{
    int count = 0;
    for (int i = 0; i < schema; ++i)
    {
        if (patterns[i] == 1){
            count++;
        }
    }

    return count;
}

