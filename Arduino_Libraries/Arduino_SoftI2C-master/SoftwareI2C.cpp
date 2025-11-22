/*
  SoftwareI2C.cpp
  2012 Copyright (c) Seeed Technology Inc.  All right reserved.

  Author:Loovee
  Author:Loovee

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <Arduino.h>

#include <Streaming.h>

#include "SoftwareI2C.h"

/*************************************************************************************************
 * Function Name: begin
 * Description:  config IO
 * Parameters: Sda: Scl:
 * Return: none
*************************************************************************************************/
void SoftwareI2C::begin(int Sda, int Scl)
{
    pinSda = Sda;
    pinScl = Scl;

    pinMode(pinScl, OUTPUT);
    pinMode(pinSda, OUTPUT);
    digitalWrite(pinScl, HIGH);
    digitalWrite(pinSda, HIGH);

}

/*************************************************************************************************
 * Function Name: sdaSet
 * Description:  set sda
 * Parameters: ucDta: HIGH or LOW
 * Return: none
*************************************************************************************************/
void SoftwareI2C::sdaSet(uchar ucDta)
{
    pinMode(pinSda, OUTPUT);
    digitalWrite(pinSda, ucDta);
}

/*************************************************************************************************
 * Function Name: sclSet
 * Description:  set scl
 * Parameters: ucDta: HIGH or LOW
 * Return: none
*************************************************************************************************/
void SoftwareI2C::sclSet(uchar ucDta)
{
    digitalWrite(pinScl, ucDta);
}

/*************************************************************************************************
 * Function Name: sdaGet
 * Description:  get sda value
 * Parameters: None
 * Return: return value of sda
*************************************************************************************************/
uchar SoftwareI2C::sdaGet(void)
{
    pinMode(pinSda, INPUT);
    return digitalRead(pinSda);
}

/*************************************************************************************************
 * Function Name: i2c_delay
 * Description:  delay 1 us
 * Parameters: None
 * Return: None
*************************************************************************************************/
void SoftwareI2C::i2c_delay(void)
{
    delayMicroseconds(1);
}

/*************************************************************************************************
 * Function Name: getAck
 * Description:  get ack
 * Parameters: None
 * Return: 0 – Nak; 1 – Ack
*************************************************************************************************/
uchar SoftwareI2C::getAck(void)
{
    unsigned int ntime = 50000;

    pinMode(pinSda, INPUT);
    digitalWrite(pinSda, HIGH);
    DELAY();
    sclSet(HIGH);
    // DELAY();
    while(ntime--)
    {
        if(!digitalRead(pinSda))                                // get ack
        {
            sclSet(LOW);                                        // scl low
            DELAY();
            return GETACK;
        }
    }

    if(ntime<1)
    {
#if __Debug
        Serial.println("get nak");
#endif
    }

    sclSet(LOW);
    DELAY();
    
    return GETNAK;
}

/*************************************************************************************************
 * Function Name: sendAck
 * Description:  send ack signal
 * Parameters: None
 * Return: None
*************************************************************************************************/
void SoftwareI2C::sendAck(void)
{
    sdaSet(LOW);                                                       // sdaSet(LOW)                 
    DELAY();
    sclSet(HIGH);                                                      // sclSet(HIGH)    
    DELAY();
    sclSet(LOW);                                                       //  sclSet(LOW)   
    DELAY();
}

/*************************************************************************************************
 * Function Name: sendNak
 * Description:  send nak signal
 * Parameters: None
 * Return: None
*************************************************************************************************/
void SoftwareI2C::sendNak(void)
{
    sdaSet(HIGH);                                                      /* sdaSet(LOW)                 */
    DELAY();
    sclSet(HIGH);                                                      /* sclSet(HIGH)                */
    DELAY();
    sclSet(LOW);                                                       /* sclSet(LOW)                 */
    DELAY();
}

/*************************************************************************************************
 * Function Name: sendStart
 * Description:   send start clock
 * Parameters: None
 * Return: None
*************************************************************************************************/
void SoftwareI2C::sendStart(void)
{
    sclSet(HIGH);DELAY();DELAY();DELAY();DELAY();                      /* scl =  1                     */
    sdaSet(HIGH);DELAY();DELAY();DELAY();DELAY();                      /* sda  = 1                     */
    sdaSet(LOW);DELAY();DELAY();DELAY();DELAY();                       /* sdaSet(LOW);                */
    DELAY();DELAY();DELAY();DELAY();
    sclSet(LOW);DELAY();DELAY();DELAY();DELAY();                                             /* scl = 0;                     */
                                                                        /* delay_us_cfg(15);            */

}

/*************************************************************************************************
 * Function Name: setClockDivider
 * Description:  setup clock divider for spi bus
 * Parameters: divider – clock divider
 * Return: 0 – setup ok; 1 – setup failed
*************************************************************************************************/
void SoftwareI2C::sendStop(void)
{

    sdaSet(LOW); DELAY();
    sclSet(HIGH);DELAY();
    
    sdaSet(HIGH);DELAY();
    sclSet(LOW);
    for(int i = 0; i<10; i++)
    DELAY();
}

/*************************************************************************************************
 * Function Name: sendBit
 * Description:  send a bit
 * Parameters: bit: 0 or 1?
 * Return: None
*************************************************************************************************/
void SoftwareI2C::sendBit(uchar bit)
{
    if (bit & 0x80) {
        sdaSet(HIGH);
    } else {
        sdaSet(LOW);
    }
    DELAY();
    sclSet(HIGH);
    DELAY();
    sclSet(LOW);

}

/*************************************************************************************************
 * Function Name: revBit
 * Description:  receive a bit
 * Parameters: None
 * Return: value
*************************************************************************************************/
uchar SoftwareI2C::revBit()
{
    unsigned  char  ucRt;
    DELAY();
    sclSet(HIGH);
    DELAY();
    ucRt = sdaGet();
    sclSet(LOW);
    return  ucRt;

}

/*************************************************************************************************
 * Function Name: sendByte
 * Description:  send a byte
 * Parameters: ucDta: data to send
 * Return: None
*************************************************************************************************/
void SoftwareI2C::sendByte(uchar ucDta)
{
    unsigned  char  i;

    i = 8;
    do {
        sendBit(ucDta);
        ucDta=ucDta << 1;
    } while (--i != 0);

}

/*************************************************************************************************
 * Function Name: sendByteAck
 * Description:  send a byte and get ack signal
 * Parameters: ucDta: data to send
 * Return: 0: get nak  1: get ack
*************************************************************************************************/
uchar SoftwareI2C::sendByteAck(uchar ucDta)
{
    sendByte(ucDta);
    return getAck();
}

/*************************************************************************************************
 * Function Name: revByte
 * Description:  receive a byte
 * Parameters: None
 * Return: value that receive
*************************************************************************************************/
uchar SoftwareI2C::revByte()
{
    unsigned  char  ucRt;
    unsigned  char  i;

    i = 8;
    do {
        ucRt  =  (ucRt << 1) + revBit();
    } while (--i != 0);

    return ucRt;

}

/*************************************************************************************************
 * Function Name: beginTransmission
 * Description:  send begin signal
 * Parameters: divider – clock divider
 * Return: 0: get nak  1: get ack
*************************************************************************************************/
uchar SoftwareI2C::beginTransmission(uchar addr)
{

    sendStart();                       // start signal
    return sendByteAck(addr<<1);       // send write address and get ack

}

/*************************************************************************************************
 * Function Name: endTransmission
 * Description:  send stop signal
 * Parameters: None
 * Return: None
*************************************************************************************************/
void SoftwareI2C::endTransmission()
{
    sendStop();
    
}

/*************************************************************************************************
 * Function Name: write
 * Description:  send a byte
 * Parameters: dta: data to send
 * Return: 0: get nak  1: get ack
*************************************************************************************************/  
uchar SoftwareI2C::write(uchar dta)
{
    return sendByteAck(dta);
}

/*************************************************************************************************
 * Function Name: write
 * Description:  write array
 * Parameters: len - length of the array
               *dta - array to be sent
 * Return: 0: get nak  1: get ack
*************************************************************************************************/
uchar SoftwareI2C::write(uchar len, uchar *dta)
{
    for(int i=0; i<len; i++)
    {
    
        if(GETACK != write(dta[i]))
        {
            return GETNAK;
        }
    }
    
    return GETACK;
}

/*************************************************************************************************
 * Function Name: requestFrom
 * Description:  request data from slave
 * Parameters: addr - address of slave
               len  - length of request
 * Return: 0: get nak  1: get ack
*************************************************************************************************/
uchar SoftwareI2C::requestFrom(uchar addr, uchar len)
{

    sendStart();                       // start signal
    recv_len = len;
    return sendByteAck((addr<<1)+1);       // send write address and get ack
}

/*************************************************************************************************
 * Function Name: read
 * Description:  read a byte from i2c
 * Parameters: None
 * Return: data get
*************************************************************************************************/
uchar SoftwareI2C::read()
{
    
    if(-1 == recv_len)return 0;
    
    uchar dta = revByte();
    
    recv_len--;
    
    if(recv_len>0)
    sendAck();
    else
    {
        sendNak();
        sendStop();
        recv_len=-1;
    }

    return dta;
 
}

SoftwareI2C Wire;
    
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
