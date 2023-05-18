#include "user_pwm.h"
#include "stm32f1xx_hal_tim.h"
#include "stdio.h"

/*
 * 函数  : UserMain
 * 描述  : 用户主函数
 * 输入  :
 * 输出  :
 */
void UserPwmOutput(uint32_t Frequency, uint32_t Dutycycle, uint32_t NumPulse)
{
    uint32_t pwm_period;
    uint32_t pwm_pulse;
    
    /* 输出PWM */
    pwm_period = PWM_CK_CNT/Frequency - 1;                             //计算出计数周期(决定输出的频率)
    pwm_pulse  = (pwm_period + 1)*Dutycycle / 100;                     //计算出脉宽值(决定PWM占空比)

        /* 脉冲个数计时 */
    HAL_TIM_Base_Stop_IT(&CNT_TIMx);
    __HAL_TIM_SET_COUNTER(&CNT_TIMx, 0);
    __HAL_TIM_SET_AUTORELOAD(&CNT_TIMx, NumPulse-1);                           //设置中断更新数
    __HAL_TIM_CLEAR_IT(&CNT_TIMx, TIM_IT_UPDATE);
    HAL_TIM_Base_Start_IT(&CNT_TIMx); //使能定时器3和定时器3更新中断：TIM_IT_UPDATE

        /* 脉冲个数计时 */
    HAL_TIM_Base_Stop_IT(&CNT_TIM2);
    __HAL_TIM_SET_COUNTER(&CNT_TIM2, 0);
    __HAL_TIM_SET_AUTORELOAD(&CNT_TIM2, NumPulse-1);                           //设置中断更新数
    __HAL_TIM_CLEAR_IT(&CNT_TIM2, TIM_IT_UPDATE);
    HAL_TIM_Base_Start_IT(&CNT_TIM2); //使能定时器3和定时器3更新中断：TIM_IT_UPDATE


//    HAL_TIM_PWM_Stop(&PWM_TIMx, PWM_CHANNEL);                                        //失能TIM
//    __HAL_TIM_SET_COUNTER(&PWM_TIMx, 0);                                       //计数清零
//    __HAL_TIM_SET_AUTORELOAD(&PWM_TIMx, pwm_period);                           //更改频率
//    __HAL_TIM_SET_COMPARE(&PWM_TIMx, PWM_CHANNEL, pwm_pulse);                          //更改占空比
//    HAL_TIM_Base_Start(&PWM_TIMx);                                         //使能TIM
//    HAL_TIM_PWM_Start(&PWM_TIMx, PWM_CHANNEL);//开启PWM通道4
    


    HAL_TIM_PWM_Stop(&PWM_TIM2, PWM_CHANNEL);                                        //失能TIM
    __HAL_TIM_SET_COUNTER(&PWM_TIM2, 0);                                       //计数清零
    __HAL_TIM_SET_AUTORELOAD(&PWM_TIM2, pwm_period);                           //更改频率
    __HAL_TIM_SET_COMPARE(&PWM_TIM2, PWM_CHANNEL, pwm_pulse);                          //更改占空比
    HAL_TIM_Base_Start(&PWM_TIM2);                                         //使能TIM
    HAL_TIM_PWM_Start(&PWM_TIM2, PWM_CHANNEL);//开启PWM通道4
    
    HAL_TIM_PWM_Stop(&PWM_TIMx, PWM_CHANNEL);                                        //失能TIM
    __HAL_TIM_SET_COUNTER(&PWM_TIMx, 0);                                       //计数清零
    __HAL_TIM_SET_AUTORELOAD(&PWM_TIMx, pwm_period);                           //更改频率
    __HAL_TIM_SET_COMPARE(&PWM_TIMx, PWM_CHANNEL, pwm_pulse);                          //更改占空比
    HAL_TIM_Base_Start(&PWM_TIMx);                                         //使能TIM
    HAL_TIM_PWM_Start(&PWM_TIMx, PWM_CHANNEL);//开启PWM通道4


}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *hitm)
{
    if (hitm->Instance == TIM1) {
    }
    if (hitm->Instance == TIM2) {
    }
    if (hitm->Instance == TIM3) {
        HAL_TIM_PWM_Stop(&PWM_TIMx, PWM_CHANNEL);
        HAL_TIM_Base_Stop_IT(&CNT_TIMx);
    }
    if (hitm->Instance == TIM4) {
        HAL_TIM_PWM_Stop(&PWM_TIM2, PWM_CHANNEL);
        HAL_TIM_Base_Stop_IT(&CNT_TIM2);
    }

}







