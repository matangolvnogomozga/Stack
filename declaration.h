#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<windows.h>
#include<cassert>
#include<math.h>

#include<functions.h>

long long RandomBig();
void SetColor(ConsoleColor text, ConsoleColor background);

const bool FAIL = false;
const bool SUCCESS = true;
const int LEN = 12;
const long long CANARYBEGIN1 = RandomBig();
const long long CANARYBEGIN2 = RandomBig();
