#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

// Declaração dos semáforos
SemaphoreHandle_t semTarefa1;
SemaphoreHandle_t semTarefa2;
SemaphoreHandle_t semTarefa3;

// Função da Tarefa 1
void tarefa1(void *pvParameters) {
    while(1) {
        xSemaphoreTake(semTarefa1, portMAX_DELAY); // Espera pelo semáforo
        printf("[Tarefa 1] Executou - Guilherme\n");
        vTaskDelay(pdMS_TO_TICKS(1000)); // Intervalo de 1 segundo
        xSemaphoreGive(semTarefa2); // Libera a Tarefa 2
    }
}

// Função da Tarefa 2
void tarefa2(void *pvParameters) {
    while(1) {
        xSemaphoreTake(semTarefa2, portMAX_DELAY);
        printf("[Tarefa 2] Executou - Guilherme\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
        xSemaphoreGive(semTarefa3); // Libera a Tarefa 3
    }
}

// Função da Tarefa 3
void tarefa3(void *pvParameters) {
    while(1) {
        xSemaphoreTake(semTarefa3, portMAX_DELAY);
        printf("[Tarefa 3] Executou - Guilherme\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
        xSemaphoreGive(semTarefa1); // Libera a Tarefa 1 novamente
    }
}

void app_main(void) {
    // Criação dos semáforos binários
    semTarefa1 = xSemaphoreCreateBinary();
    semTarefa2 = xSemaphoreCreateBinary();
    semTarefa3 = xSemaphoreCreateBinary();

    if(semTarefa1 == NULL || semTarefa2 == NULL || semTarefa3 == NULL) {
        printf("Erro ao criar semáforo!\n");
        return;
    }

    // Inicializa o ciclo dando permissão para a Tarefa 1 começar
    xSemaphoreGive(semTarefa1);

    // Criação das tarefas
    xTaskCreate(tarefa1, "Tarefa 1", 2048, NULL, 1, NULL);
    xTaskCreate(tarefa2, "Tarefa 2", 2048, NULL, 1, NULL);
    xTaskCreate(tarefa3, "Tarefa 3", 2048, NULL, 1, NULL);
}
