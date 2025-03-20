const client = mqtt.connect('ws://185.122.200.9:9001');

client.on('connect', function () {
    console.log('connected to MQTT');
    client.subscribe("esp32/led/status");
});

client.on('message', function (topic, message) {
    document.getElementById('status').innerText = message.toString();
});

document.getElementById('onButton').addEventListener("click", () => {
    client.publish("esp32/led", "ON");
});

document.getElementById('offButton').addEventListener("click", () => {
    client.publish("esp32/led", "OFF");
});
