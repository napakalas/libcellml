/* The content of this file was generated using the C profile of libCellML 0.2.0. */

#include <stddef.h>

extern const char LIBCELLML_VERSION[];

extern const size_t STATE_COUNT;
extern const size_t VARIABLE_COUNT;

typedef enum {
    CONSTANT,
    COMPUTED_CONSTANT,
    ALGEBRAIC
} VariableType;

typedef struct {
    char name[8];
    char units[16];
    char component[25];
} VariableInfo;

typedef struct {
    char name[8];
    char units[16];
    char component[25];
    VariableType type;
} VariableInfoWithType;
