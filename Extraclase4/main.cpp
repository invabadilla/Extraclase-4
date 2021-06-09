#include <iostream>
#include <string>
#include "SHA_1.h"
#include "MD5.h"

using namespace std;

int main(){
    SHA_1 sha_1;
    string msg = "Hola Mundo";

    cout << "Mensaje del transmisor: " << msg << endl <<endl;
    string encript = sha_1.resultSha1(msg);
    cout << "El mensaje del receptor con Sha1 es: " << encript << endl;

    auto hash = ConstexprHashes::md5("Hola Mundo");
    cout << "El mensaje del receptor con MD5 es: ";
    cout << hex;
    for (auto i : hash) {
        cout << (static_cast<int>(i) & 0xff);
    }
    cout << endl;

    return 0;
}
