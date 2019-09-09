/* The contents of this file was generated from version 0.2.0 of libCellML. */

#include <math.h>
#include <stddef.h>
#include <stdlib.h>

const char VERSION[] = "0.2.0";

const size_t STATE_COUNT = 1;
const size_t VARIABLE_COUNT = 2;

struct VariableInfo {
    char component[9];
    char name[3];
    char units[14];
};

const struct VariableInfo VOI_INFO = {"my_model", "t", "second"};

const struct VariableInfo STATE_VECTOR_INFORMATION_ARRAY[] = {
    {"my_model", "x", "dimensionless"},
};

const struct VariableInfo VARIABLE_VECTOR_INFORMATION_ARRAY[] = {
    {"my_model", "a", "per_s"},
    {"my_model", "xx", "dimensionless"},
};

double * createStatesArray()
{
    return (double *) malloc(1 * sizeof(double));
}

double * createVariablesArray()
{
    return (double *) malloc(2 * sizeof(double));
}

void deleteArray(double *array)
{
    free(array);
}

void initializeConstants(double *states, double *variables)
{
    states[0] = 1.0;
    variables[0] = 1.0;
}

void computeComputedConstants(double *variables)
{
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    rates[0] = variables[0];
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
    variables[1] = 2.0*states[0];
}
