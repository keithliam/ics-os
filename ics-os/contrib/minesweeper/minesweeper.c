
/*
	MANALOTO, Keith Liam L.
	GALVEZ, Juan Miguel T.
	CMSC 125 T-6L
*/

#include "../../sdk/dexsdk.h"
// void drawRectangle(int x, int y, int w, int h, int color){
//    int i,j;
//    for (i=y;i<=(y+h);i++)
//       for (j=x;j<=(x+w);j++)
//          write_pixel(j,i,color);
// }

void drawRectangle(int x, int y, int w, int h, int color){
   int i,j;
   for (i=y;i<=(y+h);i++)
      for (j=x;j<=(x+w);j++)
         write_pixel(j,i,color);
}

int main() {

    set_graphics(VGA_320X200X256);
	drawRectangle(0,0,320,3,0);
	drawRectangle(3,3,320,3,1);
	drawRectangle(6,6,320,3,2);
	drawRectangle(9,9,320,3,3);
	drawRectangle(12,12,320,3,4);
	drawRectangle(15,15,320,3,5);
	drawRectangle(18,18,320,3,6);
	drawRectangle(21,21,320,3,7);
	drawRectangle(24,24,320,3,8);
	drawRectangle(27,27,320,3,9);
	drawRectangle(30,30,320,3,10);
	drawRectangle(33,33,320,3,11);
	drawRectangle(36,36,320,3,12);
	drawRectangle(39,39,320,3,13);
	drawRectangle(42,42,320,3,14);
	drawRectangle(45,45,320,3,15);
	drawRectangle(48,48,320,3,16);
	drawRectangle(51,51,320,3,17);
	drawRectangle(54,54,320,3,18);
	drawRectangle(57,57,320,3,19);
	drawRectangle(60,60,320,3,20);
	drawRectangle(63,63,320,3,21);
	drawRectangle(66,66,320,3,22);
	drawRectangle(69,69,320,3,23);
	drawRectangle(72,72,320,3,24);
	drawRectangle(75,75,320,3,25);
	drawRectangle(78,78,320,3,26);
	drawRectangle(81,81,320,3,27);
	drawRectangle(84,84,320,3,28);
	drawRectangle(87,87,320,3,29);
	drawRectangle(90,90,320,3,30);
	drawRectangle(93,93,320,3,30);
	drawRectangle(96,96,320,3,31);
	drawRectangle(99,99,320,3,32);
	drawRectangle(102,102,320,3,33);
	drawRectangle(105,105,320,3,34);
	drawRectangle(108,108,320,3,35);
	drawRectangle(111,111,320,3,36);
	drawRectangle(114,114,320,3,37);
	drawRectangle(117,117,320,3,38);
	drawRectangle(120,120,320,3,39);
	drawRectangle(123,123,320,3,40);
	drawRectangle(126,126,320,3,41);
	drawRectangle(129,129,320,3,42);
	drawRectangle(132,132,320,3,43);
	drawRectangle(135,135,320,3,44);
	drawRectangle(138,138,320,3,45);
	drawRectangle(141,141,320,3,46);
	drawRectangle(144,144,320,3,47);
	drawRectangle(147,147,320,3,48);
	drawRectangle(150,150,320,3,49);
	drawRectangle(153,153,320,3,50);
	drawRectangle(156,156,320,3,51);
	drawRectangle(159,159,320,3,52);
	drawRectangle(162,162,320,3,53);
	drawRectangle(165,165,320,3,54);
	drawRectangle(168,168,320,3,55);
	drawRectangle(171,171,320,3,56);
	drawRectangle(174,174,320,3,57);
	drawRectangle(177,177,320,3,58);
	drawRectangle(180,180,320,3,59);
	drawRectangle(183,183,320,3,60);
	drawRectangle(186,186,320,3,61);
	drawRectangle(189,189,320,3,62);
	drawRectangle(192,192,320,3,63);
	drawRectangle(195,195,320,3,64);
	drawRectangle(198,198,320,3,65);
	drawRectangle(201,201,320,3,66);
	drawRectangle(204,204,320,3,67);
	drawRectangle(207,207,320,3,68);
    write_text("SUNGKA",140,50,WHITE,2);
    write_text("SUNGKAA",140,100,WHITE,1);
    write_text("SUNGKAAA",140,150,WHITE,0);
   printf("Hello World from ICS-OS!\n");
   return 0;
}
