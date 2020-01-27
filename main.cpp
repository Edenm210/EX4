
#include <iostream>
#include "Main.h"

int main(int argc, char *argv[]){
  boot::Main m;
  try{
    if(argc<2) {
      throw "MISSING PORT IN CMD";
    } else {
      m.main(atoi(argv[1]));
    }
  } catch  (const char * e) {
    cout << e << endl;
  }

}