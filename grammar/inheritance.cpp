//
// Created by Chuanchao Lyu on 2022/11/24.
//

#include "inheritance.h"
#include <cstdio>

Base::~Base() {
    puts("Pure Base virtual desturctor is called!");
}

Derive::~Derive(){
    puts("Derive desturctor is called!");
}