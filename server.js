const express = require("express");
const mqtt = require("mqtt");
const path = require("path");

const app = express();
const PORT = 3000;

app.use(express.static(path.join(__dirname, 'public')));

const mqttClient = mqtt.connect('mqtt://185.122.200.9:1883');

mqttClient.on('connect', () => {
        console.log("connected tp MQTT broker");
        mqttClient.subscribe('esp32/led/status', (err) => {
                if (err) {
                        console.log('subscription error: ', err);
                }
        });
});

app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'index.html'));
});

app.listen(PORT, () => {
    console.log(`server running at http://localhost:${PORT}`);
});
