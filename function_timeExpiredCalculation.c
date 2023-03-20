/**
* @brief   Example of functions to compute time expired using one running timer.
*		   Check is done in polling, so in a cycle.
*		   Can be used to execute a loop with a certain period.
*
* @author  Gerardo Detta, gerardodetta@gmail.com
* @date    2023.03.03
*
*/






/**
* @brief check 	expired  time referred to Timer
*
* @param [in] <interval> [16bit]    : time inteval to check if expired
* @param [in] <oldTime>  [16bit] 	: old value of timer
* @param [in] <nowTime>  [16bit]    : actual value of timer
*
* @return TRUE  : interval time Expired
* @return FALSE : *NOT* expired
*/
static bool timer_expired_calc(uint16_t interval, uint16_t oldTime, uint16_t nowTime)
{
    const uint32_t timer_max_count = 0xFFFFuL; //max value on 16bit [4x4=16] (defined on 32 for overflow check)

    bool toReturn; 
    
    uint32_t interval_32bit; //store value of interval on 32bit, on 32 for overflow check
    uint32_t delta; //time expired from old to now (computed with overflow check)
    
    if  (interval <= 0u) 
    {
    	toReturn = true;
    }
    else
    {
    	interval_32bit = (uint32_t) interval;  /* cast on 32bit for overlow check */
                           
		/* overflow occurred */
    	if ((((uint32_t) oldTime + interval_32bit) >= timer_max_count) && (nowTime < oldTime))
    	{
    		delta = timer_max_count - oldTime;
    		interval_32bit -= delta ;
    		toReturn = (nowTime >= interval_32bit) ? true: false;
    	}
		/* no overflow */
    	else
    	{
    		delta = nowTime - (uint32_t) oldTime;
    		toReturn = (delta >= interval_32bit) ? true: false;
    	}
    }
                   
    return toReturn;
}




/**
 * @brief Example of call for "timer_expired_calc()" function
 *		  As <nowTime> pass the the actual value of timer (timer need to be configured before).
 *		  Compare <startingTime_ms> with timer value, to check if <timeout_value_ms> expired.
 *		  Done in polling.
 *
 * @param [in]  <timeout_value_ms>: time interval to check if expired
 * @param [in]  <startingTime_ms>: starting value from wich time need to expire
 *
 * @return TRUE  : if expired <timeout_value_ms> from <startingTime_ms>
 * @return FALSE : *NOT* expired
 */
bool timer_expired_ms(uint16_t timeout_value_ms, uint16_t startingTime_ms)
{      
    return timer_expired_calc(timeout_value_ms, startingTime_ms, HAL_timer1Ms_now() );
}





/**
 * @brief Example of usage of "timer_expired_ms()" function, in polling. 
 *		  Cycle is done with <LOOP_MS> period.
 *		  <startingTime_ms> needs to be updated after time expired, to start again.
 *
 */
#define LEDCUP_LOOP_MS ((uint16_t)50) 	/* [ms] loop duration, define as constant  */
static uint16_t loop_timer_ms = 0;  	/* [ms] timer variable to store loop time  */

while(1) /*done in a loop for polling*/
{
	if (timer_expired_ms(LOOP_MS, loop_timer_ms))
	{
		/* do something... */

		loop_timer_ms = HAL_timer1Ms_now(); //update loop's timer variable
	}

	/*alternative in which is passed only the duration, while the timer is local*/
	LEDCUP_TaskExec(LEDCUP_LOOP_MS);


}


static void LEDCUP_TaskExec(uint32_t delay_ms)
{
	static uint32_t led_timer_ms = 0;
	if (TIMER_isExpired_ms(led_timer_ms, delay_ms))
	{
		/* do something... */

		led_timer_ms = TIMER_Now_ms();
	}
}