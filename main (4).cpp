//taliyarial1@gmail.com
#include <iostream>
#include "MyContainer.hpp"

using namespace con;

int main(){
    MyContainer<> m;
    int a = 7;
    int b = 15;
    int c = 6;
    int d = 1;
    int e = 2;
    m.add(a);
    m.add(b);  
    m.add(c);
    m.add(d);
    m.add(e);
    m.add(e);

    std::cout << "order:" << std::endl;
    for (auto it = m.begin_order(); it != m.end_order(); ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << "reverse_order:" << std::endl;
    for (auto it = m.begin_reverse_order(); it != m.end_reverse_order(); ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << "ascending_order:" << std::endl;
    for (auto it = m.begin_ascending_order(); it != m.end_ascending_order(); ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << "descending_order:" << std::endl;
    for (auto it = m.begin_descending_order(); it != m.end_descending_order(); ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << "side_cross_order:" << std::endl;
    for (auto it = m.begin_side_cross_order(); it != m.end_side_cross_order(); ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << "middle_out_order:" << std::endl;
    for (auto it = m.begin_middle_out_order(); it != m.end_middle_out_order(); ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << "operator<< :\n" << m << std::endl;

    m.remove(e);
    m.remove(b);
    std::cout << "remove '2' and '15':\n" << m << std::endl;
};