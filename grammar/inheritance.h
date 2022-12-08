//
// Created by Chuanchao Lyu on 2022/11/24.
//

#ifndef CPP17_INHERITANCE_H
#define CPP17_INHERITANCE_H


#include <string>

class Base{
public:
    Base()=default;
    virtual ~Base()=0;
    virtual Base* clone() const = 0;
    std::string info() const{return imp_info();}
private:
    virtual std::string imp_info() const{return "In Base!";}
private:
    int m_b{0};
};

class Derive:public Base{
public:
    Derive()=default;
    virtual ~Derive();
    virtual Derive* clone() const override{
        return new Derive(*this);
    };
private:
    virtual std::string imp_info() const override {
        return "In Derive!";
    }
};

class Lifetime{
public:
    Lifetime() noexcept {
        puts("Lifetime() [default constructor]");
    }
    Lifetime(const Lifetime&) noexcept{
        puts("Lifetime(const Lifetime&) [copy constructor]");
    }
    Lifetime(const Lifetime&&) noexcept{
        puts("Lifetime(const Lifetime&&) [move constructor]");
    }
    Lifetime& operator=(const Lifetime&) noexcept{
        puts("operator=(const Lifetime&) [copy assignment]");
        return *this;
    }
    Lifetime& operator=(const Lifetime&&) noexcept{
        puts("operator=(const Lifetime&&) [move assignment]");
        return *this;
    }
    ~Lifetime() noexcept{
        puts("~Lifetime() [destructor]");
    }
};




#endif //CPP17_INHERITANCE_H
