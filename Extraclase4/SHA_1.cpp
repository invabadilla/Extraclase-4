//
// Created by Usuario on 8/6/2021.
//


#include "SHA_1.h"

/**
 * Convertir una cadena binaria de cuatro dígitos en un carácter hexadecimal
 * @param a Primer digito
 * @param b Segundo digito
 * @param c Tercer digito
 * @param d Cuarto digito
 * @return
 */
char SHA_1::binToHex(int a, int b, int c, int d){
    if(a == 0 && b  == 0 && c == 0 && d == 0)
        return '0';
    else if(a == 0 && b  == 0 && c == 0 && d == 1)
        return '1';
    else if(a == 0 && b  == 0 && c == 1 && d == 0)
        return '2';
    else if(a == 0 && b  == 0 && c == 1 && d == 1)
        return '3';
    else if(a == 0 && b  == 1 && c == 0 && d == 0)
        return '4';
    else if(a == 0 && b  == 1 && c == 0 && d == 1)
        return '5';
    else if(a == 0 && b  == 1 && c == 1 && d == 0)
        return '6';
    else if(a == 0 && b  == 1 && c == 1 && d == 1)
        return '7';
    else if(a == 1 && b  == 0 && c == 0 && d == 0)
        return '8';
    else if(a == 1 && b  == 0 && c == 0 && d == 1)
        return '9';
    else if(a == 1 && b  == 0 && c == 1 && d == 0)
        return 'A';
    else if(a == 1 && b  == 0 && c == 1 && d == 1)
        return 'B';
    else if(a == 1 && b  == 1 && c == 0 && d == 0)
        return 'C';
    else if(a == 1 && b  == 1 && c == 0 && d == 1)
        return 'D';
    else if(a == 1 && b  == 1 && c == 1 && d == 0)
        return 'E';
    else if(a == 1 && b  == 1 && c == 1 && d == 1)
        return 'F';
}

/**
 * Convierte un entero a la longitud de la forma vectorial hexadecimal
 * @param a entero
 * @param sys forma vectorial
 * @param length largo
 * @return
 */
vector<int> SHA_1::intToSys(const unsigned long long &a, int sys, int length){
    vector<int> result;
    stack<int> tmp;
    unsigned long long a1 = a;
    do{
        int temp = a1 % sys;
        tmp.push(temp);
        a1 /= sys;
    }while(a1 != 0);

    for(int i = 0; i < length - tmp.size(); i++)    //Fill 0
        result.push_back(0);

    while(!tmp.empty()){
        result.push_back(tmp.top());
        tmp.pop();
    }

    return result;
}

/**
 * Convierte cadena de símbolo hexadecimal (palabra) a cadena entera hexadecimal
 * @param word
 * @return
 */
vector<int> SHA_1::charToHex(const string &word){
    vector<int> result(NUM, 0);
    for(int i = 0; i < NUM; i++){
        if(word[i] >= '0' && word[i] <= '9')
            result[i] = word[i] - '0';
        else if(word[i] >= 'A' && word[i] <= 'Z')
            result[i] = 10 + word[i] - 'A';
    }
    return result;
}

/**
 * Cadena entera hexadecimal a char de símbolo hexadecimal
 * @param a
 * @return
 */
string SHA_1::hexToChar(const vector<int> &a){
    string result;
    for(int i = 0; i < NUM; i++){
        if(a[i] >= 0 && a[i] <= 9)
            result += a[i] + '0';
        else if(a[i] >= 10 && a[i] <= 15)
            result += a[i] - 10 + 'A';
    }
    return result;
}

/**
 * Char a cadena binaria de 8 bits
 * @param a
 * @return
 */
string SHA_1::charToBinary(const char a){
    int a_int;
    if(a >= '0' && a <= '9')
        a_int = a - '0' + 48;
    else if(a >= 'A' && a <= 'Z')
        a_int = a - 'A' + 65;
    else if(a >= 'a' && a <= 'z')
        a_int = a - 'a' + 97;

    vector<int> temp = intToSys(a_int, 2, 8);
    string result;
    for(int i = 0; i < temp.size(); i++)
        result += temp[i] + '0';

    return result;
}

//Funciones aritmeticas
string SHA_1::wAnd(const string &a, const string &b) {
    vector<int> a_int = charToHex(a);
    vector<int> b_int = charToHex(b);
    vector<int> r_int(NUM, 0);

    for(int i = 0; i < NUM; i++)
        r_int[i] = a_int[i] & b_int[i];

    return hexToChar(r_int);
}

string SHA_1::wOr(const string &a, const string &b){
    vector<int> a_int = charToHex(a);
    vector<int> b_int = charToHex(b);
    vector<int> r_int(NUM, 0);

    for(int i = 0; i < NUM; i++)
        r_int[i] = a_int[i] | b_int[i];

    return hexToChar(r_int);
}

string SHA_1::wXoR(const string &a, const string &b){
    vector<int> a_int = charToHex(a);
    vector<int> b_int = charToHex(b);
    vector<int> r_int(NUM, 0);

    for(int i = 0; i < NUM; i++)
        r_int[i] = a_int[i] ^ b_int[i];

    return hexToChar(r_int);
}

string SHA_1::wCpl(const string &a){
    vector<int> a_int = charToHex(a);
    vector<int> r_int(NUM, 0);

    for(int i = 0; i < NUM; i++)
        r_int[i] = HEX - 1 - a_int[i];

    return hexToChar(r_int);
}

string SHA_1::wAdd(const string &a, const string &b){
    vector<int> A = charToHex(a);
    vector<int> B = charToHex(b);
    vector<int> Result(NUM, 0);

    int sign = 0;
    for(int i = NUM - 1; i >= 0; i--){
        Result[i] = A[i] + B[i] + sign;
        sign = Result[i] / HEX;
        Result[i] %= HEX;
    }
    return hexToChar(Result);
}

string SHA_1::ROTL(const string &a, int s){
    vector<int> A = charToHex(a);
    unsigned long a_int = 0;    //valor numerico de la palabra

    for(int i = 0; i < NUM; i++)
        a_int += A[NUM - 1 - i] * pow(HEX, i);

    a_int = (a_int >> (NUM * 4 - s)) | (a_int << s);

    vector<int> A1 = intToSys(a_int, HEX, NUM);
    return hexToChar(A1);
}

string SHA_1::Ft(int t, const string &B, const string &C, const string &D){
    if(t >= 0 && t <= 19)
        return wOr(wAnd(B, C), wAnd(wCpl(B), D));
    else if(t >= 20 && t <= 39)
        return wXoR(wXoR(B, C), D);
    else if(t >= 40 && t <= 59)
        return wOr(wOr(wAnd(B, C), wAnd(B, D)), wAnd(C, D));
    else if(t >= 60 && t <= 79)
        return wXoR(wXoR(B, C), D);
}

string SHA_1::K(int t){
    if(t >= 0 && t <= 19)
        return "5A827999";
    else if(t >= 20 && t <= 39)
        return "6ED9EBA1";
    else if(t >= 40 && t <= 59)
        return "8F1BBCDC";
    else if(t >= 60 && t <= 79)
        return "CA62C1D6";
}

/**
 * Se llena el mensaje con el string
 * @param b_msg
 * @return
 */
vector<vector<int> > SHA_1::sha1Pad(const string &b_msg){
    unsigned long long length = b_msg.size();
    int d = (447 - length) % BIT;
    // Representación binaria de la longitud de la información, y la longitud de esta representación binaria es 64
    vector<int> l = intToSys(length, 2, 64);

    vector<vector<int> > result;
    string str_result;
    str_result += b_msg;
    str_result += '1';
    for(int i = 0; i < d; i++)
        str_result += '0';
    for(int i = 0; i < l.size(); i++)
        str_result += '0' + l[i];

    // El mensaje completo tiene n conjuntos de datos BIT
    int n = str_result.size() / BIT;
    result.resize(n, vector<int>(BIT, 0));

    for(int i = 0; i < n; i++)
        for(int j = 0; j < BIT; j++)
            result[i][j] = str_result[i * BIT + j] - '0';

    return result;
}

/**
 * Funcion para dividir el mensaje completo en una serie de palabras (ocho números hexadecimales) como la unidad
 * @param result
 * @return
 */
vector<vector<string> > SHA_1::divide(const vector<vector<int> > &result){
    vector<vector<string> > w_result(result.size(), vector<string>(HEX, ""));
    for(int i = 0; i < result.size(); i++)
        // Para cada cadena, se obtiene una cadena de notación hexadecimal de ocho dígitos a partir del número binario de 32 bits del resultado.
        for(int j = 0; j < HEX; j++){
            w_result[i][j] += binToHex(result[i][j * 32], result[i][j * 32 + 1], result[i][j * 32 + 2],
                                       result[i][j * 32 + 3]);
            w_result[i][j] += binToHex(result[i][j * 32 + 4], result[i][j * 32 + 5], result[i][j * 32 + 6],
                                       result[i][j * 32 + 7]);
            w_result[i][j] += binToHex(result[i][j * 32 + 8], result[i][j * 32 + 9], result[i][j * 32 + 10],
                                       result[i][j * 32 + 11]);
            w_result[i][j] += binToHex(result[i][j * 32 + 12], result[i][j * 32 + 13], result[i][j * 32 + 14],
                                       result[i][j * 32 + 15]);
            w_result[i][j] += binToHex(result[i][j * 32 + 16], result[i][j * 32 + 17], result[i][j * 32 + 18],
                                       result[i][j * 32 + 19]);
            w_result[i][j] += binToHex(result[i][j * 32 + 20], result[i][j * 32 + 21], result[i][j * 32 + 22],
                                       result[i][j * 32 + 23]);
            w_result[i][j] += binToHex(result[i][j * 32 + 24], result[i][j * 32 + 25], result[i][j * 32 + 26],
                                       result[i][j * 32 + 27]);
            w_result[i][j] += binToHex(result[i][j * 32 + 28], result[i][j * 32 + 29], result[i][j * 32 + 30],
                                       result[i][j * 32 + 31]);
        }
    return w_result;
}

/**
 * Método para implementar la encriptacion
 * @param msg mensaje a cifrar
 * @return
 */
string SHA_1::resultSha1(const string &msg) {
    string b_msg;
    for (int i = 0; i < msg.size(); i++)
        b_msg += charToBinary(msg[i]);

    vector<vector<int> > y = sha1Pad(b_msg);
    vector<vector<string> > w_y = divide(y);

    vector<string> W(80, "");
    for (int i = 0; i < y.size(); i++) {

        for (int t = 0; t <= 15; t++)
            W[t] = w_y[i][t];

        for (int t = 16; t <= 79; t++) {
            string tmp = wXoR(wXoR(wXoR(W[t - 3], W[t - 8]), W[t - 14]), W[t - 16]);
            W[t] = ROTL(tmp, 1);
        }

        string A = H0;
        string B = H1;
        string C = H2;
        string D = H3;
        string E = H4;

        for (int t = 0; t <= 79; t++) {
            string temp;
            temp = wAdd(wAdd(wAdd(wAdd(ROTL(A, 5), Ft(t, B, C, D)), E), W[t]), K(t));
            E = D;
            D = C;
            C = ROTL(B, 30);
            B = A;
            A = temp;
        }
        H0 = wAdd(H0, A);
        H1 = wAdd(H1, B);
        H2 = wAdd(H2, C);
        H3 = wAdd(H3, D);
        H4 = wAdd(H4, E);
    }

    string result = H0 + H1 + H2 + H3 + H4;

    // Las mayúsculas se vuelven minúsculas
    for (int i = 0; i < result.size(); i++) {
        if (result[i] >= 'A' && result[i] <= 'Z')
            result[i] = result[i] - 'A' + 'a';
    }
    return result;
}
