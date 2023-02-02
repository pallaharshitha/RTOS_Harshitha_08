
#include<stdio.h>
#include"freertos/FreeRTOS.h"
#include"freertos/task.h"
#include"freertos/queue.h"

#define MQ_SIZE 4
#define MSG_SIZE 64
TaskHandle_t task1_handle,task2_handle,task3_handle,task4_handle,task5_handle;
QueueHandle_t msg_que;
static int taskcore = 1;

void task1(void *data)
{
    printf("\n task1 : created ");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    vTaskDelete(NULL);
}

void task2(void *data)
{
    printf("\n task2 : created ");
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    vTaskDelete(NULL);
}

void task3(void *data)
{
    printf("\n task3 : created ");
    vTaskDelay(5000 / portTICK_PERIOD_MS);
    vTaskDelete(NULL);
}

void task4(void *data)
{
    int task4_data = 300;
    printf("\ntask 4 : created ");
    while(1)
    {
        task4_data++;
        printf("\ntask 4 sending integer data to task 5 ");
        xQueueSend(msg_que,&task4_data,pdMS_TO_TICKS(3000));
        
        vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}


void task5(void *data)
{
    int buffer = 0;
    printf("\ntask 5 : created");
    while(1)
    {
        xQueueReceive(msg_que,&buffer,portMAX_DELAY);
        printf("\ntask 5:received data from task 4:%d ",buffer);
    }
    vTaskDelete(NULL);
}

void app_main()
{
    printf("main task\n");
    msg_que = xQueueCreate(MQ_SIZE,MSG_SIZE);
    xTaskCreate(task1,"task1",2048,NULL,5,&task1_handle);
    xTaskCreate(task2,"task2",2048,NULL,6,&task2_handle);
    xTaskCreate(task3,"task3",2048,NULL,7,&task3_handle);
    xTaskCreatePinnedToCore(task4,"task4",2048,NULL,8,&task4_handle,taskcore);
    xTaskCreatePinnedToCore(task5,"task5",2048,NULL,9,&task5_handle,taskcore);

}
