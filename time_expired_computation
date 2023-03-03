/**
* @brief check 	expired  time referred to Timer
*
* @param [in] <sec>     : period to compare with reftime
* @param [in] <reftime> : old value of timer
* @param [in] <now>     :
*
* @return TRUE  : Timer Expired
* @return FALSE : Timer *NOT* expired
*/
static bool timer_expired_calc(uint16_t ms, uint16_t refTime, uint16_t now)
{
    const uint32_t timer_max_count = 0xFFFFuL;

    bool ret;
    
    uint32_t expired_ms;
    uint32_t delta;
    
    if (ms <= 0u)
    {
    	ret = true;
    }
    else
    {
    	expired_ms = (uint32_t) ms;  /* intervallo timer 1 millisecondo fisso */
                           
    	if ((((uint32_t) refTime + expired_ms) >= timer_max_count) && (now < refTime))
    	{
    		delta = timer_max_count - refTime;
    		expired_ms -= delta ;
    		ret = (now >= expired_ms) ? true: false;
    	}
    	else
    	{
    		delta = now - (uint32_t) refTime;
    		ret = (delta >= expired_ms) ? true: false;
    	}
    }
                   
    return ret;
}
