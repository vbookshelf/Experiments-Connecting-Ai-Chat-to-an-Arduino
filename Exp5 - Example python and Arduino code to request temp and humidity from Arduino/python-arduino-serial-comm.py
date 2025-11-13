
import serial # Note that this package is named: pyserial 
import json
import time

# This needs to be changed to
# match the port you are using to
# connect to the Arduino.
PORT = '/dev/cu.usbserial-110'



# Define a function

def get_sensor_readings(port=PORT, baud_rate=9600):
    """
    Connects to an Arduino over a serial port, requests sensor data,
    and returns the temperature and humidity as a dictionary.
    This function is exposed as a "tool" to the LLM.
    """
    try:
		
        # Establish serial connection
		# ----------------------------------
		
        ser = serial.Serial(port, baud_rate, timeout=2)
        time.sleep(2) # Wait for the connection to establish
		

        # Send the command to Arduino to request data:
		# ----------------------------------
		
		# The code running on the Arduino is listening for this text: READ_SENSORS
        ser.write(b'READ_SENSORS\n')
		
        print()
        print(f"Sent 'READ_SENSORS' command to {port}")
		
		
        # Response from the Arduino:
		# ----------------------------------
		
        # Wait for and read the response from the Arduino.
		# The response will be formatted as JSON.
        response = ser.readline().decode('utf-8').strip()
        print(f"Received response: {response}")
        print()

        # Close the connection
        ser.close()
		

        # Parse the JSON response
		# ----------------------------------
		
        if response:
            data = json.loads(response)
            return data
        else:
            return {"error": "No response from device."}

    except serial.SerialException as e:
        print(f"Serial Error: {e}")
        return {"error": f"Could not connect to device on {port}."}
    except json.JSONDecodeError:
        print(f"JSON Decode Error: Received invalid data: {response}")
        return {"error": "Invalid data format received from device."}
    except Exception as e:
        print(f"An unexpected error occurred: {e}")
        return {"error": "An unexpected error occurred."}
		


if __name__ == '__main__':
	
    # Call the function
    sensor_data = get_sensor_readings()

    if "error" not in sensor_data:
        
        response_to_user = f"The current temperature is {sensor_data['temperature']}°C and the humidity is {sensor_data['humidity']}%."
    else:
        
        response_to_user = f"I'm sorry, I couldn't retrieve the sensor data. Reason: {sensor_data['error']}"

    print(response_to_user)
    print()
	
	