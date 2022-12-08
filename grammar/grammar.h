//
// Created by Chuanchao Lyu on 2022/11/25.
//

#ifndef CPP17_GRAMMAR_H
#define CPP17_GRAMMAR_H
#include <functional>
//std::ref, std::cref
void fref(int&, int&, const int&);
void testref(const std::function<void(int&,int&,const int&)>&);

template<typename Container, typename index>
auto authAndAccess(Container&& c, index i)-> decltype(c[i]){
    //authenticateUser();
    return std::forward<Container>(c)[i];
}


#endif //CPP17_GRAMMAR_H
