#include<stdio.h>
#include"freertos/FreeRTOS.h"
#include"freertos/task.h"
#include"freertos/timers.h"

TaskHandle_t task1_handle,task2_handle,task3_handle;
TimerHandle_t task3_timer_handle;

void task3_timer_callback(TimerHandle_t task3_timer_handle)
{
    printf("timer fired\n");
}

void task1(void *data)
{
    printf("\n task1:created ");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    vTaskDelete(NULL);
}

void task2(void *data)
{
    printf("\n task2:created ");
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    vTaskDelete(NULL);
}



void task3(void *data)
{
    printf("\n task3:created ");
    printf("\n starting task3 ");
    printf("\n creating the timer in task3 \n");
    vTaskDelay(5000 / portTICK_PERIOD_MS);
    task3_timer_handle = xTimerCreate("one_s_timer",10000/portTICK_PERIOD_MS,pdFALSE,0,task3_timer_callback);
    xTimerStart(task3_timer_handle,0);
    
    vTaskDelete(NULL);
}

void app_main()
{
    printf("main task\n ");
    xTaskCreate(task1,"task1",2048,NULL,5,&task1_handle);
    xTaskCreate(task2,"task2",2048,NULL,6,&task2_handle);
    xTaskCreate(task3,"task3",2048,NULL,7,&task3_handle);
   
}

