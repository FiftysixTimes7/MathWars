#include "functionutil.hpp"

Expression::Expression()
{
    e = te_compile("x", vars, 1, 0);
}

Expression::~Expression()
{
    te_free(e);
}

void Expression::set(const char *expr)
{
    te_free(e);
    e = te_compile(expr, vars, 1, 0);
}

real_t Expression::operator()(real_t x)
{
    if (e == NULL)
        return 0;
    this->x = x;
    double result = godot::Math::max(te_eval(e), 0.0);
    if (std::isinf(result) || result > 3.4e+38)
        return 0;
    return result;
}

int Expression::evaluate()
{
    real_t sum = 0;
    for (int i = 1; i < 16; ++i)
    {
        real_t cur = (*this)(i);
        sum += roundf(i - cur);
    }
    for (int i = 51; i < 56; ++i)
    {
        real_t cur = (*this)(i);
        sum += roundf(i - cur);
    }
    real_t digest;
    if (sum > 0)
    {
        digest = sum / 20 + 1;
        digest = digest * log(digest);
        digest = pow(digest, 1.75);
        return roundf(1328 * tan((digest / 1328.3 + 1) * M_PI / 4) - 1327);
    }
    else
    {
        digest = -sum / 20 + 1;
        digest = digest * log(digest);
        digest = pow(digest, 1.5);
        if (digest == INFINITY)
            return -500;
        return godot::Math::max(-roundf(digest), (float)-500.0);
    }
}

int evaluate(const char *expr)
{
    Expression e;
    e.set(expr);
    return e.evaluate();
}
