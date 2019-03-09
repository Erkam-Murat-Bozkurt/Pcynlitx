/*

Copyright ©  2019,  Erkam Murat Bozkurt

This file is part of the research project which is carried by Erkam Murat Bozkurt.

This is a free software: you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation
either version 3 of the License, or any later version.

This software is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program. If not, see <http://www.gnu.org/licenses/>.

*/

#include "IntToCharTranslater.h"

IntToCharTranslater::IntToCharTranslater(){

  this->BaseNumbers[0]= 48;

  for(int i=1;i<10;i++){

    this->BaseNumbers[i] = this->BaseNumbers[i-1]+1;
  };
}

IntToCharTranslater::IntToCharTranslater(const IntToCharTranslater & oring){

}

IntToCharTranslater::~IntToCharTranslater(){

}

char * IntToCharTranslater::Translate(int integer){

  if(integer > 9){

     this->CharValue[0]= this->BaseNumbers[integer/10];
     this->CharValue[1]= this->BaseNumbers[integer%10];
     this->CharValue[2]= '\0';

  }
  else
  {
    this->CharValue[0]= this->BaseNumbers[integer];
    this->CharValue[1]= '\0';
    this->CharValue[2]= '\0';
  }

  return this->CharValue;
}

int IntToCharTranslater::TranslateFromCharToInt(char * ch){

      int base_size = strlen(ch);

      int integer_base[base_size];

      for(int k=0;k<base_size;k++){

          int buffer = (int) (ch[k]);

          for(int i=0;i<10;i++){

             if(buffer == this->BaseNumbers[i]){

                integer_base[k] = i;
             }
          }
      }

     this->IntegerValue = 0;

     int integerBase = 0;

     for(int k=base_size-1;k>-1;k--){

         this->IntegerValue = this->IntegerValue + integer_base[integerBase] * this->Power(10,k);

         integerBase++;
     }

     return this->IntegerValue;
}

int IntToCharTranslater::Power(int base,int power){

    this->IntegerPower = 1;

    if(power == 0){

       return this->IntegerPower;
    }

    int counter =1;

    do{

        this->IntegerPower = base * this->IntegerPower;

        counter++;

    }while(counter<power+1);

    return this->IntegerPower;
}
