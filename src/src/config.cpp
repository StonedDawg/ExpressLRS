#include "config.h"
#include "common.h"
#include "POWERMGNT.h"

void
TxConfig::Load()
{
    // Populate the struct from eeprom
    m_eeprom->Get(0, m_config);

    // Check if version number matches
    if (m_config.version != TX_CONFIG_VERSION)
    {
        // If not, revert to defaults for this version
        Serial.println("EEPROM version mismatch! Resetting to defaults...");
        SetDefaults();
    }

    m_modified = false;
}

void
TxConfig::Commit()
{    
    if (!m_modified)
    {
        // No changes
        return;
    }

    // Write the struct to eeprom
    m_eeprom->Put(0, m_config);
    m_eeprom->Commit();

    m_modified = false;
}
// Getters
uint32_t
TxConfig::GetRate()
{
    return m_config.rate;
}

uint32_t
TxConfig::GetTlm()
{
    return m_config.tlm;
}
uint32_t
TxConfig::GetSwitchMode()
{
    return m_config.switchMode;
}
uint32_t
TxConfig::GetPower()
{
    return m_config.power;
}

bool
TxConfig::IsModified()
{
    return m_modified;
}
// Setters
void
TxConfig::SetRate(uint32_t rate)
{
    if (m_config.rate != rate)
    {
        //can only change rate to 50hz or lower in analog7 mode
        if((m_config.switchMode == 2 && rate > 1) || (m_config.switchMode != 2)){
        m_config.rate = rate;
        m_modified = true;
        }
    }
}

void
TxConfig::SetTlm(uint32_t tlm)
{
    if (m_config.tlm != tlm)
    {
        m_config.tlm = tlm;
        m_modified = true;
    }
}

void
TxConfig::SetSwitchMode(uint32_t modeSwitch)
{
    #if defined(Regulatory_Domain_AU_915) || defined(Regulatory_Domain_EU_868) || defined(Regulatory_Domain_FCC_915)

    if (m_config.switchMode != modeSwitch && modeSwitch >= 0 && modeSwitch <4){
        if(modeSwitch == 2){    //if analog7 is selected, change the RATE to 50hz
            m_config.rate = 2;
        }
        m_config.switchMode = modeSwitch;
        m_modified = true;
        
    }
    #endif
}
void
TxConfig::SetPower(uint32_t power)
{
    if (m_config.power != power)
    {
        m_config.power = power;
        m_modified = true;
    }
}

void
TxConfig::SetDefaults()
{
    expresslrs_mod_settings_s *const modParams = get_elrs_airRateConfig(RATE_DEFAULT);
    m_config.version = TX_CONFIG_VERSION;
    SetRate(modParams->index);
    SetTlm(modParams->TLMinterval);
    SetPower(DefaultPowerEnum);
    SetSwitchMode(1);
    Commit();
}

void
TxConfig::SetStorageProvider(ELRS_EEPROM *eeprom)
{
    if (eeprom)
    {
        m_eeprom = eeprom;
    }
}

/////////////////////////////////////////////////////

void
RxConfig::Load()
{
    // Populate the struct from eeprom
    m_eeprom->Get(0, m_config);

    // Check if version number matches
    if (m_config.version != RX_CONFIG_VERSION)
    {
        // If not, revert to defaults for this version
        Serial.println("EEPROM version mismatch! Resetting to defaults...");
        SetDefaults();
    }

    m_modified = false;
}

void
RxConfig::Commit()
{    
    if (!m_modified)
    {
        // No changes
        return;
    }

    // Write the struct to eeprom
    m_eeprom->Put(0, m_config);
    m_eeprom->Commit();

    m_modified = false;
}

// Getters
bool
RxConfig::GetIsBound()
{
    #ifdef MY_UID
        return true;
    #else
        return m_config.isBound;
    #endif
}

uint8_t*
RxConfig::GetUID()
{
    return m_config.uid;
}

uint8_t
RxConfig::GetPowerOnCounter()
{
    return m_config.powerOnCounter;
}

bool
RxConfig::IsModified()
{
    return m_modified;
}

// Setters
void
RxConfig::SetIsBound(bool isBound)
{
    if (m_config.isBound != isBound)
    {
        m_config.isBound = isBound;
        m_modified = true;
    }
}

void
RxConfig::SetUID(uint8_t* uid)
{
    for (uint8_t i = 0; i < UID_LEN; ++i)
    {
        m_config.uid[i] = uid[i];
    }
    m_modified = true;
}

void
RxConfig::SetPowerOnCounter(uint8_t powerOnCounter)
{
    if (m_config.powerOnCounter != powerOnCounter)
    {
        m_config.powerOnCounter = powerOnCounter;
        m_modified = true;
    }
}

void
RxConfig::SetDefaults()
{
    m_config.version = RX_CONFIG_VERSION;
    SetIsBound(false);
    SetPowerOnCounter(0);
    Commit();
}

void
TxConfig::SetStorageProvider(ELRS_EEPROM *eeprom)
{
    if (eeprom)
    {
        m_eeprom = eeprom;
    }
}

/////////////////////////////////////////////////////

void
RxConfig::Load()
{
    // Populate the struct from eeprom
    m_eeprom->Get(0, m_config);

    // Check if version number matches
    if (m_config.version != RX_CONFIG_VERSION)
    {
        // If not, revert to defaults for this version
        Serial.println("EEPROM version mismatch! Resetting to defaults...");
        SetDefaults();
    }

    m_modified = false;
}

void
RxConfig::Commit()
{    
    if (!m_modified)
    {
        // No changes
        return;
    }

    // Write the struct to eeprom
    m_eeprom->Put(0, m_config);
    m_eeprom->Commit();

    m_modified = false;
}

// Getters
bool
RxConfig::GetIsBound()
{
    #ifdef MY_UID
        return true;
    #else
        return m_config.isBound;
    #endif
}

uint8_t*
RxConfig::GetUID()
{
    return m_config.uid;
}

uint8_t
RxConfig::GetPowerOnCounter()
{
    return m_config.powerOnCounter;
}

bool
RxConfig::IsModified()
{
    return m_modified;
}

// Setters
void
RxConfig::SetIsBound(bool isBound)
{
    if (m_config.isBound != isBound)
    {
        m_config.isBound = isBound;
        m_modified = true;
    }
}

void
RxConfig::SetUID(uint8_t* uid)
{
    for (uint8_t i = 0; i < UID_LEN; ++i)
    {
        m_config.uid[i] = uid[i];
    }
    m_modified = true;
}

void
RxConfig::SetPowerOnCounter(uint8_t powerOnCounter)
{
    if (m_config.powerOnCounter != powerOnCounter)
    {
        m_config.powerOnCounter = powerOnCounter;
        m_modified = true;
    }
}

void
RxConfig::SetDefaults()
{
    m_config.version = RX_CONFIG_VERSION;
    SetIsBound(false);
    SetPowerOnCounter(0);
    Commit();
}

void
RxConfig::SetStorageProvider(ELRS_EEPROM *eeprom)
{
    if (eeprom)
    {
        m_eeprom = eeprom;
    }
}
