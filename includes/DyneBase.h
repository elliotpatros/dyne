//
//  DyneBase.h
//  dyne
//
//  Created by Elliot Patros on 12/10/15.
//  Copyright (c) 2015 Elliot Patros. All rights reserved.
//

#ifndef dyne_DyneBase_h
#define dyne_DyneBase_h

#include <iostream>
#include <vector>
#include <pthread.h>
#include <unistd.h> // for chdir and usleep

#define DYNE_MAX_GBALLS 5

using std::cout;
using std::endl;

using std::vector;
using std::string;

using std::runtime_error;
using std::exception;

using std::unique_ptr;

struct IO
{
    inline static void post(void)
    {
        cout << endl;
    }
    
    template<typename Type, typename... Types>
    inline static void post(Type type, Types... types)
    {
        cout << type;
        post(types...);
    }
};


#endif
