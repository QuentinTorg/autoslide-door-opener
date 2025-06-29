#!/usr/bin/env python3
"""Pymodbus synchronous client example.

An example of a single threaded synchronous client.

usage: simple_sync_client.py

All options must be adapted in the code
The corresponding server must be started before e.g. as:
    python3 server_sync.py
"""

# --------------------------------------------------------------------------- #
# import the various client implementations
# --------------------------------------------------------------------------- #
import pymodbus.client as ModbusClient
from pymodbus import (
    FramerType,
    ModbusException,
    pymodbus_apply_logging_config,
)
import time


def run_sync_simple_client(host, port, framer=FramerType.SOCKET):
    """Run sync client."""
    # activate debugging
    pymodbus_apply_logging_config("DEBUG")

    print("get client")
    #client: ModbusClient.ModbusBaseSyncClient

    client = ModbusClient.ModbusSerialClient(
        port,
        framer=framer,
        timeout=3,
        # retries=3,
        baudrate=9600,
        bytesize=8,
        parity="N",
        stopbits=1,
        # handle_local_echo=False,
    )

    print("connect to server")
    client.connect()
    time.sleep(1)

    print("get and verify data")
    for address in [2, 4, 40003, 40005]:
        client.connect()
        print("\n\ntrying address", address)
        try:
            # See all calls in client_calls.py
            rr = client.read_holding_registers(address, count=1, slave=1)
        except ModbusException as exc:
            print(f"Received ModbusException({exc}) from library")
            continue
            client.close()
            time.sleep(1)
            client.connect()
            time.sleep(1)
            #return
        if rr.isError():
            print(f"Received exception from device ({rr})")
            continue
            # THIS IS NOT A PYTHON EXCEPTION, but a valid modbus message
            #client.close()
            #return
        value_int16 = client.convert_from_registers(rr.registers, data_type=client.DATATYPE.INT16)
        print(f"Address {address} Got int16: {value_int16}\n")

#    for address in [1, 2]:
#        print("trying to write address", address)
#        try:
#            rr = client.write_register(address, 1, slave=1)
#        except ModbusException as exc:
#            print(f"Received ModbusException({exc}) from library")
#            continue
#            client.close()
#            time.sleep(1)
#            client.connect()
#            time.sleep(1)
#            #return
#        if rr.isError():
#            print(f"Received exception from device ({rr})")
#            continue
#            # THIS IS NOT A PYTHON EXCEPTION, but a valid modbus message
#            #client.close()
#            #return
#        value_int16 = client.convert_from_registers(rr.registers, data_type=client.DATATYPE.INT16)
#        print(f"\nAddress {address} Got int16: {value_int16}\n")


    print("close connection")
    client.close()


if __name__ == "__main__":
    run_sync_simple_client("127.0.0.1", "/dev/ttyUSB0", FramerType.RTU)
