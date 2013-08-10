#ifndef NONCOPYABLE_H
#define NONCOPYABLE_H

#include "global.h"
namespace multithreads{
    class noncopyable{
        protected:
            noncopyable(){}
            ~noncopyable(){}
        private:
            noncopyable(const noncopyable& ){}
            noncopyable& operator=(const noncopyable& );
    };
}
#endif
