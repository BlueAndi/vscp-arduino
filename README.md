#VSCP arduino library

1. [VSCP](https://github.com/BlueAndi/vscp-arduino#vscp)
2. [Library](https://github.com/BlueAndi/vscp-arduino#library)
3. [How to send a VSCP event?](https://github.com/BlueAndi/vscp-arduino#how-to-send-a-vscp-event)
4. [Examples](https://github.com/BlueAndi/vscp-arduino#examples)
5. [FAQ](https://github.com/BlueAndi/vscp-arduino#faq)
6. [Mailing list](https://github.com/BlueAndi/vscp-arduino#mailing-list)
7. [Issues, Ideas and bugs](https://github.com/BlueAndi/vscp-arduino#issues-ideas-and-bugs)
8. [License](https://github.com/BlueAndi/vscp-arduino#license)

##VSCP

![VSCP logo](http://vscp.org/images/vscp_logo.jpg)

The Very Simple Control Protocol (VSCP), an open and free protocol for IoT/m2m automation tasks.

More information can be found on the main site http://www.vscp.org

##Library
This is a arduino library of the VSCP software framework for level 1 devices.
It provides several layers according to the [VSCP specification](http://www.vscp.org/docs/vscpspec/doku.php).

##How to send a VSCP event?

###Define a transmit message

```
vscp_TxMessage  txMsg;
```

###Prepare the transmit message
That means to add the node nickname, the hardcoded flag, the class, the type and the priority.

```
vscp.prepareTxMessage(txMsg, VSCP_CLASS_L1_INFORMATION, VSCP_TYPE_INFORMATION_ON, VSCP_PRIORITY_3_NORMAL);
```

###Add the class and type specific data.

```
txMsg.data[0] = 1;  // Index
txMsg.data[1] = 0;  // Zone
txMsg.data[2] = 0;  // Sub zone
txMsg.dataNum = 3;
```

###Send the event.

```
vscp.write(txMsg);
```

##Examples

###Generic

The generic example shows the basic integration of the VSCP arduino library.

###Seeed-Studio CAN BUS Shield

This example assume that the CAN BUS Shield from Seeed-Studio is used, as well as the corresponding CAN controller library.

- Shield: http://www.seeedstudio.com/wiki/CAN-BUS_Shield
- Library: https://github.com/Seeed-Studio/CAN_BUS_Shield

![Connection to Seeed-Studio CAN BUS Shield](https://github.com/BlueAndi/vscp-arduino/seeed-studio_can_bus_shield.jpg)

###Sparkfun CAN-BUS Shield

This example assume that the CAN-BUS Shield from Sparkfun is used.
Because they provide no arduino library, the MCP2515 library from Frank Kienast is used.

- Shield: https://www.sparkfun.com/products/10039
- Library: https://github.com/franksmicro/Arduino/tree/master/libraries/MCP2515

##FAQ

### Where to find all the VSCP class defines and their corresponding types?

You will find the class defines here:
```
VSCP/src/framework/vscp_class_l1.h
VSCP/src/framework/vscp_class_l1_l2.h
```

You will find the type defines here:
```
VSCP/src/framework/vscp_type_alarm.h
VSCP/src/framework/vscp_type_control.h
VSCP/src/framework/vscp_type_display.h
VSCP/src/framework/vscp_type_information.h
VSCP/src/framework/vscp_type_measurement.h
VSCP/src/framework/vscp_type_measurezone.h
VSCP/src/framework/vscp_type_phone.h
VSCP/src/framework/vscp_type_protocol.h
VSCP/src/framework/vscp_type_remote.h
VSCP/src/framework/vscp_type_security.h
VSCP/src/framework/vscp_type_weather.h
VSCP/src/framework/vscp_type_weather_forecast.h
```

##Mailing list

Are you interesting? Join us on the mailing list: https://groups.google.com/forum/#!forum/vscp

##Issues, Ideas and bugs

If you have further ideas or you found some bugs, great! Create a [issue](https://github.com/BlueAndi/vscp-framework/issues) or if
you are able and willing to fix it by yourself, clone the repository and create a pull request.

##License
The whole source code is published under the [MIT license](http://choosealicense.com/licenses/mit/).
