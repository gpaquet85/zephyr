.. _mb1329_bg96:

STMOD MB1329_BG96
#################

Overview
********

The ``MB1329_BG96`` is a STMOD created by STMicroelectronics. 
It can be used with a stm32l496g_discovery board, and can be found in a `package`_.
It features a ``BG_96`` modem from Quectel. This modem is a worldwide cellular modem for LTE Cat M/Cat NB/EGRPS communication.

The modem can be controlled through AT Commands with a UART communication.

More information for this module at `BG96`_.

Pins Assignment of the MB1329_BG96
==================================

Those appear to be the useful pins for this STMOD.

+------------+-----------------------+---------------------------------------------+
| Pin number | Shield Connector Pin  | Function                                    |
+============+=======================+=============================================+
|   #Pin 1   | CTSS                  | Modem UART CTS                              |
+------------+-----------------------+---------------------------------------------+
|   #Pin 2   | RXDS                  | Modem UART RXD                              |
+------------+-----------------------+---------------------------------------------+
|   #Pin 3   | TXDS                  | Modem UART TXD                              |
+------------+-----------------------+---------------------------------------------+
|   #Pin 4   | RTSS                  | Modem UART RTS                              |
+------------+-----------------------+---------------------------------------------+
|   #Pin 5   | GND                   | Ground                                      |
+------------+-----------------------+---------------------------------------------+
|   #Pin 6   | VCC                   | +5V                                         |
+------------+-----------------------+---------------------------------------------+
|   #Pin 9   | PWRen                 | Modem power enable                          |
+------------+-----------------------+---------------------------------------------+
|   #Pin 12   | RST                   | Modem reset                                |
+------------+-----------------------+---------------------------------------------+


Requirements
************

This shield can only be used with a board which provides a configuration
for STMOD connectors and defines node aliases for UART and GPIO interfaces

Programming
***********

Set ``-DSHIELD="mb1329_bg96"`` when you invoke ``west build``. For example:

west build -p auto -b stm32l496agi6 zephyr/samples/basic/blinky -DSHIELD="mb1329_bg96"

References
**********

.. target-notes::

.. _package:
   https://www.st.com/en/evaluation-tools/p-l496g-cell02.html

.. _BG96:
   https://www.quectel.com/product/bg96.htm
