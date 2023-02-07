#include "co/tasked.h"
#include "co/cout.h"
#include "co/time.h"

void f() {
    COUT << "f(): " << now::str();
}

void g() {
    COUT << "g(): " << now::str();
}

int main(int argc, char** argv) {
    COUT << "now: " << now::str();

    Tasked s;
    s.run_in(f, 0);
    s.run_in(f, 1);
    s.run_in(f, 2);
    s.run_in(f, 0);
    s.run_every(g, 3);
    s.run_at(f, 17, 12, 59);
    s.run_daily(f, 5, 18, 0);

    while (1) sleep::sec(1024);
    return 0;
}
