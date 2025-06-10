//taliyarial1@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
#include <string>
#include "MyContainer.hpp"
#include "doctest.h"
#include <sstream>

using namespace con;

TEST_CASE("MyContainer: constractor") {
    MyContainer<double> m;
    CHECK(m.size() == 0);
    CHECK_THROWS_AS_MESSAGE(m.get(2) ,std::invalid_argument, "index is not in container range");
    MyContainer<> mc;
    int a = 4;
    mc.add(a);
    CHECK(mc.get(0) == 4);
}

TEST_CASE("MyContainer: add") {
    MyContainer<double> m;
    double a = 5;
    m.add(a);
    CHECK(m.size() == 1);
    CHECK(m.get(0) == 5);
}

TEST_CASE("MyContainer: remove"){
    MyContainer<double> m;
    double a = 5;
    double b = 2.4;
    double c = 3.7;
    double d = 5;
    double e = 20;
    m.add(a);
    m.add(b);
    m.add(c);
    m.add(d);
    CHECK(m.size() == 4);
    m.remove(b);
    CHECK(m.size() == 3);
    CHECK(m.get(1) == 3.7);
    CHECK_THROWS_AS_MESSAGE(m.get(3) ,std::invalid_argument, "index is not in container range");
    CHECK_THROWS_AS_MESSAGE(m.remove(e) ,std::invalid_argument, "Container don't contain 20");
    m.remove(d);
    CHECK(m.size() == 1);
    CHECK(m.get(0) == 3.7);
}

TEST_CASE("MyContainer: get"){
    MyContainer<double> m;
    double a = 5;
    double b = 2.4;
    m.add(a);
    m.add(b);
    CHECK_THROWS_AS_MESSAGE(m.get(3) ,std::invalid_argument, "index is not in container range");
    CHECK_THROWS_AS_MESSAGE(m.get(-1) ,std::invalid_argument, "index is not in container range");
}

TEST_CASE("MyContainer: increasCapacity"){
    //Capacity is 5 objects
    MyContainer<double> m;
    double a = 5;
    double b = 2.4;
    double c = 3.7;
    double d = 5;
    double e = 20;
    double f = 35.2;
    m.add(a);
    m.add(b);
    m.add(c);
    m.add(d);
    CHECK(m.getCapacity() == 10);
    m.add(e);
    m.add(f);
    m.add(a);
    m.add(e);
    //capacity grew up
    CHECK(m.get(5) == 35.2);
    CHECK(m.getCapacity() == 20);

}

TEST_CASE("MyContainer: decreasCapacity"){
    //Capacity is 5 objects
    MyContainer<double> m;
    double a = 5;
    double b = 9.2;
    double c = 3.7;
    m.add(a);
    m.add(b);
    m.add(a);
    m.add(c);
    //capacity grew up
    CHECK(m.getCapacity() == 10);
    m.remove(a);
    CHECK(m.getCapacity() == 5);
}

TEST_CASE("MyContainer: operator<<"){
    MyContainer<std::string> m;
    std::string a = "a";
    std::string b = "b";
    std::string c = "c";
    m.add(a);
    m.add(b);
    m.add(a);
    m.add(c);
    std::string res = "MyContainer:\na b a c ";
    std::ostringstream start;
    start << m;
    std::string output = start.str();
    CHECK_EQ(res, output);
    MyContainer<double> m1;
    double a1 = 2.2;
    double b1 = 40.3;
    double c1 = 0.89;
    m1.add(a1);
    m1.add(b1);
    m1.add(a1);
    m1.add(c1);
    std::string res1 = "MyContainer:\n2.200 40.300 2.200 0.890 ";
    std::ostringstream start1;
    start1 << m1;
    std::string output1 = start1.str();
    CHECK_EQ(res1, output1);
}

TEST_CASE("MyContainer: copyNewData") {
    MyContainer<double> m;
    double a = 5;
    double b = 8.8;
    double c = -70.64;
    m.add(a);
    m.add(b);
    m.add(b);
    m.add(c);
    CHECK(m.size() == 4);
    CHECK(m.get(3) == -70.64);
    m.remove(b);
    CHECK(m.size() == 2);
    CHECK(m.get(1) == -70.64);
}

TEST_CASE("Iterator: Order"){
    MyContainer<> m;
    int a = 5;
    int b = 98;
    int c = 168;
    m.add(a);
    m.add(b);
    m.add(c);
    m.add(a);
    std::string res = "5 98 168 5 ";
    std::ostringstream start;
    for(auto it = m.begin_order(); it != m.end_order(); ++it){
        start << *it << " ";
    }
    std::string output = start.str();
    CHECK_EQ(output, res);
}

TEST_CASE("Iterator: Order"){
    MyContainer<std::string> m1;
    std::string d = "d_letter";
    std::string e = "e_letter";
    std::string f = "f_letter";
    std::string g = "g_letter";
    m1.add(d);
    m1.add(e);
    m1.add(f);
    m1.add(g);
    m1.add(f);
    std::string res1 = "d_letter e_letter f_letter g_letter f_letter ";
    std::ostringstream start1;
    for(auto it = m1.begin_order(); it != m1.end_order(); ++it){
        start1 << *it << " ";
    }
    std::string output1 = start1.str();
    CHECK_EQ(output1, res1);
}

TEST_CASE("Iterator: ReverseOrder"){
    MyContainer<double> m;
    double a = -5.001;
    double b = 98.65;
    double c = 168.2;
    m.add(a);
    m.add(b);
    m.add(c);
    m.add(a);
    std::string res = "-5.001 168.2 98.65 -5.001 ";
    std::ostringstream start;
    for(auto it = m.begin_reverse_order(); it != m.end_reverse_order(); ++it){
        start << *it << " ";
    }
    std::string output = start.str();
    CHECK_EQ(output, res);
}

TEST_CASE("Iterator: ReverseOrder"){
    MyContainer<std::string> m1;
    std::string d = "d_letter";
    std::string e = "e_letter";
    std::string f = " ";
    std::string g = "g_letter";
    m1.add(d);
    m1.add(e);
    m1.add(f);
    m1.add(g);
    m1.add(e);
    std::string res1 = "e_letter g_letter   e_letter d_letter ";
    std::ostringstream start1;
    for(auto it = m1.begin_reverse_order(); it != m1.end_reverse_order(); ++it){
        start1 << *it << " ";
    }
    std::string output1 = start1.str();
    CHECK_EQ(output1, res1);
}

TEST_CASE("Iterator: AscendingOrder"){
    MyContainer<double> m;
    double a5 = -5.001;
    double a2 = -2.9;
    double b = 98.65;
    double c = 168.2;
    double z = 0;
    m.add(a5);
    m.add(b);
    m.add(c);
    m.add(b);
    m.add(a2);
    m.add(z);
    std::string res = "-5.001 -2.9 0 98.65 98.65 168.2 ";
    std::ostringstream start;
    for(auto it = m.begin_ascending_order(); it != m.end_ascending_order(); ++it){
        start << *it << " ";
    }
    std::string output = start.str();
    CHECK_EQ(output, res);
}

TEST_CASE("Iterator: AscendingOrder"){
    MyContainer<std::string> m1;
    std::string d = "d_letter";
    std::string e = "e_letter";
    std::string f = " ";
    std::string g = "g_letter";
    std::string h = "g_lethhh";
    m1.add(d);
    m1.add(e);
    m1.add(f);
    m1.add(g);
    m1.add(e);
    m1.add(h);
    std::string res1 = "  d_letter e_letter e_letter g_lethhh g_letter ";
    std::ostringstream start1;
    for(auto it = m1.begin_ascending_order(); it != m1.end_ascending_order(); ++it){
        start1 << *it << " ";
    }
    std::string output1 = start1.str();
    CHECK_EQ(output1, res1);
}

TEST_CASE("Iterator: DescendingOrder"){
    MyContainer<double> m;
    double a5 = -5.001;
    double a2 = -2.9;
    double b = 98.65;
    double c = 168.2;
    double z = 0;
    m.add(a5);
    m.add(b);
    m.add(c);
    m.add(b);
    m.add(a2);
    m.add(z);
    std::string res = "168.2 98.65 98.65 0 -2.9 -5.001 ";
    std::ostringstream start;
    for(auto it = m.begin_descending_order(); it != m.end_descending_order(); ++it){
        start << *it << " ";
    }
    std::string output = start.str();
    CHECK_EQ(output, res);
}

TEST_CASE("Iterator: DescendingOrder"){
    MyContainer<std::string> m1;
    std::string d = "d_letter";
    std::string e = "e_letter";
    std::string f = " ";
    std::string g = "g_letter";
    std::string h = "g_lethhh";
    m1.add(d);
    m1.add(e);
    m1.add(f);
    m1.add(g);
    m1.add(e);
    m1.add(h);
    std::string res1 = "g_letter g_lethhh e_letter e_letter d_letter   ";
    std::ostringstream start1;
    for(auto it = m1.begin_descending_order(); it != m1.end_descending_order(); ++it){
        start1 << *it << " ";
    }
    std::string output1 = start1.str();
    CHECK_EQ(output1, res1);
}

TEST_CASE("Iterator: SideCrossOrder"){
    MyContainer<double> m;
    double a5 = -5.001;
    double a2 = -2.9;
    double b = 98.65;
    double c = 168.2;
    double z = 0;
    m.add(a5);
    m.add(b);
    m.add(c);
    m.add(b);
    m.add(a2);
    m.add(z);
    std::string res = "-5.001 168.2 -2.9 98.65 0 98.65 ";
    std::ostringstream start;
    for(auto it = m.begin_side_cross_order(); it != m.end_side_cross_order(); ++it){
        start << *it << " ";
    }
    std::string output = start.str();
    CHECK_EQ(output, res);
}

TEST_CASE("Iterator: SideCrossOrder"){
    MyContainer<std::string> m1;
    std::string d = "d_letter";
    std::string e = "e_letter";
    std::string f = " ";
    std::string g = "g_letter";
    std::string h = "g_lethhh";
    m1.add(d);
    m1.add(e);
    m1.add(f);
    m1.add(g);
    m1.add(e);
    m1.add(h);
    m1.add(e);
    std::string res1 = "  g_letter d_letter g_lethhh e_letter e_letter e_letter ";
    std::ostringstream start1;
    for(auto it = m1.begin_side_cross_order(); it != m1.end_side_cross_order(); ++it){
        start1 << *it << " ";
    }
    std::string output1 = start1.str();
    CHECK_EQ(output1, res1);
}

TEST_CASE("Iterator: MiddleOutOrder"){
    MyContainer<double> m;
    double a5 = -5.001;
    double a2 = -2.9;
    double b = 98.65;
    double c = 168.2;
    double z = 0;
    m.add(a5);
    m.add(b);
    m.add(c);
    m.add(b);
    m.add(a2);
    m.add(z);
    //odd number of objects
    std::string res = "98.65 168.2 -2.9 98.65 0 -5.001 ";
    std::ostringstream start;
    for(auto it = m.begin_middle_out_order(); it != m.end_middle_out_order(); ++it){
        start << *it << " ";
    }
    std::string output = start.str();
    CHECK_EQ(output, res);
}

TEST_CASE("Iterator: MiddleOutOrder"){
    MyContainer<std::string> m1;
    std::string d = "d_letter";
    std::string e = "e_letter";
    std::string f = " ";
    std::string g = "g_letter";
    std::string h = "g_lethhh";
    m1.add(d);
    m1.add(e);
    m1.add(f);
    m1.add(g);
    m1.add(e);
    m1.add(h);
    m1.add(e);
    //even number of objects
    std::string res1 = "g_letter   e_letter e_letter g_lethhh d_letter e_letter ";
    std::ostringstream start1;
    for(auto it = m1.begin_middle_out_order(); it != m1.end_middle_out_order(); ++it){
        start1 << *it << " ";
    }
    std::string output1 = start1.str();
    CHECK_EQ(output1, res1);
}