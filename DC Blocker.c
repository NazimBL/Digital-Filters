/*
 filter equation:
 w(t)=x(t)+∝∗w(t−1) 
 y(t)=w(t)−w(t−1)
 */ 
 
 #define ALPHA 0.95  //dc filter alpha value
 #define DATA_SIZE 50
 
 typedef struct {
 float w;
 float output;
 }DC_Filter;

DC_Filter dcBlocker(float x, float prev_w, float alpha);

//pre filled data array from which we wanna take off the dc bias
unsigned int x_table[DATA_SIZE];
DC_Filter dc_filter;
float filtered_dc=0;

char txt[10];
unsigned short i;

void main(){

  UART1_Init_Advanced(9600, _UART_8_BIT_DATA, _UART_NOPARITY, _UART_ONE_STOPBIT, &_GPIO_MODULE_USART1_PA9_10);
  dc_filter.w=0;
  dc_filter.output=0;
  
  while(1){
  
  for(i=0; i<DATA_SIZE; i++){
  dc_filter=dcBlocker((float)x_table[i],dc_filter.w,ALPHA);
          filtered_dc=dc_filter.output;
          FloatToStr(dcFilteredIR,txt);
          UART1_Write_Text("Filtered Value= ");
          UART1_Write_Text(txt);
          UART1_Write_Text("\n\r");
  }
  
  }
}

DC_Filter dcBlocker(float x, float prev_w, float alpha)
{
  DC_Filter filtered;
  filtered.w = x + alpha * prev_w;
  filtered.output = filtered.w - prev_w;

  return filtered;
}
