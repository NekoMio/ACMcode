#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int base = 76543;
int main(int argc, const char *argv[])
{
    if (argc == 1) return 0;
    int n = strlen(argv[1]);
    unsigned long long Hash = 0;
    for (int i = 0; i < n; i++)
        Hash = Hash * base + argv[1][i];
    while (Hash)
    {
        printf("%c", '0' + Hash % 50);
        Hash /= 50;
    }
    printf ("\n");
}
