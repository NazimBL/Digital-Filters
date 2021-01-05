typedef struct
{
  float v[2];
  float result;
}ButterWorthFilter;

lowPassButterworthFilter( float x, ButterworthFilter * filterResult );


//pre filled input data array 
unsigned int x_table[DATA_SIZE];
ButterWorthFilter bwFilter;
float bwResult=0;

char txt[10];
unsigned short i;

void main(){

  UART1_Init_Advanced(9600, _UART_8_BIT_DATA, _UART_NOPARITY, _UART_ONE_STOPBIT, &_GPIO_MODULE_USART1_PA9_10);
  bwFilter.v[0] = 0;
  bwFilter.v[1] = 0;
  bwFilter.result = 0;
  
  while(1){
  
  for(i=0; i<DATA_SIZE; i++){
  
  bwResult=lowPassButterworthFilter((float)x_table[i], &bwFilter);
          FloatToStr(bwResult,txt);
          UART1_Write_Text("bwF output= ");
          UART1_Write_Text(txt);
          UART1_Write_Text("\n\r");
  }
  
  }
}

float lowPassButterworthFilter( float x, ButterWorthFilter * filterResult )
{
  filterResult->v[0] = filterResult->v[1];

  //Fs = 100Hz and Fc = 10Hz
  //filterResult->v[1] = (2.452372752527856026e-1 * x) + (0.50952544949442879485 * filterResult->v[0]);

  //Fs = 100Hz and Fc = 4Hz
  filterResult->v[1] = (1.367287359973195227e-1 * x) + (0.72654252800536101020 * filterResult->v[0]); //Very precise butterworth filter

  filterResult->result = filterResult->v[0] + filterResult->v[1];
  
  return filterResult->result;
}
