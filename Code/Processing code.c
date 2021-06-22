// Processing code/graphics

import processing.serial.*;//importig serial port

Serial portCom3;        //making object of serial port com3
   
PImage img; //variable for loading image

int prevhoriz=1;//variable to set previous horizontal position
int preh=0;//variable to setprevious height
int horiz = 1;  //varialbe to set horizontal position of graph
void setup () // setup function which runs once during program execution
{
  
  size(800, 600); //size for console/window       

 
  println(Serial.list());//printing all the available ports
  
 

  portCom3 = new Serial(this, Serial.list()[0], 9600);  //using dynamic memory allocation use serial at position zero of array which is com3
 img=loadImage("red.png");//loading image for background
  portCom3.bufferUntil('\n');//before calling serial  set some specific data buffer 
  background(0);      //for background colour
}
void draw () {
  
}

void serialEvent (Serial portCom3)//serial event function for gettig the data from com3
{
  
  String istring = portCom3.readStringUntil('\n');// read the string from com3 using ascii values
  if (istring != null) {
    istring = trim(istring);                //function for trimming white spaces
    float bytstring = float(istring);           // casting for cinverting into floating no.
    bytstring = map(bytstring, 0, 1023, 0, height); //map the range of data come from serialport according to window size

    
    stroke(127,34,255);     //stroke function for setting the colour of graph line
    strokeWeight(4);        //strokeweight function for setting the thickness of line 
    line(prevhoriz, preh, horiz, height - bytstring); //drawing line according to given data
    prevhoriz= horiz;//updating the value of previous horizontal position
   preh= int(height-bytstring);//setting the height of graph

      prevhoriz= 0;
       horiz = 0;
      background(0);  
    } 
    else { 
      horiz++;// continue to incrememt horizontal position for motion of graph
    }
  }
}
