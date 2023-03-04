#define dataport PORTB
#define rs RD5
#define rw RD6
#define en RD7
void cmm(unsigned char item);
void dat(unsigned int item);
void data_str(unsigned char *str);
void msdelay(unsigned char msec);
void lcdint();

void cmm(unsigned char item) // Function to send command to LCD
{	
	dataport = item;
	rs=0;
	rw=0;
	en=1;
	msdelay(1);
	en=0;
	msdelay(1);
	return;
}
void dat(unsigned int item)// Function to send data to LCD
{
	dataport = item;
	rs= 1;
	rw=0;
	en=1;
	msdelay(1);
	en=0;
	msdelay(1);
	return;
}
void lcdint()
{	
	cmm(0x38);
	cmm(0x0C);
	cmm(0x01);
	cmm(0x06);
	cmm(0x80);
}
void msdelay(unsigned char item) // Time delay function
{
	int i,j ;
	for(i=0;i<item;i++)
  	{
		for(j=0;j<150;j++);
	}
} 
void data_str(unsigned char *str) // Function to send data to string
{
	int i=0;
	while(str[i]!='\0')
	{
	  dat(str[i]);
	  i++;
	}
	return;
}