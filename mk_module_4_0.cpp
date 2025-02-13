#include "pxt.h"
#include <stdio.h>
#include <ctype.h>
#include "MicroBitConfig.h"
#include "Module_4_0_Service.h"
#include "BLEAdvManager.h"

using namespace pxt;

/**
 * Support for M0uld K1ng Module 4.0.
 */
namespace mk_module_4_0 
{
    Module_4_0_Service* _pService = NULL;

    //%
    Module_4_0_Service* getService() 
    {
        if (NULL == _pService)
        {
            BLEAdvManager *p_BLEAdvManager = BLEAdvManager::getInstance();

            _pService = new Module_4_0_Service(*p_BLEAdvManager);
        }

        return _pService;
    }


    //%
    void init(uint8_t moduleNo) 
    {
        Module_4_0_Service *pService = getService();

        pService->connect();
    }


    //% 
    void setChannelValue(uint8_t moduleNo, uint8_t channel, float value_pct) 
    {
        Module_4_0_Service *pService = getService();

        pService->setChannelValue(moduleNo * 3 + channel, value_pct);
    }   


    //% 
    void setChannelOffset(uint8_t moduleNo, uint8_t channel, float offset_pct) 
    {
        Module_4_0_Service *pService = getService();

        pService->setChannelOffset(moduleNo * 3 + channel, offset_pct);
    }   


    //% 
    void setChannelMax(uint8_t moduleNo, uint8_t channel, float maximum_pct) 
    {
        Module_4_0_Service *pService = getService();

        pService->setChannelMax(moduleNo * 3 + channel, maximum_pct);
    }   


    //% 
    void setChannelReverse(uint8_t moduleNo, uint8_t channel, bool reverse) 
    {
        Module_4_0_Service *pService = getService();

        pService->setChannelReverse(moduleNo * 3 + channel, reverse);
    }   


    //% 
    void setZeroHysteresis(uint8_t moduleNo, float zeroHysteresis_pct) 
    {
        Module_4_0_Service *pService = getService();

        pService->setZeroHysteresis(zeroHysteresis_pct);
    }   


    //% 
    void reset(uint8_t moduleNo) 
    {
        Module_4_0_Service *pService = getService();

        pService->reset();
    }   


    //% 
    void setData(uint8_t moduleNo) 
    {
        Module_4_0_Service *pService = getService();

        pService->setData();
    }   


    //% 
    void stopAdvertising(uint8_t moduleNo) 
    {
        Module_4_0_Service *pService = getService();

        if (NULL != pService) 
        {
            pService->stopAdvertising();
        }        
    }   


    //% 
    uint8_t getVersion(uint8_t moduleNo) 
    {
        Module_4_0_Service *pService = getService();

        return pService->getVersion();
    }   
}