#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <stdbool.h>
#include <map>
#include <cfloat>
#include "NumberWithUnits.hpp"
using namespace std;
using namespace ariel;
 double EPS = 0.0001;

namespace ariel 
{
   
    std::map<string, std::map< string , double >> NumberWithUnits::map_unit; 
    //void NumberWithUnits::son_map(const string& s1, const string& s2);
   
    
    void NumberWithUnits::son_map(const string& s1, const string& s2)
    {
        for(pair<string,double> e: NumberWithUnits::map_unit[s1])
        {
            //if( NumberWithUnits::map_unit[e.first][s2] == 0)
            //{
            NumberWithUnits::map_unit[e.first][s2]= 1/ (NumberWithUnits::map_unit[s2][s1] * NumberWithUnits::map_unit[s1][e.first]);
           // }
            // if(NumberWithUnits::map_unit[s2][e.first] == 0)
            // {
            NumberWithUnits::map_unit[s2][e.first] = NumberWithUnits::map_unit[s2][s1] * NumberWithUnits::map_unit[s1][e.first] ;
            //}
        }
    }
    
    void NumberWithUnits::read_units(ifstream &units_file)
    {
        double num, num1;
        num=0,num1=0;
        string unit1, unit2, eq;
        while (units_file >> num >> unit1 >> eq >> num1 >> unit2) 
        {
            map_unit[unit1][unit1] = 1;
            map_unit[unit2][unit2] = 1;
            if(unit1 != unit2)
            {
                map_unit[unit1][unit2] = num1/num;
                map_unit[unit2][unit1] = num/num1;
                son_map(unit1,unit2);
                son_map(unit2,unit1);
            }
            
        }
        
        for(auto it = map_unit.cbegin(); it != map_unit.cend(); ++it)
            {
         for(auto is = it->second.cbegin(); is != it->second.cend(); ++is)
                {
                  std::cout << it->first << " " << is->first << " " << is->second << "\n";
                        }
             }

    };

    NumberWithUnits ver(const NumberWithUnits num, string str)
    {
        NumberWithUnits a;
        if(NumberWithUnits::map_unit[num.s][str] == 0)
        {
            throw "there is not that unit";
        }
        a.d = num.d * NumberWithUnits::map_unit[num.s][str];
        a.s =str;
        return a;
    }

    //empty
    NumberWithUnits::NumberWithUnits()
    {

    }

    NumberWithUnits::NumberWithUnits (double dou , string str)
    {
        // this->d=dou;
        // this->s=str;
        if(map_unit[str][str] != 0 )
        {
            this->d=dou;
           this->s=str;
        }
        else{
            throw "there is not that unit con";
        }
    }

     NumberWithUnits operator+(const NumberWithUnits& num,const NumberWithUnits& num1)
    {
        NumberWithUnits a=ver(num1,num.s);
        
        return NumberWithUnits(a.d+num.d,num.s);
    }

     NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits& num)
    {
        NumberWithUnits a=ver(num,this->s);
        this->d += a.d;
        return *this;
    }

     NumberWithUnits NumberWithUnits::operator+()//*1
    {
        
        return *this;
    }

     NumberWithUnits operator-(const NumberWithUnits& num,const NumberWithUnits& num1)
    {
        NumberWithUnits a=ver(num1,num.s);
        
        return NumberWithUnits(num.d-a.d,num.s);
    }

     NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits& num)
    {
        NumberWithUnits a=ver(num,this->s);
        this->d -= a.d;
        return *this;
    }

     NumberWithUnits NumberWithUnits::operator-()//*(-1)
    {
         return NumberWithUnits{-d, s};
    }
    
    bool NumberWithUnits::operator<(const NumberWithUnits& num)const
    {
        NumberWithUnits a=ver(num,this->s);
        if(this->d + EPS < a.d)
        {return true;}
        return false;
    }

    bool  NumberWithUnits::operator<=(const NumberWithUnits& num )const
    {
        return NumberWithUnits::operator<(num) || NumberWithUnits::operator==( num);
    }

    bool  NumberWithUnits::operator>(const NumberWithUnits& num)const
    {
    
      return  !NumberWithUnits::operator<( num) && !NumberWithUnits::operator==( num);
    }

    bool  NumberWithUnits::operator>=(const NumberWithUnits& num )const
    {
            return !NumberWithUnits::operator<(num) || NumberWithUnits::operator==( num);;
    }

    bool  NumberWithUnits::operator!=(const NumberWithUnits& num)const
    {
        return !NumberWithUnits::operator==(num);
    }

    bool NumberWithUnits::operator==(const NumberWithUnits& num)const
    {
        NumberWithUnits a=ver(num,this->s);
        if(abs(this->d - a.d) <= EPS)
        {
            return true;
            }
        return false;
    }

     NumberWithUnits &NumberWithUnits::operator++()
    {
        (this->d)++;
         return *this;
    }

     NumberWithUnits &NumberWithUnits::operator--()
    {
        (this->d)--;
         return *this;
    }

     NumberWithUnits NumberWithUnits::operator++( int )
    {
        double a=this->d;
       (this->d) ++ ;
        return NumberWithUnits(a,this->s );
    }

     NumberWithUnits NumberWithUnits::operator--( int )
    {
        double a=this->d;
       --(this->d)  ;
        return NumberWithUnits(a,this->s );
    }
     NumberWithUnits operator*(const double x, const NumberWithUnits &n)
    {
         return NumberWithUnits( n.d * x, n.s);
    }

     NumberWithUnits operator*(const NumberWithUnits &n, const double x)
    {
         return NumberWithUnits( n.d * x, n.s);
    }

    istream& operator>>(istream &is, NumberWithUnits& num)
    {
        double d1=0;
        char c='.';
        string s1,sd;

        while(c != '[')
        {
            is >> c ;
            if(c != ' ' )
            {
                sd += c;
            }
        }
        d1 = std::stod(sd);
        while (c != ']')
        {
            is >> c;
            if (c != ' ' && c !=']')
            {
                s1 += c;
            }
        }

        if(NumberWithUnits::map_unit[s1][s1] == 0)
        {
            throw "not the same units";
        }
        //cout << num.d ;
        num.s = s1;
        num.d = d1;
        //cout <<  "==" << num << endl;
      
        return is;
    }

    ostream& operator<<(ostream &os,const NumberWithUnits& num)
    {
        os << num.d << "[" << num.s << "]" << endl;
        return os;
    }

}

    