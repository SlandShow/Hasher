/*
 * Хэширование строк
 * Определённого размера
 *
 */


#include <iostream>
#include <string>
#include <vector>
#include "Hash.h"


using namespace std;


int main() {

    Hash hash;

    string str;
    int lenght;

    cin >> str;
    cin >> lenght;
    cout << hash.getHash(str, lenght);
    return 0;
}