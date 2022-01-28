//延时函数初始化
uint32_t Sys_us;

void Init_Delay(uint8_t SYSClock)
{
  //设置滴答计时器时钟为HCLK
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
  Sys_us = SYSClock;
}

void Delay_us(uint32_t N_us)
{
  uint32_t Ticks;
  uint32_t Time_Old,Time_Now,Time_Count = 0;
  uint32_t Reload = SysTick -> LOAD;//滴答计时器重装载值
  Ticks = N_us * Sys_us;//需要产生的微秒数
  Time_Old = SysTick->VAL;//刚进入时的微秒数
  while(1)
  {
    Time_Now = SysTick->VAL;
    if(Time_Now != Time_Old)
    {
      if(Time_Now < Time_Old)
      {
        Time_Count += Time_Old - Time_Now;
      }
      else
      {
        Time_Count += Reload - Time_Now +Time_Old;
      }
      Time_Old = Time_Now;
      if(Time_Count >= Ticks)
      {
        break;//时间超过/等于要延迟的时间，就退出
      }
    }
  }
}