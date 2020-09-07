#include "random.hpp"
#include <iostream>
#include <unistd.h>
#include <assert.h>

// pulled directly from StackOverflow for use with randomization on calls that occur multiple times per second
unsigned int mix(unsigned long a, unsigned long b, unsigned long c){
    a=a-b;  a=a-c;  a=a^(c >> 13);
    b=b-c;  b=b-a;  b=b^(a << 8);
    c=c-a;  c=c-b;  c=c^(b >> 13);
    a=a-b;  a=a-c;  a=a^(c >> 12);
    b=b-c;  b=b-a;  b=b^(a << 16);
    c=c-a;  c=c-b;  c=c^(b >> 5);
    a=a-b;  a=a-c;  a=a^(c >> 3);
    b=b-c;  b=b-a;  b=b^(a << 10);
    c=c-a;  c=c-b;  c=c^(b >> 15);
    return (int)c;
}

int intRandom(int low, int high){
    // StackOverflow code
    unsigned int seed = mix(clock(), time(NULL), getpid());
    srand(seed);
//    std::cout<<seed;
    
    if(low>=high){
        return low;
    } else {
        int r3 = low + static_cast <int> (rand()) /( static_cast <int> (RAND_MAX/(high-low)));
        return r3;
    }
}

float floatRandom(float low, float high){
    // StackOverflow code
    unsigned int seed = mix(clock(), time(NULL), getpid());
    srand(seed);
//    std::cout<<seed;
    if(low>=high){
        return low;
    } else {
        float r3 = low + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(high-low)));
        return r3;
    }
}
