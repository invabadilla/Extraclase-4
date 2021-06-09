//
// Created by Usuario on 8/6/2021.
//

#ifndef EXTRACLASE4_SHA_1_H
#define EXTRACLASE4_SHA_1_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <stack>

#define NUM 8    //Una palabra equivale a 8 números hexadecimales
#define HEX 16   //Hexadecimal
#define BIT 512 //Código de autenticación de mensajes 512 bites group

using namespace std;

class SHA_1 {
public:

    char binToHex(int a, int b, int c, int d);
    vector<int> intToSys(const unsigned long long &a, int sys, int length);
    static vector<int> charToHex(const string &word);
    static string hexToChar(const vector<int> &a);
    string charToBinary(const char a);


    static string wAnd(const string &a, const string &b);
    static string wOr(const string &a, const string &b);
    static string wXoR(const string &a, const string &b);
    static string wCpl(const string &a);
    static string wAdd(const string &a, const string &b);
    string ROTL(const string &a, int s);
    static string Ft(int t, const string &B, const string &C, const string &D);
    static string K(int t);


    vector<vector<int> > sha1Pad(const string &b_msg);
    vector<vector<string> > divide(const vector<vector<int> > &result);
    string resultSha1(const string &msg);

private:
    string H0 = "67452301";
    string H1 = "EFCDAB89";
    string H2 = "98BADCFE";
    string H3 = "10325476";
    string H4 = "C3D2E1F0";

};

#endif //EXTRACLASE4_SHA_1_H
