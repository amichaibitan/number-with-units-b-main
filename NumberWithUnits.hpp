#pragma once

#include <string>
#include <iostream>
#include <stdexcept>
#include <map>
#include <fstream>
#include <sstream>
using namespace std;
//using namespace ariel;

namespace ariel{
    class NumberWithUnits
    {
        //    string s;
        //    double d;
        public:
           string s;
           double d;
           static std::map<string, std::map< string , double >>  map_unit; 
           void static  son_map(const string& s1, const string& s2);


            NumberWithUnits (double dou , string str);
            NumberWithUnits();

            static void read_units(std::ifstream& );
            friend NumberWithUnits operator+(const NumberWithUnits& num, const NumberWithUnits& num1);
            NumberWithUnits &operator+=(const NumberWithUnits& num);
            NumberWithUnits operator+();
            friend NumberWithUnits operator-(const NumberWithUnits& num, const NumberWithUnits& num1);
            NumberWithUnits &operator-=(const NumberWithUnits& num);
             NumberWithUnits operator-();
            bool operator<(const NumberWithUnits& num )const;
            bool operator<=(const NumberWithUnits& num)const;
            bool operator>(const NumberWithUnits& num)const;
            bool operator>=(const NumberWithUnits& num )const;
            bool operator!=(const NumberWithUnits& num )const;
            bool operator==(const NumberWithUnits& num )const;
            NumberWithUnits &operator++();
            NumberWithUnits &operator--();
            NumberWithUnits operator++( int x);
            NumberWithUnits operator--( int x);
            friend NumberWithUnits operator*(const double x, const NumberWithUnits &n);
            friend NumberWithUnits operator*(const NumberWithUnits &n, const double x);
            friend istream& operator>>(istream& is, NumberWithUnits& num);
            friend ostream& operator<<(ostream& os,const NumberWithUnits& num);
    };
}