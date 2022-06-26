#pragma once

#include <cmath>
#include <Godot.hpp>
#include "tinyexpr.h"

class Expression
{
    te_variable vars[1] = {{"x", &x}};
    te_expr *e = NULL;
    double x;

public:
    Expression();
    ~Expression();
    void set(const char *expr);
    int evaluate();
    real_t operator()(real_t x);
};

int evaluate(const char *expr);
