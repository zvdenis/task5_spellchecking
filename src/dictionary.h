#ifndef  _DICTIONARY_H_ 
#define  _DICTIONARY_H_

#include  <iostream>
#include  <vector>
#include  <list>
#include  <algorithm>
#include  <string>
#include  <stdlib.h>

#include  "hashset.h"
#include  "hashset.cpp"

using namespace std;

class hash_function
{
public:

    const int mod = 37;

    unsigned int operator()( const string& s )  const {
        int key = 0;
        int pow = 1;

        for(int i = 0; i < s.size();i++){
            key += (s[i] - 'a') * pow;
            pow *= mod;
        }

        return key;
        
    }
};

class equality
{
public:
    equality() {}
    bool  operator()( const string& A, const string& B )  const 
    {
        return  (A == B);
    }
};

class Dictionary: public HashSet<string, hash_function, equality> {



public:
	Dictionary(string filename);

};
#endif // _DICTIONARY_H_
