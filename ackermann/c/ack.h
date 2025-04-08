/* 
* Author: Liam Mackay
* Date: April 4th, 2025
* Description: This is a C-implementation of the Ackermann function, considered
* to be the first discovered non-primitive recursive function. There are 
* several implementations of this algorithm contained within, with various 
* levels of optimizations applied to them. It is ill-advised to attempt to 
* calucate beyond A(4,1) as A(4,2) has 19729 digits. Perhaps there is a 
* concurrent algorithm that can compute this efficiently- it is unknown to me.
*/
#ifndef _ACK_H
#define _ACK_H

#include <sys/time.h>
#include <sys/resource.h>

#include <ctype.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ackermann.h"

#define PEEK_SIZE 5
#endif
