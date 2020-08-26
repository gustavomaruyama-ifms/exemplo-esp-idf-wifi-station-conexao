#include "freertos/FreeRTOS.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "esp_event_loop.h"

void wifi_event_handler(void *arg, esp_event_base_t event_base,	int32_t event_id, void *event_data)
{
	printf("Entrou no manipulador de eventos do WiFi!\n");

	if(event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START){
		printf("Modo Station de WiFi inicializado!\n");
		printf("Conectando com a rede WiFi.\n");
		esp_wifi_connect();
	}

	if(event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_CONNECTED){
		printf("Conectado a rede WiFi.\n");
	}
}


void app_main(void)
{
	nvs_flash_init();
	tcpip_adapter_init();

	esp_event_loop_create_default();
	esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL);

	wifi_init_config_t config = WIFI_INIT_CONFIG_DEFAULT();
	wifi_config_t wifi_config = {
			.sta = {
					.ssid = "",
					.password = "",
			}
	};

	esp_wifi_init(&config);
	esp_wifi_set_mode(WIFI_MODE_STA);
	esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config);
	esp_wifi_start();
}
