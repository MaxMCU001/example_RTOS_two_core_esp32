#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"
#include "freertos/task.h"
#include "esp_task_wdt.h"

void print_core_0(void *pvParameters)
{
	while(1)
	{
		printf("Task is running on core ");
		printf("%d\n",xPortGetCoreID());
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void print_core_1(void *pvParameters)
{
	while(1)
	{
		printf("Task is running on core ");
		printf("%d\n",xPortGetCoreID());
		vTaskDelay(2000 / portTICK_PERIOD_MS);
	}
}

void app_main(void)
{
    esp_task_wdt_deinit();

	xTaskCreatePinnedToCore(
			print_core_0,				// Function name of the task
			"Print 1",			        // Name of the task (e.g. for debugging)
			2048,				        // Stack size (bytes)
			NULL,				        // Parameter to pass
			1,					        // Task priority
			NULL,				        // Task handle
			0					        // run on Core 0
			);
	xTaskCreatePinnedToCore(
	        print_core_1,       // Function name of the task
	        "Print 2",          // Name of the task (e.g. for debugging)
	        2048,               // Stack size (bytes)
	        NULL,               // Parameter to pass
	        1,                  // Task priority
	        NULL,               // Task handle
	        1                   // run on Core 1
	    );

}
