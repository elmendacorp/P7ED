#include <iostream>
#include "Gitcode.h"
int main() {
    Gitcode migit("ficheros2.txt","commits2.txt");
    migit.estadisticas();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}