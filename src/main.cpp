#include <Arduino.h>
#include <NimBLEDevice.h>
#include "esp_bt.h"

// UUIDs do serviço UART (Nordic UART Service - NUS)
#define UART_SERVICE_UUID        "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define UART_CHAR_RX_UUID        "6E400002-B5A3-F393-E0A9-E50E24DCCA9E" // escrita
#define UART_CHAR_TX_UUID        "6E400003-B5A3-F393-E0A9-E50E24DCCA9E" // leitura/notificação

NimBLECharacteristic* txCharacteristic;

// Callback RX
class UART_RX_Callback : public NimBLECharacteristicCallbacks {
    //void onWrite(NimBLECharacteristic* pCharacteristic) override {
    void onWrite(NimBLECharacteristic* pCharacteristic, NimBLEConnInfo& connInfo) override{
        std::string value = pCharacteristic->getValue();
        if(value.length() > 0) {
            Serial.print("Comando recebido: ");
            Serial.println(value.c_str());

            if(value == "1") {
                txCharacteristic->setValue("\nOla\n");
                txCharacteristic->notify();
            } else if(value == "2") {
                txCharacteristic->setValue("\nHello, \nfrom ESP32-S3!\nmandando com +9 dBm\ncambio\ndesligo\n");
                txCharacteristic->notify();
            } else {
                txCharacteristic->setValue("\nComando desconhecido\n");
                txCharacteristic->notify();
            }
        }
    }
};

void setup() {
    Serial.begin(115200);
    Serial.println("Iniciando BLE UART com NimBLE...");

    // Inicializa BLE
    NimBLEDevice::init("ESP32-S3-NimBLE");

    // Ajuste de potência BLE para o máximo (+9 dBm)
    esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_DEFAULT, ESP_PWR_LVL_P9);
    esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV,     ESP_PWR_LVL_P9);
    esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_SCAN,    ESP_PWR_LVL_P9);
    esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_CONN_HDL0, ESP_PWR_LVL_P9);

    Serial.println("Potência BLE configurada para +9 dBm.");

    // Cria servidor BLE
    NimBLEServer* pServer = NimBLEDevice::createServer();

    // Cria serviço UART
    NimBLEService* pService = pServer->createService(UART_SERVICE_UUID);

    // Característica TX (notify)
    txCharacteristic = pService->createCharacteristic(
                          UART_CHAR_TX_UUID,
                          NIMBLE_PROPERTY::NOTIFY
                       );

    // Característica RX (write)
    NimBLECharacteristic* rxCharacteristic = pService->createCharacteristic(
                          UART_CHAR_RX_UUID,
                          NIMBLE_PROPERTY::WRITE
                       );
    rxCharacteristic->setCallbacks(new UART_RX_Callback());

    // Inicia serviço
    pService->start();

    // Inicia advertising
    NimBLEAdvertising* pAdvertising = NimBLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(UART_SERVICE_UUID);
    NimBLEDevice::startAdvertising();

    Serial.println("BLE UART iniciado. Procure pelo dispositivo 'ESP32-S3-NimBLE'.");
}

void loop() {
    delay(1000);
}
