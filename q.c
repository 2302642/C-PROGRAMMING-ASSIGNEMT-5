/*!
@file       the name of source file is qdriver.c
@author     Najih & DP login: n.hajasheikallaudin
@course     This source file meant for RSE course    
@section    which section of this course are you enrolled in RSE
@tutorial   Assignment 4
@date       file created on 27/09/2023
@brief      provide a brief explanation about what this source file does:
            This file is contains the 3 function definections to 
            calculate aproximation of pi using 3 diffent methods
______________________________________________________________________*/

//#include <stdio.h>                // printf, scanf
#include <math.h>                   // to use maths functions   pow(a,b), sqr()
#include <stdlib.h>                 // srand, rand
#include "q.h"

#define final_limit 2.00
#define initial_limit 0.00

double trapezoid_pi(int num_of_rects){                                            // num_of_rects represents number of rectangles that will be in the range of the curve
  double width = (final_limit - initial_limit) / num_of_rects;
  double area_of_summed_rectangles = 0;
  double height = 0;
  /*                                                                              // not working got ISSUE with large output
  for (int i = 0; i < num_of_rects; ++i){
    double x1 = i * width;                                                                  // Left x-coordinate of the rectangle
    double x2 = (i + 1) * width;                                                            // Right x-coordinate of the rectangle    

    double mid = (x1 + x2) / 2;                                                             // calculate the mid-point of the rectangle     //(mid-point is the height difference in between the taller and shorter rectangle)
        
    height = sqrt(pow(final_limit,2)  - pow(mid,2));                                        // calculate the height at the mid-point using Pythagorean theorem

    area_of_summed_rectangles +=  (width * height);                                         // Calculate the area of the trapezoid and add it to the total
  }*/
  for (int i = 0; i < num_of_rects; ++i){                                         // loop to calcaulate total height of rectangles
     height += sqrt( pow(final_limit,2) - pow(((i*2+1)*width/2),2));              // equation used to calaulate total height of rectangles
  }
  area_of_summed_rectangles = width * height;
  return area_of_summed_rectangles ;                                              // returning total area of rectangles
}

double montecarlo_pi(unsigned int seed, int num_of_trials) {                      // function used to calculate the result approximation of pi unig montecarlo method
  int inside_circle = 0;
  srand(seed);                                                                    // initialize the random number generator with the provided seed

  for (int i = 0; i < num_of_trials; i++) {                                       // num of times the darts are thrown onto the dart board -POINT_1-
    double x = (double) rand() / RAND_MAX;                                        // to generate a random x-coordinate in the given range [0, 1]
    double y = (double) rand() / RAND_MAX;                                        // to generate a random y-coordinate in the given range [0, 1]

    if (x * x + y * y <= 1) {                                                     // to check if the point (x, y) is inside the inscribed circle(for this case refering to the circle in the square)
      inside_circle++;                                                            // and adding when the point is in the inscribed circle
    }
  }
  return (double) inside_circle / num_of_trials * 4;                              // To compute and return to main in qdriver the approximate value of pi
}                                                                                 //Need to scale the result of the simulation by 4 due to calculating in 1 quadrent   // refer to "-POINT_2-"

double leibniz_pi(unsigned int num_elements){                                     // function used calculate the result approximation of pi using the leibniz method
    double sum = 0.00;

    //general forumula used based on leibniz method/rule, loop used to make it easier for calculation based on leibniz method/rule.
    for(unsigned int i = 0; i < num_elements; i++){                               //using unsigned int to make sure that the we dont accidently get negative numbers

        //if (i%2 == 0){sum += 1.0/(i*2 +1);}else{sum -= 1.0/(i*2 +1);}
        (i%2 == 0) ? (sum += 1.0/(i*2 +1)) : (sum -= 1.0/(i*2 +1));               //for alternating between + and - based on leibniz method/rule
    }

    //returning the output to the the leibniz_pi(i) function in main
    return sum * pow((double) final_limit, 2);                                    //multiplying the output based on the upper bound of the given interval for the output
}
/*
POINTS:
    "-POINT_1-"
    the number of time the dart is thrown at the dartbord per trail(refer to page 8 on assignemnt 5 PDF)

    "-POINT_2-"
    Because it is easier to generate positive random numbers, you will randomly throw a dart at the upper-right quadrant of the dartboard shaded in green in the above figure to the right 
    (refer to page 8 on assignemnt 5 PDF). In this case, the probability that the random point 'P' at which the dart strikes dartboard 'S' is also  in 'C' is '(pi/4)'. To compute approximate 
    value of 'pi', you will then have to scale the result of the simulation by '4'


current issue:
  5000000       3.141592653620     3.141559200000     3.1415924 | 5000000       3.141592653621     3.141559200000     3.1415924
  10000000      3.141592653601     3.140656800000     3.1415925 | 10000000      3.141592653600     3.140656800000     3.1415925

  issue with trapezoid_pi output;
*/