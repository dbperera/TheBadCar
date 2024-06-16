import requests #Please install with PIP: pip install requests
import json
req = None

print("Bushfire Analyser Drone RC: The BAD Car!")
print("A remote control car designed to scan environments for potential bushfire threats.\n")

print("Retrieving data from ThingSpeak.")
req = requests.get("http://api.thingspeak.com/channels/2530936/feeds/last.json?api_key=DMHPL51SNZSG736U")
Feed = requests.get("https://api.thingspeak.com/channels/2530936/fields/1.json?api_key=DMHPL51SNZSG736U&results=2")
Feed = requests.get("https://api.thingspeak.com/channels/2530936/feeds.json?api_key=DMHPL51SNZSG736U&results=2")
Channel = requests.get("https://api.thingspeak.com/channels/2530936/feeds.json?api_key=DMHPL51SNZSG736U&results=1")


Channel = json.loads(Channel.text)
ChannelInfo = Channel["channel"]
ChannelData = Channel["feeds"]
ChannelData = ChannelData[0]

print("Device Name: " + ChannelInfo['name'])
print("About this device: " + ChannelInfo['description'])
print("Latest Entry: " + ChannelInfo['updated_at'])
print("Current Location: " + ChannelInfo['latitude'] + ", " + ChannelInfo['longitude'] + "\n")

ChannelInfo.pop('id')
ChannelInfo.pop('name')
ChannelInfo.pop('description')
ChannelInfo.pop('latitude')
ChannelInfo.pop('longitude')
ChannelInfo.pop('created_at')
ChannelInfo.pop('updated_at')
ChannelInfo.pop('last_entry_id')

ChannelData.pop('created_at')
ChannelData.pop('entry_id')

Fields = []

#for Field in Fields:

for index in ChannelData:
	if ChannelData[index] == None:
		break
	Fields.append((ChannelInfo[index], float(ChannelData[index])))

print("Data:")
for Field in Fields:
	Labels = Field[0].split()
	Labels[len(Labels)-1] = Labels[len(Labels)-1][1:len(Labels[len(Labels)-1]) - 1]
	for Label in range(len(Labels) - 1):
		print(Labels[Label], end='')
		if Label != len(Labels) - 2:
			print(" ", end='')
	print(": " + str(Field[1]) + Labels[len(Labels) - 1])
