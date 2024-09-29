#include "testlib.h"

using namespace std;

int main(int argc, char** argv) {
    int al, ar, bl, br, a, b;
    
    registerGen(argc, argv, 1);

    al = atoi(argv[1]);
    ar = atoi(argv[2]);
    bl = atoi(argv[3]);
    br = atoi(argv[4]);

    a = rnd.next(al, ar);
    b = rnd.next(bl, br);

    printf("%d %d\n", a, b);
    return 0;
}
