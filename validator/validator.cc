#include "testlib.h"
using namespace std;

#define A_MIN 1
#define A_MAX 9
#define B_MIN 1
#define B_MAX 9

int main(int argc, char** argv) {
    registerValidation(argc, argv);
    inf.readInt(A_MIN, A_MAX, "A");
    inf.readSpace();
    inf.readInt(B_MIN, B_MAX, "B");
    inf.readEoln();
    inf.readEof();
}
