
#include <iostream>
#include "Factory.h"

using namespace std;

int main() {
    Factory f = Factory::getFactory();
    f.process();
    return 0;
}
