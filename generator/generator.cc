#include "testlib.h"

using namespace std;

int main(long long argc, char** argv) {
    long long al, ar, bl, br, a, b;
    
    registerGen(argc, argv, 1);

    al = atoi(argv[1]);
    ar = atoi(argv[2]);
    bl = atoi(argv[3]);
    br = atoi(argv[4]);
    cl = atoi(argv[3]);
    cr = atoi(argv[4]); 

    a = rnd.next(al, ar);
    b = rnd.next(bl, br);
    c = rnd.next(cl, cr);
    printf("%d %d\n", a, b, c);
    return 0;
}
