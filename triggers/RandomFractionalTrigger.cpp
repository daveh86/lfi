/*
     Created by Paul Marinescu and George Candea
     Copyright (C) 2009 EPFL (Ecole Polytechnique Federale de Lausanne)

     This file is part of LFI (Library-level Fault Injector).

     LFI is free software: you can redistribute it and/or modify it  
     under the terms of the GNU General Public License as published by the  
     Free Software Foundation, either version 3 of the License, or (at  
     your option) any later version.

     LFI is distributed in the hope that it will be useful, but  
     WITHOUT ANY WARRANTY; without even the implied warranty of  
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU  
     General Public License for more details.

     You should have received a copy of the GNU General Public  
     License along with LFI. If not, see http://www.gnu.org/licenses/.

     EPFL
     Dependable Systems Lab (DSLAB)
     Room 330, Station 14
     1015 Lausanne
     Switzerland
*/

#include "RandomFractionalTrigger.h"
#include "Backtrace.i"
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iostream>

unsigned int RandomFractionalTrigger::seed = 0;

RandomFractionalTrigger::RandomFractionalTrigger()
  : probability(0), good(0)
{
}

void RandomFractionalTrigger::Init(xmlNodePtr initData)
{
  xmlNodePtr nodeElement, textElement;
  time_t t;
  const char* seedFile = "rndtrigger.seed";

  nodeElement = initData->children;
  while (nodeElement)
  {
    if (XML_ELEMENT_NODE == nodeElement->type &&
      !xmlStrcmp(nodeElement->name, (const xmlChar*)"percent"))
    {
      textElement = nodeElement->children;
      if (XML_TEXT_NODE == textElement->type)
        probability = atof((char*)textElement->content);
    }
    nodeElement = nodeElement->next;
  }
  
  if (!seed)
  {
    seed = (unsigned)time(&t);
    srand(seed);
  }
}

bool RandomFractionalTrigger::Eval(const string*, ...)
{
  int rand_num = rand();
  int prob = 100*(1/probability);
  if (rand_num % prob == 1) {
    cout << "Good is: " << good << endl;
    good = 0;
    Backtrace();
    return true;
  }
  good++;
  return false;
}
