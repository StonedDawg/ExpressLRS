#pragma once 

#include <Arduino.h>
#include "targets.h"
#include "elrs_eeprom.h"

#define TX_CONFIG_VERSION   1
#define RX_CONFIG_VERSION   1
#define UID_LEN             6

typedef struct {
    uint32_t    version;
    uint32_t    rate;
    uint32_t    tlm;
    uint32_t    power;

    uint32_t    switchMode;

} tx_config_t;

class TxConfig
{
public:
    void Load();
    void Commit();

    // Getters
    uint32_t GetRate();
    uint32_t GetTlm();
    uint32_t GetPower();
    uint32_t GetSwitchMode();
    bool     IsModified();

    // Setters
    void SetRate(uint32_t rate);
    void SetTlm(uint32_t tlm);
    void SetPower(uint32_t power);
    void SetSwitchMode(uint32_t modeSwitch);
    void SetDefaults();
    void SetStorageProvider(ELRS_EEPROM *eeprom);

private:
    tx_config_t m_config;
    ELRS_EEPROM *m_eeprom;
    bool        m_modified;
};


typedef struct {
    uint32_t    version;
    bool        isBound;
    uint8_t     uid[UID_LEN];
    uint8_t     powerOnCounter;
} rx_config_t;

class RxConfig
{
public:
    void Load();
    void Commit();

    // Getters
    bool     GetIsBound();
    uint8_t* GetUID();
    uint8_t  GetPowerOnCounter();
    bool     IsModified();

    // Setters
    void SetIsBound(bool isBound);
    void SetUID(uint8_t* uid);
    void SetPowerOnCounter(uint8_t powerOnCounter);
    void SetDefaults();
    void SetStorageProvider(ELRS_EEPROM *eeprom);

private:
    rx_config_t m_config;
    ELRS_EEPROM *m_eeprom;
    bool        m_modified;
};
