#pragma once
#include <stdio.h>
#include "shanle.h"
class test
{
private:
    /* data */
public:
    test(/* args */);
    ~test();
};

test::test(/* args */)
{
    printf("test---------\n");
}

test::~test()
{
}
