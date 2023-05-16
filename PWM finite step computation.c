
PWM_PERIOD 3    /*number of steps in which divide the 100 duty*/

uint16_t HALi_PulseOutputGetPulses(uint8_t dutyPerc)
{

    uint16_t hal_pwm_period=PWM_PERIOD;  
    uint16_t hal_pwm_step;  /*step dimension*/
    uint16_t pulses;    /*number of puses as output*/

    hal_pwm_step = (100 % hal_pwm_period) ? (100/hal_pwm_period) : ((100/hal_pwm_period)+1);

    /* rounding */
    dutyPerc = ((dutyPerc + (hal_pwm_step / 2U)) / hal_pwm_step) * hal_pwm_step;

    /* saturation */
    if (dutyPerc > 100U) {
        dutyPerc = 100U;
    }

    /* pulses */
    pulses = ((uint16_t)dutyPerc * hal_pwm_period) / 100U;

    return pulses;
}