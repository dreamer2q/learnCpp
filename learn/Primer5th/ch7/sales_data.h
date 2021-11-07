
#pragma once
#ifndef __SALES_DATA_HEADER_H
#define __SALES_DATA_HEADER_H

#include <iostream>
#include <string>

//auxiliary functions
class Sales_data {
   public:
    Sales_data() = default;
    Sales_data(const std::string& s) : bookNo(s) {}
    Sales_data(const std::string& s, unsigned n, double p) : bookNo(s), revenue(n * p) {}
    Sales_data(std::istream&);

    std::string isbn() const { return bookNo; }
    Sales_data& combine(const Sales_data&);
    double avg_price() const;

    friend std::istream& read(std::istream&, Sales_data&);
    friend std::ostream& print(std::ostream&, const Sales_data&);
    friend Sales_data add(const Sales_data&, const Sales_data&);

   private:
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

std::istream& read(std::istream& is, Sales_data& item);
std::ostream& print(std::ostream& os, const Sales_data& item);
Sales_data add(const Sales_data& lhs, const Sales_data& rhs);

#endif
