
#include <iostream>
#include <execinfo.h>

inline void Backtrace()
{
        int j, nptrs;
        void *buffer[100];
        char **strings;

        nptrs = backtrace(buffer, 100); 
        strings = backtrace_symbols(buffer, nptrs);
        if (strings == NULL) {
                cout << "Failed to produce Backtrace" << endl;
                return;
        }
        for (j = 0; j < nptrs; j++)
                cout << strings[j] << endl;
        delete strings;
}
