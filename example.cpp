#include "example.h"


example::example()
{
    cout << "example::example()" << endl;
    MatrixConvert<uint16_t> m(8182);
    cout << " MatrixConvert<uint16_t> m(1000);" << endl;
}
void example::say_hello(void) {
    cout << "hello python,I am C++" << endl;
}

void example::change(int din) {
    num = din;
}

//int example::get_num(void) {
//    return num;
//}

