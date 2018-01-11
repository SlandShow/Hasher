//
// Created by slandshow on 11.01.18.
//

#include <iostream>
using namespace std;

namespace hash {

    class Hash {

        string hash;

        int receivingExistCodes(int x);

        int getControlSum(string str);

    public:
        string getHash(string userStr, unsigned int cashLenght);
    };


    // Приводим код к существуещему ANSI
    int Hash::receivingExistCodes(int x) {
        x += 256;
        while (!(((x <= 57) && (x >= 48)) || ((x <= 90) && (x >= 65)) || ((x <= 122) && (x >= 97)))) {
            if (x < 48)
                x += 24;
            else x -= 47;
        }
        return x;
    }

    // Взятие контрольной суммы
    int Hash::getControlSum(string str) {
        unsigned int sault = 0, strlen = 0;
        for (; strlen < str.size(); strlen++) {
            sault += int(str[strlen]);
        }
        return sault;
    }

    string Hash::getHash(string userStr, unsigned int hashLenght) {
        if (hashLenght > 3) {
            // Минимальная длина строки хеша, кратная двум
            unsigned int minLen = 2;
            // Длина строки, близкая к нужной длине хеша
            unsigned int realMinLen = 0;

            // Соль оригинальной строки
            unsigned int originalSault = this->getControlSum(userStr);
            unsigned int originalLenghtStr = (userStr.size());

            while (minLen <= hashLenght)
                realMinLen = (minLen *= 2);

            while (minLen < originalLenghtStr)
                minLen *= 2;

            if ((minLen - originalLenghtStr) < minLen)
                minLen *= 2;

            int addCount = minLen - originalLenghtStr;

            // Добавление
            for (int i = 0; i < addCount; i++) {
                userStr += this->receivingExistCodes(userStr[i] + userStr[i + 1]);
            }

            // Получаем максимальную соль
            int maxSault = this->getControlSum(userStr);
            int maxLenghtStr = userStr.size();

            while (userStr.size() != realMinLen) {
                for (int i = 0, center = userStr.size() / 2; i < center; i++) {
                    this->hash += this->receivingExistCodes(userStr[center - i] + userStr[i + center]);
                    userStr = this->hash;
                    this->hash.clear();
                }
                // Приведение к нужной длине
                unsigned int rem = realMinLen - hashLenght;

                for (unsigned int i = 0, countCompress = realMinLen / rem; this->hash.size() < (hashLenght - 4); i++) {
                    if (i % countCompress == 0)
                        this->hash += this->receivingExistCodes(userStr[i] + userStr[++i]);
                    else
                        this->hash += userStr[i];
                }

                this->hash += this->receivingExistCodes(originalSault);
                this->hash += this->receivingExistCodes(originalLenghtStr);

                this->hash += this->receivingExistCodes(maxSault);
                this->hash += this->receivingExistCodes(maxLenghtStr);
            }
            return "";
        }
    }

}

#endif //HASHER_HASH_H
