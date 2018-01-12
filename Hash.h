#include <iostream>
using namespace std;


class Hash {

    string hash;

    int receivingExistCodes(int x);

    int getControlSum(string str);

    public:
        string getHash(string userStr, unsigned int cashLenght);
};

