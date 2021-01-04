#define MEAN_FILTER_SIZE        15

typedef struct{
  float values[MEAN_FILTER_SIZE];
  short index;
  float sum;
  short count;
}MeanDiffFilter;


MeanDiffFilter meanDiffFilterIR;
float meanDiffResult=0;

//affiliate this variable to the data you wanna filter
float dataToFilter;
char txt[12];

void main(){
  
  UART1_Init_Advanced(9600, _UART_8_BIT_DATA, _UART_NOPARITY, _UART_ONE_STOPBIT, &_GPIO_MODULE_USART1_PA9_10);
  
  //init variables
  meanDiffFilterIR.index = 0;
  meanDiffFilterIR.sum = 0;
  meanDiffFilterIR.count = 0;
  
  while(1){
  
    meanDiffResult = MeanDiffFilter(dataToFilter,&meanDiffFilterIR);
    FloatToStr(meanDiffResult,txt);
    UART1_Write_Text("Result= ");
    UART1_Write_Text(txt);
    UART1_Write_Text("\n\r");
  }


}
float meanDiffFilter(float M, MeanDiffFilter* filterValues){
 
  float avg = 0;

  filterValues->sum -= filterValues->values[filterValues->index];
  filterValues->values[filterValues->index] = M;
  filterValues->sum += filterValues->values[filterValues->index];

  filterValues->index++;
  filterValues->index = filterValues->index % MEAN_FILTER_SIZE;

  if(filterValues->count < MEAN_FILTER_SIZE)
    filterValues->count++;

  avg = filterValues->sum / filterValues->count;
  return avg - M;
 }
