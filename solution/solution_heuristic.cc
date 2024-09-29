#include <algorithm>
#include <cstdio>

int main() {
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d\n", std::min(10, a + b));
    return 0;
}
