#define DATAOUT 11//MOSI
#define DATAIN  12//MISO
#define SPICLOCK  13//sck
#define CHIPSELECT 10//ss

//opcodes
#define WREN  6
#define WRDI  4
#define RDSR  5
#define WRSR  1
#define READ  3
#define WRITE 2

byte read_vsense()
{
  int data;
  data = spi_transfer(0xFF);
  return data;
  
}

int data;

char spi_transfer(volatile char data)
{

  SPDR = data;                    // Start the transmission

  while (!(SPSR & (1<<SPIF)))     // Wait the end of the transmission

  {

  };

  return SPDR;                    // return the received byte
}

void setup()
{

  Serial.begin(9600);

  pinMode(DATAOUT, OUTPUT);

  pinMode(DATAIN, INPUT);

  pinMode(SPICLOCK,OUTPUT);

  pinMode(CHIPSELECT,OUTPUT);

  digitalWrite(CHIPSELECT,HIGH); //disable device

  /*
  SPCR
| 7    | 6    | 5    | 4    | 3    | 2    | 1    | 0    |
| SPIE | SPE  | DORD | MSTR | CPOL | CPHA | SPR1 | SPR0 |

SPIE - Enables the SPI interrupt when 1

SPE - Enables the SPI when 1

DORD - Sends data least Significant Bit First when 1, most Significant Bit first when 0

MSTR - Sets the Arduino in controller mode when 1, peripheral mode when 0

CPOL - Sets the data clock to be idle when high if set to 1, idle when low if set to 0

CPHA - Samples data on the falling edge of the data clock when 1, rising edge when 0

SPR1 and SPR0 - Sets the SPI speed, 00 is fastest (4MHz) 11 is slowest (250KHz)
  */

// so for the device we need SPCR 01010111

/*
Is data shifted in MSB or LSB first? MSB

SPI-Compatible Serial Digital Data Output Pin. ADC conversion data is
shifted out by SCLK clock, with MSB first.

Is the data clock idle when high or low? low

This device supports a standard SPI Mode
0,0 only. SPI MODE 0,0: in this mode, the
SCLK idle state is Low. Data is clocked out
on the SDO pin on the falling edge of the
SCLK pin. For the MCP33151/41-XX, this
means that there will be a rising edge
before there is a falling edge.

Are samples on the rising or falling edge of clock pulses? falling

What speed is the SPI running at? slowest 250kHz device supports up to 100MHz

Once you have your SPI Control Register set correctly you just need to figure out
how long you need to pause between instructions and you are ready to go. 
*/


//need to know the shape of the output signal of the sensor
//when CS goes high, chip starts data conversion, and on the falling edge data is available and shifted out by the clock
//data conversion takes at most 1.2 microseconds, and then you can read the data at 100 MHz, meaning 100Mbps?
//you need to read 12 or 14 bits into your SPI data register

//14 bits or 12 bits of data 
//MCP33151-XX //this is the one we have
//(14-bit)

//MCP33141-XX
//(12-bit) //this is the one that we DO NOT have

//how frequent does the sensor output this data? mananged by SPI clock?
//the slowest is 500 Ksps but each
//you can set the clock frequency to 100MHz max

//how many bytes are sent every clock cycle? 1 bit
//how much I need to delay between the readings? at least 2 microseconds?

//where do I set the clock frequency in the code? in the control register perhaps?



//

  // SPCR = 01010000

  //interrupt disabled,spi enabled,msb 1st,controller,clk low when idle,

  //sample on leading edge of clk,system clock/4 rate (fastest)

  SPCR = (1<<SPE)|(1<<MSTR)|(1<<CPHA)|(1<<SPE1)|(1<<SPE0);

  clr=SPSR;

  clr=SPDR;

  delay(10);

}



void loop()
{

  
  digitalWrite(CHIPSELECT,LOW); //get data ready at output of sensor
  data = spi_transfer(0xFF); //read byte
  Serial.print(data,DEC); //print byte
  Serial.print('\n',BYTE); //print endl
  data = spi_transfer(0xFF);
  Serial.print(data,DEC);
  Serial.print('\n',BYTE);
  digitalWrite(CHIPSELECT,HIGH); //get a new sample (start a new conversion)
  // delay (1); // wait certain amount of time for conversion to finish before you read data again
  // delay argument in ms.
  // delay (1000); // delay some time for readablitiy
  

  /*
    eeprom_output_data = read_eeprom(address);

  Serial.print(eeprom_output_data,DEC);

  Serial.print('\n',BYTE);

  address++;

  if (address == 128)

    address = 0;

  delay(500); //pause for readability
  */

}