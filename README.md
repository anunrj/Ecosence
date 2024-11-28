# Ecosence
 ESP32 microcontroller-based sensors with AWS IoT services and visualization via AWS QuickSight.

 In this phase of the Eco Sense project, the focus is on the implementation, integration, and evaluation of the system's deliverables. The design and conceptual framework transition into a fully functional IoT solution, where all components—ranging from the ESP32 microcontroller to the suite of environmental sensors and AWS cloud services—are brought together to create a seamless operation. Comprehensive testing is conducted to ensure the accuracy and reliability of sensor data, the efficiency of data transmission, and the responsiveness of the system to dynamic environmental changes.
The implementation highlights the project's advanced automation capabilities, including threshold-based actions such as activating grow lights in response to low light intensity and notifying users of significant environmental variations. These automated features work in parallel with real-time data visualization and reporting, powered by AWS Quick Sight, offering users actionable insights through dynamic dashboards and scheduled reports.
This phase also focuses on ensuring the robustness and scalability of the system, addressing the challenges of handling high-frequency data streams, maintaining system stability, and optimizing resources for long-term use. By integrating advanced analytics with automated controls, the Eco Sense project demonstrates its capability to enhance resource management, monitor critical environmental parameters, and provide valuable insights to optimize plant growth. This stage marks a significant step towards delivering a comprehensive, efficient, and intelligent solution for modern agricultural and environmental monitoring needs.

2)Pre-requisites
2.1)Hardware Requirements
•	Microcontroller: ESP32 (or ESP32-S3 for enhanced processing power).
•	Sensors: DHT22 (temperature & humidity), capacitive soil moisture sensor, and light intensity sensor.
•	Actuators: Grow light (LED).
•	Power Solutions: Reliable power supply or optional backup (rechargeable battery/solar panel).
•	Additional Peripherals: USB cable for ESP32 programming, breadboard, jumper wires for hardware connections.
2.2)Software Requirements
•	Operating Systems: Windows, macOS, or Linux for the development environment.
•	Programming Tools: Arduino IDE or PlatformIO for ESP32 programming.
•	Libraries:
o	WiFiClientSecure for secure network communication.
o	PubSubClient for MQTT messaging.
o	WebServer for hosting the local HTTP server.
•	Cloud Services: AWS IoT Core for device management, AWS Timestream for data storage, AWS QuickSight for visualization.
•	Additional Tools: Serial monitor (e.g., integrated in Arduino IDE) for debugging.
2.3)Credentials
•	Wi-Fi Network: SSID and password for ESP32 internet access.
•	AWS IoT Core:
o	Access Key and Secret Key.
o	IoT endpoint URL.
o	Certificates: Private key, public key, and root CA for TLS authentication.
•	MQTT Broker: Configuration details (topics, QoS levels).
2.4)Network Requirements
•	Firewall Rules:
o	Open ports for MQTT communication (default: 1883 or 8883 for secure connections).
o	Allow outgoing traffic to AWS IoT Core endpoints.
•	IP Addresses: Configure ESP32 to dynamically obtain an IP address via DHCP or assign a static IP for web server hosting.
•	Local Network: Stable internet connection with low latency for real-time operations.
2.5)Dependencies
•	Hardware Components: Properly functioning sensors, microcontroller, and actuators.
•	AWS Services:
o	Active AWS account with necessary IoT Core, Timestream, and QuickSight resources.
o	AWS Lambda (optional) for data processing.
•	ESP32 Drivers: Installed on the host machine to enable communication with the microcontroller.

2.6)Skillset
•	Technical Expertise:
o	Familiarity with IoT protocols like MQTT and HTTP.
o	Basic knowledge of Arduino programming and ESP32 libraries.
o	Experience configuring cloud services like AWS IoT Core and QuickSight.
o	Network troubleshooting skills for debugging connectivity issues.
•	Optional:
o	Understanding of JSON for data payload formatting.
o	Basic electronics knowledge for assembling sensors and actuators.
3. Environment Setup
3.1)Steps to Prepare the Deployment Environment
1.	Set Up the Hardware:
o	Assemble the sensors (DHT22, capacitive soil moisture sensor, and photosensor) with the ESP32 microcontroller.
o	Connect the grow light (LED) to the ESP32 GPIO pins for automation.
o	Ensure proper wiring and secure connections using a breadboard or soldering.
o	Power the ESP32 via USB or a reliable external power source.
2.	Configure the ESP32:
o	Install the ESP32 driver on your host machine to enable USB communication.
o	Open the Arduino IDE or PlatformIO and install the necessary libraries (WiFiClientSecure, PubSubClient, and WebServer).
o	Load the ESP32 firmware with pre-configured Wi-Fi credentials, AWS IoT settings, and sensor logic.
3.	Set Up the Local Web Server:
o	Configure the WebServer API in the ESP32 code to serve real-time data over HTTP.
o	Ensure that the ESP32 can host a webpage accessible via its local IP address.
4.	Configure AWS IoT Core:
o	Log in to the AWS Management Console.
o	Create a Thing in IoT Core and download the certificate files (private key, public key, and root CA).
o	Attach a policy to the Thing, allowing it to publish and subscribe to MQTT topics.
o	Note the IoT endpoint for integration with the ESP32.
5.	Set Up AWS Timestream:
o	Create a database and table in AWS Timestream for storing sensor data.
o	Ensure the table is configured to handle time-series data with proper retention policies.
6.	Set Up AWS QuickSight:
o	Connect QuickSight to the Timestream database.
o	Create dashboards to visualize temperature, humidity, soil moisture, and light intensity.
o	Add calculations, such as Vapour Pressure Deficit (VPD), for actionable insights.
7.	Enable AWS SNS for Notifications:
o	Configure Simple Notification Service (SNS) to send alerts for critical conditions (e.g., low soil moisture or high temperature).
o	Integrate SNS with IoT Core for automated notifications.
8.	Database and Backup Setup:
o	Ensure all data pushed to AWS Timestream is automatically backed up according to AWS policies.
o	Set up local logging on the ESP32, if applicable, for offline debugging and data redundancy.
3.2)Installation of Necessary Software
•	Arduino IDE/PlatformIO: For programming the ESP32.
•	AWS CLI: To interact with AWS services and validate configurations.
•	Browser: For accessing the local web server and AWS Console.
•	Monitoring Tools: Tools like MQTT Explorer (optional) for testing MQTT messages.
3.3)Configuration of Hardware, Servers, or Cloud Instances
•	Assign a static IP to the ESP32 if required for stable local network access.
•	Open necessary firewall ports (e.g., 1883 or 8883) for MQTT communication.
•	Ensure the cloud environment has appropriate IAM roles for AWS services (IoT Core, Timestream, QuickSight, SNS).


4. Deployment Steps
Step-by-Step Instructions
1.	Prepare the Hardware:
o	Assemble and connect the DHT22, capacitive soil moisture sensor, and photosensor to the ESP32 microcontroller using jumper wires.
o	Connect the grow light (LED) to the designated GPIO pin on the ESP32.
o	Power the ESP32 using a USB connection or an external power source.
2.	Flash the ESP32 Firmware:
o	Open the Arduino IDE or PlatformIO and load the ESP32 firmware code.
o	Ensure the code includes:
	Wi-Fi credentials (SSID and password).
	AWS IoT Core endpoint, Thing name, and certificates.
	Configuration for connected sensors and actuators.
o	Select the appropriate board and port in the Arduino IDE.
o	Compile and upload the code to the ESP32.
3.	Configure AWS IoT Core:
o	Log in to AWS and navigate to IoT Core.
o	Create a Thing and download the device certificate, private key, and root CA file.
o	Attach an IoT policy to the Thing with permissions for iot:Publish, iot:Subscribe, and iot:Connect.
o	Note the MQTT endpoint URL for integration with the ESP32 firmware.
4.	Set Up AWS Timestream:
o	Create a database and table in AWS Timestream to store environmental sensor data.
o	Configure the retention period for the data as required (e.g., 30 days for memory, 365 days for magnetic storage).
o	Ensure the ESP32 firmware is publishing data to the appropriate Timestream table via MQTT.
5.	Integrate AWS QuickSight:
o	Connect AWS QuickSight to the Timestream database.
o	Create a visualization dashboard displaying metrics such as temperature, humidity, soil moisture, and light intensity.
o	Add a calculated field for Vapour Pressure Deficit (VPD) to provide actionable insights.
6.	Set Up Local Web Server:
o	Ensure the WebServer API in the ESP32 firmware is correctly configured.
o	Access the ESP32's local IP address to view live sensor data and system diagnostics via a web browser.
7.	Configure AWS SNS for Notifications:
o	Set up a Simple Notification Service (SNS) topic to send alerts for critical environmental conditions.
o	Configure IoT rules to trigger notifications when threshold conditions are met (e.g., soil moisture below 30%).



