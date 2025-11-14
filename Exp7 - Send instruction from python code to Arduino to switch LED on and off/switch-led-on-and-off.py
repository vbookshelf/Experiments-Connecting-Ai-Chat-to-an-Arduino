

import serial
import json
import time

# This needs to be changed to
# match the port you are using to
# connect to the Arduino.
PORT = '/dev/cu.usbserial-110'



def control_led(state, port=PORT, baud_rate=9600):
    """
    Connects to an Arduino to control the built-in LED.
    This function is exposed as a "tool" to the LLM.

    Args:
        state (str): The desired state of the LED. Must be 'on' or 'off'.
    
    Returns:
        dict: A dictionary containing the status of the operation.
    """
    if state.lower() not in ['on', 'off']:
        return {"status": "error", "message": "Invalid state. Must be 'on' or 'off'."}

    # Construct the command based on the desired state
    command = f"LED_{state.upper()}\n"

    try:
        # Establish serial connection
        ser = serial.Serial(port, baud_rate, timeout=2)
        time.sleep(2) # Wait for the connection to establish

        # Send the command to the Arduino
        ser.write(command.encode('utf-8'))
        print(f"Sent command: '{command.strip()}' to {port}")

        # Wait for and read the confirmation response
        response = ser.readline().decode('utf-8').strip()
        print(f"Received response: '{response}'")
        
        ser.close()
        
        if response:
            return {"status": "success", "response": response}
        else:
            return {"status": "error", "message": "No response from device."}

    except Exception as e:
        print(f"An error occurred: {e}")
        return {"status": "error", "message": str(e)}
		
		

# --- This is how the LLM's environment would call the function ---
if __name__ == '__main__':
	
    # Scenario 1: LLM decides to turn the light on
    print()
    print("--- Action: Turn LED ON ---")
    result_on = control_led(state='on')
    # LLM formulates a response based on the result
    if result_on['status'] == 'success':
        print(f"LLM to User: Okay, I've turned the light on. The device confirmed: '{result_on['response']}'")
    else:
        print(f"LLM to User: Sorry, I couldn't turn the light on. Reason: {result_on['message']}")

    time.sleep(5) # Wait a few seconds

    # Scenario 2: LLM decides to turn the light off
    print("\n--- Action: Turn LED OFF ---")
    result_off = control_led(state='off')
    if result_off['status'] == 'success':
        print(f"LLM to User: Okay, the light is now off. The device confirmed: '{result_off['response']}'")
    else:
        print(f"LLM to User: I ran into an issue turning the light off. Reason: {result_off['message']}")
		
    print()
   
   
   
		
		