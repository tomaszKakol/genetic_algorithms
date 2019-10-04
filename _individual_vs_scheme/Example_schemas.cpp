#include <iostream>

//przyk³¹d schematów dla 1 osobnika
const int N = 6;
int tab[N] = {1, 0, 0, 0, 0, 1};

void population_create(int arr[]);
void schemas_all(int arr[], int * ptr[], int ile_whilow, int ile_pointerow);

void population_create(int arr[])
{
    for (int j = 0; j < N; ++j) {
        arr[j] = tab[j];
    }
}

int main()
{
    for (int i = 0; i < N; ++i) std::cout << tab[i] << " ";
    std::cout << std::endl;
    int t[N];
    for (int i = 1; i < N+1; ++i)
    {
        population_create(t);
        int ** ptr = new int * [i]; //wskaŸniki na stosie

        std::cout << "-add star-" << std::endl;
        for (int j = 0; j < i; ++j){
             ptr[j] = &t[j];
        }

        schemas_all(t, ptr, i, i);
        delete [] ptr;
    }

    return 0;
}

void schemas_all(int arr[], int * ptr[], int all_while_loop, int all_pointers)
{
    if (all_while_loop <= 0) {
        for (int j = 0; j < all_pointers; ++j) {
            *ptr[j] = 2;
        }
        for (int j = 0; j < N; ++j) {
            std::cout << arr[j] << " ";
        }
        std::cout << std::endl;
        population_create(arr);
        return;
    }

    while (ptr[all_pointers - all_while_loop] != &arr[N - all_while_loop + 1])
    {
        schemas_all(arr, ptr, all_while_loop - 1, all_pointers);

        int count = 1;
        for (int i = all_pointers - all_while_loop; i < all_pointers; ++i){
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
